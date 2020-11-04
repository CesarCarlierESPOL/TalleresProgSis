#include <stdio.h>
#include <stdlib.h>

typedef struct estTDA{
  int c;
  long *arr;
  unsigned long cant_arr;
  char *mensaje;
}est;

void mostrar_arr(long *a, unsigned long cant){
  int i = 0;
  for(i = 0; i < cant; i++){		//sizeof(a)/sizeof(long)
    printf("%ld\n", *(a+i));
  }
  printf("\n");
}

long *crear_arr(int cantidad){
  long *arr = malloc(sizeof(int)*cantidad);
  int i = 0;
  for(i = cantidad; i >= 0; i--){
    *(arr+i) = 4500000000 + 250000*i;
  }
  return arr;
}

void llenar_arr(long *arr, unsigned long cant, long mul){
  int i = 0;
  for(i = 0; i <= cant; i++){
    *(arr+i) = mul*i;		//sizeof(long)
  }
  printf("\n");
}

void mostrar_est(est * data){
  printf("\nDatos estructura:\n");
  printf("%d\n", data->c);
  mostrar_arr(data->arr, data->cant_arr);
  printf("%s\n", data->mensaje);
}


int main(int argc, char **argv){

  if(argc < 2){
    printf("Uso: ./programa <numero de elemenetos>\n");
    exit(EXIT_FAILURE);
  }

  if ((atol(*(argv+1)) == 0) || (atol(*(argv+1)) == 1)){
    printf("Argumento erróneo.\n");
    exit(EXIT_FAILURE);
  }
  long cant = atol(*(argv+1));

  long arr1[cant];
  long arr2[cant];

  llenar_arr(arr1	,cant, 70000);
  llenar_arr(arr2,cant, 20000);

  long *data = crear_arr(cant);

  mostrar_arr(arr1, cant);
  mostrar_arr(arr2, cant);
  mostrar_arr(data, cant);

  est datos;
  datos.c = 6;
  datos.arr = &arr1[2];
  datos.cant_arr = cant - 2;
  datos.mensaje = "una estructura";


  mostrar_est(&datos);

  exit(EXIT_SUCCESS);
}
