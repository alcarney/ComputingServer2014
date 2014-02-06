#include "PyFunc.h"

int main ()
{
    PyFunc func("hello", "hello");

    int* ret = func.callFunction();
    
    std::cout << ret[0] <<std::endl;
    std::cout << ret[1] <<std::endl;
    std::cout << ret[2] <<std::endl;

    return 0;
}

