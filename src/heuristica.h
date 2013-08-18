/*
 ============================================================================
 TRABALHO PRÁTICO 0 - Stable Marriage Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 HEURISTICA.H - Descreve o cabeçalho da heurística e das funções que avaliarão a qualidade dos resultados através do índice de satisfabilidade
 ============================================================================
 */

#ifndef HEURISTICA_H_INCLUDED
#define HEURISTICA_H_INCLUDED

#include "lista.h"

/*###############################################################################################################################
#   Assinatura: void men_porpose_algorithm(LISTA mulher[], LISTA homem[], int n);
#   Definição: Casa esses dois grupos através do algoritmo de Gale-Stanley
#   Argumentos: Dois vetores de listas, homem e mulher
#   Premissas: A lista de mulher e de homem foi completamente povoada, n é verdadeiro
#   Ordem de Complexidade: O(n²), pois percorre as n preferências de n homens
################################################################################################################################*/
void men_porpose_algorithm(LISTA mulher[], LISTA homem[], int n);


/*###############################################################################################################################
#   Assinatura: float calcula_satisfabilidade(LISTA lista[], int n);
#   Definição: Calcula a satisfabilidade de uma lista após o algoritmo de casamento
#   Argumentos: Um vetor de listas, homem ou mulher
#   Saída: Satisfabilidade dessa lista com o casamento atual
#   Premissas: Todos estão casados e n é verdadeiro
#   Ordem de Complexidade: O(n²), pois percorre n listas preferências com n elementos cada
################################################################################################################################*/
float calcula_satisfabilidade(LISTA lista[], int n);


/*###############################################################################################################################
#   Assinatura: float calcula_satisfabilidade_geral(float satisf_fem, float satisf_masc);
#   Definição: Calcula a satisfabilidade geral entre duas listas após o casamento através da média aritmética das satisfabilidades dos grupos
#   Argumentos: Índice de satisfabilidade das mulheres e dos homens
#   Saída: Satisfabilidade geral
#   Premissas: As satisfabilidades estão corretas e não são nulas
#   Ordem de Complexidade: O(1), simples média aritmética entre 2 floats
################################################################################################################################*/
float calcula_satisfabilidade_geral(float satisf_fem, float satisf_masc);


#endif // HEURISTICA_H_INCLUDED
