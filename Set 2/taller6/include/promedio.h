typedef struct
{
        int capacidad, size;
        float *items;
} arrD;

void minMax(float num);
void calcularDE(arrD *arrD);
void imprimirResultados();
void arrD_init(arrD *arrD);
void arrD_agregar(arrD *arrD, float valor);
void arrD_duplicar_capacidad(arrD *arrD);
void arrD_free(arrD *arrD);
void arrD_imprimir(arrD *arrD);
