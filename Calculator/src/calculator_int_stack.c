/******************************************************************************

    Writer: Tal Aharon

    Reviewer: No one.

    Date: 01.05.2023

*******************************************************************************

                              Description:

    This code is a C implementation of a int stack, which is 
    a type of data structure that follows the Last In First Out (LIFO) principle. 
    The stack is used to store ints and provides basic stack operations 
    such as push, pop, and peek. The implementation uses dynamic memory 
    allocation and includes error checking to prevent buffer overflow. 
    The code includes a function for creating a new stack, pushing 
    elements onto the stack, popping elements off the stack, 
    peeking at the top element, and destroying the stack.

******************************************************************************/
#include <stdlib.h>                    /* malloc, free */
#include <stddef.h>                    /* size_t, NULL */
#include <assert.h>                    /* assert       */

#include "calculator_int_stack.h"      /* Internal use */
/*****************************************************************************/
struct c_stack
{
	size_t capacity;
	size_t top;
	int *elements;
};
/*****************************************************************************/
c_stack_t *CStackCreate(size_t size)
{
	c_stack_t *c_stack = (c_stack_t *)malloc(sizeof(c_stack_t) + sizeof(int) * size);
	if(NULL == c_stack)
	{
		return (NULL);
	}

	c_stack->elements = (int *)(c_stack + 1);
	c_stack->capacity = size;
	c_stack->top = 0;
	return (c_stack);
}
/*****************************************************************************/
int CStackPush(c_stack_t *c_stack, int data)
{
	assert(c_stack && "Stack is not valid.");
	if(c_stack->top > c_stack->capacity)
	{
		return (0);
	}

	(c_stack->elements)[++c_stack->top] = data;
	return (1);
}
/*****************************************************************************/
int CStackPop(c_stack_t *c_stack)
{
	assert(c_stack && "Stack is not valid.");
	if(!CStackIsEmpty(c_stack))
	{
		--(c_stack->top);
		return ((c_stack->elements)[c_stack->top + 1]);
	}

	return (0);
}
/*****************************************************************************/
int CStackPeek(c_stack_t *c_stack)
{
	assert(c_stack && "Stack is not valid.");
	return ((c_stack->elements)[c_stack->top]);
}
/*****************************************************************************/
void CStackDestroy(c_stack_t *c_stack)
{
	free(c_stack);
	c_stack = NULL;
}
/*****************************************************************************/
int CStackIsEmpty(c_stack_t *c_stack)
{
	assert(c_stack && "Stack is not valid.");
	return c_stack->top == 0;
}
/*****************************************************************************/
size_t CStackSize(c_stack_t *c_stack)
{
	assert(c_stack && "Stack is not valid.");
	return (c_stack->top);
}
/*****************************************************************************/
