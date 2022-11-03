#include "HttpServer.h"
#include "MessageQueue.hpp"
#include <unistd.h>
#include <iostream>
using std::endl, std::cout;

#if 1
int main(int argc, char **argv)
{
    if (argc == 2)
        chdir(argv[1]);

    HttpServer server(12345);
    server.Run();
    cout << "ok" << endl;
    return 0;
}

#else
#include <thread>
#include <chrono>

using namespace std::chrono;
using std::thread;
struct test
{
    const char *mes;
    int status;
};
MessageQueue<test> queue;

void worker()
{
    while (true)
    {
        // 不停的取出任务并且读
        auto msg = queue.pop();
        cout << "线程id:" << std::this_thread::get_id() << "取出msg" << endl;
        cout << msg.mes << "\t" << msg.status << "\t" << endl;
    }
}
int main(int argc, char **argv)
{
    thread t[10];
    for (int i = 0; i < 10; i++)
        t[i] = thread(worker);

    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(3s);
        test t{"test", i};
        queue.push(t);
    }

    for (int i = 0; i < 10; i++)
        t[i].join();
    return 0;
}

#endif
