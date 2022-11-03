#include "HttpServer.h"
#include <unistd.h>
#include "Reactor.h"

HttpServer::HttpServer(short port) noexcept : sock(Socket(port))
{
}

void HttpServer::Run()
{
    Reactor reactor(sock);
    reactor.EventLoop();
}