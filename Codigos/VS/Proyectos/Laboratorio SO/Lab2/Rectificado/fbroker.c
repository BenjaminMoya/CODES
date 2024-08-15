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
    int width_per_worker = image->width / num_workers;
    int remaining_width = image->width % num_workers;

    BMPImage **subimages = malloc(num_workers * sizeof(BMPImage*));
    for (int i = 0; i < num_workers; i++) {
        int start_col = i * width_per_worker;
        int end_col = (i + 1) * width_per_worker;

        if (i == num_workers - 1) {
            // Último worker recibe las columnas adicionales si existen
            end_col += remaining_width;
        }

        int subimage_width = end_col - start_col;

        // Crear la subimagen para este worker
        BMPImage *subimage = malloc(sizeof(BMPImage));
        subimage->name = image->name; // O asignar un nombre único
        subimage->width = subimage_width;
        subimage->height = image->height;
        subimage->type = image->type;
        subimage->data = malloc(subimage_width * image->height * sizeof(RGBPixel));

        // Copiar los datos de la imagen original a la subimagen
        for (int y = 0; y < image->height; y++) {
            for (int x = 0; x < subimage_width; x++) {
                subimage->data[y * subimage_width + x] = image->data[y * image->width + (start_col + x)];
            }
        }

        subimages[i] = subimage;
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


BMPImage* reassemble_image(BMPImage **subimages, int num_workers) {
    if (num_workers < 1) {
        return NULL;
    }

    // Calcular el ancho total de la imagen original
    int total_width = 0;
    int height = subimages[0]->height;  // Todas las subimágenes tienen la misma altura

    for (int i = 0; i < num_workers; i++) {
        total_width += subimages[i]->width;
    }

    // Crear la imagen restaurada
    BMPImage *restored_image = malloc(sizeof(BMPImage));
    restored_image->name = "Restored Image";  // O asignar un nombre adecuado
    restored_image->width = total_width;
    restored_image->height = height;
    restored_image->type = subimages[0]->type;  // Se asume que todas las subimágenes tienen el mismo tipo
    restored_image->data = malloc(total_width * height * sizeof(RGBPixel));

    // Copiar los datos de las subimágenes a la imagen restaurada
    int current_col = 0;
    for (int i = 0; i < num_workers; i++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < subimages[i]->width; x++) {
                restored_image->data[y * total_width + (current_col + x)] = subimages[i]->data[y * subimages[i]->width + x];
            }
        }
        current_col += subimages[i]->width;
    }

    return restored_image;
}

BMPImage** send_and_receive(BMPImage** imageSplit, int num_workers, int filter_opt, float saturation_fact, float threshold_bina){
    
    int fd[2];  
    int fd2[2];
    pid_t pid;
    size_t pixel_data_size;

    for (int i = 0; i < num_workers; i++){ // crear hijos

        if (pipe(fd) == -1 || pipe(fd2) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        printf("Pipe creado\n");
        pid = fork();
        if(pid == -1){

            printf("Error");
            exit(EXIT_FAILURE);

        } else if (pid == 0){ // si es el proceso hijo
            printf("Proceso hijo\n");
            // Cerrar extremos no utilizados del pipe
            close(fd[1]); // Cerrar escritura del pipe principal
            close(fd2[0]); // Cerrar lectura del pipe para la salida del hijo

            // Redirigir stdin y stdout
            dup2(fd[0], STDIN_FILENO);
            dup2(fd2[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd2[1]);

            char int_str1[32],float_str2[32],float_str3[32];
            sprintf(int_str1,"%d",filter_opt);
            sprintf(float_str2,"%f",saturation_fact);
            sprintf(float_str3,"%f",threshold_bina);
            char* argv[] = {"./worker",int_str1,float_str2,float_str3,NULL};
            printf("Ejecutando worker\n");
            execv(argv[0],argv);    
            printf("Error en la ejecucion del worker"); // si hay error en el execv
            exit(EXIT_FAILURE);

        } else { // Envio de la imagen por el
            printf("Proceso padre\n");
            close(fd[0]); // Cerrar lectura del pipe principal
            close(fd2[1]); // Cerrar escritura del pipe para la salida del hijo
            printf("Enviando imagen\n");
            // Enviar la imagen al hijo
            write(fd[1], &imageSplit[i]->width, sizeof(int));
            write(fd[1], &imageSplit[i]->height, sizeof(int));
            write(fd[1], &imageSplit[i]->type, sizeof(int));
            pixel_data_size = imageSplit[i]->width * imageSplit[i]->height * sizeof(RGBPixel);
            write(fd[1], imageSplit[i]->data, pixel_data_size);
            close(fd[1]); // Cerrar escritura después de enviar todos los datos
            printf("Imagen enviada\n");
            waitpid(pid, NULL, 0);
            printf("Esperando al hijo\n");
            close(fd2[1]);
            BMPImage *processed_image = malloc(sizeof(BMPImage));
            read(fd2[0], &processed_image->width, sizeof(int));
            read(fd2[0], &processed_image->height, sizeof(int));
            read(fd2[0], &processed_image->type, sizeof(int));
            printf("Leyendo imagen\n");
            // Reservar memoria para los píxeles de la imagen procesada
            pixel_data_size = processed_image->width * processed_image->height * sizeof(RGBPixel);
            processed_image->data = (RGBPixel *)malloc(pixel_data_size);

            // Leer los píxeles de la imagen procesada
            read(fd2[0], processed_image->data, pixel_data_size);
            close(fd2[0]);
            imageSplit[i] = processed_image;
            printf("Imagen asignada\n");
            free_bmp(processed_image);
        }

    }

    return imageSplit;
        
}   