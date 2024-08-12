all: fworker.o fbroker.o worker broker lab2

fworker.o: fworker.c fworker.h
		gcc -g -c fworker.c 

fbroker.o: fbroker.c fbroker.h
		gcc -g -c fbroker.c

worker: fworker.o worker.c
		gcc -g fworker.o worker.c -o worker

broker: fworker.o fbroker.o broker.c
		gcc -g fworker.o fbroker.o broker.c -o broker

lab2: fworker.o fbroker.o lab2.o
		gcc -g -o fworker.o fbroker.o lab2 funciones.o lab2.o

clean:
		rm -f lab2 fworker.o fbroker.o wroker broker lab2

#Posibles comandos por consola luego de compilar
#./lab1 -N ejemplo -C directorio -R tabla
#./lab1 -N ejemplo -f 1 -p 20 -C directorio -R tabla