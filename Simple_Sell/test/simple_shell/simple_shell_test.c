/******************************************************************************

    Writer: Tal Aharon

    Reviewer: David.

    Date: 28.05.2023

******************************************************************************/
#include <string.h>         /* strcmp  */
#include <stdio.h>         /*  puts   */
#include "simple_shell.h" /*   API   */
/*****************************************************************************/
#define OPTIONS (2)
#define FORK(X) (!strcmp(X, "fork"))
#define SYSTEM(X) (!strcmp(X, "system"))
/*****************************************************************************/
int main(int argc, char *argv[])
{
    status_t status = SUCCESS;
    if(2 == argc)
    {
        if(FORK(argv[1]))
        {
            status = ShellFork();
        }
        else if(SYSTEM(argv[1]))
        {
            status = ShellSystem();
        }
    }
    else
    {
        status = FAILURE;
        puts("Usage: simple_shall fork or system");
    }

    return (status);
}
/*****************************************************************************/
