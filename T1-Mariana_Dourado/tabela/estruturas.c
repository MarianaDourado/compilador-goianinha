// um arquivo com as implementa¸c˜oes das fun¸c˜oes ( arquivo .c ou .c++)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

TabelaSimbolos *PilhaTabelaSimbolos = NULL;

void initPilhaTabelaSimbolos(){
    PilhaTabelaSimbolos = NULL;
}

void pushTabelaSimbolos(){
    TabelaSimbolos *novaTabela = (TabelaSimbolos *) malloc(sizeof(TabelaSimbolos));
    if(!novaTabela){
        fprintf(stderr, "Erro: falha ao alocar memória para nova tabela de símbolos.\n");
        exit(EXIT_FAILURE);
    }
    novaTabela->simbolos = NULL;
    novaTabela->prox = PilhaTabelaSimbolos;
    PilhaTabelaSimbolos = novaTabela;
}

Simbolo *procuraSimbolo(const char *nome){
    TabelaSimbolos *tabela = PilhaTabelaSimbolos;
    while(tabela){
        Simbolo *simboloAtual = tabela->simbolos;
        while(simboloAtual){
            if(strcmp(simboloAtual->nome, nome) == 0)
                return simboloAtual;
            simboloAtual = simboloAtual->prox;
        }
        tabela = tabela->prox;
    }
    return NULL;
}

void popTabelaSimbolos(){
    if(PilhaTabelaSimbolos == NULL)
        return;
    TabelaSimbolos *top = PilhaTabelaSimbolos;
    Simbolo *simboloAtual = top->simbolos;
    while(simboloAtual){
        Simbolo *temp = simboloAtual;
        simboloAtual = simboloAtual->prox;
        free(temp->nome);
        free(temp);
    }
    PilhaTabelaSimbolos = top->prox;
    free(top);
}

// funções auxiliares pra inserir função, variável ou parâmetro
Simbolo *criaSimbolo(const char *nome, tipoSimbolo tipo, int tipoDado, int posicao, int numParams, Simbolo *entradaFuncao){
    Simbolo *simboloAtual = (Simbolo*) malloc(sizeof(Simbolo));
    if(!simboloAtual){
        fprintf(stderr, "Erro: falha ao alocar memória para novo símbolo.\n");
        exit(EXIT_FAILURE);
    }
    simboloAtual->nome = strdup(nome);
    if(!simboloAtual->nome){
        fprintf(stderr, "Erro: falha ao duplicar nome do símbolo.\n");
        free(simboloAtual);
        exit(EXIT_FAILURE);
    }
    simboloAtual->tipo = tipo;
    simboloAtual->tipoDado = tipoDado;
    simboloAtual->posicao = posicao;
    simboloAtual->numParams = numParams;
    simboloAtual->entradaFuncao = entradaFuncao;
    simboloAtual->prox = NULL;
    return simboloAtual;
}

Simbolo *insereSimbolo(Simbolo *novoSimbolo){
    if(PilhaTabelaSimbolos == NULL){
        fprintf(stderr, "Erro: nenhuma tabela de símbolos encontrada (pilha vazia).\n");
        exit(EXIT_FAILURE);
    }
    // insere no início da lista da tabela atual
    novoSimbolo->prox = PilhaTabelaSimbolos->simbolos;
    PilhaTabelaSimbolos->simbolos = novoSimbolo;
    return novoSimbolo;
}
// fim das funções auxiliares

Simbolo *insereFuncao(const char *nome, int numParams, int tipoRetorno){
    Simbolo *simboloAtual = criaSimbolo(nome, SIMBOLO_FUNCAO, tipoRetorno, 0, numParams, NULL);
    return insereSimbolo(simboloAtual);
}

Simbolo *insereVariavel(const char *nome, int tipoDado, unsigned int posicao){
    Simbolo *simboloAtual = criaSimbolo(nome, SIMBOLO_VARIAVEL, tipoDado, posicao, 0, NULL);
    return insereSimbolo(simboloAtual);
}

Simbolo *insereParametro(const char *nome, int tipoDado, unsigned int posicao, Simbolo *entradaFuncao){
    Simbolo *simboloAtual = criaSimbolo(nome, SIMBOLO_PARAMETRO, tipoDado, posicao, 0, entradaFuncao);
    return insereSimbolo(simboloAtual);
}

void destroiPilhaTabelaSimbolos(){
    while(PilhaTabelaSimbolos){
        popTabelaSimbolos();
    }
}
