#include <stdlib.h>
#include <unistd.h>
#include "objetos.h"

void crear_elfo(void *ref, size_t tamano){
  Elfo *elf = (Elfo *)ref;
  elf->dinero = 1000;
  elf->flechas = 70;
  elf->nombre = (char *)malloc(sizeof(char)*100);
}

void destruir_elfo(void *ref, size_t tamano){
  Elfo *elf = (Elfo *)ref;
  elf->dinero = -1;
  elf->flechas = -1;
  free(elf->nombre);  
}
