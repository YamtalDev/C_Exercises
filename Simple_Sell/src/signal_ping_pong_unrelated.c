#define _POSIX_SOURCE
#include <stdio.h>     /* puts                                                */
#include <time.h>      /* time                                                */
#include <string.h>    /*                                                      */                                          
#include <sys/types.h> /* pid_t                                               */
#include <unistd.h>    /* fork, execvp, sleep                                 */
#include <sys/wait.h>  /* wait, WEXITSTATUS, WTERMSIG                         */
#include <signal.h>    /* SIGUSR1, SIGUSR2, sigaction, kill, pause, sigaction */
#include <stdlib.h>

#define TRUE (1)
#define SUCCESS (0)
#define FAILURE (1)
static void pongHandler(int sig);
int main(int argc, char *argv[])
{
    pid_t sender_pid = atoi(argv[1]);
    struct sigaction handler = {0};
    handler.sa_flags = 0;
    handler.sa_handler = pongHandler;
    sigemptyset(&handler.sa_mask);
    sigaction(SIGUSR2, &handler, NULL);

    if(2 != argc)
    {
        return (FAILURE);
    }

    while(TRUE)
    {
        sleep(1);
        kill(sender_pid, SIGUSR2);
        pause();
    }

    return (SUCCESS);
}

static void pongHandler(int sig)
{
    (void)sig;
    puts("pong");
}