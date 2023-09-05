/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: Amitai Glaube             ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    date : 03.04.2023                   ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀

******************************************************************************/
#include <unistd.h>         /* getpid, sleep */
#include <stdlib.h>         /* malloc, free  */
#include <stddef.h>         /* size_t, NULL  */
#include <assert.h>         /* assert        */
#include <time.h>           /* time          */

#include "priority_queue.h" /* Internal use */
#include "scheduler.h"      /* Internal use */
#include "task.h"           /* Internal use */


/*****************************************************************************/
enum state
{
	SELF_DESTROY = -2,
	INTERNAL_ERROR,
	CONTINUE,
	RUN, STOP
};
/*****************************************************************************/
struct scheduler
{
	priority_queue_t *pq;
	int stop;
};
/*****************************************************************************/
#define TIME(X) ((time_t)X)
#define TASK(X) ((task_t *)X)
#define MAX(a,b) ((a) > (b) ? (a) : (b))
/*****************************************************************************/
static int Priority(void *when1, void *when2);
static int IsMatch(void *task, void *task_uid);
/*****************************************************************************/
scheduler_t *SchedulerCreate(void)
{
	scheduler_t *scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if(NULL == scheduler)
	{
		return NULL;
	}

	scheduler->pq = PriorityQueueCreate(Priority);
	if(NULL == scheduler->pq)
	{
		free(scheduler);
		scheduler = NULL;
		return (NULL);
	}

	scheduler->stop = RUN;
	return (scheduler);
}
/*****************************************************************************/
void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);

	SchedulerClear(scheduler);
	PriorityQueueDestroy(scheduler->pq);

	scheduler->pq = NULL;
	free(scheduler);
	scheduler = NULL;
}
/*****************************************************************************/
ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler, scheduler_action_func_t action, \
void *parameter, scheduler_clean_func_t clean, size_t interval, time_t when)
{
	task_t *task = NULL;

	assert(clean);
	assert(action);
	assert(scheduler);
	assert(scheduler->pq);
	assert(TIME(INTERNAL_ERROR) != when);

	task = TaskCreate(action, parameter, clean, interval, when);
	if(NULL == task || 0 != PriorityQueueEnqueue(scheduler->pq, task))
	{
		return (UIDGetBad());
	}

	return (TaskGetUID(task));
}
/*****************************************************************************/
int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t task_uid)
{
	task_t *task = NULL;
	assert(scheduler);
	assert(scheduler->pq);

	task = TASK(PriorityQueueErase(scheduler->pq, IsMatch, &task_uid));
	if((priority_queue_t *)task == scheduler->pq)
	{
		return (FAILURE);
	}

	TaskDestroy(task);
	return (SUCCESS);
}
/*****************************************************************************/
int SchedulerRun(scheduler_t *scheduler)
{
	size_t interval = 0;
	task_t *task = NULL;
	int status = CONTINUE;
	time_t now = TIME(INTERNAL_ERROR);

	assert(scheduler);
	assert(scheduler->pq);
	while(!PriorityQueueIsEmpty(scheduler->pq) && !scheduler->stop && !status)
	{
		task = TASK(PriorityQueueDequeue(scheduler->pq));
		interval = TaskGetInterval(task);

		now = time(NULL);
		sleep(MAX(TaskGetTime(task) - now, 0));

		if(SELF_DESTROY == (status = TaskRun(task)))
		{
			SchedulerRemoveTask(scheduler, TaskGetUID(task));
			status = (CONTINUE);
		}

		if(interval)
		{
			TaskSetTime(task, now + TIME(interval) - 
			((now - TIME(interval)) % TIME(interval)));

			if(PriorityQueueEnqueue(scheduler->pq, task))
			{
				return (INTERNAL_ERROR);
			}
		}
		else
		{
			TaskDestroy(task);
		}
	}

	scheduler->stop = RUN;
	return (status);
}
/*****************************************************************************/
void SchedulerStop(scheduler_t *scheduler)
{
	assert(scheduler);
	scheduler->stop = STOP;
}
/*****************************************************************************/
size_t SchedulerSize(scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	return (PriorityQueueSize(scheduler->pq));
}
/*****************************************************************************/
int SchedulerIsEmpty(scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	return (PriorityQueueIsEmpty(scheduler->pq));
}
/*****************************************************************************/
void SchedulerClear(scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	while(!PriorityQueueIsEmpty(scheduler->pq))
	{
		TaskDestroy(TASK(PriorityQueueDequeue(scheduler->pq)));
	}
}
/*****************************************************************************/
static int Priority(void *task2, void *task1)
{
	return ((int)(TaskGetTime(TASK(task2)) - TaskGetTime(TASK(task1))));
}
/*****************************************************************************/
static int IsMatch(void *task, void *task_uid)
{
	return (UIDIsMatch(*(ilrd_uid_t *)task_uid, TaskGetUID(TASK(task))));
}
/*****************************************************************************/
