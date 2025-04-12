/* Secao de declaracao (delcaration section)*/

%{
#include <stdio.h>
#include <stdlib.h>
extern int yylex();
FILE *yyin;
void yyerror(char const *);
extern int yylineno;

%}
/* Bison Declarations */
%token WHITESPACE
%token  NUMERO
%left MAIS MENOS
%left MULT DIV
%token ABREPAREN
%token FECHAPAREN
%verbose

%% /*Grammar rules*/
linha:         expr  {printf("%d \n", $1);}
;

expr:          expr MAIS term  {printf ("expr=%d  + term=%d\n", $1,$3); $$=$1+$3;}
               |expr MENOS term {printf ("expr=%d  - term=%d\n", $1,$3);$$=$1-$3; }
               |term {printf ("term= %d\n", $1);$$=$1}
;

term:          term MULT factor {printf ("term=%d  * factor=%d\n", $1,$3);$$=$1*$3;}
               |term DIV factor {printf ("term=%d  / factor=%d\n", $1,$3);$$=$1/$3;}
               | factor {printf ("factor=%d\n", $1); $$=$1}
;

factor:        |ABREPAREN expr FECHAPAREN {printf("( expr=%d  )\n", $2);$$=$2;}
               |NUMERO {printf("NUMERO=%d\n", $1); $$=$1;}
               ;
%% /*Epilogue*/
void yyerror(char const* msg){
printf("%s -- Linha %d\n",msg, yylineno); 
}

int main(int argc, char**argv){
     if(argc!=2){
          printf("Uso correto: calc <nome> \n");
          exit(1);
     }
     yyin=fopen(argv[1],"rt");
     if(yyin)
          return yyparse();
     else 
          yyerror("arquivo nao encontrado");
     return(1);
}