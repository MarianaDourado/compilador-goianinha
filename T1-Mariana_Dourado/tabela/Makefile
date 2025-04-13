CC = gcc
CFLAGS = -g  -Wall

all: main_testes

main_testes: estruturas.o main_testes.o 
	$(CC) $(CFLAGS) -o main_testes estruturas.o main_testes.o

estruturas.o: estruturas.c  estruturas.h
	$(CC) $(CFLAGS) -c estruturas.c

main_testes.o: main_testes.c estruturas.h
	$(CC) $(CFLAGS) -c main_testes.c
                
clean:
	rm -f  *.o  main_testes
