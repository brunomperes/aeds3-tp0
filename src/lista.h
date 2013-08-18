/*
 ============================================================================
 TRABALHO PRÁTICO 0 - Stable Marriage Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 LISTA.H - Define as estruturas de dados e cabeçalhos das funções relacionadas às operações sobre o TAD lista
 ============================================================================
 */

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

//Guarda o conteúdo relativo ao nó (preferência da pessoa)
typedef struct {
    int indice; //Indica se é o 1º elemento, 2º elemento. É utilizado para buscas e calcular o índice de satisfabilidade
    int valor; //Armazena a id do pretendente
} ITEM;

//Armazena os ponteiros para o próximo e para o nó anterior, além de uma estrutura contendo valores relativos à preferência da pessoa
typedef struct NO {
    ITEM item;
    struct NO *proximo;
    struct NO *anterior;
} NO;

//Define a lista, que representará uma pessoa
typedef struct {
    int casado;
    int casado_com_id; //id do pretendente com o qual o interessado casou-se
    NO *inicio;
    NO *fim;
} LISTA;

//Cria uma lista vazia em O(1)
void lista_criar(LISTA *lista);

//Verifica se uma lista está vazia em O(1)
int lista_vazia(LISTA *lista);

//Apaga uma lista em O(n)
void lista_apagar(LISTA *lista);

//Push_front, O(1). Retorna 0 em caso de erro
int lista_inserir_inicio(LISTA *lista, ITEM *item);

//Push_back, O(1). Retorna 0 em caso de erro
int lista_inserir_fim(LISTA *lista, ITEM *item);

//Busca um valor contido em um nó em O(n)
NO* lista_busca(LISTA* lista, int valor);

//Imprime os valores de nó de uma lista encadeada
void lista_imprimir(LISTA *lista);

#endif // LIST_H_INCLUDED
