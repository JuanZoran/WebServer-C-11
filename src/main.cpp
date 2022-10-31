#include <Buffer.hpp>
#include <iostream>
#include <string_view>
#include <memory>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <cassert>

using namespace std;

int main(int argc, char **argv)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(fd > 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr));

    listen(fd, 128);

    struct sockaddr_in caddr;
    socklen_t addrlen = sizeof(caddr);
    int cfd = accept(fd, (struct sockaddr *)&caddr, &addrlen);
    cout << "cfd = " << cfd << endl;

    constexpr int BUFFER_SIZE = 1024;
    Zoran::Buffer<BUFFER_SIZE> buffer;

    // auto flag = fcntl(cfd, F_GETFL, 0);
    // fcntl(cfd, F_SETFL, flag | O_NONBLOCK);

    int ret = recv(cfd, buffer, BUFFER_SIZE, 0);
    buffer.update(ret);
    cout << ret << endl;
    if (ret < 0)
    {
        perror("ret error");
    }
    string_view request(buffer.data(), buffer.dataSize());
    cout << request << endl;

    close(cfd);
    close(fd);
    return 0;
}