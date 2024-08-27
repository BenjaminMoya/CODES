#include "funciones.h"

int main(int argc, char *argv[]) { 
    
    int num_filters = 3;
    int opt_option;
    float security;
    float saturation_fact = 1.3;  
    float threshold_bina= 0.5;
    float threshold_class = 0.5;
    char exe_option;
    char* img_prefix = NULL;
    char* folder_name = NULL;
    char* csv_name = NULL;
    
    while((opt_option = getopt(argc, argv, "N:f:p:u:v:C:R:W:")) != -1){ // Ciclo para leer las opciones ingresadas por el usuario

        switch(opt_option){

            case 'N': // Opción para ingresar el prefijo de las imágenes
            
                img_prefix = optarg;
                break;
            
            case 'f': // Opción para ingresar el número de filtro a aplicar
                
                if(optarg == NULL){
                    break;
                }
                security = atof(optarg);
                num_filters = atoi(optarg);
                if(security != num_filters){
                    printf("El número de filtro debe ser un número entero");
                    return 0;
                }
                break;
            
            case 'p': // Opción para ingresar el valor de saturación    

                if(optarg == NULL){
                    break;
                }
                saturation_fact = atof(optarg);
                break;
            
            case 'u': // Opción para ingresar el umbral de binarización

                if(optarg == NULL){
                    break;
                }
                threshold_bina = atof(optarg);
                break;
            
            case 'v': // Opción para ingresar el umbral de clasificación

                if(optarg == NULL){
                    break;
                }
                threshold_class = atof(optarg);
                break;
            
            case 'C': // Opción para ingresar el nombre del directorio donde se guardarán las imágenes
           
                folder_name = optarg;
                break;
            
            case 'R': // Opción para ingresar el nombre del archivo csv

                csv_name = optarg;
                break;
        
        }
    
    }
    
    if(num_filters < 1 || num_filters > 3){ // Verificar si el número de filtro está entre 1 y 3

        printf("El número de filtro debe estar entre 1 y 3");
        return 1;
    } 

    if (saturation_fact < 0){ // Verificar si el valor de saturación es mayor a 0

        printf("El valor de saturacion debe ser mayor a 0");
        return 1;
    }
    
    if (threshold_bina <= 0 || threshold_bina >= 1){ // Verificar si el umbral de binarización está entre 0 y 1

        printf("El umbral de binarizacion debe estar entre 0 y 1");
        return 1;
    }

    if (threshold_class <= 0 || threshold_class >= 1){ // Verificar si el umbral de clasificación está entre 0 y 1

        printf("El umbral de clasificacion debe estar entre 0 y 1");
        return 1;
    }

    if(csv_name == NULL){ // Verificar si se ingresó el nombre del archivo csv

        printf("No se ingreso el nombre del archivo csv");
        return 1;
    }
    
    if(folder_name == NULL){ // Verificar si se ingresó el nombre del directorio

        printf("No se ingreso el nombre del directorio");
        return 1;
    }
   
    csv_name= strcat(csv_name,".csv"); // Agregar la extensión .csv al nombre del archivo csv
    int i = 0;
    new_folder(folder_name); // Crear el directorio donde se guardarán las imágenes
    new_csv(csv_name); // Crear el archivo csv
    char** filenames_arr = file_names(img_prefix); // Obtener los nombres de los archivos con el prefijo especificado
    
    if (filenames_arr == NULL || *filenames_arr == NULL) {
        printf("Error: No se encontraron archivos con el prefijo especificado.\n");
        return 1;
    }
    
    while(*filenames_arr != NULL){
        
        char* filename = *filenames_arr;
        BMPImage* image = read_bmp(filename); // Leer la imagen

        if (!image) {
            printf("Error: No se pudo leer la imagen %s\n", filename);
            return 1;
        }

        if(num_filters == 1){ // Aplicar el filtro de saturación

            BMPImage* saturated_img = saturate_bmp(image, saturation_fact); // Aplicar el filtro de saturación
            char saturated_name[100] = "saturated_";
            strncat(saturated_name,filename, sizeof(saturated_name) - strlen(saturated_name) - 1);// Crear el nombre del archivo de la imagen saturada
            write_bmp(saturated_name, saturated_img); // Escribir la imagen saturada
            classify(image,threshold_class);
            write_csv(image,csv_name); // Escribir en el archivo csv
            classify(saturated_img,threshold_class);
            write_csv(saturated_img,csv_name);
            move_file(saturated_name,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
            free_bmp(saturated_img); // Liberar la memoria de la imagen saturada
            
        }

        if(num_filters == 2){ // Aplicar el filtro de saturacion y escala de grises

            BMPImage* saturated_img = saturate_bmp(image, saturation_fact); // Aplicar el filtro de saturación
            char saturated_name[100] = "saturated_";
            strncat(saturated_name,filename, sizeof(saturated_name) - strlen(saturated_name) - 1);// Crear el nombre del archivo de la imagen saturada
            write_bmp(saturated_name, saturated_img);
            classify(saturated_img,threshold_class);
            write_csv(saturated_img,csv_name);
            move_file(saturated_name,folder_name); // Mover el archivo de la imagen saturada al directorio especificado

            BMPImage* gray_img = grayscale_bmp(image); // Aplicar el filtro de escala de grises
            char gray_name[100] = "grayscale_";
            strncat(gray_name,filename, sizeof(gray_name) - strlen(gray_name) - 1);
            write_bmp(gray_name, gray_img); // Escribir la imagen en escala de grises
            classify(gray_img,threshold_class); // Clasificar la imagen
            write_csv(gray_img,csv_name);
            classify(image,threshold_class); // Clasificar la imagen
            write_csv(image,csv_name);
            move_file(gray_name,folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
            free_bmp(saturated_img);
            free_bmp(gray_img);
           
        }

        if (num_filters == 3) { // Aplicar los tres filtros
        
            BMPImage* saturated_img = saturate_bmp(image, saturation_fact); // Aplicar el filtro de saturación
            char saturated_name[100] = "saturated_";
            strncat(saturated_name,filename, sizeof(saturated_name) - strlen(saturated_name) - 1); // Crear el nombre del archivo de la imagen saturada
            write_bmp(saturated_name, saturated_img);
            classify(saturated_img,threshold_class);
            write_csv(saturated_img,csv_name);
            move_file(saturated_name, folder_name);

            BMPImage* gray_img = grayscale_bmp(image); // Aplicar el filtro de escala de grises
            char gray_name[100] = "grayscale_";
            strncat(gray_name,filename, sizeof(gray_name) - strlen(gray_name) - 1); // Crear el nombre del archivo de la imagen en escala de grises
            write_bmp(gray_name, gray_img);
            classify(gray_img,threshold_class); // Clasificar la imagen
            write_csv(gray_img,csv_name);
            move_file(gray_name, folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado

            BMPImage* binar_img = binarization_bmp(image, threshold_bina); // Aplicar el filtro de binarización
            char binar_name[100] = "binarization_"; 
            strncat(binar_name,filename, sizeof(binar_name) - strlen(binar_name) - 1); // Crear el nombre del archivo de la imagen binarizada
            write_bmp(binar_name, binar_img);
            classify(binar_img,threshold_class); // Clasificar la imagen
            write_csv(binar_img,csv_name);
            classify(image, threshold_class);
            write_csv(image, csv_name);
            move_file(binar_name, folder_name); // Mover el archivo de la imagen binarizada al directorio especificado
            free_bmp(saturated_img);
            free_bmp(gray_img);
            free_bmp(binar_img);
 
        }

        free_bmp(image); // Liberar la memoria de la imagen original
        *filenames_arr++; // Mover el puntero al siguiente nombre de archivo
    }
    
    return 0;
}
