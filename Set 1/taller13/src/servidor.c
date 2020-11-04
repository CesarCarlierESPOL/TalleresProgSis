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

#define QUEUESIZE 1
#define CHUNK_SIZE 128


//Main

int main( int argc, char *argv[]) {

  if(argc == 1){
    printf("Uso: ./servidor <interfaz> <número de puerto>\n");
    exit(-1);
  }

  if(argc != 3){
    printf( "Por favor especificar una interfaz y número de puerto\n");
  }

  int puerto = atoi(argv[2]);


  //Direccion del servidor
  struct sockaddr_in direccion_servidor;

  memset(&direccion_servidor, 0, sizeof(direccion_servidor));	//ponemos en 0 la estructura direccion_servidor

  //llenamos los campos
  direccion_servidor.sin_family = AF_INET;		//IPv4
  direccion_servidor.sin_port = htons(puerto);		//Convertimos el numero de puerto al endianness de la red
  direccion_servidor.sin_addr.s_addr = inet_addr(argv[1]) ;	//Nos vinculamos a la interface localhost o podemos usar INADDR_ANY para ligarnos A TODAS las interfaces

  int sockfd;

  if((sockfd = socket(direccion_servidor.sin_family, SOCK_STREAM, 0)) < 0){
    perror("Error al crear socket\n");
    return -1;
  }

  if(bind(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) < 0){
    perror("Error en bind\n");
    return -1;
  }

  if(listen(sockfd, QUEUESIZE) < 0){
    perror("Error en listen\n");
    return -1;
  }

  while(1){
    int sockfd_conectado = accept(sockfd, NULL, 0);
    printf("Se conectó alguien.\n");

    char ruta[CHUNK_SIZE], archivo[CHUNK_SIZE], tam[50], solicitud[200] = {0};

    //Server espera datos del cliente
    int leidos = read(sockfd_conectado, ruta, CHUNK_SIZE);
    if(leidos < 0){
      perror("Error al leer\n");
    }

    recv(sockfd_conectado, solicitud, 200,0);
    printf("%s\n", solicitud);
    //Para tamaño archivo
    struct stat datos_archivo;
    int res = stat(ruta, &datos_archivo);
    if(res < 0){
      perror("Error de stat\n");
    }
    unsigned long tamano_archivo = datos_archivo.st_size;
    sprintf(tam, "%lu", tamano_archivo);

    send(sockfd_conectado, tam, 50, 0);

    //Empieza el codigo para envio de archivo
    int fd1 = open(ruta, O_RDONLY, 0);
    ssize_t escrito = 0;
    if( fd1 < 0){
      perror("No se pudo abrir el archivo\n");
    }

    while (((read(fd1, archivo, CHUNK_SIZE)) != 0)) {
      escrito += send(sockfd_conectado, archivo, CHUNK_SIZE, 0);
    }
    //int env = write(sockfd_conectado, mens_conf, strlen(mens_conf)-1);
    close(sockfd_conectado);
    return(0);

  }

}
