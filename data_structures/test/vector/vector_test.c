#include<stdio.h>   /* printf, puts  */
#include<stddef.h>  /* size_t, NULL */

#include "vector.h"

/*****************************************************************************/
int CreationTest(size_t capacity);

void PushTest(size_t capacity);

void ReservePopShrinkTest(size_t capacity);
/*****************************************************************************/
int main(void)
{
	int i = 0;
	size_t capacity = 0;

	puts("---------------- Creation, capacity and size test ----------------");
	for(; i < 3; ++i)
	{
		if(CreationTest(capacity))
		{
			puts("Creation, capacity and size test : passed");
		}
		else
		{
			puts("Creation, capacity and size test : faild");
		}
		capacity += 97 / 2;
	}

	capacity = 1;

	puts("\n-------- Pushback, get element, set element and is empty --------\n");

	PushTest(capacity);

	puts("\n------------ Popback, SafePop, Reserve and Shrink  --------------\n");

	ReservePopShrinkTest(capacity);

    return 0;
}
/*****************************************************************************/
int CreationTest(size_t capacity)
{
	vector_t *vector = DVectorCreate(capacity);

	int ans = (capacity == DVectorCapacity(vector) && vector &&\
	0 == DVectorSize(vector)) ? 1 : 0;

	printf("\ncapacity - %lu, size - %lu\n\n",\
	DVectorCapacity(vector), DVectorSize(vector));

	DVectorDestroy(vector);
	vector = NULL;

	return ans;
}
/*****************************************************************************/
void PushTest(size_t capacity)
{
	vector_t *vector = DVectorCreate(capacity);

	int i = 0;
    int var1 = 5;
    float var2 = 123.456789;
    char var3 = 'z';
    int var9 = 59;

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

    var4.var = 111222333444555;
    var4.k = 0.45;
    var7.uvar = 100;

	if(DVectorIsEmpty(vector))
	{
		puts("Is empty test : passed\n");
	}
	else
	{
		puts("Is empty test : faild.\n");
	}

	DVectorPushBack(vector, &var1);

	printf("Vector new element after pushing int : %d\n",
	*(int *)DVectorGetElement(vector, i++));

	printf("Vector new size and capacity - size : %lu capacity : %lu\n\n",
	DVectorSize(vector), DVectorCapacity(vector));

	DVectorPushBack(vector, &var2);

	printf("Vector new element after pushing float : %f\n",
	*(float *)DVectorGetElement(vector, i++));

	printf("Vector new size and capacity - size : %lu capacity : %lu\n\n",
	DVectorSize(vector), DVectorCapacity(vector));

	DVectorPushBack(vector, &var3);

	printf("Vector new element after pushing char : '%c'\n",
	*(char *)DVectorGetElement(vector, i++));

	printf("Vector new size and capacity - size : %lu capacity : %lu\n\n",
	DVectorSize(vector), DVectorCapacity(vector));

	DVectorPushBack(vector, &var4);

	printf("Vector new element after pushing size_t from struct : %lu\n",
	*(size_t *)DVectorGetElement(vector, i++));

	printf("Vector new size and capacity - size : %lu capacity : %lu\n\n",
	DVectorSize(vector), DVectorCapacity(vector));

	DVectorPushBack(vector, &var5);

	printf("Vector new element after pushing double : %f\n",
	*(double *)DVectorGetElement(vector, i++));

	printf("Vector new size and capacity - size : %lu capacity : %lu\n\n",
	DVectorSize(vector), DVectorCapacity(vector));

	DVectorPushBack(vector, &var6);

	printf("Vector new element after pushing int array[8]: %d\n",
	*((int *)DVectorGetElement(vector, i++) + 8));

	printf("Vector new size and capacity - size : %lu capacity : %lu\n\n",
	DVectorSize(vector), DVectorCapacity(vector));

	DVectorPushBack(vector, &var7);

	printf("Vector new element after pushing int union element : %d\n",
	*(int *)DVectorGetElement(vector, i++));

	printf("Vector new size and capacity - size : %lu capacity : %lu\n\n",
	DVectorSize(vector), DVectorCapacity(vector));

	DVectorPushBack(vector, &var9);

	printf("Vector new element after pushing int : %d\n",
	*(int *)DVectorGetElement(vector, i++));

	printf("Vector new size and capacity - size : %lu capacity : %lu\n\n",
	DVectorSize(vector), DVectorCapacity(vector));

	DVectorPushBack(vector, &var8);

	printf("Vector new element after pushing enum : %d\n",
	evar);

	printf("Vector new size and capacity - size : %lu capacity : %lu\n\n",
	DVectorSize(vector), DVectorCapacity(vector));


	if(!DVectorIsEmpty(vector))
	{
		puts("Is empty test : passed\n");
	}
	else
	{
		puts("Is empty test : faild.\n");
	}

	printf("Vector element before seting index 4 : %f\n",
	*(double *)DVectorGetElement(vector, 4));

	DVectorSetElement(vector, 4, &var9);

	printf("Vector element after seting index 4 to int : %d\n",
	*(int *)DVectorGetElement(vector, 4));

	printf("Vector new size and capacity - size : %lu capacity : %lu\n\n",
	DVectorSize(vector), DVectorCapacity(vector));

	printf("Vector element before seting index 5 -> array[5] : %d\n"\
	,*((int *)DVectorGetElement(vector, 5) + 4));

	DVectorSetElement(vector, 5, &var5);

	printf("Vector element after seting index 5 to float : %f\n",
	*(double *)DVectorGetElement(vector, 5));

	printf("Vector new size and capacity - size : %lu capacity : %lu\n",
	DVectorSize(vector), DVectorCapacity(vector));

	DVectorDestroy(vector);
	vector = NULL;
}
/*****************************************************************************/
void ReservePopShrinkTest(size_t capacity)
{
	int i = 0;
	vector_t *vector = DVectorCreate(capacity);
	vector_t *vector1 = DVectorCreate(capacity);

	puts("----------------------------Pop---------------------------\n");

	for(; i < 30; i++)
	{
		DVectorPushBack(vector, &i);
	}

	for(i = 0; i < 30; i++)
	{
		DVectorPopBack(vector);
		printf("Size and capacity - size : %lu capacity : %lu\n\n",
		DVectorSize(vector), DVectorCapacity(vector));
	}

	puts("----------------------------Safe-Pop------------------------\n");

	for(i = 0; i < 30; i++)
	{
		DVectorPushBack(vector, &i);
	}

	for(i = 0; i < 30; i++)
	{
		DVectorSafePop(vector);
		printf("Size and capacity - size : %lu capacity : %lu\n\n",
		DVectorSize(vector), DVectorCapacity(vector));
	}

	DVectorDestroy(vector);
	vector = NULL;

	puts("-------------------------- Reserve ----------------------\n");

	for(i = 0; i < 25; i++)
	{
		DVectorPushBack(vector1, &i);
	}

	printf("Size and capacity befor reserve - size : %lu capacity : %lu\n\n",
	DVectorSize(vector1), DVectorCapacity(vector1));

	DVectorReserve(vector1, 0);

	printf("After reserve 0 - size : %lu capacity : %lu\n\n\n\n",
	DVectorSize(vector1), DVectorCapacity(vector1));

	printf("Size and capacity befor reserve - size : %lu capacity : %lu\n\n",
	DVectorSize(vector1), DVectorCapacity(vector1));

	DVectorReserve(vector1, 8);

	printf("After reserve 8 - size : %lu capacity : %lu\n\n\n\n",
	DVectorSize(vector1), DVectorCapacity(vector1));

	printf("Size and capacity befor reserve - size : %lu capacity : %lu\n\n",
	DVectorSize(vector1), DVectorCapacity(vector1));

	DVectorReserve(vector1, 10000000);

	printf("After reserve 10000000 - size : %lu capacity : %lu\n\n\n\n",
	DVectorSize(vector1), DVectorCapacity(vector1));

	puts("-------------------------- Shrink ----------------------\n");

	printf("Size and capacity befor Shrink - size : %lu capacity : %lu\n\n",
	DVectorSize(vector1), DVectorCapacity(vector1));

	DVectorShrinkToFit(vector1);

	printf("After Shrinking - size : %lu capacity : %lu\n\n\n\n",
	DVectorSize(vector1), DVectorCapacity(vector1));

	printf("Size and capacity befor Shrink - size : %lu capacity : %lu\n\n",
	DVectorSize(vector1), DVectorCapacity(vector1));

	DVectorShrinkToFit(vector1);

	printf("After Shrinking - size : %lu capacity : %lu\n\n\n\n",
	DVectorSize(vector1), DVectorCapacity(vector1));

	DVectorDestroy(vector1);
	vector = NULL;
}
/*****************************************************************************/
