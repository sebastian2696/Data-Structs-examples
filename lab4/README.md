# Lab 4

An associative array (or dictionary) is an abstract data type that maps input keys to output values (for example: names to telephone numbers, or words to definitions). In this assignment, you will create an associative array to store keys and values with a simple singly linked-list implementation.

You will use the following definition of a linked list node:

```
#define MAX_KEY_LEN (32)
#define MAX_VALUE_LEN (32)

struct list_data {
  char key[MAX_KEY_LEN];
  char value[MAX_VALUE_LEN];
};

struct list_node {
  struct list_data data;
  struct list_node *next;
};

struct list_node *head = NULL;
```
You have to implement the following functions for your code:

```
void list_print(struct list_node *head);
struct list_node *list_find_exact(struct list_node *head, const char *key);
struct list_node *list_find_before(struct list_node *head, const char *key);
int list_insert(struct list_node **head, struct list_node *before,
                struct list_data data);
void list_destroy(struct list_node *head);
```

The exact semantics for each function are provided in the example code, and several test files are included.

Simply typing `make` will compile your code.

Your code will output the entire list after every insertion. After inserting all of the key­value pairs There is an additional command­line argument that takes in a list of entries to search for and prints the value for each entry or an error if no entry is found.

Example run command will look like this:

```
> ./dict 1 <inputfile> <optional lookups>
```
(The 1 indicates that the data should be sorted.)

Read the code to understand the details of command line arguments. Replace `dict` with `dict_full` to run the sample executable. Please make sure your executable gives the same output as our executable dict_full. 

**VERY IMPORTANT** Please read the skeleton code we gave you carefully line by line and understand it before you start coding. Most of you struggle trying to implement a functionality that is already provided to you.
