all: lab2.o funciones.o lab2

funciones.o: funciones.c funciones.h
		gcc -g -c funciones.c 

lab2.o: lab2.c funciones.h
		gcc -g -c lab2.c 

lab: funciones.o lab2.o
		gcc -g -o lab2 funciones.o lab2.o

clean:
		rm -f lab2 funciones.o lab2.o

#Posibles comandos por consola luego de compilar
#./lab1 -N ejemplo -C directorio -R tabla
#./lab1 -N ejemplo -f 1 -p 20 -C directorio -R tabla

