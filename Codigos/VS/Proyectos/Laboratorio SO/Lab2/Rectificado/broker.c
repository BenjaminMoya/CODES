#include "fbroker.h"

int main(int argc, char *argv[]){//no se envian bien los argumentos al broker revisar

    int num_filters = atoi(argv[2]);
    int num_workers = atoi(argv[6]);
    float saturation_fact = atof(argv[3]);  
    float threshold_bina= atof(argv[4]);
    float threshold_class = atof(argv[5]);
    char* img_prefix = argv[1]; // Obtener el prefijo de los archivos
    char *folder_name = argv[7]; // Obtener el nombre del directorio donde se guardarán las imágenes
    char *csv_name = argv[8]; // Obtener el nombre del archivo csv

    char** filenames = file_names(img_prefix); // Obtener los nombres de los archivos con el prefijo especificado
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

        if(num_filters == 1){ // Aplicar el filtro de saturación
            printf("Aplicando filtro de saturación a la imagen %s\n", filename);
            BMPImage **imageSplit1 = split_image(image, num_workers);
            printf("Imagen dividida\n");
            imageSplit1 = send_and_receive(imageSplit1,num_workers,1,saturation_fact,threshold_bina);
            printf("Imagen enviada y recibida\n");
            BMPImage* imageRestored1 = reassemble_image(imageSplit1,num_filters);//Enviar , recibir y armar
            char *saturatedname = strcat(img_prefix, "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
            write_bmp(saturatedname,imageRestored1); // Escribir la imagen saturada en un archivo
            classify(image,threshold_class);
            write_csv(image,csv_name); // Escribir en el archivo csv
            move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
            free(imageSplit1);
            free_bmp(imageRestored1);
        }

        if(num_filters == 2){ // Aplicar el filtro de escala de grises y saturacion

            BMPImage** imageSplit1 = split_image(image, num_workers);
            BMPImage** imageSplit2 = split_image(image, num_workers);
            imageSplit1 = send_and_receive(imageSplit1,num_workers,1,saturation_fact,threshold_bina);
            imageSplit2 = send_and_receive(imageSplit2,num_workers,2,saturation_fact,threshold_bina);
            BMPImage* imageRestored1 = reassemble_image(imageSplit1,num_workers);
            BMPImage* imageRestored2= reassemble_image(imageSplit2,num_workers);//Enviar , recibir y armar
            char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
            char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
            write_bmp(saturatedname,imageRestored1);
            write_bmp(grayname,imageRestored2);
            classify(image,threshold_class); // Clasificar la imagen
            write_csv(image,csv_name);
            move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
            move_file(grayname,folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
            free(imageSplit1);
            free(imageSplit2);
            free_bmp(imageRestored1);
            free_bmp(imageRestored2);
           
        }

        if (num_filters == 3) { // Aplicar los tres filtros

            BMPImage** imageSplit1 = split_image(image, num_workers);
            BMPImage** imageSplit2 = split_image(image, num_workers);
            BMPImage** imageSplit3 = split_image(image, num_workers);
            imageSplit1 = send_and_receive(imageSplit1,num_workers,1,saturation_fact,threshold_bina);
            imageSplit2 = send_and_receive(imageSplit2,num_workers,2,saturation_fact,threshold_bina);
            imageSplit3 = send_and_receive(imageSplit3,num_workers,3,saturation_fact,threshold_bina);
            BMPImage* imageRestored1 = reassemble_image(imageSplit1,num_workers);
            BMPImage* imageRestored2= reassemble_image(imageSplit2,num_workers);
            BMPImage* imageRestored3 = reassemble_image(imageSplit3,num_workers);//Enviar , recibir y armar
            char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
            char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
            char *binarname = strcat(strcpy(filename_copy, filename), "_binarization.bmp"); 
            write_bmp(saturatedname,imageRestored1);
            write_bmp(grayname,imageRestored2);
            write_bmp(binarname,imageRestored3);
            classify(image, threshold_class);
            write_csv(image, csv_name);
            move_file(saturatedname, folder_name);
            move_file(binarname, folder_name);
            move_file(grayname, folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
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

    return 0;
}