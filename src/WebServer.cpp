#include "WebServer.h"
#include "Listener.h"
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>

#ifdef SMART_PTR
#include <memory>
#endif

WebServer::WebServer(const ServerConf &config) : m_config(config)
{
    // 初始化监听套接字
    this->m_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(this->m_listen_fd > 0);
    init();
}

WebServer::~WebServer()
{
    close(m_listen_fd);
}

//初始化操作
void WebServer::init()
{
    // 初始化监听的地址
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(m_config.server_port);

    // 绑定对应的端口
    int ret = bind(m_listen_fd, (struct sockaddr *)&addr, sizeof(addr));
    assert(ret != -1);

    // 创建线程池
    this->m_pool = ThreadPool::getInstance();
    assert(m_pool != nullptr);

    ret = listen(m_listen_fd, 128);
    assert(ret != -1);
}

// 主线程初始化后处理连接
void WebServer::EventLoop()
{
#ifdef SMART_PTR
    using Listener_ptr = std::shared_ptr<Listener>;
#endif

    // 使用智能指针管理内存
#ifdef SMART_PTR
    Listener_ptr listener(new Listener(m_listen_fd));
#else
    Listener *listener = new Listener(m_listen_fd);
#endif
    listener->Start();

#ifndef SMART_PTR
    delete listener;
#endif
}

void WebServer::Accepter(void *arg)
{

    if (arg == nullptr)
    {
        return;
    }
}