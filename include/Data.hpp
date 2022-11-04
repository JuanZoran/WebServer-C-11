#include <string_view>
#include <unordered_map>
#include <ostream>

using str = std::string_view;
using Header = std::unordered_map<str, str>;
using Body = std::string_view;

// 定义请求处理阶段的数据结构
static std::ostream &operator<<(std::ostream &os, const Header &header)
{
    for (auto &[key, value] : header)
        os << key << ":" << value << "\r\n";
    return os;
}

struct RequestLine
{
    str method;
    str uri;
    str protocol;

    friend std::ostream &operator<<(std::ostream &os, const RequestLine &line)
    {
        return os << line.method << " " << line.uri << " " << line.protocol;
    }
};

struct ResponseLine
{
    // 使用的Http协议
    str protocol;
    // 状态码
    int status;
    // 描述
    str description;
    friend std::ostream &operator<<(std::ostream &os, const ResponseLine &line)
    {
        return os << line.protocol << " " << line.status << " " << line.description;
    }
};

struct HttpRequest
{

    RequestLine line;
    Header header;
    Body body;

    friend std::ostream &operator<<(std::ostream &os, const HttpRequest &request)
    {
        os << request.line << "\r\n";
        os << request.header << "\r\n";
        return os << request.body << "\r\n";
    }
};

struct HttpResponse
{
    ResponseLine line;
    Header header;
    Body body;
    bool isFileName;
    friend std::ostream &operator<<(std::ostream &os, const HttpResponse &response)
    {
        os << response.line << "\r\n";
        os << response.header << "\r\n";
        os << "\r\n";
        return os << response.body << "\r\n";
    }
};
