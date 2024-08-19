#include <stdio.h>
#include "gerenciador.h"

void menu() { // Menu de opções
    printf("========================================\n");
    printf("1. Inserir Concurso\n");
    printf("2. Buscar Concurso\n");
    printf("3. Remover Concurso\n");
    printf("4. Visualizar Todos os Concursos\n");
    printf("5. Carregar Concursos de um Arquivo\n");
    printf("6. Apresentar Estatísticas\n");
    printf("7. Sair\n");
    printf("========================================\n");
}

int main() {
    TabelaDispersao tabela;
    inicializarTabela(&tabela);

    int opcao;
    do {
        menu();
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) { //Caso a entrada seja inválida
        while (getchar() != '\n');
        printf("Opção inválida. Por favor, tente novamente.\n");
        continue;
        }

        switch (opcao) { // Switch case para as opções
            case 1: { // Insere um concurso
                Concurso concurso;
                printf("Número do Concurso: ");
                scanf("%d", &concurso.numero);
                if (buscarConcurso(&tabela, concurso.numero) != NULL) { // Verifica se o concurso já existe 
                    printf("Esse concurso já existe, adicionar irá sobrescrever o existente. Tem certeza que quer continuar? (S/N)\n");
                    char resposta;
                    scanf(" %c", &resposta);
                    if (resposta != 'S' && resposta != 's') {
                        printf("Operação cancelada.\n");
                        break;
                    }
                }
                printf("Data do Sorteio (dd-mm-aaaa): ");
                scanf("%s", concurso.data);
                printf("Números Sorteados: ");
                for (int i = 0; i < 6; i++) {
                    scanf("%d", &concurso.numeros[i]);
                }
                inserirConcurso(&tabela, concurso);
                printf("\nConcurso inserido com sucesso.\n");
                break;
        }
            case 2: { // Busca um concurso
                int numero;
                printf("Número do Concurso: ");
                scanf("%d", &numero);
                Concurso* concurso = buscarConcurso(&tabela, numero);
                if (concurso != NULL) {
                    printf("Concurso %d: Data %s, Números: %d %d %d %d %d %d\n",
                           concurso->numero, concurso->data,
                           concurso->numeros[0], concurso->numeros[1], concurso->numeros[2],
                           concurso->numeros[3], concurso->numeros[4], concurso->numeros[5]);
                } else {
                    printf("Concurso não encontrado.\n");
                }
                break;
            }
            case 3: { // Remove um concurso
                int numero;
                printf("Número do Concurso: ");
                scanf("%d", &numero);
                removerConcurso(&tabela, numero);
                if (removerConcurso(&tabela, numero) == 1) {
                    printf("Remoção bem sucedida");
                } else {
                    printf("Concurso não encontrado \n \n");
                }
                break;
            }
            case 4: { // Visualiza todos os concursos
                for (int i = 0; i < TAMANHO_TABELA; i++) {
                    No* atual = tabela.tabela[i];
                    while (atual != NULL) {
                        Concurso* concurso = &atual->concurso;
                        printf("Concurso %d: Data %s, Números: %d %d %d %d %d %d\n",
                               concurso->numero, concurso->data,
                               concurso->numeros[0], concurso->numeros[1], concurso->numeros[2],
                               concurso->numeros[3], concurso->numeros[4], concurso->numeros[5]);
                        atual = atual->proximo;
                    }
                }
                break;
            }
            case 5: { // Carrega concursos de um arquivo
                char nomeArquivo[256];
                printf("Nome do Arquivo (ex: data/sorteios.csv): ");
                scanf("%s", nomeArquivo);
                carregarConcursos(&tabela, nomeArquivo);
                printf("Concursos carregados com sucesso.\n");
                break;
            }
            case 6: { // Apresenta estatísticas
                int numeroEspecifico, anoEspecifico;
                printf("Número (quantas vezes foi sorteado): ");
                scanf("%d", &numeroEspecifico);
                printf("Ano (quantidade de concursos nesse ano): ");
                scanf("%d", &anoEspecifico);
                apresentarEstatisticas(&tabela, numeroEspecifico, anoEspecifico);
                break;
            }
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 7);

    return 0;
}