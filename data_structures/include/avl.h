
/*=============================================================================

                           Customer requirements:

===============================================================================

* No duplication of element in the avl.

* Using recursion solution to the binary search tree.

=============================================================================*/
#ifndef __AVL_H__
#define __AVL_H__

#include "dll.h"       /* Doubly linked list API */
#include <sys/types.h> /*         ssize_t        */

typedef struct avl avl_t;

typedef enum order
{
	PRE_ORDER = 0, IN_ORDER, POST_ORDER, NUMBER_OF_ORDERS
} order_t;
/******************************************************************************

 Return value specification for avl_compare_func_t: negative for new_data after 
 data, zero if equal, positive else. The param is to determine how to compare nodes. 

 Return value specification for avl_action_func_t: zero on success and non zero 
 on failure.

 *Important: avl_action_func_t - Can't reorder the tree. 

******************************************************************************/
typedef int (*avl_action_func_t)(void *data, void *arg);
typedef int (*avl_is_match_func_t)(void *data, void *param);
typedef int (*avl_compare_func_t)(void *data, void *new_data, void *param);
/******************************************************************************

Function: AVLCreate - Creating avl

Usage: avl_t *avl = AVLCreat(cmp, param)

Description: Creating avl and returning a pointer to it.

Arguments: cmp - pointer to a comparison function, param - input to compare.

Return value: pointer to avl, returns NULL in failure.

Time complexity: Worst : O(1).
Space complexity Worst: O(1). 

******************************************************************************/

avl_t *AVLCreate(avl_compare_func_t cmp, void *param);

/******************************************************************************

Function: AVLDestroy - Destroy the avl

Usage: AVLDestroy(avl)

Description: Clean-up AVL and all its nodes and delete it

Arguments: avl - pointer to the avl it self.

Return value: No return value.

Time complexity Worst: O(n).
Space complexity Worst: O(log(n)).

******************************************************************************/

void AVLDestroy(avl_t *avl);

/******************************************************************************

Function: AVLRemove - removes an element from the tree.

Usage: void *removed_node_data = AVLRemove(avl, data)

Description: removes an element from the avl.

Arguments: pointer to the avl it self, data to be used by the cmp 
           function to recognize the node to remove.

Return value: The data that was removed.

Time complexity amortized: O(log(n)).
Space complexity Worst: O(log(n)).

******************************************************************************/

void *AVLRemove(avl_t *avl, const void *data);

/******************************************************************************

Function: AVLInsert - Insert new data into the avl.

Usage: int status = AVLInsert(avl, data)

Description: Insertion by the comparison function.

Arguments: avl - pointer to the avl it self, data - the data to insert.

Return value: int - 0 on success, none zero on failure.

Time complexity amortized : O(log(n)).
Space complexity Worst: O(log(n)).

******************************************************************************/

int AVLInsert(avl_t *avl, const void *data);

/******************************************************************************

Function: AVLHeight - Clculate the height of the tree.

Usage: size_t height = AVLHeight(avl)

Description: returns the height of the avl tree.

Arguments: avl - pointer to the avl it self.

Return value: The height of the tree.

Time complexity: O(1).
Space complexity Worst: O(1).

******************************************************************************/

size_t AVLHeight(const avl_t *avl);

/******************************************************************************

Function: AVLCount - Number of elements.

Usage: size_t size = AVLCount(avl)

Description: Counts the number of elements in the avl.

Arguments: avl - pointer to the avl it self.

Return value: size_t - number of elements.

Time complexity Worst: O(n).
Space complexity Worst: O(log(n)).

******************************************************************************/

size_t AVLCount(const avl_t *avl);

/******************************************************************************

Function: AVLIsEmpty - Checks if avl is empty. 

Usage: int status = AVLIsEmpty(avl)

Description: Checking whether the avl is empty.

Arguments: avl - pointer to the avl it self.

Return value: non-zero if is empty, zero if not.

Time complexity Worst: O(1).
Space complexity Worst: O(1).

******************************************************************************/

int AVLIsEmpty(const avl_t *avl);

/******************************************************************************

Function: AVLFind - Find an element iside the avl.

Usage: void *data_found = AVLFind(avl, data)

Description: Find an element with a specific data in the tree.

Arguments: avl - pointer to the avl it self, data - data that the element needs to have.

Return value: The data of the node found, if fails return pointer to the NULL.

Time complexity Worst: O(log(n)).
Space complexity Worst: O(log(n)).

******************************************************************************/

void *AVLFind(const avl_t *avl, const void *data);

/******************************************************************************

Function: AVLForEach - For each element the do somthing.

Usage: int status = AVLForEach(avl, act, param)

Description: For each element in the avl the function act will be preformed.

Arguments: avl - pointer to the avl it self, act - pointer to user defined function,
           param - the data to be inserted to the user function, order - The order.

Return value: On success returns 0, if fails returns the value of the user defined function.

Time complexity Worst: O(n).
Space complexity Worst: O(log(n)).

******************************************************************************/

int AVLForEach(avl_t *avl, avl_action_func_t act, void *arg, order_t order);

/******************************************************************************

Function: MultiFind - Finds multiple nodes in the avl.

Usage: ssize_t number_of_nodes_found = MultiFind(avl, act, param)

Description: Find multiple nodes in the avl using recursion while counting the 
             nodes found and inserting them into the doubly linked list.

Arguments: avl - pointer to the avl it self, is_match - pointer to user defined 
           function, param - the data to be inserted to the user function, dll - 
           Doubly linked list to be a container to the found nodes.

Return value: ssize_t - the number of nodes found, failure - return negative value.

Time complexity Worst: O(n).
Space complexity Worst: O(log(n)).

******************************************************************************/

ssize_t MultiFind(const avl_t *avl, avl_is_match_func_t is_match, const void *param, dll_t *dll);

/******************************************************************************

Function: RemoveMultiple - Remove multiple nodes from the tree.

Usage: ssize_t number_of_nodes_removed = AVLForEach(avl, act, param)

Description: Remove the nodes found in the doubly linked list.

Arguments: avl - pointer to the avl it self, is_match - pointer to user defined 
           function, param - the data to be inserted to the user function, dll - 
           Doubly linked list containing the nodes to be delete.

Return value: ssize_t - the number of nodes deleted, failure - return negative value.

Time complexity Worst: O(n).
Space complexity Worst: O(log(n)).

******************************************************************************/

ssize_t RemoveMultiple(const avl_t *avl, avl_is_match_func_t is_match, const void *param, dll_t *dll);

/******************************************************************************/

#endif /* __AVL_H__ */
