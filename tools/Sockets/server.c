// A demo server that broadcasts "hello world!" for all to see

#include "server.h"

void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

// Get the ip address
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

int main(void)
{

    int sockfd, new_fd;                         // Listen on sockfd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;         // Client's connection info
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset (&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;        // Don't care if we use IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    // TCP sockets
    hints.ai_flags = AI_PASSIVE;        // Fill in my IP for me

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // Loop through the results and bind to the first one we can
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        // Make sure we can get a socket file descriptor
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            perror("setsockopt");
            exit(1);
        }

        // Make sure we can bind to the socket
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        // If all the above conditions are satisfied carry on
        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    // Finished with the addresses now
    freeaddrinfo(servinfo);

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler;         // Reap all dead processes?
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    // Main client handling loop
    while(1)
    {
        sin_size = sizeof(their_addr);
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr),
                s, sizeof(s));
        printf("server: new connection from %s\n", s);

        // This is the child process
        if (!fork())
        {
            struct location loc;        // Create a new location structure
            double ack_signal;          // Used to tell python to send the next one
            char* buf = (char*)&loc;    // Cast the pointer into a char 
            char* outbuf = (char*)&ack_signal;

            close(sockfd); // The child doesn't need the listener

            while (1)
            {

                // Read the data into the buffer 
                if (recv(new_fd, buf,24, 0) == -1)
                {
                    perror("recv");
                }

                // Print the data
                printf("Location received\n\tid: %f\n\tx: %f\n\ty: %f\n",loc.id, loc.latitude, loc.longitude);


                // Acknowledge python that we heard it
                if (send(new_fd, outbuf, 8, 0) == -1)
                {
                    perror("send");
                }

                // If we receive end of stream break the loop
                if (loc.id == 0)
                    break;

            }

            // Close the connection
            close(new_fd);
            exit(0);
        }

        close(new_fd);      // Parent doesn't need this now
    }

    return 0;

}
