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

    date : 20.04.2023

    Description: Linear sort algorithms.

******************************************************************************/
#include <stdlib.h>        /* rand           */
#include <stdio.h>         /* printf         */
#include <assert.h>        /* assert         */
#include <time.h>          /* clock, clock_t */

#include "linear_sort.h"   /* API            */
/*****************************************************************************/
void RadixSortTest(void);
void CountingSortTest(void);
int cmpfunc(const void * x, const void * y);
/*****************************************************************************/
int main(void)
{
	CountingSortTest();
	puts("\nCountingSortTest() : passed.\n\n---------------------------------");
	RadixSortTest();
	puts("\nRadixSortTest() : passed.\n\n---------------------------------");
	return (0);
}
/*****************************************************************************/
void CountingSortTest(void)
{
	clock_t t;
	clock_t qt;
	int i = 0;
	int array[5000];
	int qarray[5000];
	int size = 5000;
	double time_taken = 0;
	double qtime_taken = 0;

	for(; i < size; ++i)
	{
		array[i] = (rand() % 2000) - 1000;
		qarray[i] = (rand() % 2000) - 1000;
	}

	qt = clock();
	qsort(qarray, size, sizeof(array[0]), cmpfunc);
	qt = clock() - qt;

	t = clock();
	CountingSort(array, size);
	t = clock() - t;

	for(i = 0; i < (size - 1); ++i)
	{
		assert(array[i] <= array[i + 1]);
	}

	time_taken = ((double)t)/CLOCKS_PER_SEC;
	qtime_taken = ((double)qt)/CLOCKS_PER_SEC;
	printf("\nCountingSort: %.6f\n\nqsort: %.6f.",  time_taken, qtime_taken);
	printf("\n\nCountingSort is %.0f times faster.\n", qtime_taken / time_taken);
	printf("\nCountingSort clocks: %ld qsort clocks: %ld.\n", t, qt);

	return;
}
/*****************************************************************************/
void RadixSortTest(void)
{
	clock_t t;
	clock_t qt;
	int i = 0;
	int array[5000];
	int qarray[5000];
	int size = 5000;
	double time_taken = 0;
	double qtime_taken = 0;

	for(; i < size; ++i)
	{
		array[i] = (rand() % 10000000);
		qarray[i] = (rand() % 10000000); 
	}

	qt = clock();
	qsort(qarray, size, sizeof(array[0]), cmpfunc);
	qt = clock() - qt;

	t = clock();
	RadixSort(array, size);
	t = clock() - t;

	for(i = 0; i < (size - 1); ++i)
	{
		assert(array[i] <= array[i + 1]);
	}

	time_taken = ((double)t)/CLOCKS_PER_SEC;
	qtime_taken = ((double)qt)/CLOCKS_PER_SEC;
	printf("\nRadixSort: %.6f\n\nqsort: %.6f.",  time_taken, qtime_taken);
	printf("\n\nRadixSort is %.0f times faster.\n", qtime_taken / time_taken);
	printf("\nRadixSort clocks: %ld qsort clocks: %ld.\n", t, qt);

	return;
}
/*****************************************************************************/
int cmpfunc(const void * x, const void * y)
{
	return (*(int *)x - *(int *)y);
}
/*****************************************************************************/
