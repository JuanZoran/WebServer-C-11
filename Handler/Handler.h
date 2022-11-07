#pragma once
#include <iostream>
#include "Handler_base.h"
#include "Handler_impl.h"
#include <functional>

using std::endl, std::cout;
// 接口继承
class Handler : public Handler_base
{
private:
    // 使用map来映射 不同策略的方案
    using map = std::unordered_map<str, std::function<HttpResponse(const HttpRequest &)>>;

    // 不同类型的不同方案
    static map strategy;

    // 错误时候的数据
    // static HttpResponse badRequest;
    static HttpResponse notFound;

public:
    void processRequest(int cfd)
    try
    {
        auto request = recvRequest(cfd);
        auto response = HandleRequest(request);
        if (response.header.find("content-length") == response.header.end())
            response.header["content-length"] = "-1";

        sendResponse(cfd, response);
    }
    catch (std::logic_error e)
    {
        // TODO: 查看错误结果
        cout << "抓到错误" << endl;
        cout << e.what() << endl;
        sendResponse(cfd, notFound);
    }

private:
    HttpRequest recvRequest(int cfd) noexcept;

    HttpResponse HandleRequest(const HttpRequest &request) noexcept;

    void sendResponse(int cfd, const HttpResponse &response) noexcept;
};
