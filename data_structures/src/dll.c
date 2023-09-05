/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: Alina Dvoretskaya         ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    📅️ : 15.03.2023                     ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀
******************************************************************************/
#include <stdlib.h> /* malloc, free  */
#include <stddef.h> /* size_t        */
#include <assert.h> /* assert    :)  */

#include "dll.h"    /* Internal use */

/*****************************************************************************/
typedef struct dll_node
{
	void *data;
	struct dll_node *next;
	struct dll_node *prev;

} dll_node_t;

struct dll
{
	dll_node_t *head;
	dll_node_t *tail;
};
/* The action function declaration to be used in for each */
int Action(void *data, void *param);
static void DLLSwap(dll_iter_t iter1, dll_iter_t iter2);
/*****************************************************************************/
/* Complexity - time Complexity O(1), space complexity O(1).
   Creation of a list, if creation fails it will return NULL */

dll_t *DLLCreate(void)
{
	dll_t *dll = (dll_t *)malloc(sizeof(dll_t));

	if(NULL == dll)
	{
		return NULL;
	}

	/* Creating the first node to be a dummy */
	dll->head = (dll_node_t *)malloc(sizeof(dll_node_t));
	dll->tail = dll->head;

	if(NULL == dll->head)
	{
		free(dll);
		return NULL;
	}

    /* Initializing values to NULL to mark the end of dll */
	dll->head->next = NULL;
	dll->head->prev = NULL;
	dll->head->data = &(dll->tail);

	return dll;
}
/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Delete the list. */

void DLLDestroy(dll_t *dll)
{
	/* Temporary nodes to point to dll nodes and free one by one */
	dll_node_t *next = NULL;

	assert(dll && "dll isn't valid. Can not be freed.");

	while(dll->head)
	{
		next = dll->head->next;
		free(dll->head);
		dll->head = next;
	}

	free(dll);
	dll = NULL;
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Inserts node next with data in the current position of the iterator.
   If the insertion will fail the function will return end of list */

dll_iter_t DLLInsertAfter(dll_iter_t iterator, void *data)
{
	assert(iterator && "Iterator isn't valid.");
	return DLLInsertBefore(iterator->next, data);
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Inserts node with data in the previous position of the iterator.
   If the insertion will fail the function will return end of list */

dll_iter_t DLLInsertBefore(dll_iter_t iterator, void *data)
{
	dll_node_t *new_node = (dll_node_t *)malloc(sizeof(dll_node_t));
	assert(iterator && "Iterator isn't valid.");

	if(NULL == new_node)
	{
		while(iterator->next)
		{
			iterator = iterator->next;
		}

		return iterator;
	}

	if(NULL == iterator->next)
	{
		*(dll_node_t **)(iterator->data) = new_node;
	}
	else
	{
		iterator->next->prev = new_node;
	}
	

	new_node->data = iterator->data;
	iterator->data = data;
	new_node->prev = iterator;
	new_node->next = iterator->next;
	iterator->next = new_node;

	return iterator;
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Removes node that iterator points to. 
   return Next iterator. undefined behavior on EOL */

dll_iter_t DLLRemove(dll_iter_t iterator)
{
	dll_iter_t tmp = iterator->next;
	assert(iterator && "Iterator isn't valid.");

	iterator->data = tmp->data;
	iterator->next = tmp->next;
	if(NULL == iterator->next)
	{
		*((dll_node_t **)tmp->data) = iterator;
	}
	else
	{
		iterator->next->prev = iterator;
	}

	free(tmp);
	return iterator;
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
	Push Back Data to Dll, return end of list if fail */

dll_iter_t DLLPushBack(dll_t *dll, void *data)
{
	assert(dll && "dll isn't valid.");
	return DLLInsertBefore(dll->tail, data); 
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
	Push Front Data to Dll, return end of list if fail */

dll_iter_t DLLPushFront(dll_t *dll, void *data)
{
	assert(dll && "dll isn't valid.");
	return DLLInsertBefore(dll->head, data);
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
	Pop Back Data to Dll. return data */

void *DLLPopBack(dll_t *dll)
{
	void *data = dll->tail->prev->data;
	assert(dll && "dll isn't valid.");

	DLLRemove(dll->tail->prev);
	return data;
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
	Pop Front Data to Dll return data */

void *DLLPopFront(dll_t *dll)
{
	void *data = dll->head->data;
	assert(dll && "dll isn't valid.");

	DLLRemove(dll->head);
	return data;
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Sets data at a specific node pointed by iterator. */

void DLLSetData(dll_iter_t iterator, void *data)
{
	assert(iterator && "Iterator isn't valid.");
	iterator->data = data;
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Get specific data from a specific node if list is empty will be
   undefined behavior. */

void *DLLGetData(const dll_iter_t position)
{
	assert(position && "Iterator isn't valid.");
	return position->data;
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Returns iterator pointing to the start of the list. */

dll_iter_t DLLBegin(const dll_t *dll)
{
	assert(dll && "dll isn't valid.");
	return dll->head;
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Returns iterator pointing to the end of the list. */

dll_iter_t DLLEnd(const dll_t *dll)
{
	assert(dll && "dll isn't valid.");
	return dll->tail;
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Return the next iterator. If the iterator is the end it is 
   undefined behavior. */

dll_iter_t DLLNext(const dll_iter_t iterator)
{
	assert(iterator && "Iterator isn't valid.");
	return iterator->next;
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Return the previous iterator. If the iterator is the beginning it is 
   undefined behavior. */

dll_iter_t DLLPrev(const dll_iter_t iterator)
{
	assert(iterator && "Iterator isn't valid.");
	return iterator->prev;
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Returns 1 if empty and 0 if not */

int DLLIsEmpty(const dll_t *dll)
{
	assert(dll && "dll isn't valid.");
	return DLLBegin(dll) == DLLEnd(dll);
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Returns 1 if equal and 0 if not. Function comparing data at two iterators. */

int DLLIterIsEqual(const dll_iter_t iter1, const dll_iter_t iter2)
{
	assert(iter1 && "First iterator isn't valid.");
	assert(iter2 && "Second iterator isn't valid.");
	return iter1 == iter2;
}
/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Returns the number of nodes in the list. */

size_t DLLCount(const dll_t *dll)
{
	size_t count = 0;
	assert(dll && "dll isn't valid.");

	DLLForEach(dll->head, dll->tail, Action, &count);

	return count;
}
/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Action on every data element in node in a given range. Returns status 
   if success and if not return the status of action function 
   provided by the user. */

int DLLForEach(dll_iter_t from, const dll_iter_t to, dll_act_func_t act, void *param)
{
	int status = 0;
	assert(from && "From iterator isn't valid.");
	assert(to && "To iterator isn't valid.");

	while(from != to)
	{
		if((status = act(&from->data, param)))
		{
			return status;
		}
		from = from->next;
	}

	return 0;
}
/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Cut and Paste nodes from src_from to src_to (not included) into dest */

void DLLSplice(dll_iter_t dest, dll_iter_t source_from, dll_iter_t source_to)
{
	void *tmp1 = source_from->data;
	dll_iter_t tmp_node = source_to->next;

	assert(dest && "Destination iterator isn't valid.");
	assert(source_from && "From iterator isn't valid.");
	assert(source_to && "To iterator isn't valid.");

	source_from->data = source_to->data;
	source_to->data = dest->data;
	dest->data = tmp1;

	source_to->next = dest->next;
	dest->next = source_from->next;
	source_from->next = tmp_node;
	dest->next->prev = dest;

	/* Setting dummy node again */
	if(NULL == source_from->next)
	{
		*(dll_node_t **)(source_from->data) = source_from;
	}
	else
	{
		source_from->next->prev = source_from;
	}

	if(NULL == source_to->next)
	{
		*(dll_node_t **)(source_to->data) = source_to;
	}
	else
	{
		source_to->next->prev = source_to;
	}


}
/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Finds the iterator to the node with the same data as the input data after
   comparison function return true. */

dll_iter_t DLLFind(const dll_iter_t from, const dll_iter_t to, dll_cmp_func_t cmp, void *param)
{
	dll_iter_t runner = from;

	assert(from && "From iterator isn't valid.");
	assert(to && "To iterator isn't valid.");

	for(; runner !=  to; runner = runner->next)
	{
		if(!cmp(runner->data, param))
		{
			return runner;
		}
	}

	return to;
}
/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Finds the iterators to the node with the same data as the input data after
   comparison. push back the iterators to dest. return 0 if interator has not
   been found, negative int if allocation failed, positive number on success*/

int DLLMultiFind(const dll_iter_t from, const dll_iter_t to, dll_cmp_func_t cmp, void *param, dll_t *dest)
{
	int status = 0;
	dll_iter_t found = from;
	assert(dest && "Destination isn't valid.");
	assert(from && "From iterator isn't valid.");
	assert(to && "To iterator isn't valid.");

	for(; found !=  to; found = found->next)
	{
		found = DLLFind(found, to, cmp, param);

		if(to != found)
		{
			if(NULL == DLLPushBack(dest, found)->next)
			{
				return -1;
			}
			status++;
		}
	}

	return status;
}
/*****************************************************************************/
int Action(void *data, void *param)
{
	(void) data;
	++(*(size_t *)param);
	return 0;
}
/*****************************************************************************/
void DLLArrange(dll_t *dll, void *pivot)
{
    dll_iter_t left = DLLBegin(dll);
    dll_iter_t right = DLLPrev(DLLEnd(dll));
    int piv = *(int *)pivot;

    while (left != right && left != DLLNext(right))
    {
        while (left != right && *(int *)left->data < piv)
        {
            left = DLLNext(left);
        }

        while (left != right && *(int *)right->data > piv)
        {
            right = DLLPrev(right);
        }

        DLLSwap(left, right);
    }
}
/*****************************************************************************/
static void DLLSwap(dll_iter_t iter1, dll_iter_t iter2)
{
    void *tempData = NULL;
    if(DLLIterIsEqual(iter1, iter2))
        return;

    tempData = iter1->data;
    iter1->data = iter2->data;
    iter2->data = tempData;
}
/*****************************************************************************/
