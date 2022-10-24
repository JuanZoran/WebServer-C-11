#pragma once
#include <stdint.h>

class WebServer
{

public:
    // 启动服务器
    void Run();

private:
    void setFd(int sock);
    void initLfd();
    void initEfd();

public:
    WebServer();
#if 0
    bool setWebServer(Config config);
    WebServer(Coifig&& config);

#endif
    ~WebServer();

private:
    int16_t m_lfd;
    int16_t m_efd;
    int16_t m_port;
    bool isET;
};