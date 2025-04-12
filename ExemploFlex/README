Este diretorio contém arquivos que podem ser utilizados como exemplos para a implementacao do trabalho.
O arquivo lex.l e um exemplo de arquivo de entrada para o Flex.
O arquivo main.c contem um exemplo de programa principal para o trabalho ( Na verdade voce pode utilizar o programa exatamente como esta ou fazer uma pequena modificacao para que ele grave a saida em arquivo em vez de envia-la para a tela).
Abra o programa main.c 
     Voce sabe porque yylex e yyin foram declarados com extern?
     Repare que a funcao yylex(), que corresponde ao analisador lexico implementado pelo Flex, retorna um valor de token igual a zero quando o fim de arquivo e encontrado no arquivo de entrada. Por isto o while e interrompido e o programa termina.

Dados estes dois arquivos fontes (lex.l e main.c) use o comando make para ativar o Makefile. O Makefile tem instrucoes para:
     1) Compilar o programa main.c gerando o main.o
     1) Compilar o lex.l utilizando o Flex e gerar o lex.yy.c que contem a funcao yylex() (o analisador lexico) 
     2) Compilar o lex.yy.c gerando o lexico.o
     3) "Linkar"  lexico.o e main.o gerando o arquivo executável programaPrincipal

Uma vez que o comando make tenha terminado
execute na shell o seguinte comando: ./programaPrincipal teste.txt
a seguinte saida deve aparecer na tela:

Inteiro: 234
Inteiro: 345
Real: 23.4


Abra o arquivo Makefile tente entender como ele funciona, lendo os comentários inseridos no arquivo.
Você pode aproveitar o Makefile tal como está para o seu trabalho, mas deve procurar entender como ele funciona pois
sera necesario fazer extensoes nos proximos trabalhos.


