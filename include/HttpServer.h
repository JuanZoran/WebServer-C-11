#pragma once
#include "Reactor.h"

class HttpServer
{
public:
    // 接受用户指定的端口号
    explicit HttpServer(short port) noexcept;

    // 启动整体框架
    void Run() noexcept;

    HttpServer(HttpServer &server) = delete;
    HttpServer &operator=(HttpServer &server) = delete;

private:
    Reactor reactor;
};