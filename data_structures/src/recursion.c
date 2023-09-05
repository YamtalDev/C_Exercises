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

    Reviewer: Itamar Brafman.

    Date: 03.05.2023

*******************************************************************************

    Description:

******************************************************************************/
#include <string.h>         /* strncmp, strlen */
#include <stdlib.h>         /* malloc, free    */
#include <stddef.h>         /* size_t, NULL    */
#include <assert.h>         /* assert          */

#include "recursion.h"      /* Internal API    */

static void Sort(int_stack_t *stack, int stack_element);
/*****************************************************************************/
int IterativeFibonacci(int n)
{
	int i = 0, j = 1, a = 2, k = 0;

	if(!n)
		return (0);

	for(; a <= n; ++a)
	{
		k = i + j;
		i = j;
		j = k;
	}

	return (j);
}
/*****************************************************************************/
int Fibonacci(int index)
{
	return ((index <= 1) ? index : Fibonacci(index -1) + Fibonacci(index - 2));
}
/*****************************************************************************/
void StackSort(int_stack_t *stack)
{
	int stack_element = 0;
	assert(stack);

	if(IntStackIsEmpty(stack))
	{
		return;
	}

	stack_element = IntStackPop(stack);
	StackSort(stack);

	Sort(stack, stack_element);
}
/*****************************************************************************/
static void Sort(int_stack_t *stack, int stack_element)
{
	int tmp_element = 0;
	if(IntStackIsEmpty(stack) || stack_element > IntStackPeek(stack))
	{
		IntStackPush(stack, stack_element);
		return;
	}

	tmp_element = IntStackPop(stack);
	Sort(stack, stack_element);

	IntStackPush(stack, tmp_element);
}
/*****************************************************************************/
Node *FlipList(Node *node)
{
	Node *tmp = NULL;
	assert(NULL != node );
	if(NULL == node->next)
	{
		return (node);
	}

	tmp = FlipList(node->next);
	node->next->next = node;
	node->next = NULL;
	return (tmp);
}
/*****************************************************************************/
size_t Strlen(const char *str)
{
	return ('\0' == *str ? 0 : (Strlen(str + 1) + 1));
}
/*****************************************************************************/
int Strcmp(const char *str1, const char *str2)
{
	if(*str1 - *str2)
	{
		return (*str1 - *str2);
	}

	return ('\0' == *str1 ? 0 : Strcmp(str1 + 1, str2 + 1));
}
/*****************************************************************************/
char *Strcpy(char *buffer, const char *src)
{
	if(buffer && src && (*buffer = *src))
	{
		return ('\0' == *src ? buffer : Strcpy(buffer + 1, src + 1));
	}

	return (NULL);
}
/*****************************************************************************/
char *Strcat(char *dest, const char *src)
{
	if('\0' != *dest)
	{
		return (Strcat(dest + 1, src));
	}

	return ((*dest = *src) ? Strcat(dest + 1, src + 1) : dest);
}
/*****************************************************************************/
char *Strstr(const char *haystack, const char *needle)
{
	int cmp = 0;
	if('\0' == *haystack || '\0' == *needle)
	{
		return (NULL);
	}

	cmp = strncmp(haystack, needle, Strlen(needle));
	return (!cmp ? (char*)haystack : Strstr(haystack + 1, needle));
}
/*****************************************************************************/
