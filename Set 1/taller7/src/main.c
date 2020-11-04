#include <stdio.h>
#include "util.h"


int main(){
	//Creamos los 3 arreglos a los que vamos aplicarles diferentes comparadores a cada uno
	int arr1[10]={9,7,3,31,1,12,5,2,29,7};
	int arr2[10]={9,7,3,31,1,12,5,2,29,7};
	int arr3[10]={9,7,3,31,1,12,5,2,29,7};
	//llamamos a la funcion insertionSort con diferentes comparadores cada vez
	insertionSort(arr1,10,comp1);
	insertionSort(arr2,10,comp2);
	insertionSort(arr3,10,comp_extrano);
	printf("Sorted by comp1: ");
	for (int i =0;i<10;i++){
		printf(" %d ",arr1[i]);
	}
	printf("\n");
	printf("Sorted by comp2: ");
	for (int i =0;i<10;i++){
		printf(" %d ",arr2[i]);
	}
	printf("\n");
	printf("Sorted by comp_extrano: ");
	for (int i =0;i<10;i++){
		printf(" %d ",arr3[i]);
	}
	printf("\n");
	return 0;
}
