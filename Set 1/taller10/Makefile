matmul: matriz_hilos.c
	gcc -Wall -fsanitize=address,undefined -pthread matriz_hilos.c -o matmul

.PHONY: clean
clean:
	rm matmul
