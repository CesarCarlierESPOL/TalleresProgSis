#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buf[100] = {0};
double promedio, suma = 0, conversion, max=0, min=0;
int contador = 0;

void minMax(double num);

int main(int argc, char** argv){
  char buf[100] = {0};
  double promedio, suma = 0, conversion;
  int contador = 0;
  int numeroBandera;

  if (argc>1 && strcmp(argv[1],"-n")==0){
    numeroBandera=atoi(argv[2]);
  }

  while(1){
    fgets(buf, 100, stdin);
    if(strcmp(buf, "x\n")==0){
      break;
    }
    conversion = atof(buf);
    suma += conversion;
    contador++;
    minMax(conversion);
    memset(buf, 0, 100);
    if(argc>1 && contador==numeroBandera){
      break;
    }
  }

  promedio = suma/contador;
  printf("%.2f\t", promedio);
  printf("%.2f\t", min);
  printf("%.2f\t\n", max);
  return 0;

}

void minMax(double num){
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
