#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void traducirMorse(char* entrada, char*salida);

void cifrarMorse(char* entrada, char* salida){

  while(1){
    fgets(entrada, 2000, stdin);
    traducirMorse(entrada, salida);
    break;
  }
}

void traducirMorse(char* entrada, char* salida){
  int j=0;
  for(int i=0;i<=strlen(entrada);i++)
  {
    /*Evalúa cada letra del arreglo entrada y añade su traducción en morse
    al arreglo salida */
    switch(toupper(entrada[i]))
    {
      case 'A':
      salida[j++]='.';
      salida[j]='-';
      break;

      case 'B':
      salida[j++]='-';
      salida[j++]='.';
      salida[j++]='.';
      salida[j]='.';
      break;

      case 'C':
      salida[j++]='-';
      salida[j++]='.';
      salida[j++]='-';
      salida[j]='.';
      break;

      case 'D':
      salida[j++]='-';
      salida[j++]='.';
      salida[j]='.';
      break;

      case 'E':
      salida[j]='.';
      break;

      case 'F':
      salida[j++]='.';
      salida[j++]='.';
      salida[j++]='-';
      salida[j]='.';
      break;

      case 'G':
      salida[j++]='-';
      salida[j++]='-';
      salida[j]='.';
      break;

      case 'H':
      salida[j++]='.';
      salida[j++]='.';
      salida[j++]='.';
      salida[j]='.';
      break;

      case 'I':
      salida[j++]='.';
      salida[j]='.';
      break;

      case 'J':
      salida[j++]='.';
      salida[j++]='-';
      salida[j++]='-';
      salida[j]='-';
      break;

      case 'K':
      salida[j++]='-';
      salida[j++]='.';
      salida[j]='-';
      break;

      case 'L':
      salida[j++]='.';
      salida[j++]='-';
      salida[j++]='.';
      salida[j]='.';
      break;

      case 'M':
      salida[j++]='-';
      salida[j]='-';
      break;

      case 'N':
      salida[j++]='-';
      salida[j]='.';
      break;

      case 'O':
      salida[j++]='-';
      salida[j++]='-';
      salida[j]='-';
      break;

      case 'P':
      salida[j++]='.';
      salida[j++]='-';
      salida[j++]='-';
      salida[j]='.';
      break;

      case 'Q':
      salida[j++]='-';
      salida[j++]='-';
      salida[j++]='.';
      salida[j]='-';
      break;

      case 'R':
      salida[j++]='.';
      salida[j++]='-';
      salida[j]='.';
      break;

      case 'S':
      salida[j++]='.';
      salida[j++]='.';
      salida[j]='.';
      break;

      case 'T':
      salida[j]='-';
      break;

      case 'U':
      salida[j++]='.';
      salida[j++]='.';
      salida[j]='-';
      break;

      case 'V':
      salida[j++]='.';
      salida[j++]='.';
      salida[j++]='.';
      salida[j]='-';
      break;

      case 'W':
      salida[j++]='.';
      salida[j++]='-';
      salida[j]='-';
      break;

      case 'X':
      salida[j++]='-';
      salida[j++]='.';
      salida[j++]='.';
      salida[j]='-';
      break;

      case 'Y':
      salida[j++]='-';
      salida[j++]='.';
      salida[j++]='-';
      salida[j]='-';
      break;

      case 'Z':
      salida[j++]='-';
      salida[j++]='-';
      salida[j++]='.';
      salida[j]='.';
      break;

      case '0':
      salida[j++]='-';
      salida[j++]='-';
      salida[j++]='-';
      salida[j++]='-';
      salida[j]='-';
      break;

      case '1':
      salida[j++]='.';
      salida[j++]='-';
      salida[j++]='-';
      salida[j++]='-';
      salida[j]='-';
      break;

      case '2':
      salida[j++]='.';
      salida[j++]='.';
      salida[j++]='-';
      salida[j++]='-';
      salida[j]='-';
      break;

      case '3':
      salida[j++]='.';
      salida[j++]='.';
      salida[j++]='.';
      salida[j++]='-';
      salida[j]='-';
      break;

      case '4':
      salida[j++]='.';
      salida[j++]='.';
      salida[j++]='.';
      salida[j++]='.';
      salida[j]='-';
      break;

      case '5':
      salida[j++]='.';
      salida[j++]='.';
      salida[j++]='.';
      salida[j++]='.';
      salida[j]='.';
      break;

      case '6':
      salida[j++]='-';
      salida[j++]='.';
      salida[j++]='.';
      salida[j++]='.';
      salida[j]='.';
      break;

      case '7':
      salida[j++]='-';
      salida[j++]='-';
      salida[j++]='.';
      salida[j++]='.';
      salida[j]='.';
      break;

      case '8':
      salida[j++]='-';
      salida[j++]='-';
      salida[j++]='-';
      salida[j++]='.';
      salida[j]='.';
      break;

      case '9':
      salida[j++]='-';
      salida[j++]='-';
      salida[j++]='-';
      salida[j++]='-';
      salida[j]='.';
      break;

      case ' ':
      salida[j]=' ';
      break;
    }
    j++;
  }

  salida[j-1]='\0';

  /*printf("Usted escribió: %s\n", entrada);*/
  printf("%s\n", salida);
}
