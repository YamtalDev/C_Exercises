/*=============================================================================

                           Costumer requirements:

===============================================================================

* A calculator program that can perform basic arithmetic operations (+, -, *, /)

* The program should take input from the user in the form of infix notation.

* The program should convert the infix notation to postfix notation and then 
  evaluate the expression.

* The program should handle errors gracefully and provide helpful error messages.

* The program should be implemented using a stack data structure.

* The program should be implemented in C language.

===============================================================================

                           CALCULATOR functionalities:

===============================================================================

1.) Convert infix notation to postfix notation.

2.) Evaluate postfix expression.

3.) Handle errors gracefully.

4.) Use stack data structure for implementation.

5.) Implemented in C language.

==============================================================================*/

#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

/*****************************************************************************/

typedef enum status
{
	SUCCESS,
	MATH_ERROR,
	SYNTAX_ERROR,
	INTERNAL_ERROR,
	STATUS_AMOUNT
} calculator_status_t;

/******************************************************************************

Function: Calculate - calculate a mathematical expression.

Usage: status_t status = Calculate(expression, &result);

Description: The Calculate function reads a mathematical expression in string 
             format, evaluates the expression and stores the result in a provided 
             pointer to double.

Arguments:

expression (const char*): A constant string representing the mathematical 
                          expression to be evaluated.
result (double*): A pointer to a double, where the result of the evaluation will 
                  be stored.

Return value:

calculator_status_t: an enum that defines the status of the calculation operation.
                     CALC_SUCCESS if the calculation was successful, CALC_ERROR 
                     if an error occurred during calculation.

Time complexity: Worst case time complexity of the function is O(n), where n is 
                 the length of the input expression.

Space complexity: The space complexity of the function is O(n), where n is the 
                  length of the input expression.

Note: The expression string should be a valid mathematical expression containing 
      operators such as +, -, *, /, and parentheses. The function does not support 
      advanced operations like trigonometric or logarithmic functions. The result 
      variable should be pre-allocated by the caller. In case of an error, the 
      result variable will not be modified. The function returns CALC_ERROR in 
      case of errors like invalid input expression, division by zero, or 
      stack overflow.

******************************************************************************/

calculator_status_t Calculate(const char *expression, double *result);

/*****************************************************************************/

#endif /* __CALCULATOR_H__ */
