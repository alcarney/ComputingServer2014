// The implementation of the python interpreter class 
// this class manages a list of functions that can be called 
// and the state of the python interpreter

#include "PyI.h"


// The default constructor for the class
PyI::PyI()
{
    // Fire up the python interpreter
    Py_Initialize();

    // Create a linked list to store functions and modules in
    modList = new LinkedList<int>();
    funcList = new LinkedList<int>();
}

PyI::~PyI()
{
    // Clean up our lists
    delete modList;
    delete funcList;

    // CLose down python
    Py_Finalize();
}
