all: flatten_tree flatten_tree_full

flatten_tree_full: flatten_tree_full.c
	$(CC) -Wall -g -o $@ $< -lm

flatten_tree: flatten_tree.c
	$(CC) -Wall -g -o $@ $< -lm

clean:
	$(RM) flatten_tree flatten_tree_full
