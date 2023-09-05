
#define _POSIX_SOURCE
#include <unistd.h>          /* sleep          */
#include <signal.h>          /* kill, pause    */

#include "signal_ping_pong.h" /* Internal API  */

#define TRUE (1)
#define SUCCESS (0)
/*****************************************************************************/
int main(void)
{
    InitProgramSettings();
    while(TRUE)
    {
        pause();
        sleep(1);
        kill(getppid(), SIGUSR2);
    }

    return (SUCCESS);
}
/*****************************************************************************/