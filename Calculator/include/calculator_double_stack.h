#ifndef __CALCULATOR_DOUBLE_STACK_H__
#define __CALCULATOR_DOUBLE_STACK_H__

typedef struct d_stack d_stack_t;

/******************************************************************************

Function: DStackPop - Pop the top element from the double stack.

Usage: double value = DStackPop(d_stack);

Description: This function pops the top element from the double stack and returns 
             it. If the stack is empty, it returns the maximum value of double 
             minus one.

Arguments: d_stack - A pointer to the double stack.

Return value: The function returns the top element of the double stack. 
              If the stack is empty, it returns the maximum value of double minus 
              one.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

double DStackPop(d_stack_t *);

/******************************************************************************

Function: DStackPeek - Return the top element from the double stack.

Usage: double value = DStackPeek(d_stack);

Description: This function returns the top element from the double stack without 
             removing it. If the stack is empty, it returns undefined behavior.

Arguments: d_stack - A pointer to the double stack.

Return value: The function returns the top element of the double stack.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

double DStackPeek(d_stack_t *);

/******************************************************************************

Function: DStackCreate - Create a new double stack.

Usage: d_stack_t *d_stack = DStackCreate(size);

Description: This function creates a new double stack with the specified size.

Arguments: size - The size of the double stack.

Return value: The function returns a pointer to the new double stack.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(size), Average: O(size), Best: O(size).

******************************************************************************/

d_stack_t *DStackCreate(size_t);

/******************************************************************************

Function: DStackDestroy - Destroy the double stack.

Usage: DStackDestroy(d_stack);

Description: This function destroys the double stack and frees its memory.

Arguments: d_stack - A pointer to the double stack.

Return value: None.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

void DStackDestroy(d_stack_t *);

/******************************************************************************

Function: DStackPush - Push an element onto the double stack.

Usage: DStackPush(d_stack, value);

Description: This function pushes an element onto the double stack.

Arguments: d_stack - A pointer to the double stack, value - The value to push 
           onto the stack.

Return value:  non zero on success, 0 on failure.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

int DStackPush(d_stack_t *, double);

/******************************************************************************

Function: DStackIsEmpty - Check if the double stack is empty.

Usage: int is_empty = DStackIsEmpty(d_stack);

Description: This function checks if the double stack is empty.

Arguments: d_stack - A pointer to the double stack.

Return value: The function returns 1 if the stack is empty, otherwise it returns 0.

Time complexity: Worst: O(1), Average: O(1), Best: O(1).
Space complexity: Worst: O(1), Average: O(1), Best: O(1).

******************************************************************************/

int DStackIsEmpty(d_stack_t *);

/*****************************************************************************/

size_t DStackSize(d_stack_t *);

/*****************************************************************************/

#endif /* __CALCULATOR_DOUBLE_STACK_H__ */
