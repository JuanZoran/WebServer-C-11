#include "Reactor.h"

Reactor::Reactor(int sock) noexcept : sock(sock)
{
    // 将该监听文件描述符插入到Epoll 树上
    epoll.add(sock);
}

void Reactor::EventLoop() noexcept
{
    // 开始事件循环
    while (true)
    {
        auto ret = epoll.wait(-1);
        if (ret)
        {
            for (int fd : *ret)
            {
                if (fd == sock)
                    // TODO: 插入到请求队列
                    ;
                else
                    // TODO: 插入到消息队列
                    ;
            }
        }
    }
}
