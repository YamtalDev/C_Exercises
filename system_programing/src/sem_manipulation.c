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

    Reviewer: Ravit.

    Date: 05.06.2023

*******************************************************************************

                          Description:

  This code is a program that interacts with a semaphore. It allows the user to 
  manipulate the semaphore using commands. The program initializes the semaphore 
  based on a given name. It provides commands to increment, decrement, and view 
  the semaphore value. The program includes cleanup operations and can delete a 
  file associated with the semaphore.

******************************************************************************/
#include <stdio.h>   /* puts, remove, stdin, sscanf, sprintf, printf */
#include <string.h>  /* strstr, strcspn, strcat, strcpy, fgets       */
#include <sys/sem.h> /* semget, ftok, semctl, semop                  */
#include <stdlib.h>  /* system                                       */

#include "sem_manipulation.h" /* Internal API */
/*****************************************************************************/
static int semid;
static char *file_name;
typedef status_t (*table_t)(char *);
/*****************************************************************************/
#define EXIT (1)
#define RM_FLG "-rm"
#define SEM_FAILURE (-1)
#define TABLE_SIZE (256)
#define BUFFER_LENGTH (100)
#define IGNORE(X) ((void)X)
static table_t input_handle_table[TABLE_SIZE];
/*****************************************************************************/
static void CleanUp(void);
static int GetNumber(char *);
static void GetInput(char *);
static void HandleTableInit(void);
static status_t HandleInput(char *);
static status_t ExitProgram(char *);
static status_t InitSettings(char *);
static status_t InitSemaphore(char *);
static status_t IgnoreCommand(char *);
static status_t ViewSemaphoreValue(char *);
static status_t DecrementSemaphore(char *);
static status_t IncrementSemaphore(char *);
static init_status_t IsSemaphoreRunning(void);
static status_t HandleSemaphoreOperation(char *, int);
/*****************************************************************************/
status_t StartPlayingWithSemaphore(char *semaphore_name)
{
    status_t status = SUCCESS;
    char input_buffer[BUFFER_LENGTH];
    status = InitSettings(semaphore_name);
    if(FAILURE == status)
    {
        return (FAILURE);
    }

    while(SUCCESS == status)
    {
        GetInput(input_buffer);
        status = HandleInput(input_buffer);
    }

    return (SUCCESS);
}
/*****************************************************************************/
static status_t HandleInput(char *command)
{
    if(strstr(command, RM_FLG))
    {
        CleanUp();
        return (EXIT);
    }

    return (input_handle_table[(int)command[0]](command));
}
/*****************************************************************************/
static status_t ExitProgram(char *command)
{
    IGNORE(command);
    return (EXIT);
}
/*****************************************************************************/
static status_t ViewSemaphoreValue(char *command)
{
    printf("\nSemaphore value: %d\n\n", semctl(semid, 0, GETVAL));
    IGNORE(command);
    return (SUCCESS);
}
/*****************************************************************************/
static status_t IgnoreCommand(char *command)
{
    IGNORE(command);
    return (SUCCESS);
}
/*****************************************************************************/
static status_t DecrementSemaphore(char *command)
{
    int number_to_decrement = GetNumber(command);
    return (HandleSemaphoreOperation(command, -1 * number_to_decrement));
}
/*****************************************************************************/
static status_t IncrementSemaphore(char *command)
{
    int number_to_increment = GetNumber(command);
    return (HandleSemaphoreOperation(command, number_to_increment));
}
/*****************************************************************************/
static status_t InitSemaphore(char *semaphore_name)
{
    union semun arg;
    key_t key = ftok(semaphore_name, 'J');

    if(SEM_FAILURE == key)
    {
        return (FAILURE);
    }

    semid = semget(key, 1, 0666 | IPC_CREAT);
    if(INITIALIZED == IsSemaphoreRunning())
    {
        return (SUCCESS);
    }

    if(SEM_FAILURE == semid)
    {
        return (FAILURE);
    }

    arg.val = 0;
    if(SEM_FAILURE == semctl(semid, 0, SETVAL, arg))
    {
        return (FAILURE);
    }

    return (SUCCESS);
}
/*****************************************************************************/ 
static init_status_t IsSemaphoreRunning(void)
{
    struct semid_ds sem_info;
    if(SEM_FAILURE == semid)
    {
        return (NOT_INITIALIZED);
    }

    if(SEM_FAILURE == semctl(semid, 0, IPC_STAT, &sem_info))
    {
        return (NOT_INITIALIZED);
    }

    if(0 != sem_info.sem_otime)
    {
        return (INITIALIZED);
    }

    return (NOT_INITIALIZED);
}
/*****************************************************************************/
static void CleanUp(void)
{
    char buffer[BUFFER_LENGTH];
    char delete_command[BUFFER_LENGTH];
    const char *base_command = "ipcrm -s ";
    sprintf(buffer, "%d", semid);

    if(0 == remove(file_name))
    {
       puts("\nFile deleted successfully\n");
    }
    else
    {
       puts("\nUnable to delete file\n");
    }

    strcpy(delete_command, base_command);
    strcat(delete_command, buffer);
    system(delete_command);
}
/*****************************************************************************/
static status_t HandleSemaphoreOperation(char *command, int value)
{
    status_t status = SUCCESS;
    struct sembuf semaphore;
    semaphore.sem_op = value;
    semaphore.sem_num = 0;
    semaphore.sem_flg = 0;

    if(!value)
    {
        return (SUCCESS);
    }

    if(strstr(command, "undo"))
    {
        semaphore.sem_flg = SEM_UNDO;
    }

    if(SEM_FAILURE == semop(semid, &semaphore, 1))
    {
        status = FAILURE;
    }

    return (status);
}
/*****************************************************************************/
static void HandleTableInit(void)
{
    int i = 0;
    for(; i < TABLE_SIZE; ++i)
    {
        input_handle_table[i] = IgnoreCommand;
    }

    input_handle_table['X'] = ExitProgram;
    input_handle_table['x'] = ExitProgram;
    input_handle_table['D'] = DecrementSemaphore;
    input_handle_table['d'] = DecrementSemaphore;
    input_handle_table['I'] = IncrementSemaphore;
    input_handle_table['i'] = IncrementSemaphore;
    input_handle_table['V'] = ViewSemaphoreValue;
    input_handle_table['v'] = ViewSemaphoreValue;
}
/*****************************************************************************/
static void GetInput(char *input)
{
    fgets(input, BUFFER_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';
}
/*****************************************************************************/
static int GetNumber(char *command)
{
    int number = 0;
    /* Retrieving the number */
    sscanf(command, "%*[^0-9]%d", &number);
    return (number);
}
/*****************************************************************************/
static status_t InitSettings(char *semaphore_name)
{
    HandleTableInit();
    file_name = semaphore_name;
    return (InitSemaphore(semaphore_name));
}
/*****************************************************************************/