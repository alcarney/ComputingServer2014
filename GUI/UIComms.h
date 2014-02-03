#ifndef UICOMMS_CPP
#define UICOMMS_CPP

#include "../Interface/PyI.h"

// UIComms class inherits the PyI class
class UIComms : public PyI
{
    public:

            // The constructor should call PyI's constructor then call the loadPythonSource() function
            UIComms() : PyI() {loadPythonSource();};
            ~UIComms();

            // This is used to load the UI for the user
            void run();
            void loadPythonSources();
}

#endif
