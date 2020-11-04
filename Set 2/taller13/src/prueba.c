#include "slaballoc.h"
#include "objetos.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	if(argc!=5){
		printf("Uso: ./bin/prueba -n <# de hilos> -k <# de objetos>\n");
		exit(-1);
	}

	SlabAlloc *alloc_test = crear_cache("AllocTest",sizeof(objeto_ejemplo),crear_Ejemplo,destruir_Ejemplo);
	pthread_t id_hilos[atoi(argv[2])];
	opciones_hilo args[atoi(argv[2])];

	for(int i=0;i<atoi(argv[2]);i++){
		args[i].slaballoc=alloc_test;
		args[i].id_hilo=i;
		pthread_create(&id_hilos[i],NULL,rutina_hilo,&args[i]);
	}

	stats_cache(alloc_test);

	return 0;
}

void *rutina_hilo(void *args){
  opciones_hilo *argv =(opciones_hilo*)args;
  void *objetos[1000]={0};
  SlabAlloc *slaballoc=(SlabAlloc * )argv->slaballoc;

  for(int j=0;j<1000;j++){
    void *obj =obtener_cache(slaballoc,0);
    objeto_ejemplo *cast=(objeto_ejemplo*)obj;
    cast->id_hilo = argv->id_hilo;
    cast->data[0] = argv->id_hilo * 0;
    cast->data[1] = argv->id_hilo * 1;
    cast->data[2] = argv->id_hilo * 2;
    objetos[j] = obj;
  }

  for(int k=700;k<1000;k++){
    devolver_cache(slaballoc,objetos[k]);
  }

  for(int m=0;m<700;m++){
    objeto_ejemplo *cast1 = (objeto_ejemplo *)objetos[m];
    if(cast1->id_hilo!=argv->id_hilo||
      cast1->data[0] != argv->id_hilo* 0||
      cast1->data[1] != argv->id_hilo* 1||
      cast1->data[2] != argv->id_hilo* 2){
        perror("Valor esperado era:  %d");
      }

    }
    char *mensaje="Completado.";
    return (void*)mensaje;

  }
