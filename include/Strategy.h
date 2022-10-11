#pragma once
#include "Listener.h"

namespace STRATEGY
{
    class LISTEN_STRATEGY
    {
    public:
        LISTEN_STRATEGY();
        virtual ~LISTEN_STRATEGY();

        virtual bool Process(int epoll_fd, int fd) = 0;
    };

    class LISTEN_ADD : public LISTEN_STRATEGY
    {
        bool Process(int epoll_fd, int fd) override;
    };

    class LISTEN_DEL : public LISTEN_STRATEGY
    {
        bool Process(int epoll_fd, int fd) override;
    };
} // namespace STRATEGY
