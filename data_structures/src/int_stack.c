/******************************************************************************
                                        ▄▄▀▀▀▀████▓▓░░  ░
                                     ▄█▓░░   ░▓█▓
                                   ▄█▓░░    ░▓█░
                                  █▓░░░░   ░▓█░
                                ▄█▓░░░    ░░▓█░
        ▄▄▄              ▄▄▄▄█▄█▓▓▀▀▀▓███▄▄▓██▓░ ░
       █░  █         ▄▄▓▓▓▓░░░░░░░░░░░░░░░▓████▄▄                      ▄▄▄▄▄▄▓
      █    ▓█    ▄▄▓▓▓▓░▓░░░   ░░░░░░░░░░░░░░░▓▓▓█▄▄     ▄        ▄▄▓▓▓░░░░█▀
       █  ▓█   ▄█▓░▄██▓░░       ░  ░░░░░░ ░░░░░░▓▓▓▓██▄    ▄   ░▄▓▓▓░░  ░▓█▓
        ▀▀▀  ▄█▓░ ▄▄▄▄▄ ░░           ░░░   ░  ▄▄▄ ░░▓▓▓█▄ ▀▓▀ ░█▓▓░░   ░▓█▓
      ▄▄    ██▓░▄▀  ░░▓█▓░░       ░  ░░      █░  █  ░░░▓▓█▄  ▓█▓▓░░   ░▓▓█░
     █ ▓█  ██▓░▓█     ░▓█▓░░   ░   ░░░      █░  ░▓█   ░░▓▓██▓█▓▓░    ░░▓▓█
      ▀▀  ██▓▓░█▓      ░▓░░   ░ ░            █ ░▓█     ░░░▓███▓░ ░  ░░░▓█▓
   ▄▄  ▄ ██▓▓░ █░  ▄▄▄  ░░     ░    ▄▄▄▄▄     ▀▀▀ ▄  ░  ░░░▓█▓░    ░░░▓▓█
  █ ▓█  ███▓▓░▄█▄▄██▄█▄▄▄░░     ▄▓▓▓░░░ ░▀  ░░░          ░░▓█▓    ░ ░░░▓█ ▀
   ▀▀   ███▓▓▓░░░░░░░  ░▓▓░░         ░     ░▓████▓▓░░░ ░  ░░▓▓  ░   ░░▓▓▓▀
     ▄▓▄ ███▓▓▓░░░░  ▄░▀▄░░░░░░░    ░    ░▓███▓░▀▀▀██▄    ░░░     ░░░▓▓▓ ▄░▀▀▄
      ▀   ▀███▓▓▓▄▄▄ ▀▄▓▀░ ▄▄▄ ░░░░░░ ░░░▓███▓░     ▀██░ ░▓░░░ ░░░░░▓▓▓ █░   ▓█
*******************************************************************************

    Writer: Tal Aharon

    Reviewer: No one.

    Date: 01.05.2023

*******************************************************************************

                              Description:

    This code is a C implementation of a int stack, which is a type of data 
    structure that follows the Last In First Out (LIFO) principle. The stack
    is used to store ints and provides basic stack operations such as push, 
    pop, and peek. The implementation uses dynamic memory allocation and 
    includes error checking to prevent buffer overflow. The code includes 
    a function for creating a new stack, pushing elements onto the stack, 
    popping elements off the stack, peeking at the top element, and 
    destroying the stack.

******************************************************************************/
#include <stdlib.h>                    /* malloc, free */
#include <stddef.h>                    /* size_t, NULL */
#include <assert.h>                    /* assert       */

#include "int_stack.h"
/*****************************************************************************/
#define FAILURE (0)
#define SUCCESS (1)
struct int_stack
{
	size_t size;
	size_t top;
	int *data;
};
/*****************************************************************************/
int_stack_t *IntStackCreate(size_t size)
{
	int_stack_t *stack = malloc(sizeof(int_stack_t) + size * sizeof(int));
	if(NULL == stack)
	{
		return (NULL);
	}

	stack->data = (int *)(stack + 1);
	stack->size = size;
	stack->top = 0;
	return stack;
}
/*****************************************************************************/
void IntStackDestroy(int_stack_t *stack)
{
	free(stack);
}
/*****************************************************************************/
int IntStackPush(int_stack_t *stack, int data)
{
	if(stack->top >= stack->size)
	{
		return (FAILURE);
	}

	stack->data[stack->top] = data;
	stack->top++;
	return (SUCCESS);
}
/*****************************************************************************/
int IntStackPop(int_stack_t *stack)
{
	if(stack->top == 0) {
		return (FAILURE);
	}

	stack->top--;
	return (stack->data[stack->top]);
}
/*****************************************************************************/
int IntStackPeek(int_stack_t *stack)
{
	if(stack->top == 0)
	{
		return '\0';
	}

	return (stack->data[stack->top - 1]);
}
/*****************************************************************************/
int IntStackIsEmpty(int_stack_t *stack)
{
	return (stack->top == 0);
}
/*****************************************************************************/
size_t IntStackSize(int_stack_t *stack)
{
	return (stack->top);
}
/*****************************************************************************/
