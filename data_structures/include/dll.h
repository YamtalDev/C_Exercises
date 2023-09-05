#ifndef __DLL_H__
#define __DLL_H__


#include <stddef.h>   /*size_t */


typedef struct dll_node *dll_iter_t;

typedef struct dll dll_t;

typedef int (*dll_act_func_t) (void *data, void * param);
 
typedef int (*dll_cmp_func_t) (void *data, void *param);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Creation of a list, if creation fails it will return NULL */

dll_t *DLLCreate(void);

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Delete the list. */

void DLLDestroy(dll_t *dll);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Inserts node next with data in the current position of the iterator.
   If the insertion will fail the function will return end of list */

dll_iter_t DLLInsertAfter(dll_iter_t iterator, void *data);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Inserts node with data in the previous position of the iterator.
   If the insertion will fail the function will return end of list */

dll_iter_t DLLInsertBefore(dll_iter_t iterator, void *data);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Removes node that iterator points to. 
   return Next iterator. undefined behavior on EOL */

dll_iter_t DLLRemove(dll_iter_t iteretor);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
	Push Back Data to Dll, return end of list if fail */

dll_iter_t DLLPushBack(dll_t *dll, void *data);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
	Push Front Data to Dll, return end of list if fail */

dll_iter_t DLLPushFront(dll_t *dll, void *data);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
	Pop Back Data to Dll. return data */

void *DLLPopBack(dll_t *dll);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
	Pop Front Data to Dll return data */

void *DLLPopFront(dll_t *dll);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Sets data at a specific node pointed by iterator. */

void DLLSetData(dll_iter_t iterator, void *data);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Get specific data from a specific node if list is empty will be
   undefined behavior. */

void *DLLGetData(const dll_iter_t iterator);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Returns iterator pointing to the start of the list. */

dll_iter_t DLLBegin(const dll_t *dll);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Returns iterator pointing to the end of the list. */

dll_iter_t DLLEnd(const dll_t *dll);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Return the next iterator. If the iterator is the end it is 
   undefined behavior. */

dll_iter_t DLLNext(const dll_iter_t iterator);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Return the previous iterator. If the iterator is the beginning it is 
   undefined behavior. */

dll_iter_t DLLPrev(const dll_iter_t iterator);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Returns 1 if empty and 0 if not */

int DLLIsEmpty(const dll_t *dll);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Returns 1 if equal and 0 if not. Function comparing data at two iterators. */

int DLLIterIsEqual(const dll_iter_t iter1, const dll_iter_t iter2);

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Returns the number of nodes in the list. */

size_t DLLCount(const dll_t *dll);

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Action on every data element in node in a given range. Returns status 
   if success and if not return the status of action function 
   provided by the user. */

int DLLForEach(dll_iter_t from, const dll_iter_t to, dll_act_func_t act, void *param);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Cut and Paste nodes from src_from to src_to (not included) into dest */

void DLLSplice(dll_iter_t dest, dll_iter_t source_from, dll_iter_t source_to);

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Finds the iterator to the node with the same data as the input data after
   comparison function return true. */

dll_iter_t DLLFind(const dll_iter_t from, const dll_iter_t too, dll_cmp_func_t cmp, void *paramter);

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Finds the iterators to the node with the same data as the input data after
   comparison. push back the iterators to dest. return 0 if interator has not
   been found, negative int if allocation failed, positive number on succes*/

int DLLMultiFind(const dll_iter_t from, const dll_iter_t to, dll_cmp_func_t cmp, void *param, dll_t *dest);

/*****************************************************************************/

void DLLArrange(dll_t *dll, void *pivot);

#endif /* __DLL_H__ */
