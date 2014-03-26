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

// Load the accounts from file into the struct provided
int loadAccounts(FILE* file, struct account* accounts, int num)
{
    char buffer[256]; 
    int i;

    // Loop through each account in the file and pass it into an appropriate struct
    for (i = 0; i < num; i++)
    {
        // Get the next line from the file and store it in buffer
        fgets(buffer, sizeof(buffer), file);

        // Assumning the file is in csv format, split the string into name password using the comma
        // as a delimeter
        //accounts->username = strtok(buffer, ",");
        //accounts->password = strtok(NULL, ",");
        printf("%s\n", strtok(buffer, ","));
        printf("%s\n", strtok(NULL, ","));

        // Increment the pointer through the array
        accounts++;
    }

    // Return non zero if all ok 
    return 1;
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

    // We assume that each line in the accounts file is a separate account
    printf("\tlogin: Getting number of registered accounts\n");
    int numAccounts = getNumLines(users);

    // Create an array of account structs of length equal to the number of accounts
    struct account accounts[numAccounts];

    // Loop through the file and add each entry to an element of the array
    printf("\tlogin: Retreiving accounts from file\n");
    loadAccounts(users, (struct account*)&accounts, numAccounts);

    // Print the accounts to see if the above worked
    //int c;
    //for (c = 0; c < numAccounts; c++)
    //{
    //    printf("Username: %s\nPassword: %s\n", accounts[0].username, accounts[1].password);
    //}
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
