#include "fbroker.h"

int main(int argc, char *argv[]){

    sem_t *mutex_main = sem_open("/mutex_main", 0); // No se crea, solo se abre
    if (mutex_main == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    char* prefix; // Prefijo de las imágenes
    int filters = 3,option,workers; 
    float saturation = 1.3;  
    float thresholdbina= 0.5;
    float thresholdclass = 0.5;
    char *foldername;
    char *csvname;

    while((option = getopt(argc, argv, "N:f:p:u:v:C:R:W")) != -1){ // Ciclo para leer las opciones ingresadas por el usuario

        switch(option){

            case 'N': // Opción para ingresar el prefijo de las imágenes

                prefix = (char*)malloc(strlen(optarg) + 1); // Asignación de memoria para prefix
                if(prefix != NULL) {
                    strcpy(prefix, optarg);
                } else {
                    // Manejo de error si malloc falla en asignar memoria
                    printf("Error: No se pudo asignar memoria para prefix\n");
                    exit(EXIT_FAILURE);
                }
            
            case 'f': // Opción para ingresar el número de filtro a aplicar
            
                filters = atoi(optarg);
                break;
            
            case 'p': // Opción para ingresar el valor de saturación    
            
                saturation = atof(optarg);
                break;
            
            case 'u': // Opción para ingresar el umbral de binarización
            
                thresholdbina = atof(optarg);
                break;
            
            case 'v': // Opción para ingresar el umbral de clasificación
            
                thresholdclass = atof(optarg);
                break;
            
            case 'C': // Opción para ingresar el nombre del directorio donde se guardarán las imágenes

                foldername = malloc(strlen(optarg) + 1); // Asignar memoria dinámica
                if (foldername == NULL) {
                    fprintf(stderr, "Error: No se pudo asignar memoria.\n");
                    return EXIT_FAILURE;
                }
                strcpy(foldername, optarg); // Copiar el nombre del directorio
                break;
            
            case 'R': // Opción para ingresar el nombre del archivo csv

                if (optind >= argc || argv[optind][0] == '-') {
                    fprintf(stderr, "Error: Falta el argumento para la opción '-R' o el argumento está malformado\n");
                    return EXIT_FAILURE;
                }
                csvname = malloc(strlen(argv[optind]) + 1); // Asignar memoria dinámica
                if (csvname == NULL) {
                    fprintf(stderr, "Error: No se pudo asignar memoria.\n");
                    return EXIT_FAILURE;
                }
                strcpy(csvname, argv[optind]);
                optind++; // Incrementa optind para pasar al siguiente argumento
                break;

            case 'W':

                workers = atoi(optarg);
                break;
        
        }
    
    }

    char** filenames = file_names(prefix); // Obtener los nombres de los archivos con el prefijo especificado
        
    if (filenames == NULL || *filenames == NULL) {
        printf("Error: No se encontraron archivos con el prefijo especificado.\n");
        return 1;
    }
    
    while(*filenames != NULL){
        
        char* filename = *filenames;
        BMPImage* image = read_bmp(filename); // Leer la imagen
        char filename_copy[strlen(filename) + 1]; // Crear una copia del nombre de archivo
        strcpy(filename_copy, filename); // Copiar el nombre de archivo
       
        if (!image) {
            printf("Error: No se pudo leer la imagen %s\n", filename);
            return 1;
        }

            //Aqui el broker deberia separar la imagen en partes y enviarlas a los workers

        if(filters == 1){ // Aplicar el filtro de saturación

            BMPImage** imageSplit1 = (BMPImage**)malloc(sizeof(BMPImage*) * workers);
            imageSplit1 = split_image(image, workers); // Dividir la imagen en partes
            imageSplit1 = send_and_receive(imageSplit1,workers,1,saturation,thresholdbina);
            BMPImage* imageRestored1 = reassemble_image(imageSplit1,workers);//Enviar , recibir y armar
            char *saturatedname = strcat(prefix, "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
            write_bmp(saturatedname,imageRestored1); // Escribir la imagen saturada en un archivo
            classify(image,thresholdclass);
            write_csv(image,csvname); // Escribir en el archivo csv
            move_file(saturatedname,foldername); // Mover el archivo de la imagen saturada al directorio especificado
            free(imageSplit1);
            free_bmp(imageRestored1);
            
        }

        if(filters == 2){ // Aplicar el filtro de escala de grises y saturacion

            BMPImage** imageSplit1 = (BMPImage**)malloc(sizeof(BMPImage*) * workers);
            BMPImage** imageSplit2 = (BMPImage**)malloc(sizeof(BMPImage*) * workers);
            imageSplit1 = send_and_receive(imageSplit1,workers,1,saturation,thresholdbina);
            imageSplit2 = send_and_receive(imageSplit1,workers,2,saturation,thresholdbina);
            BMPImage* imageRestored1 = reassemble_image(imageSplit1,workers);
            BMPImage* imageRestored2= reassemble_image(imageSplit2,workers);//Enviar , recibir y armar
            char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
            char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
            write_bmp(saturatedname,imageRestored1);
            write_bmp(grayname,imageRestored2);
            classify(image,thresholdclass); // Clasificar la imagen
            write_csv(image,csvname);
            move_file(saturatedname,foldername); // Mover el archivo de la imagen saturada al directorio especificado
            move_file(grayname,foldername); // Mover el archivo de la imagen en escala de grises al directorio especificado
            free(imageSplit1);
            free(imageSplit2);
            free_bmp(imageRestored1);
            free_bmp(imageRestored2);
           
        }

        if (filters == 3) { // Aplicar los tres filtros

            BMPImage** imageSplit1 = (BMPImage**)malloc(sizeof(BMPImage*) * workers);
            BMPImage** imageSplit2 = (BMPImage**)malloc(sizeof(BMPImage*) * workers);
            BMPImage** imageSplit3 = (BMPImage**)malloc(sizeof(BMPImage*) * workers);
            imageSplit1 = send_and_receive(imageSplit1,workers,1,saturation,thresholdbina);
            imageSplit2 = send_and_receive(imageSplit1,workers,2,saturation,thresholdbina);
            imageSplit3 = send_and_receive(imageSplit1,workers,3,saturation,thresholdbina);
            BMPImage* imageRestored1 = reassemble_image(imageSplit1,workers);
            BMPImage* imageRestored2= reassemble_image(imageSplit2,workers);
            BMPImage* imageRestored3 = reassemble_image(imageSplit3,workers);//Enviar , recibir y armar
            char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
            char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
            char *binarname = strcat(strcpy(filename_copy, filename), "_binarization.bmp"); 
            write_bmp(saturatedname,imageRestored1);
            write_bmp(grayname,imageRestored2);
            write_bmp(binarname,imageRestored3);
            classify(image, thresholdclass);
            write_csv(image, csvname);
            move_file(saturatedname, foldername);
            move_file(binarname, foldername);
            move_file(grayname, foldername); // Mover el archivo de la imagen en escala de grises al directorio especificado
            free(imageSplit1);
            free(imageSplit2);
            free(imageSplit3);
            free_bmp(imageRestored1);
            free_bmp(imageRestored2);
            free_bmp(imageRestored3);
        }

        free_bmp(image); // Liberar la memoria de la imagen original
        *filenames++; // Mover el puntero al siguiente nombre de archivo
    }

    free(prefix); // Liberar la memoria de prefix
    free(foldername); // Liberar la memoria de foldername
    free(csvname); // Liberar la memoria de csvname
    sem_post(mutex_main);

    return 0;
}