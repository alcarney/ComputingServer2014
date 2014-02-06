#include "PyFunc.h"

int main ()
{
    PyFunc func("hello", "hello");

    int* ret = func.callFunction();

    for (int i = 0; i < 10; i++)
    {
        std::cout << ret[i] << std::endl;
    }
    return 0;
}

