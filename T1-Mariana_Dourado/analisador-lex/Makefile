CC = gcc
CFLAGS =   -g  -Wall -ansi
LFLAGS = -lfl -lm


goianinha:   goianinha.o  main.o
	$(CC) $(CFLAGS) $(LFLAGS) goianinha.o main.o -o goianinha

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

lex.yy.c: goianinha.l
	flex goianinha.l

goianinha.o: lex.yy.c  
	$(CC) $(CFLAGS) -c lex.yy.c -o goianinha.o

clean:
	rm -f   *.o    goianinha
	
cleanObj:
	rm -f   *.o

tgz: 
	rm -f *.o rm goianinha *.tgz 
	tar -zcvf Lexico.tgz *
	echo "O arquivo Lexico.tgz com os fontes e Makefile foi gerado. Pode ser enviado."	
