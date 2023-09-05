#ifndef __NETWORK_PROGRAMMING_H__
#define __NETWORK_PROGRAMMING_H__

#include <stddef.h>     /* size_t, NULL       */
#include <netinet/in.h> /* struct sockaddr_in */

extern in_port_t PORT;
#define BACK_LOG (5)
#define CLIENT ("Client")
#define SERVER ("Server")
#define MAX_MSG (BUFSIZ / sizeof(size_t))
#define SOCK_ADDR_SIZE (sizeof(struct sockaddr_in))

enum np_status
{
    NP_SOCKET_FD_FAILURE = -2,
    NP_BIND_FAILURE,
    NP_SUCCESS,
    NP_FAILURE,
    NP_READ_FAILURE,
    NP_SEND_FAILURE,
    NP_WRITE_FAILURE,
    NP_ACCEPT_FAILURE,
    NP_SERVER_FAILURE,
    NP_LISTEN_FAILURE,
    NP_RECEIVE_FAILURE,
    NP_CONNECT_FAILURE
};

typedef enum np_status np_status_t;
int SetServer(struct sockaddr_in *, uint32_t, int);
void SetServerInfo(struct sockaddr_in *, uint32_t);
np_status_t StartCommunicationSession(int, const char *);
np_status_t UDPReceiveMessage(void *, char *, int, socklen_t *);
np_status_t UPDSendMessage(void *, int, socklen_t, const char *);


#endif /* __NETWORK_PROGRAMMING_H__ */
