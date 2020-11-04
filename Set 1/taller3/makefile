bin/ultifecha: obj/main.o obj/dias.o obj/fecha.o obj/segundos.o
	gcc -Wall obj/main.o obj/dias.o obj/fecha.o obj/segundos.o -o bin/utilfecha

obj/main.o: src/main.c
	gcc -Wall -c -I include/ src/main.c -o obj/main.o

obj/dias.o: src/dias.c
	gcc -Wall -c -I include/ src/dias.c -o obj/dias.o

obj/fecha.o: src/fecha.c
	gcc -Wall -c -I include/ src/fecha.c -o obj/fecha.o

obj/segundos.o: src/segundos.c
	gcc -Wall -c -I include/ src/segundos.c -o obj/segundos.o

clean:
	rm obj/*.o
	rm bin/utilfecha
