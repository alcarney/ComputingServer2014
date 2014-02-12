#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

// This file declares all the classes that will be used to call different types of python function 
// from C++

#include "PyFunc.h"

class ReturnIntListNoArgs : public PyFunc
{
    public:

            ReturnIntListNoArgs(const char* ModuleName, const char* FuncName) : PyFunc(ModuleName, FuncName);
            int* callFunction();

}

#endif
