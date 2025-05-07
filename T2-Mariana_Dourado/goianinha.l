/* O c´odigo de entrada para o gerador de analisador l´exico utilizado */
/* goianinha.l – especificação do analisador léxico (Flex) */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "goianinha.tab.h"

extern int yylineno;

%}

%option noyywrap

WHITESPACE [\t' '\r] 

DIGITO [0-9]
LETRA [a-zA-Z]
ID ({LETRA}|_)({LETRA}|{DIGITO}|_)*
INTCONST {DIGITO}+
CARCONST \'([^\'\n])\'
CONSTSTRING \"([^\"\n])*\"

%x COMENTARIO

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
";"           { return PONTOVIRGULA; }

{ID}          { yylval.string = strdup(yytext); return ID; }
{INTCONST}    { yylval.intval = atoi(yytext); return INTCONST; }
{CARCONST}    { yylval.charval = yytext[1]; return CARCONST; }
{CONSTSTRING} { yylval.string = strdup(yytext); return CONSTSTRING; }

"/*"          { BEGIN(COMENTARIO); }

\n            { yylineno++; }


<COMENTARIO>{
    "*/"      {BEGIN(INITIAL); }
    \n        {yylineno++;}
    .         {/* ignora outros caracteres*/ }
}


<<EOF>>       {
    if(YY_START == COMENTARIO){
        fprintf(stderr, "ERRO: COMENTÁRIO NÃO TERMINA %d\n", yylineno);
        exit(1);
    }
    return 0; // EOF
}


\"([^\"\n\\]|\\.)*\n {
    fprintf(stderr, "ERRO: CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA %d\n", yylineno);
    exit(1);
}

. {
    fprintf(stderr, "ERRO: CARACTERE INVÁLIDO %d\n", yylineno);
    exit(1);
}

%%
