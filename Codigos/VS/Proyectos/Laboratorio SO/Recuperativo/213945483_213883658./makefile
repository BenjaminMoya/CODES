all: funciones.o lab1

funciones.o: funciones.c funciones.h
		gcc -g -c funciones.c 

lab1: funciones.o lab1.c
		gcc -g funciones.o lab1.c -o lab1

clean:
		rm -f funciones.o lab1 

#Posibles comandos por consola luego de compilar
#./lab1 -N ejemplo -C directorio -R tabla
#./lab1 -N ejemplo -f 1 -p 20 -C directorio -R tabla

