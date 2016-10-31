# Frequently Asked Questions About The Assignment

#### How do I test my code partially?

First, you have to realize that the code we have given is not compilable. But it is fairly simple to make it compilable. Just add return statements to the end of your functions to make compiler happy, then it should run as-is. For all non-void function in mean_median.c just add

```
return 0;
```

#### How should I run stuff?

First, I'd make sure I am able to compile array_gen so that I can generate an input file.
```
> make array_gen
```
will compile array_gen.c to generate executable named array_gen.

```
> ./array_gen 10 test_input 100
```
will create a file named test_file that has 10 integers that has 100 as upper limit.

When you are ready to compile and test your code:
```
> make mean_median
```
will compile main.c and mean_median.c together to create an executable named mean_median.

```
> ./mean_median test_input
```
will run your code.

#### Where should I begin?

First thing you should do, is to read main.c and understand how it works.

The functions print_array, mean_array and median_array are relatively easier compared to other two. I'd start by implementing one of these three. For all of them, the function takes two argument array A(as a pointer) and size n. I think all of you by now can write a piece of code that can find the mean/median of an array given its size. And even simpler, to print it out.

Then you can start coding read_array function which might be the hardest one.

#### read_array function

There are many ways to implement this function. The algorithm I endorsed so far is this

1. Scan file and just count number of lines
2. Allocate space for the array
3. Rewind the file pointer back to the beginning of the file. (ie rewind(fp))
4. Scan file again populating the array
5. Return number of lines

###### Details
The function takes a file pointer and a *pointer to an integer array* as arguments. Very, very, very important two things to note here: 1) File pointer is already opened for you in main function, something you can learn by reading main.c! 2) p_A is *NOT* an array, it is a *pointer to* an array. This will allow you to allocate space for the array that p_A points to.

Most common problem everyone facing is how to create space for the array and populate it.

```
p_A = malloc(/*...........*/);    #not correct!
```

As p_A is not the array but a pointer to it, allocating a space for p_A is not something we want to do. Note that if you do it this way it _might_ compile and run. But the results generated will be junk, because you will be touching wrong memory addresses.

```
*p_A = malloc(/*...........*);    #correct!
```

p_A is a pointer to an array which we want to allocate space for. To get that array that is pointed by p_A you "dereference" it. If you don't know what dereferencing is, please go back and study pointers.

After creating the array the same logic must be applied when you fscanf values from file into the array(4th step in the algorithm described above). Remember the last argument for fscanf: address of the variable that will be changed. If you go step by step

- The value I want to change is ith index of an array that is pointed by p_A
- Therefore I must pass **address of the ith index of the array that p_A points to**

Then try to find how to get **address of the ith index of the array that p_A points to**

- p_A           : the pointer
- *p_A          : the array pointed by the pointer
- (*p_A)[i]     : ith index of the array that p_A points to
- &((\*p_A)[i])  : **address of the ith index of the array that p_A points to**

So, your fscanf will look something like this:

```
fscanf(/*......*/ , &((*p_A)[i]));
```

#### select_sort function

This function is simple as it was covered in lectures and in the textbook. Just like three easier functions you have array with name A and size n. Note that textbook defines a "macro" named SWAP to swap two values in the array. I advice against doing it as it is prone to weird syntax errors. If you check the code in the textbook, replace the line that does SWAP(), with your own code, that essentially swaps two values in the array through a third temporary variable.

#### Common pitfalls & General recommendations

- Read the main function and make sure you understand it.
- File pointer is opened and closed for you. Do not fopen or fclose at any point.
- You are not going to get user input for anything. Input file is given as command line argument and taken care of in main function.
