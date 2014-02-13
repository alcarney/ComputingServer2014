#include "Functions.h"

int main ()
{
    ReturnList<int> func("hello", "hello");

    std::cout << *func.callFunction() << std::endl;

    return 0;
}
