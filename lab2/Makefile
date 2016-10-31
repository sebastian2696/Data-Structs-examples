CC=gcc
CFLAGS+=-Wall -g -O0
all: mean_median array_gen

mean_median: mean_median.c main.c
array_gen: array_gen.o

# Extra libs for link stage, also see $(LOADLIBES), $(LDLIBS)
LDFLAGS+=
LDLIBS+=-lm

clean:
	$(RM) *.o mean_median array_gen
