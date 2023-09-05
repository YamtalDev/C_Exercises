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
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>

typedef struct queue queue_t;

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Creation of a Queue, if creation fails it will return NULL */

queue_t *QueueCreate(void);

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Destroy of the Queue. */

void QueueDestroy(queue_t *queue);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Adds element to the back of queue. return 0 on success. */

int QueueEnqueue(queue_t *queue, void *data);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Removes element from head of queue */

void QueueDequeue(queue_t *queue);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Return the data from the head of queue */

void *QueuePeek(const queue_t *queue);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Return 1 if empty and 0 if not */

int QueueIsEmpty(const queue_t *queue);

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Returns the size of queue */

size_t QueueSize(const queue_t *queue);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Appends two queues. source will be empty after appending. */

void QueueAppend(queue_t *dest, queue_t *source);

/*****************************************************************************/

#endif /* __QUEUE_H__ */
