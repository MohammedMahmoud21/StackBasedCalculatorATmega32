/***************************************************************************************/
/***************************************************************************************/
/**************************** Authors : Mohammed Elsayaad ******************************/
/**************************** Date : 9 June,2023         *******************************/
/**************************** Describtion: Main File     *******************************/
/*
This smart calculator uses a stack data structure to store the operands and operators of an expression. The stack is a LIFO (last in, first out) data structure, which means that the last element that is pushed onto the stack is the first element that is popped off.

The calculator works by first reading the expression from the user. Then, it pushes the operands onto the stack. When it encounters an operator, it pops the top two operands off the stack, performs the operation, and pushes the result back onto the stack.

The calculator can calculate complex operations, such as addition, subtraction, multiplication, division, and exponentiation. It also has parentheses, which are used to group expressions together. The calculator follows the order of operations, which means that it evaluates expressions inside parentheses first, followed by multiplication and division, and then addition and subtraction.

The calculator also supports associativity, which means that it evaluates expressions with the same operator in the same order, regardless of how they are written. For example, the expression `2 + 3 * 4` is evaluated as `(2 + 3) * 4`, because multiplication is asociated to the right.

The calculator is designed over ATmega32 MCU. The ATmega32 is a 8-bit microcontroller that has a built-in stack. This makes it easy to implement the stack data structure in the calculator.
*/
/***************************************************************************************/
/***************************************************************************************/


#include "Calculator_Interface.h"

int main(void)
{
	CALC_voidInit();
    CALC_voidStart();
	
	return 0;
}

