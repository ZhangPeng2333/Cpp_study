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
    Client() : fd(),
               m_isConnected(false),
               sendbuf(),
               recvbuf()
    {
        memset(&addr, 0, sizeof(addr));
    };
    virtual ~Client() {};
    virtual bool init(SockType t);
    virtual bool connect(const char *IP, const char *Port) = 0;
    virtual bool msgsend(const char *msg) = 0;
    virtual bool recvdata() = 0;

    explicit operator bool() const
    {
        return m_isConnected;
    } // 外部可以直接用if(对象)判断是否已经链接

    const std::string& getRecvBuf() const { return recvbuf; }

protected:
    bool m_isConnected; // 是否连接 false未连接 true已连接
    Socketfd fd;
    std::string sendbuf;
    std::string recvbuf;
    struct sockaddr_in addr;

private:
    Client(const Client &) = delete;            // 不让拷贝构造
    Client &operator=(const Client &) = delete; // 不让赋值函数
};

class TCP_Client : public Client
{
public:
    TCP_Client();
    ~TCP_Client();

    bool connect(const char *IP, const char *Port);

    bool msgsend(const char *msg);

    bool recvdata();
};

class UDP_Client : public Client
{
public:
    UDP_Client();
    ~UDP_Client();

    bool connect(const char *IP, const char *Port);

    bool msgsend(const char *msg);

    bool recvdata();
};

class ClientFactory {
public:
    static Client* create(SockType type);
};

#endif // CLIENT_HPP_