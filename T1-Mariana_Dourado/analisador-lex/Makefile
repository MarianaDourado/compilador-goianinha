CC = gcc
CFLAGS =   -g  -Wall -ansi
LFLAGS = -lm


# Só pra ficar mais organizado coloquei o "rm" aqui
analisador-lex:   goianinha.o  main.o
	$(CC) $(CFLAGS) $(LFLAGS) goianinha.o main.o -o analisador-lex
	rm -f   *.o    lex.yy.c 

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o


lex.yy.c: lex.l
	flex lex.l

goianinha.o: lex.yy.c  
	$(CC) $(CFLAGS) -c lex.yy.c   -o goianinha.o


clean:
	rm -f   *.o    analisador-lex
	
cleanObj:
	rm -f   *.o

tgz: 
	rm -f *.o rm analisador-lex *.tgz 
	tar -zcvf Lexico.tgz *
	echo "O arquivo Lexico.tgz com os fontes e Makefile foi gerado. Pode ser enviado."	
