#include "funciones.h"
#pragma pack(pop)
//entrada: ninguna
//salida: cantidad de archivos en el directorio
//Descripción: cuenta la cantidad de archivos en el directorio
int n_files(){

    DIR *dir;
    struct dirent *entry;
    int count = 0;
    char cwd[1024];

    // Obtiene el directorio actual
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Error al obtener el directorio actual");
        return 1;
    }

    // Abre el directorio
    dir = opendir(cwd);

    // Verifica si el directorio se abrió correctamente
    if (dir == NULL) {
        perror("No se pudo abrir el directorio");
        return 1;
    }

    // Lee cada entrada en el directorio
    while ((entry = readdir(dir)) != NULL) {
        // Ignora las entradas "." y ".."
        if (entry->d_name[0] != '.') {
            count++;
        }
    }

    // Cierra el directorio
    closedir(dir);
    return count;

}
//entreada: nombre del archivo
//salida: estructura BMPImage
//Descripción: lee un archivo BMP y lo guarda en una estructura BMPImage
BMPImage* read_bmp(const char* filename) {
    FILE* file = fopen(filename, "rb"); //rb = read binary
    if (!file) {
        fprintf(stderr, "Error: No se pudo abrir el archivo.\n");
        return NULL;
    }

    BMPHeader header; //se crea una estructura de tipo BMPHeader
    fread(&header, sizeof(BMPHeader), 1, file); //fread(puntero a la estructura, tamaño de la estructura, cantidad de estructuras, archivo) 
    if (header.type != 0x4D42) { // 42 = 66 en decimal = B en ASCII y 4D = 77 en decimal = M en ASCII
        fprintf(stderr, "Error: El archivo no es un BMP válido.\n");
        fclose(file);
        return NULL;
    }

    BMPInfoHeader info_header;
    fread(&info_header, sizeof(BMPInfoHeader), 1, file); //fread(puntero a la estructura, tamaño de la estructura, cantidad de estructuras, archivo)

    BMPImage* image = (BMPImage*)malloc(sizeof(BMPImage));
    image->name = filename;
    image->width = info_header.width;
    image->height = info_header.height;
    image->data = (RGBPixel*)malloc(sizeof(RGBPixel) * info_header.width * info_header.height);

    fseek(file, header.offset, SEEK_SET); // fseek(archivo, desplazamiento, origen desde donde se desplaza SEEK_SET = inicio del archivo, SEEK_CUR = posición actual del archivo, SEEK_END = final del archivo)

    //se hace padding para que la imagen tenga un tamaño múltiplo de 4, esto se hace para que la imagen sea más rápida de leer
    int padding = (4 - (info_header.width * sizeof(RGBPixel)) % 4) % 4; // primero se pasan a bytes los píxeles de la imagen y se calcula el residuo de la división entre 4, si el residuo es 0 no hay padding, si el residuo es 1, 2 o 3 se calcula el padding
    for (int y = info_header.height - 1; y >= 0; y--) {
        for (int x = 0; x < info_header.width; x++) {
            RGBPixel pixel;
            fread(&pixel, sizeof(RGBPixel), 1, file);
            image->data[y * info_header.width + x] = pixel;
        }
        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);
    return image;
}
//entrada: estructura BMPImage
//salida: estructura BMPImage liberada
//Descripción: libera la memoria de una estructura BMPImage
void free_bmp(BMPImage* image) {
    if (image) {
        free(image->data);
        free(image);
    }
}


//Entrada: imagen BMP y un factor de saturación
//Salida: imagen BMP saturada
//Descripción: satura la imagen con un factor deseado
BMPImage* saturate_bmp(BMPImage* image, float factor) {
    BMPImage* new_image = (BMPImage*)malloc(sizeof(BMPImage));
    new_image->width = image->width;
    new_image->height = image->height;
    new_image->data = (RGBPixel*)malloc(sizeof(RGBPixel) * image->width * image->height);

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGBPixel pixel = image->data[y * image->width + x];
            RGBPixel new_pixel = pixel; // Copia del valor del píxel
            new_pixel.r = (unsigned char)(pixel.r * factor);
            new_pixel.g = (unsigned char)(pixel.g * factor);
            new_pixel.b = (unsigned char)(pixel.b * factor);

            // Ajuste de los valores de los canales de color para evitar desbordamientos
            new_pixel.r = (new_pixel.r > 255) ? 255 : new_pixel.r;
            new_pixel.g = (new_pixel.g > 255) ? 255 : new_pixel.g;
            new_pixel.b = (new_pixel.b > 255) ? 255 : new_pixel.b;

            new_image->data[y * image->width + x] = new_pixel;
        }
    }

    return new_image;
}
//Entrada: imagen BMP
//Salida: imagen BMP en escala de grises
//Descripción: convierte la imagen a escala de grises
BMPImage* grayscale(BMPImage* image) {
    BMPImage* new_image = (BMPImage*)malloc(sizeof(BMPImage));
    new_image->width = image->width;
    new_image->height = image->height;
    new_image->data = (RGBPixel*)malloc(sizeof(RGBPixel) * image->width * image->height);

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGBPixel pixel = image->data[y * image->width + x];
            unsigned char gray = (unsigned char)(0.3 * pixel.r + 0.59 * pixel.g + 0.11 * pixel.b);
            pixel.r = gray;
            pixel.g = gray;
            pixel.b = gray;
            new_image->data[y * image->width + x] = pixel;
        }
    }

    return new_image;
}
//Entrada: imagen BMP y un umbral
//Salida: imagen BMP binarizada
//Descripción: convierte la imagen a escala de grises y luego binariza la imagen con un umbral
BMPImage* binarization(BMPImage* image, float umbral) {
    BMPImage* new_image = (BMPImage*)malloc(sizeof(BMPImage));
    new_image->width = image->width;
    new_image->height = image->height;
    new_image->data = (RGBPixel*)malloc(sizeof(RGBPixel) * image->width * image->height);

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGBPixel pixel = image->data[y * image->width + x];
            RGBPixel new_pixel = pixel; // Copia del valor del píxel
            unsigned char gray = (unsigned char)(0.3 * pixel.r + 0.59 * pixel.g + 0.11 * pixel.b);

            new_pixel.r = (gray < umbral) ? 0 : 255;
            new_pixel.g = (gray < umbral) ? 0 : 255;
            new_pixel.b = (gray < umbral) ? 0 : 255;

            new_image->data[y * image->width + x] = new_pixel;
        }
    }
    
    return new_image;
}
//entrada: imagen BMP
//salida: porcentaje de pixeles negros
//Descripción: calcula el porcentaje
float black_percentage(BMPImage* image) {
    float* percentages = (float*)malloc(sizeof(float) * ((image->height)*(image->width)));
    int count = 0;
    float percentage = 0;

    for (int y = 0; y < image->height; y++) {
        
        for (int x = 0; x < image->width; x++) {
            RGBPixel pixel = image->data[y * image->width + x];
            if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0) {
                count++;
            }
        }
        
    }
    percentage = (count) / ((image->height)*(image->width));
    return percentage;
}

//entrada: imagen BMP y un umbral  
//salida: imagen BMP clasificada
//Descripción: clasifica la imagen en nearly black o no nearly black dependiendo del porcentaje de pixeles
BMPImage* classify(BMPImage* image, float umbral) {
   
    float percentage = black_percentage(image);
    if (percentage > umbral) {
        image->type = 1;
    } else {
        image->type = 0;
    }
    return image;
}

//entrada: nombre del archivo y estructura BMPImage
//salida: archivo BMP
//Descripción: guarda la estructura BMPImage en un archivo BMP
void write_bmp(const char* filename, BMPImage* image) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Error: No se pudo abrir el archivo.\n");
        return;
    }

    BMPHeader header;
    header.type = 0x4D42; // BM
    header.size = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + image->width * image->height * sizeof(RGBPixel);
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.offset = sizeof(BMPHeader) + sizeof(BMPInfoHeader);

    BMPInfoHeader info_header;
    info_header.size = sizeof(BMPInfoHeader);
    info_header.width = image->width;
    info_header.height = image->height;
    info_header.planes = 1;
    info_header.bit_count = 24; // 24 bits por píxel (RGB)
    info_header.compression = 0; // Sin compresión
    info_header.size_image = 0; // Puede ser 0 si no hay compresión
    info_header.x_pixels_per_meter = 0;
    info_header.y_pixels_per_meter = 0;
    info_header.colors_used = 0; // Todos los colores están siendo utilizados
    info_header.colors_important = 0; // Todos los colores son importantes

    fwrite(&header, sizeof(BMPHeader), 1, file);
    fwrite(&info_header, sizeof(BMPInfoHeader), 1, file);

    for (int y = image->height - 1; y >= 0; y--) {
        for (int x = 0; x < image->width; x++) {
            RGBPixel pixel = image->data[y * image->width + x];
            fwrite(&pixel, sizeof(RGBPixel), 1, file);
        }
    }

    fclose(file);
}
//entrada: nombre de la carpeta
//salida: carpeta creada
//Descripción: crea una carpeta con el nombre deseado
void new_folder(const char *foldername) {
    // Comando para crear la carpeta
    char comand[100];
    sprintf(comand, "mkdir %s", foldername);
    system(comand);
}

//entrada: nombre del archivo y nombre de la carpeta
//salida: archivo movido a la carpeta
//Descripción: mueve un archivo a una carpeta
void move_file(const char *filename, const char *foldername) {
    // Comando para mover el archivo
    char comand[500];
    sprintf(comand, "move %s %s/", filename, foldername);
    system(comand);
}
//entrada: nombre del archivo csv
//salida: archivo csv
//Descripción: crea un archivo csv con el nombre del archivo

void new_csv(const char *filename){

    FILE *file;
    file = fopen(filename, "a");

    if (file == NULL) {
        printf("Error al abrir el csv\n");
        return ;
    }

    fprintf(file, "Nombre,Clasificacion\n");
    fclose(file);


}
//entrada: imagen BMP y nombre del archivo csv
//salida: archivo csv
//Descripción: guarda el nombre de la imagen y su clasificación en un archivo csv

void write_csv(BMPImage *image, const char *csvname) {
    FILE *file;
    file = fopen(csvname, "a");

    if (file == NULL) {
        printf("Error al abrir el csv\n");
        return;
    }

    const char *name = image->name;
    int type = image->type;
    char typestr[20]; // Suponiendo que el número entero convertido puede tener hasta 20 caracteres
    sprintf(typestr, "%d", type);
    char buffer[100]; // Asegúrate de tener suficiente espacio para contener las cadenas concatenadas
    snprintf(buffer, sizeof(buffer), "%s-%s\n", name, typestr);

    fprintf(file, "%s", buffer);
    fclose(file);
}

//entrada: prefijo de los archivos
//salida: arreglo de strings con los nombres de los archivos
//Descripción: lee los nombres de los archivos que tengan el prefijo deseado y los guarda en un arreglo de strings
char** file_names(const char *prefix) {
    DIR *dir;
    struct dirent *entry;
    char **file_names = NULL;
    int count = 0;
    int size = 10; // Tamaño inicial para el arreglo de nombres de archivo
    dir = opendir(".");
    if (dir == NULL) {
        printf("No se pudo abrir el directorio\n");
        return NULL;
    }

    // Asignar memoria para el arreglo de nombres de archivo
    file_names = (char **)malloc(size * sizeof(char *));
    if (file_names == NULL) {
        printf("Error de memoria\n");
        closedir(dir);
        return NULL;
    }

    // Leer cada entrada del directorio
    while ((entry = readdir(dir)) != NULL) {
        // Verificar si el nombre del archivo tiene el prefijo deseado
        if (strncmp(entry->d_name, prefix, strlen(prefix)) == 0) {
            // Asignar memoria para el nombre de archivo
            file_names[count] = (char *)malloc(strlen(entry->d_name) + 1);
            if (file_names[count] == NULL) {
                printf("Error de memoria\n");
                closedir(dir);
                for (int i = 0; i < count; ++i) {
                    free(file_names[i]);
                }
                free(file_names);
                return NULL;
            }
            // Copiar el nombre del archivo al arreglo de strings
            strcpy(file_names[count], entry->d_name);
            count++;

            // Redimensionar el arreglo de nombres de archivo si es necesario
            if (count >= size) {
                size *= 2;
                file_names = (char **)realloc(file_names, size * sizeof(char *));
                if (file_names == NULL) {
                    printf("Error de memoria\n");
                    closedir(dir);
                    for (int i = 0; i < count; ++i) {
                        free(file_names[i]);
                    }
                    free(file_names);
                    return NULL;
                }
            }
        }
    }

    closedir(dir);

    // Redimensionar el arreglo de nombres de archivo al número real de nombres de archivo encontrados
    file_names = (char **)realloc(file_names, count * sizeof(char *));
    if (file_names == NULL && count > 0) {
        printf("Error de memoria\n");
        for (int i = 0; i < count; ++i) {
            free(file_names[i]);
        }
        free(file_names);
        return NULL;
    }
    file_names[count] = NULL; // Marcar el final del arreglo de nombres de archivo
    return file_names;
}