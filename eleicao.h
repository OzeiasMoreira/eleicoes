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

int quantChapas();

Chapa *cadastrarChapa(Chapa *chapas);

int verificaNumero(int numero, Chapa *chapas,int quantidade);

int verificaData(char dataNascimento[]);

int verificarChapa(Chapa *chapas, int pos, int quant, int data[3]);

int compararIdade(int data1[3], int data2[3]);

int quantidadeEleitores();

void ImprimeCandidatos(Chapa *chapas, int quantidade);

void porcentagemVotos(FILE *boletim, Chapa *chapas, int *votosBrancos, int *votosNulos, int *votosValidos, int *votosTotais, int quantidadeidade);

void Votar(Chapa *chapas, int voto, int *votosBrancos, int *votosNulos, int quant);

void boletimDeUrna(FILE *boletim, Chapa *chapas, int *votosBrancos, int *votosNulos, int *votosValidos, int *votosTotais, int quantidade);

int verificarSegundoTurno(FILE *boletim1Turno, Chapa *chapas, int *votosValidos);

Chapa *candidatosSegundoTurno(FILE *boletim1Turno, Chapa *chapas, Chapa *chapas2Turno);

void defineCandidatoEleito(FILE *boletim2Turno, Chapa *chapas2Turno, int *votosValidos);

void limparTerminal();

void limparBuffer();

#endif