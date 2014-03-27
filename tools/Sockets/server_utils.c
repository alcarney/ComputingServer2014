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
    printf("server-setup: Allocating memory\n");
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;        // Dont mind if we use IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    // TCP sockets
    hints.ai_flags = AI_PASSIVE;        // Fill in my IP address for me - I'm lazy :p

    // Get a linked list of addrinfo structs based on our hints and store it in servinfo 
    printf("server-setup: Getting list of possible local address details\n");
    if (( rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
    {
        // If there was an error exit after printing the error msg
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    printf("server-setup: Choosing an appropriate result\n");
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


/*! Function that reads data from a client into a given location
      \param their_sock - The socket file descriptor of the client
      \param data       - A pointer to where the data will be stored*/
int receiveData(int their_socket, char* data, int data_size)
{
    // Set up the required variables
    int ack = 1;                            // Used to tell python we received the data
    char* ackBuf = (char *)&ack;            // Used by send to get the data from ack

    // Receive the data
    if (recv(their_socket, data, data_size, 0) == -1)
    {
        // Something went wrong
        perror("recv");
        return -1;
    }

    // Else it went fine - let the sender know we got the data
    if (send(their_socket, ackBuf, sizeof(ack), 0) == -1)
    {
        // Something went wrong
        perror("send");
        fprintf(stderr, "Unable to notify client of successful data aquisition\n");
        return -1;
    }

    return 0;
}

/*! Function that sends data to the client
      \param their_sock - The socket file descriptor for the client
      \param data       - A pointer to the data to be sent
*/
int sendData(int their_socket, char* data, int data_size)
{
    // Send the data
    if(send(their_socket, data, data_size, 0) == -1)
    {
        perror("send");
        return -1;
    }

    return 0;
}

/*
int basicHandleClient(int their_socket)
{
        // Create a new child process
        if (!fork())
        {
            printf("Entered handle client function\n");
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
                //printf("New location recevied\n\t\tid: %f\n\t\tx: %f\n\t\ty: %f\n",
                //          loc.id, loc.latitude, loc.longitude);

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
*/
