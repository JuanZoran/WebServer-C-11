#include "HttpServer.h"
#include "MessageQueue.hpp"
#include <unistd.h>

#if 1
int main(int argc, char **argv)
{
    if (argc == 2)
        chdir(argv[1]);

    HttpServer server(12345);
    server.Run();
    return 0;
}

#else
#include <string_view>
#include <iostream>
using namespace std;

string_view f()
{
    return "test for string_view";
}

int main(int argc, char **argv)
{
    cout << f() << endl;
    return 0;
}

#endif
