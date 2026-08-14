#include "Client.hpp"

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
    return true;
}

TCP_Client::TCP_Client()
{
}

TCP_Client::~TCP_Client()
{
}

bool TCP_Client::connect(const char *IP, const char *Port)
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

    if (::connect(fd.getFD(), (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect err");
        return false;
    }
    m_isConnected = true;
    std::cout << "connet success!" << std::endl;
    return true;
}

bool TCP_Client::msgsend(const char *msg)
{
    if (m_isConnected == false)
    {
        perror("Client isn't connect");
        return false;
    }
    sendbuf.clear();
    sendbuf.append(msg);

    size_t total = sendbuf.size();
    const char *pData = sendbuf.data();

    size_t sent = 0;
    while (sent < total)
    {
        ssize_t ret = ::send(fd.getFD(), pData + sent, total - sent, 0);
        if (ret <= 0)
        {
            perror("TCP send error");
            m_isConnected = false;
            return false;
        }
        sent += ret;
    }

    return true;
}

bool TCP_Client::recvdata()
{
    if (m_isConnected == false)
    {
        perror("Client isn't connect");
        return false;
    }

    recvbuf.clear();
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
        m_isConnected = false;
        return false;
    }
    // ret==0时 对方关闭连接，接收完成

    recvbuf.push_back('\0');
    return true;
}

UDP_Client::UDP_Client()
{
}

UDP_Client::~UDP_Client()
{
}

bool UDP_Client::connect(const char *IP, const char *Port)
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
    m_isConnected = true;
    std::cout << "connet success!" << std::endl;
    return true;
}

bool UDP_Client::msgsend(const char *msg)
{
    if (m_isConnected == false)
    {
        perror("Client isn't connect");
        return false;
    }
    sendbuf.clear();
    sendbuf.append(msg);

    size_t total = sendbuf.size();
    const char *pData = sendbuf.data();

    ssize_t ret = ::sendto(fd.getFD(), pData, total, 0, (struct sockaddr *)&addr, sizeof(addr));
    if (ret != (ssize_t)total)
    {
        perror("UDP sendto error");
        m_isConnected = false;
        return false;
    }
    return true;
}

bool UDP_Client::recvdata()
{
    if (m_isConnected == false)
    {
        perror("Client isn't connect");
        return false;
    }
    // UDP
    recvbuf.clear();
    char tmp[UDP_BUFSIZE];
    socklen_t recvlen = sizeof(addr);
    ssize_t ret = ::recvfrom(fd.getFD(), tmp, sizeof(tmp), 0, (struct sockaddr *)&addr, &recvlen);
    if (ret <= 0)
    {
        perror("UDP recvfrom error");
        m_isConnected = false;
        return false;
    }
    recvbuf.append(tmp, ret);
    recvbuf.push_back('\0');
    return true;
}

/**
 * @brief 给用户的接口
 * 
 * @param type TCP/UDP
 * @return Client* 成功返回指向 Client 对象的指针 失败返回 NULL
 */
Client* ClientFactory::create(SockType type) {
    Client* client = NULL;

    if (type == TCP) {
        client = new TCP_Client();
    } else if (type == UDP) {
        client = new UDP_Client();
    } else {
        perror("SockType err\n");
        return NULL;
    }

    if (!client->init(type)) {
        delete client;
        return NULL;
    }

    return client;
}

#if 0
int main() {
    Client* client = ClientFactory::create(TCP);
    if (client && client->connect("127.0.0.1", "8888")) {
        client->msgsend("Hello World!\n");
        client->msgsend("Hello C Language!\n");
        client->msgsend("Hello Cpp!\n");
        client->msgsend("123456789!");
    }
    delete client;
    return 0;
}

#endif

