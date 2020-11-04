typedef int (*comp)(int, int);

int comp1(int a, int b){
  if (a > b){
    return 1;
  } else if (a < b){
    return -1;
  } else return 0;
}

int comp2(int a, int b){
  if (a > b){
    return -1;
  } else if (a < b){
    return 1;
  } else return 0;
}

int comp_extrano(int a, int b){
  if (a < b){
    return -1;
  } else if (a > b){
    return 0;
  } else return 1;
}


void insertionSort(int arr[], int n, comp comp);
void imprimirArreglo(int arr[], int n);
void imprimirResultados(int arr[], comp comp_1, comp comp_2, comp comp_3);

/*comp_extrano deja el arreglo tal cual.*/
