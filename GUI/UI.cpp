// This file manages the UI

#include <iostream>
#include "../tools/Python/Functions.h"


// This wont be in the final version since there is only one main()
// function per C++ program but it will be commented out later and used
// as a guide on how to use the functions defined here
int main()
{
    ReturnList<int>* login = new ReturnList<int>("login", "main");

    int* ret = login->callFunction();

    std::cout << ret[0] << ret[1] << ret[2] << std::endl;

    return 0;
}
