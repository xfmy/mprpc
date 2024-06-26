#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <fmt/core.h>

#include "rpc_channel.h"
#include "rpc_closure.h"
#include "rpc_controller.h"
#include "tinyPB_protocol.h"
#include "tinyPB_coder.h"
#include "muduo/base/Logging.h"
#include "error_code.h"
#include "random_number.h"
#include "tcp_client.h"
#include "consul.h"

namespace tinyrpc {

RpcChannel::RpcChannel()
{
    // LOG_INFO << "RpcChannel";
    // client_ = std::make_shared<tinyrpc::TcpClient>(peer_addr);
}

RpcChannel::~RpcChannel()
{ // LOG_INFO << "~RpcChannel";
}

void RpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                            google::protobuf::RpcController* controller,
                            const google::protobuf::Message* request,
                            google::protobuf::Message* response,
                            google::protobuf::Closure* done)
{
    std::shared_ptr<tinyrpc::TinyPBProtocol> req_protocol =
        std::make_shared<tinyrpc::TinyPBProtocol>();

    RpcClosure* my_rpcClosure = dynamic_cast<RpcClosure*>(done);
    RpcController* my_controller = dynamic_cast<RpcController*>(controller);

    // 入参参数完整性判断
    if (my_controller == NULL || request == NULL || response == NULL)
    {
        LOG_ERROR << "failed callmethod, RpcController convert error";
        my_controller->SetError(ERROR_RPC_CHANNEL_INIT,
                                "controller or request or response NULL");
        if (my_rpcClosure) my_rpcClosure->Run();
        return;
    }

    // 初始化网络
    if (!init_) 
    { 
        ConsulClient consul;
        std::unique_ptr<muduo::net::InetAddress> serviceAddrPtr =
            consul.DiscoverService(method->service()->name());
        if (!serviceAddrPtr)
        {
            LOG_ERROR << "No service found available in consul";
            my_controller->SetError(ERROR_RPC_CHANNEL_INIT,
                                    "No service found available in consul");
            if (my_rpcClosure) my_rpcClosure->Run();
            return;
        }
        client_ = std::make_shared<tinyrpc::TcpClient>(*serviceAddrPtr);
        init_ = true;
    }

    //设置msgId
    if (my_controller->GetMsgId().empty())
    {
        req_protocol->msgId_ = tinyrpc::GetRandomNumberString();
        my_controller->SetMsgId(req_protocol->msgId_);
    }
    else
    {
        // 如果 controller 指定了 msg id, 直接使用
        req_protocol->msgId_ = my_controller->GetMsgId();
    }

    req_protocol->methodName_ = method->full_name();

    LOG_INFO << req_protocol->msgId_ + "| call method name->" +
                    req_protocol->methodName_;

    // requeset 的序列化
    if (!request->SerializeToString(&req_protocol->pbData_))
    {
        std::string err_info = "failde to serialize";
        my_controller->SetError(ERROR_FAILED_SERIALIZE, err_info);

        LOG_ERROR << req_protocol->msgId_ + err_info + "origin requeset->" +
                         request->ShortDebugString();
        if (my_rpcClosure) my_rpcClosure->Run();
        return;
    }

    //判断网络连接是否
    if (!client_->connected())
    {
        my_controller->SetError(ERROR_FAILED_CONNECT, "network connect error");

        LOG_ERROR << fmt::format(
            "{} | connect error, error coode[{}], error info[{}], "
            "peer addr[{}]",
            req_protocol->msgId_, my_controller->GetErrorCode(),
            my_controller->GetErrorInfo(), client_->GetPeerAddrString());

        if (my_rpcClosure) my_rpcClosure->Run();

        return;
    }

    LOG_INFO << fmt::format("{} | connect success, peer addr[{}]",
                            req_protocol->msgId_, client_->GetPeerAddrString());

    // 发起rpc调用网络请求
    client_->request(req_protocol);

    LOG_INFO << fmt::format(
        "{} | send rpc request success. call method name[{}], "
        "peer addr[{}]",
        req_protocol->msgId_, req_protocol->methodName_,
        client_->GetPeerAddrString());

    std::shared_ptr<tinyrpc::TinyPBProtocol> resp_protocol =
        std::make_shared<tinyrpc::TinyPBProtocol>();

    // 客户端同步等待rpc响应,并通过control类控制
    bool timeout = client_->GetTinyPBProtocol(my_controller, resp_protocol);

    // 超时处理
    if (!timeout)
    {
        LOG_INFO << fmt::format("{}| call rpc timeout arrive",
                                my_controller->GetMsgId());

        my_controller->StartCancel();
        my_controller->SetError(
            ERROR_RPC_CALL_TIMEOUT,
            "rpc call timeout " + std::to_string(my_controller->GetTimeout()));

        if (my_rpcClosure) my_rpcClosure->Run();
    }

    LOG_INFO << fmt::format(
        "{} | success get rpc response, call method name[{}], peer "
        "addr[{}]",
        resp_protocol->msgId_, resp_protocol->methodName_,
        client_->GetPeerAddrString());

    // 解析响应数据
    if (!response->ParseFromString(resp_protocol->pbData_))
    {
        LOG_ERROR << resp_protocol->msgId_ + "| serialize error";
        my_controller->SetError(ERROR_FAILED_SERIALIZE, "serialize error");
        if (my_rpcClosure) my_rpcClosure->Run();
        return;
    }

    // 判断错误码
    if (resp_protocol->errorCode_ != 0)
    {
        LOG_ERROR << fmt::format(
            "{} | call rpc methood[{}] failed, error "
            "code[{}], error info[{}]",
            resp_protocol->msgId_, resp_protocol->methodName_,
            resp_protocol->errorCode_, resp_protocol->errorInfo_);

        my_controller->SetError(resp_protocol->errorCode_,
                                resp_protocol->errorInfo_);
        if (my_rpcClosure) my_rpcClosure->Run();
        return;
    }

    LOG_INFO << fmt::format(
        "{} | call rpc success, call method name[{}], peer addr[{}]",
        resp_protocol->msgId_, resp_protocol->methodName_,
        client_->GetPeerAddrString());
    if (my_rpcClosure) my_rpcClosure->Run();
}


} // namespace tinyrpc

// void RpcChannel::Init(ControllerPtr controller, MessagePtr reqest,
//                       MessagePtr response, ClosurePtr done)
// {
//     if (isInit_)
//     {
//         return;
//     }
//     controller_ = controller;
//     request_ = reqest;
//     response_ = response;
//     closure_ = done;
//     isInit_ = true;
// }

// google::protobuf::RpcController* RpcChannel::getController()
// {
//     return controller_.get();
// }

// google::protobuf::Message* RpcChannel::getRequest() { return request_.get();
// }

// google::protobuf::Message* RpcChannel::getResponse() { return
// response_.get(); }

// google::protobuf::Closure* RpcChannel::getClosure() { return closure_.get();
// }

// tinyrpc::TcpClient* RpcChannel::getTcpClient() { return client_.get(); }

// muduo::net::InetAddress RpcChannel::FindAddr(const std::string& str)
// {
//     if (IPNetAddr::CheckValid(str))
//     {
//         return std::make_shared<IPNetAddr>(str);
//     }
//     else
//     {
//         auto it = Config::GetGlobalConfig()->m_rpc_stubs.find(str);
//         if (it != Config::GetGlobalConfig()->m_rpc_stubs.end())
//         {
//             INFOLOG("find addr [%s] in global config of str[%s]",
//                     (*it).second.addr->toString().c_str(), str.c_str());
//             return (*it).second.addr;
//         }
//         else
//         {
//             INFOLOG("can not find addr in global config of str[%s]",
//                     str.c_str());
//             return nullptr;
//         }
//     }
// }

// namespace tinyrpc {
// void RpcChannel::CallMethod(
//     const PROTO::MethodDescriptor *method,
//     PROTO::RpcController *controller,
//     const PROTO::Message *request,
//     PROTO::Message *response,
//     PROTO::Closure *done)
// {
//     std::string sendData;
//     std::string requestData;
//     request->SerializeToString(&requestData);
//     const PROTO::ServiceDescriptor *service = method->service();

//     tinyrpcHeader::rpcHeader header;
//     header.set_servicename(service->name());
//     header.set_methodname(method->name());
//     header.set_argssize(requestData.size());

//     std::string headerData;
//     header.SerializeToString(&headerData);
//     int headerSize = headerData.size();
//     sendData.append((const char *)&headerSize, 4);
//     sendData.append(headerData);
//     sendData.append(requestData);

//     std::string target;
//     package::encapsulation(sendData, target);

//     int clientFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//     if (clientFd == -1)
//     {
//         perror("socket error");
//         exit(0);
//     }
//     sockaddr_in addr;
//     addr.sin_port = htons(9001);
//     addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//     addr.sin_family = PF_INET;

//     int res = connect(clientFd, (sockaddr*)&addr, sizeof(addr));
//     if(res == -1){
//         perror("connect error:");
//         exit(0);
//     }
//     int sendLen = send(clientFd, target.data(), target.size(), 0);
//     char str[4096]{0};
//     std::cout << "send data size:" << sendLen << std::endl;
//     ssize_t len = recv(clientFd, str, 4096, 0);
//     std::cout << "recv data size:" << len << std::endl;
//     response->ParseFromString(std::string(str, len));

//     close(clientFd);
// }
// }

// void RpcChannel::callBack()
// {
//     RpcController* controller =
//     dynamic_cast<RpcController*>(getController()); if
//     (controller->Finished())
//     {
//         return;
//     }

//     if (closure_)
//     {
//         closure_->Run();
//         if (controller)
//         {
//             controller->SetFinished(true);
//         }
//     }

// }