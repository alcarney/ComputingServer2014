#include "python_ui.h"

// The new and improved UI handler
int handleUI(int their_socket, int task)
{
    switch (task)
    {
        case 0:
            loginSuccessful(their_socket);
            break;

        case 1:     // Travelling Salesman Algorithm

            // Get the locations from python
//            getLocations(their_socket);
            break;

        default:
            printf("server:python_ui: Error! Invalid task type\n");
            return -1;
    }

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

    // Reset the cursor position to the start of the file
    rewind(file);

    // Return the result
    return i;
}

// Load the accounts from file into the struct provided
int loadAccounts(FILE* file, struct account* accounts, int num)
{
    char buffer[256];
    char test[256];
    int i;

    // Loop through each account in the file and pass it into an appropriate struct
    while(fgets(buffer, 256, file))
    {

        //printf("Buffer is %s", buffer);
        // Assumning the file is in csv format, split the string into name password using the comma
        // as a delimeter
        //printf("\t\tCalculating split\n");
        char* split = strchr(buffer, ',');
        //printf("\t\tSplit is %s", strncpy(test ,buffer,strlen(buffer) - strlen(split)));

        //printf("\t\tSetting username\n");

        // Allocate memory for the username
        accounts->username = malloc(sizeof(char)*128);
        strncpy(accounts->username, buffer, strlen(buffer) - strlen(split));
        //strncat(accounts->username, 1);        // Dont forget the null character


        // Allocate memory for the password
        //printf("\t\tSetting password\n");
        accounts->password = malloc(sizeof(char)*127);
        strcpy(accounts->password, split+1);

        // Increment the pointer through the array
        accounts++;
    }

    // Return non zero if all ok
    return 1;
}

// Login function
int loginSuccessful(int their_socket)
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
    loadAccounts(users, accounts, numAccounts);

    // Create a single instance of the account structure to store the attempt in
    // and allocate the memory
    //struct account attempt;
    //attempt.username = malloc(128);
    //attempt.password = malloc(128);
/*
    char attempt[128];

    // Get the login attempt
    int requestID = 1;                          // Login request
    char* buffer = (char *)&requestID;

    // Send the request
    sendData(their_socket, buffer, sizeof(requestID));

    // Get the answer
    receiveData(their_socket, &attempt, sizeof(attempt));

    printf("Details to check:\n\tUsername:\t%s\n", attempt);
*/

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
