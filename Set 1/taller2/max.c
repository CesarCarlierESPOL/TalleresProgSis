#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
  char buf[100] = {0};
  //int elements[100];
  int maximo = 0, posicion = 0;
  int contador = 1;
  int suma = 0;
  int numeroBandera = 0;

  char opcion;
  while((opcion=getopt(argc,argv,"n:"))!= -1){
    switch(opcion){
      case 'n':
                numeroBandera=atoi(optarg);
                break;
    }
  }

  //if (argc>1 && strcmp(argv[1],"-n")==0){
    //numeroBandera=atoi(argv[2]);
  //}

  while(1){
    fgets(buf, 100, stdin);
    if(strcmp(buf, "x\n")==0){
      break;
    }
    if((atof(buf)>maximo) && ((contador<=numeroBandera)||(numeroBandera==0))){
      maximo = atof(buf);
      posicion = contador;
    }
    //elements[contador] = atof(buf);
    suma += atof(buf);
    contador++;
    memset(buf, 0, 100);
  }

  //for (int i = posicion; i<contador; i++) {
  //  suma += elements[i];
  //}

  printf("%s\n","max \t pos \t suma" );
  printf("%i \t %i \t %i \n", maximo,posicion,suma);
  return 0;
}
