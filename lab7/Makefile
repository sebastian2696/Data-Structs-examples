all: dict_list dict_tree

dict_list: dict_list.c
	$(CC) -Wall -g -o $@ $< -lm

dict_tree: dict_tree.c
	$(CC) -Wall -g -o $@ $< -lm

clean:
	$(RM) *.o dict_list dict_tree

