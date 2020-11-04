#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char** argv){
	umask(0);
	char* rfuente=argv[1];
	char* rdestino=argv[2];
	int fn=open(rfuente,O_RDONLY,0444);
	if (fn<0) {
		perror("No se pudo encontrar el archivo:\n");
		exit(1);
	}
	int ds=open(rdestino,O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fn<0) {
		perror("No se pudo copiar el archivo:\n");
		exit(1);
	}
	int contbytes=0;
	int iterabytes=1000;
	unsigned char buff[iterabytes];
	int res =0;
	lseek(fn,0,SEEK_SET);
	while((res = read(fn,buff,iterabytes))>0){
		contbytes+=res;
	}
	lseek(fn,0,SEEK_SET);
	unsigned char* bf = (unsigned char*) malloc(sizeof(unsigned char)*contbytes);
	res = read(fn,bf,contbytes);
	if (res==-1) perror("No existe el directorio al que se quiere copiar.");
	int copybytes = write(ds,bf,contbytes);
	printf("%d bytes copiados\n",copybytes);
	close(fn);
	close(ds);

	return 0;
}

