// 服务器入口
/// @file main.cpp
/// @brief 服务端 main 函数, 构造 Server 并启动

#include "server.h"

/**
 * @brief 服务端程序入口
 * @param argc 参数个数
 * @param argv 参数列表(ip port)
 * @return Server::run 的返回值
 */
int main(int argc, char *argv[])
{
    Server srv;
    return srv.run(argc, argv);
}
