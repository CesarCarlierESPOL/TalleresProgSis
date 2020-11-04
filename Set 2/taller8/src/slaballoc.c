#include "slaballoc.h"
#include "objetos.h"


SlabAlloc *crear_cache(char *nombre, size_t tamano_objeto, constructor_fn constructor, destructor_fn destructor){
  //Inicialización, asignación
  SlabAlloc *slab=(SlabAlloc *)malloc(sizeof(SlabAlloc));
  slab->nombre=nombre;
  slab->mem_ptr=(void *)malloc(tamano_objeto*TAMANO_CACHE);
  slab->tamano_cache=TAMANO_CACHE;
  slab->cantidad_en_uso=0;
  slab->tamano_objeto=tamano_objeto;
  slab->constructor=constructor;
  slab->destructor=destructor;
  Slab* punteroSlab=(Slab *)malloc(sizeof(Slab)*TAMANO_CACHE);
  slab->slab_ptr=punteroSlab;

  for(int j=0;j<TAMANO_CACHE;j++){
    punteroSlab[j].ptr_data=NULL;
    punteroSlab[j].ptr_data_old=NULL;
    punteroSlab[j].status=DISPONIBLE;
  }

  return slab;
}


void *obtener_cache(SlabAlloc *alloc, int crecer){
  SlabAlloc cache_a_obtener= *alloc;
  Slab *casillero= cache_a_obtener.slab_ptr;
  void *punteroAObjeto = NULL;

  // Marca casilleros como en uso si están disponibles
  for(int i =0; i<cache_a_obtener.tamano_cache; i++){
    if (casillero[i].status == DISPONIBLE){
      void *direccion_memoria= cache_a_obtener.mem_ptr + (cache_a_obtener.tamano_objeto * i);
      cache_a_obtener.constructor(direccion_memoria,cache_a_obtener.tamano_objeto);
      casillero[i].status= EN_USO;
      punteroAObjeto= cache_a_obtener.mem_ptr+(cache_a_obtener.tamano_objeto)*i;
      casillero[i].ptr_data=punteroAObjeto;
      cache_a_obtener.cantidad_en_uso+=1;
      break;
    }
  }

  //Para duplicar caché si crecer == 1
  if (cache_a_obtener.tamano_cache== cache_a_obtener.cantidad_en_uso && crecer==1){
    cache_a_obtener.tamano_cache=cache_a_obtener.tamano_cache*2;
    cache_a_obtener.mem_ptr= realloc(cache_a_obtener.mem_ptr,cache_a_obtener.tamano_objeto*cache_a_obtener.tamano_cache);
    for(int i=0;i<cache_a_obtener.tamano_cache/2;i++){
      casillero[i].ptr_data_old= casillero[i].ptr_data;
      casillero[i].ptr_data=cache_a_obtener.mem_ptr+i*cache_a_obtener.tamano_objeto;
    }
    casillero=(Slab *)realloc(cache_a_obtener.slab_ptr,cache_a_obtener.tamano_cache*sizeof(Slab));
    for(int i=cache_a_obtener.tamano_cache/2;i<cache_a_obtener.tamano_cache;i++){
      casillero[i].ptr_data=NULL;
      casillero[i].ptr_data_old=NULL;
      casillero[i].status= DISPONIBLE;
    }
    cache_a_obtener.slab_ptr= casillero;
  }

  return punteroAObjeto;
}

void devolver_cache(SlabAlloc *alloc, void *obj){
  SlabAlloc cache_a_devolver= *alloc;
  Slab *casillero= cache_a_devolver.slab_ptr;
  for(int i =0;i<cache_a_devolver.tamano_cache;i++){
    if (casillero[i].ptr_data== obj){
      casillero[i].status= DISPONIBLE;
      casillero[i].ptr_data=NULL;
      cache_a_devolver.cantidad_en_uso-=1;
      break;
    }
  }
}


void destruir_cache(SlabAlloc *alloc){
  SlabAlloc cache_a_destruir = *alloc;
  if(cache_a_destruir.cantidad_en_uso == 0){
    Slab *slab = cache_a_destruir.slab_ptr;
    for(int i = 0;i < cache_a_destruir.tamano_cache;i++){
      cache_a_destruir.destructor(cache_a_destruir.mem_ptr + cache_a_destruir.tamano_objeto*i, cache_a_destruir.tamano_objeto);
    }
    for(int i = 0;i < cache_a_destruir.tamano_cache;i++){
      slab[i].ptr_data = NULL;
      slab[i].ptr_data_old = NULL;
      slab[i].status = DISPONIBLE;
    }
    free(cache_a_destruir.mem_ptr);
    free(cache_a_destruir.slab_ptr);
    cache_a_destruir.mem_ptr = NULL;
    cache_a_destruir.nombre = NULL;
    cache_a_destruir.tamano_cache = 0;
    cache_a_destruir.cantidad_en_uso = 0;
    cache_a_destruir.tamano_objeto = 0;
    cache_a_destruir.constructor = NULL;
    cache_a_destruir.destructor = NULL;
  }
}

void stats_cache(SlabAlloc *cache){
  printf("\n");
  printf("Nombre del SlabAlloc:\t%s\n", cache->nombre);
  printf("Cantidad de slabs:\t%d\n", cache->tamano_cache);
  //printf("Cantidad de slabs en uso:\t%d\n", cache->cantidad_en_uso);
  printf("Tamaño de objeto:\t%ld\n\n", cache->tamano_objeto);
  printf("Dirección de cache->mem_ptr: %p\n\n",cache->mem_ptr);

  Slab *slab = cache->slab_ptr;
  for (int i = 0; i< TAMANO_CACHE; i++){
    printf("Dirección ptr[%d].ptr_data: %p %d,\tptr[%d].ptr_data_old: %p\n",i,slab[i].ptr_data,slab[i].status,i,slab[i].ptr_data_old);
  }

}
