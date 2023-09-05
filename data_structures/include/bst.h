/*=============================================================================

                           Costumer requirements:

===============================================================================

* No duplication of element in the bst.

* No recursion is used in the implementation.

* Using iterative solution to the binary search tree.

=============================================================================*/

#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /* size_t */

typedef struct bst bst_t;
typedef struct bst_node *bst_iter_t;

/* Return value specification: negative for new_data after data, zero if equal, positive else.
   The param is to determine how to compare */
   
typedef int (*bst_compare_func_t)(void *data, void *new_data, void *param);

/* Important: Can't reorder the tree. */
typedef int (*bst_action_func_t)(void *data, void *param);

/******************************************************************************
Function: BSTCreate - Creating BST

Usage: bst_t *bst = BSTCreat(cmp, param)

Description: Creating bst and returning a pointer to it.

Arguments: cmp - pointer to a comparison function, param - input to compare.

Return value: pointer to bst, returns NULL in failure.

Time complexity: Worst : O(1).
Space complexity Worst: O(1). */

bst_t *BSTCreate(bst_compare_func_t cmp, void *param);

/******************************************************************************
Function: BSTDestroy - Destroy the BST

Usage: BSTDestroy(bst)

Description: Clean-up The BTS and delete it

Arguments: bst - pointer to the bst it self.

Return value: No return value.

Time complexity Worst: O(n).
Space complexity Worst: O(1). */

void BSTDestroy(bst_t *bst);

/******************************************************************************
Function: BSTInsert - Insert new data into the bst.

Usage: bst_iter_t element = BSTInsert(bst, data)

Description: Insertion by the comparison function.

Arguments: bst - pointer to the bst it self, data - the data to insert.

Return value: iterator to the new element inserted. If fails return non-valid iterator (BSTEnd).

Time complexity Worst: O(n), Avarage: O(log(n)).
Space complexity Worst: O(1). */

bst_iter_t BSTInsert(bst_t *bst, void *data);

/******************************************************************************
Function: BSTRemove - removes an element from the tree.

Usage: BSTRemove(iterator)

Description: removes an element from the bst.

Arguments: iterator to the element to remove.

Return value: The data that was removed.

Time complexity Amortized: O(1).
Space complexity Worst: O(1). */

void *BSTRemove(bst_iter_t iter);

/******************************************************************************
Function: BSTCount - Number of elements.

Usage: size_t count = BSTCount(bst)

Description: Counts the number of elements in the bst.

Arguments: bst - pointer to the bst it self.

Return value: size_t - number of elements.

Time complexity Worst: O(n).
Space complexity Worst: O(1).*/

size_t BSTCount(bst_t *bst);

/******************************************************************************
Function: BSTIsEmpty - Checks if bst is empty. 

Usage: int status = BSTIsEmpty(bst)

Description: Checking whether the bst is empty.

Arguments: bst - pointer to the bst it self.

Return value: non-zero if is empty, zero if not.

Time complexity Worst: O(1).
Space complexity Worst: O(1). */

int BSTIsEmpty(const bst_t *bst);

/******************************************************************************
Function: BSTIsIterEqual - Compares 2 iterators.

Usage: int status = BSTIsIterEqual(iter1, iter2)

Description: Checking whether iter1 is equal to iter2.

Arguments: iter1 - element in the bst, iter2 - element in the bst.

Return value: non-zero if is equal, zero if not.

Time complexity Worst: O(1).
Space complexity Worst: O(1). */

int BSTIsIterEqual(bst_iter_t iter1, bst_iter_t iter2);

/******************************************************************************
Function: BSTFind - Find an element iside the bst.

Usage: bst_iter_t element = BSTFind(bst, data)

Description: Find an element with a specific data in the tree.

Arguments: bst - pointer to the bst it self, data - data that the element needs to have.

Return value: iterator to the element found, if fails return non-valid iterator (BSTEnd).

Time complexity Worst: O(n).
Space complexity Worst: O(1). */

bst_iter_t BSTFind(const bst_t *bst, void *data);

/******************************************************************************
Function: BSTBegin - Begining of tree.

Usage: bst_iter_t begin = BSTBegin(bst)

Description: returns an iterator to the first element.

Arguments: bst - pointer to the bst it self.

Return value: Iterator to the begining.

Time complexity Worst: O(n), Avarage: O(log(n)).
Space complexity Worst: O(1). */

bst_iter_t BSTBegin(const bst_t *bst);

/******************************************************************************
Function: BSTEnd - End of the bst.

Usage: bst_iter_t end = BSTEnd(bst)

Description: returns an iterator to the end of the bst.

Arguments: bst - pointer to the bst it self.

Return value: iterator to the end of the bst (non-valid iterator).

Time complexity Worst: O(1).
Space complexity Worst: O(1). */

bst_iter_t BSTEnd(const bst_t *bst);

/******************************************************************************
Function: BSTPrev - previous element.

Usage: bst_iter_t prev = BSTPrev(iterator)

Description: get the previous element from the iterator that was given.

Arguments: iter - iterator to the bst element.

Return value: the previous element, if iter is the begining of the bst, it's undefined behavior.

Time complexity Amortized: O(1).
Space complexity Worst: O(1). */

bst_iter_t BSTPrev(bst_iter_t iter);

/******************************************************************************
Function: BSTNext - Next element.

Usage: bst_iter_t next = BSTNext(iterator)

Description: get the next element to the iterator that was given.

Arguments: iter - iterator to the bst element.

Return value: the next element, if iterator is the end of bst, it's undefined behavior.

Time complexity Amortized: O(1).
Space complexity Worst: O(1). */

bst_iter_t BSTNext(bst_iter_t iter);

/******************************************************************************
Function: BSTGetData - Data element.

Usage: void *data = BSTGetData(iterator)

Description: get the data of element.

Arguments: iter - iterator to the bst element.

Return value: the data of element. if iterator is the end of bst, it's undefined behavior.

Time complexity Worst: O(1).
Space complexity Worst: O(1). */

void *BSTGetData(bst_iter_t iter);

/******************************************************************************
Function: BSTForEach - For each element the do somthing.

Usage: int status = BSTForEach(bst, act, param)

Description: For each element in the bst the function act will be preformed.

Arguments: bst - pointer to the bst it self, act - pointer to user defined function,
           param - the data to be inserted to the user function.

Return value: ON success returns 0, if fails returns the value of the user defined function.

Time complexity Worst: O(n).
Space complexity Worst: O(1). */

int BSTForEach(bst_t *bst, bst_action_func_t act, void *param);

/******************************************************************************/

#endif /* __BST_H__ */
