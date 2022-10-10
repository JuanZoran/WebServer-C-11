#include "WebServer.h"
#include <arpa/inet.h>
#include <assert.h>

WebServer::WebServer(const ServerConf &config) : config(config)
{
    // 初始化监听套接字
    this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(this->listen_fd > 0);
    init();
}

//初始化操作
void WebServer::init()
{
    // 初始化监听的地址
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(config.server_port);
    int ret = bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr));
    assert(ret == 0);
    this->Pool = new ThreadPool();
    assert(Pool != nullptr);
}

// 主线程初始化后处理连接
void WebServer::Listen()
{
    listen(listen_fd, 16);
    sockaddr_in addr;
    socklen_t len = sizeof(addr);
    while (true)
    {
        int socket = accept(listen_fd, (struct sockaddr *)&addr, &len);
        assert(socket > 0);
    }
}
