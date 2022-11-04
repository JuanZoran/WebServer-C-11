#include "Reactor.h"
#include "Epoll.h"
#include "MessageQueue.hpp"
#include <arpa/inet.h>
#include <task.hpp>
#include "Handler.h"

extern MessageQueue<int> requestQueue;
extern Epoll epoll;

#include <thread>
#include <iostream>
using std::endl, std::cout;
void worker()
{
    Handler handler;
    while (true)
    {
        int cfd = requestQueue.pop();
        cout << "Handler begin to work" << endl;
        handler.processRequest(cfd);
    }
}

void acceptConnection(int sock)
{
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    int cfd = accept(sock, (struct sockaddr *)&addr, &addrlen);
    epoll.add(cfd);
    cout << "添加客户端连接成功:" << cfd << endl;
}

Reactor::Reactor(int sock) noexcept : sock(sock)
{
    // 将该监听文件描述符插入到Epoll 树上
    epoll.add(sock);
    std::thread work(worker);
    work.detach();
}

void Reactor::EventLoop() noexcept
{
    // 开始事件循环
    cout << "begin to loop..." << endl;
    while (true)
    {
        auto ret = epoll.wait(-1);
        if (ret)
        {
            // FIXME: 连接队列使用条件变量, 可以不用使用任务队列
            for (int fd : *ret)
                fd == sock
                    ? acceptConnection(sock)
                    : requestQueue.push(fd);
        }
    }
}
