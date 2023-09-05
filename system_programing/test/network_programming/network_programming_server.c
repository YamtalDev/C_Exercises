#include <stdlib.h>              /* atoi           */
#include <unistd.h>              /* close          */
#include <arpa/inet.h>           /* inet_ntoa      */
#include <stdio.h>               /* puts, prontf   */
#include <string.h>              /* strlen, memset */

#include "network_programming.h" /* Internal API   */
/*****************************************************************************/
np_status_t UDPServer(void);
np_status_t TCPServer(void);
/*****************************************************************************/
int main(int argc, char *argv[])
{
    np_status_t status = NP_SUCCESS;
    if(2 != argc)
    {
        perror("Port number");
        return (NP_FAILURE);
    }

    PORT = atoi(argv[1]);
    status =  UDPServer();
    if(NP_SUCCESS != status)
    {
        return (NP_FAILURE);
    }

    status = TCPServer();
    if(NP_SUCCESS != status)
    {
        return (NP_FAILURE);
    }

    return (NP_SUCCESS);
}
/*****************************************************************************/
np_status_t UDPServer(void)
{
    int sock_fd = 0;
    socklen_t socket_len = 0;
    char buffer[MAX_MSG] = {0};
    np_status_t status = NP_SUCCESS;
    struct sockaddr_in cliaddr, servaddr;

    memset(&cliaddr, 0, SOCK_ADDR_SIZE);
    sock_fd = SetServer(&servaddr, htonl(INADDR_ANY), SOCK_DGRAM);
    if(0 > sock_fd)
    {
        return (NP_SERVER_FAILURE);
    }

    socket_len = SOCK_ADDR_SIZE;
    status = UDPReceiveMessage(&cliaddr, buffer, sock_fd, &socket_len);
    if(NP_SUCCESS != status)
    {
        return (status);
    }

    printf("Client sent: %s\n", buffer);
    status = UPDSendMessage(&cliaddr, sock_fd, socket_len, SERVER);
    if(NP_SUCCESS != status)
    {
        return (status);
    }

    printf("Sending message to client back: %s.", SERVER);
    return (status);
}
/*****************************************************************************/
np_status_t TCPServer(void)
{
    int sock_fd = 0;
    int connect_id = 0;
    socklen_t socket_len = 0;
    np_status_t status = NP_SUCCESS;
    struct sockaddr_in servaddr, cliaddr;

    memset(&cliaddr, 0, SOCK_ADDR_SIZE);
    sock_fd = SetServer(&servaddr, htonl(INADDR_ANY), SOCK_STREAM);
    if(0 > sock_fd)
    {
        return (NP_SERVER_FAILURE);
    }

    printf("Server: listening on port %d.\n", PORT);
    if(0 != listen(sock_fd, BACK_LOG))
    {
        perror("Listen failed");
        return (NP_LISTEN_FAILURE);
    }

    socket_len = sizeof(cliaddr);
    connect_id = accept(sock_fd, (struct sockaddr *)&cliaddr, &socket_len);
    if(connect_id < 0)
    {
        perror("Server accept failed");
        return (NP_ACCEPT_FAILURE);
    }

    status = StartCommunicationSession(connect_id, SERVER);
    if(NP_SUCCESS != status)
    {
        close(sock_fd);
        return (status);
    }

    close(sock_fd);
    return (NP_SUCCESS);
}
/*****************************************************************************/
