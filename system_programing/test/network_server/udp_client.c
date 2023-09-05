#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PORT (5000)
#define MAX_LINE (1024)

int main(void)
{
    int sock_fd = 0;
    char buffer[1024] = {0};
    struct sockaddr_in servaddr;
    const char *message = "UDP message";
    int i = 0, rand_amounts = 0;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(-1 == sock_fd)
    {
        return (1);
    }

    srand(time(NULL));
    rand_amounts = (rand() % 7) + 3;
    printf("UDP Client: Message will be sent %d times\n", rand_amounts); 
    for(; i < rand_amounts; i++)
    {
        if(-1 == sendto(sock_fd, message, MAX_LINE, 0, (struct sockaddr *)&servaddr, sizeof(servaddr)))
        {
            close(sock_fd);
            perror("Send");
            return (1);
        }

        if(-1 == recvfrom(sock_fd, buffer, sizeof(buffer), 0, NULL, NULL))
        {
            close(sock_fd);
            perror("Recv");
            return (1);
        }

        printf("UDP Client: iteration %d of %d. %s received from server\n", i + 1, rand_amounts,buffer);
        bzero(buffer, sizeof(buffer));
        sleep(1);
    }

    close(sock_fd);
    puts("UDP Client: connection closed");
    return 0;
}