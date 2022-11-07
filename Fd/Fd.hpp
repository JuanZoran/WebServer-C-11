#pragma once
#include <unistd.h>

#if 1
#include <iostream>
using std::cout, std::endl;
#endif

class Fd
{
public:
    // 仅仅使用fd, 应该将接口声明为int, 这样就不会掌管fd的生命周期
    operator int() noexcept
    {
        return m_fd;
    }

public:
    // 不可赋值, 类似于unique_ptr
    Fd() = default;
    Fd(int fd) noexcept : m_fd(fd){};

    Fd &operator=(Fd &fd) noexcept
    {
        m_fd = fd.m_fd;
        fd.m_fd = 0;
        return *this;
    }

    Fd(Fd &other) noexcept : m_fd(other.m_fd)
    {
        other.m_fd = 0;
    }

    ~Fd() noexcept
    {
        if (m_fd > 0)
            close(m_fd);
        cout << m_fd << "被关闭" << endl;
    }

protected:
    int m_fd;
};