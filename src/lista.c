/*
 ============================================================================
 TRABALHO PRÁTICO 0 - Stable Marriage Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 LISTA.C - Define as funções que operam sobre o TAD lista adequado às necessidades do algoritmo
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

#define SIM 1
#define NAO 0

//Cria uma lista vazia em O(1)
void lista_criar(LISTA *lista) {
    lista->inicio = NULL;
    lista->casado = NAO;
    lista->casado_com_id = 0;
    lista->fim = NULL;
}

//Verifica se uma lista está vazia em O(1)
int lista_vazia(LISTA *lista) {
    if (lista->inicio == NULL && lista->fim==NULL) return SIM;
    else return NAO;
}

//Apaga uma lista em O(n)
void lista_apagar(LISTA *lista) {
    if (!lista_vazia(lista)) {
        NO *paux = lista->inicio;

        while (paux != NULL) {
            NO *prem = paux;
            paux = paux->proximo;
            free(prem);
        }
    }

    lista->inicio = NULL;
    lista->fim = NULL;

}

//Push_front, O(1). Retorna 0 em caso de erro
int lista_inserir_inicio(LISTA *lista, ITEM *item) {
    NO *pnovo = (NO *)malloc(sizeof(NO)); //crio um novo nó

    if (pnovo != NULL) { //verifica se existe memória disponível
        //preenche o os dados
        pnovo->item = *item;
        pnovo->proximo = lista->inicio;
        pnovo->anterior = NULL;
        if (lista->inicio != NULL) {
            lista->inicio->anterior = pnovo;
        } else {
            lista->fim = pnovo; //ajusta ponteiro para fim
        }

        lista->inicio = pnovo; //ajusta ponteiro início

        return 1;

    } else {
        //Em caso de erro
        return 0;
    }
}

//Push_back, O(1). Retorna 0 em caso de erro
int lista_inserir_fim(LISTA *lista, ITEM *item) {
    NO *pnovo = (NO *)malloc(sizeof(NO)); //Cria um novo nó

    if (pnovo != NULL) { //Verifica se existe memória disponível
        //Preenche os dados do nó
        pnovo->item = *item;
        pnovo->proximo = NULL;
        pnovo->anterior = lista->fim;

        if (lista->fim != NULL) {
            lista->fim->proximo = pnovo;
        } else {
            lista->inicio = pnovo; //Ajusta ponteiro para início
        }

        lista->fim = pnovo; //Ajusta ponteiro fim

        return 1;

    } else {
        //Em caso de erro
        return 0;
    }
}

//Busca um valor contido em um nó em O(n)
NO* lista_busca(LISTA* lista, int valor_procurado) {
    NO* cursor = lista->inicio;
    while (cursor->item.valor != valor_procurado && cursor != NULL) {
        cursor = cursor->proximo;
    }
    return cursor;
}

//Imprime os valores de nó de uma lista encadeada
void lista_imprimir(LISTA *lista) {
    NO* aux;
    aux = lista->inicio;
    if (!lista_vazia(lista)) {
        printf ("%d ", aux->item.valor); //Mostra o 1º valor
        aux = aux->proximo ;
        while (aux != NULL ) {
            printf ("%d ", aux->item.valor);
            if (aux->proximo != NULL) aux = aux->proximo ;
            else break;
        }
        printf("\n");
    } else printf("Lista vazia\n");
}
