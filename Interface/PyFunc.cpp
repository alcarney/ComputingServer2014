// Contains the defintion for the python function class

#include "PyFunc.h"


// Constructor automatically pulls function from python if needed
PyFunc::PyFunc(const char* ModuleName, const char* FuncName)
{
    Py_Initialize();

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
PyFunc::~PyFunc()
{
    //Py_DECREF(pModule);
   // Py_DECREF(pName);
    //Py_DECREF(pFunc);
    //Py_DECREF(pArgs);
    //Py_DECREF(pValue);
    Py_Finalize();
}

// Calls the function it has loaded, note this is only capable of handling 
// functions that take no arguments and returns a list of ints
int* PyFunc::callFunction()
{
    // Call the function and catch the return value
    pValue = PyObject_CallObject(pFunc, NULL);

    // Check that data it received and in proper format
    if (PyList_Check(pValue))
    {
        // Get the length of the list and convert it to C++ data
        pListLength =  PyList_Size(pValue);
        int length = PyInt_AsLong(pListLength);

        // Reserve space for the array
        int* values = new int[length];

        // Convert the values and add them to the array 
        for (int i = 0; i < length; i++)
        {
            // Get a value from the list
            pListItem = PyList_GetItem(pValue, i);

            *values[i] = PyInt_AsLong(pListItem);
        }
        return values;

    }
    else 
    {
        std::cout << "Error no data returned or in wrong format\n";
        return 0;
    }

}
