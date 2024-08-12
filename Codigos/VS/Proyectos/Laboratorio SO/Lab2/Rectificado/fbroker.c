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

BMPImage** divide_image(BMPImage *image, int workers){
    int columns_per_worker = image->width / workers;
    int remainder_columns = image->width % workers;
    BMPImage** sub_images;

    for (int i = 0; i < workers; i++) {
        sub_images[i] = (BMPImage*)malloc(sizeof(BMPImage));
        sub_images[i]->width = columns_per_worker + (i < remainder_columns ? 1 : 0);
        sub_images[i]->height = image->height;
        sub_images[i]->data = (RGBPixel*)malloc(sub_images[i]->width * image->height * sizeof(RGBPixel));

        int offset = i * columns_per_worker + (i < remainder_columns ? i : remainder_columns);
        for (int y = 0; y < image->height; y++) {
            memcpy(&sub_images[i]->data[y * sub_images[i]->width], 
                   &image->data[y * image->width + offset], 
                   sub_images[i]->width * sizeof(RGBPixel));
        }
    }

    return sub_images;
}

BMPImage* reassemble_image(BMPImage **sub_images, int num_workers) {
    int total_width = 0;
    int height = sub_images[0]->height;
    for (int i = 0; i < num_workers; i++) {
        total_width += sub_images[i]->width;
    }

    BMPImage *full_image = (BMPImage*)malloc(sizeof(BMPImage));
    full_image->width = total_width;
    full_image->height = height;
    full_image->data = (RGBPixel*)malloc(total_width * height * sizeof(RGBPixel));

    int offset = 0;
    for (int i = 0; i < num_workers; i++) {
        for (int y = 0; y < height; y++) {
            memcpy(&full_image->data[y * total_width + offset], 
                   &sub_images[i]->data[y * sub_images[i]->width], 
                   sub_images[i]->width * sizeof(RGBPixel));
        }
        offset += sub_images[i]->width;
    }

    return full_image;
}

BMPImage** send_and_receive(BMPImage** imageSplit, int workers, int filter, float saturation, float thresholdbina){

    sem_t *mutex_broker = sem_open("/mutex_broker", O_CREAT | O_EXCL, 0644, 0);
    if (mutex_broker == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    sem_t *mutex_worker = sem_open("/mutex_worker", O_CREAT | O_EXCL, 0644, 0);
    if (mutex_worker == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    int pipe_parent_to_child[2];
    int pipe_child_to_parent[2];

    close(pipe_parent_to_child[1]); // No se usa el descriptor de escritura hacia el padre
    close(pipe_child_to_parent[0]); // No se usa el descriptor de lectura hacia el padre

    for (int i = 0; i < workers; i++) {
        // Crear pipes
        if (pipe(pipe_parent_to_child) == -1 || pipe(pipe_child_to_parent) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        
        if (pid == 0) { // Proceso hijo

            close(pipe_parent_to_child[1]); // No se usa el descriptor de escritura hacia el padre
            close(pipe_child_to_parent[0]); // No se usa el descriptor de lectura desde el padre
            // Redirigir stdin y stdout
            dup2(pipe_parent_to_child[0], STDIN_FILENO);  // Redirige stdin del hijo al pipe de entrada
            dup2(pipe_child_to_parent[1], STDOUT_FILENO); // Redirige stdout del hijo al pipe de salida

            //Ejecutar el programa deseado
            char flag1[]="-f ",flag2[]="-p ",flag3[]="-u ";
            char float_str1[32],float_str2[32],float_str3[32];
            sprintf(float_str1,"%d",filter);
            sprintf(float_str2,"%f",saturation);
            sprintf(float_str3,"%f",thresholdbina);
            strcat(flag1,float_str1);
            strcat(flag2,float_str2);
            strcat(flag3,float_str3);
            char* argv[] = {"./worker",flag1,flag2,flag3,NULL};
            execv(argv[0],argv);
            exit(0);

        } else { // Proceso padre tiene que esperar a que termine el hijo para buscar en el pipe lo que hizo el hijo

            close(pipe_parent_to_child[0]); // No se usa el descriptor de lectura desde el hijo
            close(pipe_child_to_parent[1]); // No se usa el descriptor de escritura hacia el hijo

            // Enviar datos al hijo
            ssize_t bytes_written = write(pipe_child_to_parent[1], imageSplit[i], sizeof(imageSplit[i]));
            if (bytes_written != sizeof(imageSplit[i])) {
                perror("write");
                exit(EXIT_FAILURE);
            }
            bytes_written = write(pipe_child_to_parent[1], imageSplit[i]->data, imageSplit[i]->width * imageSplit[i]->height * sizeof(RGBPixel));
            if (bytes_written != imageSplit[i]->width * imageSplit[i]->height * sizeof(RGBPixel)) {
                perror("write");
                exit(EXIT_FAILURE);
            }
            sem_post(mutex_worker); //Le avisa al worker que ya puede empezar a trabajar
            sem_wait(mutex_broker); //Espera a que el worker termine su ejecucion

            //Leer y guardar la imagen procesada
            imageSplit[i]->data = malloc(imageSplit[i]->width * imageSplit[i]->height * sizeof(RGBPixel));
            if (imageSplit[i]->data == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            ssize_t bytes_read = read(pipe_parent_to_child[0], imageSplit[i], sizeof(imageSplit[i]));
            if (bytes_read != sizeof(imageSplit[i])) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            bytes_read = read(pipe_parent_to_child[0], imageSplit[i]->data, imageSplit[i]->width * imageSplit[i]->height * sizeof(RGBPixel));
            if (bytes_read != imageSplit[i]->width * imageSplit[i]->height * sizeof(RGBPixel)) {
                perror("read");
                exit(EXIT_FAILURE);
            }

            close(pipe_child_to_parent[1]);
            close(pipe_parent_to_child[0]);
        }
    }
}