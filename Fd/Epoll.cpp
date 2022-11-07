#include "Epoll.h"
#include <sys/epoll.h>
#include <fcntl.h> // 设置noblock

#if 1
#include <iostream>
using std::endl, std::cout;
#endif

void Epoll::setNonBlock(int fd) noexcept
{
    // cout << "设置成功" << endl;
    auto flag = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

Epoll::Epoll() noexcept
{
    m_fd = epoll_create(128);
}

void Epoll::add(int fd) noexcept
{
    // TODO: 支持配置Epoll模式
    // 目前默认使用 ET模式
    setNonBlock(fd);
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(m_fd, EPOLL_CTL_ADD, fd, &event);

    // cout << "添加了" << fd << endl;
    num++;
}

void Epoll::del(int fd) noexcept
{
    epoll_ctl(m_fd, EPOLL_CTL_DEL, fd, NULL);
    num--;
}

Epoll::Events Epoll::wait(int timeout) const noexcept
{
    // 监听所有事件
    struct epoll_event events[num];
    cout << "监听" << num << endl;
    int ret = epoll_wait(m_fd, events, num, timeout);
    // cout << "监听完成" << endl;

    std::vector<int> res(ret, 0);
    // 将有效的数据返回
    for (int i = 0; i < ret; i++)
        res[i] = events[i].data.fd;
    return res;
}