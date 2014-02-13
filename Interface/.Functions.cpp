#include "Functions.h"

// Calls the function it has loaded, note this is only capable of handling 
// functions that take no arguments and returns a list of ints
int* ReturnList::callFunction()
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
