/******************************************************************************
                                        ▄▄▀▀▀▀████▓▓░░  ░
                                     ▄█▓░░   ░▓█▓
                                   ▄█▓░░    ░▓█░
                                  █▓░░░░   ░▓█░
                                ▄█▓░░░    ░░▓█░
        ▄▄▄              ▄▄▄▄█▄█▓▓▀▀▀▓███▄▄▓██▓░ ░
       █░  █         ▄▄▓▓▓▓░░░░░░░░░░░░░░░▓████▄▄                      ▄▄▄▄▄▄▓
      █    ▓█    ▄▄▓▓▓▓░▓░░░   ░░░░░░░░░░░░░░░▓▓▓█▄▄     ▄        ▄▄▓▓▓░░░░█▀
       █  ▓█   ▄█▓░▄██▓░░       ░  ░░░░░░ ░░░░░░▓▓▓▓██▄    ▄   ░▄▓▓▓░░  ░▓█▓
        ▀▀▀  ▄█▓░ ▄▄▄▄▄ ░░           ░░░   ░  ▄▄▄ ░░▓▓▓█▄ ▀▓▀ ░█▓▓░░   ░▓█▓
      ▄▄    ██▓░▄▀  ░░▓█▓░░       ░  ░░      █░  █  ░░░▓▓█▄  ▓█▓▓░░   ░▓▓█░
     █ ▓█  ██▓░▓█     ░▓█▓░░   ░   ░░░      █░  ░▓█   ░░▓▓██▓█▓▓░    ░░▓▓█
      ▀▀  ██▓▓░█▓      ░▓░░   ░ ░            █ ░▓█     ░░░▓███▓░ ░  ░░░▓█▓
   ▄▄  ▄ ██▓▓░ █░  ▄▄▄  ░░     ░    ▄▄▄▄▄     ▀▀▀ ▄  ░  ░░░▓█▓░    ░░░▓▓█
  █ ▓█  ███▓▓░▄█▄▄██▄█▄▄▄░░     ▄▓▓▓░░░ ░▀  ░░░          ░░▓█▓    ░ ░░░▓█ ▀
   ▀▀   ███▓▓▓░░░░░░░  ░▓▓░░         ░     ░▓████▓▓░░░ ░  ░░▓▓  ░   ░░▓▓▓▀
     ▄▓▄ ███▓▓▓░░░░  ▄░▀▄░░░░░░░    ░    ░▓███▓░▀▀▀██▄    ░░░     ░░░▓▓▓ ▄░▀▀▄
      ▀   ▀███▓▓▓▄▄▄ ▀▄▓▀░ ▄▄▄ ░░░░░░ ░░░▓███▓░     ▀██░ ░▓░░░ ░░░░░▓▓▓ █░   ▓█
*******************************************************************************

    Writer: Tal Aharon

    Reviewer: David.

    Date: 28.05.2023

*******************************************************************************

                          Description:

  This implementation is a simple shell-like program written in C. It allows 
  users to enter commands and executes them using either fork and execvp or 
  the system function. The program handles the termination status of child 
  processes and provides a user-friendly shell prompt for interaction. 
  It supports parsing user input into tokens, forking a child process 
  to execute the command, and waiting for the child process to finish. 
  The implementation offers a basic shell environment with command 
  execution and termination status handling capabilities.

******************************************************************************/
#include <string.h>              /* strcmp, strtok, strcspn, strcpy */
#include <sys/wait.h>           /* wait, WEXITSTATUS, WTERMSIG     */
#include <stdio.h>             /* fgets , BUFSIZ                  */
#include <unistd.h>           /* fork, execvp                    */
#include <stddef.h>          /* size_t, NULL                    */
#include <stdlib.h>         /* system                          */
#include <sys/types.h>     /* pid_t                           */
#include "simple_shell.h" /* API                             */

#define FAILURE (1)
#define CONTINUE(X) (strcmp(X, "exit"))
static void HandleReturn(int status, char *program);
static status_t HandleShellPrompt(char program[BUFSIZ]);
/*****************************************************************************/
status_t ShellFork(void)
{
    int i = 0;
    int status = 0;
    pid_t child_pid = 0;
    status_t state = SUCCESS;
    char program[BUFSIZ] = {0};
    char *tokens[BUFSIZ / 2] = {NULL};

    state = HandleShellPrompt(program);
    while(i = 1, CONTINUE(program))
    {
        tokens[0] = strtok(program, " ");
        while(NULL != tokens[i - 1])
        {
            tokens[i] = strtok(NULL, " ");
            ++i;
        }

        tokens[i] = NULL;
        if(0 == (child_pid = fork()))
        {
            execvp(tokens[0], tokens);
            return (EXIT_FAILURE);
        }
        else
        {
            wait(&status);
            HandleReturn(status, program);
        }

        state = HandleShellPrompt(program);
 
    }

    return (state);
}
/*****************************************************************************/ 
status_t ShellSystem(void)
{
    char program[BUFSIZ];
    status_t status = SUCCESS;
    if(FAILURE ==  HandleShellPrompt(program))
    {
        return (FAILURE);
    }
    while(CONTINUE(program))
    {
        HandleReturn(system(program), program);
        status = HandleShellPrompt(program);
    }

    return (status);
}
/*****************************************************************************/ 
static void HandleReturn(int status, char *program)
{
    int exit_status = 0;
    int signal_number = 0;
    if(WIFEXITED(status))
    {
        exit_status = WEXITSTATUS(status);
        printf("Program '%s' exited with status: %d\n", program, exit_status);
    }
    else if(WIFSIGNALED(status))
    {
        signal_number = WTERMSIG(status);
        printf("Program '%s' terminated by signal: %d\n", program, signal_number);
    }
}
/*****************************************************************************/
static status_t HandleShellPrompt(char program[BUFSIZ])
{
        printf("> ");
        if(!fgets(program, BUFSIZ, stdin))
        {
            strcpy(program, "exit\0");
            return (FAILURE);
        }

        program[strcspn(program, "\n")] = '\0';
        return (SUCCESS);
}
