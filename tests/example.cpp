// This example file runs a given function from a given python source file and given arguments

#include <python2.7/Python.h>
#include <iostream>

int main (int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    // Initilise pointers to python objects
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;

    // Check to see if enough arguments have been provided
    if (argc < 3)
    {
        cout << "Usage: call pythonfile funcname [args]\n";
        return 1;
    }

    // Fire up the python interpreter
    Py_Initialize();

    // Get the name of the source file to use
    pName = PyString_FromString(argv[1]);

    // Import the source code contained in that file into the interpreter
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    // If the import was succesfull
    if (pModule != NULL)
    {
        // Get the function from the source file
        pFunc = PyObject_GetAttrString(pModule, argv[2]);

        // Check to see if this function exists and is valid
        if (pFunc && PyCallable_Check(pFunc))
        {
            // Create a python list to store the function arguments in
            pArgs = PyTuple_New(argc - 3);

            // For each argument given
            for (int i = 0; i < argc - 3; i++)
            {
                // Convert the arguments into something python can understand
                pValue = PyInt_FromLong(atoi(argv[i + 3]));

                // If conversion fails
                if (!pValue)
                {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);

                    cout << "Error! Unable to convert argument" << argv[i + 3] << endl;
                    return 1;
                }

                // Add the argument to the list
                PyTuple_SetItem(pArgs, i, pValue);
            }

            // Call the function in python and catch the return value
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            // If we get a return value
            if (pValue != NULL)
            {
                // Be sure to convert the value back into something C++ understands
                cout << "Result of function call: " << PyInt_AsLong(pValue) << endl;
                Py_DECREF(pValue);
            }
            else
            {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);

                // Print the error from python
                PyErr_Print();
                cout << "Call Failed\n";
                return 1;
            }
        }
        else
        {
            // If there was a python error
            if (PyErr_Occurred())
            {
                // Show it to me
                PyErr_Print();
            }
            cout << "Unable to find function " << argv[2] << " from file " << argv[1] << endl;
        }

        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else
    {
        PyErr_Print();
        cout << "Failed to load " << argv[1] << endl;
        return 1;
    }

    // Close down the python interpreter
    Py_Finalize();
    return 0;
}
