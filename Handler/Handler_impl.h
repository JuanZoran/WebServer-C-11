#pragma cone
#include "Handler_base.h"
#include "Data.hpp"

int recvMessage(int cfd, char *buffer, size_t BUFFER_SIZE);

void parseLine(RequestLine &target, std::string_view &origin);

void parseHeader(Header &target, std::string_view &origin);

// TODO:文件类型解析
str getFileType(str filename);