#ifndef ELEICAO_H
#define ELEICAO_H

#define MAX_CHAPAS 99
#define MIN_ELEITORES_2TURNO 10

typedef struct {
    char nomeCandidato[50];
    int numeroCandidato;
    int dia,mes,ano;
    char nomeVice[50];
    int votos;
} Chapa;

void cadastrarChapas(Chapa chapas[], int *numeroChapas);
void exibirCandidatos(Chapa chapas[],int numeroChapas);
void registraVotos(Chapa chapas[],int numeroChapas, int *votosBranco, int *votosNulo, int eleitores);
void gerarBoletim(Chapa chapas[], int numeroChapas, int votosBranco, int votosNulo, int eleitores, char *arquivo);

#endif