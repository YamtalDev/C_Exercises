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

    writer: Tal Aharon

    reviewer: No one.

    date : 19.04.2023

    Description:

******************************************************************************/
#include <stdlib.h>  /* rand           */
#include <assert.h>  /* assert         */
#include <stddef.h>  /* size_t, NULL   */
#include <stdio.h>   /* printf, puts   */
#include <time.h>    /* clock, clock_t */

#include "comparison_sort.h"

void BubbleSortTest(void);
void SelectionSortTest(void);
void InsertionSortTest(void);
int cmpfunc(const void * x, const void * y);

/*****************************************************************************/
int main(void)
{
	BubbleSortTest();
	puts("\nBubbleSortTest() : passed.\n\n-----------------------------------");
	SelectionSortTest();
	puts("\nSelectionSortTest() : passed.\n\n-----------------------------------");
	InsertionSortTest();
	puts("\nInsertionSortTest() : passed.\n\n-----------------------------------");
	return (0);
}
/*****************************************************************************/
void BubbleSortTest(void)
{
	clock_t t;
	clock_t qt;
	size_t i = 0;
	int array[5000];
	int qarray[5000];
	size_t size = 5000;
	double time_taken = 0;
	double qtime_taken = 0;

	for(; i < size; ++i)
	{
		array[i] = rand();
		qarray[i] = rand();
	}

	qt = clock();
	qsort(qarray, size, sizeof(array[0]), cmpfunc);
	qt = clock() - qt;

	t = clock();
	BubbleSort(array, size);
	t = clock() - t;

	for(i = 0; i < (size - 1); ++i)
	{
		assert(array[i] <= array[i + 1]);
	}

	time_taken = ((double)t)/CLOCKS_PER_SEC;
	qtime_taken = ((double)qt)/CLOCKS_PER_SEC;
	printf("\nBubbleSort: %.4f, qsort: %.4f. qsort is %.0f times faster.\n", time_taken, qtime_taken, time_taken / qtime_taken);

	return;
}
/*****************************************************************************/
void SelectionSortTest(void)
{
	clock_t t;
	clock_t qt;
	size_t i = 0;
	int array[5000];
	int qarray[5000];
	size_t size = 5000;
	double time_taken = 0;
	double qtime_taken = 0;

	for(; i < size; ++i)
	{
		array[i] = rand();
		qarray[i] = rand();
	}

	qt = clock();
	qsort(qarray, size, sizeof(array[0]), cmpfunc);
	qt = clock() - qt;

	t = clock();
	SelectionSort(array, size);
	t = clock() - t;

	for(i = 0; i < (size - 1); ++i)
	{
		assert(array[i] <= array[i + 1]);
	}

	time_taken = ((double)t)/CLOCKS_PER_SEC;
	qtime_taken = ((double)qt)/CLOCKS_PER_SEC;
	printf("\nSelectionSort: %.4f, qsort: %.4f. qsort is %.0f times faster.\n", time_taken, qtime_taken, time_taken / qtime_taken);

	return;
}
/*****************************************************************************/
void InsertionSortTest(void)
{
	clock_t t;
	clock_t qt;
	size_t i = 0;
	int array[5000];
	int qarray[5000];
	size_t size = 5000;
	double time_taken = 0;
	double qtime_taken = 0;

	for(; i < size; ++i)
	{
		array[i] = rand();
		qarray[i] = rand();
	}

	qt = clock();
	qsort(qarray, size, sizeof(array[0]), cmpfunc);
	qt = clock() - qt;

	t = clock();
	InsertionSort(array, size);
	t = clock() - t;

	for(i = 0; i < (size - 1); ++i)
	{
		assert(array[i] <= array[i + 1]);
	}

	time_taken = ((double)t)/CLOCKS_PER_SEC;
	qtime_taken = ((double)qt)/CLOCKS_PER_SEC;
	printf("\nInsertionSort: %.4f, qsort: %.4f. qsort is %.0f times faster.\n", time_taken, qtime_taken, time_taken / qtime_taken);

	return;
}
/*****************************************************************************/
int cmpfunc(const void * x, const void * y)
{
	return (*(int *)x - *(int *)y);
}
