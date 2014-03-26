#include "python_ui.h"

// The new and improved UI handler
int handleUI(int their_socket)
{
    printf("pythonUI: New client detected, requesting login\n");
    if(loginSuccessful() == 0)
    {
        printf("User quit without logging in or maximum trials reached closing connection\n");
        return 1;
    }

    printf("Successful login!\n");

    return 0;
}

// Get the of lines in a text file
int getNumLines(FILE * file)
{

    int i = 0;                  // Store the count in i
    char x [256];             // Buffer to store the lines in

    // Loop through to end of file
    while(fgets(x, 256, file))
    {
        //puts(x);
        i++;    // Else increment counter
    }

    // Return the result
    return i;
}

// Login function
int loginSuccessful()
{
    // Open the user accounts file in read only mode
    printf("\tlogin: Opening accounts file\n");
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

    // We assume that each line in the accounts file is a separate account
    printf("\tlogin: Getting number of registered accounts\n");
    printf("There are %i accounts to check\n", getNumLines(users));

    // Loop through each character in the file
    //printf("s\n", user.username);

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
