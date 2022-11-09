#include "Fd.hpp"
#include "Handler.h"
#include <sys/sendfile.h>
#include <sstream>
#include "GET.h"
#include <fcntl.h>
#include <arpa/inet.h>

HttpResponse Handler::notFound{
    {"HTTP/1.1", 404, "Not Found"},
    {},
    "404.html",
    {},
    true};

Handler::map Handler::strategy{
    {"GET", [](const HttpRequest &request) -> HttpResponse
     {
         return HttpResponse{
             {"HTTP/1.1", 200, "OK"},
             {},
             GET::map[request.line.uri],
             {},
             true};
     }}};

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
#if 1
    // TODO: 查看解析结果
    cout << "解析结果如下:" << endl;
    cout << request << endl;
#endif
    return request;
}

HttpResponse Handler::HandleRequest(const HttpRequest &request) noexcept
{
    auto res = strategy.find(request.line.method);
    // 如果有对应的处理函数则调用, 否则返回错误请求报文
    return res == strategy.end() ? notFound : res->second(request);
}

void Handler::sendResponse(int cfd, const HttpResponse &response) noexcept
{
    // // 创建缓冲区
    std::ostringstream buf;
    cout << response << "\r\n";

    // TODO: 实现自动计算报文大小
    // 响应行
    if (response.isFileName)
    {
        buf << response.line << "\r\n";
        buf << response.header << "\r\n";
        // 发送文件
        // C++20 可以使用 view 返回视图, 不用拷贝一份字符串
        auto res = buf.str();
        send(cfd, res.data(), res.size(), 0);
        // auto size = std::filesystem::file_size(response.body);
        Fd file = open(response.body.data(), O_RDONLY);
        auto size = lseek(file, 0, SEEK_END);
        lseek(file, 0, SEEK_SET);
        sendfile(cfd, file, 0, size);
    }
    else
    {
        buf << response;
        auto res = buf.str();
        send(cfd, res.data(), res.size(), 0);
    }
    // 响应体
}
