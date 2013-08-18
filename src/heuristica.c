/*
 ============================================================================
 TRABALHO PRÁTICO 0 - Stable Marriage Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 HEURISITCA.C - Define as operações que realizarão o método heurístico e avaliarão a qualidade dos resultados através do índice de satisfabilidade
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>

#include "heuristica.h"
#include "lista.h"

#define SIM 1
#define NAO 0

//Calcula a satisfabilidade de uma lista após o algoritmo de casamento
float calcula_satisfabilidade(LISTA lista[], int n) {
    int i;
    NO* cursor;
    float satisf=0;
    for (i=1; i<=n; i++) {
        cursor = lista[i].inicio;
        satisf++; //O mínimo que pode estar é na primeira posição então incrementa
        while (cursor->item.valor != lista[i].casado_com_id) { //Continua incrementando somente se não estiver na primeira posição
            satisf++;
            cursor = cursor->proximo;
        }
    }
    return satisf /= n;
}

//Calcula a satisfabilidade após o algoritmo de casamento
float calcula_satisfabilidade_geral(float satisf_fem, float satisf_masc) {
    return (satisf_fem+satisf_masc)/2;
}

//Mostra os casais formados até agora
//Omite aqueles que não estão casados
void mostracasais(LISTA* mulher, LISTA* homem, int n) {
    int i;
    for (i=1; i<=n; i++)
        printf ("mulher %d casa com homem %d\n", i, mulher[i].casado_com_id);
    printf ("\n");
    getchar();
}

//Perorre a lista de preferência da mulher à procura das ids dos pretendentes conflitantes, retorna o que for mais interessante para a mulher
//O(n) pois percorre as prioridades da mulher
NO* desempata(LISTA* mulher, int id_homem1, int id_homem2) {
    NO* cursor;
    cursor = mulher->inicio; //Recebe a ordem de pretendentes que o interessado quer casar

    while (cursor != NULL) { //Percorre todos os pretendentes do interessado na lista de preferência

        if (cursor->item.valor == id_homem1) {
            return cursor;
        } else if(cursor->item.valor == id_homem2) {
            return cursor;
        }
        cursor = cursor->proximo;
    }

    return cursor; //Garante um retorno
}

//Retorna 1 se a pessoa estiver casada e 0 se não
int casado(LISTA* pretendente) {
    return pretendente->casado;
}

//Altera o estado de casado dentre dois casados para CASADOS
void casa(LISTA* pessoa1, int id_pessoa1, LISTA* pessoa2, int id_pessoa2) {
    pessoa1->casado_com_id = id_pessoa2;
    pessoa2->casado_com_id = id_pessoa1;
    pessoa1->casado = SIM;
    pessoa2->casado = SIM;
}

//Altera o estado de casado dentre dois casados para NÃO casados
void descasa(LISTA* pessoa1, LISTA* pessoa2) {
    pessoa1->casado_com_id = 0;
    pessoa2->casado_com_id = 0;
    pessoa1->casado = NAO;
    pessoa2->casado = NAO;
}

//Recebe a lista de preferencias de um homem e casa esse homem, respeitando critério de desempate da heurística
void casa_homem(LISTA homem[], LISTA mulher[], int i, int *qnt_solteiros) {

    NO* cursor = homem[i].inicio; //Percorrerá a lista de preferência do homem
    int id_homem = i; //Função tenta casar o homem atual
    int id_mulher = cursor->item.valor;

    //O(n)
    while (homem[i].casado == NAO && cursor != NULL) {

        //Verifica se a mulher está casada
        if (casado(&mulher[id_mulher])) {

            //Se ela está casada, ela escolhe o de sua maior preferência, nomeado como 'melhor_opcao'
            NO* melhor_opcao;
            melhor_opcao = desempata(&mulher[id_mulher], mulher[id_mulher].casado_com_id, id_homem);

            if (melhor_opcao->item.valor != mulher[id_mulher].casado_com_id) {
                //Se a melhor opção NÃO for com quem ela está casada atualmente, casa com a melhor opção

                //Descasa a mulher 'id_mulher' com o homem 'id_homem'
                descasa(&mulher[id_mulher], &homem[mulher[id_mulher].casado_com_id]); //Descasa o homem com quem a mulher está atualmente casada
                (*qnt_solteiros)++;
                //Casa homem 'melhor_opcao->item.valor' com mulher 'id_mulher'
                casa(&mulher[id_mulher], id_mulher, &homem[melhor_opcao->item.valor], melhor_opcao->item.valor); //Casa a melhor opção
                (*qnt_solteiros)--;
                return;

            } else {
                //Caso a melhor opção seja com quem ela está casada atualmente, passa para a próxima opção na lista de preferências do homem
                cursor = cursor->proximo;
                id_mulher = cursor->item.valor;
            }

        } else {
            //Caso a mulher não esteja casada, casa ela com o homem 'i', tal que i = id_homem
            casa(&mulher[id_mulher], id_mulher, &homem[id_homem], id_homem);
            (*qnt_solteiros)--;
            return;
        }

    }
    return;
}

//Casa dois grupos através do algoritmo de Gale-Stanley, onde os homens propõem e o critério de desempate de conflito é a preferência da mulher
void men_porpose_algorithm(LISTA mulher[], LISTA homem[], int n) {

    int i=1;
    int qnt_solteiros = n;

    //Casa todos os homens, o critério de desempate é o interesse da mulher sobre os dois pretendentes conflitantes

    //Enquanto houverem solteiros, percorrer todo o vetor de homens
    //O(n)
    while (qnt_solteiros > 0) {
        if (i > n) i = 1;
        casa_homem(homem, mulher, i, &qnt_solteiros); //Casa o homem i
        i++;
    }
}

