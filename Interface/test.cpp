#include "Functions.h"

int main ()
{
    ReturnList<int*> func("hello", "hello");

    func.callFunction();

    return 0;
}
