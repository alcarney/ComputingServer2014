#include "python_ui.h"

// The new and improved UI handler
// in the far off future as features are added maybe function pointers
// could be used here to distingish between the various tasks the server could 
// perform
int handleUI(int their_socket)
{
    // Set up what we need
    int ack_signal = 1;
    int numLocations;
    char* outbuf = (char *)&ack_signal;
    char* buf = (char *)&numLocations;

    // Let the UI know that we are ready to deal with it
    if (send(their_socket, outbuf, sizeof(ack_signal), 0) == -1)
    {
        // Something went wrong
        perror("send");
        return 1;
    }

    // Get python to tell us how many locations we'll be receiving
    if (recv(their_socket, buf, sizeof(numLocations), 0) == -1)
    {
        // Something is wrong
        perror("recv");
        fprintf(stderr, "Unable to determine how many locations will be sent aborting\n");
        return 1;
    }

    // print the number of locs we will receive
    printf("The UI is sending %d locations over, put some more pies in the oven\n", numLocations);

    return 0;
}
