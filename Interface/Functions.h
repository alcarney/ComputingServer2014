#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

// This file declares all the classes that will be used to call different types of python function 
// from C++

#include "PyFunc.h"

template <class Type>
class ReturnList<Type> : public PyFunc<Type>
{
    public:

            ReturnList(const char* ModuleName, const char* FuncName) : PyFunc<Type>(ModuleName, FuncName) {};
            Type callFunction();

};


// Calls the function it has loaded, note this is only capable of handling 
// functions that take no arguments and returns a list of ints
template <class Type>
Type ReturnList<Type>::callFunction()
{
    if (validFunc())
    {
        // Call the function and catch the return value
        pValue = PyObject_CallObject(pFunc, NULL);

        // Check that data it received and in proper format
        if (PyList_Check(pValue))
        {
            // Get the length of the list and convert it to C++ data
            int length = PyList_Size(pValue);


            // Reserve space for the array
            int* values = new int[length];

            // Convert the values and add them to the array 
            for (int i = 0; i < length; i++)
            {
                // Get a value from the list
                values[i] = PyInt_AsLong(PyList_GetItem(pValue, i));
            }
            return values;

        }
        else 
        {
            std::cout << "Error no data returned or in wrong format\n";
            return NULL;
        }
    }
    else
    {
        std::cout << "[PyFunc][ERROR]: Attempted call to undefined function, doing nothing\n";
        return NULL;
    }

}

#endif
