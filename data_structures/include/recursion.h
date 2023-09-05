#ifndef __RECURSION_H__
#define __RECURSION_H__

#include "int_stack.h"

typedef struct node Node;

struct node
{
	struct node *next;
	int data;
};

/******************************************************************************

Function: Fibonacci - Find the number at the fibonacci series

Usage: int num = Fibonacci(5)

Description: return the number from the index given using recurtion.

Arguments: int index - The fibonacci index number.

Return value: int.

Time complexity: Worst: O(n^2).
Space complexity: Worst: O(n). 

******************************************************************************/

int Fibonacci(int);

int IterativeFibonacci(int);

/******************************************************************************

Function: StackSort - Sort an unsorted stack.

Usage: StackSort(stack)

Description: StackSort will sort a stack using two recursive functions.

Arguments: int index - The Fibonacci index number.

Return value: No return value.

Time complexity: Worst: O(n^2).
Space complexity: Worst: O(n). 

******************************************************************************/

void StackSort(int_stack_t *);

/******************************************************************************

Function: FlipList - Flips the nodes in a given SLL.

Usage: Node *sll = FlipList(Node *node)

Description: FlipList will flip the order of the nodes in a given SLL.

Arguments: Node * - A pointer to a node in the SLL.

Return value: A pointer to a node in the SLL.

Time complexity: Worst: O(n^2).
Space complexity: Worst: O(n). 

******************************************************************************/

Node *FlipList(Node *);

/******************************************************************************

Function: Strlen - Get the size of the string.

Usage: size_t size = Strlen("str")

Description: Strlen will count recursively the number of charecters in a given string.

Arguments: const char * - The string to be evaluated.

Return value: size_t size - the size of str.

Time complexity: Worst: O(n^2).
Space complexity: Worst: O(n). 

******************************************************************************/

size_t Strlen(const char *);

/******************************************************************************

Function: Strcmp - Compare two strings.

Usage: int is_equal = Strcmp(str1, str2)

Description: Strcmp will compare two strings and return the resulted outcome.

Arguments: const char * - Two strings to be compared.

Return value: int - 0 if equal, positive number if str1 is greater then str2 and 
              negative if the str2 is smaller then str1.

Time complexity: Worst: O(n^2).
Space complexity: Worst: O(n). 

******************************************************************************/

int Strcmp(const char *, const char *);

/******************************************************************************

Function: Strcpy - Copy one string to another.

Usage: char *destination = Strcpy(destination, source)

Description: Strcpy will copy one string to enother and return the starting 
             address of the destination strings.

Arguments: const char * - string to be copyed, char *  destination buffer.

Return value: char * - The starting address of the destination buffer;

Time complexity: Worst: O(n^2).
Space complexity: Worst: O(n). 

******************************************************************************/

char *Strcpy(char *, const char *);

/******************************************************************************

Function: Strcat - Concatenate one string to another.

Usage: char *destination = Strcat(destination, source)

Description: Strcat will concatenate one string to enother and return the starting 
             address of the destination strings.

Arguments: const char * - string to be concatenated, char * - destination buffer.
           string to be concatenated to the destination.

Return value: char * - The starting address of the destination buffer;

Time complexity: Worst: O(n^2).
Space complexity: Worst: O(n). 

******************************************************************************/

char *Strcat(char *destination, const char *source);

/******************************************************************************

Function: Strstr - Find the occurrence of a string in the haystack.

Usage: char *occurrence = Strstr(haystack, needle)

Description: Strstr will find the first occurrence of a sub string needle in 
             the haystack string.
Arguments: const char * - string to be checked for occurrence of needle.

Return value: char * - The starting address of the destination buffer;

Time complexity: Worst: O(n^2).
Space complexity: Worst: O(n). 

******************************************************************************/

char *Strstr(const char *haystack, const char *needle);

/*****************************************************************************/

#endif /* __RECURSION_H__ */
