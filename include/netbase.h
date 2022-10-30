#pragma once
#include "Buffer.h"

// 封装Linux给的C语言api
// socket, epoll, send, recv
namespace Zoran
{
    // RAII 管理文件描述符

    class Fd
    {
    public:
        // TODO: 设置Fd的属性: 非阻塞, 端口复用
        // virtual bool set()
        // {
        //     return true;
        // }

        // 获取文件描述符
        int fd() const
        {
            return m_fd;
        }

    public:
        Fd(int fd) noexcept : m_fd(fd)
        {
        }

        Fd(Fd &&other) noexcept;

        void operator=(Fd &&other) noexcept;

        // 析构函数关闭文件描述符
        virtual ~Fd();

    protected:
        Fd() : m_fd(0) {}
        int m_fd;
    };

    class Socket : public Fd
    {
        // 重载对应的流操作符, 实现 socket >> buffer; 获取该socket的内容
    public:
        friend Socket &operator>>(Socket &socket, Buffer &buffer) noexcept;
    };

    class Epoll : public Fd
    {
    public:
        Epoll() noexcept;
    };

} // namespace Zoran
