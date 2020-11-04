include config.mk
# Bandera -c genera código objeto para archivos separados
# Opción -g habilita modo depuración/debug
# Opción -Wall habilita mensajes de advertencia
# Opción -I seguido de directorio le dice dónde buscar las librerías

# Creación del ejecutable "taller7"

$(EXE_DIR)/taller7: $(OBJ_FILES)
	$(CC) $(OFLAGS)

$(OBJ_DIR)/taller7.o: $(SRC_DIR)/taller7.c
	$(CC) $(CFLAGS)


.PHONY: run
run: $(EXE_DIR)/taller7
	$(EXE_DIR)/taller7

# Limpia todo
.PHONY: clean
clean:
	rm $(OBJ_FILES)
	rm $(EXE_FILES)
