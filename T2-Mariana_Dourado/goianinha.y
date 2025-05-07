/* O codigo de entrada para o gerador de analisador sintatico utilizado*/
/* goianinha.y – especificação do analisador sintático (Bison/YACC) */


%{
#include <stdio.h>
#include <stdlib.h>
extern int yylex(); // extern mesmo? não devo definir?
void yyerror(const char *);
%}
/* 
%union {
    int intval;
    char charval;
    char *string;
} */

%token PROGRAMA INT CAR LEIA ESCREVA NOVALINHA RETORNE
%token INTCONST CARCONST ID CADEIACARACTERES
%token SE ENTAO SENAO
%token ENQUANTO EXECUTE
%token OU E NEG
%token EQ NEQ LE GE MENOR MAIOR RECEBE
%token MAIS MENOS VEZES DIVIDE
%token PONTOVIRGULA VIRGULA
%token ABREPARENT FECHAPARENT ABRECHAVE FECHACHAVE


%%

Programa
    : DeclFuncVar DeclProg
    ;

DeclFuncVar
    : Tipo ID DeclVar PONTOVIRGULA DeclFuncVar
    | Tipo ID DeclFunc DeclFuncVar
    | /* vazio */
    ;

DeclProg
    : PROGRAMA Bloco
    ;

DeclVar
    : VIRGULA ID DeclVar
    | /* vazio */
    ;

DeclFunc
    : ABREPARENT ListaParametros FECHAPARENT Bloco
    ;

ListaParametros
    : /* vazio */
    | ListaParametrosCont
    ;

ListaParametrosCont
    : Tipo ID
    | Tipo ID VIRGULA ListaParametrosCont
    ;

Bloco
    : ABRECHAVE ListaDeclVar ListaComando FECHACHAVE
    ;

ListaDeclVar
    : /* vazio */
    | Tipo ID DeclVar PONTOVIRGULA ListaDeclVar
    ;

Tipo
    : INT
    | CAR
    ;

ListaComando
    : Comando
    | Comando ListaComando
    ;

Comando
    : PONTOVIRGULA
    | Expr PONTOVIRGULA
    | RETORNE Expr PONTOVIRGULA
    | LEIA ID PONTOVIRGULA
    | ESCREVA Expr PONTOVIRGULA
    | ESCREVA CADEIACARACTERES PONTOVIRGULA
    | NOVALINHA PONTOVIRGULA
    | SE ABREPARENT Expr FECHAPARENT ENTAO Comando
    | SE ABREPARENT Expr FECHAPARENT ENTAO Comando SENAO Comando
    | ENQUANTO ABREPARENT Expr FECHAPARENT EXECUTE Comando
    | Bloco
    ;

Expr
    : OrExpr
    | ID RECEBE Expr
    ;

OrExpr
    : OrExpr OU AndExpr
    | AndExpr
    ;

AndExpr
    : AndExpr E EqExpr
    | EqExpr
    ;

EqExpr
    : EqExpr EQ DesigExpr
    | EqExpr NEQ DesigExpr
    | DesigExpr
    ;

DesigExpr
    : DesigExpr MENOR AddExpr
    | DesigExpr MAIOR AddExpr
    | DesigExpr GE AddExpr
    | DesigExpr LE AddExpr
    | AddExpr
    ;

AddExpr
    : AddExpr MAIS MulExpr
    | AddExpr MENOS MulExpr
    | MulExpr
    ;

MulExpr
    : MulExpr VEZES UnExpr
    | MulExpr DIVIDE UnExpr
    | UnExpr
    ;

UnExpr
    : MENOS PrimExpr
    | NEG PrimExpr
    | PrimExpr
    ;

PrimExpr
    : ID ABREPARENT ListExpr FECHAPARENT
    | ID ABREPARENT FECHAPARENT
  FECHAPARENT ID
    | CARCONST
    | INTCONST
    | ABREPARENT Expr FECHAPARENT
    ;

ListExpr
    : Expr
    | ListExpr VIRGULA Expr
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "ERRO: %s na linha %d\n", s, yylineno);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso correto: goianinha <arquivo>\n");
        exit(1);
    }
    // extern FILE *yyin;
    yyin = fopen(argv[1], "rt");
    if (!yyin) {
        yyerror("Erro ao abrir arquivo");
        exit(1);
    }
    // mudar isso depois se pá
    if (yyparse() == 0)
        printf("Análise sintática concluída com sucesso.\n");
    //return yyparse();
}
