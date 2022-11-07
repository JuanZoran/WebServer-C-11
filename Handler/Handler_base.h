#pragma once

class Handler_base
{
public:
    Handler_base() : buffer{0} {};
    ~Handler_base() = default;

protected:
    const static int BUFFER_SIZE = 1024;

protected:
    // 接受时用的缓冲区
    char buffer[BUFFER_SIZE];
};
