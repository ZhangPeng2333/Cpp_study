// 封装tcp
#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

enum Status
{
    SOCKERR,
    WAITCONT,
    CONETERR,
    CONETSUC
};
#define BUF_SIZE 512
class tcp_client
{
private:
    int m_sockfd;
    Status status;
    char sendbuf[BUF_SIZE];
    char recvbuf[BUF_SIZE];
    
public:
    // 建立发送缓冲区

    tcp_client();

    bool m_connect(const char *IP, const char *Port);

    bool m_msgsend(const char *msg);

    ssize_t m_recv(void *buffer, size_t bufsize);

    ~tcp_client();
};
#endif