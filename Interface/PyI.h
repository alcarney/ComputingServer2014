#ifndef PYTHON_INTERPRETER_CPP
#define PYTHON_INTERPRETER_CPP

#include "../tools/LinkedList.h"
#include <python2.7/Python.h>

class PyI
{
    private:
        LinkedList<int>* modList;
        LinkedList<int>* funcList;

    public:

        PyI();
        ~PyI();

        void addFunction(PyFunc* pFunc);


};

#endif
