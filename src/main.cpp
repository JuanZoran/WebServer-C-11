#include "WebServer.h"
#include <memory>
#include <unistd.h>

// #include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    if (argc == 2)
        chdir(argv[1]);
    argc == 2 ? chdir(argv[1]) : chdir("../HTML");
    unique_ptr<WebServer> server(new WebServer());
    server->Run();
    return 0;
}