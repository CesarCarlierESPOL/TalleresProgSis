include config.mk
# Bandera -c genera código objeto para archivos separados
# Opción -g habilita modo depuración/debug
# Opción -Wall habilita mensajes de advertencia
# Opción -I seguido de directorio le dice dónde buscar las librerías
.PHONY: all
all:$(EXE_DIR)/terminal

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

$(EXE_DIR)/terminal: $(O_DIR)/terminal.o
	$(CC) $(OFLAGS)

$(O_DIR)/terminal.o: $(SRC_DIR)/terminal.c
	$(CC) $(CFLAGS)

.PHONY: run
run:
	$(EXE_DIR)/terminal
