#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include <pthread.h>

typedef struct matriz_str{
	double **m1;
	unsigned long filasM1;
	unsigned long columnasM1;
	double **m2;
	unsigned long filasM2;
	unsigned long columnasM2;
	double **res;
	unsigned long filasRes;
	unsigned long columnasRes;
	int id;
	int nHilos;
} matriz_t;

double **crear_matriz(unsigned long filas, unsigned long columnas){

	double **matriz = (double **)calloc(filas, sizeof(double *));

	if(matriz == NULL){
		return NULL;	
	}

	unsigned long i = 0;
	for(i = 0; i < filas; i++){
		matriz[i] = calloc(columnas, sizeof(double));	
	}

	return matriz;
}


void liberar_matriz(double **m, unsigned long filas){
	for(unsigned long i = 0; i < filas; i++){
		free(m[i]);	
	}
	free(m);
}


void llenar_matriz_azar(double **m, unsigned long filas, unsigned long columnas, float max){
	srand( time( NULL ) );
	for(unsigned long i = 0; i < filas; i++){
		for(unsigned long j = 0; j < columnas; j++){
			m[i][j] = ((double)rand()/(double)(RAND_MAX)) * max;
		}	
	}

}

void mostrar_matriz(double **m, unsigned long filas, unsigned long columnas){
	
	for(unsigned long i = 0; i < filas; i++){
		for(unsigned long j = 0; j < columnas; j++){
			printf("%6.2f ", m[i][j]); 
		}
		printf("\n");	
	}
	printf("\n");

}


//Calcula el producto punto de una fila de m1, con una columna de m2
double producto_punto(double **m1, unsigned long filasM1, unsigned long columnasM1, unsigned long fila,
	             double **m2, unsigned long filasM2, unsigned long columnasM2, unsigned long columna){

	double resultado = 0.0f;
	//printf("fila %ld columna %ld\n", fila, columna);
	//columnas m1
	for(unsigned long j = 0; j < columnasM1; j++){
		//filas m2
		for(unsigned long i = 0; i < filasM2; i++){
			//printf("m1[fila][j] = %f, m2[i][columna] = %f\n", m1[fila][j], m2[i][columna]);
			resultado += (m1[fila][j] * m2[i][columna]);
			j++;
		}	
	}
	//printf("%f\n", resultado);
	return resultado;
}

//funcion obsoleta
/*
void multiplicar_matrices(double **m1, unsigned long filasM1, unsigned long columnasM1,
			  double **m2, unsigned long filasM2, unsigned long columnasM2,
			  double **res, unsigned long filasRes, unsigned long columnasRes){

	//Trabajar AQUI!
	for(unsigned long filres = 0; filres < filasRes; filres++){
		for(unsigned long colres = 0; colres < columnasRes; colres++){
			res[filres][colres] = producto_punto(m1, filasM1, columnasM1, filres,
							     m2, filasM2, columnasM2, colres);
		}
	}
} */

//funcion nueva
void multiplicar_matrices(void *args){
	matriz_t *mat = (matriz_t *)args;
	//Trabajar AQUI!
	for(unsigned long filres = mat->id; filres < mat->filasRes; filres = filres + mat->nHilos){
		for(unsigned long colres = 0; colres < mat->columnasRes; colres++){
			mat->res[filres][colres] = producto_punto(mat->m1, mat->filasM1, mat->columnasM1, filres,
							     mat->m2, mat->filasM2, mat->columnasM2, colres);
		}
	}
}


double obtener_tiempo(){
	struct timespec tsp;
	
	clock_gettime(CLOCK_REALTIME, &tsp);
	double secs = (double)tsp.tv_sec;
	double nsecs = (double)tsp.tv_nsec / 1000000000.0f;

	return secs + nsecs;

}

int main(int argc, char **argv){

	/* unsigned long m1Filas = -1;
	unsigned long m1Cols = -1;

	unsigned long m2Filas = -1;
	unsigned long m2Cols = -1; */

	//creamos la estructura que pasaremos como arg inicializandola
	matriz_t matriz;
	matriz.filasM1 = -1;
	matriz.columnasM1 = -1;
	matriz.filasM2 = -1;
	matriz.columnasM2 = -1;
	matriz.nHilos = -1;

	//const int required_arguement = 1;

	//opciones
 	static struct option long_options[7] = {
		{"filas_m1",  required_argument, 0, 'a' },
		{"cols_m1",   required_argument, 0, 'b' },
		{"filas_m2",  required_argument, 0, 'c' },
		{"cols_m2",   required_argument, 0, 'd' },
		{"n_hilos",   required_argument, 0, 'e' },
		{"mostrar_matrices", no_argument  , 0, 'f' },
		{0, 0, 0, 0 }
	    };



	char opcion = 0;
	int mostra_matrices = 0;
	int long_index = 0;
	while ( (opcion = getopt_long(argc,argv,  "a:b:c:d:e:f:", long_options,  &long_index)) != -1){
		switch(opcion){
			case 'a':
				matriz.filasM1 = atol(optarg);
				break;
			case 'b':
				matriz.columnasM1 = atol(optarg);
				break;
			case 'c':
				matriz.filasM2 = atol(optarg);
				break;
			case 'd':
				matriz.columnasM2 = atol(optarg);
				break;
			case 'e':
				matriz.nHilos = atoi(optarg);
				break;
			case 'f':
				mostra_matrices = 1;
				break;
			default:
				break;
		}
	}

	if(matriz.columnasM1 != matriz.filasM2){
		printf("El numero de columnas de la matriz m1 debe ser igual al numero de filas de la matriz m2\n");
		exit(-1);	
	}

	if(matriz.nHilos == 0 || matriz.nHilos == -1){
		printf("Numero de hilos invalido\n");
		return -1;	
	}



	matriz.filasRes = matriz.filasM1;
	matriz.columnasRes = matriz.columnasM2;

	matriz.m1 = crear_matriz(matriz.filasM1, matriz.columnasM1);
	matriz.m2 = crear_matriz(matriz.filasM2, matriz.columnasM2);

	
	llenar_matriz_azar(matriz.m1, matriz.filasM1, matriz.columnasM1, 100.0f);
	sleep(2);
	llenar_matriz_azar(matriz.m2, matriz.filasM2, matriz.columnasM2, 100.0f);

	if(mostra_matrices){
		printf("Matriz m1:\n");
		mostrar_matriz(matriz.m1,matriz.filasM1, matriz.columnasM1);
	}

	if(mostra_matrices){
		printf("Matriz m2:\n");
		mostrar_matriz(matriz.m2,matriz.filasM2, matriz.columnasM2);
	}
	
	matriz.res = crear_matriz(matriz.filasRes, matriz.columnasRes);
	
	//inicializacion de hilos
	pthread_t p[matriz.nHilos];
	int h;

	//toma de tiempo
	double ini = obtener_tiempo();

	for(h=0;h<matriz.nHilos;h++){
		matriz.id=h;
	pthread_create(&p[h], NULL, (void *)multiplicar_matrices, (void *)&matriz);
	void *stat;
	pthread_join(p[h], &stat);
	}

	// multiplicar_matrices(m1, m1Filas, m1Cols, m2, m2Filas, m2Cols, resultado, resFilas, resCols);
	double fin = obtener_tiempo();
	double delta = fin - ini;

	if(mostra_matrices){
		printf("Matriz resultado:\n");
		mostrar_matriz(matriz.res, matriz.filasRes, matriz.columnasRes);
	}
	printf("\nTiempo de multiplicacion de matrices %.6f\n", delta);

	//liberar matrices para no provocar leaks
	liberar_matriz(matriz.m1,matriz.filasM1);
	liberar_matriz(matriz.m2,matriz.filasM2);
	liberar_matriz(matriz.res,matriz.filasRes);
}


