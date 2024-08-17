#include "fbroker.h"

int main(int argc, char *argv[]) { 
    
    int num_filters = 3;
    int opt_option;
    int num_workers = 0;
    float saturation_fact = 1.3;  
    float threshold_bina= 0.5;
    float threshold_class = 0.5;
    char* img_prefix = NULL;
    char* folder_name = NULL;
    char* csv_name = NULL;

    while((opt_option = getopt(argc, argv, "N:f:p:u:v:C:R:W:")) != -1){ // Ciclo para leer las opciones ingresadas por el usuario

        switch(opt_option){

            case 'N': // Opción para ingresar el prefijo de las imágenes
            
                img_prefix = malloc(strlen(optarg) + 1);
                if (img_prefix == NULL) {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }
                strcpy(img_prefix, optarg);
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
           
                folder_name = malloc(strlen(optarg) + 1);
                if (folder_name == NULL) {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }
                strcpy(folder_name, optarg);
                break;
            
            case 'R': // Opción para ingresar el nombre del archivo csv
           
                csv_name = malloc(strlen(optarg) + 5); // +5 para ".csv" y terminador nulo
                if (csv_name == NULL) {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }
                strcpy(csv_name, optarg);
                strcat(csv_name, ".csv");
                break;

            case 'W': // Opción para ingresar el número de trabajadores

                if(optarg == NULL){
                    fprintf(stderr, "Error: No se ingreso la cantidad de workers\n");
                    return EXIT_FAILURE;
                }
                num_workers = atoi(optarg);
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
    
    if(num_workers <= 0){

        printf("El número de workers debe ser mayor a 0");
        return 1;
    }
    
    new_folder(folder_name); // Crear el directorio donde se guardarán las imágenes
    new_csv(csv_name); // Crear el archivo csv

    int pid = fork();
    if(pid == 0){
        
        char arg1[32],arg2[32],arg3[32],arg4[32],arg5[32];
        snprintf(arg1, sizeof(arg1), "%d", num_filters);
        snprintf(arg2, sizeof(arg2), "%f", saturation_fact);
        snprintf(arg3, sizeof(arg3), "%f", threshold_bina);
        snprintf(arg4, sizeof(arg4), "%f", threshold_class);
        snprintf(arg5, sizeof(arg5), "%d", num_workers);
        char* args[] = {"./broker",img_prefix,arg1,arg2,arg3,arg4,arg5,folder_name,csv_name,NULL};
        execv(args[0],args);
        perror("execv");
        exit(EXIT_FAILURE);

    } else if(pid > 0){ 
        

        waitpid(pid, NULL, 0); //Esperar a que el proceso hijo termine
    } else {

        perror("fork");
        return EXIT_FAILURE;
    }
    
    return 0;
}