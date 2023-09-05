/******************************************************************************

    Writer: Tal Aharon

    Reviewer: Matias Yoel Kaliroff Kravchik.

    Date: 30.04.2023

*******************************************************************************

    Description:

    The code is implementing a test for the Calculate function from a custom 
    library calculator.h. The Calculate function takes a string as input and 
    evaluates the arithmetic expression contained within it, returning the 
    result through a pointer.

    The main function calls CalculateTest and prints "CalculateTest() : passed." 
    if all the tests pass. The CalculateTest function contains multiple tests 
    for the Calculate function, using the assert macro to check the output of 
    Calculate against expected values. The tests cover a variety of inputs 
    and arithmetic operations, including invalid inputs that should trigger 
    syntax errors or division by zero.

    If all tests pass, the program returns 0 to indicate success. Otherwise, 
    it will exit with a non-zero exit code indicating failure.

******************************************************************************/
#include <stdio.h>
#include <assert.h>
#include "calculator.h"
void CalculateTest(void);
/*****************************************************************************/
int main(void)
{
	CalculateTest();
	puts("\nCalculateTest() : passed.");
	return (0);
}
/*****************************************************************************/
void CalculateTest(void)
{
	double result = 0;

	assert(SUCCESS == Calculate("0", &result));
	assert(0 == result);
	assert(SUCCESS == Calculate("0.567", &result));
	assert(0.567 == result);
	assert(SUCCESS == Calculate("150.6", &result));
	assert(150.6 == result);
	assert(SUCCESS == Calculate("-57.4", &result));
	assert(-57.4 == result);
	assert(SUCCESS == Calculate("+57.4", &result));
	assert(57.4 == result);
	assert(SUCCESS == Calculate("9", &result));
	assert(9 == result);
	assert(SUCCESS == Calculate("  5", &result));
	assert(5 == result);
	assert(SUCCESS == Calculate(".33", &result));
	assert(0.33 == result);
	assert(SUCCESS == Calculate("+.33", &result));
	assert(0.33 == result);

	assert(SYNTAX_ERROR == Calculate("(", &result));
	assert(SYNTAX_ERROR == Calculate(")", &result));
	assert(SYNTAX_ERROR == Calculate("*", &result));
	assert(SYNTAX_ERROR == Calculate("=", &result));
	assert(SYNTAX_ERROR == Calculate("+", &result));
	assert(SYNTAX_ERROR == Calculate("-", &result));
	assert(SYNTAX_ERROR == Calculate(".", &result));
	assert(SYNTAX_ERROR == Calculate("3 3", &result));
	assert(SYNTAX_ERROR == Calculate("..3", &result));
	assert(SYNTAX_ERROR == Calculate("++3", &result));
	assert(SYNTAX_ERROR == Calculate("", &result));
	assert(SYNTAX_ERROR == Calculate("    ", &result));

	assert(SUCCESS == Calculate("0+5", &result));
	assert(5 == result);
	assert(SUCCESS == Calculate("0 + 5", &result));
	assert(5 == result);
	assert(SUCCESS == Calculate("0 + -5", &result));
	assert(-5 == result);
	assert(SUCCESS == Calculate("0 + .5", &result));
	assert(0.5 == result);
	assert(SUCCESS == Calculate("0 - 5", &result));
	assert(-5 == result);
	assert(SUCCESS == Calculate("0 - +5", &result));
	assert(-5 == result);
	assert(SUCCESS == Calculate("0 - -5.6", &result));
	assert(5.6 == result);
	assert(SUCCESS == Calculate("3 - -5.6", &result));
	assert(8.6 == result);
	assert(SUCCESS == Calculate("0 + 5 + 6 - 4", &result));
	assert(7 == result);
	assert(SUCCESS == Calculate("0 + 5 -1.5 - 4", &result));
	assert(-0.5 == result);
	
	assert(SYNTAX_ERROR == Calculate("1 ++- 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 +-- 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 -+- 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 --- 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 + 3 5", &result));
	assert(SYNTAX_ERROR == Calculate("1 + 3 -", &result));

	assert(SUCCESS == Calculate("1+5 * 2", &result));
	assert(11 == result);
	assert(SUCCESS == Calculate("7 * 2", &result));
	assert(14 == result);
	assert(SUCCESS == Calculate("6 * 2 /1 + 3", &result));
	assert(15 == result);
	assert(SUCCESS == Calculate("1- 5 * 2 /4", &result));
	assert(-1.5 == result);
	assert(SUCCESS == Calculate("9*5*2/10 + 1 -2", &result));
	assert(8 == result);
	assert(SUCCESS == Calculate("9*-2", &result));
	assert(-18 == result);
	assert(SUCCESS == Calculate("9*+2 - 7*-3", &result));
	assert(39 == result);
	assert(SUCCESS == Calculate("1 / 3 * 0", &result));
	assert(0 == result);
	
	assert(SYNTAX_ERROR == Calculate("1 +* 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 *+- 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 /+- 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 +/ 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 ** 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 /* 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 + 3 -", &result));
	assert(SYNTAX_ERROR == Calculate("1 */ 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 // 3", &result));
	assert(MATH_ERROR == Calculate("1 / 0 * 3", &result));

	assert(SUCCESS == Calculate("(1+5) * 2", &result));
	assert(12 == result);
	assert(SUCCESS == Calculate("6 * 2 /(1 + 3)", &result));
	assert(3 == result);
	assert(SUCCESS == Calculate("(1- 5) * 2 /(4 - 6)", &result));
	assert(4 == result);
	assert(SUCCESS == Calculate("((1- 5) * 2 /(4 - 6))", &result));
	assert(4 == result);
	assert(SUCCESS == Calculate("((1- 5) + 2 /(4 - 6))", &result));
	assert(-5 == result);
	assert(SUCCESS == Calculate("9*5*2/(10 + 1 -2)", &result));
	assert(10 == result);
	assert(SUCCESS == Calculate("(1 + 9)*-2", &result));
	assert(-20 == result);
	assert(SUCCESS == Calculate("9*(+2 - 7)*-3", &result));
	assert(135 == result);
	assert(SUCCESS == Calculate("((((((5))))))", &result));
	assert(5 == result);

	assert(MATH_ERROR == Calculate("1 /( 0 * 3)", &result));
	assert(MATH_ERROR == Calculate("1 / (3 * 0)", &result));
	assert(SYNTAX_ERROR == Calculate("(1 + 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 + 3)", &result));
	assert(SYNTAX_ERROR == Calculate("((1 + 3)", &result));
	assert(SYNTAX_ERROR == Calculate("(1 +* 3))", &result));
	assert(SYNTAX_ERROR == Calculate("(1- 5)( * 2 /(4 - 6)", &result));
	assert(SYNTAX_ERROR == Calculate("((1- 5) * 2 /(4 - 6)", &result));
	assert(SYNTAX_ERROR == Calculate("(1- 5) * 2 /(4) - 6)", &result));
	assert(SYNTAX_ERROR == Calculate("(((((((((", &result));	
	assert(SYNTAX_ERROR == Calculate("((((()))))", &result));

	assert(SUCCESS == Calculate("(1+5) ^ 2", &result));
	assert(36 == result);
	assert(SUCCESS == Calculate("3 ^ 2 ^ 2", &result));
	assert(81 == result);
	assert(SUCCESS == Calculate("(3 ^ 2) ^ 2", &result));
	assert(81 == result);
	assert(SUCCESS == Calculate("3 ^ 2 ^ 3", &result));
	assert(6561 == result);
	assert(SUCCESS == Calculate("(3 ^ 2) ^ 3", &result));
	assert(729 == result);
	assert(SUCCESS == Calculate(".5 ^ 8", &result));
	assert(0.00390625 == result);
	assert(SUCCESS == Calculate("-3 ^ 3", &result));
	assert(-27 == result);
	assert(SUCCESS == Calculate("9 ^ 0.5", &result));
	assert(3 == result);
	assert(SUCCESS == Calculate("2 ^ -1", &result));
	assert(0.5 == result);
	assert(SUCCESS == Calculate("2 ^ -3", &result));
	assert(0.125 == result);
	
	assert(MATH_ERROR == Calculate("-1 ^ 0.5", &result));
	assert(MATH_ERROR == Calculate("-1 ^ -6.5", &result));
	assert(SYNTAX_ERROR == Calculate("1 ^^ 3", &result));
	assert(SYNTAX_ERROR == Calculate("1 ^++ 3", &result));
}
/*****************************************************************************/
