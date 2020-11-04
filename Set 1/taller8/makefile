ejecutables: bin/estatico bin/dinamico

bin/estatico: obj/main.o lib/libdateutils.a
	gcc -static -Llib $< -ldateutils -o $@

obj/main.o: src/main.c
	gcc -Wall -I include/ -c -fPIC $< -o $@

lib/libdateutils.a: obj/dias.o obj/fecha.o obj/segundos.o
	ar rcs $@ $^

obj/dias.o: src/dias.c
	gcc -Wall -I include/ -c -fPIC $< -o $@

obj/fecha.o: src/fecha.c
	gcc -Wall -I include/ -c -fPIC $< -o $@
	
obj/segundos.o: src/segundos.c
	gcc -Wall -I include/ -c -fPIC $< -o $@

bin/dinamico: obj/main.o lib/libdateutils.so
	gcc -Llib $^ -ldateutils -o $@

lib/libdateutils.so: obj/dias.o obj/fecha.o obj/segundos.o
	gcc -shared $^ -o $@
	

.PHONY: clean

clean:
	rm obj/*.o
	rm bin/*o
	rm lib/*.*
