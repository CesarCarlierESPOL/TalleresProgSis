#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct
{
        int capacidad, size;
        float *items;
} arreglo;

void minMax(float num);
void calcularDE(arreglo *arreglo);
void imprimirResultados();
void arreglo_init(arreglo *arreglo);
void arreglo_agregar(arreglo *arreglo, float valor);
void arreglo_duplicar_capacidad(arreglo *arreglo);
void arreglo_free(arreglo *arreglo);
void arreglo_imprimir(arreglo *arreglo);

char buf[100] = {0};
float promedio, suma = 0, conversion, desviacion, max=0, min=0;
int contador = 0;

int main(int argc, char** argv){
  arreglo arr;
  arreglo_init(&arr);

  while(1){
    fgets(buf, 100, stdin);
    if(strcmp(buf, "x\n")==0){
      break;
    }

    conversion = atof(buf);
    suma += conversion;
    arreglo_agregar(&arr, conversion);
    contador++;
    minMax(conversion);
    memset(buf, 0, 100);
  }

  promedio = suma/contador;
  calcularDE(&arr);
  imprimirResultados();
  arreglo_free(&arr);
  return 0;
}

void minMax(float num){
  if (min == 0 || max == 0){
    max = min = num;
  }
  if (num > max){
    max = num;
  }
  if (num < min){
    min = num;
  }
}

void calcularDE(arreglo *arreglo){
  int i;
  for(i=0; i<arreglo->size; ++i){
    desviacion += pow(arreglo->items[i] - promedio, 2);
  }
  desviacion = sqrt(desviacion/i);
}

void imprimirResultados(){
  printf("%.2f\t", promedio);
  printf("%.2f\t", min);
  printf("%.2f\t", max);
  printf("%.2f\t\n", desviacion);
}


void arreglo_init (arreglo *arreglo){
  // inicializa tamaño y capacidad
  arreglo->size = 0;
  arreglo->capacidad = sizeof(float);

  //asigna memoria a arreglo->data
  arreglo->items = malloc(sizeof(float) * arreglo->capacidad);
  if(arreglo->items==NULL){ exit(1);}
}

void arreglo_agregar(arreglo *arreglo, float valor){
  // valida espacio disponible
  arreglo_duplicar_capacidad(arreglo);

  // agrega valor e incrementa variable correspondiente al tamaño del arreglo
  arreglo->items[arreglo->size++] = valor;
}

void arreglo_duplicar_capacidad(arreglo *arreglo){
  if (arreglo->size >= arreglo->capacidad){
    // duplica capacidad y hace realloc apropiado
    arreglo->capacidad *= 2;
    arreglo->items = realloc(arreglo->items, sizeof(float) * arreglo->capacidad);
  }
}

void arreglo_free(arreglo *arreglo){
  free(arreglo->items);
}

void arreglo_imprimir(arreglo *arreglo){
  printf("Los elementos del arreglo son:\n");
  for(int i=0; i<arreglo->size; ++i){
    printf("%.2f\n", arreglo->items[i]);
  }
  printf("\n");
}
