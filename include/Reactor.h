#pragma once
#include "Epoll.h"
// 职责: 开始事件循环
// 根据事物类型分发事物
class Reactor
{
public:
    Reactor(int sock) noexcept;

    void EventLoop() noexcept;

private:
    Epoll epoll;
    int sock;
};