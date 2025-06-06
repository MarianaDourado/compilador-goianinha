CC      = gcc
LEX     = flex
YACC    = bison -d -t -v --output=goianinha.sintatico.c
CFLAGS  = -Wall -g

all: goianinha

lex.yy.c: goianinha.l goianinha.sintatico.h
	$(LEX) goianinha.l

goianinha.sintatico.c goianinha.sintatico.h: goianinha.y
	$(YACC) -o goianinha.sintatico.c goianinha.y

# Compilamos todos os .c juntos:
goianinha: goianinha.sintatico.c lex.yy.c ast.c tabelaDeSimbolos.c
	$(CC) $(CFLAGS) goianinha.sintatico.c lex.yy.c ast.c tabelaDeSimbolos.c -o goianinha -lfl

clean:
	rm -f lex.yy.c goianinha.sintatico.c goianinha.sintatico.h *.o goianinha

tgz:
	rm -f *.o goianinha *.tgz
	tar -zcvf goianinha.tgz *
	echo "O arquivo goianinha.tgz com os fontes foi gerado."
