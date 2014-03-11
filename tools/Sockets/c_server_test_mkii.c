#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main (int argc, char *argv[])
{
    int listenfd =0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1025];
    time_t ticks;

    // Create an unanmed socket, returns an integer called a socket descriptor
    //      AF_INET     - Use IPv4 Addresses
    //      SOCK_STREAM - Specifies the protocol to use for communications needs to be reliable
    //                    and have capacity for acknowledgement e.g. handshaking
    //      0           - Let the kernel decide to use its default protocol, for connections of 
    //                    the type we specified this will be TCP
    //
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // As far as I know these steps are to allocate memory for the strcuture and the buffer
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;                 // Family (IPv4)
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // Which interface to listen from e.g. lo,wlan0,eth0
    serv_addr.sin_port = htons(5000);               // Which porthole to listen from

    // Assign the details specified above in the serv_addr structure to the socket we created 
    bind(listenfd, (struct sockaddr* )&serv_addr, sizeof(serv_addr));

    // Specify the socket to listen with, 10 specifies the number of client connections we should allow
    listen(listenfd, 10);

    while(1)
    {
        // Server goes to sleep when this is called and waits for a complete TCP handshake
        // when complete it returns with the client's details
        connfd = accept(listenfd, (struct sockaddr* )NULL, NULL);

        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));

        // We then write the current date to the client's socket and disconnect
        write(connfd, sendBuff, strlen(sendBuff));

        close(connfd);
        sleep(1);
    }
}
