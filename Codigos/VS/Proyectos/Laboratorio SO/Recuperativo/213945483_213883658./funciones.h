#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <bits/getopt_core.h>

#pragma pack(push, 1)
 //cuando se trabaja con uint se usa para leer directamente los bytes de la imagen, push hace que la estructura se lea byte por byte y pop hace que se lea de forma normal
typedef struct {
    // BMP Header | Tipo de dato por bits | Descripción
    uint16_t type; // Tipo de dato, tiene 2 bytes y es un número que indica si el archivo es BMP a través de las siglas BM
    uint32_t size; // Tamaño del archivo, tiene 4 bytes y es un número que indica el tamaño del archivo en bytes
    uint16_t reserved1; // Reservado, tiene 2 bytes y es un número que no se utiliza
    uint16_t reserved2; // Reservado, tiene 2 bytes y es un número que no se utiliza
    uint32_t offset; // Offset, tiene 4 bytes y es un número que indica la posición en bytes donde comienza la información de la imagen
} BMPHeader;

typedef struct {
    uint32_t size; // Tamaño de la información de la imagen, tiene 4 bytes y es un número que indica el tamaño de la información de la imagen en bytes
    int32_t width; // Ancho de la imagen, tiene 4 bytes y es un número que indica el ancho de la imagen en píxeles
    int32_t height; // Alto de la imagen, tiene 4 bytes y es un número que indica el alto de la imagen en píxeles
    uint16_t planes; // Planos, tiene 2 bytes y es un número que indica la cantidad de planos de color, debe valer 1
    uint16_t bit_count; // Bits por píxel, tiene 2 bytes y es un número que indica la cantidad de bits por píxel, debe valer 1, 4, 8, 16, 24, or 32
    uint32_t compression; // Compresión, tiene 4 bytes y es un número que indica el tipo de compresión, puede ser 0 (sin compresión), 1 (RLE 8-bit/píxel), 2 (RLE 4-bit/píxel), 3 (bitfields), 4 (JPEG), 5 (PNG)
    uint32_t size_image; // Tamaño de la imagen, tiene 4 bytes y es un número que indica el tamaño de la imagen en bytes
    int32_t x_pixels_per_meter; // Píxeles por metro en el eje X, tiene 4 bytes y es un número que indica la cantidad de píxeles por metro en el eje X
    int32_t y_pixels_per_meter; // Píxeles por metro en el eje Y, tiene 4 bytes y es un número que indica la cantidad de píxeles por metro en el eje Y
    uint32_t colors_used; // Colores usados, tiene 4 bytes y es un número que indica la cantidad de colores usados
    uint32_t colors_important; // Colores importantes, tiene 4 bytes y es un número que indica la cantidad de colores importantes
} BMPInfoHeader;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGBPixel;

typedef struct {
    const char *name;
    int width;  // Ancho de la imagen en píxeles
    int height; // Alto de la imagen en píxeles
    int type; //  Clasificacion que se detallara en el archivo .csv donde 1=nearly black y 0=no nearly black
    RGBPixel *data; // Puntero a los píxeles de la imagen
} BMPImage;

//Funciones para leer,escribir y modificar imágenes BMP
int n_files();
BMPImage* read_bmp(const char* file_name); 
void free_bmp(BMPImage* image);
BMPImage* saturate_bmp(BMPImage* image, float saturation_fact);
BMPImage* grayscale_bmp(BMPImage* image);
BMPImage* binarization_bmp(BMPImage *image, float threshold_bina);
double black_percentage(BMPImage* image);
BMPImage* classify(BMPImage* image, float threshold_class);
void write_bmp(const char* file_name, BMPImage* image);

//Funciones para crear directorios, manejarlos, crear archivos csv y escribir en ellos
void new_folder(const char *folder_name);
void move_file(const char *file_name, const char *folder_name);
void new_csv(const char *file_name);
void write_csv(BMPImage *image,const char *csv_name);

//Funcion extra para conseguir la lista de los archivos en directorio con cierto prefijo
char** file_names(const char *img_prefix);


