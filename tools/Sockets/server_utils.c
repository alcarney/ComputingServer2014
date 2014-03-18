#include "server_utils.h"


// Something to do with the child processes in run_server
void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

// Get the IP address from the given struct - helps make the code
// below IP version agnostic
void *get_in_addr(struct sockaddr *sa)
{
    // If IPv4
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    // Else IPv6 
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// This sets up a new socket on the specified port num so that we're 
// ready to send/receive data returns the socket file descriptor that is used 
// to communicate with the loopback interface - Hopefully that's all we need 
// for this to work
int new_socket(int portNum)
{
    // Initialise all the variables that we need
    int sock_fd;        // Socket file descriptor, this is our gateway to the network

    // 3 addrinfo structs
    //      hints       - Used to help getaddrinfo find the correct details for our needs
    //      servinfo    - The head of a linked list of addrinfos returned by getaddrinfo
    //      p           - Used to walk through the linked list mentioned above and to find the 
    //                    correct details
    struct addrinfo hints, *servinfo, *p;

    // Something to do with setsocketopt
    int yes = 1;

    // Used to catch the retrun value of getaddrinfo and retrieve the appropriate
    // error message if somethin should go wrong
    int rv;

    // Allocate the memory for the hints struct and load in our parameters
    printf("Allocating memory...\n");
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;        // Dont mind if we use IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    // TCP sockets
    hints.ai_flags = AI_PASSIVE;        // Fill in my IP address for me - I'm lazy :p

    // Get a linked list of addrinfo structs based on our hints and store it in servinfo 
    printf("Getting addr info...\n");
    if (( rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
    {
        // If there was an error exit after printing the error msg
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    printf("Looping through list...\n");
    // Loop through the linked list and bind to the first appropriate result
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        // Make sure we can get a socket file descriptor 
        if ((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            // If not report the error and skip to the next item in the list
            perror("server: socket");
            continue;
        }

        // ? 
        if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            // If not report the error and quit
            perror("setsockopt");
            exit(1);
        }

        // Bind the socket to the port on the computer
        if (bind(sock_fd, p->ai_addr, p->ai_addrlen) == -1)
        {
            // If we can't scrap everything and go to the next item in the list
            close(sock_fd);
            perror("server: bind");
            continue;
        }

        // If we have got this far then everything has gone well and we don't need this loop 
        // anymore
        break;
    }

    // Check to make sure the previous loop returned something useful
    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    // We don't need the linked list of addrinfos now
    freeaddrinfo(servinfo);

    // Return the socket file descriptor
    return sock_fd;
}

// Run the server through the specified socket
int run_server(int sock)
{

    // --- Initialse variables ---

    // Socket file descriptor for client
    int their_socket;

    // Used to keep info about clients
    struct sockaddr_storage their_addr;

    // ?
    socklen_t sin_size;

    // ? 
    struct sigaction sa;

    // I think this is where the IP address is stored?
    char s[INET6_ADDRSTRLEN];

    // --- Server Start ---

    // Listen for a connection request
    if (listen(sock, 10) == -1)       // 10 denotes how many pending connections to leave in a queue
    {
        // If something goes wrong report the error and exit
        perror("listen");
        return 1;
    }

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

    printf("server: Successfully started, waiting for clients...\n");

    // Main client handling loop - consider implementing function pointers to allow
    // custom server behavoirs and easier maintainability
    // E.g handlerClients() function pointer passed as argument
    while(1)
    {
        sin_size = sizeof(their_addr);

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
        printf("server: New connection from %s", s);

        // Get the client to identify itself so we know which handler to call - Eventually
        int clientType;
        char* buf = (char *)&clientType;            // Create a buffer to read the data

        if (recv(their_socket, buf, sizeof(loc), 0) == -1)
        {
            // If something went wrong, report and skip to the next client
            perror("recv");
            printf("Unable to identify client ignoring\n");
            continue;
        }

        // Choose appropriate action based on client type
        switch (clientType)
        {
            case UI:
                    printf("User Interface client, preparing handler\n");
                    basicHandleClient(their_socket);
                    break;

            case APP:
                    printf("Sorry this client isn't supported yet...\n");
                    break;

            default:
                    fprintf(stderr, "Unable to identify client, ignoring...\n");
                    break;
        }

        // Close the main parent's connection
        close(their_socket);
    }

    return 0;
}

int basicHandleClient(int their_socket)
{
        // Create a new child process
        if (!fork())
        {
            struct location loc;                // Used to store the incoming data
            int ack_signal = 1;             // Used to tell python to send the next bit of data
            char* buf = (char*)&loc;            // Data comes in through this variable, it points
                                                // to the location of loc in memory
            char* outbuf = (char *)&ack_signal; // Point the outward buffer at what is stored in 
                                                // ack_signal

            //close(sock);                      // For some reason we can do this??

            // Loop through the incoming data
            while (1)
            {
                // Read the data (client->buf->loc)
                if (recv(their_socket, buf, sizeof(loc), 0) == -1)
                {
                    // If it goes wrong
                    perror("recv");
                }

                // Print the data we receive
                printf("New location recevied\n\t\tid: %f\n\t\tx: %f\n\t\ty: %f\n",
                            loc.id, loc.latitude, loc.longitude);

                // Acknowledge
                if (send(their_socket, outbuf, sizeof(ack_signal), 0) == -1)
                {
                    // If it goes wrong
                    perror("send");

                    // If we receive end of stream [(0,0,0)] break the loop
                    if (loc.id == 0 && loc.longitude == 0 && loc.latitude == 0)
                    {
                        printf("EOS Reached: Closing current connection\n");
                        break;
                    }
                }
            }

            // Close the child's connection to the client
            close(their_socket);

            // Quit the child process
            exit(0);

        }
}
