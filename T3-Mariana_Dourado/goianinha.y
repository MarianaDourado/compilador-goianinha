/* O codigo de entrada para o gerador de analisador sintatico utilizado*/
/* goianinha.y – especificação do analisador sintático (Bison/YACC) */


%{
#include <stdio.h>
#include <stdlib.h>
#include "goianinha.sintatico.h"
#include "ast.h"

extern FILE *yyin;
extern int yylineno;
void yyerror(const char *);
extern int yyparse();
extern int yylex();
%}

/* %define parse.trace */ // para debug

%union {
    int intval;
    char charval;
    char *string;
    ASTNode *node;
}

%token PROGRAMA INT CAR LEIA ESCREVA NOVALINHA RETORNE

/* %token INTCONST CARCONST ID CONSTSTRING */
%token <intval> INTCONST
%token <charval> CARCONST
%token <string> ID CONSTSTRING

%token SE ENTAO SENAO
%token ENQUANTO EXECUTE
%token OU E NEG
%token EQ NEQ LEQ GEQ MENOR MAIOR RECEBE
%token MAIS MENOS VEZES DIVIDE
%token PONTOVIRGULA VIRGULA
%token ABREPARENT FECHAPARENT ABRECHAVE FECHACHAVE

%type <node> Programa
%type <node> DeclFuncVar DeclProg DeclVar DeclFunc
%type <node> ListaParametros ListaParametrosCont Bloco ListaDeclVar
%type <node> ListaComando Comando Expr OrExpr AndExpr EqExpr DesigExpr
%type <node> AddExpr MulExpr UnExpr PrimExpr ListExpr

%%

Programa
    : DeclFuncVar DeclProg
        {
            $$ = astCreate("Programa", @1.first_line, 2, $1, $2);
            raizAST = $$;
        }
    ;

DeclFuncVar
    : Tipo ID DeclVar PONTOVIRGULA DeclFuncVar
        {
            ASTNode *nTipo  = astCreate("Tipo", @1.first_line, 1, $1);
            ASTNode *nID    = astNewId($2, @2.first_line);
            ASTNode *nDeclV = $3;
            ASTNode *next   = $5;

            $$ = astCreate("DeclVarGlobal", @1.first_line, 4, nTipo, nID, nDeclV, next);
        }
    | Tipo ID DeclFunc DeclFuncVar
        {
            ASTNode *nTipo     = astCreate("Tipo", @1.first_line, 1, $1);
            ASTNode *nID       = astNewId($2, @2.first_line);
            ASTNode *nParams   = $3;
            ASTNode *nCont     = $4;  // corpo
            ASTNode *next      = $5;

            $$ = astCreate("DeclFuncGlobal", @1.first_line, 4, nTipo, nID, nParams, nCont);
        }
    | /* vazio */ { $$ = astCreate("DeclFuncVar", @$.first_line, 0); }
    ;

DeclProg
    : PROGRAMA Bloco
        {
            ASTNode *nProgTok = astCreate("KW_PROGRAMA", @1.first_line, 0);
            $$ = astCreate("DeclProg", @1.first_line, 2, nProgTok, $2);
        }
    ;

DeclVar
    : VIRGULA ID DeclVar
        {
            ASTNode *nID = astNewId($2, @2.first_line); ASTNode *nRest = $3;
            $$ = astCreate("DeclVarMulti", @2.first_line, 2, nID, nRest);
        }
    | /* vazio */ { $$ = astCreate("DeclVarMulti", @$.first_line, 0); }
    ;

DeclFunc
    : ABREPARENT ListaParametros FECHAPARENT Bloco
        {
            ASTNode *nLP = $2; ASTNode *nB = $4;
            $$ = astCreate("DeclFunc", @1.first_line, 2, nLP, nB);
        }
    ;

ListaParametros
    : /* vazio */ { $$ = astCreate("ListaParametros", @$.first_line, 0); }
    | ListaParametrosCont { $$ = $1; }
    ;

ListaParametrosCont
    : Tipo ID
        {
            ASTNode *nTipo = astCreate("Tipo", @1.first_line, 1, $1);
            ASTNode *nID   = astNewId($2, @2.first_line);
            $$ = astCreate("Param", @1.first_line, 2, nTipo, nID);
        }
    | Tipo ID VIRGULA ListaParametrosCont
        {
            ASTNode *nTipo = astCreate("Tipo", @1.first_line, 1, $1);
            ASTNode *nID   = astNewId($2, @2.first_line);
            ASTNode *nRest = $4;
            $$ = astCreate("ParamLista", @1.first_line, 3, nTipo, nID, nRest);
        }
    ;

Bloco
    : ABRECHAVE ListaDeclVar ListaComando FECHACHAVE
        {
            $$ = astCreate("Bloco", @1.first_line, 2, $2, $3);
        }
    ;

ListaDeclVar
    : /* vazio */ { $$ = astCreate("ListaDeclVar", @$.first_line, 0); }
    | Tipo ID DeclVar PONTOVIRGULA ListaDeclVar
        {
            ASTNode *nTipo   = astCreate("Tipo", @1.first_line, 1, $1);
            ASTNode *nID     = astNewId($2, @2.first_line);
            ASTNode *nDeclV  = $3;    /* resto DeclVar */
            ASTNode *nResto  = $5;    /* continuação ListaDeclVar */
            $$ = astCreate("DeclVarLocal", @1.first_line, 4, nTipo, nID, nDeclV, nResto);
        }
    ;

Tipo
    : INT
    | CAR
    ;

ListaComando
    : Comando { $$ = astCreate("ListaComando", @1.first_line, 1, $1); }
    | Comando ListaComando
        {
            $$ = astCreate("ListaComando", @1.first_line, 2, $1, $2);
        }
    ;

Comando
    : PONTOVIRGULA
        {
            $$ = astCreate("NoOp", @1.first_line, 0);
        }
    | Expr PONTOVIRGULA
        {
            $$ = astCreate("ExprStmt", @1.first_line, 1, $1);
        }
    | RETORNE Expr PONTOVIRGULA
        {
            $$ = astCreate("Return", @1.first_line, 1, $2);
        }
    | LEIA ID PONTOVIRGULA
        {
            ASTNode *nID = astNewId($2, @2.first_line);
            $$ = astCreate("Read", @1.first_line, 1, nID);
        }
    | ESCREVA Expr PONTOVIRGULA
        {
            $$ = astCreate("WriteExpr", @1.first_line, 1, $2);
        }
    | ESCREVA CONSTSTRING PONTOVIRGULA
        {
            ASTNode *nStr = astNewString($2, @2.first_line);
            $$ = astCreate("WriteString", @1.first_line, 1, nStr);
        }
    | NOVALINHA PONTOVIRGULA
        {
            $$ = astCreate("NewLine", @1.first_line, 0);
        }
    | SE ABREPARENT Expr FECHAPARENT ENTAO Comando
        {
            $$ = astCreate("If", @1.first_line, 2, $3, $6);
        }
    | SE ABREPARENT Expr FECHAPARENT ENTAO Comando SENAO Comando
        {
            $$ = astCreate("IfElse", @1.first_line, 3, $3, $6, $8);
        }
    | ENQUANTO ABREPARENT Expr FECHAPARENT EXECUTE Comando
        {
            $$ = astCreate("While", @1.first_line, 2, $3, $6);
        }
    | Bloco
        {
            $$ = astCreate("BlockStmt", @1.first_line, 1, $1);
        }
    ;


Expr
    : OrExpr
      {
        $$ = $1;
      }
    | ID RECEBE Expr
      {
        ASTNode *nID  = astNewId($1, @1.first_line);
        ASTNode *rhs  = $3;
        $$ = astCreate("Assign", @1.first_line, 2, nID, rhs);
      }
    ;

/* OrExpr: recursiva para “||” (ou “ou”) */
OrExpr
    : OrExpr OU AndExpr
      {
        $$ = astCreate("Or", @2.first_line, 2, $1, $3);
      }
    | AndExpr
      {
        $$ = $1;
      }
    ;

/* AndExpr: recursiva para “&&” (ou “e”) */
AndExpr
    : AndExpr E EqExpr
      {
        $$ = astCreate("And", @2.first_line, 2, $1, $3);
      }
    | EqExpr
      {
        $$ = $1;
      }
    ;

/* EqExpr: == ou != */
EqExpr
    : EqExpr EQ DesigExpr
      {
        $$ = astCreate("Eq", @2.first_line, 2, $1, $3);
      }
    | EqExpr NEQ DesigExpr
      {
        $$ = astCreate("Neq", @2.first_line, 2, $1, $3);
      }
    | DesigExpr { $$ = $1; }
    ;


DesigExpr
    : DesigExpr MENOR AddExpr
        {
            $$ = astCreate("Less", @2.first_line, 2, $1, $3);
        }
    | DesigExpr MAIOR AddExpr
        {
            $$ = astCreate("Greater", @2.first_line, 2, $1, $3);
        }
    | DesigExpr GEQ AddExpr
        {
            $$ = astCreate("Geq", @2.first_line, 2, $1, $3);
        }
    | DesigExpr LEQ AddExpr
        {
            $$ = astCreate("Leq", @2.first_line, 2, $1, $3);
        }
    | AddExpr { $$ = $1; }
    ;

AddExpr
    : AddExpr MAIS MulExpr
      {
        $$ = astCreate("Add", @2.first_line, 2, $1, $3);
      }
    | AddExpr MENOS MulExpr
      {
        $$ = astCreate("Sub", @2.first_line, 2, $1, $3);
      }
    | MulExpr { $$ = $1; }
    ;

/* MulExpr: *, / */
MulExpr
    : MulExpr VEZES UnExpr
      {
        $$ = astCreate("Mul", @2.first_line, 2, $1, $3);
      }
    | MulExpr DIVIDE UnExpr
      {
        $$ = astCreate("Div", @2.first_line, 2, $1, $3);
      }
    | UnExpr { $$ = $1; }
    ;

/* UnExpr: - ou ! unário */
UnExpr
    : MENOS PrimExpr
      {
        $$ = astCreate("Neg", @1.first_line, 1, $2);
      }
    | NEG PrimExpr
      {
        $$ = astCreate("Not", @1.first_line, 1, $2);
      }
    | PrimExpr { $$ = $1; }
    ;

PrimExpr
    : ID ABREPARENT ListExpr FECHAPARENT
      {
        ASTNode *nID   = astNewId($1,   @1.first_line);
        ASTNode *args  = $3;
        $$ = astCreate("Call", @1.first_line, 2, nID, args);
      }
    | ID ABREPARENT FECHAPARENT
      {
        ASTNode *nID = astNewId($1, @1.first_line);
        $$ = astCreate("CallNoArgs", @1.first_line, 1, nID);
      }
    | ID
      {
        $$ = astNewId($1, @1.first_line);
      }
    | CARCONST
      {
        $$ = astNewChar($1, @1.first_line);
      }
    | INTCONST
      {
        $$ = astNewInt($1, @1.first_line);
      }
    | ABREPARENT Expr FECHAPARENT
      {
        $$ = $2;
      }
    ;

ListExpr
    : Expr
      {
        $$ = astCreate("ArgList", @1.first_line, 1, $1);
      }
    | ListExpr VIRGULA Expr
      {
        $$ = astCreate("ArgList", @2.first_line, 2, $1, $3);
      }
    ;

%%

void yyerror(const char *s){
    fprintf(stderr, "ERRO: %s na linha %d\n", s, yylineno);
}

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "Uso correto: goianinha <arquivo>\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if(!yyin){
        fprintf(stderr, "Erro ao abrir arquivo %s\n", argv[1]);
        exit(1);
    }

    /* extern int yydebug;
    yydebug = 1;  */

    int result = yyparse(); 
    
    /* falha */
    if(result != 0){
        /* fprintf(stderr, "Análise sintática falhou com código: %d.\n", result); */
        return result;
    }

    printf("=== AST gerada ===\n");
    astPrint(raizAST, 0);
    astDestroy(raizAST);

    /* sucesso */
    printf("Análise sintática concluída com sucesso.\n");
    
    fclose(yyin);
    return result;
}
