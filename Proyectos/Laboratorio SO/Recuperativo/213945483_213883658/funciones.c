#include "funciones.h"
#pragma pack(pop)

//Entrada: void
//Salida: cantidad de archivos en el directorio
//Descripción: cuenta la cantidad de archivos en el directorio
int n_files(){

    DIR *dir;
    struct dirent *entry;
    int count = 0;
    char cwd[1024];

    // Obtiene el directorio actual
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stderr, "Error: En el directorio actual.\n");
        return 1;
    }

    // Abre el directorio
    dir = opendir(cwd);

    // Verifica si el directorio se abrió correctamente
    if (dir == NULL) {
        fprintf(stderr, "Error: No se pudo abrir el directorio.\n");
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

//Entrada: nombre del archivo como string 
//Salida: estructura BMPImage que le corresponde al nombre en directorio
//Descripción: lee un archivo BMP y retorna una estructura BMPImage para su manipulacion
BMPImage* read_bmp(const char* filename){

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

//Entrada: estructura BMPImage
//Salida: void
//Descripción: libera la memoria de una estructura BMPImage
void free_bmp(BMPImage* image) {

    if(image == NULL){
        fprintf(stderr, "Error: Imagen invalida.\n");
        return;
    }

    if (image) {
        free(image->data);
        free(image);
    }
}

//Entrada: imagen BMP y un factor de saturación
//Salida: imagen BMP saturada
//Descripción: satura la imagen con un factor deseado
BMPImage* saturate_bmp(BMPImage* image, float saturation_fact){

    if(image == NULL){
        fprintf(stderr, "Error: No se pudo leer la imagen.\n");
        return NULL;
    }

    BMPImage* new_image = (BMPImage*)malloc(sizeof(BMPImage)); // Se asigna memoria para la nueva imagen
    new_image->width = image->width;
    new_image->height = image->height;
    new_image->data = (RGBPixel*)malloc(sizeof(RGBPixel) * image->width * image->height); // Se asigna memoria para los píxeles de la nueva imagen

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGBPixel pixel = image->data[y * image->width + x]; // Se obtiene el valor del píxel
            RGBPixel new_pixel = pixel; // Copia del valor del píxel
            new_pixel.r = (unsigned char)(pixel.r * saturation_fact); // Se ajusta el valor del canal rojo
            new_pixel.g = (unsigned char)(pixel.g * saturation_fact); // Se ajusta el valor del canal verde
            new_pixel.b = (unsigned char)(pixel.b * saturation_fact); // Se ajusta el valor del canal azul

            // Ajuste de los valores de los canales de color para evitar desbordamientos
            new_pixel.r = (new_pixel.r > 255) ? 255 : new_pixel.r; // Si el valor del canal rojo es mayor a 255, se ajusta a 255
            new_pixel.g = (new_pixel.g > 255) ? 255 : new_pixel.g; // Si el valor del canal verde es mayor a 255, se ajusta a 255
            new_pixel.b = (new_pixel.b > 255) ? 255 : new_pixel.b; // Si el valor del canal azul es mayor a 255, se ajusta a 255

            new_image->data[y * image->width + x] = new_pixel; // Se guarda el nuevo valor del píxel en la nueva imagen
        }
    }

    return new_image;
}
//Entrada: imagen BMP
//Salida: imagen BMP en escala de grises
//Descripción: convierte la imagen a escala de grises
BMPImage* grayscale_bmp(BMPImage* image){

    if(image == NULL){
        fprintf(stderr, "Error: No se pudo leer la imagen.\n");
        return NULL;
    }

    BMPImage* new_image = (BMPImage*)malloc(sizeof(BMPImage));
    new_image->width = image->width;
    new_image->height = image->height;
    new_image->data = (RGBPixel*)malloc(sizeof(RGBPixel) * image->width * image->height); // Se asigna memoria para los píxeles de la nueva imagen

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            RGBPixel pixel = image->data[y * image->width + x];
            unsigned char gray = (unsigned char)(0.3 * pixel.r + 0.59 * pixel.g + 0.11 * pixel.b); // Se calcula el valor en escala de grises
            pixel.r = gray; // Se ajusta el valor del canal rojo
            pixel.g = gray; // Se ajusta el valor del canal verde
            pixel.b = gray; // Se ajusta el valor del canal azul
            new_image->data[y * image->width + x] = pixel; // Se guarda el nuevo valor del píxel en la nueva imagen
        }
    }

    return new_image;
}

//Entrada: imagen BMP y un umbral 
//Salida: imagen BMP binarizada
//Descripción: convierte la imagen a escala de grises y luego binariza la imagen segun un umbral
BMPImage* binarization_bmp(BMPImage *image, float threshold_bina){

    if(image == NULL){
        fprintf(stderr, "Error: No se pudo leer la imagen.\n");
        return NULL;
    }

    BMPImage *binarizedImg = (BMPImage *)malloc(sizeof(BMPImage));
    if (binarizedImg == NULL) {
        fprintf(stderr, "Error: No se pudo lozalizar memoria para la binarizacion.\n");
        return NULL;
    }

    binarizedImg->width = image->width;
    binarizedImg->height = image->height;
    binarizedImg->data = (RGBPixel *)malloc(image->width * image->height * sizeof(RGBPixel));
    if (binarizedImg->data == NULL) {
        fprintf(stderr, "Error: No se pudo lozalizar memoria para los pixeles de la binarizacion.\n");
        free(binarizedImg);
        return NULL;
    }

    size_t numPixels = image->width * image->height;
    for (size_t i = 0; i < numPixels; ++i) {
        RGBPixel *srcPixel = &image->data[i];
        RGBPixel *dstPixel = &binarizedImg->data[i];

        // Calculate the luminance of the pixel (average of red, green, and blue values)
        float luminance = (srcPixel->r + srcPixel->g + srcPixel->b) / 3.0f;
        // Normalize luminance to the range [0, 1]
        luminance /= 255.0f;

        // Apply the threshold
        if (luminance > threshold_bina) {
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
double black_percentage(BMPImage* image){

    if(image == NULL){
        fprintf(stderr, "Error: No se pudo leer la imagen.\n");
        return -1;
    }

    int pixelTotal = image->width * image->height;
    int blackPixels = 0;

    for (int i = 0; i < pixelTotal; i++) {
        RGBPixel pixel = image->data[i];

        // Consideramos un píxel como negro si todos sus componentes (R, G, B) son 0
        if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0) {
            blackPixels++;
        }
    }

    // Calculamos el porcentaje de píxeles negros
    double blackPercentage = (double)blackPixels / pixelTotal;
    return blackPercentage;
}

//Entrada: imagen BMP y un umbral  
//Salida: imagen BMP clasificada
//Descripción: clasifica la imagen en nearly black (1) o no nearly black(0) dependiendo del porcentaje de pixeles
BMPImage* classify(BMPImage* image, float threshold_class){

    if(image == NULL){
        fprintf(stderr, "Error: No se pudo leer la imagen.\n");
        return NULL;
    }
   
    double percentage = black_percentage(image);
    if (percentage > threshold_class) {
        image->type = 1;
    } else {
        image->type = 0;
    }
    return image;
}

//Entrada: nombre del archivo a crear e informacion en estructura BMPImage del mismo
//Salida: void
//Descripción: guarda la estructura BMPImage en un archivo BMP que podra visualizarse en el directorio correspondiente
void write_bmp(const char* file_name, BMPImage* image){

    FILE* file = fopen(file_name, "wb");
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
    
    image->name = file_name;
    
    fclose(file);
}
//Entrada: nombre de la carpeta 
//Salida: void
//Descripción: crea una carpeta con el nombre deseado
void new_folder(const char *folder_name){
    
    if(folder_name == NULL){
        fprintf(stderr, "Error: Nombre de directorio invalido.\n");
        return;
    }

    char comand[100];
    sprintf(comand, "mkdir %s", folder_name);
    system(comand);
}

//Entrada: nombre de archivo y nombre de la carpeta
//Salida: void
//Descripción: mueve un archivo a una carpeta determinada
void move_file(const char *file_name, const char *folder_name){
    
    if(folder_name == NULL){
        fprintf(stderr, "Error: Nombre de directorio invalido.\n");
        return;
    }

    if(file_name == NULL){
        fprintf(stderr, "Error: Nombre de imagen invalida.\n");
        return;
    }

    char comand[500];
    sprintf(comand, "mv %s %s/", file_name, folder_name);
    system(comand);
}

//Entrada: nombre del archivo csv
//Salida: void
//Descripción: crea un archivo csv con el nombre ingresado
void new_csv(const char *file_name){

    if(file_name == NULL){
        fprintf(stderr, "Error: Nombre de imagen invalida.\n");
        return;
    }

    FILE *file;
    file = fopen(file_name, "a");

    if (file == NULL) {
        printf("Error al abrir el csv\n");
        return;
    }

    fprintf(file, "Nombre,Clasificacion\n");
    fclose(file);


}

//Entrada: imagen BMP y nombre del archivo csv
//Salida: void
//Descripción: guarda el nombre de la imagen y su clasificación en un archivo csv
void write_csv(BMPImage *image,const char *csv_name){

    if(csv_name == NULL){
        fprintf(stderr, "Error: Nombre del csv invalido.\n");
        return;
    }

    FILE *file;
    file = fopen(csv_name, "a");

    if (file == NULL) {
        printf("Error al abrir el csv\n");
        return;
    }

    const char *name = image->name;
    if(name == NULL){
        fprintf(stderr, "Error: Nombre de imagen invalida.\n");
        return;
    }
    int type = image->type;
    char typestr[20]; // Suponiendo que el número entero convertido puede tener hasta 20 caracteres
    sprintf(typestr, "%d", type);
    char buffer[100]; // Asegúrate de tener suficiente espacio para contener las cadenas concatenadas
    snprintf(buffer, sizeof(buffer), "%s-%s\n", name, typestr);

    fprintf(file, "%s", buffer);
    fclose(file);
}

//Entrada: prefijo 
//Salida: arreglo de strings 
//Descripción: lee los nombres de los archivos que tengan el prefijo deseado y los guarda en un arreglo de strings
char** file_names(const char *img_prefix){

    if(img_prefix == NULL){
        fprintf(stderr, "Error: Prefijo de imagen invalida.\n");
        return NULL;
    }

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
        if (strncmp(entry->d_name, img_prefix, strlen(img_prefix)) == 0) {
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
    if (file_names == NULL && count > 0) {
        printf("Error de memoria\n");
        for (int i = 0; i < count; ++i) {
            free(file_names[i]);
        }
        free(file_names);
        return NULL;
    } else if (count != 0){ //Solo si hay archivos con el prefijo se redimensiona

        file_names = (char **)realloc(file_names, count * sizeof(char *));
    }

    file_names[count] = NULL; // Marcar el final del arreglo de nombres de archivo
    return file_names;
}