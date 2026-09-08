// 客户端入口
/// @file main.cpp
/// @brief 客户端 main 函数, 构造 Client 并启动

#include "client.h"

/**
 * @brief 客户端程序入口
 * @param argc 参数个数
 * @param argv 参数列表(ip port)
 * @return Client::run 的返回值
 */
int main(int argc, char *argv[])
{
    Client cli;
    return cli.run(argc, argv);
}
