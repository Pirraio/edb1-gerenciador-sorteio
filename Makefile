CC = gcc
CFLAGS = -Wall

all: main

main: main.o gerenciador.o
	$(CC) $(CFLAGS) -o main main.o gerenciador.o

main.o: main.c gerenciador.h
	$(CC) $(CFLAGS) -c main.c

gerenciador.o: gerenciador.c gerenciador.h
	$(CC) $(CFLAGS) -c gerenciador.c

clean:
	rm -f *.o main