#include <unistd.h>
#include <stdlib.h>
#include "objetos.h"


void crear(void *ref, size_t tamano){
    Ejemplo *buf = (Ejemplo *)ref;
    buf->a = 0;
    int i = 0;
    for(i = 0; i< 100; i++){
    	buf->b[i] = i;
    }
    buf->msg = (char *)malloc(sizeof(char)*1000);
}

void destruir(void *ref, size_t tamano){
    Ejemplo *buf = (Ejemplo *)ref;
    buf->a = -1;
    //buf->b = 0.0f;
    free(buf->msg);
}

