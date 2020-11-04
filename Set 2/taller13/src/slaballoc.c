#include "slaballoc.h"
#include "objetos.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


SlabAlloc *crear_cache(char *nombre, size_t tamano_objeto, constructor_fn constructor, destructor_fn destructor){
  //Inicialización, asignación
  SlabAlloc *slab=(SlabAlloc *)malloc(sizeof(SlabAlloc));
  slab->nombre=nombre;
  slab->mem_ptr=(void *)malloc(tamano_objeto*TAMANO_CACHE);
  slab->tamano_cache=TAMANO_CACHE;
  slab->constructor=constructor;
  slab->destructor=destructor;

  for(int i=0;i<tamano_objeto*TAMANO_CACHE;i+=tamano_objeto){
    constructor(slab->mem_ptr+i,tamano_objeto);
  }

  slab->cantidad_en_uso=0;
  slab->tamano_objeto=tamano_objeto;
  Slab* punteroSlab=(Slab *)malloc(sizeof(Slab)*TAMANO_CACHE);

  for(int j=0;j<TAMANO_CACHE;j++){
    Slab cache;

    cache.ptr_data = slab->mem_ptr+(j*tamano_objeto);
    cache.ptr_data_old = slab->mem_ptr+(j*tamano_objeto);
    cache.status = DISPONIBLE;

    *(punteroSlab+j)=cache;
  }
  slab->slab_ptr=punteroSlab;

  return slab;
}

void *obtener_cache(SlabAlloc *alloc, int crecer){
  if(alloc == NULL){
    return NULL;
  }

  Slab *ptr = alloc->slab_ptr;

  int i = 0;
  //P(s)
  for (i = 0; i< alloc->tamano_cache;i++){
    if(ptr[i].status == DISPONIBLE){
      ptr[i].status = EN_USO;
      alloc->cantidad_en_uso +=1;
      return ptr[i].ptr_data;
    }
  }
  //V(s)
  return NULL;
}

void devolver_cache(SlabAlloc *alloc, void *obj){
  Slab *slab= alloc->slab_ptr;

  for(int i =0;i<alloc->tamano_cache;i++){
    if (obj==slab[i].ptr_data){
      slab[i].ptr_data=NULL;
      slab[i].status= DISPONIBLE;
      alloc->cantidad_en_uso -=1;
      alloc->destructor(alloc->mem_ptr + alloc->tamano_objeto*i, alloc->tamano_objeto);
      break;
    }
  }
}

void destruir_cache(SlabAlloc *alloc){
  if (alloc->cantidad_en_uso == 0){
    int i = 0;
    for (i = 0; i < alloc->tamano_cache; i++){
      alloc->destructor(alloc->mem_ptr + alloc->tamano_objeto*i, alloc->tamano_objeto);
    }
    free(alloc->slab_ptr);
    free(alloc->mem_ptr);
    alloc = NULL;
    free(alloc);
  }
}

void stats_cache(SlabAlloc *cache){
  SlabAlloc cache1 = *cache;
  printf("\nNombre del SlabAlloc:\t%s\n", cache1.nombre);
  printf("Cantidad de slabs:\t%d\n", cache1.tamano_cache);
  printf("Cantidad de slabs en uso:\t%d\n", cache1.cantidad_en_uso);
  printf("Tamaño de objeto:\t%ld\n\n", cache1.tamano_objeto);
  printf("Dirección de cache: %p\n\n",cache1.mem_ptr);

  Slab *slab = cache->slab_ptr;
  for (int i = 0; i< TAMANO_CACHE; i++){
    if(slab[i].status == DISPONIBLE){
      printf("Direccion ptr[%d].ptr_data: <%p>    <DISPONIBLE>,   ptr[%d].ptr_data_old: <%p>\n", i, slab[i].ptr_data, i, slab[i].ptr_data_old);
    } else {
      printf("Direccion ptr[%d].ptr_data: <%p>    <EN_USO>,   ptr[%d].ptr_data_old: <%p>\n", i, slab[i].ptr_data, i, slab[i].ptr_data_old);
    }
  }
}
