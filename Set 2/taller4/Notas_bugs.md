# Notas

* *Aparentemente* ejecuta bien con:
  * argv[1] = 0
  * argv[1] = 1
  * argv[1] = 8 y argv[1] = 9 pero bota número raro en la 3ra salida
  * Lo mismo de la línea anterior con 16 y 17 de argumento
* Se cae con:
  * 1 < argv[1] < 7
  * 9 < argv[1] > 15

## bug01

### Descripción

Falla de segmentación.
* Código 0x00005555555547fe en función mostrar_arr, src/taller/taller4_bad.c : 14
  * Refiere a línea 63, primera ejecución de mostrar_arr() dentro de main()

Con argumento 2:
* a = 0x9c40
* cant = 2

### Causa
* Lo que jode es el puntero que será evaluado en el **%ld**
  * Parece que viene de la condición i < sizeof del lazo *for*
  * También de multiplicar sizeof(long) por i en la función llenar_arr

### Solución
* Arreglos constan en capturas/bug01post.jpg
