#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerenciador.h"


void inicializarTabela(TabelaDispersao* tabela) { // Inicializa a tabela de dispersão
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela->tabela[i] = NULL;
    }
}

int funcaoDispersao(int numero) { 
    return numero % TAMANHO_TABELA;
}

void inserirConcurso(TabelaDispersao* tabela, Concurso concurso) { // Insere um concurso na tabela de dispersão
    int indice = funcaoDispersao(concurso.numero);
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->concurso = concurso;
    novoNo->proximo = tabela->tabela[indice];
    tabela->tabela[indice] = novoNo;
}

Concurso* buscarConcurso(TabelaDispersao* tabela, int numero) { // Busca um concurso na tabela de dispersão
    int indice = funcaoDispersao(numero);
    No* atual = tabela->tabela[indice];
    while (atual != NULL) {
        if (atual->concurso.numero == numero) {
            return &atual->concurso;
        }
        atual = atual->proximo;
    }
    return NULL;
}

int removerConcurso(TabelaDispersao* tabela, int numero) { // Remove um concurso da tabela de dispersão
    int indice = funcaoDispersao(numero);
    No* atual = tabela->tabela[indice];
    No* anterior = NULL;
    while (atual != NULL) {
        if (atual->concurso.numero == numero) {
            if (anterior == NULL) {
                tabela->tabela[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return 1; // Retornar 1 se remoção bem-sucedida
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return 0; // se concurso não encontrado
}

void carregarConcursos(TabelaDispersao* tabela, const char* nomeArquivo) { // Carrega concursos de um arquivo (.csv ou .tsv)
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        Concurso concurso;
        sscanf(linha, "%d,%10[^,],%d,%d,%d,%d,%d,%d",
               &concurso.numero, concurso.data,
               &concurso.numeros[0], &concurso.numeros[1], &concurso.numeros[2],
               &concurso.numeros[3], &concurso.numeros[4], &concurso.numeros[5]);
        inserirConcurso(tabela, concurso);
    }

    fclose(arquivo);
}

int compararFrequencia(const void* a, const void* b) { // Compara a frequência de dois números
    return ((NumeroFrequencia*)b)->frequencia - ((NumeroFrequencia*)a)->frequencia;
}

void apresentarEstatisticas(TabelaDispersao* tabela, int numeroEspecifico, int anoEspecifico) { // Apresenta estatísticas sobre os concursos
    int quantidadeNumeroEspecifico = 0;
    int quantidadeConcursosAno = 0;
    
    NumeroFrequencia frequencias[60] = {0};
    for (int i = 0; i < 60; i++) {
        frequencias[i].numero = i + 1;
        frequencias[i].frequencia = 0;
    }

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        No* atual = tabela->tabela[i];
        while (atual != NULL) {
            Concurso concurso = atual->concurso;
            char anoStr[5];
            strncpy(anoStr, concurso.data + 6, 4);
            anoStr[4] = '\0';
            int ano = atoi(anoStr);
            if (ano == anoEspecifico) {
                quantidadeConcursosAno++;
            }
            for (int j = 0; j < 6; j++) {
                int numero = concurso.numeros[j];
                frequencias[numero - 1].frequencia++;
                if (numero == numeroEspecifico) {
                    quantidadeNumeroEspecifico++;
                }
            }
            atual = atual->proximo;
        }
    }

    qsort(frequencias, 60, sizeof(NumeroFrequencia), compararFrequencia);

    printf("Quantidade de vezes que o número %d foi sorteado: %d\n", numeroEspecifico, quantidadeNumeroEspecifico);
    printf("Dez números mais sorteados:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d: %d vezes\n", frequencias[i].numero, frequencias[i].frequencia);
    }

    printf("Dez números menos sorteados:\n");
    for (int i = 59; i >= 50; i--) {
        printf("%d: %d vezes\n", frequencias[i].numero, frequencias[i].frequencia);
    }

    printf("Quantidade de concursos no ano %d: %d\n", anoEspecifico, quantidadeConcursosAno);
}