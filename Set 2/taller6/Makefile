include config.mk
# Bandera -c genera código objeto para archivos separados
# Opción -g habilita modo depuración/debug
# Opción -Wall habilita mensajes de advertencia
# Opción -I seguido de directorio le dice dónde buscar las librerías

# Creación del ejecutable "promedio"

$(EXE_DIR)/promedio: $(OBJ_FILES)
	$(CC) $(OFLAGS)

$(OBJ_DIR)/promedio.o: $(SRC_DIR)/promedio.c
	$(CC) $(CFLAGS)


.PHONY: run
run: $(EXE_DIR)/promedio
	$(EXE_DIR)/promedio


.PHONY: run-f
run-f: $(EXE_DIR)/promedio
	$(EXE_DIR)/promedio < data.in

# Limpia todo
.PHONY: clean
clean:
	rm $(OBJ_FILES)
	rm $(EXE_FILES)
