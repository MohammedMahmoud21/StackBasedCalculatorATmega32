# Smart Calculator
This project is a smart calculator that uses a stack data structure to store the operands and operators of an expression. The calculator is designed over ATmega32 MCU and has the following features:

* Can calculate complex operations, such as addition, subtraction, multiplication, division, and exponentiation.
* Has parentheses, which are used to group expressions together.
* Follows the order of operations.
* Supports associativity.

## Features

* Can calculate complex operations: The calculator can calculate complex expressions, such as `2 + 3 * 4 - 5 / 6`.
* Has parentheses: The calculator has parentheses, which are used to group expressions together. This makes it easier to read and write complex expressions.
* Follows the order of operations: The calculator follows the order of operations, which means that it evaluates expressions inside parentheses first, followed by multiplication and division, and then addition and subtraction. This ensures that the expressions are evaluated correctly.
* Supports associativity: The calculator supports associativity, which means that it evaluates expressions with the same operator in the same order, regardless of how they are written. For example, the expression `2 + 3 * 4` is evaluated as `(2 + 3) * 4`, because multiplication is asociated to the right.

## Requirements

* ATmega32 MCU
* LCD display
* Keypad
* Breadboard
* Jumper wires

## Instructions
1. Gather the necessary components.
2. Connect the components to the MCU.
3. Open the code form any IDE and compile it for your target (ATmega32).
4. Upload the code to the MCU.
