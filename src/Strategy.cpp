#include "../include/Strategy.h"

bool STRATEGY::LISTEN_ADD::Process(int epoll_fd, int fd)
{
    if (epoll_fd <= 0)
        return false;
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
    return ret != -1;
}

bool STRATEGY::LISTEN_DEL::Process(int epoll_fd, int fd)
{
    if (epoll_fd <= 0)
        return false;
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
    return ret != -1;
}