// This program contains the main logic and flow control for the whole application
// Everything will be linked to this file in some shape or form.
//
// I think at the moment the program should function something similar to the following:
//
//      - Program starts, initialises the python interpreter and loads the python code it needs
//      to load the UI. THIS SHOULD BE THE ONLY CODE C++ should have to deal with, all communication
//      must take place through the code loaded at the this step
//
//      - C++ spawns a new thread containing the UI which gets presented to the user and waits to be notified 
//      with a job request. A new thread is necessary so that the user can still use the interface to set up another
//      order while C++ churnes away through the algorithms
//
//      - C++ receives a job request from the UI thread and procedes to process the request by spawning another new thread
//
//      - The program will allow threads to be spawned up until the number of active threads is equal to that available by
//      the computer running the code, at which point jobs will enter a queue to wait until a thread has become free before 
//      proceding to be processed.
//
//      - Finally when the user decides to quit C++ will shut everything down and close.
//
//      Simples!! :P



