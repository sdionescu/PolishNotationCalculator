Polish Notation Calculator

<!-- 
((2+3)*((7+1)/4))/10
/ * + 2 3 / + 7 1 4 10

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
