#include "server_utils.h"


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

    // Used to keep info about clients
    //struct sockaddr_storage their_addr;

    // ?
    //socklen_t sin_size;

    // ? 
    //struct sigaction sa;

    // ?
    int yes = 1;

    // I think this is where the IP address is stored?
    //char s[INET6_ADDRSTRLEN];

    // Used to catch the retrun value of getaddrinfo and retrieve the appropriate
    // error message if somethin should go wrong
    int rv;

    // Allocate the memory for the hints struct and load in our parameters
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;        // Dont mind if we use IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    // TCP sockets
    hints.ai_flags = AI_PASSIVE;        // Fill in my IP address for me - I'm lazy :p

    // Get a linked list of addrinfo structs based on our hints and store it in servinfo
    if (( rv = getaddrinfo(NULL, portNum, &hints, &servinfo)) != 0)
    {
        // If there was an error exit after printing the error msg
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

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
        if (setsocketopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
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
