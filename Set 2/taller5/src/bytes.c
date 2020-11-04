#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bytes.h"

void printByte(unsigned char *direccion,int tamano){
  int i;
  for (i=0;i<tamano;i++){
    printf("Byte %d: %.2X\n",i,direccion[i]);
  }
}

void bytesChar(char valor){
  printf("%d char\n", valor);
  unsigned char *byteDireccion = (unsigned char *)&valor;
  int i;
  for (i=0;i<sizeof(char);i++){
    printf("Byte %d: %.2X\n",i,byteDireccion[i]);
  }
}
void bytesShort(short valor){
  printf("%d short\n", valor);
  unsigned char *byteDireccion = (unsigned char *)&valor;
  int i;
  for (i=0;i<sizeof(short);i++){
    printf("Byte %d: %.2X\n",i,byteDireccion[i]);
  }
}
void bytesInt(int valor){
  printf("%d int\n", valor);
  unsigned char *byteDireccion = (unsigned char *)&valor;
  int i;
  for (i=0;i<sizeof(int);i++){
    printf("Byte %d: %.2X\n",i,byteDireccion[i]);
  }
}
void bytesLong(long valor){
  printf("%ld long\n", valor);
  unsigned char *byteDireccion = (unsigned char *)&valor;
  int i;
  for (i=0;i<sizeof(long);i++){
    printf("Byte %d: %.2X\n",i,byteDireccion[i]);
  }
}
void bytesFloat(float valor){
  printf("%.2f float\n", valor);
  unsigned char *byteDireccion = (unsigned char *)&valor;
  int i;
  for (i=0;i<sizeof(float);i++){
    printf("Byte %d: %.2X\n",i,byteDireccion[i]);
  }
}
void bytesDouble(double valor){
  printf("%f double\n", valor);
  unsigned char *byteDireccion = (unsigned char *)&valor;
  int i;
  for (i=0;i<sizeof(double);i++){
    printf("Byte %d: %.2X\n",i,byteDireccion[i]);
  }
}

int main(int argc, char **argv){
  char buf[100] = {0};
  int opcion = 0;

  while(1){
    fgets(buf,100,stdin);
    if(strcmp(buf,"x\n")==0){break;}
    else if(strcmp(buf,"char\n")==0){opcion = 1;}
    else if(strcmp(buf,"short\n")==0){opcion = 2;}
    else if(strcmp(buf,"int\n")==0){opcion = 3;}
    else if(strcmp(buf,"long\n")==0){opcion = 4;}
    else if(strcmp(buf,"float\n")==0){opcion = 5;}
    else if(strcmp(buf,"double\n")==0){opcion = 6;}
    else{
      if(opcion==1){
        char dato = (char) atoi(buf);
        bytesChar(dato);
      }
      else if(opcion==2){
        short dato = (short) atoi(buf);
        bytesShort(dato);
      }
      else if(opcion==3){
        int dato = (int) atoi(buf);
        bytesInt(dato);
      }
      else if(opcion==4){
        long dato = atol(buf);
        bytesLong(dato);
      }
      else if(opcion==5){
        float dato = atof(buf);
        bytesFloat(dato);
      }
      else if(opcion==6){
        double dato = atof(buf);
        bytesDouble(dato);
      }
      else{printf("%s\n","No ingresó un tipo de dato");}
    }
  }
  return 0;
}
