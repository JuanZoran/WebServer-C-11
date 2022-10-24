#include "WebServer.h"
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <assert.h>
#include <Accepter.h>
#include <Reactor.h>

// #include <iostream>
// using namespace std;

WebServer::WebServer()
    : m_port(12345), isET(true)
{
    initLfd();
    initEfd();
}

WebServer::~WebServer()
{
    close(m_lfd);
    close(m_efd);
}

// 初始化监听文件描述符
void WebServer::initLfd()
{
    m_lfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(m_lfd != -1);
    setFd(m_lfd);

    struct sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(m_port);
    addr.sin_family = AF_INET;
    int ret = bind(m_lfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    assert(ret != -1);
}

// 初始化Epoll树
void WebServer::initEfd()
{
    m_efd = epoll_create(128);
    assert(m_efd != -1);
}

// 启动服务器、开始事件循环
void WebServer::Run()
{
    // 监听lfd
    assert(listen(m_lfd, 128) != -1);

    // 将lfd添加到epoll树上
    Accepter accepter(isET);
    Reactor reactor;
    accepter.addEpollFd(m_lfd, m_efd);

    const int size = 1024;
    struct epoll_event events[size];

    // 开始事件循环
    int num = 0, cfd = 0;
    while (true)
    {
        num = epoll_wait(m_efd, events, size, -1);
        for (int i = 0; i < num; i++)
        {
            cfd = events[i].data.fd;
            if (cfd == m_lfd)
            {
                // 分发给Accpeter
                accepter.acceptConnection(cfd, m_efd);
            }
            else
            {
                // 分发给Reactor
                reactor.processRequest(cfd);
            }
        }
    }
}

void WebServer::setFd(int sock)
{
    // FIXME: 设置端口复用和超时关闭
    struct linger tmp = {1, 1};
    setsockopt(m_lfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof(tmp));
}
