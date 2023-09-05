#include<stdio.h>   /* printf       */
#include<stddef.h>  /* size_t       */

#include "queue.h"

/*****************************************************************************/
int main(void)
{
	size_t var1 = 1;
	int var2 = 2;
	float var3 = 3.33;
	unsigned long int var4 = 700;
	long double var5 = 666.666;
	double var6 = 4.4444444;

	queue_t *queue = QueueCreate();
	queue_t *queue2 = QueueCreate();

	printf("\nQueue size after creation : %lu\n", QueueSize(queue));

	if(QueueIsEmpty(queue))
	{
		printf("\nQueue is empty after creation.\n\n");
	}

	QueueEnqueue(queue, &var1);
	QueueEnqueue(queue, &var2);
	QueueEnqueue(queue, &var3);
	QueueEnqueue(queue, &var4);
	QueueEnqueue(queue, &var5);
	QueueEnqueue(queue, &var6);

	printf("\nQueue peek after enqueues : %lu\n", *(size_t *)QueuePeek(queue));

	QueueEnqueue(queue2, &var2);
	QueueEnqueue(queue2, &var2);
	QueueEnqueue(queue2, &var2);
	QueueEnqueue(queue2, &var2);
	QueueEnqueue(queue2, &var2);
	QueueEnqueue(queue2, &var2);
	QueueEnqueue(queue2, &var2);
	QueueEnqueue(queue2, &var2);
	QueueEnqueue(queue2, &var2);

	if(!QueueIsEmpty(queue))
	{
		printf("\nQueue is not empty after creation.\n");
	}

	printf("\nQueue size after enqueues : %lu\n\n", QueueSize(queue));

	QueueDequeue(queue);
	printf("\nQueue peek after dequeue : %d\n", *(int *)QueuePeek(queue));
	QueueDequeue(queue);
	printf("\nQueue peek after dequeue : %f\n", *(float *)QueuePeek(queue));
	QueueDequeue(queue);
	printf("\nQueue peek after dequeue : %lu\n", *(unsigned long int *)QueuePeek(queue));
	QueueDequeue(queue);
	printf("\nQueue peek after dequeue : %Lf\n", *(long double *)QueuePeek(queue));
	QueueDequeue(queue);
	printf("\nQueue peek after dequeue : %f\n", *(double *)QueuePeek(queue));

	printf("\nQueue size after dequeues : %lu\n\n", QueueSize(queue));

	printf("\nQueue2 size before appending : %lu\n", QueueSize(queue2));

	printf("\nQueue2 peek int : %d\n", *(int *)QueuePeek(queue2));

	QueueEnqueue(queue, &var1);
	QueueEnqueue(queue, &var2);
	QueueEnqueue(queue, &var3);
	QueueEnqueue(queue, &var4);
	QueueEnqueue(queue, &var5);
	QueueEnqueue(queue, &var6);

	QueueAppend(queue2, queue);

	printf("\nQueue2 size after appending : %lu\n", QueueSize(queue2));

	printf("\nQueue2 peek after appending int : %d\n\n", *(int *)QueuePeek(queue2));

	QueueDestroy(queue);
	QueueDestroy(queue2);

    return 0;
}
