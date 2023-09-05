#include <string.h>              /* strlen                        */
#include <unistd.h>              /* close, write, close           */
#include <stdio.h>               /* memsset, perror, printf, puts */
#include "network_programming.h" /* Internal API                  */
/*****************************************************************************/
in_port_t PORT = 8080;
static np_status_t ServerCommunication(int);
static np_status_t ClientCommunication(int);
static np_status_t ReadMessage(int, char *);
static np_status_t WriteMessage(int, char *);
/*****************************************************************************/
void SetServerInfo(struct sockaddr_in *servaddr, uint32_t ip)
{
    memset(servaddr, 0, SOCK_ADDR_SIZE);
    servaddr->sin_port = htons(PORT);
    servaddr->sin_family = AF_INET;
    servaddr->sin_addr.s_addr = ip;
}
/*****************************************************************************/
int SetServer(struct sockaddr_in *servaddr, uint32_t ip, int sock_type)
{
    int sock_fd= 0;
    int set_sock = 0;
    int bind_status = 0;
    int broadcast_enable = 1;
    sock_fd = socket(AF_INET, sock_type, 0);
    if(sock_fd < 0)
    {
        perror("socket creation failed");
        return (NP_SOCKET_FD_FAILURE);
    }

    SetServerInfo(servaddr, ip);
    set_sock = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &broadcast_enable, sizeof(int));
    if(-1 == set_sock)
    {
        perror("setsockopt");
        return (NP_FAILURE);
    }

    bind_status = bind(sock_fd, (const struct sockaddr *)servaddr, SOCK_ADDR_SIZE);
    if(0 > bind_status)
    {
        close(sock_fd);
        perror("bind failed");
        return (NP_BIND_FAILURE);
    }

    return (sock_fd);
}
/*****************************************************************************/
np_status_t UDPReceiveMessage(void *structure, char *buffer, int sock_fd, socklen_t *socket_len)
{
    ssize_t bytes_received = recvfrom(sock_fd, buffer, MAX_MSG, MSG_WAITALL,\
    (struct sockaddr *)structure, socket_len);

    if(0 >= bytes_received)
    {
        close(sock_fd);
        perror("Receive failure");
        return (NP_RECEIVE_FAILURE);
    }

    buffer[bytes_received] = '\0';
    return (NP_SUCCESS);
}
/*****************************************************************************/
np_status_t UPDSendMessage(void *structure, int sock_fd, socklen_t socket_len, const char *msg)
{
    ssize_t bytes_sent = 0;
    bytes_sent = sendto(sock_fd, msg, strlen(msg), MSG_CONFIRM,\
    (const struct sockaddr *)structure, socket_len);

    if(0 >= bytes_sent)
    {
        close(sock_fd);
        perror("Send failure");
        return (NP_SEND_FAILURE);
    }

    return (NP_SUCCESS);
}
/*****************************************************************************/
np_status_t StartCommunicationSession(int sock_fd, const char *communicator)
{
    if(!strcmp(communicator, SERVER))
    {
        return (ServerCommunication(sock_fd));
    }
    else if(!strcmp(communicator, CLIENT))
    {
        return (ClientCommunication(sock_fd));
    }

    return (NP_FAILURE);
}
/*****************************************************************************/
static np_status_t ServerCommunication(int sock_fd)
{
    char buffer[MAX_MSG] = {0};
    for(;;)
    {
        if(NP_SUCCESS != ReadMessage(sock_fd, buffer))
        {
            return (NP_READ_FAILURE);
        }

        printf("\nServer received message: %s\nSend back: ", buffer);
        if(NP_SUCCESS != WriteMessage(sock_fd, buffer))
        {
            return (NP_WRITE_FAILURE);
        }

        if(strncmp("exit", buffer, 4) == 0)
        {
            puts("Server: exit");
            break;
        }
    }

    return (NP_SUCCESS);
}
/*****************************************************************************/
static np_status_t ClientCommunication(int sock_fd)
{
    char buffer[MAX_MSG] = {0};
    for(;;)
    {
        printf("\nSend: ");
        if(NP_SUCCESS != WriteMessage(sock_fd, buffer))
        {
            return (NP_WRITE_FAILURE);
        }

        if(NP_SUCCESS != ReadMessage(sock_fd, buffer))
        {
            return (NP_READ_FAILURE);
        }

        printf("\nClient received message: %s", buffer);
        if(strncmp("exit", buffer, 4) == 0)
        {
            puts("Client: exit");
            break;
        }
    }

    return (NP_SUCCESS);
}
/*****************************************************************************/
static np_status_t WriteMessage(int sock_fd, char *buffer)
{
    int n = 0;
    ssize_t bytes = 0;
    memset(buffer, 0, MAX_MSG);
    while((buffer[n++] = getchar()) != '\n');
    bytes = write(sock_fd, buffer, MAX_MSG);
    if(0 >= bytes)
    {
        return (NP_WRITE_FAILURE);
    }

    return (NP_SUCCESS);
}
/*****************************************************************************/
static np_status_t ReadMessage(int sock_fd, char *buffer)
{
    ssize_t bytes = 0;
    memset(buffer, 0, MAX_MSG);
    bytes = read(sock_fd, buffer, MAX_MSG);
    if(0 >= bytes)
    {
        return (NP_READ_FAILURE);
    }

    return (NP_SUCCESS);
}
/*****************************************************************************/

