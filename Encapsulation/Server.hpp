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
    Server() : fd(), m_isStarted(false), sendbuf(), recvbuf()
    {
        memset(&addr, 0, sizeof(addr));
        memset(&peer_addr, 0, sizeof(peer_addr));
    }
    virtual ~Server() {}
    virtual bool init(SockType t);
    virtual bool start(const char *IP, const char *Port) = 0;
    virtual bool acceptClient() = 0; // TCP阻塞接受，UDP无操作
    virtual bool recvdata() = 0;
    virtual bool senddata(const char *msg) = 0;

    explicit operator bool() const
    {
        return m_isStarted;
    }

    const std::string &getRecvBuf() const { return recvbuf; }

protected:
    bool m_isStarted;
    Socketfd fd;
    std::string sendbuf;
    std::string recvbuf;
    struct sockaddr_in addr;      // 本机地址
    struct sockaddr_in peer_addr; // 对端地址

private:
    Server(const Server &) = delete;
    Server &operator=(const Server &) = delete;
};

class TCP_Server : public Server
{
public:
    TCP_Server();
    ~TCP_Server();

    bool start(const char *IP, const char *Port);
    bool acceptClient();
    bool recvdata();
    bool senddata(const char *msg);

private:
    int client_fd; // TCP客户端fd
};

class UDP_Server : public Server
{
public:
    UDP_Server();
    ~UDP_Server();

    bool start(const char *IP, const char *Port);
    bool acceptClient();
    bool recvdata();
    bool senddata(const char *msg);
};

class ServerFactory
{
public:
    static Server *create(SockType type);
};

#endif // SERVER_HPP_