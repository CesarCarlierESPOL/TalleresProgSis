//
//Autor: Eduardo Murillo, M.Sc.
//
//NO modificar este archivo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define TAMANO_CACHE 250        //en # de slabs
#define EN_USO 1
#define DISPONIBLE 0

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

//Punteros a funciones
typedef void (*constructor_fn)(void *, size_t);
typedef void (*destructor_fn)(void *, size_t);


typedef struct slab{
  void *ptr_data;          //puntero al objeto del usuario
  void *ptr_data_old;      //si el cache mem_ptr fue movido por realloc, aqui tendremos la direccion anterior donde apuntaba ptr_data
  unsigned int status;     //Si el slab esta en uso o no
} Slab;


typedef struct slaballoc{
  char *nombre;		//Nombre de este allocator
  void *mem_ptr;              //Puntero al bloque de memoria donde se cachearan los objetos de usuario
  unsigned int tamano_cache;       //cantidad de slabs. Por defecto TAMANO_CACHE
  unsigned int cantidad_en_uso;    //Cantidad de slabs en uso;
  size_t tamano_objeto;       //tamano de objeto de usuario
  constructor_fn constructor; //funcion constructora del objeto de usurio
  destructor_fn destructor;   //funcion destructora del objeto de usuario
  Slab *slab_ptr;             //Arreglo de estructuras con informacion de cada slab;
} SlabAlloc;




//Crea el cache. Esta funcion debe crear
//1. El objeto SlabAlloc
//2. El arreglo de tamano TAMANO_CACHE de estructuras SlabAlloc
//   (este espacio debe ser creado dinamicamente, ya que podrá crecer).
//3. Reservar el espacio de memoria para cachear los objetos dado por TAMANO_CACHE * tamano_objeto
//   (este espacio debe ser creado dinamicamente, ya que podrá crecer).
//4. La funcion recibe dos punteros a funciones, que se guardan en la struct SlabAlloc
//Cuando cree el cache, ud debe llamar a la funcion constructor por cada objeto
SlabAlloc *crear_cache(char *nombre, size_t tamano_objeto, constructor_fn constructor, destructor_fn destructor);



  //Retorna un objeto con bandera en DISPONIBLE
  //Tiene que haber slabs disponibles
  //Se marca el slab como EN_USO.
  //Si la bandera cache->crecer == 1 y si ya no hay
  //objetos disponibles, debe hacer crecer el cache
  //al doble del tamaño anterior. Caso contrario, solo
  //retorne null. No olvide crear las nuevas structs
  //SlabAlloc que tendran la información de los nuevos
  //objetos.
  //Si ya todos los objetos estan en uso, y la bandera
  // crecer == 1, duplique el tamano del cache actual.
  void *obtener_cache(SlabAlloc *alloc, int crecer);



  //Devuelve un objeto al cache (se marca el slab  como DISPONIBLE).
  //Estos sucede si *obj == slab.ptr_data (sabemos cual es el slab
  //que esta asociado al objeto, y por lo tanto podemos marcar el
  //slab como disponible.
  void devolver_cache(SlabAlloc *alloc, void *obj);


  //Destruimos el cache. Solo lo destruimos si no hay ninguna asignacion
  //(cantidad_en_uso == 0).
  //No olvide no solo liberar la memoria del cache
  //sino tambien la memoria de la informacion de slabs y del puntero cache
  //tambien. Llama a destructor sobre cada objeto.
  void destruir_cache(SlabAlloc *alloc);


  //Muestra el estado del cache. El formato de salida es:
  //
  //Nombre de cache: 		<nombre>
  //Cantidad de slabs: 		<numero>
  //Cantidad de slabs en uso	<numero>
  //Tamano de objeto		<tamano en bytes>
  //
  //Direccion de cache->mem_ptr	<direccion del bloque de memoria de cache de objetos>
  //direccion ptr[0].ptr_data: 	<direccion en hex>  <EN_USO|DISPONIBLE>, ptr[0].ptr_data_old: 	<direccion en hex>
  //direccion ptr[1].ptr_data: 	<direccion en hex>  <EN_USO|DISPONIBLE>, ptr[1].ptr_data_old: 	<direccion en hex>
  //direccion ptr[2].ptr_data: 	<direccion en hex>  <EN_USO|DISPONIBLE>, ptr[2].ptr_data_old: 	<direccion en hex>
  //...
  void stats_cache(SlabAlloc *cache);
