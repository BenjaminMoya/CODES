#include "fbroker.h"

int main(int argc, char *argv[]){
    
    int num_filters = atoi(argv[2]);// Obtener el número de filtros a aplicar
    int num_workers = atoi(argv[6]);// Obtener el número de trabajadores
    float saturation_fact = atof(argv[3]);// Obtener el factor de saturación
    float threshold_bina= atof(argv[4]);// Obtener el umbral de binarización
    float threshold_class = atof(argv[5]);// Obtener el umbral de clasificación nearly black
    char* img_prefix = argv[1]; // Obtener el prefijo de los archivos
    char *folder_name = argv[7]; // Obtener el nombre del directorio donde se guardarán las imágenes
    char *csv_name = argv[8]; // Obtener el nombre del archivo csv
    
    char** filenames = file_names(img_prefix); // Obtener los nombres de los archivos con el prefijo especificado
    if (filenames == NULL || *filenames == NULL || sizeof(filenames) == 0) {
        printf("Error: No se encontraron archivos con el prefijo especificado.\n");
        return 1;
    }

    while(*filenames != NULL){
        
        char* filename = *filenames;
        BMPImage* image1 = read_bmp(filename); // Leer la imagen
        BMPImage* image2 = read_bmp(filename); // Leer la imagen
        BMPImage* image3 = read_bmp(filename); // Leer la imagen
        char filename_copy[strlen(filename) + 1]; // Crear una copia del nombre de archivo
        strcpy(filename_copy, filename); // Copiar el nombre de archivo
        if (!image1) {
            printf("Error: No se pudo leer la imagen %s\n", filename);
            return 1;
        }
        if (!image2) {
            printf("Error: No se pudo leer la imagen %s\n", filename);
            return 1;
        }
        if (!image3) {
            printf("Error: No se pudo leer la imagen %s\n", filename);
            return 1;
        }
        
        if(num_filters == 1){ // Aplicar el filtro de saturación
            
            if((image1->height * image1->width)/num_workers >= BUFFER_SIZE){
                
                int new_amount = (int)ceil(image1->height * image1->width / BUFFER_SIZE);// Calcular la cantidad de trabajadores necesarios
                int width_per_worker = image1->width / new_amount;
                int remaining_width = image1->width % new_amount;
                BMPImage** imageSplit1 = split_image(image1, new_amount); // Dividir la imagen en subimagenes
                for(int i = 0; i < new_amount; i++){ // Asignar el ancho y alto de las subimagenes
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit1[i]->width = subimage_width;
                    imageSplit1[i]->height = image1->height;
                }
                imageSplit1 = send_and_receive(imageSplit1,new_amount,1,saturation_fact,threshold_bina);// Enviar las subimagenes a los trabajadores
                BMPImage* imageRestored1 = combine_images(imageSplit1,new_amount);// Combinar las subimagenes
                char *saturatedname = strcat(img_prefix, "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
                write_bmp(saturatedname,imageRestored1); 
                classify(image1,threshold_class); // Clasificar la imagen
                write_csv(image1,csv_name);// Escribir la imagen saturada en un archivo
                classify(imageRestored1,threshold_class); // Clasificar la imagen
                write_csv(imageRestored1,csv_name);// Escribir en el archivo csv
                move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
                free(imageSplit1);
                free_bmp(imageRestored1);

            } else {
                
                int width_per_worker = image1->width / num_workers;
                int remaining_width = image1->width % num_workers;
                BMPImage** imageSplit1 = split_image(image1, num_workers); 
                for(int i = 0; i < num_workers; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit1[i]->width = subimage_width;
                    imageSplit1[i]->height = image1->height;
                }
                imageSplit1 = send_and_receive(imageSplit1,num_workers,1,saturation_fact,threshold_bina);
                BMPImage* imageRestored1 = combine_images(imageSplit1,num_workers);
                char *saturatedname = strcat(img_prefix, "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
                write_bmp(saturatedname,imageRestored1); // Escribir la imagen saturada en un archivo
                classify(image1,threshold_class); // Clasificar la imagen
                write_csv(image1,csv_name);// Escribir la imagen saturada en un archivo
                classify(imageRestored1,threshold_class); // Clasificar la imagen
                write_csv(imageRestored1,csv_name);// Escribir en el archivo csv
                move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
                free(imageSplit1);
                free_bmp(imageRestored1);
            } 

        }
        
        if(num_filters == 2){ // Aplicar el filtro de escala de grises y saturacion
            
            if((image1->height * image1->width)/num_workers >= BUFFER_SIZE){
                
                int new_amount = (int)ceil(image1->height * image1->width / BUFFER_SIZE);
                int width_per_worker = image1->width / new_amount;
                int remaining_width = image1->width % new_amount;
                BMPImage** imageSplit1 = split_image(image1, new_amount);
                for(int i = 0; i < new_amount; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit1[i]->width = subimage_width;
                    imageSplit1[i]->height = image1->height;
                }
                imageSplit1 = send_and_receive(imageSplit1,new_amount,1,saturation_fact,threshold_bina);
                BMPImage* imageRestored1 = combine_images(imageSplit1,new_amount);
                char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
                write_bmp(saturatedname,imageRestored1);
                classify(image1,threshold_class); // Clasificar la imagen
                write_csv(image1,csv_name);// Escribir la imagen saturada en un archivo
                classify(imageRestored1,threshold_class); // Clasificar la imagen
                write_csv(imageRestored1,csv_name);// Escribir en el archivo csv
                move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
                free(imageSplit1);
                free_bmp(imageRestored1);
                
                BMPImage** imageSplit2 = split_image(image2, new_amount);
                for(int i = 0; i < new_amount; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit2[i]->width = subimage_width;
                    imageSplit2[i]->height = image1->height;
                }
                imageSplit2 = send_and_receive(imageSplit2,new_amount,2,saturation_fact,threshold_bina);
                BMPImage* imageRestored2 = combine_images(imageSplit2,new_amount);
                char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
                write_bmp(grayname,imageRestored2);
                classify(imageRestored2,threshold_class); // Clasificar la imagen
                write_csv(imageRestored2,csv_name);
                move_file(grayname,folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
                free(imageSplit2);
                free_bmp(imageRestored2);

            } else {
                
                int width_per_worker = image1->width / num_workers;
                int remaining_width = image1->width % num_workers;
                BMPImage** imageSplit1 = split_image(image1, num_workers);
                for(int i = 0; i < num_workers; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit1[i]->width = subimage_width;
                    imageSplit1[i]->height = image1->height;
                }
                imageSplit1 = send_and_receive(imageSplit1,num_workers,1,saturation_fact,threshold_bina);
                BMPImage* imageRestored1 = combine_images(imageSplit1,num_workers);
                char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
                write_bmp(saturatedname,imageRestored1);
                classify(image1,threshold_class); // Clasificar la imagen
                write_csv(image1,csv_name);// Escribir la imagen saturada en un archivo
                classify(imageRestored1,threshold_class); // Clasificar la imagen
                write_csv(imageRestored1,csv_name);// Escribir en el archivo csv
                move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
                free(imageSplit1);
                free_bmp(imageRestored1);
                
                BMPImage** imageSplit2 = split_image(image2, num_workers);
                for(int i = 0; i < num_workers; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit2[i]->width = subimage_width;
                    imageSplit2[i]->height = image1->height;
                }
                imageSplit2 = send_and_receive(imageSplit2,num_workers,2,saturation_fact,threshold_bina);
                BMPImage* imageRestored2 = combine_images(imageSplit2,num_workers);
                char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
                write_bmp(grayname,imageRestored2);
                classify(imageRestored2,threshold_class); // Clasificar la imagen
                write_csv(imageRestored2,csv_name);
                move_file(grayname,folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
                free(imageSplit2);
                free_bmp(imageRestored2);
            } 
           
        }

        if (num_filters == 3) { // Aplicar los tres filtros

            if((image1->height * image1->width)/num_workers >= BUFFER_SIZE){
                
                int new_amount = (int)ceil(image1->height * image1->width / BUFFER_SIZE);
                int width_per_worker = image1->width / new_amount;
                int remaining_width = image1->width % new_amount;
                BMPImage** imageSplit1 = split_image(image1, new_amount);
                for(int i = 0; i < new_amount; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit1[i]->width = subimage_width;
                    imageSplit1[i]->height = image1->height;
                }
                imageSplit1 = send_and_receive(imageSplit1,new_amount,1,saturation_fact,threshold_bina);
                BMPImage* imageRestored1 = combine_images(imageSplit1,new_amount);
                char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
                write_bmp(saturatedname,imageRestored1);
                classify(image1,threshold_class); // Clasificar la imagen
                write_csv(image1,csv_name);// Escribir la imagen saturada en un archivo
                classify(imageRestored1,threshold_class); // Clasificar la imagen
                write_csv(imageRestored1,csv_name);// Escribir en el archivo csv
                move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
                free(imageSplit1);
                free_bmp(imageRestored1);
                
                BMPImage** imageSplit2 = split_image(image2, new_amount);
                for(int i = 0; i < new_amount; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit2[i]->width = subimage_width;
                    imageSplit2[i]->height = image1->height;
                }
                imageSplit2 = send_and_receive(imageSplit2,new_amount,2,saturation_fact,threshold_bina);
                BMPImage* imageRestored2 = combine_images(imageSplit2,new_amount);
                char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
                write_bmp(grayname,imageRestored2);
                classify(imageRestored2,threshold_class); // Clasificar la imagen
                write_csv(imageRestored2,csv_name);
                move_file(grayname,folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
                free(imageSplit2);
                free_bmp(imageRestored2);

                BMPImage** imageSplit3 = split_image(image3, num_workers);
                for(int i = 0; i < num_workers; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit3[i]->width = subimage_width;
                    imageSplit3[i]->height = image1->height;
                }
                imageSplit3 = send_and_receive(imageSplit3,num_workers,3,saturation_fact,threshold_bina);
                BMPImage* imageRestored3 = combine_images(imageSplit3,num_workers);
                char *binarname = strcat(strcpy(filename_copy, filename), "_binarization.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
                write_bmp(grayname,imageRestored3);
                classify(imageRestored3,threshold_class); // Clasificar la imagen
                write_csv(imageRestored3,csv_name);
                move_file(grayname,folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
                free(imageSplit3);
                free_bmp(imageRestored3);

            } else {
                
                int width_per_worker = image1->width / num_workers;
                int remaining_width = image1->width % num_workers;
                BMPImage** imageSplit1 = split_image(image1, num_workers);
                for(int i = 0; i < num_workers; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit1[i]->width = subimage_width;
                    imageSplit1[i]->height = image1->height;
                }
                imageSplit1 = send_and_receive(imageSplit1,num_workers,1,saturation_fact,threshold_bina);
                BMPImage* imageRestored1 = combine_images(imageSplit1,num_workers);
                char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
                write_bmp(saturatedname,imageRestored1);
                classify(image1,threshold_class); // Clasificar la imagen
                write_csv(image1,csv_name);// Escribir la imagen saturada en un archivo
                classify(imageRestored1,threshold_class); // Clasificar la imagen
                write_csv(imageRestored1,csv_name);// Escribir en el archivo csv
                move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
                free(imageSplit1);
                free_bmp(imageRestored1);
                
                BMPImage** imageSplit2 = split_image(image2, num_workers);
                for(int i = 0; i < num_workers; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit2[i]->width = subimage_width;
                    imageSplit2[i]->height = image1->height;
                }
                imageSplit2 = send_and_receive(imageSplit2,num_workers,2,saturation_fact,threshold_bina);
                BMPImage* imageRestored2 = combine_images(imageSplit2,num_workers);
                char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
                write_bmp(grayname,imageRestored2);
                classify(imageRestored2,threshold_class); // Clasificar la imagen
                write_csv(imageRestored2,csv_name);
                move_file(grayname,folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
                free(imageSplit2);
                free_bmp(imageRestored2);

                BMPImage** imageSplit3 = split_image(image3, num_workers);
                for(int i = 0; i < num_workers; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit3[i]->width = subimage_width;
                    imageSplit3[i]->height = image1->height;
                }
                imageSplit3 = send_and_receive(imageSplit3,num_workers,3,saturation_fact,threshold_bina);
                BMPImage* imageRestored3 = combine_images(imageSplit3,num_workers);
                char *binarname = strcat(strcpy(filename_copy, filename), "_binarization.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
                write_bmp(grayname,imageRestored3);
                classify(image1,threshold_class); // Clasificar la imagen
                write_csv(image1,csv_name);
                move_file(grayname,folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
                free(imageSplit3);
                free_bmp(imageRestored3);
            }  

        }
        free_bmp(image1); // Liberar la memoria de la imagen original
        free_bmp(image2); 
        free_bmp(image3); 
        *filenames++; // Mover el puntero al siguiente nombre de archivo
    }

    return 0;
}