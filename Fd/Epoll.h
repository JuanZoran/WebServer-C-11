#pragma once
#include <Fd.hpp>
#include <vector>

class Epoll : public Fd
{
public:
    using Events = std::vector<int>;

public:
    void add(int fd) noexcept;
    void del(int fd) noexcept;
    // TODO:如果没有事件有效, 将返回空
    Events wait(int timeout) const noexcept;

private:
    static void setNonBlock(int fd) noexcept;

public:
    // 获得一颗Epoll树
    Epoll() noexcept;
    Epoll(int fd) = delete;

private:
    int num{};
};