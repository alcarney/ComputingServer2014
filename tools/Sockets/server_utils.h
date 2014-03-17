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

struct server_info
{
    int sockfd;          // The address of our socket
};

struct server_info* setup_server();

#endif
