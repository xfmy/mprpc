#定义最低版本
cmake_minimum_required(VERSION 3.0)

#定义项目名称
project(tinyrpc)

#设置c++标准
set(CMAKE_CXX_STANDARD 20) 

#包含相关头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 设置项目库文件搜索路径 -L
link_directories(${PROJECT_SOURCE_DIR}/lib)

#设置可执行程序的输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
 
#默认设置Debug版本
set(CMAKE_BUILD_TYPE Debug)

#指定clang编译器
#set(CMAKE_C_COMPILER /usr/bin/clang)
#set(CMAKE_CXX_COMPILER /usr/bin/clang++)

#生成库文件
add_subdirectory(src)  
#进行单元测试
add_subdirectory(test) 
#编译示例
add_subdirectory(example) 