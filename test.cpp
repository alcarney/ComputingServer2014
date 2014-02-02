#include <python2.7/Python.h>
#include <iostream>

int main ()
{


    //Py_SetPythonHome("/usr/lib/python27.zip:/usr/lib/python2.7/:/usr/lib/python2.7/plat-linux2:/usr/lib/python2.7/lib-tk:/usr/lib/python2.7/lib-old:/usr/lib/python2.7/lib-dynload:/home/alex/Programming/C++/PythonEmbed:");

    Py_Initialize();

    PyRun_SimpleString("import hello");
    PyRun_SimpleString("hello.hello()");

    Py_Finalize();

    return 0;
}
