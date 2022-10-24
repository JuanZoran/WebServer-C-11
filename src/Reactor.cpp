#include "Reactor.h"
#include "Parser.h"
#include "Handler.h"
#include <strings.h>

// #include <iostream>
// using std::cout;
// using std::endl;
using std::string;

void Reactor::processRequest(int fd)
{
    /// TODO: 责任链模式
#if 0
    // Receiver处理请求
    // Parser 解析请求
    Parser parser;
    HttpRequest res = parser.recvRequest(request);
    // Handler 处理请求
    Handler handler;
    string result = handler.Process(res.body);
    // Response 响应请求
    Responser responser;
    responser.responseRequest(fd, result);
#else
    // test
    auto request = Parser::recvRequest(fd);
    if (0 != strcasecmp(request.header.method.c_str(), "GET"))
        // TODO: POST请求解析
        return;
    else
        GetHandler().Process(fd, request);
#endif
}