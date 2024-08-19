#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#define TAMANHO_TABELA 100

typedef struct {
    int numero;
    char data[11];
    int numeros[6];
} Concurso;

typedef struct No {
    Concurso concurso;
    struct No* proximo;
} No;

typedef struct {
    No* tabela[TAMANHO_TABELA];
} TabelaDispersao;

typedef struct {
    int numero;
    int frequencia;
} NumeroFrequencia;

void inicializarTabela(TabelaDispersao* tabela);
int funcaoDispersao(int numero);
void inserirConcurso(TabelaDispersao* tabela, Concurso concurso);
Concurso* buscarConcurso(TabelaDispersao* tabela, int numero);
int removerConcurso(TabelaDispersao* tabela, int numero);
void carregarConcursos(TabelaDispersao* tabela, const char* nomeArquivo);
int compararFrequencia(const void* a, const void* b);
void apresentarEstatisticas(TabelaDispersao* tabela, int numeroEspecifico, int anoEspecifico);


#endif