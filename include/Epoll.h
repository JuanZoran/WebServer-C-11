#pragma once
#include <stdint.h>
#include <vector>
#include <optional>

class Epoll
{
public:
    using Events = std::optional<std::vector<int>>;

public:
    void add(int fd) noexcept;
    void del(int fd) noexcept;
    // FIXME: 实现Epoll 循环监听
    // 如果没有事件有效, 将返回空
    Events wait(int timeout) const noexcept;

    int size() const noexcept { return num; }

private:
    void setNonBlock(int fd) noexcept;

public:
    // 获得一颗Epoll树
    Epoll() noexcept;
    Epoll(const Epoll &other) = delete;
    ~Epoll() noexcept;
    Epoll &operator=(const Epoll &other) = delete;

private:
    int32_t efd;
    int32_t num = 0;
};