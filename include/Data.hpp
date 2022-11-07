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
    // tot = 48 + 56 + 16 => 120
    RequestLine line; // 48
    Header header;    // 56
    Body body;        // 16

    friend std::ostream &operator<<(std::ostream &os, const HttpRequest &request)
    {
        os << request.line << "\r\n";
        os << request.header << "\r\n";
        return os << request.body << "\r\n";
    }
};

struct HttpResponse
{
    // tot = 36 + 56 + 16 + 1 = 109
    // 对齐到16的倍数 => 120 (浪费了11个字节)
    ResponseLine line;  // 36
    Header header;      // 56
    Body body;          // 16
    int32_t isFileName; // 1
    int32_t filesize;   // 可选的

    friend std::ostream &operator<<(std::ostream &os, const HttpResponse &response)
    {
        os << response.line << "\r\n";
        os << response.header << "\r\n";
        return os << response.body << "\r\n";
    }
};
