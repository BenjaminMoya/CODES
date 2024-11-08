#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <windows.h>
#include <Shlwapi.h>


#pragma pack(push, 1) //cuando se trabaja con uint se usa para leer directamente los bytes de la imagen, push hace que la estructura se lea byte por byte y pop hace que se lea de forma normal
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

//funciones para leer,escribir y modificar imágenes BMP
int n_files();
BMPImage* read_bmp(const char* filename); 
void free_bmp(BMPImage* image);
BMPImage* saturate_bmp(BMPImage* image, float factor);
BMPImage* grayscale(BMPImage* image);
BMPImage* binarization(BMPImage* image, float umbral);
float black_percentage(BMPImage* image);
BMPImage* classify(BMPImage* image, float umbral);
void write_bmp(const char* filename, BMPImage* image);

//funciones para leer y escribir archivos CSV
void new_folder(const char *foldername);
void move_file(const char *filename, const char *foldername);
void new_csv(const char *filename);
void write_csv(BMPImage *image,const char *csvname);
char** file_names(const char *prefix);


