#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern int yylex();
extern char* yytext; /* Variavel global definida em lex.yy.c para armazenar o lexema do token 
                         após uma chamada a yylex() */
FILE * yyin;         /* Variavel utilizada por yylex como arquivo de entrada*/
int main(int argc, char** argv){
     if( argc !=2){
          printf("Uso correto: programaPrincipal arquivo_de_teste\n");
          exit(1);
     }
     yyin=fopen( argv[1], "r" );
     int token= yylex();  
     while(token){
          printf("token: %d lexema: %s", token, yytext);
          token=yylex();
     }
return(1);
}
