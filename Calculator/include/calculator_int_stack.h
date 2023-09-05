#ifndef __CALCULATOR_INT_STACK_H__
#define __CALCULATOR_INT_STACK_H__

typedef struct c_stack c_stack_t;

/******************************************************************************

Function: CStackPop - Removes the top element from the stack and returns it.

Usage: int result = CStackPop(my_stack);

Description: This function removes the top element from the stack and returns it. 
             If the stack is empty, it returns the null intacter ('\0').

Arguments: c_stack_t *c_stack - A pointer to the stack.

Return value: int - The top element of the stack.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

int CStackPop(c_stack_t *);

/******************************************************************************

Function: CStackPeek - Returns the top element of the stack without removing it.

Usage: int result = CStackPeek(my_stack);

Description: This function returns the top element of the stack without removing 
             it. If the stack is empty, it returns the null intacter ('\0').

Arguments: c_stack_t *c_stack - A pointer to the stack.

Return value: int - The top element of the stack.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

int CStackPeek(c_stack_t *);

/******************************************************************************

Function: CStackCreate - Creates a new stack with the given capacity.

Usage: c_stack_t *my_stack = CStackCreate(10);

Description: This function creates a new stack with the given capacity. 
             It allocates memory for the stack and its elements.

Arguments: size_t size - The capacity of the stack.

Return value: c_stack_t* - A pointer to the newly created stack.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(size), Average: O(size), Best: O(size).

******************************************************************************/

c_stack_t *CStackCreate(size_t);

/******************************************************************************

Function: CStackDestroy - Destroys the given stack and frees its memory.

Usage: CStackDestroy(my_stack);

Description: This function destroys the given stack and frees its memory.

Arguments: c_stack_t *c_stack - A pointer to the stack.

Return value: None.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

void CStackDestroy(c_stack_t *);

/******************************************************************************

Function: CStackPush - Adds the given element to the top of the stack.

Usage: CStackPush(my_stack, 'A');

Description: This function adds the given element to the top of the stack. 
             If the stack is full, it does nothing.

Arguments: c_stack_t *c_stack - A pointer to the stack.
int data - The element to be added.

Return value: None.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

int CStackPush(c_stack_t *, int);

/******************************************************************************

Function: CStackIsEmpty - Returns 1 if the stack is empty, 0 otherwise.

Usage: int result = CStackIsEmpty(my_stack);

Description: This function returns 1 if the stack is empty, 0 otherwise.

Arguments: c_stack_t *c_stack - A pointer to the stack.

Return value: int - 1 if the stack is empty, 0 otherwise.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

int CStackIsEmpty(c_stack_t *);

/*****************************************************************************/

size_t CStackSize(c_stack_t *);

/*****************************************************************************/

#endif /* __CALCULATOR_int_STACK_H__ */
