#ifndef PYFUNC_CPP
#define PYFUNC_CPP

#include <python2.7/Python.h>
#include <iostream>



// Values to get from python:
//      int Quantity
//      float Weight
//      2 element array (floats) location
//      3 elements array (unsigned int) Dims

template <class Type>
class PyFunc 
{
    private:
        PyObject* pName, pArgs, pValue;

    public:

        PyFunc<Type>();
        ~PyFunc<Type>();

        void defineFunction(const char* Module, const char* FuncName);
        Type callFunction(PyObject* pArgs);
};

#endif
