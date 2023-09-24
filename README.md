# AP-TA-exam
Expression Tree



In implementing an expression tree, a tree structure consisting of several operators and operands is used. Each of the operators has two working modes (Arithmetic and Bitwise) and based on which mode they are in, they perform a specific operation on the operands according to the table below:

Operator	Working Mode
NOT(x)    Arithmetic=> -	Bitwise	=> ~x
AND(x,y)	Arithmetic=> x*y	Bitwise	=> x & y 
OR(x,y)	Arithmetic=> x+y	Bitwise	=> x| y 
XOR(x1,...,xn)	Arithmetic	=>Median(x1,...,xn)    Bitwise	 => x1^...^xn
	

The tree operands are also numeric values that are provided to you in one of the four bases 2, 8, 10 or 16.

At the beginning of the program, the tree structure in a specific format is provided to you. Consider each of the leaves as a numeric value (operand) and the internal nodes as the operators of this exercise. The operators can be unary (NOT), binary (AND, OR) or n-ary (XOR). So after creating the expression tree, make sure the stated constraints are met for all the nodes of the tree. For example, a node corresponding to a binary operator should have exactly two children and the leaves of the tree should be numeric values. Handle any potential errors using Exception Handling and display an appropriate error message to the user if needed.

To calculate the result of an expression tree, we move from the leaves and apply the operators at each level until we reach the root of the tree. The desired value is equal to the result of the operator corresponding to the root. To make the program more flexible, three capabilities of changing the base of an operand, the working mode of an operator, and the value of an operand during program execution will be implemented. Next, we introduce the required instructions for this:

Calculating tree result
evaluate -<base>
After executing this instruction, we display the result of the tree in base base, where base is chosen from h, d, o, b, corresponding to bases 16, 10, 8, 2 respectively.

Changing base of a specific operand
rebase -<base> <index>
After executing this instruction, we transfer the value stored in leaf with index index to base base. Note that this is not transferring the value from one base to another, but the initial value remains constant and only the base changes, which will not be possible in some scenarios. For example, if the operand value is 'a1' and its base is 16, we cannot change the base to 2 because the symbol 'a' has no meaning in base 2. Also when constructing the tree (at the beginning of the program), consider the default base for all operands as decimal.

Changing working mode of a specific operator
remode -<mode> <index>
After executing this instruction, the working mode of the operator corresponding to the node with index index of the tree is changed to mode mode. The value of mode is chosen from b, a which respectively specify Bitwise and Arithmetic modes. When constructing the tree, also consider the default mode for all operators as Arithmetic.

Changing value of a specific operand
reset <index> <value>
Note that in implementing this exercise, inheritance and polymorphism concepts should be used and using conditional statements like if or switch to detect operand base or operator mode during computations will not be accepted!

Input
In the first line of the standard input, the number n (number of tree nodes) is entered and in the next n lines, the required information for creating each tree node is provided according to the pattern below:

<index> <parent_index> <type> <argument>

The index value specifies the index of a node. Note that the root node index is zero. The parent_index value specifies the index of this node's parent in the tree. The type value is either operator or input which respectively specify whether the node is an operator or an operand. The argument also specifies the operator type for operators and the operand value for operands. The subsequent lines of the standard input will also contain a number of commands in the defined format and your program will handle them in order.

Output
With reaching each evaluate instruction in the standard input, print the tree result in one line in the standard output.






<body>
    <div class="container">
        <div >
            <h3>Sample Input:</h3>
            <pre>
6
0 -1 operator OR
1 0 operator AND
2 0 operator NOT
3 1 input 10
4 1 input 3
5 2 input 5
evaluate -d #output 25
rebase -b 3
evaluate -d #output 1
remode -b 1
evaluate -d #output 25 -3
reset 5 6
evaluate -b #output -100
            </pre>
        </div>
</body>

