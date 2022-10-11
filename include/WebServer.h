#pragma once
#include "ServerConf.h"
#include "ThreadPool.h"

class WebServer
{
public: // Construct
    // 禁用拷贝构造函数
    WebServer(const WebServer &) = delete;
    WebServer(const ServerConf &config); // 初始化服务器配置
    ~WebServer();

public:               // methods
    void EventLoop(); // 循环监听请求

private: // attributes
    ThreadPool *m_pool;
    int m_listen_fd;
    const ServerConf m_config;

private: // methods
    void init();
    static void Accepter(void *arg);
};