ex: main.o modulo.o
	gcc main.o modulo.o -o ex -lm

main.o: main.c
	gcc -c main.c -o main.o -lm

modulo.o: modulo.S
	gcc -c modulo.S -o modulo.o