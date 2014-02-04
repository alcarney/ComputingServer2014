// Contains the defintion for the python function class

#include "PyFunc.h"


// Constructor automatically pulls function from python if needed
PyFunc::PyFunc(const char* ModuleName, const char* FuncName)
{
    Py_Initialize();

    // Convert the name of the module into something python understands
    pName = PyString_FromString(ModuleName);

    // Import said module and nullify the pName reference
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

// Destructor, calls multiple Py_DECREF calls to delete references to PyObjects
PyFunc::~PyFunc()
{
    Py_DECREF(pModule);
   // Py_DECREF(pName);
    //Py_DECREF(pFunc);
    //Py_DECREF(pArgs);
    //Py_DECREF(pValue);
    Py_Finalize();
}

// Calls the function and passes whatever arguments it gets onwards
int* PyFunc::callFunction(int a, int b)
{
    // Create a list to pass our arguments to python with
    ///pArgs = PyTuple_New(2);

    //pValue = PyInt_FromLong(a);

}
