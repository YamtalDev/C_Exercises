/******************************************************************************

    Writer: Tal Aharon

    Reviewer: No one.

    Date: 29.05.2023

******************************************************************************/
#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>     /* puts                                                */
#include <time.h>      /* time                                                */
#include <string.h>    /**/                                          
#include <sys/types.h> /* pid_t                                               */
#include <unistd.h>    /* fork, execvp, sleep                                 */
#include <sys/wait.h>  /* wait, WEXITSTATUS, WTERMSIG                         */
#include <signal.h>    /* SIGUSR1, SIGUSR2, sigaction, kill, pause, sigaction */

#include "signal_ping_pong.h" /* Internal API  */
/*****************************************************************************/
#define TRUE (1)
#define RUN_TIME_PROC (5)
static void ChildProc(void);
static void ParentProc(pid_t child);
static volatile int signal_pid = -1;
static void HandleReturnStatus(int status);
static void SignalGetPid(int sig, siginfo_t *info, void *context);
/*****************************************************************************/
status_t ProcPingPong(void)
{
    time_t start = 0;
    int proc_status = 0;
    pid_t child_process = 0;
    status_t status = SUCCESS;

    start = time(NULL);
    InitProgramSettings();
    child_process = fork();
    if(0 > child_process)
    {
        status = FAILURE;
    }

    while((time(NULL) - start) < RUN_TIME_PROC)
    {
        if(!child_process)
        {
            ChildProc();
        }
        else
        {
            ParentProc(child_process);
        }
    }

    if(child_process)
    {
        wait(&proc_status);
        HandleReturnStatus(proc_status);
    }

    return (status);
}
/*****************************************************************************/ 
status_t ProcPingPongTwo(void)
{
    time_t start = 0;
    int proc_status = 0;
    pid_t child_process = 0;
    status_t status = SUCCESS;
    char *args[] = {"../../bin/executables/pong", NULL};

    start = time(NULL);
    InitProgramSettings();
    child_process = fork();
    if(0 > child_process)
    {
        status = FAILURE;
    }

    while((time(NULL) - start) < RUN_TIME_PROC)
    {
        if(!child_process)
        {
            execvp(args[0], args);
        }
        else
        {
            ParentProc(child_process);
        }
    }

    kill(child_process, SIGTERM);
    if(child_process)
    {
        wait(&proc_status);
        HandleReturnStatus(proc_status);
    }

    return (status);
}
/*****************************************************************************/
status_t ProcPingPongUnrelated(void)
{
    struct sigaction handler = {0};
    printf("\nPid of the sender ping: %d ", getpid());
    handler.sa_flags = SA_SIGINFO;
    handler.sa_sigaction = SignalGetPid;
    sigaction(SIGUSR2, &handler, NULL);

    sleep(20);
    while(TRUE)
    {
        sleep(1);
        kill(signal_pid, SIGUSR1);
        pause();
    }

    return (SUCCESS);
}
/*****************************************************************************/
void InitProgramSettings(void)
{
    struct sigaction handler = {0};
    handler.sa_flags = 0;
    handler.sa_handler = SignalHandler;
    sigaction(SIGUSR1, &handler, NULL);
    sigaction(SIGUSR2, &handler, NULL);
}
/*****************************************************************************/
void SignalHandler(int sig)
{
    if(SIGUSR1 == sig)
    {
        puts("Ping");
    }
    else if(SIGUSR2 == sig)
    {
        puts("Pong");
    }
}
/*****************************************************************************/ 
static void SignalGetPid(int sig, siginfo_t *info, void *context)
{
    (void)sig;
    (void)context;
    signal_pid = info->si_pid;
    write(1, "\nping", 5);
}
/*****************************************************************************/ 
static void ChildProc(void)
{
    pause();
    sleep(1);
    kill(getppid(), SIGUSR2);
}
/*****************************************************************************/ 
static void ParentProc(pid_t child)
{
    sleep(1);
    kill(child, SIGUSR1);
    pause();
}
/*****************************************************************************/
static void HandleReturnStatus(int status)
{
    int exit_status = 0;
    int signal_number = 0;
    if(WIFEXITED(status) && (exit_status = WEXITSTATUS(status)))
    {
        printf("Program exited with status: %d\n", exit_status);
    }
    else if(WIFSIGNALED(status))
    {
        signal_number = WTERMSIG(status);
        printf("Program terminated by signal: %d\n", signal_number);
    }
}
/*****************************************************************************/
