#include "fbroker.h"

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

void new_folder(const char *foldername) {
    // Comando para crear la carpeta
    char comand[100];
    sprintf(comand, "mkdir %s", foldername);
    system(comand);
}

//Entrada: nombre de archivo y nombre de la carpeta
//Salida: void
//Descripción: mueve un archivo a una carpeta determinada
void move_file(const char *filename, const char *foldername) {
    // Comando para mover el archivo
    char comand[500];
    sprintf(comand, "mv %s %s/", filename, foldername);
    system(comand);
}
//Entrada: nombre del archivo csv
//Salida: void
//Descripción: crea un archivo csv con el nombre ingresado

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
//Entrada: imagen BMP y nombre del archivo csv
//Salida: void
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

//Entrada: prefijo 
//Salida: arreglo de strings 
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

BMPImage** split_image(BMPImage *image, int num_workers) {
    if (num_workers <= 0 || image == NULL) {
        fprintf(stderr, "Número de trabajadores no válido o imagen nula.\n");
        return NULL;
    }

    // Calcular el ancho de la imagen para cada worker
    int width_per_worker = image->width / num_workers;
    int remaining_width = image->width % num_workers;

    BMPImage **subimages = malloc(num_workers * sizeof(BMPImage*));
    if (subimages == NULL) {
        fprintf(stderr, "Error al asignar memoria para subimágenes.\n");
        return NULL;
    }

    int start_col = 0;

    for (int i = 0; i < num_workers; i++) {
        int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0); // Últimos workers reciben columnas adicionales

        // Crear la subimagen para este worker
        BMPImage *subimage = (BMPImage*)malloc(sizeof(BMPImage));
        if (subimage == NULL) {
            fprintf(stderr, "Error al asignar memoria para una subimagen.\n");
            // Liberar memoria de las subimágenes ya creadas
            for (int j = 0; j < i; j++) {
                free(subimages[j]->data);
                free(subimages[j]);
            }
            free(subimages);
            return NULL;
        }

        subimage->name = image->name; // O asignar un nombre único
        subimage->width = subimage_width;
        subimage->height = image->height;
        subimage->type = image->type;
        subimage->data = malloc(subimage_width * image->height * sizeof(RGBPixel));
        if (subimage->data == NULL) {
            fprintf(stderr, "Error al asignar memoria para los datos de la subimagen.\n");
            free(subimage);
            // Liberar memoria de las subimágenes ya creadas
            for (int j = 0; j < i; j++) {
                free(subimages[j]->data);
                free(subimages[j]);
            }
            free(subimages);
            return NULL;
        }

        // Copiar los datos de la imagen original a la subimagen
        for (int y = 0; y < image->height; y++) {
            for (int x = 0; x < subimage_width; x++) {
                subimage->data[y * subimage_width + x] = image->data[y * image->width + (start_col + x)];
            }
        }

        subimages[i] = subimage;
        start_col += subimage_width; // Mover el punto de inicio para la siguiente subimagen
    }

    return subimages;
}

// Liberar memoria de las subimágenes generadas
void free_subimages(BMPImage **subimages, int num_workers) {
    for (int i = 0; i < num_workers; i++) {
        free(subimages[i]->data);
        free(subimages[i]);
    }
    free(subimages);
}



BMPImage* combine_images(BMPImage **images, int num_images) {
    if (num_images == 0) return NULL;

    int total_width = 0;
    int height = images[0]->height;

    // Calcular el ancho total y verificar la altura
    for (int i = 0; i < num_images; i++) {
        total_width += images[i]->width;
        if (images[i]->height != height) {
            printf("Las imágenes deben tener la misma altura para combinarse horizontalmente.\n");
            return NULL;
        }
    }

    // Crear la imagen combinada
    BMPImage *combined_image = (BMPImage*)malloc(sizeof(BMPImage));
    combined_image->width = total_width;
    combined_image->height = height;
    combined_image->type = images[0]->type;
    combined_image->data = (RGBPixel*)malloc(total_width * height * sizeof(RGBPixel));

    // Inicializar la imagen combinada con píxeles negros
    memset(combined_image->data, 0, total_width * height * sizeof(RGBPixel));

    // Combinar las imágenes
    RGBPixel *dest = combined_image->data;
    for (int i = 0; i < num_images; i++) {
        RGBPixel *src = images[i]->data;
        int width = images[i]->width;

        for (int y = 0; y < height; y++) {
            // Copiar los píxeles de la imagen fuente al destino
            for (int x = 0; x < width; x++) {
                if (x < total_width) {
                    dest[y * total_width + x] = src[y * width + x];
                }
            }
        }
        dest += width;
    }

    return combined_image;
}

BMPImage** send_and_receive(BMPImage** imageSplit, int num_workers, int filter_opt, float saturation_fact, float threshold_bina) {

    int fd[2];  
    int fd2[2];
    pid_t pid;
    size_t pixel_data_size;

    for (int i = 0; i < num_workers; i++){ // crear hijos

        if (pipe(fd) == -1 || pipe(fd2) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        pid = fork();
        if(pid == -1){

            exit(EXIT_FAILURE);

        } else if (pid == 0){ // si es el proceso hijo
        
            close(fd[1]); // Cerrar escritura del pipe hijo
            close(fd2[0]); // Cerrar lectura del pipe padre

                // Redirigir lectura del pipe hijo a STDIN
            if (dup2(fd[0], STDIN_FILENO) == -1) {
                perror("dup2 stdin");
                exit(EXIT_FAILURE);
            }
            close(fd[0]); // Cerrar descriptor original

                // Redirigir escritura del pipe padre a STDOUT
            if (dup2(fd2[1], STDOUT_FILENO) == -1) {
                perror("dup2 stdout");
                exit(EXIT_FAILURE);
            }
            close(fd2[1]); // Cerrar descriptor original

            char int_str1[32],float_str2[32],float_str3[32];
            sprintf(int_str1,"%d",filter_opt);
            sprintf(float_str2,"%f",saturation_fact);
            sprintf(float_str3,"%f",threshold_bina);
            char* argv[] = {"./worker",int_str1,float_str2,float_str3,NULL};
            execv(argv[0],argv);    
            exit(EXIT_FAILURE);

        } else { 

            // Enviar la imagen al hijo
            write(fd[1], &imageSplit[i]->width, sizeof(int));
            write(fd[1], &imageSplit[i]->height, sizeof(int));
            write(fd[1], &imageSplit[i]->type, sizeof(int));
            pixel_data_size = imageSplit[i]->width * imageSplit[i]->height * sizeof(RGBPixel);
            write(fd[1], imageSplit[i]->data, pixel_data_size);
            close(fd[1]);
                
            BMPImage *processed_image = (BMPImage*)malloc(sizeof(BMPImage));
            processed_image->name = imageSplit[i]->name;
            processed_image->width = imageSplit[i]->width;
            processed_image->height = imageSplit[i]->height;
            processed_image->type = imageSplit[i]->type;
            // Reservar memoria para los píxeles de la imagen procesada
            processed_image->data = (RGBPixel *)malloc(pixel_data_size);

            // Leer los píxeles de la imagen procesada
            read(fd2[0], processed_image->data, pixel_data_size);
            close(fd2[0]);

            imageSplit[i] = processed_image;
        }

    }

    return imageSplit;

}