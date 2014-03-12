// Test to see if we can run the server from c++

extern "C" 
{
    #include "server.h"
}

int main ()
{
    run_server();
    return 0;
}
