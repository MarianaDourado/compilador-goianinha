#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>

/*
 * ASTNode: estrutura genérica de um nó da árvore sintática abstrata.
 *
 * Cada nó possui:
 *   - label: rótulo/descrição do nó (por ex. "Programa", "If", "Expr", "ID", etc).
 *   - string: usado em nós‐folha que carregam literais ou identificadores (ID, CONSTSTRING).
 *   - intval: usado em nós‐folha para inteiros (INTCONST).
 *   - charval: usado em nós‐folha para constantes de caractere (CARCONST).
 *   - line: número da linha no fonte onde esse nó foi gerado (para mensagens de erro).
 *   - children: vetor de ponteiros para nós‐filho.
 *   - nChildren: número de filhos.
 */
typedef struct ASTNode {
    char      *label;
    char      *string;    /* só válido se esse nó for ID ou CONSTSTRING */
    int        intval;    /* só válido se esse nó for INTCONST */
    char       charval;   /* só válido se esse nó for CARCONST */
    int        line;
    struct ASTNode **children;
    int        nChildren;
} ASTNode;


/* 
 * Cria um nó genérico, com rótulo `label`, linha `line` e exatamente `nChildren` filhos.
 * Os filhos são passados via varargs, na ordem em que devem ficar em children[0..nChildren-1].
 *
 * Exemplo de uso:
 *    ASTNode *filho1 = ...;
 *    ASTNode *filho2 = ...;
 *    ASTNode *pai   = astCreate("If", linha_if, 2, filho1, filho2);
 *
 * Atenção: em nós onde se queira guardar um valor literal (ID, INTCONST, CARCONST, CONSTSTRING),
 * recomenda‐se usar astNewId, astNewInt, astNewChar ou astNewString, em vez de astCreate diretamente.
 */
ASTNode *astCreate(const char *label, int line, int nChildren, ...);

/*
 * Cria um nó‐folha que representa um identificador (ID). A string `name` já deve vir alocada (strdup).
 * Exemplo de uso em Bison:
 *    { $$ = astNewId($1, @1.first_line); }
 */
ASTNode *astNewId(char *name, int line);

/*
 * Cria um nó‐folha que representa um inteiro literal (INTCONST).
 * Exemplo de uso em Bison:
 *    { $$ = astNewInt($1, @1.first_line); }
 */
ASTNode *astNewInt(int value, int line);

/*
 * Cria um nó‐folha que representa um caractere literal (CARCONST).
 * Exemplo de uso em Bison:
 *    { $$ = astNewChar($1, @1.first_line); }
 */
ASTNode *astNewChar(char value, int line);

/*
 * Cria um nó‐folha que representa uma string literal (CONSTSTRING).
 * A string `value` já deve vir alocada (strdup), incluindo as aspas caso deseje mantê‐las.
 * Exemplo:
 *    { $$ = astNewString($1, @1.first_line); }
 */
ASTNode *astNewString(char *value, int line);

/*
 * Destrói recursivamente toda a árvore enraizada em `node`, liberando memória.
 */
void astDestroy(ASTNode *node);

/*
 * Imprime (para stdout) a subárvore enraizada em `node`, recuando `level` espaços
 * a cada nível, para fins de debug ou visualização.
 */
void astPrint(ASTNode *node, int level);

#endif /* AST_H */
