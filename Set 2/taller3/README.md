# Integrantes

* César Carlier
* Juan Diego Vallejo


## Compilación

* Compilar con *make* / *make all*
* *make clean* permite eliminar los archivos .o y el ejecutable

### Compilación de archivos .o de manera individual

Usar los comandos:

* *make obj/main.o*
* *make obj/ciclico.o*
* *make obj/morse.o*

El comando *make cifrado* compila el ejecutable (será equivalente a correr *make* o *make all*).

## Uso

Ejecutar como:
```
./bin/cifrado -t <modo> [-p] [n]
```
donde

* **-t** y **modo** son obligatorios.

* **<modo>** debe ser "morse" o "ciclico".

### Cifrado morse

Ejecutar como:
```
./bin/cifrado -t morse
```
Como alternativa,el comando *make morse* ejecuta la misma orden.

### Cifrado cíclico

Ejecutar como:
```
./bin/cifrado -t ciclico -p [n]
```
donde **[n]** corresponde a la llave numérica; sustituye cada letra de lo ingresado por una letra **n** veces delante (en el abecedario).
