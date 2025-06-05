#ifndef AST_H
#define AST_H

// #include "../tabela_simbolos.h"
// #include "../token.h" // fazer depois se precisar 


typedef enum {
  CMD_EXPR,
  CMD_RETORNE,
  CMD_LEIA,
  CMD_ESCREVA,
  CMD_CADEIACARACTERES,
  CMD_NOVALINHA,
  CMD_SE,
  CMD_SE_SENAO,
  CMD_ENQUANTO,
  CMD_BLOCO
} comando_enum;

typedef enum {
  EXPR_OR,
  EXPR_ATRIB, // id=Expr
  EXPR_AND,
  EXPR_EQ,
  EXPR_NEQ,
  EXPR_MENOR,
  EXPR_MAIOR,
  EXPR_GEQ,
  EXPR_LEQ,
  EXPR_ADD,
  EXPR_SUB,
  EXPR_MULT,
  EXPR_DIV,
  EXPR_MINUS_NEG,
  EXPR_NOT,
  EXPR_ID,
  EXPR_CHAR,
  EXPR_INTEGER,
  EXPR
} expr_enum;


//TODO: Struct ID {nome, tipo} :

typedef struct Programa {
    DeclFuncVar *declFuncVar;
    DeclProg *declProg;
} Programa;

typedef struct DeclFuncVar {
    type_t tipo;
    char *id;
    DeclVar *declVar;
    DeclFuncVar *declFuncVar;
    DeclFunc *declFunc;
 } DeclFuncVar;

typedef struct DeclProg {  // meio inutil, mas vou manter pela redibilidade
    Bloco *bloco;
} DeclProg;

typedef struct DeclVar {
  char *id;
  DeclVar *declVar;
} DeclVar;

typedef struct DeclFunc {
  ListaParametros *listaParametros;
  Bloco *bloco;
} DeclFunc;

typedef struct ListaParametros {
    type_t tipo;
    char *id; 
    ListaParametros *listaParametros; // pode ser vazio obviamente
} ListaParametros;

typedef struct Bloco {
    ListaDeclVar *listaDeclVar;
    Comando *comando; //ListaComando
} Bloco;

typedef struct ListaDeclVar {
    type_t tipo;
    char *id;
    DeclVar *declVar;
    ListaDeclVar *listaDeclVar;
} ListaDeclVar;

typedef enum {
    TYPE_INTEGER,
    TYPE_CHAR,
    // TYPE_FUNCTION, // TODO: n precisa se pa?
} type_t;

// TODO START
typedef struct Comando { // UNION
    comando_enum tipo;
    union {
        Expr *expr; // para retorne, escreva, ...
        
        char *id; // para leia

        char *cadeiaCaracteres; // para escreva

        struct {
            Expr *expr_cond;
            Comando *comando_entao;
            Comando *comando_senao;
        } if_stmt;

        struct {
            Expr *expr_cond;
            Comando *comando_enquanto;
        } while_stmt;

        Bloco *bloco;
    };
} Comando;

typedef struct Expr { // UNION
    expr_enum tipo;

    Expr *esq;
    Expr *dir;

    union {
        struct {
            char *id;
            expr_enum *expr;
        } atribui;

        char carconst;
        int intconst;
        const char *id;
    };

    Expr *expr_list;

} Expr;

#endif