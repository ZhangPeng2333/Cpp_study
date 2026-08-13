#include "Server.hpp"

Server::Server() : fd(),
                   started_status(false),
                   client_fd(-1),
                   sendbuf(),
                   recvbuf()
{
    memset(&addr, 0, sizeof(addr));
    memset(&peer_addr, 0, sizeof(peer_addr));
}

Server::~Server()
{
    if (client_fd != -1)
        close(client_fd);
}

bool Server::init(SockType t)
{
    if (t == TCP)
        fd.setTCP();
    else if (t == UDP)
        fd.setUDP();
    else
    {
        std::cout << "Init SockType err" << std::endl;
        return false;
    }

    if (fd.init() == false)
        return false;
    return true;
}

bool Server::start(const char *IP, const char *Port)
{
    if (atoi(Port) < 1024 || atoi(Port) > 65535)
        return false;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(Port));
    addr.sin_addr.s_addr = inet_addr(IP);
    if (addr.sin_addr.s_addr == INADDR_NONE)
    {
        perror("ip wrong");
        return false;
    }

    if (bind(fd.getFD(), (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind err");
        return false;
    }

    if (fd.getSockType() == TCP)
    {
        if (listen(fd.getFD(), 5) < 0)
        {
            perror("listen err");
            return false;
        }
    }

    started_status = true;
    std::cout << "start success!" << std::endl;
    return true;
}

bool Server::isstarted()
{
    return started_status;
}

bool Server::acceptClient()
{
    if (started_status == false)
    {
        perror("Server not started");
        return false;
    }

    if (fd.getSockType() == TCP)
    {
        socklen_t len = sizeof(peer_addr);
        client_fd = accept(fd.getFD(), (struct sockaddr *)&peer_addr, &len);
        if (client_fd < 0)
        {
            perror("accept err");
            return false;
        }
        std::cout << "accept success!" << std::endl;
    }
    // UDP: nothing
    return true;
}

bool Server::recvData()
{
    if (started_status == false)
    {
        perror("Server not started");
        return false;
    }

    recvbuf.clear();

    if (fd.getSockType() == TCP)
    {
        if (client_fd == -1)
        {
            perror("No client connected");
            return false;
        }
        char tmp[1024];
        ssize_t ret;
        while ((ret = ::recv(client_fd, tmp, sizeof(tmp), 0)) > 0)
        {
            recvbuf.append(tmp, ret);
        }
        if (ret < 0)
        {
            perror("TCP recv error");
            return false;
        }
        // ret==0 客户端关了
    }
    else if (fd.getSockType() == UDP)
    {
        char tmp[UDP_BUFSIZE];
        socklen_t len = sizeof(peer_addr);
        ssize_t ret = ::recvfrom(fd.getFD(), tmp, sizeof(tmp), 0,
                                 (struct sockaddr *)&peer_addr, &len);
        if (ret <= 0)
        {
            perror("UDP recvfrom error");
            return false;
        }
        recvbuf.append(tmp, ret);
    }
    else
    {
        perror("socketfd have not init!");
        return false;
    }

    recvbuf.push_back('\0');
    return true;
}

bool Server::sendData(const char *msg)
{
    if (started_status == false)
    {
        perror("Server not started");
        return false;
    }

    sendbuf.clear();
    sendbuf.append(msg);

    size_t total = sendbuf.size();
    const char *pData = sendbuf.data();

    if (fd.getSockType() == TCP)
    {
        if (client_fd == -1)
        {
            perror("No client connected");
            return false;
        }
        size_t sent = 0;
        while (sent < total)
        {
            ssize_t ret = ::send(client_fd, pData + sent, total - sent, 0);
            if (ret <= 0)
            {
                perror("TCP send error");
                return false;
            }
            sent += ret;
        }
    }
    else if (fd.getSockType() == UDP)
    {
        ssize_t ret = ::sendto(fd.getFD(), pData, total, 0,
                               (struct sockaddr *)&peer_addr, sizeof(peer_addr));
        if (ret != (ssize_t)total)
        {
            perror("UDP sendto error");
            return false;
        }
    }
    else
    {
        perror("socketfd have not init!");
        return false;
    }
    return true;
}