# Push-Pop Assembly Language Simulator

This is a simple assembly language simulator that supports basic commands for pushing and popping values onto/from a stack and checking the status of registers and the stack.

## Table of Contents

- [Introduction](#introduction)
- [Usage](#usage)
- [Command Line Options](#command-line-options)
- [File Descriptions](#file-descriptions)
- [Example Input](#example-input)
- [Example Output](#example-output)
- [License](#license)

## Introduction

This assembly language simulator provides a minimalistic environment for executing assembly-like commands. It supports the following commands:

- `status`: Display the status of registers and the stack.
- `push %reg`: Push the value of the specified register onto the stack.
- `push $val`: Push a specific value onto the stack.
- `pop %reg`: Pop a value from the stack into the specified register.

The simulator allows you to specify input and output files, stack limits, and initial register values through command-line arguments.

## Usage

To compile and run the simulator, follow these steps:

1. Clone the repository.
2. Compile the code using a C compiler (e.g., gcc):

   ```shell
   gcc push_pop.c stack_status.c -o push_pop_simulator

./push_pop_simulator -i input.txt -o output.txt -b 0x140 -l 0x100 -s 0x130

push %rax
push %rbx
push $0x123
pop %rdx
status


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

