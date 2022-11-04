#include "Receiver.h"
#include "Epoll.h"
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdexcept>

#include <iostream>
using std::endl, std::cout;

// 声明外部定义的Epoll
extern Epoll epoll;

// 接收消息
int recvMessage(int cfd, char *buffer, size_t BUFFER_SIZE)
{
    memset(buffer, 0, BUFFER_SIZE);
    int size = 0;
    int ret = 1;
    while (ret > 0)
    {
        ret = recv(cfd, buffer + size, BUFFER_SIZE - size, 0);
        if (ret > 0)
            size += ret;
    }
    if (ret == 0)
    {
        epoll.del(cfd);
        close(cfd);
    }
    else if (ret == -1 && errno != EAGAIN)
    {
        perror("recv");
        throw std::logic_error("recv null message");
    }
    return size;
}

// 解析请求行
void parseLine(RequestLine &target, std::string_view &origin)
{
    // 解析协议
    auto pos = origin.find(" ");
    if (pos == std::string_view::npos)
        throw std::logic_error("invalid request format");
    target.method = origin.substr(0, pos);
    origin = origin.substr(pos + 1);

    // 解析方法
    pos = origin.find(" ");
    if (pos == std::string_view::npos)
        throw std::logic_error("invalid request format");
    target.uri = origin.substr(0, pos);
    origin = origin.substr(pos + 1);

    // 解析协议
    pos = origin.find("\r\n");
    if (pos == std::string_view::npos)
        throw std::logic_error("invalid request format");
    target.protocol = origin.substr(0, pos);
    origin = origin.substr(pos + 2);
}

// 解析请求头
void parseHeader(Header &target, std::string_view &origin)
{
    while (true)
    {
        // 先取出一行
        auto pos = origin.find("\r\n");
        if (pos == std::string_view::npos)
            return;
        auto line = origin.substr(0, pos);
        origin = origin.substr(pos + 2);
        // 取出键值对
        pos = line.find(":");
        if (pos == std::string_view::npos)
            return;
        target[line.substr(0, pos)] = line.substr(pos + 1);
    }
}
