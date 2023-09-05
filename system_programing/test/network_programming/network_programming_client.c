#include <unistd.h>              /* close          */
#include <arpa/inet.h>           /* inet_addr      */
#include <stdio.h>               /* puts, printf   */
#include <string.h>              /* strlen, memset */

#include "network_programming.h" /* Internal API   */
/*****************************************************************************/
np_status_t UDPClient(void);
np_status_t TCPClient(void);
np_status_t BroadCast(void);
/*****************************************************************************/
int main(void)
{
    np_status_t status = NP_SUCCESS;
    status = UDPClient();
    if(NP_SUCCESS != status)
    {
        return (NP_FAILURE);
    }

    status = TCPClient();
    if(NP_SUCCESS != status)
    {
        return (NP_FAILURE);
    }

    status = BroadCast();
    if(NP_SUCCESS != status)
    {
        return (NP_FAILURE);
    }

    return (NP_SUCCESS);
}
/*****************************************************************************/
np_status_t UDPClient(void)
{
    int sock_fd = 0;
    char buffer[MAX_MSG] = {0};
    struct sockaddr_in servaddr;
    np_status_t status = NP_SUCCESS;
    socklen_t socket_len = SOCK_ADDR_SIZE;

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_fd < 0)
    {
        perror("socket creation failed");
        return (NP_SOCKET_FD_FAILURE);
    }

    SetServerInfo(&servaddr, htonl(INADDR_ANY));
    status = UPDSendMessage(&servaddr, sock_fd, socket_len, CLIENT);
    if(NP_SUCCESS != status)
    {
        return (status);
    }

    printf("Client sending message: %s.\n", CLIENT);
    status = UDPReceiveMessage(&servaddr, buffer, sock_fd, &socket_len);
    if(NP_SUCCESS != status)
    {
        return (status);
    }

    printf("Server responded back: %s\n", buffer);

    close(sock_fd);
    return (status);
}
/*****************************************************************************/
np_status_t TCPClient(void)
{
    int sock_fd = 0;
    struct sockaddr_in servaddr;
    SetServerInfo(&servaddr, inet_addr("127.0.0.1"));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0)
    {
        perror("socket creation failed");
        return (NP_SOCKET_FD_FAILURE);
    }

    if(0 != connect(sock_fd, (struct sockaddr *)&servaddr, SOCK_ADDR_SIZE))
    {
        close(sock_fd);
        perror("Connection with server failed");
        return (NP_CONNECT_FAILURE);
    }

    StartCommunicationSession(sock_fd, CLIENT);
    close(sock_fd);
    return (NP_SUCCESS);
}
/*****************************************************************************/
np_status_t BroadCast(void)
{
    int sock_fd = 0;
    int set_sock = 0;
    int broadcast = 1;
    char buffer[1024] = {0};
    struct sockaddr_in servaddr;
    np_status_t status = NP_SUCCESS;
    socklen_t socket_len = SOCK_ADDR_SIZE;
    const char *message = "Hello, Im going to destroy your computer in 5 seconds!";

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(0 > sock_fd)
    {
        perror("Socket failed");
        return (NP_SOCKET_FD_FAILURE);
    }

    set_sock = setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));
    if(-1 == set_sock)
    {
        perror("setsockopt SO_BROADCAST");
        return (NP_FAILURE);
    }

    SetServerInfo(&servaddr, INADDR_BROADCAST);
    status = UPDSendMessage(&servaddr, sock_fd, SOCK_ADDR_SIZE ,message);
    if(NP_SUCCESS != status)
    {
        return (status);
    }

    status = UDPReceiveMessage(&servaddr, buffer, sock_fd, &socket_len);
    if(NP_SUCCESS != status)
    {
        return (status);
    }
    else
    {
        printf("Received: %s from %s\n", buffer, inet_ntoa(servaddr.sin_addr));
    }

    close(sock_fd);
    return (NP_SUCCESS);
}
/*****************************************************************************/
