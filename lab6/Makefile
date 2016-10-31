all: dict

dict_full: dict_full.c
	$(CC) -Wall -g -o $@ $< -lm

dict: dict.c
	$(CC) -Wall -g -o $@ $< -lm

clean:
	$(RM) dict

