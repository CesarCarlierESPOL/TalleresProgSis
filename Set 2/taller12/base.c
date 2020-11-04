#include <stdio.h>
#include <png.h>
/* Parte del codigo tomado de https://gist.github.com/niw/5963798 */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>


double obtenerTiempoActual(){
  struct timespec tsp;
  clock_gettime(CLOCK_REALTIME, &tsp);
  double secs=(double)tsp.tv_sec;
  double nano = (double) tsp.tv_nsec/1000000000.0;
  return secs + nano;
}

typedef struct{
  int width;
  int height;
  png_bytep *row_pointers;
  int id;
  int n;
  png_bytep *res;
}estructuraHilo;


//Retorna los pixeles de la imagen, y los datos relacionados en los argumentos: ancho, alto, tipo de color (normalmente RGBA) y bits por pixel (usualemente 8 bits)
png_bytep * abrir_archivo_png(char *filename, int *width, int *height, png_byte *color_type, png_byte *bit_depth) {
  FILE *fp = fopen(filename, "rb");

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) abort();

  png_infop info = png_create_info_struct(png);
  if(!info) abort();

  if(setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  png_read_info(png, info);

  //resolucion y color de la image. Usaremos espacio de color RGBA
  *width      = png_get_image_width(png, info);
  *height     = png_get_image_height(png, info);
  *color_type = png_get_color_type(png, info);
  *bit_depth  = png_get_bit_depth(png, info);

  // Read any color_type into 8bit depth, RGBA format.
  // See http://www.libpng.org/pub/png/libpng-manual.txt

  if(*bit_depth == 16)
  png_set_strip_16(png);

  if(*color_type == PNG_COLOR_TYPE_PALETTE)
  png_set_palette_to_rgb(png);

  // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
  if(*color_type == PNG_COLOR_TYPE_GRAY && *bit_depth < 8)
  png_set_expand_gray_1_2_4_to_8(png);

  if(png_get_valid(png, info, PNG_INFO_tRNS))
  png_set_tRNS_to_alpha(png);

  // These color_type don't have an alpha channel then fill it with 0xff.
  if(*color_type == PNG_COLOR_TYPE_RGB ||
    *color_type == PNG_COLOR_TYPE_GRAY ||
    *color_type == PNG_COLOR_TYPE_PALETTE){
      png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    }

    if(*color_type == PNG_COLOR_TYPE_GRAY ||
      *color_type == PNG_COLOR_TYPE_GRAY_ALPHA){
      png_set_gray_to_rgb(png);
    }

    png_bytep *row_pointers;
    png_read_update_info(png, info);
    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * (*height));
    if(row_pointers == NULL){
      printf("Error al obtener memoria de la imagen\n");
      exit(-1);
    }
    for(int y = 0; y < *height; y++) {
      row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }

    png_read_image(png, row_pointers);

    fclose(fp);
    return row_pointers;
  }

  //Usaremos bit depth 8
  //Color type PNG_COLOR_TYPE_GRAY_ALPHA
  void guardar_imagen_png(char *filename, int width, int height, png_byte color_type, png_byte bit_depth, png_bytep *res) {
    //int y;

    FILE *fp = fopen(filename, "wb");
    if(!fp) abort();

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();

    png_infop info = png_create_info_struct(png);
    if (!info) abort();

    if (setjmp(png_jmpbuf(png))) abort();

    png_init_io(png, fp);

    // Salida es escala de grises
    png_set_IHDR(
      png,
      info,
      width, height,
      bit_depth,
      color_type,
      PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_DEFAULT,
      PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
    // Use png_set_filler().
    //png_set_filler(png, 0, PNG_FILLER_AFTER);
    png_write_image(png, res);	//row_pointers
    png_write_end(png, NULL);
    for(int y = 0; y < height; y++) {
      free(res[y]);		//row_pointers
    }
    free(res);			//row_pointers

    fclose(fp);
  }

  //Retorna el arreglo de pixeles
  png_bytep* procesar_archivo_png(int width, int height, png_bytep *row_pointers) {

    //filas de nueva imagen
    png_bytep *res = (png_bytep*)malloc(sizeof(png_bytep *) * height);
    if(res == NULL){
      printf("No se pudo reservar espacio para la imagen procesada");
      exit(-1);
    }

    for(int y = 0; y < height; y++) {
      png_bytep row = row_pointers[y];

      //espacio para la los pixeles de dicha fila
      res[y] = malloc(sizeof(png_bytep)*width*2);			//greyscale con alpha, 2 bytes por pixel

      if(res[y] == NULL){
        printf("No se pudo reservar espacio para la imagen procesada");
        exit(-1);
      }


      for(int x = 0; x < width; x++) {
        png_bytep px = &(row[x * 4]);

        //Convertimos a escala de grises
        float a = .299f * px[0] + .587f * px[1] + .114f * px[2];
        res[y][2*x] = a;
        res[y][2*x + 1] = px[3]; //transparencia... dejamos el campo de transparencia igual.

      }
    }

    return res;
  }

  void *procesar_con_hilos(void *var){
    estructuraHilo *c = (estructuraHilo *)var;
    for(int i = c->id;i<c->height;i+=c->n){
      c->res[i] = malloc(sizeof(png_bytep)*c->width*2);
      if(c->res[i] == NULL){
        printf("No se pudo reservar espacio para la imagen procesada");
        exit(-1);
      }

      png_bytep fila = c->row_pointers[i];
      for(int x = 0; x < c->width; x++) {
        png_bytep pixeles = &(fila[x * 4]);
        float a = .299f * pixeles[0] + .587f * pixeles[1] + .114f * pixeles[2];
        c->res[i][2*x] = a;
        c->res[i][2*x + 1] = pixeles[3];
      }
    }
    return c;
  }

  png_bytep* procesar_archivo_png_con_hilos(int width, int height, int n, png_bytep *row_pointers,png_byte bit_depth) {
    pthread_t hilo[n];
    png_bytep *res = (png_bytep*)malloc(sizeof(png_bytep *) * height);

    for(int i = 0; i<n;i++){
      pthread_t id;
      estructuraHilo *thread = (estructuraHilo*) malloc(sizeof(estructuraHilo));
      thread->width = width;
      thread->height = height;
      thread->row_pointers = row_pointers;
      thread->n = n;
      thread->id=i;
      thread->res=res;
      pthread_create(&id,NULL,procesar_con_hilos,thread);
      hilo[i]=id;
    }

    for(int i=0;i<n;i++){
      void *c;
      pthread_join(hilo[i],&c);
      free(c);
    }

    for(int i = 0 ; i<height;i++){
      free(row_pointers[i]);
    }
    free(row_pointers);
    return res;
  }

  int main(int argc, char *argv[]) {
    int num_hilos = 0;
    if(argc != 5) {
      printf("Número incorrecto de argumentos.\n");
      printf("Uso apropiado: ./procesador <fuente> <destino> -n <num_hilos>\n");

    }

    num_hilos=atoi(argv[4]);
    if((strcmp(argv[3],"-n")!=0)|| num_hilos<=0){
      return 0;
    }


    //Datos de la imagen original
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    png_bytep *pixeles;

    pixeles = abrir_archivo_png(argv[1],&width, &height, &color_type, &bit_depth);
    double start = obtenerTiempoActual();
    png_bytep *res = procesar_archivo_png_con_hilos(width,height,num_hilos, pixeles, bit_depth);
    double end = obtenerTiempoActual();
    double tiempoProcesamiento = end - start;
    guardar_imagen_png(argv[2], width, height, PNG_COLOR_TYPE_GRAY_ALPHA, bit_depth, res);
    printf("Tiempo para procesamiento fue %f segundos, utilizando %d hilos.\n", tiempoProcesamiento, num_hilos);
    return 0;
  }
