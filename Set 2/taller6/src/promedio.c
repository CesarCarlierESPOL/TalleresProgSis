#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "promedio.h"

char buf[100] = {0};
float promedio, suma = 0, conversion, desviacion, max=0, min=0;
int contador = 0;

int main(int argc, char** argv){
  arrD arr;
  arrD_init(&arr);

  while(1){
    fgets(buf, 100, stdin);
    if(strcmp(buf, "x\n")==0){
      break;
    }

    conversion = atof(buf);
    suma += conversion;
    arrD_agregar(&arr, conversion);
    contador++;
    minMax(conversion);
    memset(buf, 0, 100);
  }

  promedio = suma/contador;
  calcularDE(&arr);
  imprimirResultados();
  arrD_free(&arr);
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

void calcularDE(arrD *arrD){
  for(int i=0; i<arrD->size; ++i){
    desviacion += pow(arrD->items[i] - promedio, 2);
  }
  desviacion = sqrt(desviacion/10);
}

void imprimirResultados(){
  printf("%.2f\t", promedio);
  printf("%.2f\t", min);
  printf("%.2f\t", max);
  printf("%.2f\t\n", desviacion);
}


void arrD_init (arrD *arrD){
  // inicializa tamaño y capacidad
  arrD->size = 0;
  arrD->capacidad = sizeof(float);

  //asigna memoria a arrD->data
  arrD->items = malloc(sizeof(float) * arrD->capacidad);
}

void arrD_agregar(arrD *arrD, float valor){
  // valida espacio disponible
  arrD_duplicar_capacidad(arrD);

  // agrega valor e incrementa variable correspondiente al tamaño del arreglo
  arrD->items[arrD->size++] = valor;
}

void arrD_duplicar_capacidad(arrD *arrD){
  if (arrD->size >= arrD->capacidad) {
    // duplica capacidad y hace realloc apropiado
    arrD->capacidad *= 2;
    arrD->items = realloc(arrD->items, sizeof(float) * arrD->capacidad);
  }
}

void arrD_free(arrD *arrD){
  free(arrD->items);
}

void arrD_imprimir(arrD *arrD){
  printf("Los elementos del arreglo son:\n");
  for(int i=0; i<arrD->size; ++i){
    printf("%.2f\n", arrD->items[i]);
  }
  printf("\n");
}
