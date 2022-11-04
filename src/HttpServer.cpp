#include "HttpServer.h"
#include "Reactor.h"

HttpServer::HttpServer(short port) noexcept : sock(port)
{
}

void HttpServer::Run()
{
    Reactor reactor(sock);
    reactor.EventLoop();
}