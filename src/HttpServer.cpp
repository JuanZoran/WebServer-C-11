#include "HttpServer.h"

HttpServer::HttpServer(short port) noexcept : reactor(port)
{
}

void HttpServer::Run() noexcept
{
    reactor.EventLoop();
}