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

    Reviewer: Ravit Yahud.

    Date: 14.05.2023

*******************************************************************************

                            Description:

  This C program includes test functions for a heap data structure implementation. 
  It performs tests for creating and destroying a heap, pushing elements into the 
  heap, popping elements from the heap, removing specific elements from the heap, 
  peeking at the top element of the heap, determining the size of the heap, and 
  checking if the heap is empty. The program utilizes assertions to verify the 
  expected behavior of the heap functions.

******************************************************************************/
#include <assert.h>  /* assert         */
#include <stdio.h>   /* puts           */
#include <stdlib.h>  /* rand, qsort    */
#include <time.h>    /* clock, clock_t */

#include "heap.h"    /* Internal API   */
/*****************************************************************************/
#define MAX_ARRAY_SIZE (1000000)
void HeapPopTest(void);
void HeapSortTest(void);
void HeapPeekTest(void);
void HeapSizeTest(void);
void HeapPushTest(void);
void HeapRemoveTest(void);
void HeapIsEmptyTest(void);
void HeapCreateDestroyTest(void);
int Cmp(const void *, const void *);
int Match(const void *, const void *);
int cmpfunc(const void *, const void *);
/*****************************************************************************/
int main(void)
{
	HeapCreateDestroyTest();
	puts("\nHeapCreateDestroyTest() : passed.");
	HeapPushTest();
	puts("\nHeapPushTest() : passed.");
	HeapPopTest();
	puts("\nHeapPopTest() : passed.");
	HeapRemoveTest();
	puts("\nHeapRemoveTest() : passed.");
	HeapPeekTest();
	puts("\nHeapPeekTest() : passed.");
	HeapSizeTest();
	puts("\nHeapSizeTest() : passed.");
	HeapIsEmptyTest();
	puts("\nHeapIsEmptyTest() : passed.");
    HeapSortTest();
    return (0);
}
/*****************************************************************************/
void HeapCreateDestroyTest(void)
{
	heap_t *heap = NULL;
    assert((heap = HeapCreate(Cmp)));
    HeapDestroy(heap);
}
/*****************************************************************************/
void HeapPushTest(void)
{
    heap_t *heap = NULL;
    assert((heap = HeapCreate(Cmp)));
    assert(SUCCESS == HeapPush(heap, (void *)90));
    assert(SUCCESS == HeapPush(heap, (void *)89));
    assert(SUCCESS == HeapPush(heap, (void *)70));
    assert(SUCCESS == HeapPush(heap, (void *)65));
    assert(SUCCESS == HeapPush(heap, (void *)63));
    assert(SUCCESS == HeapPush(heap, (void *)75));
    assert(SUCCESS == HeapPush(heap, (void *)36));
    assert(SUCCESS == HeapPush(heap, (void *)21));
    assert(SUCCESS == HeapPush(heap, (void *)18));
    assert(SUCCESS == HeapPush(heap, (void *)15));
    HeapDestroy(heap);
}
/*****************************************************************************/
void HeapPopTest(void)
{
    heap_t *heap = NULL;
    assert((heap = HeapCreate(Cmp)));
    assert(SUCCESS == HeapPush(heap, (void *)90));
    assert(SUCCESS == HeapPush(heap, (void *)89));
    assert(SUCCESS == HeapPush(heap, (void *)70));
    assert(SUCCESS == HeapPush(heap, (void *)65));
    assert(SUCCESS == HeapPush(heap, (void *)63));
    assert(SUCCESS == HeapPush(heap, (void *)75));
    assert(SUCCESS == HeapPush(heap, (void *)36));
    assert(SUCCESS == HeapPush(heap, (void *)21));
    assert(SUCCESS == HeapPush(heap, (void *)18));
    assert(SUCCESS == HeapPush(heap, (void *)15));

    assert(90 == (size_t)HeapPop(heap));
    assert(89 == (size_t)HeapPop(heap));
    assert(75 == (size_t)HeapPop(heap));
    assert(70 == (size_t)HeapPop(heap));
    assert(65 == (size_t)HeapPop(heap));
    assert(63 == (size_t)HeapPop(heap));
    assert(36 == (size_t)HeapPop(heap));
    assert(21 == (size_t)HeapPop(heap));
    assert(18 == (size_t)HeapPop(heap));
    assert(15 == (size_t)HeapPop(heap));
    assert(NULL == HeapPop(heap));

    HeapDestroy(heap);
}
/*****************************************************************************/
void HeapRemoveTest(void)
{
    heap_t *heap = NULL;
    assert((heap = HeapCreate(Cmp)));
    assert(SUCCESS == HeapPush(heap, (void *)90));
    assert(SUCCESS == HeapPush(heap, (void *)89));
    assert(SUCCESS == HeapPush(heap, (void *)70));
    assert(SUCCESS == HeapPush(heap, (void *)65));
    assert(SUCCESS == HeapPush(heap, (void *)63));
    assert(SUCCESS == HeapPush(heap, (void *)75));
    assert(SUCCESS == HeapPush(heap, (void *)36));
    assert(SUCCESS == HeapPush(heap, (void *)21));
    assert(SUCCESS == HeapPush(heap, (void *)18));
    assert(SUCCESS == HeapPush(heap, (void *)15));

    assert(90 == (size_t)HeapRemove(heap, (void *)90, Match));
    assert(89 == (size_t)HeapRemove(heap, (void *)89, Match));
    assert(70 == (size_t)HeapRemove(heap, (void *)70, Match));
    assert(65 == (size_t)HeapRemove(heap, (void *)65, Match));
    assert(63 == (size_t)HeapRemove(heap, (void *)63, Match));
    assert(75 == (size_t)HeapRemove(heap, (void *)75, Match));
    assert(36 == (size_t)HeapRemove(heap, (void *)36, Match));
    assert(21 == (size_t)HeapRemove(heap, (void *)21, Match));
    assert(18 == (size_t)HeapRemove(heap, (void *)18, Match));
    assert(15 == (size_t)HeapRemove(heap, (void *)15, Match));
    assert(NULL == HeapRemove(heap, (void *)15, Match));
    assert(HeapIsEmpty(heap));
    HeapDestroy(heap);
}
/*****************************************************************************/
void HeapPeekTest(void)
{
    heap_t *heap = NULL;
    assert((heap = HeapCreate(Cmp)));
    assert(SUCCESS == HeapPush(heap, (void *)90));
    assert(90 == (size_t)HeapPeek(heap));
    assert(SUCCESS == HeapPush(heap, (void *)89));
    assert(89 != (size_t)HeapPeek(heap));
    assert(SUCCESS == HeapPush(heap, (void *)70));
    assert(SUCCESS == HeapPush(heap, (void *)65));
    assert(SUCCESS == HeapPush(heap, (void *)63));
    assert(SUCCESS == HeapPush(heap, (void *)75));
    assert(SUCCESS == HeapPush(heap, (void *)36));
    assert(SUCCESS == HeapPush(heap, (void *)21));
    assert(SUCCESS == HeapPush(heap, (void *)18));
    assert(SUCCESS == HeapPush(heap, (void *)15));

    assert(90 == (size_t)HeapPop(heap));
    assert(89 == (size_t)HeapPeek(heap));
    assert(89 == (size_t)HeapPop(heap));
    assert(75 == (size_t)HeapPeek(heap));
    assert(75 == (size_t)HeapPop(heap));
    assert(70 == (size_t)HeapPeek(heap));
    assert(70 == (size_t)HeapPop(heap));
    assert(65 == (size_t)HeapPeek(heap));
    assert(65 == (size_t)HeapPop(heap));
    assert(63 == (size_t)HeapPeek(heap));
    assert(63 == (size_t)HeapPop(heap));
    assert(36 == (size_t)HeapPeek(heap));
    assert(36 == (size_t)HeapPop(heap));
    assert(21 == (size_t)HeapPeek(heap));
    assert(21 == (size_t)HeapPop(heap));
    assert(18 == (size_t)HeapPeek(heap));
    assert(18 == (size_t)HeapPop(heap));
    assert(15 == (size_t)HeapPeek(heap));
    assert(15 == (size_t)HeapPop(heap));
    assert(NULL == HeapPeek(heap));

    HeapDestroy(heap);
}
/*****************************************************************************/
void HeapSizeTest(void)
{
    heap_t *heap = NULL;
    assert((heap = HeapCreate(Cmp)));
    assert(0 == HeapSize(heap));
    assert(SUCCESS == HeapPush(heap, (void *)90));
    assert(1 == HeapSize(heap));
    assert(SUCCESS == HeapPush(heap, (void *)89));
    assert(2 == HeapSize(heap));
    assert(SUCCESS == HeapPush(heap, (void *)70));
    assert(3 == HeapSize(heap));
    assert(SUCCESS == HeapPush(heap, (void *)65));
    assert(4 == HeapSize(heap));
    assert(SUCCESS == HeapPush(heap, (void *)63));
    assert(5 == HeapSize(heap));
    assert(SUCCESS == HeapPush(heap, (void *)75));
    assert(6 == HeapSize(heap));
    assert(SUCCESS == HeapPush(heap, (void *)36));
    assert(7 == HeapSize(heap));
    assert(SUCCESS == HeapPush(heap, (void *)21));
    assert(8 == HeapSize(heap));
    assert(SUCCESS == HeapPush(heap, (void *)18));
    assert(9 == HeapSize(heap));
    assert(SUCCESS == HeapPush(heap, (void *)15));
    assert(10 == HeapSize(heap));

    assert(90 == (size_t)HeapPop(heap));
    assert(9 == HeapSize(heap));
    assert(89 == (size_t)HeapPop(heap));
    assert(8 == HeapSize(heap));
    assert(75 == (size_t)HeapPop(heap));
    assert(7 == HeapSize(heap));
    assert(70 == (size_t)HeapPop(heap));
    assert(6 == HeapSize(heap));
    assert(65 == (size_t)HeapPop(heap));
    assert(5 == HeapSize(heap));
    assert(63 == (size_t)HeapPop(heap));
    assert(4 == HeapSize(heap));
    assert(36 == (size_t)HeapPop(heap));
    assert(3 == HeapSize(heap));
    assert(21 == (size_t)HeapPop(heap));
    assert(2 == HeapSize(heap));
    assert(18 == (size_t)HeapPop(heap));
    assert(1 == HeapSize(heap));
    assert(15 == (size_t)HeapPop(heap));
    assert(0 == HeapSize(heap));

    HeapDestroy(heap);
}
/*****************************************************************************/
void HeapIsEmptyTest(void)
{
    heap_t *heap = NULL;
    assert((heap = HeapCreate(Cmp)));
    assert(HeapIsEmpty(heap));
    assert(SUCCESS == HeapPush(heap, (void *)90));
    assert(!HeapIsEmpty(heap));
    assert(90 == (size_t)HeapPop(heap));
    assert(HeapIsEmpty(heap));
    HeapDestroy(heap);
}
/*****************************************************************************/
void HeapSortTest(void)
{
    int i = 0;
    clock_t t;
    clock_t qt;
    double time_taken = 0;
    double qtime_taken = 0;
    int array[MAX_ARRAY_SIZE];
    int qarray[MAX_ARRAY_SIZE];

    for(; i < MAX_ARRAY_SIZE; ++i)
    {
        array[i] = (rand() % 2000) - 1000;
        qarray[i] = (rand() % 2000) - 1000;
    }

    qt = clock();
    qsort(qarray, MAX_ARRAY_SIZE, sizeof(array[0]), cmpfunc);
    qt = clock() - qt;

    t = clock();
    HeapSort(array, MAX_ARRAY_SIZE);
    t = clock() - t;

    for(i = 0; i < (MAX_ARRAY_SIZE - 1); ++i)
    {
        assert(array[i] <= array[i + 1]);
    }

    time_taken = ((double)t)/CLOCKS_PER_SEC;
    qtime_taken = ((double)qt)/CLOCKS_PER_SEC;
    printf("\nHeapSort: %.6f\n\nqsort: %.6f.",  time_taken, qtime_taken);
    printf("\n\nqsort is %.0f times faster.\n", time_taken / qtime_taken);
    printf("\nMergeSort clocks: %ld qsort clocks: %ld.\n", t, qt);
}
/*****************************************************************************/
int Cmp(const void *arg1, const void *arg2)
{
    return ((size_t)arg2 - (size_t)arg1);
}
/*****************************************************************************/
int Match(const void *arg1, const void *arg2)
{
    return ((size_t)arg1 == (size_t)arg2);
}
/*****************************************************************************/
int cmpfunc(const void *arg1, const void *arg2)
{
    return (*(int *)arg1 - *(int *)arg2);
}
/*****************************************************************************/

