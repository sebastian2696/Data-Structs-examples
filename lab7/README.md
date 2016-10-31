# Lab 7

In this lab, we will perform some timing analysis of lookups with
linked-lists and binary search trees.

You will reuse the singly-linked list and binary search
tree implementations of an associative array (also known as
dictionary) from your previous assignements with some small
modifications.

**If your code from those previous assignments does not work properly,
you will not be able to complete this lab. Be sure your previous code
works properly.**


# Program Changes

Recall that in your lab 4 assignment, you created a linked-list
associative array. Copy the .c file from that assignment here and
rename it to "dict_list.c". Similarly, copy the .c file from lab 6
here and rename it to "dict_tree.c". Run the "make" command to create
to executables called "dict_list" and "dict_tree". Be sure both
executables build successfully.

## Remove debug printing code
We want to peform timing analysis of lookups. **Any extra work done
in the code other than lookups may introduce noise to your timing analysis**
The type of work really time-consuming is printing, so we'll need
modify our previous code to not print elements as they're inserted or
looked up. This means removing calls to list_print and tree_print, **not
just commenting out the printfs inside those functions.** For the other
printfs, you can remove them by commenting them out. For example in
the list code:

```
// printf("Insert %s %s in sorted order\n", d.key, d.value);
```


## Add code to count the total number of successful lookups
You will have to modify your code in both programs to print the total
number of lookups that were successfully found. Here is an example of
the changes for the list code:

```
	struct list_data d;
	struct list_node *head = NULL;
	
	while (!feof(fp_data) && !ferror(fp_data)) {
		if (fscanf(fp_data, "%s %s", d.key, d.value) != 2)
			continue;
		
		if (use_sorted) {
			// printf("Insert %s %s in sorted order\n", d.key, d.value);
			struct list_node *node_before = list_find_before(head, d.key);
			if (list_insert(&head, node_before, d) < 0) {
				fprintf(stderr, "Error while inserting into list: %s\n", strerror(errno));
			}
		}
		else {
			// printf("Insert %s %s in front\n", d.key, d.value);

			if (list_insert(&head, NULL, d) < 0) {
				fprintf(stderr, "Error while inserting into list: %s\n", strerror(errno));
			}
		}

		// list_print(head);
	}


	char lookup_key[MAX_KEY_LEN];
	struct list_node *lookup_node;
	int found_count = 0;

	while (fp_lookup && !feof(fp_lookup) && !ferror(fp_lookup)) {
		if (fscanf(fp_lookup, "%s", lookup_key) != 1)
			continue;

		if ((lookup_node = list_find_exact(head, lookup_key)) != NULL) {
			// printf("Found: %s %s\n", lookup_node->data.key, lookup_node->data.value);
			found_count++;
		}
		else {
			printf("Failed to find: %s\n", lookup_key);
		}
	}

	printf("Found count is %d\n", found_count);
```

Notice the commented out lines, and the addition of found_count.

# Creating test data

We have supplied two Python scripts to help generate data for your
analyis.
Running:
```
$ python gen_words.py 10000
Wrote 10000 entries to words-10000.txt
```

Will write 10k words (really the integers from 0 to 9999 in random
order). To generate lookups from these words, run:
```
$ python gen_lookups.py 10000 100 
Wrote 100 lookups out of 10000 to lookups-100.txt
```
These creates a file of 100 word lookups from the set of items.

Now, you can supply these to your programs:
```
>time ./dict_list 1 words-10000.txt lookups-100.txt
found count is 100
0.42user 0.00system 0:00.42elapsed 100%CPU (0avgtext+0avgdata 1568maxresident)k
0inputs+0outputs (0major+438minor)pagefaults 0swaps
```

This measures the time to run dict_list with the 10k input file and
100 word lookups.

# Analysis
Use the tools to generate input sets of 10k words. Then measure this
run time for N=10 lookups, N=20, N=50, N=100, N=200, N=500,
etc. Compare the runtimes between the list and tree implementations
until you observe some interesting behavior.

# What to turn in
You are required to submit your code, along with a report, **including
a graph of the input size vs program run-time for each version of an
associative array**. Include some **explanations** of what you observe and
explain why you think that one program is faster or slower than the
other.

Your programs must run correctly, and must be free of memory misuse
and memory leaks. And be sure you are not printing extraneous
information to the output as you measure the runtime, to guarantee 
the accuracy.

