#include "python_ui.h"

// The new and improved UI handler
// in the far off future as features are added maybe function pointers
// could be used here to distingish between the various tasks the server could 
// perform
int handleUI(int their_socket)
{
    // Set up what we need
    int numLocations;
    char* buf = (char *)&numLocations;

    // Get python to tell us how many locations we'll be receiving
    receiveData(their_socket, buf, sizeof(numLocations));
    // print the number of locs we will receive
    printf("The UI is sending %d locations over, put some more pies in the oven\n", numLocations);

    return 0;
}
