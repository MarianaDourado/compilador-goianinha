/*O código de entrada para o gerador de analisador léxico utilizado*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END_OF_FILE   -1
#define PROGRAMA       1
#define CAR            2
#define INT            3
#define RETORNE        4
#define LEIA           5
#define ESCREVA        6
#define NOVALINHA      7
#define SE             8
#define ENTAO          9
#define SENAO         10
#define ENQUANTO      11
#define EXECUTE       12
#define INTCONST      13
#define CARCONST      14
#define STRING        15
#define ID            16
#define EQ            17
#define NEQ           18
#define NEG           19
#define LEQ           20
#define GEQ           21
#define MENOR         22
#define MAIOR         23
#define MAIS          24
#define MENOS         25
#define VEZES         26
#define DIVIDE        27
#define E             28
#define OU            29
#define RECEBE        30
#define ABREPARENT    31
#define FECHAPARENT   32
#define ABRECHAVE     33
#define FECHACHAVE    34
#define VIRGULA       35
#define PONTOVIRG     36

extern int yylineno = 1;
extern char* yytext;

%x COMENTARIO

%}

WHITESPACE [\t' '\r] 

DIGITO [0-9]
LETRA [a-zA-Z]
ID ({LETRA}|_)({LETRA}|{DIGITO}|_)*
INTCONST {DIGIT}+
CARCONST \'([^\'\n\\]|\\.)\'
STRING \"([^\"\n\\]|\\.)*\"

%%

{WHITESPACE}+ {/* não faz nada */}

"programa"    { return PROGRAMA; }
"car"         { return CAR; }
"int"         { return INT; }
"retorne"     { return RETORNE; }
"leia"        { return LEIA; }
"escreva"     { return ESCREVA; }
"novalinha"   { return NOVALINHA; }
"senao"       { return SENAO; }
"se"          { return SE; }
"entao"       { return ENTAO; }
"enquanto"    { return ENQUANTO; }
"execute"     { return EXECUTE; }

"=="          { return EQ; }
"!="          { return NEQ; }
"!"           { return NEG; }        
"<="          { return LEQ; }
">="          { return GEQ; }
"<"           { return MENOR; }
">"           { return MAIOR; }

"+"           { return MAIS; }
"-"           { return MENOS; }
"*"           { return VEZES; }
"/"           { return DIVIDE; }

"e"           { return E; }
"ou"          { return OU; }

"="           { return RECEBE; }

"("           { return ABREPARENT; }
")"           { return FECHAPARENT; }
"{"           { return ABRECHAVE; }
"}"           { return FECHACHAVE; }

","           { return VIRGULA; }
";"           { return PONTOVIRG; }

{INTCONST}    { return INTCONST; }
{CARCONST}    { return CARCONST; }
{STRING}      { return STRING; }
{ID}          { return ID; }

"/*"          { BEGIN(COMENTARIO); }

\n            { yylineno++; }

<<EOF>>       { return END_OF_FILE; }


<COMENTARIO> {
    "*/"      {BEGIN(INITIAL); }
    \n        {yylineno++;}
    .         {/* outros caracteres*/ }
}

<COMENTARIO><<EOF>> {
    printf("ERRO: COMENTÁRIO NÃO TERMINA %d", yylineno);
}

{STRING}\n {
    print("ERRO: CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA %d\n", yylineno);
    exit(1);
}

. {
    printf("ERRO: CARACTERE INVÁLIDO %d\n", yylineno);
    exit(1);
}

%%

int yywrap();

int yywrap(){
    return 1;
}