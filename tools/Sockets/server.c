#include "server_utils.h"



// Run the server through the specified socket
int run_server(int sock)
{

    // --- Initialse variables ---

    // Socket file descriptor for client
    int their_socket;

    // Used to keep info about clients
    struct sockaddr_storage their_addr;

    // Used to state the size of the ip addr?
    socklen_t sin_size;
    sin_size = sizeof(their_addr);

    // Some form of event handler? 
    struct sigaction sa;

    // I think this is where the IP address is stored
    char s[INET6_ADDRSTRLEN];

    // This next section has something to do with killing of the child procesess this 
    // function will create later.
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }


    // --- Server Start ---
    printf("server: Successfully started, waiting for clients...\n");

    // Listen for a connection request
    if (listen(sock, 10) == -1)       // 10 denotes how many pending connections to leave in a queue
    {
        // If something goes wrong report the error and exit
        perror("listen");
        return 1;
    }


    // Main client handling loop - consider implementing function pointers to allow
    // custom server behavoirs and easier maintainability
    while(1)
    {

        // Accept the connection, i think the arguments are as follows:
        //      socket - the file descrptor for the socket our server will use
        //      (struct sockaddr*)&their_addr - I think the client's info gets put here
        //      &sin_size - I think this lets c know how many bytes to write into the previous
        //      argument
        their_socket = accept(sock, (struct sockaddr *)&their_addr, &sin_size);

        // Check to make sure the previous step was successful
        if (their_socket == -1)
        {
            // If not throw the error and skip to next connection request
            perror("accept");
            continue;
        }

        // Convert their ip address from network byte order to host byte order
        //      their_addr.ss_family                       - IPv4 or IPv6
        //      get_in_addr((struct sockaddr*)&their_addr) - use the function thats defined elsewhere
        //                                                   to get the ip address, can handle both
        //                                                   IPv4 and IPv6
        //      s                                          - Variable to store the resulting string in
        //      sizeof(s)                                  - How many bytes to write
        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr),
                        s, sizeof(s));

        // Say that we have a new connection from ip X
        printf("server: New connection from %s\n", s);

        // Get the client to identify itself so we know which handler to call - Eventually
        int clientType;
        char* buf = (char *)&clientType;            // Create a buffer to read the data

        receiveData(their_socket, buf, sizeof(clientType));

        // Choose appropriate action based on client type
        switch (clientType)
        {
            case UI:
                    printf("User Interface client, preparing handler\n");
                    //basicHandleClient(their_socket);
                    handleUI(their_socket);
                    break;

            case APP:
                    printf("Sorry this client isn't supported yet...\n");
                    break;

            default:
                    fprintf(stderr, "Unable to identify client, ignoring...\n");
                    break;
        }
        printf("Carrying on\n");

        // Close the main parent's connection
        close(their_socket);
    }

    return 0;
}

/*
int main()
{
    int sock = new_socket(3490);
    int rv = run_server(sock);

    return 0;
}
*/
