#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eleicao.h"

void cadastrarChapas(Chapa chapas[], int *numeroChapas){
    int continuar = 1;
    while (continuar && *numeroChapas < MAX_CHAPAS)
    {
        printf("Cadastro da chapa %d:\n", *numeroChapas + 1);

        printf("Nome do Candidato:\n");
        char bufferCandidato[50];
        scanf("%s",bufferCandidato);
        strcpy(chapas[*numeroChapas].nomeCandidato,bufferCandidato);

        printf("Numero do Candidato(1 a 99): \n");
        scanf("%d",&chapas[*numeroChapas].numeroCandidato);

        printf("Data de Nascimento(dd mm aaaa): \n");
        scanf("%d %d %d", &chapas[*numeroChapas].dia, &chapas[*numeroChapas].mes, &chapas[*numeroChapas].ano);

        printf("Nome do Vice: \n");
        char bufferVice[50];
        scanf("%s",bufferVice);
        strcpy(chapas[*numeroChapas].nomeVice,bufferVice);

        chapas[*numeroChapas].votos = 0;
        (*numeroChapas)++;

        printf("Deseja cadastrar outra chapa?(1 para sim ou 0 para não): ");
        scanf("%d",&continuar);
    }
    
}

void exibirCandidatos(Chapa chapas[],int numeroChapas){
    printf("\nCandidatos cadastrados:\n");
    for (int i = 0; i < numeroChapas; i++)
    {
        printf("Candidato: %s | Numero: %d | Vice-Candidato: %s\n",
        chapas[i].nomeCandidato,chapas[i].numeroCandidato,chapas[i].nomeVice);
    }
    
}

void registraVotos(Chapa chapas[],int numeroChapas, int *votosBranco, int *votosNulo, int eleitores){
    int voto;
    for (int i = 0; i < eleitores; i++)
    {
        exibirCandidatos(chapas, numeroChapas);
        printf("Digite o número do Candidato que deseja votar ou 0 para branco.");
        scanf("%d",&voto);

        int votoConfirmado = 0;
        if (voto == 0)
        {
            (*votosBranco++);
            printf("Seu voto em branco foi confirmado!\n");

        } else {
            for (int j = 0; j < numeroChapas; j++)
            {
                if (voto == chapas[j].numeroCandidato)
                {
                    chapas[j].votos++;
                    printf("Seu voto em %s com Vice-Candidato %s foi confirmado!\n",
                    chapas[j].nomeCandidato,chapas[j].nomeVice);
                    votoConfirmado = 1;
                    break;
                }
                
            }

            if (!votoConfirmado)
            {
                (*votosNulo)++;
                printf("Voto nulo confirmado!\n");
            }
            
        }

        system("sleep 2");
        system("clear");
        
    }
    

}

void gerarBoletim(Chapa chapas[], int numeroChapas, int votosBranco, int votosNulo, int eleitores, char *arquivo){
    int votosValidos = 0;
    FILE *file = fopen(arquivo, "w");
    
    fprintf(file,"Boletim de Urna:\n");
    for (int i = 0; i < numeroChapas; i++)
    {
        votosValidos += chapas[i].votos;
        fprintf(file,"Candidato %s e Vice-Candidato %s - %d votos\n", chapas[i].nomeCandidato,chapas[i].nomeVice, chapas[i].votos);
    }

    int votosTotais = votosValidos + votosBranco + votosNulo;
    fprintf(file,"Votos em branco: %d\n",votosBranco);
    fprintf(file,"Votos nulos: %d\n",votosNulo);
    fprintf(file,"Votos validos: %d\n",votosValidos);
    fprintf(file,"Votos totais: %d\n",votosTotais);

    for (int i = 0; i < numeroChapas; i++)
    {
        float percentualVotos = (chapas[i].votos) / (float)eleitores * 100;
        fprintf(file, "Percentual de votos para %s e %s: %.2f\n",chapas[i].nomeCandidato,chapas[i].nomeVice,percentualVotos);
    }
    
    fprintf(file, "Percentual de votos em branco: %.2f\n", (votosBranco / (float)votosTotais));
    fprintf(file, "Percentual de votos nulos: %.2f\n", (votosNulo / (float)votosTotais));

    fclose(arquivo);
    
}

int main(){

    Chapa chapas[MAX_CHAPAS];
    int numeroChapas = 0,eleitores, votosBranco = 0, votosNulo = 0;
    
    printf("Digite o numero de eleitores: ");
    scanf("%d",&eleitores);

    cadastrarChapas(chapas, &numeroChapas);
    registraVotos(chapas,numeroChapas,&votosBranco,&votosNulo, eleitores);

    gerarBoletim(chapas, numeroChapas, votosBranco, votosNulo, eleitores, "boletim_primeiro_turno.txt");

    return 0;
}