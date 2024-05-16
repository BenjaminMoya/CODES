#include <stdio.h>

struct datos
{
  int edad;
  char nombre[40];
  float altura;
  char rut[15];
};
typedef struct datos datos_personales;

datos_personales *crear_perfil(int edad_perfil,char nombre_perfil[],float altura_perfil,char rut_perfil[]);
void mostrar_dato(datos_personales *datoseleccionado, int numero);

int main()
{
  int edad,opcion;
  char nombre[40];
  float altura;
  char rut[15];  
  datos_personales *perfil_1;
  printf("Edad:");
  scanf("%i",&edad);
  printf("Altura (en metros):");
  scanf("%f",&altura);
  printf("Nombre:");
  scanf("%s",nombre);
  printf("Rut (sin punto y con guion):");
  scanf("%s",rut);
  perfil_1=crear_perfil(edad,nombre,altura,rut);
  printf("Que dato quiere consultar?\n");
  printf("1)Edad\n");
  printf("2)Altura\n");
  printf("3)Nombre\n");
  printf("4)Rut\n");
  scanf("%i",&opcion);
  mostrar_dato(perfil_1,opcion);
}

datos_personales *crear_perfil(int edad_perfil,char nombre_perfil[],float altura_perfil,char rut_perfil[])
{
  datos_personales *d;
  d=(datos_personales*)malloc(4);
  d->edad=edad_perfil;
  d->altura=altura_perfil;
  return d;
}

void mostrar_dato(datos_personales *datoseleccionado,int numero)
{
  if (numero==1)
    printf("%i",datoseleccionado->edad);
  if (numero==2)
    printf("%f",datoseleccionado->altura);
  if (numero==3)
    printf("%s",datoseleccionado->nombre);
  if (numero==4)
    printf("%s",datoseleccionado->rut);
}

