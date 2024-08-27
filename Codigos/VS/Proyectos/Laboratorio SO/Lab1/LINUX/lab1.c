#include "funciones.h"

int main(int argc, char *argv[]) { 
    
    int num_filters = 3;
    int opt_option;
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
                num_filters = atoi(optarg);
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
                strcat(csv_name, ".csv");
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
    
    new_folder(folder_name); // Crear el directorio donde se guardarán las imágenes
    new_csv(csv_name); // Crear el archivo csv
    char** filenames = file_names(img_prefix); // Obtener los nombres de los archivos con el prefijo especificado
    
    if (filenames == NULL || *filenames == NULL) {
        printf("Error: No se encontraron archivos con el prefijo especificado.\n");
        return 1;
    }
    
    while(*filenames != NULL){
        
        char* filename = *filenames;
        BMPImage* image = read_bmp(filename); // Leer la imagen
       
        if (!image) {
            printf("Error: No se pudo leer la imagen %s\n", filename);
            return 1;
        }

        if(num_filters == 1){ // Aplicar el filtro de saturación

            BMPImage* saturated_img = saturate_bmp(image, saturation_fact); // Aplicar el filtro de saturación
            char *saturatedname = strcat("saturated_",filename); // Crear el nombre del archivo de la imagen saturada
            write_bmp(saturatedname,saturated_img); // Escribir la imagen saturada en un archivo
            classify(image,threshold_class); // Clasificar la imagen
            write_csv(image,csv_name);// Escribir la imagen saturada en un archivo
            classify(saturated_img,threshold_class); // Clasificar la imagen
            write_csv(saturated_img,csv_name);// Escribir en el archivo csv
            move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
            free_bmp(saturated_img);
            
        }

        if(num_filters == 2){ // Aplicar el filtro de escala de grises

            BMPImage* saturated_img = saturate_bmp(image, saturation_fact); // Aplicar el filtro de saturación
            char *saturatedname = strcat("saturated_",filename); // Crear el nombre del archivo de la imagen saturada
            write_bmp(saturatedname,saturated_img); // Escribir la imagen saturada en un archivo
            classify(saturated_img,threshold_class); // Clasificar la imagen
            write_csv(saturated_img,csv_name);// Escribir en el archivo csv
            move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
            free_bmp(saturated_img);

            BMPImage* gray_img = grayscale(image); // Aplicar el filtro de escala de grises
            char *grayname = strcat("grayscale_",filename); // Crear el nombre del archivo de la imagen en escala de grises
            write_bmp(grayname,gray_img);
            classify(gray_img,threshold_class); // Clasificar la imagen
            write_csv(gray_img,csv_name);
            classify(image,threshold_class); // Clasificar la imagen
            write_csv(image,csv_name);
            move_file(grayname,folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
            free_bmp(gray_img);
           
        }

        if (num_filters == 3) { // Aplicar los tres filtros
        
            BMPImage* saturated_img = saturate_bmp(image, saturation_fact); // Aplicar el filtro de saturación
            char *saturatedname = strcat(img_prefix, "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
            write_bmp(saturatedname,saturated_img); // Escribir la imagen saturada en un archivo
            classify(saturated_img,threshold_class); // Clasificar la imagen
            write_csv(saturated_img,csv_name);// Escribir en el archivo csv
            move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
            free_bmp(saturated_img);

            BMPImage* gray_img = grayscale(image); // Aplicar el filtro de escala de grises
            char *grayname = strcat("grayscale_",filename); // Crear el nombre del archivo de la imagen en escala de grises
            write_bmp(grayname,gray_img);
            classify(gray_img,threshold_class); // Clasificar la imagen
            write_csv(gray_img,csv_name);
            move_file(grayname,folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
            free_bmp(gray_img);

            BMPImage* binar_img = binarization(image,threshold_bina); // Aplicar el filtro de binarización
            char *binarname = strcat("binarization_",filename); // Crear el nombre del archivo de la imagen en escala de grises
            write_bmp(grayname,binar_img);
            classify(binar_img,threshold_class); // Clasificar la imagen
            write_csv(binar_img,csv_name);
            classify(image,threshold_class); // Clasificar la imagen
            write_csv(image,csv_name);
            move_file(grayname,folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
            free_bmp(binar_img);
 
        }

        free_bmp(image); // Liberar la memoria de la imagen original
        *filenames++; // Mover el puntero al siguiente nombre de archivo
    }
    
    return 0;
}
