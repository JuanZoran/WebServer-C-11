#if 1
#include "HttpServer.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        auto ret = chdir(argv[1]);
        if (ret < 0)
            return 1;
    }

    HttpServer server(12345);
    server.Run();
    return 0;
}

#else
#include <iostream>
using namespace std;

class test
{
public:
    test()
    {
        cout << "test 构造函数被调用" << endl;
    }

    test(test &a)
    {
        cout << "test 左值引用被调用" << endl;
    }
    test(test &&a)
    {
        cout << "test 右值引用被调用" << endl;
    }

    ~test()
    {
        cout << "test 析构函数被调用" << endl;
    }

    int a;
};

void fun(test a)
{
    cout << "fun 开始执行" << endl;
}

int main(int argc, char **argv)
{
    fun(test());
    cout << "fun 执行完毕" << endl;

    test a;
    a.a = 10;
    test b = move(a);
    b.a = 20;
    cout << "a = " << a.a << endl;
    cout << "b = " << b.a << endl;
    return 0;
}

#endif
