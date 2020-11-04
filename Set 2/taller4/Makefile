include config.mk
# Bandera -c genera código objeto para archivos separados
# Opción -g habilita modo depuración/debug
# Opción -Wall habilita mensajes de advertencia
# Opción -I seguido de directorio le dice dónde buscar las librerías

.PHONY: all
all: $(EXE_FILES)

$(EXE_DIR)/taller4_bad: $(OBJ_DIR)/taller4_bad.o
	$(CC) $(OFLAGS)

$(EXE_DIR)/taller4_good: $(OBJ_DIR)/taller4_good.o
	$(CC) $(OFLAGS)

$(OBJ_DIR)/taller4_bad.o: $(SRC_DIR)/taller4_bad.c
	$(CC) $(CFLAGS)

$(OBJ_DIR)/taller4_good.o: $(SRC_DIR)/taller4_good.c
	$(CC) $(CFLAGS)


# Limpia todo
.PHONY: clean
clean:
	rm -rf $(OBJ_FILES)
	rm -rf $(EXE_FILES)
