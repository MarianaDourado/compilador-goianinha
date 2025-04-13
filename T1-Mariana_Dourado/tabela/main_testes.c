/* Realiza os testes das funções implementadas */

#include <stdio.h>
#include "estruturas.h"
#define TIPO_INT 1
#define TIPO_CHAR 2

int main() {
    initSymbolTableStack();
    
    printf("Criando escopo global...\n");
    pushTabelaSimbolos();
    
    // TESTE 1 - CRIAR VARIÁVEL GLOBAL
    printf("Inserindo variável 'x' no escopo global...\n");
    insereVariavel("x", TIPO_INT, 1); 

    printf("Inserindo variável 'outro_x' no escopo global...\n");
    insereVariavel("outro_x", TIPO_INT, 2); 

    // TESTE 2 - CRIAR FUNÇÃO
    printf("Criando escopo para função 'f'\n");
    // função 'f' com 2 parâmetros e tipo de retorno INT (1)
    int numParams = 2;
    Simbolo *simboloFuncao = insereFuncao("f", numParams, TIPO_INT);
    pushTabelaSimbolos();
    
    // TESTE 3 - INSERIR PARÂMETROS
    printf("Inserindo parâmetros 'p' (int) e 'q' (char) para a função 'f'\n");
    insereParametro("p", TIPO_INT, 1, simboloFuncao);
    insereParametro("q", TIPO_CHAR, 2, simboloFuncao);

    // TESTE 4 - INSERIR VARIAVEL DENTRO DA FUNÇÃO E PROCURAR
    printf("Inserindo variável 'y' no escopo da função 'f'...\n");
    insereVariavel("y", TIPO_INT, 1); 

    Simbolo *procura;
    procura = procuraSimbolo("y");
    if(procura)
        printf("Símbolo '%s' (y) encontrado no escopo.\n", procura->nome);
    else
        printf("Símbolo 'y' não encontrado (isso é um erro).\n");
    
    // TESTE 5 - PROCURAR POR VARIÁVEL NO ESCOPO GLOBAL, ESTANDO EM 'f'
    Simbolo *procura;
    procura = procuraSimbolo("x");
    if(procura)
        printf("Símbolo '%s' (x) encontrado no escopo (global).\n", procura->nome);
    else
        printf("Símbolo 'x' não encontrado (isso é um erro).\n");
    
    // TESTE 6 - PROCURAR POR PARÂMETRO
    procura = procuraSimbolo("p");
    if(procura)
        printf("Símbolo '%s' (p) encontrado (parâmetro da função 'f').\n", procura->nome);
    else
        printf("Símbolo 'p' não encontrado (isso é um erro).\n");
    
    // TESTE 7 - SAIR DO ESCOPO DE 'f'
    printf("Finalizando escopo da função 'f'\n");
    popTabelaSimbolos();
    
    // TESTE 8 - PROCURAR POR PARÂMETRO DE FUNÇÃO JÁ FECHADA
    procura = procuraSimbolo("p");
    if(procura)
        printf("Símbolo '%s' (p) encontrado após remoção do escopo (isso é um erro).\n", procura->nome);
    else
        printf("Símbolo 'p' não encontrado, conforme esperado, pois o escopo foi removido.\n");

    // TESTE 9 - PROCURAR POR VARIÁVEL DECLARADA DENTRO DE FUNÇÃO JÁ FECHADA
    procura = procuraSimbolo("y");
    if(procura)
        printf("Símbolo '%s' (y) encontrado após remoção do escopo (isso é um erro).\n", procura->nome);
    else
        printf("Símbolo 'y' não encontrado, conforme esperado, pois o escopo foi removido.\n");

    // TESTE 10 - PROCURAR POR VARIÁVEL NO ESCOPO GLOBAL, ESTANDO NO ESCOPO GLOBAL
    Simbolo *procura;
    procura = procuraSimbolo("outro_x");
    if(procura)
        printf("Símbolo '%s' (outro_x) encontrado no escopo (global).\n", procura->nome);
    else
        printf("Símbolo 'outro_x' não encontrado (isso é um erro).\n");    
    
    // TESTE 11 - INSERIR FUNÇÃO 'g' COM PARAMETRO 'x' DO TIPO CHAR E PROCURAR 'x'
    printf("Criando escopo para função 'g'\n");
    int numParams = 1;
    Simbolo *simboloFuncao = insereFuncao("g", numParams, TIPO_CHAR);
    pushTabelaSimbolos();
    
    printf("Inserindo parâmetro 'x' (char) dentro do escopo da função 'g'\n");
    insereParametro("x", TIPO_CHAR, 1, simboloFuncao);

    procura = procuraSimbolo("x");
    if(procura && procura->tipoDado==TIPO_CHAR)
        printf("Símbolo '%s' (x) do tipo %d encontrado.\n", procura->nome, procura->tipoDado);
    else if(procura)
        printf("Símbolo 'x' encontrado, mas é do tipo %d (erro: deveria ser char, isso é, 2).\n", procura->tipoDado);
    else
        printf("Símbolo 'x' não encontrado (isso é um erro)");

    printf("Finalizando escopo da função 'g'\n");
    popTabelaSimbolos();

    // TESTE 12 - Finalizar escopo global e destruir pilha
    printf("Finalizando escopo global...\n");
    popTabelaSimbolos();
    
    destroySymbolTableStack();
    
    return 0;
}
