#include "Parser.h"
#include <sstream>
#include <string.h>
#include <arpa/inet.h>
#include <stdexcept>

HttpRequest Parser::recvRequest(int cfd)
{
    HttpRequest result;
    string lineBuffer;
    // 解析请求头
    readLine(cfd, lineBuffer);
    parseHeader(lineBuffer, result.header);

    // 解析请求键值对
    std::pair<string, string> Key_Value;
    do
    {
        readLine(cfd, lineBuffer);
        if (parseKeyValue(lineBuffer, Key_Value))
            result.keyMap.insert(Key_Value);
        else
            break;
    } while (true);

    // 接收请求主体
    // 判断是否是GET
    // 如果是GET请求则不用接受消息体了
    if (0 != strcasecmp(result.header.method.c_str(), "GET"))
    {
        int size = std::stoi(result.keyMap["content-length"]);
        recvBody(cfd, size, result.body);
    }
    return result;
}

// 接受请求行
void Parser::readLine(int cfd, string &line)
{
    // 清空字符串
    line.clear();

    // 开始接受数据
    char x = 'x';
    size_t len = 0;
    while (true)
    {
        len = recv(cfd, &x, 1, 0);
        if (len > 0)
        {
            if (x == '\r')
            {
                // http的换行为 \r\n, 需要多接收一次
                recv(cfd, &x, 1, 0);
                break;
            }
            else
                line += x;
        }
        else
            throw std::logic_error("There is no line can be accepted");
    }
}

void Parser::parseHeader(string &line, RequestHeader &header)
{
    using std::stringstream;
    stringstream ss(line);
    ss >> header.method >> header.URL >> header.protocol;
    return;
}

bool Parser::parseKeyValue(string_view line, KeyValue &result)
{
    auto pos = line.find(':');
    if (pos == std::string_view::npos)
        return false;
    result.first = line.substr(0, pos);
    result.second = line.substr(pos + 1);
    return true;
}

void Parser::recvBody(int cfd, int size, string &body)
{
    char *buf = new char[size + 1];
    int ret = recv(cfd, buf, size, 0);
    buf[size] = 0;
    body = buf;
    delete[] buf;
}