include config.mk
# Bandera -c genera código objeto para archivos separados
# Opción -g habilita modo depuración/debug
# Opción -Wall habilita mensajes de advertencia
# Opción -I seguido de directorio le dice dónde buscar las librerías

$(EXE_DIR)/prueba: $(OBJ_FILES)
	$(CC) $(OFLAGS)

#agregue los archivos .o que necesite

$(O_DIR)/prueba.o: $(SRC_DIR)/prueba.c
	$(CC) $(CFLAGS)

$(O_DIR)/Ejemplo.o: $(SRC_DIR)/Ejemplo.c
	$(CC) $(CFLAGS)

$(O_DIR)/elfo.o: $(SRC_DIR)/elfo.c
	$(CC) $(CFLAGS)

$(O_DIR)/hobbit.o: $(SRC_DIR)/hobbit.c
	$(CC) $(CFLAGS)

$(O_DIR)/sauron.o: $(SRC_DIR)/sauron.c
	$(CC) $(CFLAGS)

$(O_DIR)/slaballoc.o: $(SRC_DIR)/slaballoc.c
	$(CC) $(CFLAGS)


#agregue las reglas que necesite
.PHONY: run
run: $(EXE_DIR)/prueba
	./$(EXE_DIR)/prueba


# Limpia todo
.PHONY: clean
clean:
	rm -rf $(EXE_FILES)
	rm -rf $(OBJ_FILES)
