//um arquivo header (.h) contendo a descricao das estruturas de dados utilizadas e prot´otipos das fun¸c˜oes que manipulam a pilha de tabela de s´ımbolos.

#ifndef TABELADESIMBOLOS_H
#define TABELADESIMBOLOS_H

typedef enum {
    SIMBOLO_FUNCAO,
    SIMBOLO_VARIAVEL,
    SIMBOLO_PARAMETRO
} tipoSimbolo;

typedef struct Simbolo {
    char *nome;                    // Nome do identificador 
    unsigned int posicao;          // Posição (para variável ou parâmetro na lista de declaração) 
    int tipoDado;                  // Tipo da variável ou função (pode ser, por exemplo, INT ou CAR) 
    int numParams;                 // Apenas para função: número de parâmetros 
    struct Simbolo *entradaFuncao;  // Apenas para parâmetro: aponta para a entrada da função a qual pertence 
    struct Simbolo *prox;           // Próximo símbolo na tabela (lista encadeada) 
    tipoSimbolo tipo;               // Tipo de símbolo: função, variável ou parâmetro 
} Simbolo;

typedef struct TabelaSimbolos {
    Simbolo *simbolos;
    struct TabelaSimbolos *prox;
} TabelaSimbolos;

// Ponteiro para o topo da pilha (escopo atual)
extern TabelaSimbolos *PilhaTabelaSimbolos;


// a) Inicia a pilha de tabelas de símbolos
void initPilhaTabelaSimbolos();

// b) Cria um novo escopo (tabela de símbolos) e empilha
void pushTabelaSimbolos();

// c) Pesquisa por um símbolo na pilha de tabelas de símbolos.
// Retorna um ponteiro para a entrada se encontrado ou NULL caso contrário.
Simbolo *procuraSimbolo(const char *nome);

// d) Remove o escopo atual (desempilha a tabela do topo)
void popTabelaSimbolos();

// e) Insere uma função na tabela de símbolos atual.
Simbolo *insereFuncao(const char *nome, int numParams, int tipoRetorno);

// f) Insere uma variável na tabela de símbolos atual.
Simbolo *insereVariavel(const char *nome, int tipoDado, unsigned int posicao);

// g) Insere um parâmetro na tabela de símbolos atual.
// Parâmetros: nome, tipo do parâmetro, posição na lista de parâmetros e ponteiro para a entrada da função à qual pertence.
Simbolo *insereParametro(const char *nome, int tipoDado, unsigned int posicao, Simbolo *entradaFuncao);

// h) Elimina a pilha de tabelas de símbolos
void destroiPilhaTabelaSimbolos();

#endif
