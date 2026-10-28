# Arbitrary Precision Calculator (APC)

## Project Overview

The Arbitrary Precision Calculator is a command-line application developed in C to perform arithmetic operations on integers that exceed the range supported by standard C data types.

The project uses a doubly linked list to represent numbers, storing each decimal digit in a separate node. This approach enables arithmetic calculations on large numbers without relying on fixed-size integer variables.

The calculator supports addition, subtraction, multiplication, and division through a modular implementation of arithmetic operations.

## Features

- Performs addition of large integers.
- Supports subtraction of large integers.
- Performs multiplication on large integers.
- Supports division of large integers.
- Handles numbers beyond the limits of standard integer data types.
- Uses dynamic memory allocation to manage digits.
- Implements arithmetic operations using a doubly linked list.

## Compilation

Compile the application using GCC:

```bash
gcc main.c addition.c subtraction.c multiplication.c division.c -o apc
```

## Usage

Run the calculator by providing two integers and an arithmetic operator:

```bash
./apc 12345678901234567890 * 98765432109876543210
```

Example output:

```text
1219326311370217952237463801111263526900
```

Replace the numbers and operator to perform other supported arithmetic operations.

## Technologies Used

- C Programming
- GCC Compiler
- Linux

## Concepts Used

- Doubly Linked Lists
- Dynamic Memory Allocation
- Pointers
- Functions and Modular Programming
- Arithmetic Algorithms
- Memory Management
- Command-Line Argument Handling

## Project Objective

The objective of this project is to implement arithmetic operations on arbitrarily large integers while developing a deeper understanding of linked-list-based number representation, dynamic memory management, and algorithm design in C.

## Author

Arjun
