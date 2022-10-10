#pragma once
#include "ServerConf.h"
#include "ThreadPool.h"

class WebServer
{
public:
    WebServer(const ServerConf &config); // 初始化服务器配置
    ~WebServer();
    void Listen(); // 循环监听请求

private:
    void init();
    ThreadPool *Pool;
    int listen_fd;
    const ServerConf config;
    static void accepter();
};