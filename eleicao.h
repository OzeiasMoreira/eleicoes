#ifndef ELEICAO_H
#define ELEICAO_H

#include <stdio.h>

#define MAX_CHAPAS 99
#define MIN_ELEITORES_2TURNO 10

typedef struct {
    char nomeCandidato[50];
    int numeroCandidato;
    int data[3];
    char nomeVice[50];
    int votos;
} Chapa;

int quantidadeChapas();

Chapa *registrarChapas(Chapa *chapas);

int verificarChapa(Chapa *chapas, int pos, int quant, int data[3]);

int compararIdade(int data1[3], int data2[3]);

void processosVotacao(Chapa *chapas, int quant, int *votosBrancos, int *votosNulos);

int quantidadeEleitores();

void Votar(Chapa *chapas, int voto, int *votosBrancos, int *votosNulos, int quant);

void gerarBoletim(FILE *boletim, Chapa *chapas, int *votosBrancos, int *votosNulos, int *votosValidos, int *votosTotais, int quant);

int verificarSegundoTurno(FILE *boletim1Turno, Chapa *chapas, int *votosValidos);

Chapa *candidatosSegundoTurno(FILE *boletim1Turno, Chapa *chapas, Chapa *chapas2Turno);

int criterioOrdenacao(Chapa a, Chapa b, int criterio);

void defineCandidatoEleito(FILE *boletim2Turno, Chapa *chapas2Turno, int *votosValidos);

void quickSort(Chapa *chapas, int inicio, int fim, int criterio);

int particao(Chapa *chapas, int inicio, int fim, int criterio);

void trocar(Chapa *a, Chapa *b);

void limparTerminal();

#endif