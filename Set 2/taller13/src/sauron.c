#include <stdlib.h>
#include <unistd.h>
#include "objetos.h"

void crear_sauron(void *ref, size_t tamano){
  Sauron*sauron = (Sauron *)ref;
  sauron->anillos = 7;
  sauron->plan = (char *)malloc(sizeof(char)*100);
}

void destruir_sauron(void *ref, size_t tamano){
  Sauron*sauron = (Sauron *)ref;
  sauron->anillos = -1;
  free(sauron->plan);
}
