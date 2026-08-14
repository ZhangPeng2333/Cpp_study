#include "Server.hpp"

bool Server::init(SockType t)
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

    if (fd.init() == false)
    {
        return false;
    }
    return true;
}

TCP_Server::TCP_Server() : client_fd(-1)
{
}

TCP_Server::~TCP_Server()
{
    if (client_fd != -1)
        close(client_fd);
}

bool TCP_Server::start(const char *IP, const char *Port)
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

    if (bind(fd.getFD(), (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind err");
        return false;
    }

    if (listen(fd.getFD(), 5) < 0)
    {
        perror("listen err");
        return false;
    }

    m_isStarted = true;
    std::cout << "start success!" << std::endl;
    return true;
}

bool TCP_Server::acceptClient()
{
    if (m_isStarted == false)
    {
        perror("Server not started");
        return false;
    }

    socklen_t len = sizeof(peer_addr);
    client_fd = accept(fd.getFD(), (struct sockaddr *)&peer_addr, &len);
    if (client_fd < 0)
    {
        perror("accept err");
        return false;
    }
    std::cout << "accept success!" << std::endl;
    return true;
}

bool TCP_Server::recvdata()
{
    if (m_isStarted == false)
    {
        perror("Server not started");
        return false;
    }
    if (client_fd == -1)
    {
        perror("No client connected");
        return false;
    }

    recvbuf.clear();
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
    // ret==0 客户端关闭

    recvbuf.push_back('\0');
    return true;
}

bool TCP_Server::senddata(const char *msg)
{
    if (m_isStarted == false)
    {
        perror("Server not started");
        return false;
    }
    if (client_fd == -1)
    {
        perror("No client connected");
        return false;
    }

    sendbuf.clear();
    sendbuf.append(msg);

    size_t total = sendbuf.size();
    const char *pData = sendbuf.data();

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
    return true;
}

UDP_Server::UDP_Server()
{
}

UDP_Server::~UDP_Server()
{
}

bool UDP_Server::start(const char *IP, const char *Port)
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

    if (bind(fd.getFD(), (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind err");
        return false;
    }

    m_isStarted = true;
    std::cout << "start success!" << std::endl;
    return true;
}

bool UDP_Server::acceptClient()
{
    // UDP 无需 accept，直接认为可以通信
    if (m_isStarted == false)
    {
        perror("Server not started");
        return false;
    }
    return true;
}

bool UDP_Server::recvdata()
{
    if (m_isStarted == false)
    {
        perror("Server not started");
        return false;
    }

    recvbuf.clear();
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
    recvbuf.push_back('\0');
    return true;
}

bool UDP_Server::senddata(const char *msg)
{
    if (m_isStarted == false)
    {
        perror("Server not started");
        return false;
    }

    sendbuf.clear();
    sendbuf.append(msg);

    size_t total = sendbuf.size();
    const char *pData = sendbuf.data();

    ssize_t ret = ::sendto(fd.getFD(), pData, total, 0,
                           (struct sockaddr *)&peer_addr, sizeof(peer_addr));
    if (ret != (ssize_t)total)
    {
        perror("UDP sendto error");
        return false;
    }
    return true;
}

/**
 * @brief 给用户的接口
 * 
 * @param type TCP/UDP
 * @return Server* 成功返回指向 Server 对象的指针 失败返回 NULL
 */
Server* ServerFactory::create(SockType type) {
    Server* server = NULL;

    if (type == TCP) {
        server = new TCP_Server();
    } else if (type == UDP) {
        server = new UDP_Server();
    } else {
        perror("SockType err\n");
        return NULL;
    }

    if (!server->init(type)) {
        delete server;
        return NULL;
    }

    return server;
}

#if 0
int main() {
    Server* svr = ServerFactory::create(TCP);
    if (svr && svr->start("127.0.0.1", "8888") && svr->acceptClient()) {
        if (svr->recvdata()) {
            std::cout << svr->getRecvBuf() << std::endl;
            svr->senddata("OK");
        }
    }
    delete svr;
    return 0;
}
#endif