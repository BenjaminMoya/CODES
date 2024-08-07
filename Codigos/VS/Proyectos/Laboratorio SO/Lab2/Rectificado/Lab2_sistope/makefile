all: funciones.o worker broker.o lab2

funciones.o: funciones.c funciones.h
		gcc -c funciones.c

worker: funciones.o worker.c 
		gcc funciones.o worker.c -o worker 

broker.o: broker.c broker.h
		gcc -c broker.c

lab2: broker.o lab2.c
		gcc funciones.o broker.o lab2.c -o lab2 

clean:
		rm -f lab2 worker funciones.o lab2.o broker.o

#./lab1 -N ejemplo -C directorio -R tabla
#./lab1 -N ejemplo -f 1 -p 20 -C directorio -R tabla

