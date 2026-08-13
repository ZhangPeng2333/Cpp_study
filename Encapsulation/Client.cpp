#include"Client.hpp"

Client::Client() : fd(),
                   connect_status(false),
                   sendbuf(),
                   recvbuf()
{
}

Client::~Client()
{
}

bool Client::init(SockType t)
{
    if (t == TCP)
    {
        fd.setTCP();
    }
    else if (t == UDP)
    {
        fd.setUDP();
    }
    else
    {
        std::cout << "Init SockType err" << std::endl;
        return false;
    }

    memset(&addr, 0, sizeof(addr));

    if (fd.init() == false)
    {
        return false;
    }
}

bool Client::connect(const char *IP, const char *Port)
{
    if (atoi(Port) < 1024 || atoi(Port) > 65535)
    {
        return false;
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(IP);
    if (addr.sin_addr.s_addr == INADDR_NONE)
    {
        perror("ip wrong");
        return false;
    }
    addr.sin_port = htons(atoi(Port));

    if (fd.getSockType() == TCP)
    {
        // TCP
        if (::connect(fd.getFD(), (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("connect err");
            return false;
        }
    }
    else if (fd.getSockType() == UDP)
    {
        // UDP do nothing
    }
    else
    {
        perror("socketfd have not init!");
        return false;
    }
    connect_status = true;
    std::cout << "connet success!" << std::endl;
    return true;
}

bool Client::isconnect()
{
    return connect_status;
}

bool Client::msgsend(const void *msg, size_t len, char type)
{
    if (connect_status == false)
    {
        perror("Client isn't connect");
        return false;
    }
    // 之后在考虑
    return false;
}

bool Client::msgsend(const char *msg)
{
    if (connect_status == false)
    {
        perror("Client isn't connect");
        return false;
    }
    sendbuf.clear();
    sendbuf.append(msg);

    size_t total = sendbuf.size();
    const char *pData = sendbuf.data();

    if (fd.getSockType() == TCP)
    {
        // TCP
        size_t sent = 0;
        while (sent < total)
        {
            ssize_t ret = ::send(fd.getFD(), pData + sent, total - sent, 0);
            if (ret <= 0)
            {
                perror("TCP send error");
                connect_status = false;
                return false;
            }
            sent += ret;
        }
    }
    else if (fd.getSockType() == UDP)
    {
        // UDP
        ssize_t ret = ::sendto(fd.getFD(), pData, total, 0, (struct sockaddr *)&addr, sizeof(addr));
        if (ret != (ssize_t)total)
        {
            perror("UDP sendto error");
            connect_status = false;
            return false;
        }
    }
    else
    {
        perror("socketfd have not init!");
        connect_status = false;
        return false;
    }
    return true;
}

bool Client::recvData()
{
    if (connect_status == false)
    {
        perror("Client isn't connect");
        return false;
    }

    recvbuf.clear();

    if (fd.getSockType() == TCP)
    {
        // TCP
        char tmp[1024];
        ssize_t ret;
        while ((ret = ::recv(fd.getFD(), tmp, sizeof(tmp), 0)) > 0)
        {
            recvbuf.append(tmp, ret);
        }
        if (ret < 0)
        {
            perror("TCP recv error");
            connect_status = false;
            return false;
        }
        // ret==0时 对方关闭连接，接收完成
    }
    else if (fd.getSockType() == UDP)
    {
        // UDP
        char tmp[UDP_BUFSIZE];
        socklen_t recvlen = sizeof(addr);
        ssize_t ret = ::recvfrom(fd.getFD(), tmp, sizeof(tmp), 0, (struct sockaddr *)&addr, &recvlen);
        if (ret <= 0)
        {
            perror("UDP recvfrom error");
            connect_status = false;
            return false;
        }
        recvbuf.append(tmp, ret);
    }
    else
    {
        perror("socketfd have not init!");
        connect_status = false;
        return false;
    }

    recvbuf.push_back('\0');
    return true;
}
