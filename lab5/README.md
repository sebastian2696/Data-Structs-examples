# Lab05-Project1
In this lab (project 1), students are expected to implement four ways (respectively by array, stack, queue, and linked list) to check whether input from a file is palindrome. By definition, a word, phrase, or sequence is called palindrome if it reads the same backward as forward. For this project, we only consider numerical inputs that read from a test file.

# Examples by pseudocode:
```
switch (File content) {
  case (empty): 
    return true;
  case ([1,2,3,4]): 
    return false;
  case ([1,2,2,1]): 
    return true;
  case ([1]): 
    return true;
  case ([1,2,1]): 
    return true;
}
```

# Specifications
The input file is in the format that each line only contains a single digit from 0 to 9. The file may contains any number of lines as inputs. You can use the same executable called array_gen that we used in Lab02 to generate your test file, but notice **you need specify the upper bound as 10** to guarantee each line is between 0 and 9. The commands to generate test file is:

```
make array_gen #if you don't have array_gen executable
./array_gen 10000 testFile 10
```

Essentially, you are required to implement the following four functions, where *fp* is the file pointer and the *count* is the number of digits contained in the test file. Please feel free to add any user-defined helper functions for your need. We have provided you useful functions in the skeleton code.
```
bool checkPalByArray(FILE *fp)
bool checkPalByQueueAndStack(FILE *fp, int count)
bool checkPalByStack(FILE *fp, int count)
bool checkPalByList(FILE *fp)

``` 

# HINT:
For all the four implementations, you need to consider at least three cases: 

1. empty input
2. odd number of inputs
3. even number of inputs

Start with very small test cases.

You can reuse the your former code (e.g. *read_array*) from your previous labs, but reusing other students' code is not allowed.

# Bonus Points
If all your code can output the correct answers and without memory error, you will get 100 points. Even better, if your all your four implementations are with time complexity O(n), you can get extra 20 points.