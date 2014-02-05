#include "PyFunc.h"

int main ()
{
    PyFunc func("hello", "hello");

    std::cout << *func.callFunction() <<std::endl;

    return 0;
}

