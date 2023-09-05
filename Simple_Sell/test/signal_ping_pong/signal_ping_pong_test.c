#include <stdio.h>            /* puts         */
#include <signal.h> 
#include "signal_ping_pong.h" /* Internal API */

#define SUCCESS (0)
/*****************************************************************************/
int main(void)
{
    int status = SUCCESS;
/*     status = ProcPingPong(); */
/*     status = ProcPingPongTwo(); */
    status = ProcPingPongUnrelated();
    return (status);
}
/*****************************************************************************/
