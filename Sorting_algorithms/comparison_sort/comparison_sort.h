/*=============================================================================

                           Costumer requirements

===============================================================================

* Bubble sort, Selection sort and Insertion sort functions that sort integers.

===============================================================================

                     COMPARISON_SORT functionalities:

===============================================================================

1.) Sorting a list of integers.


==============================================================================*/

#ifndef __COMPARISON_SORT_H__
#define __COMPARISON_SORT_H__

#include <stddef.h> /* size_t */

/******************************************************************************
Function: BubbleSort - Sorting integers of array.

Usage: BubbleSort(array, size)

Description: This function uses the Bubble sorting algorithm.

Arguments: array - array of int, size - the size of the array.

Return value: the sorted array.

Complexity: Time complexity: O(n^2), Space complexity: O(1) */

void BubbleSort(int array[], size_t size);

/******************************************************************************
Function: SelectionSort - Sorting integers of array.

Usage: SelectionSort(array, size)

Description: This function uses the selection sorting algorithm.

Arguments: array - array of int, size - the size of the array.

Return value: the sorted array.

Complexity: Time complexity: O(n^2), Space complexity: O(1) */

void SelectionSort(int array[], size_t size);

/******************************************************************************
Function: InsertionSort - Sorting integers of array.

Usage: InsertionSort(array, size)

Description: This function uses the insertion sorting algorithm.

Arguments: array - array of int, size - the size of the array.

Return value: the sorted array.

Complexity: Time complexity: O(n^2), Space complexity: O(1) */

void InsertionSort(int array[], size_t size);

/*****************************************************************************/

#endif /* __COMPARISON_SORT_H__ */
