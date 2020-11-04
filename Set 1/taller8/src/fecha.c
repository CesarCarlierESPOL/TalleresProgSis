#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fecha(char* fecha){
	char *ptr = strtok(fecha,"-");
	char splited[3][100];
	int anio, mes, dia;
	int i = 0;
	while(ptr != NULL){
		strcpy(splited[i],ptr);
		ptr = strtok(NULL,"-");
		i++;
	}
	anio = atoi(splited[0]);
	mes = atoi(splited[1]);
	dia = atoi(splited[2]);
	char mesW[20]="";
	if(mes==1) strcpy(mesW,"Enero");
	if(mes==2) strcpy(mesW,"Febrero");
	if(mes==3) strcpy(mesW,"Marzo");
	if(mes==4) strcpy(mesW,"Abril");
	if(mes==5) strcpy(mesW,"Mayo");
	if(mes==6) strcpy(mesW,"Junio");
	if(mes==7) strcpy(mesW,"Julio");
	if(mes==8) strcpy(mesW,"Agosto");
	if(mes==9) strcpy(mesW,"Septiembre");
	if(mes==10) strcpy(mesW,"Octubre");
	if(mes==11) strcpy(mesW,"Noviembre");
	if(mes==12) strcpy(mesW,"Diciembre");
	if(strcmp(mesW,"")==0){
		printf("No es una fecha valida\n");
		exit(1);
	}
	printf("%i de %s de %i\n",dia,mesW,anio);

}
