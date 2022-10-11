#include "../include/Listener.h"
#include "assert.h"

Listener::Listener(int lfd) : m_listen_fd(lfd), m_stop(false)
{
    // 该参数在Linux 2.6以后被忽略
    //创建一棵epoll树, 用于监听
    m_epoll_fd = epoll_create(1);
    assert(m_epoll_fd != -1);
}

// begin to EventLoop
void Listener::Start()
{
    int ret = Process(new STRATEGY::LISTEN_ADD, m_listen_fd);
    assert(ret == 1);

    struct epoll_event ev_set[1024];
    int size = sizeof(ev_set) / sizeof(struct epoll_event);
    // begin to listen the events
    while (!m_stop)
    {
        ret = epoll_wait(m_epoll_fd, ev_set, size, -1);
        for (int i = 0; i < ret; i++)
        {
            if (ev_set[i].data.fd == m_listen_fd)
            {
                // TODO: add fd to the accept-queue
            }
            else
            {
                // TODO: notify the accepter
            }
        }
    }
}

// stop EventLoop
void Listener::Stop()
{
    m_stop = true;
}

bool Listener::Process(STRATEGY::LISTEN_STRATEGY *strategy, int fd)
{
    if (!strategy)
    {
        return false;
    }
    bool ret = strategy->Process(m_epoll_fd, fd);
    delete strategy;
    strategy = nullptr;
    return ret;
}
