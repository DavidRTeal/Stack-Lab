Push-Pop Assembly Language Simulator
This is a simple assembly language simulator that supports basic commands for pushing and popping values onto/from a stack and checking the status of registers and the stack.

Table of Contents
Introduction
Usage
Command Line Options
File Descriptions
Example Input
Example Output
License
Introduction
This assembly language simulator provides a minimalistic environment for executing assembly-like commands. It supports the following commands:

status: Display the status of registers and the stack.
push %reg: Push the value of the specified register onto the stack.
push $val: Push a specific value onto the stack.
pop %reg: Pop a value from the stack into the specified register.
The simulator allows you to specify input and output files, stack limits, and initial register values through command-line arguments.

Usage
To compile and run the simulator, follow these steps:

Clone the repository.

Compile the code using a C compiler (e.g., gcc):

shell
Copy code
gcc push_pop.c stack_status.c -o push_pop_simulator
Run the simulator with the desired command-line options:

shell
Copy code
./push_pop_simulator -i input.txt -o output.txt -b 0x140 -l 0x100 -s 0x130
Command Line Options
The simulator supports the following command-line options:

-i <input_file>: Specify the input file containing a sequence of commands. If not provided, it reads from standard input (stdin).
-o <output_file>: Specify the output file where the status and other information will be written. If not provided, it writes to standard output (stdout).
-b <stack_bottom>: Set the high address of the stack (stack bottom) as a hexadecimal value. Default is 0x140.
-l <stack_limit>: Set the low address of the stack (stack limit) as a hexadecimal value. Default is 0x100.
-s <rsp_value>: Set the initial value of the %rsp register within the stack as a hexadecimal value. Default is 0x130.
-v: Enable verbose output for diagnostic information.
-h: Display help information, including available options.
File Descriptions
push_pop.c: The main source code file containing the implementation of the simulator.
push_pop.h: Header file defining constants, function prototypes, and data structures used in the simulator.
stack_status.c: Source code file containing the implementation of the stack_status function, which displays the status of registers and the stack.
README.md: This README file.
Example Input
Here is an example of an input file (input.txt) with a sequence of commands:

assembly
Copy code
push %rax
push %rbx
push $0x123
pop %rdx
status
Example Output
After running the simulator with the above input, the contents of the output file (output.txt) might look like this:

plaintext
Copy code
register_values:
    %rsp:           0x00000130
    %rax:           0x00000020
    %rbx:           0x00000030
    %rcx:           0x00000040
    %rdx:           0x00000123

stack:
    address         value
    >               0x00000140    0x00000123
                    0x00000138    0x00000030
                    0x00000130    0x00000020
