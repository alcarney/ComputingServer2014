#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

// This file declares all the classes that will be used to call different types of python function 
// from C++

#include "PyFunc.h"

template <class Type>
class ReturnList : public PyFunc<Type>
{
    public:

            ReturnList(const char* ModuleName, const char* FuncName) : PyFunc<Type>(ModuleName, FuncName) {};
            // This function can be overidden to account for cases where different arguments can be passed
            Type* callFunction();

};


// Calls the function it has loaded, note this is only capable of handling 
// functions that take no arguments and returns a list of ints
template <class Type>
Type* ReturnList<Type>::callFunction()
{
//    std::cout << "Staring call function...\nPerforming function check\n";
    if (PyFunc<Type>::validFunc())
    {
        // Call the function and catch the return value
        std::cout << "[PYFUNC][INFO]: Calling function...\n";
        PyFunc<Type>::pValue = PyObject_CallObject(PyFunc<Type>::pFunc, NULL);

//        std::cout << "Checking the returned variable...\n";
        if (PyFunc<Type>::pValue == NULL)
        {
            std::cout << "[PYFUNC][ERROR]: Called Python function returned nothing\n;";

            // Assume an error occured and print it
            PyErr_Print();

            return NULL;
        }
        // Check that data it received and in proper format
        if (PyList_Check(PyFunc<Type>::pValue))
        {
            // Get the length of the list and convert it to C++ data
//            std::cout << "Getting the size of the returned value\n";
            int length = PyList_Size(PyFunc<Type>::pValue);
            std::cout << "[PYFUNC][INFO]: Function returned a list of length " << length << std::endl;


            // Reserve space for the array
//            std::cout << "Allocating memory...\n";
            Type* values = new Type[length];

            // Convert the values and add them to the array 
            for (int i = 0; i < length; i++)
            {
                // Get a value from the list
                values[i] = PyInt_AsLong(PyList_GetItem(PyFunc<Type>::pValue, i));
            }
//            std::cout << "Returning values\n";
            return values;

        }
        else 
        {
            std::cout << "[PyFunc][ERROR]: No data returned or in wrong format\n";
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

/* Exmaple usage using the new method
  
#include "Functions.h"

int main ()
{
    ReturnList<int> func("hello", "hello");

    std::cout << *func.callFunction() << std::endl;

    return 0;
}
 */
