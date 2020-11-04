#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilfecha.h"

void dias(int tiempo){
	int anios, meses, dias;
	anios = tiempo/ANIO;
	meses = (tiempo - anios*ANIO)/MES;
	dias = tiempo - (anios*ANIO + meses*MES);
	printf("Años\tMeses\tDias\n%i\t%i\t%i\n",anios,meses,dias);
}
