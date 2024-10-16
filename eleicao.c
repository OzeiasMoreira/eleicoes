#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eleicao.h"

void cadastrarChapas(Chapa chapas[], int *numeroChapas){
    int continuar = 1;
    while (continuar && numeroChapas < MAX_CHAPAS)
    {
        printf("Cadastro da chapa %d:\n", *numeroChapas + 1);

        printf("Nome do Candidato:");
        char bufferCandidato[50];
        scanf("%s",bufferCandidato);
        strcpy(chapas[*numeroChapas].nomeCandidato,bufferCandidato);

        printf("Numero do Candidato(1 a 99): ");
        scanf("%d",&chapas[*numeroChapas].numeroCandidato);

        printf("Data de Nascimento(dd mm aaaa): ");
        scanf("%d %d %d", &chapas[*numeroChapas].dia, &chapas[*numeroChapas].mes, &chapas[*numeroChapas].ano);

        printf("Nome do Vice: ");
        char bufferVice[50];
        scanf("%s",bufferVice);
        strcpy(chapas[*numeroChapas].nomeVice,bufferVice);

        chapas[*numeroChapas].votos = 0;
        (*numeroChapas)++;

        printf("Deseja cadastrar outra chapa?(1 para sim ou 0 para não): ");
        scanf("%d",&continuar);
    }
    
}

void exibirCandidatos(Chapa chapas[],int numeroCandidatos){

}

void registraVotos(Chapa chapas[],int numeroChapas, int *votosBranco, int *votosNulo, int eleitores){

}

void gerarBoletim(Chapa chapas[], int numeroChapas, int votosBranco, int votosNulo, int eleitores, char *arquivo){
    
}