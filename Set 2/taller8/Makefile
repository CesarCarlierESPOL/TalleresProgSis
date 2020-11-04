include config.mk
# Bandera -c genera código objeto para archivos separados
# Opción -g habilita modo depuración/debug
# Opción -Wall habilita mensajes de advertencia
# Opción -I seguido de directorio le dice dónde buscar las librerías
.PHONY: all
all:$(EXE_DIR)/estatico $(EXE_DIR)/dinamico

.PHONY: dir
dir:
	ls -lh ./*

.PHONY: run-s
run-s: $(EXE_DIR)/estatico
	./$(EXE_DIR)/estatico

.PHONY: run-d
run-d: $(EXE_DIR)/dinamico
	./$(EXE_DIR)/dinamico

$(LIB_DIR)/libslaballoc.a: $(O_DIR)/slaballoc.o $(O_DIR)/elfo.o $(O_DIR)/hobbit.o $(O_DIR)/sauron.o
	$(STATIC_LIBRARY)

$(EXE_DIR)/estatico: $(LIB_DIR)/libslaballoc.a $(O_DIR)/prueba.o
	$(CC) -static $(OFLAGS) $< -L$(LIB_DIR) -lslaballoc

$(LIB_DIR)/libslaballoc.so: $(O_DIR)/slaballoc.o $(O_DIR)/elfo.o $(O_DIR)/hobbit.o $(O_DIR)/sauron.o
	$(CC) $(DYNAMIC_LIBRARY)

$(EXE_DIR)/dinamico: $(LIB_DIR)/libslaballoc.so $(O_DIR)/prueba.o
	$(CC) $(OFLAGS) $< -L$(LIB_DIR) -lslaballoc

$(O_DIR)/prueba.o: $(SRC_DIR)/prueba.c
	$(CC) $(CFLAGS)

$(O_DIR)/elfo.o: $(SRC_DIR)/elfo.c
	$(CC) $(CFLAGS)

$(O_DIR)/hobbit.o: $(SRC_DIR)/hobbit.c
	$(CC) $(CFLAGS)

$(O_DIR)/sauron.o: $(SRC_DIR)/sauron.c
	$(CC) $(CFLAGS)

$(O_DIR)/slaballoc.o: $(SRC_DIR)/slaballoc.c
	$(CC) $(CFLAGS)

# Limpia todo
.PHONY: clean
clean:
	rm -f $(EXE_FILES)
	rm -f $(OBJ_FILES)
	rm -f $(S_LIB_FILES)
	rm -f $(D_LIB_FILES)
