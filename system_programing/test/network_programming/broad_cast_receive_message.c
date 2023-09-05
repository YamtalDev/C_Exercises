#include <unistd.h>              /* close          */
#include <stdlib.h>              /* system         */
#include <stdio.h>               /* puts, prontf   */
#include <string.h>              /* strlen, memset */

#include "network_programming.h" /* Internal API   */
/*****************************************************************************/
int main(void)
{
    int sock_fd = 0;
    int set_sock = 0;
    int broadcast_enable = 1;
    socklen_t socket_len = 0;
    char buffer[MAX_MSG] = {0};
    np_status_t status = NP_SUCCESS;
    struct sockaddr_in servaddr, cliaddr;

    sock_fd = SetServer(&servaddr, htonl(INADDR_ANY), SOCK_DGRAM);
    if(0 > sock_fd)
    {
        return (NP_SERVER_FAILURE);
    }

    set_sock = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &broadcast_enable, sizeof(int));
    if(-1 == set_sock)
    {
        perror("setsockopt SO_BROADCAST");
        return (NP_FAILURE);
    }

    socket_len = SOCK_ADDR_SIZE;
    status = UDPReceiveMessage(&cliaddr, buffer, sock_fd, &socket_len);
    if(NP_SUCCESS != status)
    {
        return (status);
    }

    puts(buffer);
    status = UPDSendMessage(&cliaddr, sock_fd, socket_len, "Ok");
    if(NP_SUCCESS != status)
    {
        return (status);
    }

    close(sock_fd);
    return (status);
}