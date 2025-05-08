# Comandos de execu¸c˜ao do gerador de analisador l´exico (Flex ou JFlex) para convers˜ao do arquivo de entrada do gerador de analisador l´exico em programas em C.
# – Comandos de execu¸c˜ao do gerador de analisador sint´atico (YACC ou Bison) para
# convers˜ao do arquivo de entrada do gerador de analisador sint´atico.
# – Comandos de compila¸c˜ao e link-edi¸c˜ao para compilar e ligar o programa principal
# com os c´odigos dos analisadores l´exicos e sint´aticos gerados.
CC      = gcc
LEX     = flex
YACC    = bison -d
CFLAGS  = -Wall -g

all: goianinha

lex.yy.c: goianinha.l goianinha.tab.h
	$(LEX) goianinha.l

goianinha.tab.c goianinha.tab.h: goianinha.y
	$(YACC) -o goianinha.tab.c goianinha.y

goianinha: goianinha.tab.c lex.yy.c 
	$(CC) $(CFLAGS) $^ -o $@ -lfl

clean:
	rm -f lex.yy.c goianinha.tab.c goianinha.tab.h goianinha
