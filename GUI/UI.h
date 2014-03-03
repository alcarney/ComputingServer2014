#ifndef UI_CPP
#define UI_CPP

#include "../tools/Python/PyI.h"

// UIComms class inherits the PyI class
class UI : public PyI
{
    public:

            // The constructor should call PyI's constructor then call the loadPythonSource() function
            UI() : PyI() {loadPythonSource();};
            ~UI();

            // This is used to load the UI for the user
            void run();
            void loadPythonSource();
}

#endif
