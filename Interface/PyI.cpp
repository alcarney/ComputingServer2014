// The implementation of the python interpreter class 
// this class manages a list of functions that can be called 
// and the state of the python interpreter

#include "PyI.h"
#include "PyFunc.h"

// The default constructor for the class
PyI::PyI()
{
    // Fire up the python interpreter
    Py_Initialize();

    // Create a linked list to store functions
    funcList = new LinkedList<PyFunc>();
}


PyI::~PyI()
{
    // Clean up our lists
    delete funcList;

    // CLose down python
    Py_Finalize();
}

void PyI::addFunction(PyFunc* pFunc )
{
    funcList->appendNode(pFunc);
}


