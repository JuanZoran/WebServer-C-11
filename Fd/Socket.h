#pragma once
#include "Fd.hpp"
class Socket : public Fd
{
public:
    explicit Socket(short port) noexcept;
    int accept() noexcept;

private:
    // TODO: 包装sock地址
};