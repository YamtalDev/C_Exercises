#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "unique_identifier.h" /* Including for task_uid creation */

enum status
{
	SUCCESS = 0, FAILURE 
};

typedef struct scheduler scheduler_t;

/*returns zero if succeed and non zero if fails*/
typedef int (*scheduler_action_func_t)(void *parameter);
typedef void (*scheduler_clean_func_t)(void *parameter);

/*****************************************************************************

function: SchedulerCreate

Usage: scheduler_t *scheduler = SchedulerCreate()

Description: The SchedulerCreate function will create an empty scheduler to be 
filed and run. 

Arguments: No arguments needed.
Return value: The function returns a pointer to scheduler_t that allows access
              to the scheduler. If fails returns NULL.

Complexities - time Complexity O(1), space complexity O(1). */

scheduler_t *SchedulerCreate(void);

/*****************************************************************************

function: SchedulerDestroy

Usage: SchedulerDestroy(scheduler)


Description: The SchedulerDestroy will clean and destroys all tasks in it and 
then it will destroy the scheduler itself.

Arguments: Pointer to scheduler_t type.
Return value: no return values.
Complexities - time Complexity O(n), space complexity O(1). */

void SchedulerDestroy(scheduler_t *scheduler);

/*****************************************************************************

function: SchedulerAdd

Usage: ilrd_task_uid_t task_uid = SchedulerAdd(scheduler, action, parameter, clean, interval, when)

Description: Adds a action to the scheduler, parameter to use, clean function if 
requires, time interval to repeat and when to activate the action. 
When an interval equal to zero, task will run only once.
Important point - adding a lot of high priority task could lead to starvation - 
task with low priority might never run.

Arguments: pointer to a scheduler, action function of type int action(void *),
clean function type void clean(void), interval - amount of seconds until next repeat,
when - time to activate.

Return value: Returns the task_uid of the action, if fails returns bad task_uid.
Complexities - time Complexity O(n), space complexity O(1). */

ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler, scheduler_action_func_t action, void *parameter, scheduler_clean_func_t clean, size_t interval, time_t when); 

/*****************************************************************************

function: SchedulerRemove

Usage: SchedulerRemove(scheduler, task_uid)

Description: Removes a action from the scheduler by its task_uid.
Arguments: pointer to a scheduler, task_uid of the task.
Return value: return non zero value if fails, and zero if succeed.
Complexities - time Complexity O(n), space complexity O(1). */

int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t task_uid);

/*****************************************************************************

function: SchedulerRun

Usage: SchedulerRun(scheduler)

Description: Runs the scheduler. Please notice - only one scheduler can run for one proccess.
API can't guarantee the exact time of execution because of delays.
Tasks that late and had to execute before current time will be treated first. 
Tasks like this will first of all run, and the intervals will be set from the time "when" \
that passed in schedulerAddFunction. If tasks have the same "when", then their order is undefined.

Arguments: pointer to a scheduler.

Return value: if fails - return value of the failed action function 
or "-1" if something went wrong in our in a proccess of running. If user wants to
remove task from the scheduler - he could return "-2" in action function to inform us.
That means that action function cannot return -1 if fails. 
If succeed - returns zero. Fail of Run stops the scheduler if a failure is met or if user stops scheduler.
All the task will be scheduler by the tasks "when" parameter. If the time "when" passed, 
the task will be executed by run function when it called according to the order of scheduler.

Complexities - undefined. */

int SchedulerRun(scheduler_t *scheduler);

/*****************************************************************************

function: SchedulerStop

Usage: SchedulerStop(scheduler)

Description: Stops the scheduler. In order to stop scheduler asynchronous - 
user can add task that In order to stop scheduler asynchronous -
user could add task that creates file in the same directory with executable and \
another task that checks if in this file there is a "stop" word. \
If the word been added - Stop function is called.
Arguments: pointer to a scheduler.
Return value: no return values.
Complexities - time Complexity O(1), space complexity O(1). */

void SchedulerStop(scheduler_t *scheduler);

/*****************************************************************************

function: SchedulerSize

Usage: size_t size = SchedulerSize(scheduler)

Description: Counts the number of tasks in the scheduler.
Arguments: pointer to a scheduler.
Return value: returns size_t.
Complexities - time Complexity O(n), space complexity O(1). */

size_t SchedulerSize(scheduler_t *scheduler);

/*****************************************************************************

function: SchedulerIsEmpty

Usage: int answer = SchedulerIsEmpty(scheduler)

Description: Checks if the scheduler is empty from tasks.
Arguments: pointer to a scheduler.
Return value: returns int, non-zero if empty and 0 if not.
Complexities - time Complexity O(1), space complexity O(1). */

int SchedulerIsEmpty(scheduler_t *scheduler);

/*****************************************************************************

function: SchedulerClear

Usage: SchedulerClear(scheduler)

Description: Clear scheduler from tasks.
Arguments: pointer to a scheduler.
Return value: No return values.
Complexities - time Complexity O(n), space complexity O(1). */

void SchedulerClear(scheduler_t *scheduler);


/*****************************************************************************/

#endif /* __SCHEDULER_H__*/

