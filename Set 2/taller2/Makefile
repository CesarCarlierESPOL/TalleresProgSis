CC=gcc -o
CFLAGS= -std=c99 -Wall -I.
EXE_FILES= promedio

.PHONY: all
all: $(EXE_FILES)

.PHONY: exe
exe: $(EXE_FILES)

promedio: promedio.c
	$(CC) $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f .o
	rm -f $(EXE_FILES)
