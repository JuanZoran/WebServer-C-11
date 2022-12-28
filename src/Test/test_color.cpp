#if 1
#include <iostream>
#endif
#include <Color.hpp>

using namespace std;
using namespace Zoran;

// TODO: 完全使用智能指针: (unique ptr, shared ptr, weak ptr)

int main(int argc, char* argv[])
{
    cout << Green << "Hello World in Green ! " << Endl;
    cout << "Hello World in plain ! " << endl;

    cout << Yellow << "Hello World in Yellow ! " << Endl;
    cout << "Hello World in plain ! " << endl;

    cout << Red << HighLight << "Hello World in Red ! " << Endl;
    cout << "Hello World in plain ! " << endl;

    cout << Dgreen << "Hello World in Dgreen ! " << Endl;
    cout << "Hello World in plain ! " << endl;

    cout << Blue << "Hello World in Blue ! " << Endl;
    cout << "Hello World in plain ! " << endl;

    cout << Purpor << "Hello World in Purpor ! " << Endl;
    cout << "Hello World in plain ! " << endl;
    return 0;
}
