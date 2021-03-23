CFLAGS=-std=gnu99 -pedantic -ggdb -Wall -Werror

.PHONY: all clean
all: rotate-matrix clean
rotate-matrix: rotate.o read-matrix.o
	gcc ${CFLAGS} -o rotate-matrix rotate.o read-matrix.o
rotate.o: rotate.c
	gcc ${CFLAGS} -c rotate.c
clean:
	rm rotate.o
