/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: Artemy Ozerski            ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    date: 09.03.2023                    ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀
******************************************************************************/
#include <stdlib.h>  /* malloc, free  */
#include <stddef.h>  /* size_t        */
#include <assert.h>  /* assert    :)  */

#include "sll.h"     /* Internal use */

/*****************************************************************************/
typedef struct sll_node
{
	void *data;
	struct sll_node *next;

} sll_node_t;

struct list
{
	sll_node_t *head;
	sll_node_t *tail;
};

/* The action function and create declaration to be used in for each */
static int Counter(void *data, void *param);
static sll_node_t *CreateNode(void *data);
/*****************************************************************************/
sll_t *SLLCreate(void)
{
	sll_t *list = (sll_t *)malloc(sizeof(sll_t));

	if(NULL == list)
	{
		return NULL;
	}

	list->head = CreateNode(&(list->tail));
	if(NULL == list->head)
	{
		free(list);
		return NULL;
	}

	list->head->next = NULL;
	list->tail = list->head;

	return list;
}
/*****************************************************************************/
void SLLDestroy(sll_t *list)
{
	/* Temporary nodes for free iteration one by one */
	sll_node_t *next = NULL;
	assert(list && "List isn't valid.");

	while(list->head)
	{
		next = list->head->next;
		free(list->head);
		list->head = next;
	}

	free(list);
	list = NULL;
}
/*****************************************************************************/
size_t SLLCount(const sll_t *list)
{
	size_t count = 0;
	assert(list && "List isn't valid.");
	SLLForEach(list->head, list->tail, Counter, &count);

	return count;
}
/*****************************************************************************/
sll_iter_t SLLEnd(const sll_t *list)
{
	assert(list && "List isn't valid.");
	return list->tail;
}
/*****************************************************************************/
sll_iter_t SLLBegin(const sll_t *list)
{
	assert(list && "List isn't valid.");
	return list->head;
}
/*****************************************************************************/
int SLLIsEmpty(const sll_t *list)
{
	assert(list && "List isn't valid.");
	return SLLIterIsEqual(SLLBegin(list), SLLEnd(list));
}
/*****************************************************************************/
int SLLIterIsEqual(const sll_iter_t iterator1,const sll_iter_t iterator2)
{
	return iterator1 == iterator2;
}
/*****************************************************************************/
void SLLSetData(sll_iter_t iterator, void *data)
{
	iterator->data = data;
}
/*****************************************************************************/
void *SLLGetData(const sll_iter_t iterator)
{
	return iterator->data;
}
/*****************************************************************************/
void SLLRemove(sll_iter_t iterator)
{
	sll_iter_t tmp = iterator->next;

	iterator->data = tmp->data;
	iterator->next = tmp->next;

	/* Condition for Dummy */
	if(NULL == iterator->next)
	{
		*((sll_node_t **)tmp->data) = iterator;
	}

	free(tmp);
	tmp = NULL;
}
/*****************************************************************************/
sll_iter_t SLLNext(const sll_iter_t iterator)
{
	return iterator->next;
}
/*****************************************************************************/
sll_iter_t SLLInsert(sll_iter_t iterator, void *data)
{
	sll_node_t *node = CreateNode(iterator->data);

	if(NULL == node)
	{
		while(iterator->next)
		{
			iterator = iterator->next;
		}
		return iterator;
	}

	if(NULL == iterator->next)
	{
		*(sll_node_t **)(iterator->data) = node;
	}

	iterator->data = data;
	node->next = iterator->next;
	iterator->next = node;

	return node;
}
/*****************************************************************************/
void SLLAppend(sll_t *dest, sll_t *source)
{
	dest->tail->data = source->head->data;
	dest->tail->next = source->head->next;

	/* Setting dummy node again */
	dest->tail = source->tail; 
	dest->tail->data = &(dest->tail);

	/* Create the empty list behavior */
	source->tail = source->head;
	source->tail->data = &(source->tail);
	source->tail->next = NULL;
}
/*****************************************************************************/
sll_iter_t SLLFind(sll_iter_t from, sll_iter_t to, sll_compare_func_t cmp, void *param)
{
	for(; from !=  to && !cmp(from->data, param); from = from->next);

	return from;
}
/*****************************************************************************/
int SLLForEach(sll_iter_t from, sll_iter_t to, sll_action_func_t action, void *param)
{
	int res = 0;

	for(;from !=  to && !(res = action(from->data, param)); from = from->next);

	return res;
}
/*****************************************************************************/
static int Counter(void *data, void *param)
{
	(void) data;
	++(*(size_t *)param);

	return 0;
}
/*****************************************************************************/
static sll_node_t *CreateNode(void *data)
{
	sll_node_t *node = (sll_node_t *)malloc(sizeof(sll_node_t));
	if(NULL == node)
	{
		return NULL;
	}

	node->data = data;
	return node;
}
