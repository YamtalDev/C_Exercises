/*=============================================================================

                           Costumer requirements

===============================================================================

* RadixSort, CountingSort functions that sort integers.

===============================================================================

                     COMPARISON_SORT functionalities:

===============================================================================

1.) Linear sorting of a list of integers.

==============================================================================*/

#ifndef __LINEAR_SORT_H__
#define __LINEAR_SORT_H__

/******************************************************************************
Function: CountingSort - Sorting integers of array.

Usage: CountingSort(array,size)

Description: This function uses the Counting linear algorithm.

Arguments: array - array of int, size - the size of the array.

Return value: 1 on failure and 0 on success.

Complexity: Time complexity: O(n), Auxiliary space complexity: O(n + k) */

int CountingSort(int array[], int size);

/******************************************************************************
Function: RadixSort - Sorting integers of array.

Usage: RadixSort(array,size)

Description: This function uses the linear Radix algorithm.

Arguments: array - array of int, size - the size of the array.

Return value:  1 on failure and 0 on success.

Complexity: Time complexity: O(n + k), Auxiliary space complexity: O(n + k) */

int RadixSort(int array[], int size);

/*****************************************************************************/

#endif /* __LINEAR_SORT_H__ */
