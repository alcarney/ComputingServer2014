#ifndef SERVER_UTILS_C
#define SERVER_UTILS_C

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT "3490"     // The port we will be using
#define BACKLOG 10      // How many pending connections the queue will allow

struct location
{
    double id;
    double latitude;
    double longitude;
};


int new_socket(int portNum);                // Get a new socket on port number x
int run_server(int socket);                 // Run the server through the given socket
void *get_in_addr(struct sockaddr *sa);     // Get the ip address from a struct (is this what an 
                                            //  inline function looks like in C?)
void sigchld_handler(int s);                // Something to do with killing off child processes...

#endif
