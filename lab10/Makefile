all: GraphBFS GraphBFS_full

GraphBFS_full: GraphBFS_full.c
	$(CC) -Wall -g -o $@ $< -lm

GraphBFS: GraphBFS.c
	$(CC) -Wall -g -o $@ $< -lm

clean:
	$(RM) GraphBFS GraphBFS_full
