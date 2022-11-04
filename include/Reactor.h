#pragma once

class Reactor
{
    // 职责: 开始事件循环
    // 根据事物类型分发事物
public:
    Reactor(int sock) noexcept;

    void EventLoop() noexcept;

private:
    int sock;
};