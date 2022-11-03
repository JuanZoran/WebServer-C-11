#pragma once
class Socket
{
public:
    Socket(short port) noexcept;
    operator int() noexcept { return sock; }
    ~Socket();
    Socket &operator=(Socket &other) = delete;
    Socket(Socket &&other) = delete;

private:
    int sock;
};