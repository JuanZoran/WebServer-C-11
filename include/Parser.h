#pragma once
#include <DataStructure.hpp>
#include <string_view>

using std::string_view;
using KeyValue = std::pair<string, string>;

class Parser
{

public:
    static HttpRequest recvRequest(int cfd);
    // static HttpRequest recvRequest(int cfd, int efd);

private:
    static void readLine(int cfd, string &line);
    static void parseHeader(string &line, RequestHeader &header);
    static bool parseKeyValue(string_view line, KeyValue &result);
    static void recvBody(int cfd, int size, string &body);
};