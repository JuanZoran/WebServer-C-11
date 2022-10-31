#include "netbase.h"
#include <sys/epoll.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <utility>

using namespace Zoran;
Fd::Fd(Fd &&other) noexcept
{
    m_fd = std::move(other.m_fd);
}

void Fd::operator=(Fd &&other) noexcept
{
    m_fd = std::move(other.m_fd);
}

Fd::~Fd() noexcept
{
    if (m_fd > 0)
        close(m_fd);
}

// Socket &operator>>(Socket &socket, Buffer &buffer)
// {
//     // 接受数据
//     return socket;
// }