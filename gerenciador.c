#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerenciador.h"

void inicializarTabela(TabelaDispersao* tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela->tabela[i] = NULL;
    }
}

int funcaoDispersao(int numero) {
    return numero % TAMANHO_TABELA;
}

void inserirConcurso(TabelaDispersao* tabela, Concurso concurso) {
    int indice = funcaoDispersao(concurso.numero);
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->concurso = concurso;
    novoNo->proximo = tabela->tabela[indice];
    tabela->tabela[indice] = novoNo;
}

Concurso* buscarConcurso(TabelaDispersao* tabela, int numero) {
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

void removerConcurso(TabelaDispersao* tabela, int numero) {
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
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

void carregarConcursos(TabelaDispersao* tabela, const char* nomeArquivo) {
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

void apresentarEstatisticas(TabelaDispersao* tabela) {
    // Implementar funções para calcular e apresentar estatísticas
}