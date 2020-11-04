include config.mk
# Bandera -c genera código objeto para archivos separados
# Opción -g habilita modo depuración/debug
# Opción -Wall habilita mensajes de advertencia
# Opción -I seguido de directorio le dice dónde buscar las librerías

# Creación del ejecutable "bytes"

$(EXE_DIR)/bytes: $(OBJ_FILES)
	$(CC) $(OFLAGS)

$(OBJ_DIR)/bytes.o: $(SRC_DIR)/bytes.c
	$(CC) $(CFLAGS)


.PHONY: run
run: $(EXE_DIR)/bytes
	$(EXE_DIR)/bytes


.PHONY: run-f
run-f: $(EXE_DIR)/bytes
	$(EXE_DIR)/bytes < data.in

# Limpia todo
.PHONY: clean
clean:
	rm $(OBJ_FILES)
	rm $(EXE_FILES)
