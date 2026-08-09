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

class tcp_client
{
private:
    int m_sockfd;
    Status status;

public:
    tcp_client();

    bool tcp_connect(const char *IP, const char *Port);

    bool tcp_msgsend(const char *msg);

    ssize_t tcp_recv(void *buffer, size_t bufsize);

    ~tcp_client();
};
#endif