all: lab1.o funciones.o lab1

funciones.o: funciones.c funciones.h
		gcc -g -c funciones.c 

lab1.o: lab1.c funciones.h
		gcc -g -c lab1.c 

lab1: funciones.o lab1.o
		gcc -g -o lab1 funciones.o lab1.o

clean:
		rm -f lab1 funciones.o lab1.o

#Posibles comandos por consola luego de compilar
#./lab1 -N ejemplo -C directorio -R tabla
#./lab1 -N ejemplo -f 1 -p 20 -C directorio -R tabla

