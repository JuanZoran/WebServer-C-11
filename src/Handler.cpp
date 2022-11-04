#include "Handler.h"
#include <sys/sendfile.h>
#include <sstream>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

HttpResponse Handler::notFound{
    {"HTTP/1.1", 404, "notFound"},
    {},
    "404.html",
    true};

Handler::map Handler::strategy;

HttpRequest Handler::recvRequest(int cfd) noexcept
{
    // 接受客户端的数据
    int size = recvMessage(cfd, buffer, BUFFER_SIZE);
    std::string_view origin(buffer, size);

    // 将客户端的数据格式成HttpRequest格式
    HttpRequest request;
    // 解析请求行
    parseLine(request.line, origin);

    // 解析请求头
    parseHeader(request.header, origin);

    request.body = origin;
#if 0
    cout << "解析结果如下:" << endl;
    cout << request.line << endl;
    for (auto &[key, value] : request.header)
        cout << key << ":" << value << endl;
    cout << request.body;
#endif
    return request;
}

HttpResponse Handler::HandleRequest(const HttpRequest &request) noexcept
{
    cout << "处理中..." << endl;
    auto res = strategy.find(request.line.method);

    // 如果有对应的处理函数则调用, 否则返回错误请求报文
    cout << "处理完成" << endl;
    return res == strategy.end() ? notFound : res->second(request);
}

void Handler::sendResponse(int cfd, const HttpResponse &response) noexcept
{
    // // 创建缓冲区
    std::ostringstream buf;
    cout << response << "\r\n";
    return;
    // 响应行
    if (response.isFileName)
    {
        buf << response.line << "\r\n";
        buf << response.header << "\r\n";
        // 发送文件
    }
    else
    {
        buf << response;
    }
    // 响应体
}
