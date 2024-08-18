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
                printf("entro");
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
                classify(image1,threshold_class);
                write_csv(image1,csv_name); // Escribir en el archivo csv
                move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
                free_subimages(imageSplit1,num_workers);
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
                classify(image1,threshold_class);
                write_csv(image1,csv_name); // Escribir en el archivo csv
                move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
                free_subimages(imageSplit1,num_workers);
                free_bmp(imageRestored1);
            } 

        }
        /*
        if(num_filters == 2){ // Aplicar el filtro de escala de grises y saturacion
            
            if(image1->height * image1->width/num_workers > BUFFER_SIZE || image2->height * image2->width/num_workers > BUFFER_SIZE){
                
                int width_per_worker = image1->width / num_workers;
                int remaining_width = image1->width % num_workers;
                BMPImage** imageSplit1 = (BMPImage**)malloc(sizeof(BMPImage*) * (int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                BMPImage** imageSplit2 = (BMPImage**)malloc(sizeof(BMPImage*) * (int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                imageSplit1 = split_image(image1,(int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                imageSplit2 = split_image(image2,(int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                for(int i = 0; i < (int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit1[i]->width = subimage_width;
                    imageSplit1[i]->height = image1->height;
                    imageSplit2[i]->width = subimage_width;
                    imageSplit2[i]->height = image1->height;
                }
                send_and_receive(imageSplit1,num_workers,1,saturation_fact,threshold_bina,1);
                send_and_receive(imageSplit2,num_workers,2,saturation_fact,threshold_bina,1);
                BMPImage* imageRestored1 = combine_images(imageSplit1,(int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                BMPImage* imageRestored2 = combine_images(imageSplit2,(int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
                char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
                write_bmp(saturatedname,imageRestored1);
                write_bmp(grayname,imageRestored2);
                classify(image1,threshold_class); // Clasificar la imagen
                write_csv(image1,csv_name);
                move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
                move_file(grayname,folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
                free(imageSplit1);
                free(imageSplit2);
                free_bmp(imageRestored1);
                free_bmp(imageRestored2);

            } else {
                
                int width_per_worker = image1->width / num_workers;
                int remaining_width = image1->width % num_workers;
                BMPImage** imageSplit1 = (BMPImage**)malloc(sizeof(BMPImage*) * num_workers);
                BMPImage** imageSplit2 = (BMPImage**)malloc(sizeof(BMPImage*) * num_workers);
                imageSplit1 = split_image(image1,num_workers);
                imageSplit2 = split_image(image2,num_workers);
                for(int i = 0; i < num_workers; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit1[i]->width = subimage_width;
                    imageSplit1[i]->height = image1->height;
                    imageSplit2[i]->width = subimage_width;
                    imageSplit2[i]->height = image1->height;
                }
                send_and_receive(imageSplit1,num_workers,1,saturation_fact,threshold_bina,1);
                send_and_receive(imageSplit2,num_workers,2,saturation_fact,threshold_bina,1);
                BMPImage* imageRestored1 = combine_images(imageSplit1,num_workers);
                BMPImage* imageRestored2 = combine_images(imageSplit2,num_workers);
                char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
                char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
                write_bmp(saturatedname,imageRestored1);
                write_bmp(grayname,imageRestored2);
                classify(image1,threshold_class); // Clasificar la imagen
                write_csv(image1,csv_name);
                move_file(saturatedname,folder_name); // Mover el archivo de la imagen saturada al directorio especificado
                move_file(grayname,folder_name); // Mover el archivo de la imagen en escala de grises al directorio especificado
                free(imageSplit1);
                free(imageSplit2);
                free_bmp(imageRestored1);
                free_bmp(imageRestored2);
            }
           
        }

        if (num_filters == 3) { // Aplicar los tres filtros

            if(image1->height * image1->width/num_workers > BUFFER_SIZE || image2->height * image2->width/num_workers > BUFFER_SIZE || image3->height * image3->width/num_workers > BUFFER_SIZE){
                
                int width_per_worker = image1->width / num_workers;
                int remaining_width = image1->width % num_workers;
                BMPImage** imageSplit1 = (BMPImage**)malloc(sizeof(BMPImage*) * (int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                BMPImage** imageSplit2 = (BMPImage**)malloc(sizeof(BMPImage*) * (int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                BMPImage** imageSplit3 = (BMPImage**)malloc(sizeof(BMPImage*) * (int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                imageSplit1 = split_image(image1,(int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                imageSplit2 = split_image(image2,(int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                imageSplit3 = split_image(image3,(int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                for(int i = 0; i < (int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit1[i]->width = subimage_width;
                    imageSplit1[i]->height = image1->height;
                    imageSplit2[i]->width = subimage_width;
                    imageSplit2[i]->height = image1->height;
                    imageSplit3[i]->width = subimage_width;
                    imageSplit3[i]->height = image1->height;
                }
                send_and_receive(imageSplit1,num_workers,1,saturation_fact,threshold_bina,1);
                send_and_receive(imageSplit2,num_workers,2,saturation_fact,threshold_bina,1);
                send_and_receive(imageSplit3,num_workers,3,saturation_fact,threshold_bina,1);
                BMPImage* imageRestored1 = combine_images(imageSplit1,(int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                BMPImage* imageRestored2 = combine_images(imageSplit2,(int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                BMPImage* imageRestored3 = combine_images(imageSplit3,(int)ceil((image1->height * image1->width)/BUFFER_SIZE) + 1);
                char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
                char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
                char *binarname = strcat(strcpy(filename_copy, filename), "_binarization.bmp"); 
                write_bmp(saturatedname,imageRestored1);
                write_bmp(grayname,imageRestored2);
                write_bmp(binarname,imageRestored3);
                classify(image1, threshold_class);
                write_csv(image1, csv_name);
                move_file(saturatedname, folder_name);
                move_file(binarname, folder_name);
                move_file(grayname, folder_name);
                free(imageSplit1);
                free(imageSplit2);
                free(imageSplit3);
                free_bmp(imageRestored1);
                free_bmp(imageRestored2);
                free_bmp(imageRestored3);

            } else {
                
                int width_per_worker = image1->width / num_workers;
                int remaining_width = image1->width % num_workers;
                BMPImage** imageSplit1 = (BMPImage**)malloc(sizeof(BMPImage*) * num_workers);
                BMPImage** imageSplit2 = (BMPImage**)malloc(sizeof(BMPImage*) * num_workers);
                BMPImage** imageSplit3 = (BMPImage**)malloc(sizeof(BMPImage*) * num_workers);
                imageSplit1 = split_image(image1,num_workers);
                imageSplit2 = split_image(image2,num_workers);
                imageSplit3 = split_image(image3,num_workers);
                for(int i = 0; i < num_workers; i++){
                    int subimage_width = width_per_worker + (i < remaining_width ? 1 : 0);
                    imageSplit1[i]->width = subimage_width;
                    imageSplit1[i]->height = image1->height;
                    imageSplit2[i]->width = subimage_width;
                    imageSplit2[i]->height = image1->height;
                    imageSplit3[i]->width = subimage_width;
                    imageSplit3[i]->height = image1->height;
                }
                send_and_receive(imageSplit1,num_workers,1,saturation_fact,threshold_bina,1);
                send_and_receive(imageSplit1,num_workers,2,saturation_fact,threshold_bina,1);
                send_and_receive(imageSplit1,num_workers,3,saturation_fact,threshold_bina,1);
                BMPImage* imageRestored1 = combine_images(imageSplit1,num_workers);
                BMPImage* imageRestored2 = combine_images(imageSplit2,num_workers);
                BMPImage* imageRestored3 = combine_images(imageSplit3,num_workers);
                char *saturatedname = strcat(strcpy(filename_copy, filename), "_saturated.bmp"); // Crear el nombre del archivo de la imagen saturada
                char *grayname = strcat(strcpy(filename_copy, filename), "_grayscale.bmp"); // Crear el nombre del archivo de la imagen en escala de grises
                char *binarname = strcat(strcpy(filename_copy, filename), "_binarization.bmp"); 
                write_bmp(saturatedname,imageRestored1);
                write_bmp(grayname,imageRestored2);
                write_bmp(binarname,imageRestored3);
                classify(image1, threshold_class);
                write_csv(image1, csv_name);
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

        }
        */
        free_bmp(image1); // Liberar la memoria de la imagen original
        free_bmp(image2); 
        free_bmp(image3); 
        *filenames++; // Mover el puntero al siguiente nombre de archivo
    }

    return 0;
}