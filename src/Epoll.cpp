#include "Epoll.h"
#include <sys/epoll.h>
#include <unistd.h>
#include <memory>

Epoll::Epoll() noexcept
{
    efd = epoll_create(128);
}

Epoll::~Epoll() noexcept
{
    close(efd);
}

void Epoll::add(int fd) noexcept
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(efd, EPOLL_CTL_ADD, fd, &event);
    num++;
}

void Epoll::del(int fd) noexcept
{
    epoll_ctl(efd, EPOLL_CTL_DEL, fd, NULL);
    num--;
}

Epoll::Events Epoll::wait(int timeout) const noexcept
{
    // TODO: 实现循环监听

    // 监听所有事件
    struct epoll_event events[num];
    int ret = epoll_wait(efd, events, num, timeout);
    if (ret <= 0)
        return std::nullopt;

    std::vector<int> res(ret, 0);
    // 将有效的数据返回
    for (int i = 0; i < ret; i++)
        res.emplace_back(events[i].data.fd);
    return res;
}