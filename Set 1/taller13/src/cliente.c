#include <sys/types.h>          /* some systems still require this */
#include <sys/stat.h>
#include <stdio.h>              /* for convenience */
#include <stdlib.h>             /* for convenience */
#include <stddef.h>             /* for offsetof */
#include <string.h>             /* for convenience */
#include <unistd.h>             /* for convenience */
#include <signal.h>             /* for SIG_ERR */
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/resource.h>

#define BUFLEN 128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

#define QUEUESIZE 10
#define CHUNK_SIZE 128


//Main

int main( int argc, char *argv[]) {
  int sockfd;

  if(argc != 5){
    printf("Uso: ./cliente <interfaz> <número de puerto> <archivo a solicitar> <nombre a guardar>\n");
    exit(-1);
  }

  int puerto = atoi(argv[2]);
  char* ruta_archivo = argv[3];

  //Direccion del servidor
  struct sockaddr_in direccion_destino;

  memset(&direccion_destino, 0, sizeof(direccion_destino));	//ponemos en 0 la estructura direccion_servidor

  //llenamos los campos
  direccion_destino.sin_family = AF_INET;		//IPv4
  direccion_destino.sin_port = htons(puerto);		//Convertimos el numero de puerto al endianness de la red
  direccion_destino.sin_addr.s_addr = inet_addr(argv[1]) ;	//Nos vinculamos a la interface localhost o podemos usar INADDR_ANY para ligarnos A TODAS las interfaces

  if((sockfd = socket(direccion_destino.sin_family, SOCK_STREAM, 0)) < 0){
    perror("Error al crear socket\n");
    return -1;
  }

  int res = connect(sockfd, (struct sockaddr *)&direccion_destino, sizeof(direccion_destino));

  if(res < 0){
    close(sockfd);
    perror("Error al conectar\n");
    return -1;
  }

  int ruta = write(sockfd, ruta_archivo, CHUNK_SIZE);

  char solicitud[200];
  sprintf(solicitud, "GET %s", ruta_archivo);
  send(sockfd, solicitud, 200,0);

  if(ruta < 0){
    close(sockfd);
    perror("Error al conectar\n");
    return -1;
  }

  char buf[CHUNK_SIZE], tam[50];
  ssize_t escrito = 0;
  int fd2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
  if( fd2 < 0){
    perror("No se pudo abrir o crear el archivo\n");
  }

  recv(sockfd, tam, 50, 0);
  printf("Tamaño del archivo a recibir: %s bytes\n", tam);


  while( (recv(sockfd, buf, CHUNK_SIZE, 0) != 0)){
    escrito += write(fd2, buf, CHUNK_SIZE);
  }

  if(escrito < 0){
    perror("No se pudo escribir el archivo destino.\n");
  }
  printf("Archivo recibido\n");
  close(sockfd);
  close(fd2);
  return(0);
}
