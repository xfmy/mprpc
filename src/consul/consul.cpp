#include <muduo/base/Logging.h>
#include "consul.h"
#include "random_number.h"

namespace tinyrpc {
ConsulClient::ConsulClient()
{
    // 根据配置文件信息初始化consul
    std::optional<std::string> consulIp =
        RpcApplication::GetInstance().atConfigItem("consulIp");
    std::optional<std::string> consulPort =
        RpcApplication::GetInstance().atConfigItem("consulPort");
    if (consulIp.has_value() && consulPort.has_value())
    {
        consulPtr_ = std::make_shared<ppconsul::Consul>(
            consulIp.value() + ':' + consulPort.value(),
            ppconsul::kw::dc = "dc1");
    }
    else
    {
        LOG_FATAL << "serverPort not config";
        exit(-1);
    }
}
void ConsulClient::RegisterService(const std::string& name,
                                   const std::string& id,
                                   const std::string& address, uint16_t port)
{
    ppconsul::agent::Agent consulAgent(*consulPtr_);

    consulAgent.registerService(
        ppconsul::agent::kw::name = name, ppconsul::agent::kw::id = id,
        ppconsul::agent::kw::address = address,
        ppconsul::agent::kw::port = port,
        ppconsul::agent::kw::check =
            ppconsul::agent::TtlCheck(std::chrono::seconds(60)));
}
void ConsulClient::DeregisterService(const std::string& id)
{
    ppconsul::agent::Agent consulAgent(*consulPtr_);
    consulAgent.deregisterService(id);
}
std::unique_ptr<muduo::net::InetAddress> ConsulClient::DiscoverService(
    const std::string& name)
{
    //根据服务名进行服务发现,并全部进行服务健康检测,随机将一个健康服务节点地址返回
    std::unique_ptr<muduo::net::InetAddress> addressPtr;
    ppconsul::health::Health health(*consulPtr_);
    auto services = health.service(name);
    std::vector<muduo::net::InetAddress> serviceAddresses;

    for (const auto& service : services)
    {
        if (!CheckHealth(service)) continue;

        serviceAddresses.emplace_back(std::get<1>(service).address,
                                      std::get<1>(service).port);
    }
    if (serviceAddresses.size() == 0) return addressPtr;
    int hashIndex = std::atoi(tinyrpc::GetRandomNumberString().c_str()) %
                    serviceAddresses.size();
    addressPtr =
        std::make_unique<muduo::net::InetAddress>(serviceAddresses[hashIndex]);
    return addressPtr;
}

void ConsulClient::ServicePass(std::string serviceId)
{
    ppconsul::agent::Agent consulAgent(*consulPtr_);
    consulAgent.servicePass(serviceId);
}

bool ConsulClient::CheckHealth(ppconsul::health::NodeServiceChecks service)
{
    auto services = std::get<2>(service);
    for (auto checkInfo : services)
    {
        if (checkInfo.status == ppconsul::CheckStatus::Critical) return false;
    }
    return true;
}
} // namespace tinyrpc