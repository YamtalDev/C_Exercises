#ifndef __INT_STACK_H__
#define __INT_STACK_H__

typedef struct int_stack int_stack_t;

/******************************************************************************

Function: IntStackPop - Removes the top element from the stack and returns it.

Usage: int result = IntStackPop(my_stack);

Description: This function removes the top element from the stack and returns it. 
             If the stack is empty, it returns the null intacter ('\0').

Arguments: int_stack_t *int_stack - A pointer to the stack.

Return value: int - The top element of the stack.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

int IntStackPop(int_stack_t *);

/******************************************************************************

Function: IntStackPeek - Returns the top element of the stack without removing it.

Usage: int result = IntStackPeek(my_stack);

Description: This function returns the top element of the stack without removing 
             it. If the stack is empty, it returns the null intacter ('\0').

Arguments: int_stack_t *int_stack - A pointer to the stack.

Return value: int - The top element of the stack.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

int IntStackPeek(int_stack_t *);

/******************************************************************************

Function: IntStackCreate - Creates a new stack with the given capacity.

Usage: int_stack_t *my_stack = IntStackCreate(10);

Description: This function creates a new stack with the given capacity. 
             It allocates memory for the stack and its elements.

Arguments: size_t size - The capacity of the stack.

Return value: int_stack_t* - A pointer to the newly created stack.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(size), Average: O(size), Best: O(size).

******************************************************************************/

int_stack_t *IntStackCreate(size_t);

/******************************************************************************

Function: IntStackDestroy - Destroys the given stack and frees its memory.

Usage: IntStackDestroy(my_stack);

Description: This function destroys the given stack and frees its memory.

Arguments: int_stack_t *int_stack - A pointer to the stack.

Return value: None.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

void IntStackDestroy(int_stack_t *);

/******************************************************************************

Function: IntStackPush - Adds the given element to the top of the stack.

Usage: IntStackPush(my_stack, 'A');

Description: This function adds the given element to the top of the stack. 
             If the stack is full, it does nothing.

Arguments: int_stack_t *int_stack - A pointer to the stack.
int data - The element to be added.

Return value: None.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

int IntStackPush(int_stack_t *, int);

/******************************************************************************

Function: IntStackIsEmpty - Returns 1 if the stack is empty, 0 otherwise.

Usage: int result = IntStackIsEmpty(my_stack);

Description: This function returns 1 if the stack is empty, 0 otherwise.

Arguments: int_stack_t *int_stack - A pointer to the stack.

Return value: int - 1 if the stack is empty, 0 otherwise.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

int IntStackIsEmpty(int_stack_t *);

/*****************************************************************************/

size_t IntStackSize(int_stack_t *);

/*****************************************************************************/

#endif /* __int_STACK_H__ */
