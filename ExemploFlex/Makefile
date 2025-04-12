#Substitua o valor de CC com o nome do compilador que voce usa: gcc ou g++
CC = gcc
CFLAGS =   -g  -Wall -ansi
LFLAGS = -lm

# O programaPrincipal executavel depende de lexico.o e main.o. Uma vez obtidos estes arquivos eles sao "linkados"
# gerando o executavel programaPrincipal

programaPrincipal:   lexico.o  main.o
	$(CC) $(CFLAGS) $(LFLAGS) lexico.o main.o -o  programaPrincipal
                
# main.o depende de main.cc. Se ele for alterado, main.o deve ser obtido novamente e o comando para fazer isto é 
# comando de compilacao dada na segunda linha a seguir
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

# lexico.o é o programa objeto gerado a partir da compilacao do arquivo lex.yy.c gerado pelo Flex. Sempre que o 
# arquivo lex.l for editado, um novo lex.yy.c deve ser gerado usando o Flex e em seguida, o novo lex.yy.c deve ser
# compilado para gerara o novo lexico.o. Entao lex.yy.c depende de lex.l e lexico.o depende de lex.yy.c.

lex.yy.c: lex.l
	flex lex.l

lexico.o: lex.yy.c  
	$(CC) $(CFLAGS) -c lex.yy.c   -o lexico.o


# Se na linha de comando voce digitar: make clean, os arquivo objetos (.o) e o executavel (programaPrincipal)
# serao apagados. Isto é util quando for submeter a versao final do trabalho para o professor, antes de fazer
# make tgz
clean:
	rm -f   *.o    programaPrincipal

cleanObj:
	rm -f   *.o  
# Quando seu trabalho estiver pronto. No diretorio onde estão fontes digite na linha de comando: make tgz
# este comando ira criar um arquivo do tipo tar zipado com extensao .tgz contendo os fontes do seu programa e o Makefile.
# envie um mail com este arquivo para o professor.
tgz: 
	rm -f *.o rm programaPrincipal *.tgz 
	tar -zcvf Lexico.tgz *
	echo "O arquivo Lexico.tgz com os fontes e Makefile foi gerado. Pode ser enviado."	
