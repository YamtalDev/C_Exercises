/******************************************************************************

    writer: Tal Aharon

    date : 19.04.2023

    Description: Sorting algorithms.

******************************************************************************/
#include <assert.h>               /* Assert       */
#include "comparison_sort.h"      /* Internal use */

static void Swap(int *x, int *y);
/*****************************************************************************/
void BubbleSort(int array[], size_t size)
{
	size_t i = 0;
	size_t j = 0;

	for(;i < (size - 1); ++i)
	{
		for(j = 0; j < (size - i -1); ++j)
		{
			if(array[j] > array[j + 1])
			{
				Swap(&array[j], &array[j +1]);
			}
		}
	}
}
/*****************************************************************************/ 
void SelectionSort(int array[], size_t size)
{
	size_t i = 0;
	size_t j = 0;
	size_t index = 0;

	for(;i < (size - 1); ++i)
	{
		index = i;
		for(j = i + 1; j < size; ++j)
		{
			if(array[j] < array[index])
			{
				index = j;
			}
		}

		if(index != i)
		{
			Swap(&array[i], &array[index]);
		}
	}

	return;
}
/*****************************************************************************/ 
void InsertionSort(int array[], size_t size)
{
	int tmp = 0;
	size_t i = 1;
	long int j = 0;

	for(;i < size; ++i)
	{
		tmp = array[i];
		j = i - 1;
		while(0 <= j && (array[j] > tmp))
		{
			array[j + 1] = array[j];
			--j;
		}

		array[j + 1] = tmp;
	}

	return;
}
/*****************************************************************************/ 
static void Swap(int *x, int *y)
{
	*x = *x ^ *y;
	*y = *y ^ *x;
	*x = *x ^ *y;
}
