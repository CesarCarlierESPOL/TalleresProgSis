#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilfecha.h"

int main(int argc, char** argv){
	if (argc!=3) {
		printf("Numero de argumentos no valido\n");
		exit(1);
	}
	int tiempoSeg=0;
	int tiempoDias=0;
	char tiempoFecha[100]="";
	char opcion;
	while((opcion=getopt(argc,argv,"h:a:f:"))!=-1){
		switch(opcion){
			case 'h':
				tiempoSeg=atoi(optarg);
				segundos(tiempoSeg);
				break;
			case 'a':
				tiempoDias=atoi(optarg);
				dias(tiempoDias);
				break;
			case 'f':
				strcpy(tiempoFecha, optarg);
				fecha(tiempoFecha);
				break;
		}
	}
	return 0;
}
