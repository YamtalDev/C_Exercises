/******************************************************************************

    Writer: Tal Aharon

    Reviewer: First name and family name.

    Date: 01.05.2023

*******************************************************************************

                           Description:

    This code is a C implementation of a double stack, which is a type of data 
    structure that follows the Last In First Out (LIFO) principle. The stack is 
    used to store double-precision floating-point numbers and provides basic 
    stack operations such as push, pop, and peek. The implementation uses 
    dynamic memory allocation and includes error checking to prevent buffer 
    overflow. The code includes a function for creating a new stack, pushing 
    elements onto the stack, popping elements off the stack, peeking at the 
    top element, checking if the stack is empty, and destroying the stack.

******************************************************************************/
#include <stdlib.h>                       /* malloc, free  */
#include <stddef.h>                       /* size_t, NULL */
#include <assert.h>                       /* assert       */

#include "calculator_double_stack.h"      /* Internal use */
/*****************************************************************************/
struct d_stack
{
	size_t capacity;
	size_t top;
	double *elements;
};
/*****************************************************************************/
d_stack_t *DStackCreate(size_t size)
{
	d_stack_t *d_stack = (d_stack_t *)malloc(sizeof(d_stack_t) + sizeof(double) * size);
	if(NULL == d_stack)
	{
		return (NULL);
	}

	d_stack->elements = (double *)(d_stack + 1);
	d_stack->capacity = size;
	d_stack->top = 0;
	return (d_stack);
}
/*****************************************************************************/
int DStackPush(d_stack_t *d_stack, double data)
{
	assert(d_stack && "Stack is not valid.");
	if(d_stack->top > d_stack->capacity)
	{
		return (0);
	}

	(d_stack->elements)[++d_stack->top] = data;
	return (1);
}
/*****************************************************************************/
double DStackPop(d_stack_t *d_stack)
{
	assert(d_stack && "Stack is not valid.");
	if(!DStackIsEmpty(d_stack))
	{
		--(d_stack->top);
		return ((d_stack->elements)[d_stack->top + 1]);
	}

	/* Max value of Double -1 */
	return (~1);
}
/*****************************************************************************/
double DStackPeek(d_stack_t *d_stack)
{
	assert(d_stack && "Stack is not valid.");
	return ((d_stack->elements)[d_stack->top]);
}
/*****************************************************************************/
void DStackDestroy(d_stack_t *d_stack)
{
	free(d_stack);
	d_stack = NULL;
}
/*****************************************************************************/
int DStackIsEmpty(d_stack_t *d_stack)
{
	assert(d_stack && "Stack is not valid.");
	return d_stack->top == 0;
}
/*****************************************************************************/
size_t DStackSize(d_stack_t *d_stack)
{
	assert(d_stack && "Stack is not valid.");
	return (d_stack->top);
}
/*****************************************************************************/
