/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: David Haver               ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    📅️ : 19.03.2023                     ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀
******************************************************************************/
#include<stdio.h>   /* printf. puts */
#include<stddef.h>  /* size_t       */

#include "sorted_list.h"

sorted_list_t *Create(void);
int Cmp(void *data, void *new_data);
int Match(void *data, void *parameter);
int AddData(void *data, void *parameter);
void PrintSortedList(sorted_list_t *sorted_list);
int SortedListPrint(void *data, void *parameter);
/*****************************************************************************/
int main(void)
{
	sorted_list_t *sorted_list = Create();
	sorted_list_t *sorted_list1 = Create();

	sorted_list_iter_t iter;


	int i = 0;

	if(sorted_list)
	{
		puts("\nCreation of sorted list passed successfully.");
	}
	else
	{
		puts("\nCreation of sorted list fails.");
	}

	SortedListInsert(sorted_list, (void *)0);
	SortedListInsert(sorted_list, (void *)10);
	SortedListInsert(sorted_list, (void *)18);
	SortedListInsert(sorted_list, (void *)9);
	SortedListInsert(sorted_list, (void *)2);
	SortedListInsert(sorted_list, (void *)6);
	SortedListInsert(sorted_list, (void *)1);
	SortedListInsert(sorted_list, (void *)1);
	SortedListInsert(sorted_list, (void *)4);
	SortedListInsert(sorted_list, (void *)23);
	SortedListInsert(sorted_list, (void *)16);
	SortedListInsert(sorted_list, (void *)-4);
	SortedListInsert(sorted_list, (void *)8);
	SortedListInsert(sorted_list, (void *)9);

	SortedListInsert(sorted_list1, (void *)0);
	SortedListInsert(sorted_list1, (void *)10);
	SortedListInsert(sorted_list1, (void *)18);
	SortedListInsert(sorted_list1, (void *)9);
	SortedListInsert(sorted_list1, (void *)2);
	SortedListInsert(sorted_list1, (void *)6);
	SortedListInsert(sorted_list1, (void *)1);
	SortedListInsert(sorted_list1, (void *)1);
	SortedListInsert(sorted_list1, (void *)4);
	SortedListInsert(sorted_list1, (void *)23);
	SortedListInsert(sorted_list1, (void *)16);
	SortedListInsert(sorted_list1, (void *)-4);
	SortedListInsert(sorted_list1, (void *)8);
	SortedListInsert(sorted_list1, (void *)9);

	printf("\nSorted List size after inserting : %lu.\n",\
	SortedListCount(sorted_list));
	printf("\nSorted List after inserting : ");
	PrintSortedList(sorted_list);

	iter = SortedListBegin(sorted_list);
	for(; i < 3; i++)
	{
		iter = SortedListRemove(iter);
	}

	printf("\n\nSorted List after removing %d elements : ", i);
	PrintSortedList(sorted_list);

	SortedListPopBack(sorted_list);
	SortedListPopBack(sorted_list);
	SortedListPopBack(sorted_list);

	printf("\n\nSorted List after poping back 3 elements: ");
	PrintSortedList(sorted_list);

	SortedListPopFront(sorted_list);
	SortedListPopFront(sorted_list);
	SortedListPopFront(sorted_list);

	printf("\n\nSorted List after poping front 3 elements: ");
	PrintSortedList(sorted_list);

	SortedListMerge(sorted_list, sorted_list1);
	printf("\n\nSorted List after merge : ");
	PrintSortedList(sorted_list);

	printf("\n\nSorted List size after inserting : %lu.\n",\
	SortedListCount(sorted_list));

	iter = SortedListFind(sorted_list, SortedListBegin(sorted_list),
	 SortedListEnd(sorted_list), (void *)-4);

	printf("\nAfter find function number found is : %ld.",
	 (long int)SortedListGetData(iter));

	iter = SortedListFindIf(SortedListBegin(sorted_list),
	 SortedListEnd(sorted_list), Match, (void *)18);

	printf("\n\nAfter findif function number found is : %ld.",
	 (long int)SortedListGetData(iter));

	#ifndef NDEBUG
	printf("\n\nSizeof iterator in debug mode is : %lu", sizeof(iter));
	#endif
	#ifdef NDEBUG
	printf("\n\nSizeof iterator not in debug mode is : %lu", sizeof(iter));
	#endif

	puts("\n\nDone!\n\n");
	SortedListDestroy(sorted_list1);
	SortedListDestroy(sorted_list);

	return 0;
}
/*****************************************************************************/
sorted_list_t *Create(void)
{
	sorted_list_t *sorted_list = SortedListCreate(Cmp);
	sorted_list_iter_t start = SortedListBegin(sorted_list);
	sorted_list_iter_t end = SortedListEnd(sorted_list);

	if(SortedListIsEmpty(sorted_list) && SortedListIsEqual(start, end) && 
	NULL == SortedListNext(start).iterator && NULL == SortedListPrev(start).iterator 
	&& 0 == SortedListCount(sorted_list))
	{
		return sorted_list;
	}
	else
	{
		return NULL;
	}
}
/*****************************************************************************/
void PrintSortedList(sorted_list_t *sorted_list)
{
	int i = 0;
	sorted_list_iter_t start = SortedListBegin(sorted_list);
	sorted_list_iter_t end = SortedListEnd(sorted_list);

	printf("SortedList = { ");
	SortedListForEach(start, end, SortedListPrint, &i);
    printf("}");
}
/*****************************************************************************/
int AddData(void *data, void *parameter)
{
    *(size_t *)data += (size_t)parameter;
    return 0;
}
/*****************************************************************************/
int SortedListPrint(void *data, void *parameter)
{
	(void) parameter;
    printf("%d ", *(int *)data);
    return 0;
}
/*****************************************************************************/
int Cmp(void *data, void *new_data)
{
	return (size_t)data - (size_t)new_data;
}
/*****************************************************************************/
int Match(void *data, void *parameter)
{
	return (size_t)data == (size_t)parameter;
}
/*****************************************************************************/
