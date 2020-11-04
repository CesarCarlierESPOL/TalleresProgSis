prog: prog2.o
	gcc -o prog prog2.o -lpthread

prog2.o: prog2.c
	gcc -c -g -Wall prog2.c

.PHONY: clean
clean:
	rm -f prog prog2.o
