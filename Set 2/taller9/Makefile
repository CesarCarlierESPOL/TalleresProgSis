include config.mk
# Bandera -c genera código objeto para archivos separados
# Opción -g habilita modo depuración/debug
# Opción -Wall habilita mensajes de advertencia
# Opción -I seguido de directorio le dice dónde buscar las librerías
.PHONY: all
all:$(EXE_DIR)/pscopy

.PHONY: dir
dir:
	ls -lhR

.PHONY: dir-report
dir-report:
	ls -lhR > dir_report.txt

# Limpia todo
.PHONY: clean
clean:
	rm -f $(EXE_FILES)
	rm -f $(OBJ_FILES)

$(EXE_DIR)/pscopy: $(O_DIR)/pscopy.o
	$(CC) $(OFLAGS)

$(O_DIR)/pscopy.o: $(SRC_DIR)/pscopy.c
	$(CC) $(CFLAGS)
