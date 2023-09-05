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

    Reviewer: Ravit Yehud.

    Date: 15.05.2023

*******************************************************************************

                          Description:

  

******************************************************************************/
#include <stdio.h>   /* printf, puts */
#include <stddef.h>  /* size_t, NULL */
#include <assert.h>  /*   assert     */
#include <stdlib.h>  /*   system     */

#include "heap_pq.h"

void HeapPQCreateTest(void);
void HeapPQEnqueueTest(void);
void HeapPQDequeueTest(void);
void HeapPQPeekTest(void);
void HeapPQIsEmptyTest(void);
void HeapPQSizeTest(void);
void HeapPQEraseTest(void);
void HeapPQClearTest(void);

/*****************************************************************************/
int main(void)
{
	HeapPQCreateTest();
	printf("\nHeapPQCreateTest(): Passed.");
	HeapPQEnqueueTest();
	printf("\nHeapPQEnqueueTest(): Passed.");
	HeapPQDequeueTest();
	printf("\nHeapPQDequeueTest(): Passed.");
	HeapPQPeekTest();
	printf("\nHeapPQPeekTest(): Passed.");
	HeapPQIsEmptyTest();
	printf("\nHeapPQIsEmptyTest(): Passed.");
	HeapPQSizeTest();
	printf("\nHeapPQSizeTest(): Passed.");
	HeapPQEraseTest();
	printf("\nHeapPQEraseTest(): Passed.");
	HeapPQClearTest();
	printf("\nHeapPQClearTest(): Passed.\n\n");
	return (0);
}
/*****************************************************************************/
int Match(const void *data, const void *parameter)
{
	return (size_t)parameter == (size_t)data;
}
/*****************************************************************************/
int Cmp(const void *data, const void *parameter)
{
	return ((size_t)parameter - (size_t)data);
}
/*****************************************************************************/
void HeapPQCreateTest(void)
{
	heap_pq_t *heap_pq = NULL;
	assert(NULL == heap_pq && "Creation failed");
	heap_pq = HeapPQCreate(Cmp);
	assert(heap_pq && "Creation failed");
	assert(1 == HeapPQIsEmpty(heap_pq));
	assert(0 == HeapPQSize(heap_pq));
	HeapPQDestroy(heap_pq);
}
/*****************************************************************************/
void HeapPQEnqueueTest(void)
{
	heap_pq_t *heap_pq = NULL;
	assert(NULL == heap_pq && "Creation failed");
	heap_pq = HeapPQCreate(Cmp);
	assert(heap_pq && "Creation failed");
	assert(1 == HeapPQIsEmpty(heap_pq));
	assert(0 == HeapPQSize(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)9);
	HeapPQEnqueue(heap_pq, (void *)18);
	HeapPQEnqueue(heap_pq, (void *)167);
	HeapPQEnqueue(heap_pq, (void *)14);
	HeapPQEnqueue(heap_pq, (void *)12);
	HeapPQEnqueue(heap_pq, (void *)112);
	HeapPQEnqueue(heap_pq, (void *)14);
	HeapPQEnqueue(heap_pq, (void *)144444);
	HeapPQEnqueue(heap_pq, (void *)144);
	HeapPQEnqueue(heap_pq, (void *)11233);
	HeapPQEnqueue(heap_pq, (void *)11);
	HeapPQEnqueue(heap_pq, (void *)0);
	HeapPQEnqueue(heap_pq, (void *)9);
	HeapPQEnqueue(heap_pq, (void *)457);
	HeapPQEnqueue(heap_pq, (void *)7);
	HeapPQEnqueue(heap_pq, (void *)6);
	HeapPQEnqueue(heap_pq, (void *)5);
	HeapPQEnqueue(heap_pq, (void *)43613);
	HeapPQEnqueue(heap_pq, (void *)1346);
	HeapPQEnqueue(heap_pq, (void *)1346);
	HeapPQEnqueue(heap_pq, (void *)1346);
	HeapPQEnqueue(heap_pq, (void *)137);
	HeapPQEnqueue(heap_pq, (void *)1347);
	HeapPQEnqueue(heap_pq, (void *)137);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)13);
	HeapPQEnqueue(heap_pq, (void *)11375);
	HeapPQEnqueue(heap_pq, (void *)1357);
	HeapPQEnqueue(heap_pq, (void *)13571357);
	HeapPQEnqueue(heap_pq, (void *)1537);
	HeapPQEnqueue(heap_pq, (void *)13571357);
	HeapPQEnqueue(heap_pq, (void *)13513571);
	HeapPQEnqueue(heap_pq, (void *)46791);
	HeapPQEnqueue(heap_pq, (void *)1578);
	HeapPQEnqueue(heap_pq, (void *)15689);
	HeapPQEnqueue(heap_pq, (void *)14679);
	HeapPQEnqueue(heap_pq, (void *)4671);
	HeapPQEnqueue(heap_pq, (void *)2451);
	HeapPQEnqueue(heap_pq, (void *)24571);
	HeapPQEnqueue(heap_pq, (void *)24571);
	HeapPQEnqueue(heap_pq, (void *)24571);
	HeapPQEnqueue(heap_pq, (void *)2451);
	HeapPQEnqueue(heap_pq, (void *)1245);
	HeapPQEnqueue(heap_pq, (void *)245724571);
	HeapPQEnqueue(heap_pq, (void *)2451);
	HeapPQEnqueue(heap_pq, (void *)24571);
	HeapPQEnqueue(heap_pq, (void *)12457);
	HeapPQEnqueue(heap_pq, (void *)3461);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)14574);
	HeapPQEnqueue(heap_pq, (void *)125);
	HeapPQEnqueue(heap_pq, (void *)1257);
	HeapPQEnqueue(heap_pq, (void *)12475);
	HeapPQEnqueue(heap_pq, (void *)135);
	HeapPQEnqueue(heap_pq, (void *)1357);
	HeapPQEnqueue(heap_pq, (void *)14679);
	HeapPQEnqueue(heap_pq, (void *)197);
	HeapPQEnqueue(heap_pq, (void *)1479);
	HeapPQEnqueue(heap_pq, (void *)14679);
	HeapPQEnqueue(heap_pq, (void *)1479);
	HeapPQEnqueue(heap_pq, (void *)14679);
	HeapPQEnqueue(heap_pq, (void *)14679);
	assert(78 == HeapPQSize(heap_pq));
	HeapPQDestroy(heap_pq);
}
/*****************************************************************************/
void HeapPQDequeueTest(void)
{
	size_t i = 77;
	heap_pq_t *heap_pq = NULL;
	assert(NULL == heap_pq && "Creation failed");
	heap_pq = HeapPQCreate(Cmp);
	assert(heap_pq && "Creation failed");
	assert(1 == HeapPQIsEmpty(heap_pq));
	assert(0 == HeapPQSize(heap_pq));

	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)9);
	HeapPQEnqueue(heap_pq, (void *)18);
	HeapPQEnqueue(heap_pq, (void *)167);
	HeapPQEnqueue(heap_pq, (void *)14);
	HeapPQEnqueue(heap_pq, (void *)12);
	HeapPQEnqueue(heap_pq, (void *)112);
	HeapPQEnqueue(heap_pq, (void *)14);
	HeapPQEnqueue(heap_pq, (void *)144444);
	HeapPQEnqueue(heap_pq, (void *)144);
	HeapPQEnqueue(heap_pq, (void *)11233);
	HeapPQEnqueue(heap_pq, (void *)11);
	HeapPQEnqueue(heap_pq, (void *)0);
	HeapPQEnqueue(heap_pq, (void *)9);
	HeapPQEnqueue(heap_pq, (void *)457);
	HeapPQEnqueue(heap_pq, (void *)7);
	HeapPQEnqueue(heap_pq, (void *)6);
	HeapPQEnqueue(heap_pq, (void *)5);
	HeapPQEnqueue(heap_pq, (void *)43613);
	HeapPQEnqueue(heap_pq, (void *)1346);
	HeapPQEnqueue(heap_pq, (void *)1346);
	HeapPQEnqueue(heap_pq, (void *)1346);
	HeapPQEnqueue(heap_pq, (void *)137);
	HeapPQEnqueue(heap_pq, (void *)1347);
	HeapPQEnqueue(heap_pq, (void *)137);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)13);
	HeapPQEnqueue(heap_pq, (void *)11375);
	HeapPQEnqueue(heap_pq, (void *)1357);
	HeapPQEnqueue(heap_pq, (void *)13571357);
	HeapPQEnqueue(heap_pq, (void *)1537);
	HeapPQEnqueue(heap_pq, (void *)13571357);
	HeapPQEnqueue(heap_pq, (void *)13513571);
	HeapPQEnqueue(heap_pq, (void *)46791);
	HeapPQEnqueue(heap_pq, (void *)1578);
	HeapPQEnqueue(heap_pq, (void *)15689);
	HeapPQEnqueue(heap_pq, (void *)14679);
	HeapPQEnqueue(heap_pq, (void *)4671);
	HeapPQEnqueue(heap_pq, (void *)2451);
	HeapPQEnqueue(heap_pq, (void *)24571);
	HeapPQEnqueue(heap_pq, (void *)24571);
	HeapPQEnqueue(heap_pq, (void *)24571);
	HeapPQEnqueue(heap_pq, (void *)2451);
	HeapPQEnqueue(heap_pq, (void *)1245);
	HeapPQEnqueue(heap_pq, (void *)245724571);
	HeapPQEnqueue(heap_pq, (void *)2451);
	HeapPQEnqueue(heap_pq, (void *)24571);
	HeapPQEnqueue(heap_pq, (void *)12457);
	HeapPQEnqueue(heap_pq, (void *)3461);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)14574);
	HeapPQEnqueue(heap_pq, (void *)125);
	HeapPQEnqueue(heap_pq, (void *)1257);
	HeapPQEnqueue(heap_pq, (void *)12475);
	HeapPQEnqueue(heap_pq, (void *)135);
	HeapPQEnqueue(heap_pq, (void *)1357);
	HeapPQEnqueue(heap_pq, (void *)14679);
	HeapPQEnqueue(heap_pq, (void *)197);
	HeapPQEnqueue(heap_pq, (void *)1479);
	HeapPQEnqueue(heap_pq, (void *)14679);
	HeapPQEnqueue(heap_pq, (void *)1479);
	HeapPQEnqueue(heap_pq, (void *)14679);
	HeapPQEnqueue(heap_pq, (void *)14679);

	for(;i > 0; --i)
	{
		HeapPQDequeue(heap_pq);
		assert(i == HeapPQSize(heap_pq));
	}
	HeapPQDequeue(heap_pq);
	assert(1 == HeapPQIsEmpty(heap_pq));
	HeapPQDestroy(heap_pq);
}
/*****************************************************************************/
void HeapPQPeekTest(void)
{
	heap_pq_t *heap_pq = NULL;
	assert(NULL == heap_pq && "Creation failed");
	heap_pq = HeapPQCreate(Cmp);
  assert(heap_pq && "Creation failed");
	assert(1 == HeapPQIsEmpty(heap_pq));
	assert(0 == HeapPQSize(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)1257);
	assert((void *)1257 == HeapPQPeek(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)12475);
  assert((void *)12475 == HeapPQPeek(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)135);
	assert((void *)12475 == HeapPQPeek(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)1357);
	assert((void *)12475 == HeapPQPeek(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)14679);
	assert((void *)14679 == HeapPQPeek(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)197);
	assert((void *)14679 == HeapPQPeek(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)1479);
	assert((void *)14679 == HeapPQPeek(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)14670009);
	assert((void *)14670009 == HeapPQPeek(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)1479);
	assert((void *)14670009 == HeapPQPeek(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)14679);
	assert((void *)14670009 == HeapPQPeek(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)14679);
	assert((void *)14670009 == HeapPQPeek(heap_pq));
	HeapPQDestroy(heap_pq);
}
/*****************************************************************************/
void HeapPQIsEmptyTest(void)
{
	heap_pq_t *heap_pq = NULL;
	assert(NULL == heap_pq && "Destroy failed");
	heap_pq = HeapPQCreate(Cmp);
	assert(heap_pq && "Destroy failed");
	assert(1 == HeapPQIsEmpty(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)1257);
	assert(0 == HeapPQIsEmpty(heap_pq));
	HeapPQDestroy(heap_pq);
}
/*****************************************************************************/
void HeapPQSizeTest(void)
{
	size_t i = 0;
	heap_pq_t *heap_pq = NULL;
	assert(NULL == heap_pq && "Destroy failed");
	heap_pq = HeapPQCreate(Cmp);
	assert(heap_pq && "Destroy failed");
	assert(0 == HeapPQSize(heap_pq));
	for(;i < 500000; i++)
	{
		HeapPQEnqueue(heap_pq, (void *)14679);
	}
	assert(500000 == HeapPQSize(heap_pq));
	HeapPQDestroy(heap_pq);
}
/*****************************************************************************/
void HeapPQEraseTest(void)
{
	heap_pq_t *heap_pq = NULL;
	assert(NULL == heap_pq && "Destroy failed");
	heap_pq = HeapPQCreate(Cmp);
	assert(heap_pq && "Destroy failed");
	assert(1 == HeapPQIsEmpty(heap_pq));
	assert(0 == HeapPQSize(heap_pq));
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)9);
	HeapPQEnqueue(heap_pq, (void *)18);
	assert(0 == HeapPQIsEmpty(heap_pq));
	assert(0 != HeapPQSize(heap_pq));
	assert((void *)1 == HeapPQErase(heap_pq, Match, (void *)1));
	assert((void *)9 == HeapPQErase(heap_pq, Match, (void *)9));
	assert((void *)heap_pq == HeapPQErase(heap_pq, Match, (void *)99));
	assert((void *)18 == HeapPQErase(heap_pq, Match, (void *)18));
	assert(1 == HeapPQIsEmpty(heap_pq));
	assert(0 == HeapPQSize(heap_pq));
	HeapPQDestroy(heap_pq);
}
/*****************************************************************************/
void HeapPQClearTest(void)
{
	heap_pq_t *heap_pq = NULL;
	assert(NULL == heap_pq && "Creation failed");
	heap_pq = HeapPQCreate(Cmp);
	assert(heap_pq && "Creation failed");
	assert(1 == HeapPQIsEmpty(heap_pq));
	assert(0 == HeapPQSize(heap_pq));

	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)9);
	HeapPQEnqueue(heap_pq, (void *)18);
	HeapPQEnqueue(heap_pq, (void *)14);
	HeapPQEnqueue(heap_pq, (void *)144444);
	HeapPQEnqueue(heap_pq, (void *)144);
	HeapPQEnqueue(heap_pq, (void *)11233);
	HeapPQEnqueue(heap_pq, (void *)11);
	HeapPQEnqueue(heap_pq, (void *)0);
	HeapPQEnqueue(heap_pq, (void *)9);
	HeapPQEnqueue(heap_pq, (void *)457);
	HeapPQEnqueue(heap_pq, (void *)7);
	HeapPQEnqueue(heap_pq, (void *)6);
	HeapPQEnqueue(heap_pq, (void *)5);
	HeapPQEnqueue(heap_pq, (void *)43613);
	HeapPQEnqueue(heap_pq, (void *)1346);
	HeapPQEnqueue(heap_pq, (void *)1346);
	HeapPQEnqueue(heap_pq, (void *)1346);
	HeapPQEnqueue(heap_pq, (void *)137);
	HeapPQEnqueue(heap_pq, (void *)1347);
	HeapPQEnqueue(heap_pq, (void *)137);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)1);
	HeapPQEnqueue(heap_pq, (void *)13);
	HeapPQEnqueue(heap_pq, (void *)11375);
	HeapPQEnqueue(heap_pq, (void *)1357);
	HeapPQEnqueue(heap_pq, (void *)13571357);
	HeapPQEnqueue(heap_pq, (void *)1537);
	HeapPQEnqueue(heap_pq, (void *)13571357);
	HeapPQEnqueue(heap_pq, (void *)13513571);
	HeapPQEnqueue(heap_pq, (void *)46791);
	HeapPQEnqueue(heap_pq, (void *)1578);
	HeapPQEnqueue(heap_pq, (void *)15689);
	HeapPQEnqueue(heap_pq, (void *)14679);
	HeapPQEnqueue(heap_pq, (void *)4671);
	HeapPQEnqueue(heap_pq, (void *)2451);
	HeapPQEnqueue(heap_pq, (void *)24571);
	HeapPQEnqueue(heap_pq, (void *)24571);
	HeapPQEnqueue(heap_pq, (void *)24571);
	HeapPQEnqueue(heap_pq, (void *)2451);
	HeapPQEnqueue(heap_pq, (void *)1245);
	HeapPQEnqueue(heap_pq, (void *)245724571);
	HeapPQEnqueue(heap_pq, (void *)2451);
	HeapPQEnqueue(heap_pq, (void *)24571);
	HeapPQEnqueue(heap_pq, (void *)12457);
	HeapPQEnqueue(heap_pq, (void *)3461);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)1457);
	HeapPQEnqueue(heap_pq, (void *)14574);
	HeapPQEnqueue(heap_pq, (void *)125);
	HeapPQEnqueue(heap_pq, (void *)1257);
	HeapPQEnqueue(heap_pq, (void *)12475);
	HeapPQEnqueue(heap_pq, (void *)135);
	HeapPQEnqueue(heap_pq, (void *)1357);
	HeapPQEnqueue(heap_pq, (void *)14679);
	HeapPQEnqueue(heap_pq, (void *)197);
	HeapPQEnqueue(heap_pq, (void *)1479);
	HeapPQEnqueue(heap_pq, (void *)14679);
	HeapPQEnqueue(heap_pq, (void *)1479);
	HeapPQEnqueue(heap_pq, (void *)14679);
	HeapPQEnqueue(heap_pq, (void *)14679);

	assert(0 == HeapPQIsEmpty(heap_pq));
	assert(0 != HeapPQSize(heap_pq));
	HeapPQClear(heap_pq);
	HeapPQClear(heap_pq);
	assert(1 == HeapPQIsEmpty(heap_pq));
	assert(0 == HeapPQSize(heap_pq));
	HeapPQDestroy(heap_pq);
}
/*****************************************************************************/