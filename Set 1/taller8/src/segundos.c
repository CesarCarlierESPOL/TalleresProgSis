#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilfecha.h"

void segundos(int tiempo){
	int hor, min, seg;
	hor = tiempo/HORA;
	min = (tiempo - hor*HORA)/MIN;
	seg = tiempo - (hor*HORA + min*MIN);
	printf("Horas\tMinutos\tSegundos\n%i\t%i\t%i\n",hor,min,seg);
}
