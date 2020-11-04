#include <unistd.h>
#include <stdlib.h>
#include "objetos.h"


void crear_Ejemplo(void *ref, size_t tamano){
  objeto_ejemplo *buf=(objeto_ejemplo *)ref;
	buf->data= (int*)calloc(3,sizeof(int));
}

void destruir_Ejemplo(void *ref, size_t tamano){
  objeto_ejemplo *buf=(objeto_ejemplo *)ref;
  buf->id_hilo=-1;
  free(buf->data);
}
