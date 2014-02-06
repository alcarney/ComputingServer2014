#ifndef PYFUNC_CPP
#define PYFUNC_CPP

#include <python2.7/Python.h>
#include <iostream>



// Values to get from python:
//      int Quantity
//      float Weight
//      2 element array (floats) location
//      3 elements array (unsigned int) Dims


class PyFunc 
{
    private:
        PyObject *pModule, *pName, *pFunc, *pList, *pValue;
        PyObject *pListLength, pListItem;
        bool isValid;

    public:

        // When created automatically loads function
        // must include call to validFunc to check all is well
        PyFunc(const char* Module, const char* FuncName);
        ~PyFunc();

        int* callFunction();

        // Used to check if the function was loaded correctly
        bool validFunc();
};

#endif
