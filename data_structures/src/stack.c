/******************************************************************************
                                           ▐▀▄       ▄▀▌   ▄▄▄▄▄▄▄
                                           ▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄
    writer: Tal Aharon                    ▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄
                                          ▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄
    reviewer: Ravit Yehud               ▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌
                                        ▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐   ▄▄
    date: 01.03.2023                    ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
                                       ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀
                                      ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀
                                      ▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌
                                        ▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀
******************************************************************************/
#include <assert.h>  /* assert       */
#include <stdio.h>   /* fprintf      */
#include <stdlib.h>  /* malloc, free */
#include <stddef.h>  /* size_t, NULL */

#include "stack.h"   /* Internal use */
/*****************************************************************************/
struct stack
{
	size_t capacity;
	size_t top;
	void **elements;
};
/*****************************************************************************/
stack_t *StackCreate(size_t size)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t) + sizeof(void *) * size);
	if(NULL == stack)
	{
		return (NULL);
	}

	stack->elements = (void **)(stack + 1);
	stack->capacity = size;
	stack->top = 0;
	return (stack);
}
/*****************************************************************************/
void StackPush(stack_t *stack, void *data)
{
	assert(stack && "Stack is not valid.");
	if(stack->top > stack->capacity)
	{
		return;
	}

	*((stack->elements) + (++stack->top)) = data;
}
/*****************************************************************************/
void StackPop(stack_t *stack)
{
	assert(stack && "Stack is not valid.");
	if(StackIsEmpty(stack))
	{
		return;
	}

	--(stack->top);
}
/*****************************************************************************/
void *StackPeek(stack_t *stack)
{
	assert(stack && "Stack is not valid.");
	return (*((stack->elements) + (stack->top)));
}
/*****************************************************************************/
size_t StackSize(stack_t *stack)
{
	assert(stack && "Stack is not valid.");
	return (stack->top);
}
/*****************************************************************************/
size_t StackCapacity(stack_t *stack)
{
	assert(stack && "Stack is not valid.");
	return (stack->capacity);
}
/*****************************************************************************/
int StackIsEmpty(stack_t *stack)
{
	assert(stack && "Stack is not valid.");
	return stack->top == 0;
}
/*****************************************************************************/
void StackDestroy(stack_t *stack)
{
	assert(stack && "Stack is not valid.");
	free(stack);
	stack = NULL;
}
/*****************************************************************************/
