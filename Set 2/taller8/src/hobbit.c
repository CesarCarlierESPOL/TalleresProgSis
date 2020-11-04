#include <stdlib.h>
#include <unistd.h>
#include "objetos.h"

void crear_hobbit(void *ref, size_t tamano){
  Hobbit*hobbit = (Hobbit *)ref;
  hobbit->edad = 39;
  hobbit->estado = 1;
  hobbit->nombre = (char *)malloc(sizeof(char)*100);
}

void destruir_hobbit(void *ref, size_t tamano){
  Hobbit*hobbit = (Hobbit *)ref;
  hobbit->edad = -1;
  hobbit->estado = -1;
  free(hobbit->nombre);
}
