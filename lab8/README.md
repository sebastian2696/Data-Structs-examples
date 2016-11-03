# Lab08
In this lab, you are expected to convert binary tree to linked list. The tree definition is different from our previous labs in that now only integers are stored in each node, instead of key-value pairs:

```
struct tree_node {
	int data;
	struct tree_node *left;
	struct tree_node *right;
};

```
After flattening a tree, all nodes' left children become `null`, so it is equivalent to a linked list, although the normal `next` node in a list is now referred as `right`.

For example, Given the following tree:
```
    5
   / \
  4   8    
 /   /     
1   6 
 \
  3
```
After being flattened, it becomes:
```
5
 \
  4
   \
    1
     \
      3
       \
        8
         \
          6
```

You can still re-use a lot codes from previous labs, such as the `tree_print` implementation from Lab06, for `list_print`, you need to change the `next` to `right` in the `list_print` function you implemented in Lab04. Also you need make some easy modifications to accommondate the changes from key-value pair to plain integers stored in the nodes.

For the above example, you program is expected to output two lines (i.e. the values (in-order) in the input tree before flattening, and in the list after flattening:
```
1 3 4 5 6 8
5 4 1 3 8 6
```
Use the provided `rand.py` to generate random test data sets by running commands similar to the following:
```
python rand.py 10 > input_10.txt
```
make sure you test your code thoroughly using different test data sets.
