// Axiom Route Logistics
//
// Main program flow and logic controlled from here

#include <iostream>
#include <thread>

#include "GUI/UI.h"

extern "C"
{
    #include "tools/Sockets/server.h"
}

int main ()
{
    using std::cout;
    using std::endl;
    using std::thread;

    cout << "Welcome to Route Logistics brought to you by Axiom Enterprises!\n";
    cout << "Please would you log in sir...\n\n";

    // Get the user to log in
    int proceed = userLogin();

    // If successful carry on
    if (proceed == 1)
    {
        cout << "[Log][INFO]: Starting UI thread\n";
        thread gui(launchGUI);


        cout << "We are waiting for data to process...\n";


        // Make sure all remaining threads close before terminating
        gui.join();
    }
    return 0;
}
