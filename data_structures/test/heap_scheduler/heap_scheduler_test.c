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

    Reviewer: First name and family name.

    Date: 15.05.2023

*******************************************************************************

                          Description:

  

******************************************************************************/
#include <stdlib.h> /* malloc, free, system */
#include <stdio.h>  /*     printf, puts     */
#include <stddef.h> /*     size_t, NULL     */
#include <assert.h> /*        assert        */
#include <unistd.h> /*        sleep         */
#include <time.h>   /*         time         */
#include <string.h> /*        strstr        */

#include "heap_scheduler.h"     /* Internal API */
/*****************************************************************************/
void HeapSchedulerCreateTest(void);
void HeapSchedulerAddTaskTest(void);
void HeapSchedulerRemoveTaskTest(void);
void HeapSchedulerRunTest(void);
void HeapSchedulerStopTest(void);
void HeapSchedulerSizeTest(void);
void HeapSchedulerIsEmptyTest(void);
void HeapSchedulerClearTest(void);
void CleanToTaskHeapScheduler(void *param);
int ActionToTaskHeapScheduler(void *param);
int Stop(void *scheduler);
void StopClean(void *param);
int FindStopInFile(const char *file_name);
char *GetFileName(void);
void FileClean(void *file_name);
int FileStop(void *file_name);
char word[5] = "stop";
char *file_name = NULL;
/*****************************************************************************/
int main(void)
{
	HeapSchedulerCreateTest();
	puts("\n HeapSchedulerCreateTest() : passed.");
	HeapSchedulerAddTaskTest();
	puts("\n HeapSchedulerAddTaskTest() : passed.");
	HeapSchedulerRemoveTaskTest();
	puts("\n HeapSchedulerRemoveTaskTest() : passed.");
	HeapSchedulerRunTest();
	HeapSchedulerStopTest();
	puts("\n HeapSchedulerStopTest() : passed.");
	HeapSchedulerSizeTest();
	puts("\n HeapSchedulerSizeTest() : passed.");
	HeapSchedulerIsEmptyTest();
	puts("\n HeapSchedulerIsEmptyTest() : passed.");
	HeapSchedulerClearTest();
	puts("\n HeapSchedulerClearTest() : passed.\n");
	return (0);
}
/*****************************************************************************/
void HeapSchedulerCreateTest(void)
{
	heap_scheduler_t *HeapScheduler = HeapSchedulerCreate();
	assert(HeapScheduler);
	HeapSchedulerDestroy(HeapScheduler);
	return;
}
/*****************************************************************************/
void HeapSchedulerAddTaskTest(void)
{
	char *param = NULL;
	size_t interval = 5;
	time_t when = time(0);
	heap_scheduler_t *HeapScheduler = HeapSchedulerCreate();
	assert(HeapScheduler);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)1, when + (time_t)1);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)2, when + (time_t)2);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)3, when + (time_t)3);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)4, when + (time_t)4);

	HeapSchedulerDestroy(HeapScheduler);

	return;
}
/*****************************************************************************/
void HeapSchedulerRemoveTaskTest(void)
{
	time_t when = time(NULL);
	char *param = NULL;
	size_t interval = 5;
	ilrd_uid_t dum_uid = UIDCreate();
	ilrd_uid_t task1_uid = UIDGetBad();
	ilrd_uid_t task2_uid = UIDGetBad(); 
	heap_scheduler_t *HeapScheduler = HeapSchedulerCreate();
	assert(HeapScheduler);

	task1_uid = HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)1, when + (time_t)1);

	task2_uid = HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval, when);

	
	assert(!HeapSchedulerRemoveTask(HeapScheduler, task2_uid));
	assert(!HeapSchedulerRemoveTask(HeapScheduler, task1_uid));
	assert(HeapSchedulerRemoveTask(HeapScheduler, dum_uid));

	HeapSchedulerDestroy(HeapScheduler);

	return;
}
/*****************************************************************************/
void HeapSchedulerRunTest(void)
{
	time_t when = time(NULL) + (time_t)5;
	char *param = NULL;
	size_t interval = 1;
	heap_scheduler_t *HeapScheduler = HeapSchedulerCreate();
	assert(HeapScheduler);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval, when);
	HeapSchedulerAddTask(HeapScheduler, Stop, (void *)HeapScheduler, 
	CleanToTaskHeapScheduler, interval, when - (time_t)5);

	HeapSchedulerRun(HeapScheduler);

	HeapSchedulerDestroy(HeapScheduler);
	return;
}
/*****************************************************************************/
void HeapSchedulerStopTest(void)
{
	heap_scheduler_t *HeapScheduler = HeapSchedulerCreate();
	time_t when = time(NULL);
	char command[150] = "xdg-open ";
	FILE *file = NULL;
	size_t interval = 2;
	char *param = NULL;

	file_name = GetFileName();
	if(NULL == file_name)
	{
		printf("Get file_name failed.");
		return;
	}

	file = fopen((char *)file_name, "w");
	if(EOF == fclose(file))
	{
		printf("Closing file failed.");
		return;
	}

	system(strcat(command, (char *)file_name));
	assert(HeapScheduler);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, 0, when);

	HeapSchedulerAddTask(HeapScheduler, FileStop, HeapScheduler, FileClean, 
	interval, when + (time_t)1);

	HeapSchedulerAddTask(HeapScheduler, Stop, HeapScheduler, StopClean, 0, when + (time_t)20);

	HeapSchedulerRun(HeapScheduler);

	HeapSchedulerDestroy(HeapScheduler);
}
/*****************************************************************************/
void HeapSchedulerSizeTest(void)
{
	time_t when = time(0);
	char *param = NULL;
	size_t interval = 5;
	heap_scheduler_t *HeapScheduler = HeapSchedulerCreate();
	assert(HeapScheduler);
	assert(0 == HeapSchedulerSize(HeapScheduler));

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)1, when + (time_t)1);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)2, when + (time_t)2);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)3, when + (time_t)3);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)4, when + (time_t)4);

	assert(4 == HeapSchedulerSize(HeapScheduler));
	HeapSchedulerDestroy(HeapScheduler);
	return;
}
/*****************************************************************************/
void HeapSchedulerIsEmptyTest(void)
{
	time_t when = time(0);
	char *param = NULL;
	size_t interval = 5;

	heap_scheduler_t *HeapScheduler = HeapSchedulerCreate();
	assert(HeapScheduler);
	assert(0 == HeapSchedulerSize(HeapScheduler));
	assert(1 == HeapSchedulerIsEmpty(HeapScheduler));

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)1, when + (time_t)1);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)2, when + (time_t)2);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)3, when + (time_t)3);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)4, when + (time_t)4);
	
	assert(0 == HeapSchedulerIsEmpty(HeapScheduler));
	assert(4 == HeapSchedulerSize(HeapScheduler));
	HeapSchedulerDestroy(HeapScheduler);

	return;
}
/*****************************************************************************/
void HeapSchedulerClearTest(void)
{
	time_t when = time(0);
	char *param = NULL;
	size_t interval = 5;

	heap_scheduler_t *HeapScheduler = HeapSchedulerCreate();
	assert(HeapScheduler);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)1, when + (time_t)1);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)2, when + (time_t)2);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)3, when + (time_t)3);

	HeapSchedulerAddTask(HeapScheduler, ActionToTaskHeapScheduler, (void *)param, 
	CleanToTaskHeapScheduler, interval + (size_t)4, when + (time_t)4);

	assert(0 == HeapSchedulerIsEmpty(HeapScheduler));
	assert(4 == HeapSchedulerSize(HeapScheduler));

	HeapSchedulerClear(HeapScheduler);

	assert(1 == HeapSchedulerIsEmpty(HeapScheduler));
	assert(0 == HeapSchedulerSize(HeapScheduler));

	HeapSchedulerDestroy(HeapScheduler);

	return;
}
/*****************************************************************************/
int ActionToTaskHeapScheduler(void *param)
{
	param = malloc(sizeof(char) * 50);
	if(NULL == param)
	{
		return FAILURE;
	}
	strcpy((char *)param, "\n HeapSchedulerRunTest() : passed.\n");
	printf(" %s", (char *)param);
	free(param);
	param = NULL;
	return SUCCESS;
}
/*****************************************************************************/
void CleanToTaskHeapScheduler(void *param)
{
	(void)param;
	return;
}
/*****************************************************************************/
int Stop(void *HeapScheduler)
{
	HeapSchedulerStop((heap_scheduler_t *)HeapScheduler);
	return SUCCESS;
}
/*****************************************************************************/
void StopClean(void *HeapScheduler)
{
	(void)HeapScheduler;
	return;
}
/*****************************************************************************/
int FileStop(void *HeapScheduler)
{
	if(FindStopInFile(file_name))
	{
		HeapSchedulerStop((heap_scheduler_t *)HeapScheduler);
	}

	return SUCCESS;
}
/*****************************************************************************/
void FileClean(void *HeapScheduler)
{
	FILE *file = fopen(file_name, "w");
	(void)HeapScheduler;
	if(EOF == fclose(file) || remove(file_name))
	{
		printf("Failed to remove or close file.");
	}
}
/*****************************************************************************/
int FindStopInFile(const char *file_name)
{
	FILE *file = fopen(file_name, "r");
	char buffer[BUFSIZ];
	char *found = NULL;

	if(NULL == file)
	{
		file = fopen(file_name, "w");
	}

	while(NULL != fgets(buffer, BUFSIZ, file) && 
	NULL != (found = strstr(buffer, word)));

	if(EOF == fclose(file))
	{
		return SUCCESS;
	}

	return found ? 1 : 0;
}
/*****************************************************************************/
char *GetFileName(void)
{
	static char buffer[100];
	pid_t process_pid = getpid();

	if(!sprintf(buffer, ".HeapScheduler.%d", (int)process_pid))
	{
		return NULL;
	}

	return buffer;
}
/*****************************************************************************/
