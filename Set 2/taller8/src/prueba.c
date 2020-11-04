#include "slaballoc.h"
#include "objetos.h"


int main(){
	SlabAlloc *slabAlloc1;
	constructor_fn constructor1 = crear_elfo;
	destructor_fn destructor1 = destruir_elfo;
	printf("\n\nCREACIÓN Y OBTENCIÓN CACHE\n\n");
	slabAlloc1 = crear_cache("Legolas", sizeof(Elfo), constructor1, destructor1);

	for (int i = 0; i<250; i++){
		obtener_cache(slabAlloc1, 0);
	}

	printf("\n\nSTATS POST OBTENCIÓN\n\n");
	stats_cache(slabAlloc1);
	/*obtener_cache(slabAlloc1, 1);
	printf("\n\nSTATS POST CRECIMIENTO\n\n");
	stats_cache(slabAlloc1);*/
	destruir_cache(slabAlloc1);
	printf("\n\nSTATS POST DESTRUCCIÓN\n\n");
	stats_cache(slabAlloc1);
	return 0;
}
