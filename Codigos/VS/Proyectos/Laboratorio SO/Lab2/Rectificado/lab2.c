#include "fbroker.h"

int main(int argc, char *argv[]) { 
    
    char* prefix; // Prefijo de las imágenes
    int filters,option,workers,ob1,ob2,ob3,ob4; 
    float saturation = 0.0;  
    float thresholdbina= 0.0;
    float thresholdclass = 0.0;
    char *foldername;
    char *csvname;

    while((option = getopt(argc, argv, "N:f:p:u:v:C:R:W")) != -1){ // Ciclo para leer las opciones ingresadas por el usuario

        switch(option){

            case 'N': // Opción para ingresar el prefijo de las imágenes
            
                prefix = (char*)malloc(strlen(optarg) + 1); // Asignación de memoria para prefix
                if(prefix != NULL) {
                    strcpy(prefix, optarg);
                    ob1 = 1;
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
                ob2 = 1;
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
                ob3 = 1;
                optind++; // Incrementa optind para pasar al siguiente argumento
                break;

            case 'W':

                workers = atoi(optarg);
                break;
        
        }
    
    }
   
    if(ob1 == 0){ // Verificar si se ingresó el prefijo de las imágenes

        printf("Se debe ingresar un prefijo de imagen\n");
        return 1;
    
    }

    if(ob2 == 0){ // Verificar si se ingresó el nombre del directorio

        printf("Se debe ingresar un nombre de directorio para imagenes\n");
        return 1;
        
    }

    if(ob3 == 0){   // Verificar si se ingresó el nombre del archivo csv

        printf("Se debe ingresar un nombre de csv");
        return 1;

    }
    
    if(ob4 == 0){

        printf("Se debe ingresar la cantidad de workers");
        return 1;
    }

    if( filters == 0){ // Verificar si se ingresó el número de filtro a aplicar

        filters = 3; // Si no se ingresa un número de filtro, se aplican los tres filtros
    }

    if(saturation == 0.0){ // Verificar si se ingresó el valor de saturación

        saturation = 1.3; // Si no se ingresa un valor de saturación, se aplica el valor por defecto
    }

    if(thresholdbina == 0.0){ // Verificar si se ingresó el umbral de binarización

        thresholdbina = 0.5; // Si no se ingresa un umbral de binarización, se aplica el valor por defecto

    } else if (thresholdbina < 0 || thresholdbina > 1){ // Verificar si el umbral de binarización está entre 0 y 1

        printf("El umbral de binarizacion debe estar entre 0 y 1");
        return 1;
    }

    if(thresholdclass == 0.0){ // Verificar si se ingresó el umbral de clasificación

        thresholdclass = 0.5; // Si no se ingresa un umbral de clasificación, se aplica el valor por defecto

    } else if (thresholdclass < 0 || thresholdclass > 1){ // Verificar si el umbral de clasificación está entre 0 y 1

        printf("El umbral de clasificacion debe estar entre 0 y 1");
        return 1;
    }

    int pid = fork();
    if(pid == 0){

        char flag1="-N ",flag2="-f ",flag3="-p ",flag4="-u ",flag5="-W";
        char arg1[2],arg2[3],arg3[4],arg4[4];
        strcat(flag1,prefix);
        sprintf(arg1,"%d",filters);
        strcat(flag2,arg1);
        sprintf(arg2,"%d",workers);
        strcat(flag3,arg2);
        sprintf(arg3,"%d",saturation);
        strcat(flag4,arg3);
        sprintf(arg4,"%d",thresholdbina);
        strcat(flag5,arg4);
        char* argv[] = {"./broker",flag1,flag2,flag3,flag4,flag5,NULL};
        execv(argv[0],argv);
        return;

    } else {
        
        csvname= strcat(csvname,".csv"); // Agregar la extensión .csv al nombre del archivo csv
        int i = 0;
        new_folder(foldername); // Crear el directorio donde se guardarán las imágenes
        new_csv(csvname); // Crear el archivo csv
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

            if(filters == 1){ // Aplicar el filtro de saturación

                char *saturatedname = strcat(prefix, "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
                classify(image,thresholdclass);
                write_csv(image,csvname); // Escribir en el archivo csv
                move_file(saturatedname,foldername); // Mover el archivo de la imagen saturada al directorio especificado
            
            }

            if(filters == 2){ // Aplicar el filtro de escala de grises

                char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
                move_file(saturatedname,foldername); // Mover el archivo de la imagen saturada al directorio especificado
                char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
                classify(image,thresholdclass); // Clasificar la imagen
                write_csv(image,csvname);
                move_file(grayname,foldername); // Mover el archivo de la imagen en escala de grises al directorio especificado
           
            }

            if (filters == 3) { // Aplicar los tres filtros
        
                char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
                move_file(saturatedname, foldername);
                char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
                move_file(grayname, foldername); // Mover el archivo de la imagen en escala de grises al directorio especificado
                char *binarname = strcat(strcpy(filename_copy, filename), "_binarization.bmp"); 
                classify(image, thresholdclass);
                write_csv(image, csvname);
                move_file(binarname, foldername);
            }

            free_bmp(image); // Liberar la memoria de la imagen original
            *filenames++; // Mover el puntero al siguiente nombre de archivo
        }

    }
    
    return 0;
}