#ifndef CLIENT_HPP_
#define CLIENT_HPP_

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

class Client
{
public:
    Client();
    ~Client();
    bool init(SockType t);
    bool connect(const char *IP, const char *Port);
    bool isconnect();
    bool msgsend(const char *msg);
    bool msgsend(const void *msg, size_t len, char type);
    bool recvData();

private:
    Client(const Client &) = delete;            // 拷贝构造
    Client &operator=(const Client &) = delete; // 赋值函数

private:
    Socketfd fd;
    bool connect_status; // 是否连接 false未连接 true已连接
    std::string sendbuf;
    std::string recvbuf;
    struct sockaddr_in addr;
};

#endif // CLIENT_HPP_