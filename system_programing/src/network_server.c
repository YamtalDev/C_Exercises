#define _POSIX_C_SOURCE (200112L)
/******************************************************************************

    Writer: Tal Aharon

    Reviewer: First name and family name.

    Date: 13.08.2023

*******************************************************************************

                          Description:

  

******************************************************************************/
#include <stdlib.h>                         /* system                        */
#include <stddef.h>                        /* size_t, NULL                  */
#include <string.h>                       /* strlen, memset                */
#include <unistd.h>                      /* close, write, close           */
#include <stdio.h>                      /* perror, printf, puts          */
#include <sys/select.h>                /* select, tumeval, fd_set       */

#include "network_server.h"          /* Internal API                  */
/************************************************************************/
static int udp = 0, tcp = 0;
typedef struct sockaddr sa_t;
typedef struct sockaddr_in sa_in_t;
static struct timeval interval = {7, 0};
/************************************************************************/
#define RUNNING (1)
#define STOP_RUNNING (0)
#define ADDR_SIZE (sizeof(sa_in_t))
#define FD_MAX(a, b) (a > b ? a : b)
#define MAX_MSG (BUFSIZ / sizeof(size_t))
/************************************************************************/
static void LogServer(void);
static void SetFDs(fd_set *rset);
static void PrintServerInfo(void);
static void ClearFDs(fd_set *rset);
static int SetServer(sa_in_t *, int);
static np_status_t InputRequest(void);
static np_status_t SelectFd(int max_fd, fd_set *rset);
static void CleanUpServer(int *clients_fd, size_t size);
static int GetFd(int *clients_fd, size_t size, fd_set *rset);
static void SetSocketInfo(sa_in_t *servaddr, in_port_t port);
static np_status_t HandleTCPRequest(char *buffer, int client_fd);
static np_status_t HandleUDPRequest(char *buffer, sa_in_t *client, socklen_t *adder_size);
/*****************************************************************************/
np_status_t SetUpServer(in_port_t port, int back_log)
{
    FILE *file = NULL;
    sa_in_t servaddr;
    file = fopen(".server_log", "w");
    if(file == NULL)
    {
        perror("Log file");
        return (NP_FAILURE);
    }

    SetSocketInfo(&servaddr, port);
    tcp = SetServer(&servaddr, SOCK_STREAM);
    if(0 > tcp)
    {
        return (NP_SERVER_FAILURE);
    }

    if(0 != listen(tcp, back_log))
    {
        close(tcp);
        perror("Listen");
        return (NP_LISTEN_FAILURE);
    }

    udp = SetServer(&servaddr, SOCK_DGRAM);
    if(0 > udp)
    {
        close(tcp);
        return (NP_SERVER_FAILURE);
    }

    fclose(file);
    printf("\nServer: listening on port %d.\n", port);
    return (NP_SUCCESS);
}
/************************************************************************/
static int SetServer(sa_in_t *servaddr, int sock_type)
{
    int bind_status = 0, server_socket = 0;
    server_socket = socket(AF_INET, sock_type, 0);
    if(server_socket < 0)
    {
        perror("Socket");
        return (NP_SOCKET_FD_FAILURE);
    }

    bind_status = bind(server_socket, (const sa_t *)servaddr, ADDR_SIZE);
    if(0 > bind_status)
    {
        perror("Bind");
        close(server_socket);
        return (NP_BIND_FAILURE);
    }

    return (server_socket);
}
/*****************************************************************************/
static void SetSocketInfo(sa_in_t *servaddr, in_port_t port)
{
    memset(servaddr, 0, ADDR_SIZE);
    servaddr->sin_family = AF_INET;
    servaddr->sin_port = htons(port);
    servaddr->sin_addr.s_addr = htonl(INADDR_ANY);
}
/*****************************************************************************/
np_status_t RunServer(void)
{
    fd_set rset;
    sa_in_t client;
    const char *server_msg = "server$ ";
    size_t i = 0, size = 0;
    char buffer[MAX_MSG] = {0};
    int clients_fd[1021] = {0};
    np_status_t status = NP_SUCCESS;
    int server_is_running = RUNNING;
    socklen_t adder_size = ADDR_SIZE;
    int max_fd = 0, tcp_client_fd = 0;

    memset(&client, 0, ADDR_SIZE);
    puts("Server is up & running");
    while(SetFDs(&rset), server_is_running)
    {
        interval.tv_sec = 7;
        interval.tv_usec = 0;
        max_fd = GetFd(clients_fd, size, &rset);
        status = SelectFd(max_fd, &rset);
        if(NP_SUCCESS != status)
        {
            server_is_running = STOP_RUNNING;
            break;
        }

        /*write(STDIN_FILENO, server_msg, strlen(server_msg));*/
        if(FD_ISSET(tcp, &rset))
        {
            tcp_client_fd = accept(tcp, (sa_t *)&client, &adder_size);
            if(-1 == tcp_client_fd)
            {
                server_is_running = STOP_RUNNING;
                status = NP_SOCKET_FD_FAILURE;
                perror("Accept");
                break;
            }

            clients_fd[size++] = tcp_client_fd;
        }

        if(FD_ISSET(udp, &rset))
        {
            status = HandleUDPRequest(buffer, &client, &adder_size);
            if(NP_SUCCESS != status)
            {
                server_is_running = STOP_RUNNING;
                perror("Server udp");
                break;
            }
        }

        for(i = 0; i < size; i++)
        {
            if(FD_ISSET(clients_fd[i], &rset))
            {
                if(NP_SUCCESS != HandleTCPRequest(buffer, clients_fd[i]))
                {
                    close(clients_fd[i]);
                    clients_fd[i] = clients_fd[size - 1];
                    --size;
                }
            }
        }

        if(FD_ISSET(STDIN_FILENO, &rset))
        {
            if(NP_SUCCESS != InputRequest())
            {
                server_is_running = STOP_RUNNING;
                break;
            }
        }

        memset(buffer, 0, MAX_MSG);
        ClearFDs(&rset);
    }

    CleanUpServer(clients_fd, size);
    return (status);
}
/*****************************************************************************/
static void LogServer(void)
{
    FILE *log_file = fopen(".server_log", "a");
    if(log_file)
    {
        fprintf(log_file, "No activity in server\n");
        fclose(log_file);
    }
}
/*****************************************************************************/
static void CleanUpServer(int *clients_fd, size_t size)
{
    size_t i = 0;
    for(; i < size; ++i)
    {
        close(clients_fd[i]);
    }

    close(udp);
    close(tcp);
    close(STDIN_FILENO);
}
/*****************************************************************************/
static np_status_t SelectFd(int max_fd, fd_set *rset)
{
    int sockets_ready = select(max_fd + 1, rset, NULL, NULL, &interval);
    if(-1 == sockets_ready)
    {
        return (NP_SERVER_FAILURE);
        perror("Select");
    }
    else if(0 == sockets_ready)
    {
        LogServer();
    }

    return (NP_SUCCESS);
}
/*****************************************************************************/
static int GetFd(int *clients_fd, size_t size, fd_set *rset)
{
    size_t i = 0;
    int max_fd = FD_MAX(tcp, udp);
    for(i = 0; i < size; i++)
    {
        FD_SET(clients_fd[i], rset);
        max_fd = FD_MAX(max_fd,  clients_fd[i]);
    }

    return (max_fd);
}
/*****************************************************************************/
static void SetFDs(fd_set *rset)
{
    FD_ZERO(rset);
    FD_SET(tcp, rset);
    FD_SET(udp, rset);
    FD_SET(STDIN_FILENO, rset);
}
/*****************************************************************************/
static void ClearFDs(fd_set *rset)
{
    FD_CLR(udp, rset);
    FD_CLR(tcp, rset);
    FD_CLR(STDIN_FILENO, rset);
}
/*****************************************************************************/
static np_status_t HandleUDPRequest(char *buffer, sa_in_t *client, socklen_t *adder_size)
{
    ssize_t bytes_sent = 0;
    ssize_t bytes_received = 0;
    char *msg = "Server UDP confirmation";
    bytes_received = recvfrom(udp, buffer, MAX_MSG, MSG_WAITALL, (sa_t *)client, adder_size);
    if(0 >= bytes_received)
    {
        perror("Receive");
        return (NP_RECEIVE_FAILURE);
    }

    buffer[bytes_received] = '\0';
    printf("UDP Client: %s\n", buffer);
    bytes_sent = sendto(udp, msg, strlen(msg), MSG_CONFIRM, (const sa_t *)client, *adder_size);
    if(0 >= bytes_sent)
    {
        perror("Send");
        return (NP_SEND_FAILURE);
    }

    return (NP_SUCCESS);
}
/*****************************************************************************/
static np_status_t HandleTCPRequest(char *buffer, int client_fd)
{
    ssize_t bytes_sent = 0;
    ssize_t bytes_received = 0;
    np_status_t status = NP_SUCCESS;
    char *msg = "Server TCP confirmation";
    bytes_received = recv(client_fd, buffer, MAX_MSG, 0);
    if(bytes_received <= 0)
    {
        return (NP_RECEIVE_FAILURE);
    }

    buffer[bytes_received] = '\0';
    printf("TCP client: %s\n", buffer);
    bytes_sent = send(client_fd, msg, strlen(msg), 0);
    if(bytes_sent <= 0)
    {
        perror("Send");
        return (NP_SEND_FAILURE);
    }

    return (status);
}
/*****************************************************************************/
static np_status_t InputRequest(void)
{
    int exit_status = 0;
    char buffer[MAX_MSG] = {0};
    ssize_t bytes = read(STDIN_FILENO, buffer, MAX_MSG);
    if(-1 == bytes)
    {
        perror("Server read");
        return (NP_READ_FAILURE);
    }

    if(0 == strcmp(buffer, "quit\n"))
    {
        puts("Server: Shut Down");
        return (NP_QUITE);
    }

    if(0 == strcmp(buffer, "info\n"))
    {
        PrintServerInfo();
    }
    else
    {
        exit_status = system(buffer);
        /* Handle exit status */
    }

    return (NP_SUCCESS);
}
/*****************************************************************************/
static void PrintServerInfo(void)
{
    return;
}
/*****************************************************************************/
