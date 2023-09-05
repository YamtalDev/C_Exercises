/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: Alina Dvoretskaya         ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    📅️ : 15.03.2023                     ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀          🐈️
******************************************************************************/
#include<stdio.h>   /* */
#include<stdlib.h>  /* */
#include<stddef.h>  /* */
#include<assert.h>  /* */

#include "dll.h"   /* Internal use */

dll_t *Create(void);
void PrintDLL(dll_t *dll);
int Cmp(void *data, void *param);
void PrintLinkedList(dll_t *dll);
void TestArrangeLinkedList(void);
int AddData(void *data, void *parameter);
int DLLPrint(void *data, void *parameter);
/*****************************************************************************/
int main(void)
{
/* 	int i = 1;
	int j = 3;
	dll_t *dll = Create();
	dll_t *dll2 = Create();
	dll_t *dll3 = Create();
	dll_iter_t iter = DLLBegin(dll);

	if(dll)
	{
		puts("\nCreation of doubly linked list passed successfully.");
	}
	else
	{
		puts("\nCreation of doubly linked list fails.");
	}

	DLLInsertBefore(iter, (void *)0);

	for(; 10 > i; ++i)
	{
		iter = DLLInsertAfter(iter, *(void **)&i);
	}

	iter = DLLBegin(dll2);
	DLLInsertBefore(iter, (void *)20);
	for(i = 21; 31 > i; ++i)
	{
		iter = DLLInsertAfter(iter, *(void **)&i);
	}

	printf("\nDLL size after inserting : %lu.\n", DLLCount(dll));
	printf("\nDLL after inserting : ");
	PrintDLL(dll);

	DLLForEach(DLLBegin(dll), DLLEnd(dll), AddData, *(void **)&j);
	printf("\n\nDLL after for each +%d and insert before : ", j);

	for(i = 2; i; --i)
	{
		iter = DLLInsertBefore(DLLBegin(dll), *(void **)&i);
	}

	PrintDLL(dll);
	printf("\n\nDLL size after inserting : %lu.\n", DLLCount(dll));

	DLLSetData(DLLPrev(DLLEnd(dll)), (void *)100);

	printf("\nDLL after set data : ");
	PrintDLL(dll);

	for(i = 0; i < 3; i++)
	{
		DLLRemove(DLLNext(DLLNext(DLLBegin(dll))));
	}

	printf("\n\nDLL after 3 remove from head : ");
	PrintDLL(dll);

	for(i = 0; i < 3; i++)
	{
		DLLPopBack(dll);
	}

	printf("\n\nDLL after 3 pop back : ");
	PrintDLL(dll);

	for(i = 0; i < 3; i++)
	{
		DLLPopFront(dll);
	}

	printf("\n\nDLL after 3 pop front : ");
	PrintDLL(dll);

	for(i = 10; i < 16; i++)
	{
		DLLPushBack(dll, (void *)14);
	}

	printf("\n\nDLL after 6 push back : ");
	PrintDLL(dll);

	printf("\n\nDLL size after pushing : %lu.\n", DLLCount(dll));

	j = 14;

	iter = DLLFind(DLLBegin(dll), DLLEnd(dll), Cmp, (void *)14);

	printf("\nDLL find data : %lu.\n", (size_t)DLLGetData(iter));

	DLLMultiFind(DLLBegin(dll), DLLEnd(dll), Cmp, (void *)14, dll3);

	printf("\nDLL dest size after multifind : %lu.\n", DLLCount(dll3));

	DLLSplice(DLLBegin(dll), DLLBegin(dll2), DLLEnd(dll2));

	printf("\nDLL find data : %lu.\n", (size_t)DLLGetData(iter));

	printf("\nDLL after splice : ");
	PrintDLL(dll);

	printf("\n\nDone!\n\n");
	DLLDestroy(dll3);
	DLLDestroy(dll2);
	DLLDestroy(dll); */
	TestArrangeLinkedList();
    return 0;
}
/*****************************************************************************/
dll_t *Create(void)
{
	dll_t *dll = DLLCreate();
	dll_iter_t start = DLLBegin(dll);
	dll_iter_t end = DLLEnd(dll);

	if(DLLIsEmpty(dll) && DLLIterIsEqual(start, end) && 
	NULL == DLLNext(start) && NULL == DLLPrev(start) && 0 == DLLCount(dll))
	{
		return dll;
	}
	else
	{
		return NULL;
	}
}
/*****************************************************************************/
void PrintDLL(dll_t *dll)
{
	int i = 0;
	dll_iter_t end = DLLEnd(dll);
	dll_iter_t start = DLLBegin(dll);

	printf("DLL = { ");
	DLLForEach(start, end, DLLPrint, &i);
    printf("}");
}
/*****************************************************************************/
int AddData(void *data, void *parameter)
{
    *(size_t *)data += (size_t)parameter;
    return 0;
}
/*****************************************************************************/
int DLLPrint(void *data, void *parameter)
{
	(void) parameter;
    printf("%d ", *(int *)data);
    return 0;
}
/*****************************************************************************/
int Cmp(void *data, void *param)
{
	return (size_t)data - (size_t)param;
}
/*****************************************************************************/
void PrintLinkedList(dll_t *dll)
{
    dll_iter_t iterator = DLLBegin(dll);
    while (iterator != DLLEnd(dll)) 
	{
        int *data = DLLGetData(iterator);
        printf("%d ", *data);
        iterator = DLLNext(iterator);
    }

    printf("\n");
}
/*****************************************************************************/
void TestArrangeLinkedList(void)
{
    int pivot = 11;
	size_t i = 0;
    dll_t *dll = DLLCreate();
    int values[] = {8, 3, 11, 55, 2, 6, 17, 7, 6, 0, 9, 5};
    size_t num_values = sizeof(values) / sizeof(values[0]);

    for(; i < num_values; i++)
    {
        DLLPushBack(dll, &values[i]);
    }

    printf("Original list: ");
    PrintLinkedList(dll);

    DLLArrange(dll, &pivot);

    printf("Modified list (arranged around %d): ", pivot);
    PrintLinkedList(dll);

    DLLDestroy(dll);
}
/*****************************************************************************/