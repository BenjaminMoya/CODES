#include "fbroker.h"

int main(int argc, char *argv[]) { 
    
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

                if(optarg == NULL){
                    printf("Se debe ingresar un prefijo de imagen\n");
                    return 1;
                }
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

                if (optarg == NULL) {
                    fprintf(stderr, "Error: Falta el argumento para la opción '-C' o el argumento está malformado\n");
                    return EXIT_FAILURE;
                }
                foldername = malloc(strlen(optarg) + 1); // Asignar memoria dinámica
                if (foldername == NULL) {
                    fprintf(stderr, "Error: No se pudo asignar memoria.\n");
                    return EXIT_FAILURE;
                }
                strcpy(foldername, optarg); // Copiar el nombre del directorio
                break;
            
            case 'R': // Opción para ingresar el nombre del archivo csv

                if(optarg == NULL){
                    printf("Se debe ingresar un nombre de csv\n");
                    return 1;
                }
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

                if(optarg == NULL){
                    printf("Se debe ingresar la cantidad de workers");
                    return 1;
                }
                workers = atoi(optarg);
                break;
        
        }
    
    }
    
    if (thresholdbina < 0 || thresholdbina > 1){ // Verificar si el umbral de binarización está entre 0 y 1

        printf("El umbral de binarizacion debe estar entre 0 y 1");
        return 1;
    }

    if (thresholdclass < 0 || thresholdclass > 1){ // Verificar si el umbral de clasificación está entre 0 y 1

        printf("El umbral de clasificacion debe estar entre 0 y 1");
        return 1;
    }
    
    sem_t *mutex_main = sem_open("/mutex_main", O_CREAT | O_EXCL, 0644, 0);
    if (mutex_main == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    
    csvname= strcat(csvname,".csv"); // Agregar la extensión .csv al nombre del archivo csv
    new_folder(foldername); // Crear el directorio donde se guardarán las imágenes
    new_csv(csvname); // Crear el archivo csv

    int pid = fork();
    if(pid == 0){

        char flag1[]="-N ",flag2[]="-f ",flag3[]="-p ",flag4[]="-u ",flag5[]="-v ",flag6[]="-W";
        char float_str1[32],float_str2[32],float_str3[32],float_str4[32],float_str5[32];
        sprintf(float_str1, "%d", filters);
        sprintf(float_str2, "%f", saturation);
        sprintf(float_str3, "%f", thresholdbina);
        sprintf(float_str4, "%f", thresholdclass);
        sprintf(float_str5, "%d", workers);
        strcat(flag1,prefix);
        strcat(flag2,float_str1);
        strcat(flag3,float_str2);
        strcat(flag4,float_str3);
        strcat(flag5,float_str4);
        strcat(flag6,float_str5);
        char* argv[] = {"./broker",flag1,flag2,flag3,flag4,flag5,NULL};
        execv(argv[0],argv);
        return;

    } else {
        
        sem_wait(mutex_main); // Esperar a que el semáforo mutexMain esté disponible
    }
    
    return 0;
}