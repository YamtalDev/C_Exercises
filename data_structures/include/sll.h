/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: Artemy Ozerski            ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    date: 08.03.2023                    ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀
******************************************************************************/
#ifndef __SLL_H__
#define __SLL_H__

#include <stddef.h>   /*size_t */

typedef struct sll_node *sll_iter_t;

typedef struct list sll_t;

typedef int (*sll_action_func_t) (void *data, void * paramter);
 
typedef int (*sll_compare_func_t) (void *data, void *paramter);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Creation of a list, if creation fails it will return NULL */

sll_t *SLLCreate(void);

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Delete the list. */

void SLLDestroy(sll_t *list);

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Returns the number of nodes in the list. */

size_t SLLCount(const sll_t *list);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Returns iterator pointing to the end of the list. */

sll_iter_t SLLEnd(const sll_t *list);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Returns iterator pointing to the start of the list. */

sll_iter_t SLLBegin(const sll_t *list);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Returns 1 if empty and 0 if not */

int SLLIsEmpty(const sll_t *list);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Returns 1 if equal and 0 if not. Function comparing iterators. */

int SLLIterIsEqual(const sll_iter_t iteretor1,const  sll_iter_t iteretor2);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Sets data at a specific node pointed by iterator. */

void SLLSetData(sll_iter_t iteretor, void *data);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Get specific data from a specific node if list is empty will be
   undefined behavior. */

void *SLLGetData(const sll_iter_t iteretor);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Removes node that iterator points to. */

void SLLRemove(sll_iter_t iteretor);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Return the next iterator. If the iterator is the end it is 
   undefined behavior. */

sll_iter_t SLLNext(const sll_iter_t iterator);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Inserts node with data in the current position of the iterator.
   If the insertion will fail the function will return NULL */

sll_iter_t SLLInsert(sll_iter_t iterator, void *data);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Append two lists to destination. The source will be empty after appending. */

void SLLAppend(sll_t *dest, sll_t *source);

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Finds the iterator to the node with the same data as the input data after
   comparison function return true. Exit if fails. */

sll_iter_t SLLFind(sll_iter_t from, sll_iter_t to, sll_compare_func_t cmp, void *paramter);

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Action on every data element in node in a given range. Returns status 
   if success and if not return the status of action function 
   provided by the user. */

int SLLForEach(sll_iter_t from, sll_iter_t to, sll_action_func_t action, void *paramter);

/*****************************************************************************/

#endif /* __SLL_H__ */
