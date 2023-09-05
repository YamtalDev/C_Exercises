#ifndef __NETWORK_SERVER_H__
#define __NETWORK_SERVER_H__

typedef enum np_status
{
    NP_SOCKET_FD_FAILURE = -10,
    NP_BIND_FAILURE, NP_READ_FAILURE,
    NP_SEND_FAILURE, NP_WRITE_FAILURE,
    NP_ACCEPT_FAILURE, NP_SERVER_FAILURE,
    NP_LISTEN_FAILURE, NP_RECEIVE_FAILURE,
    NP_CONNECT_FAILURE, NP_SUCCESS, NP_FAILURE, NP_QUITE
} np_status_t;

/* in_port_t */
#include <arpa/inet.h>
np_status_t SetUpServer(in_port_t port, int back_log);

np_status_t RunServer(void);

#endif /* __NETWORK_SERVER_H__ */




