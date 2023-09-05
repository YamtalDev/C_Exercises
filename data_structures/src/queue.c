/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: Artemy Ozerski            ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    date: 13.03.2023                    ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀
******************************************************************************/
#include <stdlib.h> /* for ex15     */
#include <stddef.h> /* size_t, NUL  */
#include <assert.h> /* assert       */

#include "queue.h"   /* Internal use */
#include "sll.h"     /* Internal use */
/*****************************************************************************/
struct queue
{
	sll_t *sll;
};
/*****************************************************************************/
int QueueEnqueue(queue_t *queue, void *data)
{
	sll_iter_t iterator = SLLInsert(SLLEnd(queue -> sll), data);

	assert(queue && "Queue isn't valid.");
	return iterator == SLLEnd(queue -> sll);
}
/*****************************************************************************/
void QueueDequeue(queue_t *queue)
{
	assert(queue && "Queue isn't valid.");
	SLLRemove(SLLBegin(queue -> sll));
}
/*****************************************************************************/
void *QueuePeek(const queue_t *queue)
{
	assert(queue && "Queue isn't valid.");
	return SLLGetData(SLLBegin(queue -> sll));
}
/*****************************************************************************/
int QueueIsEmpty(const queue_t *queue)
{
	assert(queue && "Queue isn't valid.");
	return SLLIsEmpty(queue -> sll);
}
/*****************************************************************************/
size_t QueueSize(const queue_t *queue)
{
	assert(queue && "Queue isn't valid.");
	return SLLCount(queue -> sll);
}
/*****************************************************************************/
queue_t *QueueCreate(void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));

	if(NULL == queue)
	{
		return NULL;
	}

	queue -> sll = SLLCreate();

	if(NULL == queue -> sll)
	{
		free(queue);
		return NULL;
	}

	return queue;
}
/*****************************************************************************/
void QueueDestroy(queue_t *queue)
{
	assert(queue && "Queue isn't valid.");

	SLLDestroy(queue -> sll);
	free(queue);
}
/*****************************************************************************/
void QueueAppend(queue_t *dest, queue_t *source)
{
	assert(dest && "Queue isn't valid.");
	assert(source && "Queue isn't valid.");
	SLLAppend(dest -> sll, source -> sll);
}
/*****************************************************************************/
