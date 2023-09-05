#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>     /* NULL, free*/ 
#include <time.h>

#define PORT 5000
#define MAX_LINE 1000

int main(void)
{
    int sock_fd = 0;
    char buffer[1024] = {0};
    int i = 0, rand_amounts = 0;
    struct sockaddr_in servaddr = {0};
    const char *message = "TCP message";

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sock_fd)
    {
        perror("Socket");
        return (1);
    }

    if(connect(sock_fd,(struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        perror("Connection");
        close(sock_fd);
        return (1);
    }

    srand(time(NULL));
    puts("TCP Client: connected to server");
    rand_amounts = (rand() % 7) + 3;
    printf("TCP Client: Ping will sent %d times\n",rand_amounts); 
    for(i = 0 ; i < rand_amounts; i++)
    {
        if(-1 == write(sock_fd, message, strlen(message)))
        {
            perror("Write");
            close(sock_fd);
            return (1);
        }

        bzero(buffer, sizeof(buffer));
        if(-1 == read(sock_fd, buffer, sizeof(buffer)))
        {
            perror("Read");
            close(sock_fd);
            return (1);
        }

        printf("TCP Client: iteration %d of %d. %s received from server\n", i + 1, rand_amounts, buffer);
        sleep(1);
    }
    
    close(sock_fd);
    puts("TCP Client: connection closed");

    return 0;
}
