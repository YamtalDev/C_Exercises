/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: Amitai Glauber            ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    date : 03.04.2023                   ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀
******************************************************************************/
#include <stdlib.h> /* malloc, free, system */
#include <stdio.h>  /*     printf, puts     */
#include <stddef.h> /*     size_t, NULL     */
#include <assert.h> /*        assert        */
#include <unistd.h> /*        sleep         */
#include <time.h>   /*         time         */
#include <string.h> /*        strstr        */

#include "scheduler.h"

void SchedulerCreateTest(void);
void SchedulerAddTaskTest(void);
void SchedulerRemoveTaskTest(void);
void SchedulerRunTest(void);
void SchedulerStopTest(void);
void SchedulerSizeTest(void);
void SchedulerIsEmptyTest(void);
void SchedulerClearTest(void);
void CleanToTaskScheduler(void *param);
int ActionToTaskScheduler(void *param);
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
	SchedulerCreateTest();
	puts("\n SchedulerCreateTest() : passed.");
	SchedulerAddTaskTest();
	puts("\n SchedulerAddTaskTest() : passed.");
	SchedulerRemoveTaskTest();
	puts("\n SchedulerRemoveTaskTest() : passed.");
	SchedulerRunTest();
	SchedulerStopTest();
	puts("\n SchedulerStopTest() : passed.");
	SchedulerSizeTest();
	puts("\n SchedulerSizeTest() : passed.");
	SchedulerIsEmptyTest();
	puts("\n SchedulerIsEmptyTest() : passed.");
	SchedulerClearTest();
	puts("\n SchedulerClearTest() : passed.\n");
	return (0);
}
/*****************************************************************************/
void SchedulerCreateTest(void)
{
	scheduler_t *scheduler = SchedulerCreate();
	assert(scheduler);
	SchedulerDestroy(scheduler);
	return;
}
/*****************************************************************************/
void SchedulerAddTaskTest(void)
{
	time_t when = time(0);
	char *param = NULL;
	size_t interval = 5;
	scheduler_t *scheduler = SchedulerCreate();
	assert(scheduler);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)1, when + (time_t)1);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)2, when + (time_t)2);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)3, when + (time_t)3);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)4, when + (time_t)4);

	SchedulerDestroy(scheduler);

	return;
}
/*****************************************************************************/
void SchedulerRemoveTaskTest(void)
{
	time_t when = time(NULL);
	char *param = NULL;
	size_t interval = 5;
	ilrd_uid_t dum_uid = UIDCreate();
	ilrd_uid_t task1_uid = UIDGetBad();
	ilrd_uid_t task2_uid = UIDGetBad(); 
	scheduler_t *scheduler = SchedulerCreate();
	assert(scheduler);

	task1_uid = SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)1, when + (time_t)1);

	task2_uid = SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval, when);

	
	assert(!SchedulerRemoveTask(scheduler, task2_uid));
	assert(!SchedulerRemoveTask(scheduler, task1_uid));
	assert(SchedulerRemoveTask(scheduler, dum_uid));

	SchedulerDestroy(scheduler);

	return;
}
/*****************************************************************************/
void SchedulerRunTest(void)
{
	time_t when = time(NULL) + (time_t)5;
	char *param = NULL;
	size_t interval = 1;
	scheduler_t *scheduler = SchedulerCreate();
	assert(scheduler);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval, when);
	SchedulerAddTask(scheduler, Stop, (void *)scheduler, 
	CleanToTaskScheduler, interval, when - (time_t)5);

	SchedulerRun(scheduler);

	SchedulerDestroy(scheduler);
	return;
}
/*****************************************************************************/
void SchedulerStopTest(void)
{
	scheduler_t *scheduler = SchedulerCreate();
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
	assert(scheduler);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, 0, when);

	SchedulerAddTask(scheduler, FileStop, scheduler, FileClean, 
	interval, when + (time_t)1);

	SchedulerAddTask(scheduler, Stop, scheduler, StopClean, 0, when + (time_t)20);

	SchedulerRun(scheduler);

	SchedulerDestroy(scheduler);
}
/*****************************************************************************/
void SchedulerSizeTest(void)
{
	time_t when = time(0);
	char *param = NULL;
	size_t interval = 5;
	scheduler_t *scheduler = SchedulerCreate();
	assert(scheduler);
	assert(0 == SchedulerSize(scheduler));

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)1, when + (time_t)1);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)2, when + (time_t)2);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)3, when + (time_t)3);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)4, when + (time_t)4);

	assert(4 == SchedulerSize(scheduler));
	SchedulerDestroy(scheduler);
	return;
}
/*****************************************************************************/
void SchedulerIsEmptyTest(void)
{
	time_t when = time(0);
	char *param = NULL;
	size_t interval = 5;

	scheduler_t *scheduler = SchedulerCreate();
	assert(scheduler);
	assert(0 == SchedulerSize(scheduler));
	assert(1 == SchedulerIsEmpty(scheduler));

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)1, when + (time_t)1);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)2, when + (time_t)2);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)3, when + (time_t)3);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)4, when + (time_t)4);
	
	assert(0 == SchedulerIsEmpty(scheduler));
	assert(4 == SchedulerSize(scheduler));
	SchedulerDestroy(scheduler);

	return;
}
/*****************************************************************************/
void SchedulerClearTest(void)
{
	time_t when = time(0);
	char *param = NULL;
	size_t interval = 5;

	scheduler_t *scheduler = SchedulerCreate();
	assert(scheduler);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)1, when + (time_t)1);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)2, when + (time_t)2);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)3, when + (time_t)3);

	SchedulerAddTask(scheduler, ActionToTaskScheduler, (void *)param, 
	CleanToTaskScheduler, interval + (size_t)4, when + (time_t)4);

	assert(0 == SchedulerIsEmpty(scheduler));
	assert(4 == SchedulerSize(scheduler));

	SchedulerClear(scheduler);

	assert(1 == SchedulerIsEmpty(scheduler));
	assert(0 == SchedulerSize(scheduler));

	SchedulerDestroy(scheduler);

	return;
}
/*****************************************************************************/
int ActionToTaskScheduler(void *param)
{
	param = malloc(sizeof(char) * 50);
	if(NULL == param)
	{
		return FAILURE;
	}
	strcpy((char *)param, "\n SchedulerRunTest() : passed.\n");
	printf(" %s", (char *)param);
	free(param);
	param = NULL;
	return SUCCESS;
}
/*****************************************************************************/
void CleanToTaskScheduler(void *param)
{
	(void)param;
	return;
}
/*****************************************************************************/
int Stop(void *scheduler)
{
	SchedulerStop((scheduler_t *)scheduler);
	return SUCCESS;
}
/*****************************************************************************/
void StopClean(void *scheduler)
{
	(void)scheduler;
	return;
}
/*****************************************************************************/
int FileStop(void *scheduler)
{
	if(FindStopInFile(file_name))
	{
		SchedulerStop((scheduler_t *)scheduler);
	}

	return SUCCESS;
}
/*****************************************************************************/
void FileClean(void *scheduler)
{
	FILE *file = fopen(file_name, "w");
	(void)scheduler;
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

	if(!sprintf(buffer, ".scheduler.%d", (int)process_pid))
	{
		return NULL;
	}

	return buffer;
}
/*****************************************************************************/
