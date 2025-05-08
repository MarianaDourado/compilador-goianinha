# Comandos de execu¸c˜ao do gerador de analisador l´exico (Flex ou JFlex) para convers˜ao do arquivo de entrada do gerador de analisador l´exico em programas em C.
# – Comandos de execu¸c˜ao do gerador de analisador sint´atico (YACC ou Bison) para
# convers˜ao do arquivo de entrada do gerador de analisador sint´atico.
# – Comandos de compila¸c˜ao e link-edi¸c˜ao para compilar e ligar o programa principal
# com os c´odigos dos analisadores l´exicos e sint´aticos gerados.
CC      = gcc
LEX     = flex 
YACC    = bison -d -t -v --output=goianinha.sintatico.c
CFLAGS  = -Wall -g

all: goianinha

lex.yy.c: goianinha.l goianinha.sintatico.h
	$(LEX) goianinha.l

goianinha.sintatico.c goianinha.sintatico.h: goianinha.y
	$(YACC) -o goianinha.sintatico.c goianinha.y

goianinha: goianinha.sintatico.c lex.yy.c 
	$(CC) $(CFLAGS) $^ -o $@ -lfl

clean:
	rm -f lex.yy.c goianinha*.c  *.o  goianinha

tgz: 
	rm -f *.o rm goianinha *.tgz 
	tar -zcvf goianinha.tgz *
	echo "O arquivo goianinha.tgz com os fontes e Makefile foi gerado. Pode ser enviado."	
