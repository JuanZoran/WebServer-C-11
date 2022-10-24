#pragma once
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

struct RequestHeader
{
    // 请求的方法
    string method;
    // 请求的URL [资源]
    string URL;
    // 使用的hTTP协议
    string protocol;
};

struct HttpRequest
{
    RequestHeader header;
    // 请求头
    std::unordered_map<string, string> keyMap;
    // 请求主体
    string body;
};

struct ResponseHeader
{
    const char *protocol;
    int statusCode;
    const char *description;
};
struct HttpResponse
{
    ResponseHeader header;
    std::unordered_map<string, string> headerBody;
    string body;
};
