#include "../include/cifrado.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char entrada[2000], salida[2000];

int main(int argc, char** argv){
  /* Validación número de argumentos */
  if (argc < 3 || strcmp(argv[1], "-t")!=0) {
    fprintf(stderr, "Uso: %s -t <modo> [-p] [numero]\n", argv[0]);
    exit(0);
  }

  /* Variable que guarda si se escogió Morse o cíclico*/
  char* modo = argv[2];

  /* Validación para ejecución cifrado con código Morse */
  if(strcmp(modo, "morse")==0){
    /*printf("%s", "Ejecutando convertidor a código Morse.\n");*/
    cifrarMorse(entrada, salida);
  }

  /* Validación para ejecución cifrado con código cíclico */
  else if ((strcmp(modo, "ciclico")==0)&& argc == 5 && strcmp(argv[3], "-p")==0){
    int clave = atoi(argv[4]);
    /* Uso de operador módulo para dar la vuelta luego del 26*/
    if(clave >= 26){
      clave = (clave % 26);
    }
    /*printf("%s", "Ejecutando convertidor a código cíclico.\n");*/
    cifrarCiclico(entrada, salida, clave);
  }

  /* Validación adicional número de argumentos*/
  else if ((argc == 4) || (((strcmp(modo, "ciclico")==0)) && argc == 3)){
    fprintf(stderr, "Número incorrecto de argumentos.\n");
    exit(0);
  }

  return 0;


}
