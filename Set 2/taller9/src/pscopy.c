#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define FRAG 100

int main(int argc, char** argv){
  umask(0);
  if (argc < 3 || argc > 3){
    perror("Número incorrecto de argumentos.\n");
    return -1;
  }

  int fd1 = open(argv[1], O_RDONLY, 0);
  if( fd1 < 0){
    perror("No se pudo abrir el archivo\n");
  }

  int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
  if( fd2 < 0){
    perror("No se pudo abrir o crear el archivo\n");
  }

  char buf[FRAG] = {0};
  ssize_t escrito = 0;

  while((read(fd1, buf, FRAG)) != 0){
    escrito += write(fd2, buf, (FRAG));
  }
  printf("Bytes escritos: %ld\n", escrito);

  if(escrito < 0){
    perror("No se pudo escribir el archivo destino.\n");
  }

  close(fd1);
  close(fd2);
  return(0);
}
