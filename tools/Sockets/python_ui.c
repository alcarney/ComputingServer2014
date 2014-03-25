#include "python_ui.h"

// The new and improved UI handler
int handleUI(int their_socket)
{
    if(loginSuccessful() == 0)
    {
        printf("User quit without logging in or maximum trials reached closing connection\n");
        return 1;
    }

    printf("Successful login!\n");

    return 0;
}

// Login function
int loginSuccessful()
{
    // Open the user accounts file in read only mode
    FILE *users;
    users = fopen("data/accounts.txt", "r");

    // Check to see if it opened correctly
    if (users == 0 )
    {
        fprintf(stderr, "Unable to retrieve account detals\n");
        return 0;
    }

    // Load the accounts
    int x;                       // variable to store a single character in
    int i = 0;                   // Used to count position in file
    struct account user;

    // Loop through each character in the file
    while (1)
    {
        x = fgetc(users);
        if (x == '\n')
            break;

        user.username[i] = x;
        i++;
    }
    printf("s\n", user.username);

    return 1;
}

/*
    // Set up what we need
    int numLocations;
    char* buf = (char *)&numLocations;

    // Get python to tell us how many locations we'll be receiving
    receiveData(their_socket, buf, sizeof(numLocations));
    // print the number of locs we will receive
    printf("The UI is sending %d locations over, put some more pies in the oven\n", numLocations);
*/
