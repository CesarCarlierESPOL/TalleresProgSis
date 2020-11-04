include config.mk
# Bandera -c genera código objeto para archivos separados
# Opción -g habilita modo depuración/debug
# Opción -Wall habilita mensajes de advertencia
# Opción -I seguido de directorio le dice dónde buscar las librerías
.PHONY: all
all:$(EXE_DIR)/cliente $(EXE_DIR)/servidor

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

$(EXE_DIR)/cliente: $(O_DIR)/cliente.o
	$(CC) $(OFLAGS)

$(O_DIR)/cliente.o: $(SRC_DIR)/cliente.c
	$(CC) $(CFLAGS)

$(EXE_DIR)/servidor: $(O_DIR)/servidor.o
	$(CC) $(OFLAGS)

$(O_DIR)/servidor.o: $(SRC_DIR)/servidor.c
	$(CC) $(CFLAGS)

.PHONY: run-s
run-s:
	$(EXE_DIR)/servidor 127.0.0.1 8001

.PHONY: run-c
run-c:
	$(EXE_DIR)/cliente 127.0.0.1 8001 ./resources/fuente1 ./resources/destino
