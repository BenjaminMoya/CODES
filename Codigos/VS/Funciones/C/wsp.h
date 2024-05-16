#include <stdio.h>
#include <math.h>

struct contacto
{
	char numero[13];
	char nombre[50];
	char mensaje[100];
}

typedef contacto contacto_wsp;

contacto *creacion_contacto(char numeroingresado[],char nombreingresado[])
{
	FILE *fp1;
	fp1=fopen("Contactos.txt","a");
	contacto *p;
	p=(contacto*)malloc(sizeof(contacto_wsp));
	p->numero=numeroingresado;
	p->nombre=nombreingresado;
	fprintf(fp1,"%s\n",nombreingresado);
	fprintf(fp1,"%s\n\n",numeroingresado);
	fclose(fp1);
	return p;
}

void enviar_mensaje(contacto_wsp *p,char mensajeaenviar[])
{
	FILE *fp1;
	char nombrecontacto[50];
	fp1=fopen("Mensajeria.txt","a");
	p->mensaje=mensajeaenviar;
	p->nombre=nombrecontacto;
	fprintf(fp1,"%s\n %s\n",nombrecontacto,mensajeaenviar);
	fclose(fp1);
}

bool buscar_contacto(char nombreingresado[])
{
	FILE *fp1;
	char busqueda[50];
	fp1=fopen("Contactos.txt","r");
	if (fp1==NULL)
	{
		printf("No hay contactos registrados")
		return false;
	}
	while(feof(fp1)==0)
		fscanf(fp1,"%s",busqueda);
		if (busqueda==nombreingresado)
		{
			printf("El contacto ya esta creado\n");
			return true;
		}
		else if 
		{
			printf("El contacto no ha sido creado\n")
			return false;
		}
}