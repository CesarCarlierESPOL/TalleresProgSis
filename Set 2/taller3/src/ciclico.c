#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int resultado;

void traducirCiclico(char* entrada, char* salida, int clave);

void cifrarCiclico(char* entrada, char* salida, int clave){

  while(1){
    fgets(entrada, 2000, stdin);
    traducirCiclico(entrada, salida, clave);
    break;
  }
}

void traducirCiclico(char* entrada, char* salida, int clave){

  for(int i = 0; i < strlen(entrada); i++){

    /*Operación basada en código ASCII*/
    resultado = (entrada[i] + clave);

    /*Da la vuelta para letras mayúsculas*/
    if (isupper(entrada[i]) && (resultado > 'Z'))
    {
      resultado -= 26;
    }

    /*Da la vuelta para letras minúsculas*/
    if(islower(entrada[i]) && (resultado > 'z')){
      resultado -= 26;
    }

    /*Si es caracter alfabético, cifrarlo y agregarlo a la salida */
    if(isalpha(entrada[i])){
      salida[i] = resultado;

    }
    /*Si es caracter no-alfabético, dejarlo tal cual*/
    else{
      salida [i] = entrada[i];
    }

    /*printf("The ASCII value of %c is %d.\n\n", resultado, resultado);*/
  }

  /*printf("Usted escribió: %s\n", entrada);*/
  printf("%s\n", salida);
  /*printf("Usted escribió: %d\n", clave);*/

}
