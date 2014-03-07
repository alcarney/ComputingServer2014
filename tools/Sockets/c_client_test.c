// C client test

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);

    // Create a socket point
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("Error: Unable to open socket\n");
        exit(1);
    }

    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "Error: No such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
            server->h_length);
    serv_addr.sin_port = htons(portno);

    // Now connect to the server
    if (connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error!: Unable to connect\n");
        exit(1);
    }

    // Now ask for a msg from the user which will be sent to the server
    printf("Please enter a message\n> ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);

    // Send the message to the server
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("Error!: Unable to write to socket\n");
        exit(1);
    }

    // Now read the server response
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    
    if (n < 0)
    {
        perror("Error: Unable to read from socket");
        exit(1);
    }
    printf("%s\n", buffer);
    return 0;
}
