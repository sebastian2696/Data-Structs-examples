# Lab 6

In this lab, we will write a binary search tree implementation of
an associative array (also known as dictionary). As in the previous
lab, you created an associative array to store keys and values
with a simple singly linked-list implementation. But you will use
a binary search tree this time.

Use the following definition of a tree node:

```
#define MAX_KEY_LEN (32)
#define MAX_VALUE_LEN (32)

struct tree_data {
	char key[MAX_KEY_LEN];
	char value[MAX_VALUE_LEN];
};

struct tree_node {
	struct tree_data data;
	struct tree_node *left;
	struct tree_node *right;
};

```
You have to implement the following functions for your code:

```
void tree_print(struct tree_node *node);
struct tree_node *tree_find(struct tree_node *root, const char *key);
int tree_insert(struct tree_node **p_root, struct tree_data data);
void tree_destroy(struct tree_node *root);
```

The exact semantics for each function are provided in the example
code, and several test files are included. *If you re-use code from a
previous lab, you may only reuse your own code.*

There is no tree_remove function that you have to implement.

As before, simply typing `make` will compile your code.

Your code will output the entire tree in order after every
insertion. After inserting all of the key­value pairs, there is an additional command­line argument that takes in a list of entries to search for and prints the value for each entry or an error if no entry is found.

Example run command will look like this:

```
> ./dict <inputfile> <lookup_file>
```
(There is no argument for sorting in this program. All the inserted
data should be always be in the correct order inside the tree.)

This example shows inserting entries, looking them up, and removing
them.

```
>./dict_full dict_in_00.txt lookup_00.txt
Insert hello world in sorted order
hello world
Insert spam eggs in sorted order
hello world
spam eggs
Insert foo bar in sorted order
foo bar
hello world
spam eggs
Insert aardvark blagh in sorted order
aardvark blagh
foo bar
hello world
spam eggs
Found: hello world
Found: spam eggs
Found: foo bar
Found: aardvark blagh
Failed to find: notpresent

```

Read the code to understand the details of command line arguments. Replace `dict` with `dict_full` to run the sample executable. Note that your executable must give the exact same output as our executable. 

**VERY IMPORTANT** Please read the skeleton code we gave you carefully
  line by line and understand it before you start coding. Many of you
  have struggled trying to implement a functionality that is already
  provided to you.

