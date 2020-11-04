#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define CAPACIDAD 200
#define ARGUMENTOS 10

int main(){
	char *ruta;
	char ruta_tmp[CAPACIDAD];
	char **argumentos=(char**)malloc(ARGUMENTOS*sizeof(char*));
	char *ptr;
	for(int i=0; i<ARGUMENTOS;i++){
		*(argumentos+i)=(char*)malloc(CAPACIDAD*sizeof(char));
	}

	while(1){
		printf("$ ");
		fgets(ruta_tmp,CAPACIDAD,stdin);
		ruta = strtok(ruta_tmp,"\n");
		ptr = strtok(ruta_tmp," ");
		if(strcmp(ruta_tmp,"exit")==0){
			break;
		}
		int i=0;
		while(ptr!=NULL){
			strcpy(argumentos[i],ptr);
			ptr=strtok(NULL," ");
			i++;
		}

		pid_t child = fork();
		if (child==0){
			printf("Ejecutando programa en ruta: %s\n",argumentos[0]);
			if (argumentos[1]==NULL) execl(ruta,ruta,NULL);
			else execv(argumentos[0],argumentos);
			printf("No se encontro ningun programa con dicha ruta, intente de nuevo\n");
			for(int i=0;i<ARGUMENTOS;i++){
				free(*(argumentos+i));
			}free(argumentos);
			return 1;
		}
		else {
			int status;
			wait(&status);
		}
	}
	for(int i=0;i<ARGUMENTOS;i++){
		free(*(argumentos+i));
	}free(argumentos);
	return 0;
}
