#pragma once

class Reactor
{
public:
    void processRequest(int fd);

public:
    Reactor() = default;
    ~Reactor() = default;
};