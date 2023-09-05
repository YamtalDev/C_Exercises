/******************************************************************************

    Writer: Tal Aharon

    Reviewer: Matias Yoel Kaliroff Kravchik.

    Date: 30.04.2023

*******************************************************************************

                                 Description:

    This is a C code for a calculator program that can perform basic arithmetic 
    operations on input expressions. The code initializes tables for operator 
    precedence, operation handlers, and calculation functions. The Calculate 
    function takes an expression string as input and returns the calculated 
    result if successful. The code utilizes two stacks to store the 
    operands and operators of the expression.

******************************************************************************/
#include <ctype.h>                   /* isdigit        */
#include <assert.h>                  /* assert         */
#include <string.h>                  /* strlen         */
#include <stdlib.h>                  /* strtod         */
#include <math.h>                    /* pow            */
                                     /*                */
#include "calculator.h"              /* Internal API   */
#include "calculator_int_stack.h"    /* Internal API   */
#include "calculator_double_stack.h" /* Internal API   */
/*****************************************************************************/
/* Initialize */
#define INITIALIZED (1)
/* uninitialized */
#define NOT_INITIALIZED (0)
/* IGNORE variable */
#define IGNORE(X) ((void)(X))
/* Next event in expression */
#define NEXT_EVENT(X,N) (*(*X + N))
/* Amount of all ascii chars */
#define ALL_ASCII_CHARACTERS (256)
/* Increment string to next event */
#define INCREMENT_EVENT(X) (++(*X))

typedef calculator_status_t (*calculate)(double,  double, double *);
typedef calculator_status_t (*handler)(d_stack_t *, c_stack_t *, char **);
/*****************************************************************************/
typedef enum
{
	NONE = 0, OPEN_PARENTHESES, CLOSING_PARENTHESES,
	ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION,
	POWER, ANOTHER_POWER, OPERATIONS_AMOUT

} prec_t;
/*****************************************************************************/
typedef enum
{
	OPERAND = 0, OPERATOR, ERROR, END, NUMBER_OF_STATES

} state_t;
/*****************************************************************************/
typedef struct                                 /*                            */
{                                              /*  ▄██████████████▄ ▐█▄▄▄▄█▌ */ 
	handler operation;                         /*  ██████▌▄▌▄▐▐▌███▌ ▀▀██▀▀  */
	state_t next_state;                        /*  ████▄█▌▄▌▄▐▐▌▀███▄▄▄█▌    */
} handler_t;                                   /*  ▄▄▄▄▄██████████████▀      */
/*****************************************************************************/
static prec_t prec_table[ALL_ASCII_CHARACTERS] = {0};
static calculate calculate_operations[OPERATIONS_AMOUT] = {NULL};
static handler_t calc_table[NUMBER_OF_STATES - ERROR][ALL_ASCII_CHARACTERS];
/*****************************************************************************/
static prec_t Getprec(char **);
static void InitprecTable(void);
static void InitCalculatorTable(void);
static void InitOparationsTable(void);
static void SetResult(d_stack_t *, double *);
static state_t GetNextState(state_t, char **);
static void CalculatorCleanUp(d_stack_t *, c_stack_t *);
static calculator_status_t Evaluate(d_stack_t *, c_stack_t *);
static calculator_status_t CalculateResult(prec_t, double, double, double *);
static calculator_status_t CalculatorInit(d_stack_t **, c_stack_t **, const char *);
static calculator_status_t GetNextStatus(d_stack_t *, c_stack_t *, state_t, char **);
/*****************************************************************************/
static calculator_status_t Add(double, double, double *);
static calculator_status_t Div(double, double, double *);
static calculator_status_t Sub(double, double, double *);
static calculator_status_t Exp(double, double, double *);
static calculator_status_t Mul(double, double, double *);
static calculator_status_t Err(d_stack_t *, c_stack_t *, char **);
static calculator_status_t Power(d_stack_t *, c_stack_t *, char **);
static calculator_status_t IgnoreSpace(d_stack_t *, c_stack_t *, char **);
static calculator_status_t PointHandler(d_stack_t *, c_stack_t *, char **);
static calculator_status_t UnaryOperator(d_stack_t *, c_stack_t *, char **);
static calculator_status_t OperandHandler(d_stack_t *, c_stack_t *, char **);
static calculator_status_t OpenParenthesis(d_stack_t *, c_stack_t *, char **);
static calculator_status_t FinalCalculation(d_stack_t *, c_stack_t *, char **);
static calculator_status_t OperatordHandler(d_stack_t *, c_stack_t *, char **);
static calculator_status_t ClosingParenthesis(d_stack_t *, c_stack_t *, char **);
static calculator_status_t Parentheses_Error(double a, double b, double *result);
static calculator_status_t HandleEvent(d_stack_t *, c_stack_t *, char **, prec_t);
/*****************************************************************************/
calculator_status_t Calculate(const char *expression, double *result)
{
	char *event = NULL;
	d_stack_t *values_stack = NULL;
	c_stack_t *operators_stack = NULL;
	state_t next_state = ERROR;
	state_t current_state = OPERAND;
	calculator_status_t status = SUCCESS;

	assert(expression);
	event = (char *)expression;
	status = CalculatorInit(&values_stack, &operators_stack, expression);

	while(SUCCESS == status && END != current_state)
	{
		next_state = GetNextState(current_state, &event);
		status = GetNextStatus(values_stack, operators_stack, current_state, &event);
		current_state = next_state;
	}

	SetResult(values_stack, result);
	CalculatorCleanUp(values_stack, operators_stack);
	return (status);
}
/*****************************************************************************/
static calculator_status_t CalculatorInit
(d_stack_t **values_stack, c_stack_t **operators_stack, const char *expression)
{
	size_t size = 0;
	static int table_initialized = NOT_INITIALIZED;
	if(NULL == expression)
	{
		return (INTERNAL_ERROR);
	}

	size = strlen(expression);
	*operators_stack = CStackCreate(size + 1);
	if(NULL == *operators_stack)
	{
		return (INTERNAL_ERROR);
	}

	*values_stack = DStackCreate(size + 1);
	if(NULL == values_stack)
	{
		CStackDestroy(*operators_stack);
		return (INTERNAL_ERROR);
	}

	if(!table_initialized)
	{
		InitprecTable();
		InitOparationsTable();
		InitCalculatorTable();
		table_initialized = INITIALIZED;
	}

	return (SUCCESS);
}
/*****************************************************************************/
static void CalculatorCleanUp(d_stack_t *values_stack, c_stack_t *operators_stack)
{
	DStackDestroy(values_stack);
	CStackDestroy(operators_stack);
	values_stack = NULL;
	operators_stack = NULL;
}
/*****************************************************************************/ 
static void InitprecTable(void)
{
	prec_table['^'] = POWER;
	prec_table['*'] = MULTIPLICATION;
	prec_table['/'] = DIVISION;
	prec_table['+'] = ADDITION;
	prec_table['-'] = SUBTRACTION;
}
/*****************************************************************************/ 
static void InitOparationsTable(void)
{
	calculate_operations[POWER] = Exp;
	calculate_operations[DIVISION] = Div;
	calculate_operations[ADDITION] = Add;
	calculate_operations[SUBTRACTION] = Sub;
	calculate_operations[MULTIPLICATION] = Mul;
	calculate_operations[OPEN_PARENTHESES] = Parentheses_Error;
}
/*****************************************************************************/
static void InitCalculatorTable(void)
{
	int i = 0, j = 0;
	for(;j < (NUMBER_OF_STATES - ERROR); ++j)
	{
		for(i = 0; i < ALL_ASCII_CHARACTERS; ++i)
		{
			calc_table[j][i].operation = Err;
			calc_table[j][i].next_state = ERROR;
		}
	}

	for(i = '0'; i <= '9'; ++i)
	{
		calc_table[OPERAND][i].next_state = OPERATOR;
		calc_table[OPERAND][i].operation = OperandHandler;
	}

	calc_table[OPERATOR]['^'].operation = Power;
	calc_table[OPERATOR]['^'].next_state = OPERAND;

	calc_table[OPERATOR]['*'].operation = OperatordHandler;
	calc_table[OPERATOR]['*'].next_state = OPERAND;

	calc_table[OPERATOR]['/'].operation = OperatordHandler;
	calc_table[OPERATOR]['/'].next_state = OPERAND;

	calc_table[OPERAND]['-'].operation = UnaryOperator;
	calc_table[OPERAND]['-'].next_state = OPERATOR;
	calc_table[OPERATOR]['-'].operation = OperatordHandler;
	calc_table[OPERATOR]['-'].next_state = OPERAND;

	calc_table[OPERAND]['+'].operation = UnaryOperator;
	calc_table[OPERAND]['+'].next_state = OPERATOR;
	calc_table[OPERATOR]['+'].operation = OperatordHandler;
	calc_table[OPERATOR]['+'].next_state = OPERAND;

	calc_table[OPERATOR][')'].operation = ClosingParenthesis;
	calc_table[OPERATOR][')'].next_state = OPERATOR;

	calc_table[OPERAND]['('].operation = OpenParenthesis;
	calc_table[OPERAND]['('].next_state = OPERAND;

	calc_table[OPERAND][' '].operation = IgnoreSpace;
	calc_table[OPERAND][' '].next_state = OPERAND;
	calc_table[OPERATOR][' '].operation = IgnoreSpace;
	calc_table[OPERATOR][' '].next_state = OPERATOR;

	calc_table[OPERAND]['.'].operation = PointHandler;
	calc_table[OPERAND]['.'].next_state = OPERATOR;

	calc_table[OPERATOR]['\0'].operation = FinalCalculation;
	calc_table[OPERATOR]['\0'].next_state = END;
}
/*****************************************************************************/
static calculator_status_t GetNextStatus
(d_stack_t *values_stack, c_stack_t *operators_stack, state_t state, char **event)
{
	assert(values_stack); assert(operators_stack);
	return (calc_table[state][(int)(**event)].operation(values_stack, operators_stack, event));
}
/*****************************************************************************/
static state_t GetNextState(state_t state, char **event)
{
	assert(*event);
	return (calc_table[state][(int)(**event)].next_state);
}
/*****************************************************************************/
static prec_t Getprec(char **event)
{
	return (prec_table[(int)**event]);
}
/*****************************************************************************/
static calculator_status_t CalculateResult
(prec_t prec, double a, double b, double *result)
{
	return (calculate_operations[prec](a, b, result));
}
/*****************************************************************************/
static void SetResult(d_stack_t *values_stack, double *result)
{
	*result = DStackPeek(values_stack);
}
/*****************************************************************************/
static calculator_status_t OperandHandler
(d_stack_t *values_stack, c_stack_t *operators_stack, char **event)
{
	double num = strtod(*event, event);
	DStackPush(values_stack, num);
	IGNORE(operators_stack);
	return (SUCCESS);
}
/*****************************************************************************/
static calculator_status_t Err
(d_stack_t *values_stack, c_stack_t *operators_stack, char **event)
{
	IGNORE(event);
	IGNORE(values_stack);
	IGNORE(operators_stack);
	return (SYNTAX_ERROR);
}
/*****************************************************************************/
static calculator_status_t IgnoreSpace
(d_stack_t *values_stack, c_stack_t *operators_stack, char **event)
{
	IGNORE(operators_stack);
	IGNORE(values_stack);
	INCREMENT_EVENT(event);
	return (SUCCESS);
}
/*****************************************************************************/
static calculator_status_t OpenParenthesis
(d_stack_t *values_stack, c_stack_t *operators_stack, char **event)
{
	CStackPush(operators_stack, OPEN_PARENTHESES);
	INCREMENT_EVENT(event);
	IGNORE(values_stack);
	return (SUCCESS);
}
/*****************************************************************************/
static calculator_status_t PointHandler
(d_stack_t *values_stack, c_stack_t *operators_stack, char **event)
{
	if(!isdigit(NEXT_EVENT(event, 1)))
	{
		return (SYNTAX_ERROR);
	}

	return (OperandHandler(values_stack, operators_stack, event));
}
/*****************************************************************************/
static calculator_status_t ClosingParenthesis
(d_stack_t *values_stack, c_stack_t *operators_stack, char **event)
{
	prec_t stack_top = CStackPeek(operators_stack);
	while(!CStackIsEmpty(operators_stack) && OPEN_PARENTHESES != stack_top)
	{
		Evaluate(values_stack, operators_stack);
		stack_top = CStackPeek(operators_stack);
	}

	if(CStackIsEmpty(operators_stack))
	{
		return (SYNTAX_ERROR);
	}

	INCREMENT_EVENT(event);
	CStackPop(operators_stack);
	return (SUCCESS);
}
/*****************************************************************************/
static calculator_status_t UnaryOperator
(d_stack_t *values_stack, c_stack_t *operators_stack, char **event)
{
	char next_event = NEXT_EVENT(event, 1);
	char next_next_event = NEXT_EVENT(event, 2);
	int no_number_after_point = (('.' == next_event) && !isdigit(next_next_event));
	int no_number_or_point_after_event = !(isdigit(next_event) || ('.' == next_event));

	if(no_number_or_point_after_event || no_number_after_point)
	{
		return (SYNTAX_ERROR);
	}

	return (OperandHandler(values_stack, operators_stack, event));
}
/*****************************************************************************/
static calculator_status_t FinalCalculation
(d_stack_t *values_stack, c_stack_t *operators_stack, char **event)
{
	calculator_status_t status = SUCCESS;
	while(SUCCESS == status && !CStackIsEmpty(operators_stack))
	{
		status = Evaluate(values_stack, operators_stack);
	}

	IGNORE(event);
	return (status);
}
/*****************************************************************************/
static calculator_status_t Evaluate(d_stack_t *values_stack, c_stack_t *operators_stack)
{
	double result = 0.0;
	double operand1 = 0, operand2 = 0;
	calculator_status_t status = SUCCESS;
	prec_t prec = CStackPop(operators_stack);

	operand2 = DStackPop(values_stack);
	operand1 = DStackPop(values_stack);

	status = CalculateResult(prec, operand1, operand2, &result);
	DStackPush(values_stack, result);
	return (status);
}
/*****************************************************************************/
static calculator_status_t OperatordHandler
(d_stack_t *values_stack, c_stack_t *operators_stack, char **event)
{
	prec_t prec = Getprec(event);
	return (HandleEvent(values_stack, operators_stack, event, prec));
}
/*****************************************************************************/
static calculator_status_t HandleEvent
(d_stack_t *values_stack, c_stack_t *operators_stack, char **event, prec_t prec)
{
	calculator_status_t status = SUCCESS;
	prec_t top = CStackPeek(operators_stack);
	while(SUCCESS == status && !CStackIsEmpty(operators_stack) && prec <= top)
	{
		status = Evaluate(values_stack, operators_stack);
		top = CStackPeek(operators_stack);
	}

	CStackPush(operators_stack, prec);
	INCREMENT_EVENT(event);
	return (status);
}
/*****************************************************************************/
static calculator_status_t Power
(d_stack_t *values_stack, c_stack_t *operators_stack, char **event)
{
	calculator_status_t status = SUCCESS;
	prec_t top = CStackPeek(operators_stack);
	while(SUCCESS == status && !CStackIsEmpty(operators_stack) && ANOTHER_POWER <= top)
	{
		status = Evaluate(values_stack, operators_stack);
		top = CStackPeek(operators_stack);
	}

	CStackPush(operators_stack, POWER);
	INCREMENT_EVENT(event);
	return (status);
}
/*****************************************************************************/
static calculator_status_t Parentheses_Error(double a, double b, double *result)
{
	IGNORE(a);
	IGNORE(b);
	IGNORE(result);
	return (SYNTAX_ERROR);
}
/*****************************************************************************/
static calculator_status_t Add(double a, double b, double *result)
{
	*result = (a + b);
	 return (SUCCESS);
}
/*****************************************************************************/
static calculator_status_t Sub(double a, double b, double *result)
{
	*result = (a - b);
	return (SUCCESS);
}
/*****************************************************************************/
static calculator_status_t Mul(double a, double b, double *result)
{
	*result = (a * b);
	return (SUCCESS);
}
/*****************************************************************************/
static calculator_status_t Exp(double a, double b, double *result)
{
	if((0 > a) && (0 != (b - (int)b)))
	{
		return (MATH_ERROR);
	}

	*result = pow(a, b);
	return (SUCCESS);
}
/*****************************************************************************/
static calculator_status_t Div(double a, double b, double *result)
{
	if(!b)
	{
		return (MATH_ERROR);
	}

	*result = (a / b);
	return (SUCCESS);
}
/*****************************************************************************/
