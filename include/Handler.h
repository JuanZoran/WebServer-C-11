#pragma once
#include <DataStructure.hpp>

using std::string_view;

// Handler基类
class Handler
{
public:
    // Template Method
    void Process(int cfd, const HttpRequest &request);

public:
    virtual ~Handler() = default;

protected:
    virtual void processRequest(const HttpRequest &request, HttpResponse &response) = 0;
    virtual void responseRequest(int cfd, const HttpResponse &response) = 0;
    void sendResponseHeader(int cfd, const ResponseHeader &header);
    void badRequest(int cfd);
    string getFileType(string_view file);
};

class GetHandler : public Handler
{
    // Handler类
    // 只负责处理请求和回应请求
private:
    void processRequest(const HttpRequest &request, HttpResponse &response) override;
    void responseRequest(int cfd, const HttpResponse &response) override;
    void sendFile(int cfd, const char *filename, int fsise);
};

#if 0
class PostHandler
{
public:
    // Handler类
    // 只负责处理请求和回应请求
    string Process(string_view request);
};

#endif
