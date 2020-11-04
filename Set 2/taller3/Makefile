include config.mk
# Bandera -c genera código objeto para archivos separados
# Opción -g habilita modo depuración/debug
# Opción -Wall habilita mensajes de advertencia
# Opción -I seguido de directorio le dice dónde buscar las librerías

.PHONY: all
all: $(OBJ_FILES)
		$(CC) -g $(OBJ_FILES) -o $(EXE_FILES)

# Creación del ejecutable "cifrado"
.PHONY: cifrado
cifrado: $(OBJ_FILES)
		$(CC) -g $(OBJ_FILES) -o $(EXE_DIR)/cifrado

# Crea/compila archivos individuales >>por separado<<
$(O_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS)

$(O_DIR)/ciclico.o: $(SRC_DIR)/ciclico.c
	$(CC) $(CFLAGS)

$(O_DIR)/morse.o: $(SRC_DIR)/morse.c
	$(CC) $(CFLAGS)

# Crea/compila todos los archivos (en caso de no tener reglas individuales)
$(O_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS)

# Ejecuta el programa con código morse para entrada de texto
.PHONY: morse
morse: $(EXE_DIR)/cifrado
	./$(EXE_DIR)/cifrado -t morse

# Ejecuta el programa con código morse redirigiendo el archivo data.in a la entrada
.PHONY: morse-f
morse-f: $(EXE_DIR)/cifrado
	./$(EXE_DIR)/cifrado -t morse < data.in

# Ejecuta el programa con código cíclico
# Clave por defecto =3; cambiar número para cambiar clave
.PHONY: ciclo
ciclo: $(EXE_DIR)/cifrado
	./$(EXE_DIR)/cifrado -t ciclico -p 3

# Ejecuta el programa con código cíclico redirigiendo el archivo data.in a la entrada
# Clave por defecto =3; cambiar número para cambiar clave
.PHONY: ciclo-f
ciclo-f: $(EXE_DIR)/cifrado
	./$(EXE_DIR)/cifrado -t ciclico -p 3 < data.in


# Limpia todo
.PHONY: clean
clean:
	rm -rf $(OBJ_FILES)
	rm -rf $(EXE_FILES)
