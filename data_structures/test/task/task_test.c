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
#include <stdio.h>   /* printf, puts */
#include <stddef.h>  /* size_t, NULL */
#include <assert.h>  /*   assert     */
#include <time.h>    /*     time     */
#include <stdlib.h>  /* malloc, free */
#include <string.h>  /*    strcpy    */

#include "task.h"
void TaskCreateTest(void);
void TaskRunTest(void);
void TaskGetTimeTest(void);
void TaskSetTimeTest(void);
void TaskGetIntervalTest(void);
void TaskSetIntervalTest(void);
void TaskGetUIDTest(void);
int ActionToTask(void *param);
void CleanToTask(void *param);

/*****************************************************************************/
int main(void)
{
	TaskCreateTest();
	puts("\n TaskCreateTest() : passed.");
	TaskRunTest();
	TaskGetTimeTest();
	puts("\n TaskGetTimeTest() : passed.");
	TaskSetTimeTest();
	puts("\n TaskSetTimeTest() : passed.");
	TaskGetIntervalTest();
	puts("\n TaskGetIntervalTest() : passed.");
	TaskSetIntervalTest();
	puts("\n TaskSetIntervalTest() : passed.");
	TaskGetUIDTest();
	puts("\n TaskGetUIDTest() : passed.");
	return (0);
}
/*****************************************************************************/
void TaskCreateTest(void)
{
	time_t when = time(NULL);
	size_t interval = 5;
	char *param = NULL;
	task_t *task = NULL;
	task = TaskCreate(ActionToTask, (void *)param, CleanToTask, interval, when);
	assert(task);
	TaskDestroy(task);
	return;
}
/*****************************************************************************/
void TaskRunTest(void)
{
	time_t when = time(NULL);
	size_t interval = 5;
	char *param = NULL;
	task_t *task = NULL;
	param = (char *)malloc(sizeof(char) * 40);
	strcpy(param, "\n TaskRunTest() : passed.\n");
	task = TaskCreate(ActionToTask, (void *)param, CleanToTask, interval, when);
	assert(task);
	assert(0 == TaskRun(task));
	TaskDestroy(task);
	return;
}
/*****************************************************************************/
void TaskGetTimeTest(void)
{
	time_t when = time(NULL);
	size_t interval = 5;
	char *param = NULL;
	task_t *task = NULL;
	task = TaskCreate(ActionToTask, (void *)param, CleanToTask, interval, when);
	assert(task);
	assert(when == TaskGetTime(task));
	TaskDestroy(task);
	return;
}
/*****************************************************************************/
void TaskSetTimeTest(void)
{
	time_t when = time(NULL);
	time_t new_time = time(0);
	size_t interval = 5;
	char *param = NULL;
	task_t *task = NULL;
	task = TaskCreate(ActionToTask, (void *)param, CleanToTask, interval, when);
	assert(task);
	TaskSetTime(task, new_time);
	assert(new_time == TaskGetTime(task));
	TaskDestroy(task);
	return;
}
/*****************************************************************************/
void TaskGetIntervalTest(void)
{
	time_t when = time(NULL);
	size_t interval = 5;
	char *param = NULL;
	task_t *task = NULL;
	task = TaskCreate(ActionToTask, (void *)param, CleanToTask, interval, when);
	assert(task);
	assert(interval == TaskGetInterval(task));
	TaskDestroy(task);
	return;
}
/*****************************************************************************/
void TaskSetIntervalTest(void)
{
	time_t when = time(NULL);
	size_t interval = 5;
	size_t new_interval = 7;
	char *param = NULL;
	task_t *task = NULL;
	task = TaskCreate(ActionToTask, (void *)param, CleanToTask, interval, when);
	assert(task);
	TaskSetInterval(task, new_interval);
	assert(interval != TaskGetInterval(task));
	assert(7 == TaskGetInterval(task));
	TaskDestroy(task);
	return;
}
/*****************************************************************************/
void TaskGetUIDTest(void)
{
	time_t when = time(NULL);
	ilrd_uid_t some_uid = UIDCreate();
	size_t interval = 5;
	char *param = NULL;
	task_t *task = NULL;
	task = TaskCreate(ActionToTask, (void *)param, CleanToTask, interval, when);
	assert(task);
	assert(!UIDIsMatch(some_uid, TaskGetUID(task)));
	assert(!UIDIsMatch(UIDGetBad(), TaskGetUID(task)));
	TaskDestroy(task);
	return;
}
/*****************************************************************************/
int ActionToTask(void *param)
{
	if(NULL == param)
	{
		return -1;
	}

	printf(" %s", (char *)param);
	return 0;
}
/*****************************************************************************/
void CleanToTask(void *param)
{
	free(param);
	param = NULL;
	return;
}
/*****************************************************************************/
