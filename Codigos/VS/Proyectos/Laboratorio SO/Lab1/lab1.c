#include "funciones.h"

int main(int argc, char *argv[]) { 
    
    char prefix[10]; // Prefijo de las imágenes
    int filters,option,ob1,ob2,ob3; 
    float saturation = 0.0;  
    float thresholdbina= 0.0;
    float thresholdclass = 0.0;
    char *foldername;
    char *csvname;
    
    while((option = getopt(argc, argv, "N:f:p:u:v:C:R")) != -1){ // Ciclo para leer las opciones ingresadas por el usuario
    switch(option){

        case 'N': // Opción para ingresar el prefijo de las imágenes
            
            strcpy(prefix, optarg);
            ob1 = 1;
            break;
            
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

            BMPImage* saturated = saturate_bmp(image, saturation); // Aplicar el filtro de saturación
            char *saturatedname = strcat(prefix, "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
            write_bmp(saturatedname, saturated); // Escribir la imagen saturada
            classify(image,thresholdclass);
            write_csv(image,csvname); // Escribir en el archivo csv
            move_file(saturatedname,foldername); // Mover el archivo de la imagen saturada al directorio especificado
            free_bmp(saturated); // Liberar la memoria de la imagen saturada
            
        }

        if(filters == 2){ // Aplicar el filtro de escala de grises

            BMPImage* saturated = saturate_bmp(image, saturation); // Aplicar el filtro de saturación
            char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
            write_bmp(saturatedname, saturated);
            move_file(saturatedname,foldername); // Mover el archivo de la imagen saturada al directorio especificado
            BMPImage* gray = grayscale(image); // Aplicar el filtro de escala de grises
            char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
            write_bmp(grayname, gray); // Escribir la imagen en escala de grises
            classify(image,thresholdclass); // Clasificar la imagen
            write_csv(image,csvname);
            move_file(grayname,foldername); // Mover el archivo de la imagen en escala de grises al directorio especificado
            free_bmp(saturated);
            free_bmp(gray);
           
           
           
        }
    if (filters == 3) { // Aplicar los tres filtros
        
        BMPImage* saturated = saturate_bmp(image, saturation); // Aplicar el filtro de saturación
        // Usar una copia del nombre de archivo original
        char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
        write_bmp(saturatedname, saturated);
        move_file(saturatedname, foldername);
        BMPImage* gray = grayscale(image); // Aplicar el filtro de escala de grises
        // Usar una copia del nombre de archivo original
        char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
        write_bmp(grayname, gray);
        move_file(grayname, foldername); // Mover el archivo de la imagen en escala de grises al directorio especificado
        BMPImage* binar = binarization(image, thresholdbina); // Aplicar el filtro de binarización
        // Usar una copia del nombre de archivo original
        char *binarname = strcat(strcpy(filename_copy, filename), "_binarization.bmp"); 
        write_bmp(binarname, binar);
        classify(image, thresholdclass);
        write_csv(image, csvname);
        move_file(binarname, foldername);
            
            
            
            
        }

        free_bmp(image); // Liberar la memoria de la imagen original
        *filenames++; // Mover el puntero al siguiente nombre de archivo
    }
    
    return 0;
}
