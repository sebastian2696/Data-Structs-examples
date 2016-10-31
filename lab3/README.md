# Description
In this assignment, you are required to implement a postfix (also called Reverse Polish Notation) calculator called dcc. There is a classic calculator on UNIX systems called dc that can use the same syntax as your calculator and that you can use to check your results. I have provided some source code that you can use as the basis of your program. It has several critical parts that have been stripped out. Use the comments in the example to figure out what to write. Implementing your calculator will require implementing a stack. Your program only has to handle double-precision floating point (C type double) numbers.

You can find out more about the dc program, or any of the C library functions by using the man (standing for manual) command, i.e. man dc at the command line.

# Commands
You must implement the following single-character commands:

```
p : Print the value of the top element (but leave it the top of the stack).
f : Print the value of every element on the stack, one per line,
    but leave them all in the stack.
c : Clear the stack, rendering it empty.
+ : Pop two values off the stack,
    add them, and push the result.
- : Pop two values off the stack,
    subtract the first one popped from the second one popped, and push the result.
* : Pop two values off the stack,
    multiply them, and push the result.
/ : Pop two values off the stack,
    divide the first one popped from the second one popped, and push the result.
    (Note that by default, UNIX dc uses integers while your program uses doubles).
% : Pop two values off the stack,
    push the remainder of the result that the '/' command would compute.
^ : Pop two values off the stack.
    Compute an exponentiation of the first one popped as the exponent and the
    second one popped as the base and push that.
```

# Example Output
You are also provided several input files, and a compiled executable called dcc_stack.example that uses doubles as data types. You can run the input files against dc or dcc_stack.example to see what the correct output from your program should be.

```
>cat dcc-input-00.txt    
3 4 + p

>./dcc_stack.example dcc-input-00.txt
7.000000
```

In the above, the cat command prints out the contents of the dcc-input-00.txt file. When that file is used as an input, to the dcc_stack.example command, it prints 7. That is because the input file contains a command to compute 3 + 4 and print the result.

```
>cat dcc-input-01.txt        
4 3 + 2 8 - * p

>./dcc_stack.example dcc-input-01.txt 
-42.000000
```

Using the dcc-input-01.txt file, the output is -42. That is becuase the input file contains the command to compute (4 + 3) * (2 - 8) and print the result. You should try the same with the other example input files.

# Compilation

./gcc -o dcc_stack dcc_stack.c

# Implement a queue version

Notice: for the example of dcc-input-01.txt ( 4 3 + 2 8 - * p), the result for queue version by running ./dcc_queue.example dcc-input-01.txt should be -40.000000 or 40.000000, depending on your program does 7 - 2 or 2 - 7 for queue-based calculator. Either one is accetable. But for stack-based one, the answer should be -42.000000
