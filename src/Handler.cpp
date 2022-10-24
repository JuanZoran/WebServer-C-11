#include "Handler.h"
#include <unordered_map>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <assert.h>
#include <stdexcept>
#include <unistd.h>

#include <iostream>
using std::cout, std::endl;
using std::string;
using std::string_view;

// FIXME: 客户端主动断开连接, 会发生SIGPIPE的信号, 需要去捕获该事件, 防止crash

void Handler::Process(int cfd, const HttpRequest &request)
{
    // 主流程: 处理逻辑 => 回应客户端
    HttpResponse response;
    try
    {
        processRequest(request, response);
    }
    catch (const std::logic_error &e)
    {
        cout << "request:" << request.header.URL << "  " << e.what() << endl;
        badRequest(cfd);
        return;
    }
    responseRequest(cfd, response);
    cout << "发送完成" << endl;
}

void Handler::badRequest(int cfd)
{
    // 404request
    sendResponseHeader(cfd, ResponseHeader{"HTTP/1.1", 404, "Not Found"});
}

void Handler::sendResponseHeader(int cfd, const ResponseHeader &header)
{
    int size = snprintf(NULL, 0, "%s %d %s\r\n", header.protocol, header.statusCode, header.description);
    char *buffer = (char *)malloc(size);
    sprintf(buffer, "%s %d %s\r\n", header.protocol, header.statusCode, header.description);
    send(cfd, buffer, size - 1, 0);
    free(buffer);
}

string Handler::getFileType(string_view file)
{
    auto pos = file.rfind(".");
    if (pos == std::string_view::npos)
        return "text/plain; charsets=utf-8";
    auto type = file.substr(pos + 1);
    if (type == "html" || type == "htm")
        return "text/html; charset=utf-8";
    // TODO:更多模式的文件解析
    if (type == "ico")
        return "image/x-icon";
    if (type == "jpg")
        return "image/jpeg";
    // if (type == "html" || type == "htm")
    //     return "text/html; charset=utf-8";
    // if (type == "html" || type == "htm")
    //     return "text/html; charset=utf-8";
    return "text/plain; charset=utf-8";
}

void GetHandler::processRequest(const HttpRequest &request, HttpResponse &response)
{
    // 解析URL
    if (request.header.URL == "/")
        response.body = "index.html";
    else
        response.body = request.header.URL.substr(1);
    // 获取文件的信息
    struct stat st;
    int ret = stat(response.body.c_str(), &st);
    if (ret == -1)
        throw std::logic_error("Not a valid request");
    response.header.statusCode = 200;
    response.header.description = "OK";
    response.header.protocol = "HTTP/1.1";

    // 处理消息键值对
    response.headerBody["content-length"] = std::to_string(st.st_size);
    response.headerBody["content-type"] = getFileType(response.body);
}

void GetHandler::responseRequest(int cfd, const HttpResponse &response)
{
    // 发送报头
    sendResponseHeader(cfd, response.header);

    string content;
    for (auto &i : response.headerBody)
    {
        content += i.first + ":" + i.second + "\r\n";
    }
    content += "\r\n";
    send(cfd, content.c_str(), content.size(), 0);
    sendFile(cfd, response.body.c_str(), std::stoi(response.headerBody.at("content-length")));
}

void GetHandler::sendFile(int cfd, const char *filename, int fsize)
{
    cout << "sendfile " << filename << endl;
    if (fsize < 0)
        throw std::invalid_argument("invalid file size");

    int fd = open(filename, O_RDONLY);
    off_t offset = 0;
    while (offset != fsize)
    {
        sendfile(cfd, fd, &offset, fsize - offset);
    }
}