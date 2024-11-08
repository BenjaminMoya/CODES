#include "fworker.h"
#pragma pack(pop)
sem_t* mutex;
//Entrada: nombre del archivo como string 
//Salida: estructura BMPImage que le corresponde al nombre en directorio
//Descripción: lee un archivo BMP y retorna una estructura BMPImage para su manipulacion
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
    image->type = 0;
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
//Entrada: estructura BMPImage
//Salida: void
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
//Descripción: convierte la imagen a escala de grises y luego binariza la imagen segun un umbral
BMPImage* binarization(BMPImage *img, float threshold) {
    if (threshold < 0 || threshold > 1) {
        fprintf(stderr, "Threshold must be between 0 and 1.\n");
        return NULL;
    }

    BMPImage *binarizedImg = (BMPImage *)malloc(sizeof(BMPImage));
    if (binarizedImg == NULL) {
        perror("Failed to allocate memory for binarized image");
        return NULL;
    }

    binarizedImg->width = img->width;
    binarizedImg->height = img->height;
    binarizedImg->data = (RGBPixel *)malloc(img->width * img->height * sizeof(RGBPixel));
    if (binarizedImg->data == NULL) {
        perror("Failed to allocate memory for pixel data");
        free(binarizedImg);
        return NULL;
    }

    size_t numPixels = img->width * img->height;
    for (size_t i = 0; i < numPixels; ++i) {
        RGBPixel *srcPixel = &img->data[i];
        RGBPixel *dstPixel = &binarizedImg->data[i];

        // Calculate the luminance of the pixel (average of red, green, and blue values)
        float luminance = (srcPixel->r + srcPixel->g + srcPixel->b) / 3.0f;
        // Normalize luminance to the range [0, 1]
        luminance /= 255.0f;

        // Apply the threshold
        if (luminance > threshold) {
            dstPixel->r = dstPixel->g = dstPixel->b = 255;  // White
        } else {
            dstPixel->r = dstPixel->g = dstPixel->b = 0;    // Black
        }
    }

    return binarizedImg;
}
//Entrada: imagen BMP
//Salida: porcentaje de pixeles negros
//Descripción: calcula el porcentaje de pixeles en negro de la imagen
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

//Entrada: imagen BMP y un umbral  
//Salida: imagen BMP clasificada
//Descripción: clasifica la imagen en nearly black (1) o no nearly black(0) dependiendo del porcentaje de pixeles
BMPImage* classify(BMPImage* image, float umbral) {
   
    float percentage = black_percentage(image);
    if (percentage > umbral) {
        image->type = 1;
    } else {
        image->type = 0;
    }
    return image;
}

//Entrada: imagen BMP
//Salida: booleano
//Descripción: verifica si la imagen es válida
bool isValidBMPImage(const BMPImage *image) {
    // Verificar que el puntero a datos no sea NULL
    if (image->data == NULL) {
        fprintf(stderr, "Error: El puntero a los datos de la imagen es NULL.\n");
        return false;
    }

    // Verificar que el ancho y alto sean valores positivos
    if (image->width <= 0 || image->height <= 0) {
        fprintf(stderr, "Error: El ancho o el alto de la imagen es inválido.\n");
        return false;
    }

    // Verificar que el tipo de imagen sea válido (0 o 1)
    if (image->type != 0 && image->type != 1) {
        fprintf(stderr, "Error: El tipo de imagen es inválido. Debe ser 0 o 1.\n");
        return false;
    }

    // Verificar que los datos de los píxeles sean accesibles
    size_t dataSize = (size_t)image->width * image->height * sizeof(RGBPixel);
    if (dataSize == 0) {
        fprintf(stderr, "Error: El tamaño de los datos de los píxeles es 0.\n");
        return false;
    }

    // Si todas las verificaciones pasan, la imagen es válida
    return true;
}

//Entrada: nombre del archivo a crear e informacion en estructura BMPImage del mismo
//Salida: void
//Descripción: guarda la estructura BMPImage en un archivo BMP que podra visualizarse en el directorio correspondiente
void write_bmp(const char* filename, BMPImage* image) {
    if (!isValidBMPImage(image)) {
        fprintf(stderr, "Error: La imagen BMP no es válida. No se puede escribir en el archivo.\n");
        return;
    }

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

    // Escribir los datos de la imagen en el archivo
    for (int y = image->height - 1; y >= 0; y--) {
        for (int x = 0; x < image->width; x++) {
            RGBPixel pixel = image->data[y * image->width + x];
            fwrite(&pixel, sizeof(RGBPixel), 1, file);
        }
    }

    fclose(file);
}
