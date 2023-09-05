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
#include<stdio.h>   /* puts, printf */
#include<stddef.h>  /* size_t       */

#include "sll.h"

int Cmp(void *data, void *param);

int AddData(void *data, void *parameter);

/*****************************************************************************/
int main(void)
{
	sll_t *list1 = SLLCreate();
	sll_t *list2 = SLLCreate();
	sll_t *list3 = SLLCreate();
	size_t count = SLLCount(list1);
	sll_iter_t node_pointer1 = NULL;
	sll_iter_t node_pointer2 = NULL;
	sll_iter_t node_pointer3 = NULL;

	int i = 2;
	int var1 = 5;
    float var2 = 123.456789;
    char var3 = 'z';

    struct var4
    {
        size_t var;
        float k;
    }var4;

    double var5 = 6.666666;
    int var6[10] = {9,2,3,4,7,6,7,8,9,0};

    union var7
    {
        int uvar;
        float uvar2;
    }var7;

    enum var8
    {
        evar = 0
    }var8;

    int var9 = 59;

    var4.var = 111222333444555;
    var4.k = 0.45;
    var7.uvar2 = 100.5;

	node_pointer2 = SLLBegin(list1);

	puts("\n-------------------------Creation------------------------------\n");

	puts("\nCreating a list1: sll_t *list1 = SLLCreate();");

	if(SLLIsEmpty(list1))
	{
		puts("\nlist1 is empty - SLLIsEmpty(list1); : passed.");
	}
	else
	{
		puts("\nlist1 is empty - SLLIsEmpty(list1); : faild.");
	}

	if(0 == count)
	{
		printf("\nNumber of nodes after creation %lu : passed.", count);
	}
	else
	{
		printf("\nCounting number of nodes after creation %lu : failed", count);
	}

	node_pointer1 = SLLBegin(list1);
	printf("\n\nFirst element in list1 is %p\n", SLLGetData(node_pointer1));

	node_pointer2 = SLLEnd(list1);
	printf("\nLast element in list1 is %p\n", SLLGetData(node_pointer2));


	if(SLLIterIsEqual(node_pointer1, node_pointer2))
	{
		puts("\nHead and tail are equal after creation.");
	}
	else
	{
		puts("\nHead and tail are not equal after creation!.");
	}

	puts("\n----------------- Insert, count and Get data --------------------");

	node_pointer1 = SLLInsert(node_pointer1, &var1);
	count = SLLCount(list1);

	if(1 == count)
	{
		printf("\nInsertion of %d to list was successful now list length is %lu",\
		*(int *)SLLGetData(node_pointer2), count);
	}
	else
	{
		printf("\nInsertion of %d to list was unsuccessful.",\
		*(int *)SLLGetData(node_pointer2));
	}

	node_pointer2 = SLLEnd(list1);
	node_pointer1 = SLLInsert(node_pointer1, &var2);
	count = SLLCount(list1);

	if(2 == count)
	{
		printf("\n\nInsertion of %f to list was successful now list length is %lu",\
		*(float *)SLLGetData(node_pointer2), count);
	}
	else
	{
		printf("\n\nInsertion of %f to list was unsuccessful.",\
		*(float *)SLLGetData(node_pointer2));
	}

	node_pointer2 = SLLEnd(list1);
	node_pointer1 = SLLInsert(node_pointer1, &var3);
	count = SLLCount(list1);

	if(3 == count)
	{
		printf("\n\nInsertion of %c to list was successful now list length is %lu",\
		*(char *)SLLGetData(node_pointer2), count);
	}
	else
	{
		printf("\n\nInsertion of %c to list was unsuccessful.",\
		*(char *)SLLGetData(node_pointer2));
	}

	node_pointer2 = SLLEnd(list1);
	node_pointer1 = SLLInsert(node_pointer1, &var4);
	count = SLLCount(list1);

	if(4 == count)
	{
		printf("\n\nInsertion of %lu to list was successful now list length is %lu",\
		*(size_t *)SLLGetData(node_pointer2), count);
	}
	else
	{
		printf("\n\nInsertion of %lu to list was unsuccessful.",\
		*(size_t *)SLLGetData(node_pointer2));
	}

	node_pointer2 = SLLEnd(list1);
	node_pointer1 = SLLInsert(node_pointer1, &var5);
	count = SLLCount(list1);

	if(5 == count)
	{
		printf("\n\nInsertion of %f to list was successful now list length is %lu",\
		*(double *)SLLGetData(node_pointer2), count);
	}
	else
	{
		printf("\n\nInsertion of %f to list was unsuccessful.",\
		*(double *)SLLGetData(node_pointer2));
	}

	node_pointer2 = SLLEnd(list1);
	node_pointer1 = SLLInsert(node_pointer1, &var6);
	count = SLLCount(list1);

	if(6 == count)
	{
		printf("\n\nInsertion of %d to list was successful now list length is %lu",\
		*((int *)SLLGetData(node_pointer2) + 8), count);
	}
	else
	{
		printf("\n\nInsertion of %d to list was unsuccessful.",\
		*((int *)SLLGetData(node_pointer2) + 8));
	}

	node_pointer2 = SLLEnd(list1);
	node_pointer1 = SLLInsert(node_pointer1, &var7);
	count = SLLCount(list1);

	if(7 == count)
	{
		printf("\n\nInsertion of %f to list was successful now list length is %lu",\
		*(float *)SLLGetData(node_pointer2), count);
	}
	else
	{
		printf("\n\nInsertion of %f to list was unsuccessful.",\
		*(float *)SLLGetData(node_pointer2));
	}

	node_pointer2 = SLLEnd(list1);
	node_pointer1 = SLLInsert(node_pointer1, &var8);
	count = SLLCount(list1);

	if(8 == count)
	{
		printf("\n\nInsertion of %d to list was successful now list length is %lu",\
		evar, count);
	}
	else
	{
		printf("\n\nInsertion of %d to list was unsuccessful.",\
		evar);
	}

	node_pointer2 = SLLEnd(list1);
	node_pointer1 = SLLInsert(node_pointer1, &var9);
	count = SLLCount(list1);

	if(9 == count)
	{
		printf("\n\nInsertion of %d to list was successful now list length is %lu",\
		*(int *)SLLGetData(node_pointer2), count);
	}
	else
	{
		printf("\n\nInsertion of %d to list was unsuccessful.",\
		*(int *)SLLGetData(node_pointer2));
	}

	if(!SLLIsEmpty(list1))
	{
		puts("\n\nlist1 is not empty - SLLIsEmpty(list1); : passed.");
	}
	else
	{
		puts("\nlist1 is empty - SLLIsEmpty(list1); : faild.");
	}

	node_pointer2 = SLLEnd(list1);

	puts("\n-------------------- Equal, Next, Begin, End -----------------------");

	node_pointer3 = SLLBegin(list1);

	for(var1 = 0; var1 < 9; var1++)
	{
		printf("\nAdress of pointer - %p\n", (void *)node_pointer3);
		node_pointer3 = SLLNext(node_pointer3);
	}
	printf("\nAdress of pointer - %p\n", (void *)node_pointer3);

	if(SLLIterIsEqual(node_pointer3, node_pointer2))
	{
		puts("\nGetting tail of list : passed.");
	}
	else
	{
		puts("\nGetting tail of list : failed.");
	}

	if(SLLIterIsEqual(node_pointer1, SLLEnd(list1)))
	{
		puts("\nGetting head of list : passed.");
	}
	else
	{
		puts("\nGetting head of list : failed.");
	}

	puts("\n--------------------- Append, Set Data, Remove ------------------");

	node_pointer1 = SLLEnd(list2);

	for(var1 = 0; var1 < 1000; var1++)
	{
		node_pointer1 = SLLInsert(node_pointer1, &var1);
	}

	printf("\nInserdet to list2 - %lu ints of value 1.", SLLCount(list2));

	node_pointer1 = SLLBegin(list2);
	node_pointer2 = SLLBegin(list3);

	for(var1 = 0; var1 < 990; var1++)
	{
		SLLRemove(node_pointer1);
	}

	printf("\n\nAfter remove list2 size is - %lu", SLLCount(list2));

	for(var1 = 0; var1 < 10; var1++)
	{
		node_pointer2 = SLLInsert(node_pointer2, &var1);
	}

	SLLAppend(list2, list3);

	printf("\n\nAfter appending list2 size is - %lu", SLLCount(list2));

	node_pointer1 = SLLBegin(list2);

	for(var1 = 0; var1 < 20; var1++)
	{
		SLLSetData(node_pointer1, &var1);

		printf("\n\nData set for location %p - %d.",\
		(void *)node_pointer1, *(int *)SLLGetData(node_pointer1));

		node_pointer1 = SLLNext(node_pointer1);
	}

	puts("\n\n----------------------- Find, Foreach, ------------------------");

	node_pointer1 = SLLBegin(list2);
	node_pointer2 = SLLEnd(list2);

	var1 = 1;

	SLLForEach(node_pointer1, node_pointer2, AddData, &i);

	node_pointer1 = SLLBegin(list1);
	node_pointer2 = SLLEnd(list1);

	node_pointer3 = SLLFind(node_pointer1, node_pointer2, Cmp, &var2);

	printf("\n\nData fount in list - %f", *(float *)SLLGetData(node_pointer3));
	puts("\n\n------------------------ The end! :) ------------------------\n");

	SLLDestroy(list3);
	SLLDestroy(list2);
	SLLDestroy(list1);
	return 0;
}
/*****************************************************************************/
int AddData(void *data, void *parameter)
{
	(void) parameter;
    printf("\n\nData set after ForEach - %d.", *(int *)data);
    *(int *)data += *(int *)parameter;
    return 0;
}
/*****************************************************************************/
int Cmp(void *data, void *param)
{
	return *(float *)data == *(float *)param;
}

