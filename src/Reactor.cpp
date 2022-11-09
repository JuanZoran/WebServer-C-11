#include "Reactor.h"
#include "Epoll.h"
#include "MessageQueue.hpp"
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

Reactor::Reactor(short port) noexcept : sock(port)
{
    // cout << "Reactor socket = " << sock << endl;
    // 将该监听文件描述符插入到Epoll 树上
    epoll.add(sock);
    std::thread work(worker);
    work.detach();
}

void Reactor::EventLoop() noexcept
{
    // cout << "开始事件循环........." << endl;
    // 开始事件循环
    while (true)
    {
        auto ret = epoll.wait(-1);
        // cout << "Loop..." << endl;
        for (auto fd : ret)
            // 如果是连接事件, 则接受
            // 如果是消息时间,则派发给工作线程
            fd == sock
                ? epoll.add(sock.accept())
                : requestQueue.push(fd);
    }
}
