#include "Socket.h"
#include <arpa/inet.h>
#include <unistd.h>

Socket::Socket(short port) noexcept
{
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr));

    listen(sock, 128);
}

Socket::~Socket()
{
    close(sock);
}