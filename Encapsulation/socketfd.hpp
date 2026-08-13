#ifndef SOCKETFD_HPP_
#define SOCKETFD_HPP_

#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<iostream>

enum SockType{
    UDP=1,
    TCP,
    UNKNOWN
};

class Socketfd
{
public:
    Socketfd();
    ~Socketfd();
    void setUDP();
    void setTCP();
    bool init();
    int getFD();
    SockType getSockType();
private:
    Socketfd(const Socketfd &) = delete;            // 拷贝构造
    Socketfd &operator=(const Socketfd &) = delete; // 赋值函数
private:
    int m_sockfd;
    SockType m_type;
};

Socketfd::Socketfd():
    m_sockfd(-1),
    m_type(UNKNOWN)
{
}

Socketfd::~Socketfd()
{
    if (m_sockfd!=-1)
    {
        close(m_sockfd);
    }
    
}

void Socketfd::setUDP(){
    m_type = UDP;
}

void Socketfd::setTCP(){
    m_type = TCP;
}

bool Socketfd::init(){
    if (m_type==UNKNOWN)
    {
        return false;
    }

    int con_type = -1;
    if (m_type==UDP)
        con_type = SOCK_DGRAM;
    else
        con_type = SOCK_STREAM;

    m_sockfd = socket(AF_INET,con_type,0);
    if (m_sockfd<0)
    {
        return false;
    }
    return true;
}

int Socketfd::getFD(){
    return m_sockfd;
}

SockType Socketfd::getSockType(){
    return m_type;
}

#endif // SOCKETFD_HPP_