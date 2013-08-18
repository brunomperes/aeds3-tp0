/*
 ============================================================================
 TRABALHO PR�TICO 0 - Stable Marriage Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 MAIN.C - Cont�m as fun��es de entrada e sa�da do algoritmo, aloca��o de mem�ria necess�ria e chamada da fun��o principal da heur�stica
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "heuristica.h"

#define SIM 1
#define NAO 0

//L� um n�mero inteiro de um arquivo aberto como leitura
int LeInt(FILE *ArqEntrada) {
    int x;

    //Leitura efetiva do arquivo
    fscanf(ArqEntrada, "%d", &x); //Escreve na vari�vel x o conte�do lido do arquivo

    return x;
}

//Faz a leitura das ids de prefer�ncia dos homens e das mulheres do arquivo de entrada
void LeituraInput(FILE* entrada, int n, LISTA mulher[], LISTA homem[]) {

    int i,j; //i=contador de ids e j=contador de linhas
    ITEM novo_no;

    //L� as ids de todos os homens
    for (j=1; j<=n; j++) {
        for (i=1; i<=n; i++) {
            //Preencher o novo n� com valores iniciais
            novo_no.valor = LeInt(entrada);
            novo_no.indice = i; //id atual do homem e �ndice dentro da lista
            if(!(lista_inserir_fim(&homem[j], &novo_no))) exit(1); //Escreve na lista 'mulher' as ids de prefer�ncia de cada mulher, finaliza o programa em caso de erro
        }
    }
    //L� as ids de todas as mulheres
    for (j=1; j<=n; j++) {
        for (i=1; i<=n; i++) {
            //Preencher o novo n� com valores iniciais
            novo_no.indice = i; //id atual do homem, �ndice dentro da lista
            novo_no.valor = LeInt(entrada);
            if(!(lista_inserir_fim(&mulher[j], &novo_no))) exit(1); //Escreve na lista 'homem' as ids de prefer�ncia de cada homem, finaliza o programa em caso de erro
        }
    }

}

//Escreve no arquivo output.txt os casais formados por suas ids, a satisfabilidade geral, satisfabilidade masculina e satisfabilidade feminina separados por uma quebra de linha
void EscreveResultados(LISTA mulher[], LISTA homem[], int n, float satisf_fem, float satisf_masc, float satisf_geral) {
    FILE * Saida;

    Saida = fopen ("output.txt","a");

    int i;

    for (i=1; i<=n; i++) {
        fprintf (Saida, "%d %d\n", i, homem[i].casado_com_id); //Escreve a id de homem e da mulher c�njuges separados por um espa�o simples
    }

    fprintf (Saida, "%.3f\n", satisf_geral); //Satisfabilidade Geral
    fprintf (Saida, "%.3f\n", satisf_masc); //Satisfabilidade Masculina
    fprintf (Saida, "%.3f\n", satisf_fem); //Satisfabilidade Feminina

    fclose (Saida);
}

//Imprime o conte�do de duas listas de tamanho n
void imprimir_duas_listas(LISTA *mulher, LISTA *homem, int n) {
    int i;
    printf("Lista de mulheres\n");
    for (i=1; i<=n; i++) { //L� as ids de todas as mulheres
        printf ("[%d] ",i);
        lista_imprimir(&mulher[i]);
    }
    printf("\nLista de homens\n");
    for (i=1; i<=n; i++) { //L� as ids de todas as mulheres
        printf ("[%d] ",i);
        lista_imprimir(&homem[i]);
    }
    printf("\n");
}


int main(int argc, char *argv[]) {

    //Verifica se a quantidade de argumentos passados � fun��o est� correto
    if (argc < 2) {
        printf("[ERRO] Numero incorreto de parametros!\n- Favor incluir o nome do arquivo de entrada\n\n");
        exit(1); //Finaliza o programa com status de erro

        //argv[0] == chamada do programa:  ./tp0
        //argv[1] == nome do arquivo de entrada ex.: "input.txt"

    }

    char* nomeArqEntrada = argv[1]; //Recebe o conte�do do argumento, nome do arquivo de entrada

    int i,j; //Contadores simples utilizados v�rias vezes
    int n; //Quantidade de elementos em cada lista e tamanho do vetor de listas

    //Manter um arquivo aberto para evitar ter q percorrer todo o arquivo cada vez que precisar de um dado espec�fico
    FILE *ArqEntrada = fopen(nomeArqEntrada, "r");
    if (ArqEntrada == NULL) {
        printf("\n[ERRO] Problema ao abrir o arquivo de entrada\nVerifique se o nome do arquivo passado como argumento realmente existe\n\n");
        exit(1); //Finaliza o programa com status de erro
    }

    //Limpa o arquivo de sa�da
    FILE * Saida = fopen ("output.txt","w");
    fclose (Saida);

    //Le a quantidade de inst�ncias do arquivo de entrada
    int instancias = LeInt(ArqEntrada);

    //Executa 'instancias' vezes
    for (j=0; j<instancias; j++) {

        n = LeInt(ArqEntrada); //L� o n�mero n de ind�viduos no conjunto

        //Criar vetor de listas alocadas dinamicamente que representa as MULHERES e seus interesses
        LISTA * mulher;
        mulher = (LISTA *)malloc((n+1) * sizeof (LISTA)); //Aloca um vetor de listas para guardar as ids de prefer�ncias de n mulheres
        if (mulher == NULL) exit (1); //Finaliza o programa com status de erro
        for (i = 0; i <= n; i++)
            lista_criar(&mulher[i]);
        //Criar vetor de listas alocadas dinamicamente que representa as HOMENS e seus interesses
        LISTA * homem;
        homem = (LISTA *)malloc((n+1) * sizeof (LISTA)); //Aloca um vetor de listas para guardar as ids de prefer�ncias de n homens
        if (homem == NULL) exit (1); //Finaliza o programa com status de erro
        for (i = 0; i <= n; i++)
            lista_criar(&homem[i]);

        //Povoar as listas de homens e de mulheres
        LeituraInput(ArqEntrada, n, mulher, homem);

        //Heur�stica
        men_porpose_algorithm(mulher, homem, n);

        //Calcular Satisfabilidades
        float satisf_masc = calcula_satisfabilidade(homem, n);
        float satisf_fem = calcula_satisfabilidade(mulher, n);
        float satisf_geral = calcula_satisfabilidade_geral(satisf_masc, satisf_fem);

        //Escreve os resultados no arquivo
        EscreveResultados(mulher, homem, n, satisf_fem, satisf_masc, satisf_geral);

        //Libera��o da mem�ria alocada para as listas de homem e de mulher
        for (i=0; i<=n; i++) {
            lista_apagar(&homem[i]);
            lista_apagar(&mulher[i]);
        }
        lista_apagar(homem);
        lista_apagar(mulher);
        free(homem);
        free(mulher);

    }

    fclose(ArqEntrada);

    return 0;
}
