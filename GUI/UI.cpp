// This file manages the UI

#include <iostream>
#include "../tools/Python/Functions.h"


// This function runs the login screen written in python, gets
// a yay or nay signal and passes it back to C++ who then either 
// closes or carries on executing the app
bool userLogin()
{
    // Load the python login file 
    ReturnList<bool>* login = new ReturnList<bool>("login", "main");

    // Execute it
    bool* ret = login->callFunction();

    if (ret == NULL)
    {
        std::cout << "Something went wrong function returned null\n";
        return false;
    }
    else
    {
        // Yay or nay?
        return *ret;
    }

}

/* This wont be in the final version since there is only one main()
 function per C++ program but it will be commented out later and used
 as a guide on how to use the functions defined here
int main()
{
    ReturnList<int>* login = new ReturnList<int>("login", "main");

    int* ret = login->callFunction();

    if (ret == NULL)
    {
        std::cout << "Something went wrong function returned null\n";
    }
    else
    {
        std::cout << ret[0] << ret[1] << ret[2] << std::endl;
    }

    return 0;
} */
