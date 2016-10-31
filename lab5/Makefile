CC=gcc
CFLAGS+=-Wall -g -O0
all: check_palindrome array_gen

check_palindrome: check_palindrome.c
array_gen: array_gen.o

# Extra libs for link stage, also see $(LOADLIBES), $(LDLIBS)
LDFLAGS+=
LDLIBS+=-lm

clean:
	$(RM) *.o check_palindrome array_gen
