#include <stdio.h>
#include "gerenciador.h"

void menu() {
    printf("1. Inserir Concurso\n");
    printf("2. Buscar Concurso\n");
    printf("3. Remover Concurso\n");
    printf("4. Visualizar Todos os Concursos\n");
    printf("5. Carregar Concursos de um Arquivo\n");
    printf("6. Apresentar Estatísticas\n");
    printf("7. Sair\n");
}

int main() {
    TabelaDispersao tabela;
    inicializarTabela(&tabela);

    int opcao;
    do {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Concurso concurso;
                printf("Número do Concurso: ");
                scanf("%d", &concurso.numero);
                printf("Data do Sorteio (dd-mm-aaaa): ");
                scanf("%s", concurso.data);
                printf("Números Sorteados: ");
                for (int i = 0; i < 6; i++) {
                    scanf("%d", &concurso.numeros[i]);
                }
                inserirConcurso(&tabela, concurso);
                break;
            }
            case 2: {
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
            case 3: {
                int numero;
                printf("Número do Concurso: ");
                scanf("%d", &numero);
                removerConcurso(&tabela, numero);
                break;
            }
            case 4: {
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
            case 5: {
                char nomeArquivo[256];
                printf("Nome do Arquivo (data/sorteios.csv): ");
                scanf("%s", nomeArquivo);
                carregarConcursos(&tabela, nomeArquivo);
                break;
            }
            case 6: {
                apresentarEstatisticas(&tabela);
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