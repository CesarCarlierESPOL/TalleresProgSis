bin/programa: obj/main.o obj/util.o
	gcc -Wall -I include/ obj/main.o obj/util.o -o bin/programa

obj/main.o: src/main.c
	gcc -c -Wall -I include/ src/main.c -o obj/main.o

obj/util.o: src/util.c
	gcc -c -Wall -I include/ src/util.c -o obj/util.o

.PHONY: clean, gdb

clean: 
	rm bin/programa
	rm obj/*.o

gdb: 
	gdb bin/programa
