#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "socketfd.hpp"
#define UDP_BUFSIZE 65535

class Server
{
public:
    Server();
    ~Server();
    bool init(SockType t);
    bool start(const char *IP, const char *Port);
    bool isstarted();
    bool acceptClient();                // TCP阻塞接受，UDP无操作
    bool recvData();                   // 接收数据到recvbuf
    bool sendData(const char *msg);    // 发送文本

private:
    Server(const Server &) = delete;
    Server &operator=(const Server &) = delete;

private:
    Socketfd fd;
    bool started_status;               // 是否启动 ture 启动 false没启动
    int client_fd;                     // TCP客户端fd，UDP为-1
    std::string sendbuf;
    std::string recvbuf;
    struct sockaddr_in addr;           // 本机绑定地址
    struct sockaddr_in peer_addr;      // 对端地址
};

#endif //SERVER_HPP_