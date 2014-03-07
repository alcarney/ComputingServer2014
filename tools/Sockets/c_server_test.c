// A test file to see if we can get cpp to use sockets
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main (int argc, char *argv[])
{
    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // First call to socket() function
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
       perror("Error!: Unable to open socket!\n");
        exit(1);
    }

    // Initialise socket structure
    bzero((char* ) &serv_addr, sizeof(serv_addr));
    portno = 50007;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // Now bind the host address using bind()
    if (bin(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error!: Unable to bind socket\n");
        exit(1);
    }

    // Now start listening for clients, here process will go to sleep
    // and wait for an incoming connection
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // Accept connection from client
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
    {
        perror("Error!: Unable to accept connection\n");
        exit(1);
    }

    // If connection is established then start communicating
    bzero(buffer, 256);
    n = read(newsockfd,buffer,256);

    if (n < 0)
    {
        perror("Error!: Unable to read from socket\n");
        exit(1);
    }
    printf("Here is the message: %s\n", buffer);

    // Write a response for the client
    n = write(newsockfd, "I got your message", 18);
    if (n < 0)
    {
        perror("Unable to write to socket");
        exit(1);
    }
    return 0;
}
