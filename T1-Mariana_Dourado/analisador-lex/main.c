// O código do falso sintático 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern char* yytext; /* Variavel global definida em lex.yy.c para armazenar o lexema do token 
                         após uma chamada a yylex() */
FILE * yyin;         /* Variavel utilizada por yylex como arquivo de entrada*/
extern int yylineno;

int main(int argc, char** argv){
     if(argc !=2){
          printf("Uso correto: programaPrincipal arquivo_de_teste\n");
          exit(1);
     }
     yyin=fopen( argv[1], "r" );
     int token= yylex();  
     while(token != -1){
          printf("Encontrado o lexema %s pertencente ao token de código %d linha %d", yytext, token, yylineno);
          token=yylex();
     }

     fclose(yyin);
     return(1);
}