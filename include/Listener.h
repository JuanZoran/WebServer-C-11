#pragma once
#include <sys/epoll.h>
#include "Strategy.h"

class Listener
{
public:
    // begin to EventLoop
    void Start();

    bool Process(STRATEGY::LISTEN_STRATEGY *strategy, int fd);

    // stop EventLoop
    void Stop();

    // restart EventLoop
    void Restart();

public:
    Listener(int lfd);
    ~Listener();

private:
    int m_listen_fd;
    int m_epoll_fd;
    bool m_stop;
};