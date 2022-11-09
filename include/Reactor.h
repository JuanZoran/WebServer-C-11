#pragma once
#include "Socket.h"

class Reactor
{
    // 职责: 开始事件循环
    // 根据事物类型分发事物
public:
    // 初始化socket, 初始化Epoll
    // 将socket插入到Epoll监听
    explicit Reactor(short port) noexcept;

    void EventLoop() noexcept;

private:
    Socket sock;
};