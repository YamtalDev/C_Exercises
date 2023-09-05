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

    Description: Recursion functions testing.

******************************************************************************/
#include <stddef.h>      /* size_t, NULL */
#include <stdio.h>       /* printf       */
#include <assert.h>      /* assert       */
#include <string.h>      /* strlen       */
#include <stdlib.h>      /* rand         */

#include "recursion.h"   /* Internal API */
/*****************************************************************************/
void StrlenTest(void);
void StrcmpTest(void);
void StrcpyTest(void);
void StrcatTest(void);
void StrstrTest(void);
void FlipListTest(void);
void StackSortTest(void);
void FibonacciTest(void);
/*****************************************************************************

Functions: SLLCreate, SLLDestroy, SLLCount, SLLGetData, SLLNext, SLLInsert.

Description: Data structure of a singly lined list to implement a function that 
             will flip the nodes recursively.

******************************************************************************/
Node *SLLCreate(int data);
Node *SLLNext(Node *head);
int SLLGetData(Node *head);
void SLLDestroy(Node *head);
Node *SLLInsert(Node *head, int data);
/*****************************************************************************/
int main(void)
{
	FibonacciTest();
	puts("\nFibonacciTest(): passed.");
	StackSortTest();
	puts("\nStackSortTest(): passed.");
	FlipListTest();
	puts("\nFlipListTest(): passed.");
	StrlenTest();
	puts("\nStrlenTest(): passed.");
	StrcmpTest();
	puts("\nStrcmpTest(): passed.");
	StrcpyTest();
	puts("\nStrcpyTest(): passed.");
	StrstrTest();
	puts("\nStrstrTest(): passed.");
	StrcatTest();
	puts("\nStrcatTest(): passed.");
	return (0);
}
/*****************************************************************************/
void FibonacciTest(void)
{
	assert(0 == Fibonacci(0));
	assert(1 == Fibonacci(1));
	assert(1 == Fibonacci(2));
	assert(2 == Fibonacci(3));
	assert(3 == Fibonacci(4));
	assert(5 == Fibonacci(5));
	assert(8 == Fibonacci(6));
	assert(13 == Fibonacci(7));
	assert(21 == Fibonacci(8));
	assert(34 == Fibonacci(9));
	assert(55 == Fibonacci(10));
	assert(89 == Fibonacci(11));
	assert(144 == Fibonacci(12));
	assert(233 == Fibonacci(13));
	assert(377 == Fibonacci(14));
	assert(610 == Fibonacci(15));
	assert(987 == Fibonacci(16));
	assert(1597 == Fibonacci(17));
	assert(2584 == Fibonacci(18));
	assert(4181 == Fibonacci(19));
	assert(2584 + 4181== Fibonacci(20));

	assert(0 == IterativeFibonacci(0));
	assert(1 == IterativeFibonacci(1));
	assert(1 == IterativeFibonacci(2));
	assert(2 == IterativeFibonacci(3));
	assert(3 == IterativeFibonacci(4));
	assert(5 == IterativeFibonacci(5));
	assert(8 == IterativeFibonacci(6));
	assert(13 == IterativeFibonacci(7));
	assert(21 == IterativeFibonacci(8));
	assert(34 == IterativeFibonacci(9));
	assert(55 == IterativeFibonacci(10));
	assert(89 == IterativeFibonacci(11));
	assert(144 == IterativeFibonacci(12));
	assert(233 == IterativeFibonacci(13));
	assert(377 == IterativeFibonacci(14));
	assert(610 == IterativeFibonacci(15));
	assert(987 == IterativeFibonacci(16));
	assert(1597 == IterativeFibonacci(17));
	assert(2584 == IterativeFibonacci(18));
	assert(4181 == IterativeFibonacci(19));
	assert(2584 + 4181== IterativeFibonacci(20));
}
/*****************************************************************************/
void StackSortTest(void)
{
	size_t i = 0;
	int element = 0;
	size_t stack_size = 20;

	int_stack_t *stack = IntStackCreate(stack_size);

	assert(stack);
	for(; i < stack_size; IntStackPush(stack, rand()), ++i);

	StackSort(stack);
	for(i = 0; i < stack_size; ++i)
	{
		element = IntStackPop(stack);
		assert(element > IntStackPeek(stack));
	}

	IntStackDestroy(stack);
	stack = NULL;
}
/*****************************************************************************/
void FlipListTest(void)
{
	int i = 1;
	int list_size = 20;
	Node *head = SLLCreate(0);
	Node *runner = head;
	Node *test_runner = head;

	for(; i < list_size; ++i)
	{
		SLLInsert(head, i);
		head = SLLNext(head);
	}

	for(i = 0; i < list_size - 1; ++i)
	{
		assert(SLLGetData(test_runner) < SLLGetData(SLLNext(test_runner)));
		test_runner = SLLNext(test_runner);
	}

	runner = FlipList(runner);
	for(i = 0; i < list_size - 1; ++i)
	{
		assert(SLLGetData(runner) > SLLGetData(SLLNext(runner)));
		runner = SLLNext(runner);
	}

	SLLDestroy(head);
}
/*****************************************************************************/
void StrlenTest(void)
{
	char *str = "A string with characters";
	char another_str[35] = "Another string with characters";
	assert(strlen(str) == Strlen(str));
	assert(strlen(another_str) == Strlen(another_str));
	assert(strlen("A string literal") == Strlen("A string literal"));
	assert(strlen("") == Strlen(""));
}
/*****************************************************************************/
void StrcmpTest(void)
{
	char *str2 = "B";
	char *str1 = "A";
	char another_str2[35] = "B";
	char another_str1[35] = "A";
	assert(strcmp("A", "B") == Strcmp("A", "B"));
	assert(strcmp("B", "A") == Strcmp("B", "A"));
	assert(strcmp("B", "B") == Strcmp("B", "B"));
	assert(strcmp(str1, str2) == Strcmp(str1, str2));
	assert(strcmp(str1, str1) == Strcmp(str1, str1));
	assert(strcmp("This i", "Thir") == Strcmp("This i", "Thir"));
	assert(strcmp("dgfnbd", "dhdaf") == Strcmp("dgfnbd", "dhdaf"));
	assert(strcmp("kakakaka", "kakakaka") == Strcmp("kakakaka", "kakakaka"));
	assert(strcmp(another_str1, another_str2) == Strcmp(another_str1, another_str2));
	assert(strcmp(another_str1, another_str1) == Strcmp(another_str1, another_str1));
}
/*****************************************************************************/
void StrcpyTest(void)
{
	char *src = "String to copy";
	char buffer[20] = {0};

	Strcpy(buffer, src);
	assert(0 == strcmp(buffer, src));

	Strcpy(buffer, "hi");
	assert(0 != strcmp(buffer, src));

	Strcpy(buffer, "");
	assert(0 == strcmp(buffer, ""));

	Strcpy(buffer, "123456789012345");
	assert(0 == strcmp(buffer, "123456789012345"));

	assert(NULL == Strcpy(NULL, src));
	assert(NULL == Strcpy(buffer, NULL));
	Strcpy(buffer, "abc\0def");
	assert(0 == strcmp(buffer, "abc"));
}
/*****************************************************************************/
void StrstrTest(void)
{
	char *haystack = "The quick brown fox jumps over the lazy dog";
	char *needle = "fox";
	char *expected = "fox jumps over the lazy dog";
	assert(0 == strcmp(expected, Strstr(haystack, needle)));
	haystack = "The quick brown fox jumps over the lazy dog";
	needle = "cat";
	expected = NULL;
	assert(expected == Strstr(haystack, needle));

	haystack = "";
	needle = "";
	expected = "";
	assert(NULL ==  Strstr(haystack, needle));

	haystack = "needle";
	needle = "needle";
	expected = "needle";
	assert(0 == strcmp(expected, Strstr(haystack, needle)));

	haystack = "needle";
	needle = "needles";
	expected = NULL;
	assert(expected == Strstr(haystack, needle));

	haystack = "Hello world";
	needle = "world";
	expected = "world";
	assert(0 == strcmp(expected, Strstr(haystack, needle)));

	haystack = "Hello world";
	needle = "lo w";
	expected = "lo world";
	assert(0 == strcmp(expected, Strstr(haystack, needle)));
}
/*****************************************************************************/
void StrcatTest(void)
{
	char s1[50] = "Hello";
	char s2[] = " World";
	char expected[] = "Hello World";
	char s3[50] = "";
	char s4[] = "";
	char expected2[] = "";
	char s5[50] = "This is a test";
	char s6[] = " of Strcat";
	char expected3[] = "This is a test of Strcat";

	Strcat(s1, s2);
	assert(strcmp(s1, expected) == 0);

	Strcat(s3, s4);
	assert(strcmp(s3, expected2) == 0);

	Strcat(s5, s6);
	assert(strcmp(s5, expected3) == 0);
}
/*****************************************************************************/
Node *SLLCreate(int data)
{
	Node *head = (Node *)malloc(sizeof(Node));
	if(NULL == head)
	{
		return NULL;
	}

	head->next = NULL;
	head->data = data;
	return (head);
}
/*****************************************************************************/
void SLLDestroy(Node *head)
{
	Node *runner = head;
	Node *next = NULL;

	assert(head);
	while(runner)
	{
		next = runner->next;
		free(runner);
		runner = next;
	}

	head = NULL;
}
/*****************************************************************************/
int SLLGetData(Node *head)
{
	assert(head);
	return (head->data);
}
/*****************************************************************************/
Node *SLLNext(Node *head)
{
	assert(head);
	return (head->next);
}
/*****************************************************************************/
Node *SLLInsert(Node *head, int data)
{
	Node *new_node = (Node *)malloc(sizeof(Node));
	if(NULL == new_node)
	{
		return (head);
	}

	new_node->data = data;
	new_node->next = NULL;
	head->next = new_node;

	return (new_node);
}
/*****************************************************************************/
