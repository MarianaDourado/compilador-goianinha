#include "ast.h"
#include <stdarg.h>
#include <string.h>

/* ------------------------------------------------------------
 * astCreate: cria nó genérico com label e nChildren filhos
 * ------------------------------------------------------------ */
ASTNode *astCreate(const char *label, int line, int nChildren, ...)
{
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: falha ao alocar ASTNode\n");
        exit(EXIT_FAILURE);
    }

    node->label     = strdup(label);
    node->string    = NULL;
    node->intval    = 0;
    node->charval   = 0;
    node->line      = line;
    node->nChildren = nChildren;

    if (nChildren > 0) {
        node->children = (ASTNode **) malloc(sizeof(ASTNode *) * nChildren);
        if (!node->children) {
            fprintf(stderr, "Erro: falha ao alocar array de children\n");
            exit(EXIT_FAILURE);
        }

        va_list ap;
        va_start(ap, nChildren);
        for (int i = 0; i < nChildren; i++) {
            ASTNode *filho = va_arg(ap, ASTNode *);
            node->children[i] = filho;
        }
        va_end(ap);
    } else {
        node->children = NULL;
    }

    return node;
}

/* ------------------------------------------------------------
 * astNewId: cria nó‐folha para identificador (ID)
 * ------------------------------------------------------------ */
ASTNode *astNewId(char *name, int line)
{
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: falha ao alocar ASTNode (ID)\n");
        exit(EXIT_FAILURE);
    }

    node->label     = strdup("ID");
    node->string    = strdup(name);
    node->intval    = 0;
    node->charval   = 0;
    node->line      = line;
    node->nChildren = 0;
    node->children  = NULL;
    return node;
}

/* ------------------------------------------------------------
 * astNewInt: cria nó‐folha para inteiro literal (INTCONST)
 * ------------------------------------------------------------ */
ASTNode *astNewInt(int value, int line)
{
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: falha ao alocar ASTNode (INTCONST)\n");
        exit(EXIT_FAILURE);
    }

    node->label     = strdup("INTCONST");
    node->string    = NULL;
    node->intval    = value;
    node->charval   = 0;
    node->line      = line;
    node->nChildren = 0;
    node->children  = NULL;
    return node;
}

/* ------------------------------------------------------------
 * astNewChar: cria nó‐folha para caractere literal (CARCONST)
 * ------------------------------------------------------------ */
ASTNode *astNewChar(char value, int line)
{
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: falha ao alocar ASTNode (CARCONST)\n");
        exit(EXIT_FAILURE);
    }

    node->label     = strdup("CARCONST");
    node->string    = NULL;
    node->intval    = 0;
    node->charval   = value;
    node->line      = line;
    node->nChildren = 0;
    node->children  = NULL;
    return node;
}

/* ------------------------------------------------------------
 * astNewString: cria nó‐folha para string literal (CONSTSTRING)
 * ------------------------------------------------------------ */
ASTNode *astNewString(char *value, int line)
{
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: falha ao alocar ASTNode (CONSTSTRING)\n");
        exit(EXIT_FAILURE);
    }

    node->label     = strdup("CONSTSTRING");
    node->string    = strdup(value);
    node->intval    = 0;
    node->charval   = 0;
    node->line      = line;
    node->nChildren = 0;
    node->children  = NULL;
    return node;
}

/* ------------------------------------------------------------
 * astDestroy: libera recursivamente toda a subárvore
 * ------------------------------------------------------------ */
void astDestroy(ASTNode *node)
{
    if (!node) return;

    if (node->label) free(node->label);
    if (node->string) free(node->string);

    for (int i = 0; i < node->nChildren; i++) {
        astDestroy(node->children[i]);
    }
    if (node->children) free(node->children);
    free(node);
}

/* ------------------------------------------------------------
 * astPrint: imprime recursivamente a subárvore para debug
 * ------------------------------------------------------------ */
void astPrint(ASTNode *node, int level)
{
    if (!node) return;

    /* imprime recuo */
    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    /* imprime este nó */
    if (strcmp(node->label, "ID") == 0) {
        printf("%s (\"%s\") [linha %d]\n", node->label, node->string, node->line);
    } else if (strcmp(node->label, "INTCONST") == 0) {
        printf("%s (%d) [linha %d]\n", node->label, node->intval, node->line);
    } else if (strcmp(node->label, "CARCONST") == 0) {
        printf("%s ('%c') [linha %d]\n", node->label, node->charval, node->line);
    } else if (strcmp(node->label, "CONSTSTRING") == 0) {
        printf("%s (\"%s\") [linha %d]\n", node->label, node->string, node->line);
    } else {
        printf("%s [linha %d]\n", node->label, node->line);
    }

    /* imprime filhos */
    for (int i = 0; i < node->nChildren; i++) {
        astPrint(node->children[i], level + 1);
    }
}
