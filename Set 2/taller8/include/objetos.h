//En este archivo ud podra definir los objetos que podrán ser usados
//con el slab allocator. Declare tambien el constructor y destructor de
//cada objeto declarado. Abajo se provee un objeto de ejemplo.
//Declare al menos tres objetos distintos

//El constructor siempre recibe un puntero tipo void al tipo de objeto,
//y su tamaño (tal como se declaro el puntero a funcion).
//No olvide implementar las funciones de crear y destruir de cada objeto.
typedef void (*constructor)(void *, size_t);
typedef void (*destructor)(void *, size_t);


typedef struct ejemplo{
    int a;
    float b[100];
    char *msg;
    unsigned int refcount;
} Ejemplo;

//Constructor
void crear_Ejemplo(void *ref, size_t tamano);

//Destructor
void destruir_Ejemplo(void *ref, size_t tamano);

//TODO: Crear 3 objetos mas

// Objeto 1
typedef struct Elfo {
  float dinero;
  int flechas;
  char *nombre;
} Elfo;

// Constructor Objeto 1
void crear_elfo(void *ref, size_t tamano);

// Destructor Objeto 1
void destruir_elfo(void *ref, size_t tamano);

// Objeto 2
typedef struct Hobbit {
  int edad;
  int estado;
  char *nombre;
} Hobbit;

// Constructor Objeto 2
void crear_hobbit(void *ref, size_t tamano);

// Destructor Objeto 2
void destruir_hobbit(void *ref, size_t tamano);

// Objeto 3
typedef struct Sauron {
  int anillos;
  char *plan;
} Sauron;

// Constructor Objeto 3
void crear_sauron(void *ref, size_t tamano);

// Destructor Objeto 3
void destruir_sauron(void *ref, size_t tamano);
