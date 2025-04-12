#Substitua o valor de CC com o nome do compilador que voce usa: gcc ou g++
CC = gcc
CFLAGS =   -g  -Wall -ansi
LFLAGS = -lm

# O programaPrincipal executavel depende de lexico.o e main.o. Uma vez obtidos estes arquivos eles sao "linkados"
# gerando o executavel programaPrincipal

programaPrincipal:    main.o lexico.o
	$(CC) $(CFLAGS) $(LFLAGS) lexico.o main.o -o  programaPrincipal
                
# main.o depende de calc.tab.c Se ele for alterado, main.o deve ser obtido novamente e o comando para fazer isto é 
# comando de compilacao dada na segunda linha a seguir
main.o: calc.tab.c
	$(CC) $(CFLAGS) -c calc.tab.c -o main.o

# lexico.o é o programa objeto gerado a partir da compilacao do arquivo lex.yy.c gerado pelo Flex. Sempre que o 
# arquivo lex.l for editado, um novo lex.yy.c deve ser gerado usando o Flex e em seguida, o novo lex.yy.c deve ser
# compilado para gerara o novo lexico.o. Entao lex.yy.c depende de lex.l e lexico.o depende de lex.yy.c.

lex.yy.c: lex.l
	flex  --yylineno lex.l

lexico.o: lex.yy.c  
	$(CC) $(CFLAGS) -c lex.yy.c   -o lexico.o


# calc.tab.c depende do arquivo fonte para o Bison calc.y. Se calc.y for modificado, novo calc.tab.c deve ser gerado
# Repare que a opcao -d foi usada. Ela causa a criacao do arquivo de cabeçalho calc.tab.h pelo bison. Este arquivo é 
# utilizado em lex.l para que o lexico e o sintático concordem com os mesmos codigos de tokens.

calc.tab.c: calc.y
	bison -d calc.y


# Se na linha de comando voce digitar: make clean, os arquivo objetos (.o) e o executavel (programaPrincipal)
# serao apagados. Isto é util quando for submeter a versao final do trabalho para o professor, antes de fazer
# make tgz
clean:
	rm -f   calc.tab.c lex.yy.c *.o    programaPrincipal

cleanObj:
	rm -f   *.o  
# Quando seu trabalho estiver pronto. No diretorio onde estão fontes digite na linha de comando: make tgz
# este comando ira criar um arquivo do tipo tar zipado com extensao .tgz contendo os fontes do seu programa e o Makefile.
# envie um mail com este arquivo para o professor.
tgz: 
	rm -f *.o rm programaPrincipal *.tgz 
	tar -zcvf cezinho.tgz *
	echo "O arquivo cezinho.tgz com os fontes e Makefile foi gerado. Pode ser enviado."	
