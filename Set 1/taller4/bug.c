#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void intercambiar(int *arr){
	
	int tam = sizeof(arr)/sizeof(int);

	for(int i = 0; i < tam/2 ; i++){
		arr[i] = arr[i*2];
		arr[i*2] = arr[i];
	}

	return;
}

void inicializar_arreglo(int *arr, int tam);

void mostrar_arreglo(int *arr, int tam){
	for(int i = 0; i < tam; i++){
		printf("Item %d del arreglo es %i\n", i+1, arr[i]);
	}
}

int main(int argc, char **argv){
	char opcion;
	int tam = 0;
	while( (opcion = getopt(argc,argv,"n:")) != -1){
		switch(opcion){
			case 'n':
				tam = atoi(optarg);
				break;
			default:
				printf("opcion no reconocida\n");
				return -1;
		}
	}
	
	if(tam > 1000){
		printf("Arreglo demasiado grande\n");
		return -1;
	}
	int arreglo[tam];	//Solo para propositos del taller 
	inicializar_arreglo(arreglo, tam);	
	mostrar_arreglo(arreglo, tam);
	return 0;
}



void inicializar_arreglo(int *arr, int tam){
	for(int i = tam-1; i >= 0; i--){
		arr[i] = 2*i;
	}
	
}

					
