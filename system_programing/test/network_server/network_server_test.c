/******************************************************************************

    Writer: Tal Aharon

    Reviewer: First name and family name.

    Date: 13.08.2023

******************************************************************************/
/*     Internal API      */
#include "network_server.h"
/*****************************************************************************/
int main(void)
{
    np_status_t status = SetUpServer(5000, 10);
    if(NP_SUCCESS != status)
    {
        return (status);
    }

    status = RunServer();
    if(NP_SUCCESS != status)
    {
        return (status);
    }

    return (0);
}
/*****************************************************************************/