// 封装tcp
#include "tcp_client.h"

/**
 * @brief Construct a new tcp client::tcp client object
 *
 */
tcp_client::tcp_client() : m_sockfd(-1)
{
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // 使用init 
    if (m_sockfd < 0)
    {
        status = SOCKERR;
        // 抛异常
        perror("sock err\n");
    }
    status = WAITCONT;
}

/**
 * @brief 封装tcp的连接
 *
 * @param IP 传入IP字符串
 * @param Port 传入端口字符串
 * @return true 与对端连接成功
 * @return false 与对端连接失败
 */
bool tcp_client::connect(const char *IP, const char *Port)
{
    if (this->m_sockfd < 0)
    {
        return false;
    }
    if (atoi(Port) < 1024 || atoi(Port) > 65535)
    {
        return false;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(IP);
    if (addr.sin_addr.s_addr == INADDR_NONE)
    {
        return false;
    }
    addr.sin_port = htons(atoi(Port));

    if (::connect(m_sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect err");
        status = CONETERR;
        return false;
    }

    status = CONETSUC;
    std::cout << "connet success!" << std::endl;
    return false;
}

// static derialize_xxx();序列化
// 反序列化

/**
 * @brief 封装tcp的简易传信
 *
 * @param msg 要传信的字符数组
 * @return true 传信完毕
 * @return false 传信失败
 */
bool tcp_client::msgsend(void* msg,char type)
{
    //1.序列化
    if (type == XXX)
    {
        //序列化xxx到 sendbuf
    
    }
    
    
    if (m_sockfd < 0 || status != CONETSUC)
    {
        std::cerr << "not connected" << std::endl;
        return false;
    }
    size_t msg_len = strlen(msg);
    size_t sent_len = 0;
    const char *ptr = msg;
    while (sent_len < msg_len)
    {
        ssize_t n = send(m_sockfd, ptr + sent_len, msg_len - sent_len, 0);
        // send sendbuf
        if (n < 0)
        {
            perror("send failed");
            return false;
        }
        sent_len += n;
    }
    return true;
}

/**
 * @brief 封装客户端接受函数
 *
 * @param buffer 传出，存储对端传信的内容
 * @param bufsize 字符数组大小
 * @return ssize_t 接收到的大小
 */
ssize_t tcp_client::tcp_recv(void *buffer, size_t bufsize)
{
    if (m_sockfd < 0 || status != CONETSUC)
    {
        std::cerr << "not connected" << std::endl;
        return -1;
    }
    ssize_t n = recv(m_sockfd, buffer, bufsize, 0);
    if (n < 0)
    {
        perror("recv failed");
    }
    return n;
}

/**
 * @brief Destroy the tcp client::tcp client object
 *
 */
tcp_client::~tcp_client()
{
    if (m_sockfd != -1)
    {
        close(m_sockfd);
    }    
}