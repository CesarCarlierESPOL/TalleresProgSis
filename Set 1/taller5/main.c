#include <stdio.h>

void verBytes(void *valor,  long tamano);

typedef struct datos{
	int a;
	short p;
	char *w;
	char *msg;
}teststruct;

int main(void){
	int a = 7899;
	printf("tipo de dato: int\n");
	verBytes(&a,sizeof(a));

	char b = 'b';
	printf("tipo de dato: char\n");
	verBytes(&b,sizeof(b));

	short c = 788;
	printf("tipo de dato: short\n");
	verBytes(&c,sizeof(c));

	long d = 8900000000;
	printf("tipo de dato: long\n");
	verBytes(&d,sizeof(d));

	float e = 4.5f;
	printf("tipo de dato: float\n");
	verBytes(&e,sizeof(e));

	double f = 17.6;
	printf("tipo de dato: double\n");
	verBytes(&f,sizeof(f));

	teststruct g;
	g.a=0xffffffff;
	g.p=0xbbae;
	g.w="z";
	g.msg="hola";
	printf("tipo de dato: struct\n");
	verBytes(&g,sizeof(g));

	return 0;
}

void verBytes(void *valor,  long tamano){
	unsigned char *p;
	p = valor;
	for (int i=0; i<tamano; i++) {
		printf("%p\t0x%.2x\n",p+i,*(p+i));
	}
	printf("\n");
}
