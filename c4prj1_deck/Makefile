CFLAGS =-std=gnu99 -ggdb3 -pedantic -Wall -Werror
test-c4deck: test-c4deck.o cards.o deck.o eval.o 
	gcc $(CFLAGS) -o $@ $^
test-c4deck.o: test-c4deck.c 
	gcc -c $< $(CFLAGS)
deck.o: deck.c
	gcc -c $< $(CFLAGS)
eval.o: eval.c
	gcc -c $< $(CFLAGS)
cards.o: cards.c
	gcc -c $< $(CFLAGS)
clean:
	rm -rf *.o test_c4 *~
