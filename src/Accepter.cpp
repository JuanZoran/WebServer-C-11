#include "Accepter.h"
#include <fcntl.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/epoll.h>

Accepter::Accepter(bool isET) : isET(isET)
{
}

int Accepter::acceptConnection(int lfd, int efd)
{
    assert(lfd != -1 && efd != -1);
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    int cfd = accept(lfd, (struct sockaddr *)&addr, &addrlen);
    assert(cfd != -1);
    if (isET)
        setNonBlocking(cfd);
    addEpollFd(cfd, efd);
    return cfd;
}

void Accepter::setNonBlocking(int fd)
{
    int flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void Accepter::addEpollFd(int fd, int efd)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = isET ? EPOLLIN | EPOLLET : EPOLLIN;
    assert(epoll_ctl(efd, EPOLL_CTL_ADD, fd, &event) != -1);
}
