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
    protected:
        PyObject *pModule, *pName, *pFunc, *pList, *pValue;
        PyObject *pListLength, pListItem;
        bool isValid;

    public:

        // When created automatically loads function
        // must include call to validFunc to check all is well
        PyFunc<Type>(const char* Module, const char* FuncName, char* FileName);
        ~PyFunc<Type>();

        // Makes the function pure virtual and must be implemented by classes that inherit this
//        virtual Type callFunction();

        // Used to check if the function was loaded correctly
        bool validFunc() {return isValid;};
};


// Constructor automatically pulls function from python if needed
template <class Type>
PyFunc<Type>::PyFunc(const char* ModuleName, const char* FuncName, char* FileName)
{
    Py_Initialize();

    // The following is awful inflexible hard coded cruft, needed to shoehorn something in 
    // for now
    int argc = 1;
    char * argv[3];

    argv[0] = FileName;

    // Set the argv variable
    PySys_SetArgv(argc, argv);

    // Convert the name of the module into something python understands
    pName = PyString_FromString(ModuleName);

    // Import said module
    pModule = PyImport_Import(pName);


    // If import was succesful continue else throw a wobbly
   if (pModule != NULL)
    {
        std::cout << "Loading function ...\n";
        // Now get the function from the file
        pFunc = PyObject_GetAttrString(pModule, FuncName);

        // Check that it worked
        if (pFunc && PyCallable_Check(pFunc))
        {
            std::cout << "[PyFunc][INFO]: Succesfully loaded function " << FuncName 
                << " from " << ModuleName << " module\n";
            isValid = true;
        }
        else
        {
           std::cout << "[PyFunc][ERROR]: " << FuncName << " not a valid function or not in " << ModuleName << std::endl;
           isValid = false;
        }
    }
    else
    {
        std::cout << "[PyFunc][ERROR]: Unable to load module " << ModuleName << std::endl;
        isValid = false;
    }
}

// Destructor,
template <class Type>
PyFunc<Type>::~PyFunc()
{
    Py_Finalize();
}

/*
template <class Type>
bool PyFunc::validFunc()
{
    return isValid;
}*/

/* An example program
 *
 *
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
    
    And the python file

    hello.py:

    def hello();
        return [1,2,3,4,5,6,7,8,9,10]

*/

#endif
