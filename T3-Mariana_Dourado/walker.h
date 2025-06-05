#ifndef AST_WALKER_H
#define AST_WALKER_H

#include "ast.h"

// typedef struct {
//   int value;
//   const char *name;
// } map_enum_nome;

// static map_enum_nome cmd_map[] = {
//     {CMD_EXPR, "CMD_EXPR"},      
//     {CMD_RETORNE, "CMD_RETORNE"},
//     {CMD_LEIA, "CMD_LEIA"},
//     {CMD_ESCREVA, "CMD_ESCREVA"},
//     {CMD_CADEIACARACTERES, "CMD_CADEIACARACTERES"},
//     {CMD_NOVALINHA, "CMD_NOVALINHA"},
//     {CMD_SE, "CMD_SE"},
//     {CMD_SE_SENAO, "CMD_SE_SENAO"},
//     {CMD_ENQUANTO, "CMD_ENQUANTO"},
//     {CMD_BLOCO, "CMD_BLOCO"},
//     {-1, NULL}
// };

// static map_enum_nome expr_map[] = {
//     {EXPR_OR, "EXPR_OR"},
//     {EXPR_ATRIB, "EXPR_ATRIB"},
//     {EXPR_AND, "EXPR_AND"},
//     {EXPR_EQ, "EXPR_EQ"},
//     {EXPR_NEQ, "EXPR_NEQ"},
//     {EXPR_MENOR, "EXPR_MENOR"},
//     {EXPR_MAIOR, "EXPR_MAIOR"},
//     {EXPR_GEQ, "EXPR_GEQ"},
//     {EXPR_LEQ, "EXPR_LEQ"},
//     {EXPR_ADD, "EXPR_ADD"},
//     {EXPR_SUB, "EXPR_SUB"},
//     {EXPR_MULT, "EXPR_MULT"},
//     {EXPR_DIV, "EXPR_DIV"},
//     {EXPR_MINUS_NEG, "EXPR_MINUS_NEG"},
//     {EXPR_NOT, "EXPR_NOT"},
//     {EXPR_ID, "EXPR_ID"},
//     {EXPR_CHAR, "EXPR_CHAR"},
//     {EXPR_INTEGER, "EXPR_INTEGER"},
//     {EXPR, "EXPR"},
//     {-1, NULL}
// };

static map_enum_nome type_map[] = {{TYPE_INTEGER, "TYPE_INTEGER"},
                                       {TYPE_STRING, "TYPE_STRING"},
                                       {TYPE_FUNCTION, "TYPE_FUNCTION"},
                                       {-1, NULL}};

const char *enum_to_string(map_enum_nome *map, int value);

void walk_program(program_t *program);

void walk_block(block_t *block);

void walk_cmd(cmd_t *cmd);

void walk_expr(expr_t *expr);

#endif