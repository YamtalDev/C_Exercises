#include<stdio.h>  /* printf, puts */
#include<stddef.h> /* size_t */

#include "stack.h"

void StackTest(void);

/*****************************************************************************/
int main(void)
{
    StackTest();
    return 0;
}
/*****************************************************************************/
void StackTest(void)
{
    int capacity = 20;
    stack_t *stack = StackCreate(capacity);

    int var1 = 5;
    float var2 = 123.456789;
    char var3 = 'z';

    struct var4
    {
        size_t var;
        float k;
    }var4;

    double var5 = 6.666666;
    int var6[10] = {9,2,3,4,5,6,7,8,9,0};

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

    puts("-------------------------- Empty test --------------------------");

    if(StackIsEmpty(stack))
    {
        printf("\nstack IsEmpty test - passed.\nstack is empty.\n\n");    
    }
    else
    {
        printf("\nstack IsEmpty test - failed.\nstack is not empty.\n\n");
    }

    puts("-------------------------- Push test --------------------------");

    StackPush(stack, &var1);

    printf("\nFirst argument pushed to stack int - %d",\
    *(int *)StackPeek(stack));

    StackPush(stack, &var2);

    printf("\nSecond argument pushed to stack float- %f", \
    *(float *)StackPeek(stack));

    StackPush(stack, &var3);

    printf("\nThird argument pushed to stack char - %c", \
    *(char *)StackPeek(stack));

    StackPush(stack, &var4);

    printf("\nFourth argument pushed to stack struct - %lu", \
    *(size_t *)StackPeek(stack));

    StackPush(stack, &var5);

    printf("\nFifth argument pushed to stack double - %f", \
    *(double *)StackPeek(stack));

    StackPush(stack, &var6);

    printf("\nSix argument pushed to stack int array - %d", \
    *((int *)StackPeek(stack) + 3));

    StackPush(stack, &var7);

    printf("\nSeventh argument pushed to stack union - %d", \
    *(int *)StackPeek(stack));

    StackPush(stack, &var8);

    printf("\nEighth argument pushed to stack enum - %d", evar);

    puts("\n\n-------------------------- Size test --------------------------");
    if(8 == StackSize(stack))
    {
        printf("\nstack push test - passed.\nstack size %lu.\n\n", \
        StackSize(stack));    
    }
    else
    {
        printf("\nstack push test - failed.\nstack size %lu.\n\n", \
        StackSize(stack));
    }

    puts("-------------------------- Capacity test --------------------------");

    if((size_t)capacity == StackCapacity(stack))
    {
        printf("\nstack capacity test - passed.\nstack capacity %lu.\n\n", \
        StackCapacity(stack));    
    }
    else
    {
        printf("\nstack capacity test - failed.\nstack capacity %lu.\n\n", \
        StackCapacity(stack));
    }

    puts("-------------------------- Is Empty test --------------------------");

    if(!StackIsEmpty(stack))
    {
        printf("\nstack IsEmpty test - passed.\nstack is not empty.\n\n");    
    }
    else
    {
        printf("\nstack IsEmpty test - failed.\nstack is empty.\n\n");
    }

    puts("-------------------------- Pop test --------------------------");

    StackPop(stack);

    printf("\nSeventh argument is now the head of stack - union %d\n", \
    *(int *)StackPeek(stack));

    StackPop(stack);

    printf("\nSix argument is now the head of stack - int array[4] - %d\n\n", \
    *((int *)StackPeek(stack) + 3));

    if(6 == StackSize(stack))
    {
        printf("\nstack pop test - passed.\nstack size %lu after popping 2 elements\n\n", \
        StackSize(stack));    
    }
    else
    {
        printf("\nstack pop test - failed.\nstack size %lu after popping 2 elements\n\n", \
        StackSize(stack));
    }

    StackDestroy(stack);
}
/*****************************************************************************/
