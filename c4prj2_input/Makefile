CFLAGS=-Wall -Werror -ggdb3 -std=gnu99 -pedantic $(OTHERFLAGS)
future.o: future.c
	gcc -c $< $(CFLAGS)

input.o: input.c
	gcc -c $< $(CFLAGS)
clean:
	rm -rf *.o poker *~
