#include "Socket.h"
#include <arpa/inet.h>
#include <cassert>

Socket::Socket(short port) noexcept
{
    m_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(m_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
    assert(ret != -1);

    ret = listen(m_fd, 128);
    assert(ret != -1);
}

int Socket::accept() noexcept
{
    // TODO: accept和地址绑定
    return ::accept(m_fd, NULL, NULL);
}