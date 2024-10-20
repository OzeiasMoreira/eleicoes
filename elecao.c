#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "eleicao.h"


int quantidadeChapas;
int segundoTurno = 0;

int quantChapas(){
    int quantidade;

    while (1)
    {
        printf("Insira a quantidade de Chapas que serão cadastradas(1 a 99): ");
        scanf("%d", &quantidade);

        if (quantidade != 1)
        {
            printf("Entrada inválida. Por favor insira um número. \n\n");
            while (getchar() != '\n');    
            
        } else if (quantidade < 1 || quantidade > 99){

            printf("Valor inválido!Insira um número entre 1 e 99.\n\n");

        } else {

            break;
        }
        
    }
    
   return quantidade;

}

int verificaNumero(Chapa *chapas, int posicao, int quantidade){
    int numeroAtual = chapas[posicao].numeroCandidato;

    if (numeroAtual <= 0 || numeroAtual > 99)
    {
        printf("Erro: O número deve estar entre 1 e 99!\n\n");
        return 1;
    }

    for (int i = 0; i < quantidade; i++)
    {
        if (i != posicao && chapas[i].numeroCandidato == numeroAtual)
        {
            printf("Erro: O número %d já está sendo utilizado por outra chapa!Tente outro número.\n\n",numeroAtual);
            return 1;
        }
        
    }
    
    return 0;
    
}

int verificaData(int data[3]){

    time_t hoje = time(NULL);
    struct tm *dataAtual = localtime(&hoje);

    if (data[2] > (dataAtual->tm_year + 1900) ||
        (data[2] == (dataAtual->tm_year + 1900) && data[1] > (dataAtual->tm_mon + 1)) ||
        (data[2] == (dataAtual->tm_year + 1900) && data[1] == (dataAtual->tm_mon + 1) && data[0] > dataAtual->tm_mday))
    {
        printf("Erro: Data inválida!Essa pessoa ainda não nasceu.\n\n");
        return 1;
    }

    if (data[1] < 1 || data[1] > 12) {
        printf("Erro: Mês inválido!\n\n");
        return 1;
    }
    
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((data[2] % 4 == 0 && data[2] % 100 != 0) || data[2] % 400 == 0) {
        diasPorMes[1] = 29; 
    }

    if (data[0] < 1 || data[0] > diasPorMes[data[1] - 1]) {
        printf("Erro: Dia inválido para o mês informado!\n\n");
        return 1;
    }

    return 0;
}

Chapa *registrarChapas(Chapa *chapas) {
    
    chapas = (Chapa *) malloc(quantidadeChapas * sizeof(Chapa));
    if (chapas == NULL) {
        perror("Erro ao alocação de memória.");
        exit(1);
    }

    
    for (int i = 0; i < quantidadeChapas; i++) {
        limparTerminal();

        
        printf("Insira o nome do candidato a prefeito: ");
        fgets(chapas[i].nomeCandidato, sizeof(chapas[i].nomeCandidato), stdin);
          
        do {
            printf("Insira o número do candidato (1 a 99): ");
            scanf("%d", &chapas[i].numeroCandidato);
            setbuf(stdin, NULL);  
        } while (verificaNumero(chapas, i, quantidadeChapas));  

        
        do {
            printf("Insira a data de nascimento do candidato (dd/mm/aaaa): ");
            scanf("%d %d %d", &chapas[i].data[0], &chapas[i].data[1], &chapas[i].data[2]);
            setbuf(stdin, NULL);
        } while (verificaData(chapas[i].data));  

        
        printf("Insira o nome do vice: ");
        fgets(chapas[i].nomeVice, sizeof(chapas[i].nomeVice), stdin);
        
        chapas[i].votos = 0;
    }

    return chapas;
}

void ImprimeCandidatos(Chapa *chapas, int quantidade){
    for(int i = 0; i < quantidade; i++){
        printf("%s - %d - %s\n", chapas[i].nomeCandidato, chapas[i].numeroCandidato, chapas[i].nomeVice);
    }
}

void Votar(Chapa *chapas, int voto, int *votosBrancos, int *votosNulos, int quantidade) {
    if (voto == 0) {
        (*votosBrancos)++;
        printf("Seu voto em branco foi confirmado!\n");
        return;
    }

    int inicio = 0, final = quantidade - 1;
    while (inicio <= final) {
        int meio = inicio + (final - inicio) / 2; 

        if (voto > chapas[meio].numeroCandidato) {
            inicio = meio + 1; 
        } else if (voto < chapas[meio].numeroCandidato) {
            final = meio - 1; 
        } else {
           
            chapas[meio].votos++;
            printf("Seu voto em %s e vice %s foi confirmado!\n", chapas[meio].nomeCandidato, chapas[meio].nomeVice);
            return;
        }
    }

    (*votosNulos)++;
    printf("Seu voto nulo foi confirmado!\n");
}

int quantidadeEleitores() {
    int quantidade;
    limparTerminal();
    
    do {
        printf("Insira a quantidade de eleitores: \n");
        scanf("%d", &quantidade);
        setbuf(stdin, NULL);

        if (quantidade <= 0) {
            printf("Insira um valor maior que 0.\n\n");
        } else if (segundoTurno && quantidade < 10) {
            printf("Para o segundo turno, a quantidade de eleitores deve ser no mínimo 10.\n\n");
        }

    } while (quantidade <= 0 || (segundoTurno && quantidade < 10));

    return quantidade;
}

void votacao(Chapa *chapas, int *votosBrancos, int *votosNulos, int quantidade) {
    int quantidadeidadeEleitores = quantidadeEleitores(0); 
    int numeroVotado;

    for (int i = 0; i < quantidadeidadeEleitores; i++) {
        limparTerminal();
        
        printf("\n=== CANDIDATOS ===\n\n");
        printf(" NOME         |   NUMERO   |  VICE\n");
        printf("-------------------------------\n");
        ImprimeCandidatos(chapas, quantidade); 
        printf("\n");

        printf("Eleitor %d, digite o número do candidato para prefeito (ou 0 para branco): ", i + 1);
        scanf("%d", &numeroVotado);

        Votar(chapas, numeroVotado, votosBrancos, votosNulos, quantidade);

        printf("Seu voto foi registrado com sucesso!\n\n");
        printf("Pressione a tecla ENTER para o próximo eleitor.\b");
        getchar(); 
        getchar(); 
    }

    limparTerminal();
    printf("Fim da votação!\n\n");
}

void porcentagemVotos(FILE *boletim, Chapa *chapas, int *votosBrancos, int *votosNulos, int *votosValidos, int *votosTotais, int quantidadeidade) {

    if (*votosTotais == 0) {
        fprintf(boletim, "Nenhum voto registrado.\n");
        return;
    }

    fprintf(boletim, "\nPorcentagem de votos dos VOTOS TOTAIS:\n");
    for (int i = 0; i < quantidadeidade; i++) {
        double porcentagemTotal = (chapas[i].votos * 100.0) / (*votosTotais);
        fprintf(boletim, "Candidato %s: %.2f%% dos votos totais\n", chapas[i].nomeCandidato, porcentagemTotal);
    }

    double porcentagemValidos = (*votosValidos) * 100.0 / (*votosTotais);
    double porcentagemBrancos = (*votosBrancos) * 100.0 / (*votosTotais);
    double porcentagemNulos = (*votosNulos) * 100.0 / (*votosTotais);

    fprintf(boletim, "\nVotos válidos: %.2f%%\n", porcentagemValidos);
    fprintf(boletim, "Votos brancos: %.2f%%\n", porcentagemBrancos);
    fprintf(boletim, "Votos nulos: %.2f%%\n", porcentagemNulos);
    fprintf(boletim, "Total de votos: 100%%\n");

    if (*votosValidos == 0) {
        fprintf(boletim, "\nNenhum voto válido registrado.\n");
        return;
    }

    fprintf(boletim, "\nPorcentagem de votos dos VOTOS VALIDOS:\n");
    for (int i = 0; i < quantidadeidade; i++) {
        double porcentagemValidosCandidato = (chapas[i].votos * 100.0) / (*votosValidos);
        fprintf(boletim, "Candidato %s: %.2f%% dos votos válidos\n", chapas[i].nomeCandidato, porcentagemValidosCandidato);
    }
}

void boletimDeUrna(FILE *boletim, Chapa *chapas, int *votosBrancos, int *votosNulos, int *votosValidos, int *votosTotais, int quantidade) {
    
    int totalVotosValidos = 0; 

    for (int i = 0; i < quantidade; i++) {
        totalVotosValidos += chapas[i].votos; 
        fprintf(boletim, "Candidato: %s |Vice: %s | Votos: %d\n",
         chapas[i].nomeCandidato,chapas[i].nomeVice, chapas[i].votos);
    }

    *votosValidos = totalVotosValidos;
    
    *votosTotais = *votosBrancos + *votosNulos + *votosValidos;

    if (*votosTotais < 0) {
        fprintf(boletim, "Erro: O número total de votos não pode ser negativo.\n");
        return; 
    }

    fprintf(boletim, "Total de votos válidos: %d\n", *votosValidos);
    fprintf(boletim, "Total de votos brancos: %d\n", *votosBrancos);
    fprintf(boletim, "Total de votos nulos: %d\n", *votosNulos);
    fprintf(boletim, "Total de votos: %d\n\n", *votosTotais);

    porcentagemVotos(boletim, chapas, votosBrancos, votosNulos, votosValidos, votosTotais, quantidade);
}

int verificaSegundoTurno(FILE *boletim, Chapa *chapas, int *votosValidos) {
    if (*votosValidos > 0) {
        int votosUltimoCandidato = chapas[quantidadeChapas - 1].votos;

        if ((votosUltimoCandidato * 100.0 / *votosValidos) < 50.0) {
            segundoTurno = 1;
            return 1; // 
        }
    } else {
        fprintf(boletim, "Erro: Não há votos válidos para determinar um vencedor.\n");
        return -1; 
    }

    limparTerminal();
    fprintf(boletim, "\n\nO prefeito eleito é %s e vice %s.\n", chapas[quantidadeChapas - 1].nomeCandidato, chapas[quantidadeChapas - 1].nomeVice);
    printf("\n\nO prefeito eleito é %s e %s.\n", chapas[quantidadeChapas - 1].nomeCandidato, chapas[quantidadeChapas- 1].nomeVice);
    return 0; 
}


void limparTerminal(){
    system("clear || cls");
}

int main(){
    return 0;
}