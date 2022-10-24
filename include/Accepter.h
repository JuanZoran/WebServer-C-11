#pragma once

class Accepter
{
public:
    // 接受连接请求
    int acceptConnection(int lfd, int efd);
    // 将文件描述符设置为非阻塞
    void setNonBlocking(int fd);
    //文件描述符加入到epoll树上
    void addEpollFd(int fd, int efd);

public:
    // 默认ET模式
    explicit Accepter(bool isET = true);
    ~Accepter() = default;

private:
    bool isET;
};