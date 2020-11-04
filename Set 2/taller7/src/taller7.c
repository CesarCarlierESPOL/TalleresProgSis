#include <stdio.h>
#include "taller7.h"

int main(int argc, char** argv){
  int arr1[10] = {69,45,85,32,6,92,57,8,619,1};
  int arr2[10] = {56,21,34,55,35,48,9,33,420,54};
  int arr3[10] = {57,10,82,65,53,90,95,80,2,115};
	

  comp co1 = comp1;
  comp co2 = comp2;
  comp co_ex = comp_extrano;


  printf("\n\n*****ARREGLO 1*****\n");
  imprimirResultados(arr1, co1, co2, co_ex);
  printf("\n\n\n*****ARREGLO 2*****\n");
  imprimirResultados(arr2, co1, co2, co_ex);
  printf("\n\n\n*****ARREGLO 3*****\n");
  imprimirResultados(arr3, co1, co2, co_ex);

  return 0;
}

void insertionSort(int arr[], int n, comp comp){
  int i, key, j;
  for (i = 1; i < n; i++){
    key = arr[i]; //Selecciona primer elemento sin ordenar
    j = i-1;

		/*Este loop mueve los elementos para crear las posiciones*/
    while (j >= 0 && comp(arr[j],key)>0){ 
      arr[j+1] = arr[j];
      j = j-1;
    }
    arr[j+1] = key; //Esto inserta el elemento en su posición apropiada
  }
}

void imprimirArreglo(int arr[], int n){
  int i; 
    for (i = 0; i < n; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
}

void imprimirResultados(int arr[], comp comp_1, comp comp_2, comp comp_3){
  int size = 10;
	imprimirArreglo(arr, size);
  printf("*****comp1*****\n");
  insertionSort(arr,size,comp_1);
  imprimirArreglo(arr, size);
  printf("*****comp2*****\n");
  insertionSort(arr,size,comp_2);
  imprimirArreglo(arr, size);
  printf("*****comp_extrano*****\n");
  insertionSort(arr,size,comp_3);
  imprimirArreglo(arr, size);
}
