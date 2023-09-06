/******************************************************************************

    writer: Tal Aharon

    reviewer: No one.

    date : 20.04.2023

    Description: Linear sorting algorithms Counting and redix.

******************************************************************************/
#include <stdio.h>            /* printf, puts */
#include <stdlib.h>           /* malloc, free */
#include <assert.h>           /* assert       */

#include "linear_sort.h"      /* Internal use */

/*****************************************************************************/
#define SUCCESS (0)
#define FAILURE (1)
static int CountingSortForRadix(int array[], int size, int exp);
/*****************************************************************************/
int CountingSort(int array[], int size)
{
	int range = 0;
	int* count = NULL;
	int min = array[0];
	int max = array[0];
	int i = 1, j = 0, k = 0;

	for(; i < size; ++i)
	{
		if(array[i] > max)
		{
			max = array[i];
		}

		if(array[i] < min)
		{
			min = array[i];
		}
	}

	range = max - min + 1;
	count = calloc(range, sizeof(int));
	if(count == NULL)
	{
		return (FAILURE);
	}

	for(i = 0; i < size; ++i)
	{
		++count[array[i] - min];
	}

	for(i = min, k = 0; i <= max; ++i)
	{
		for(j = 0; j < count[i - min]; ++j)
		{
			array[k++] = i;
		}
	}

	free(count);
	return (SUCCESS);
}
/*****************************************************************************/ 
int RadixSort(int array[], int size)
{
	int i = 0;
	int exp = 1;
	int max = 0;
	for(; i < size; ++i)
	{
		if(array[i] > max)
		{
			max = array[i];
		}
	}

	for(; (max / exp) > 0; exp *= 10)
	{
		if(CountingSortForRadix(array, size, exp))
		{
			return (1);
		}
	}

	return (0);
}
/*****************************************************************************/
static int CountingSortForRadix(int array[], int size, int exp)
{
	int i = 0;
	int *sorted = NULL;
	int range = 10;
	int count[10] = {0};
	sorted = (int *)malloc(sizeof(array[0]) * size);
	if(NULL == sorted)
	{
		return (1);
	}

	for(i = 0; i < size; ++count[((array[i] / exp) % 10)], ++i);
	for(i = 1; i < range; count[i] += count[i - 1], ++i);

	for(i = size -1; 0 <= i; --i)
	{
		sorted[count[((array[i] / exp) % 10)] - 1] = array[i];
		--count[((array[i] / exp) % 10)];
	}

	for(i = 0; i < size; array[i] = sorted[i], ++i);

	free(sorted);
	sorted = NULL;
	return (0);
}
/*****************************************************************************/
