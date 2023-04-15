Write a calculator that performs arithmetic operations on a string that contains operands and operations written in a Polish notation
Development should proceed in the following order:
	- Development of the interface specification
	- The simplest tests for expressions containing two operands and one operation
	- Implementation of the code so that all tests are performed
	- Development of tests for expressions containing three operands and two operations
	- Implementation of the code so that all tests are performed
	- Development of tests for complex expressions
	- Implementation of the code so that all tests are performed

<!-- 
/ * + 2 3 / + 7 1 4 10
((2+3)*((7+1)/4))/10

stack: 10
stack: 4 10
stack: 1 4 10
stack: 7 1 4 10

found +: push (pop() + pop()) => push(8)

stack: 8 4 10

found /: push (pop() / pop()) => push(2)

stack: 2 10
stack: 3 2 10
stack: 2 3 2 10

found +: push (pop() + pop()) => push(5)

stack: 5 2 10

found *: push (pop() * pop()) => push(10)
stack: 10 10

found /: push (pop() / pop()) => push(1)
 -->
