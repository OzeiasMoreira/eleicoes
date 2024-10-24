#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "eleicao.h"

#define TAM_DATA 11 
#define TAM_NOME 100


int quantidadeChapas;
int segundoTurno = 0;

int quantChapas(){
    int quantidade;

    while (1)
    {
        printf("Insira a quantidade de Chapas a serem cadastradas(1 a 99): \n");
        scanf("%d", &quantidade);

        if (quantidade < 1 || quantidade > 99){

            printf("Valor inválido!Insira um numero entre 1 e 99.\n\n");

        } else {

            break;
        }
        
    }
    
   return quantidade;

}

int verificaNumero(int numero, Chapa *chapas,int quantidade){

    if (numero < 1 || numero > 99)
    {
        printf("Erro: O numero deve estar entre 1 e 99!\n\n");
        return 1;
    }

    for (int i = 0; i < quantidade; i++)
    {
        if (chapas[i].numeroCandidato == numero)
        {
            printf("Erro: O numero %d já está sendo utilizado por outra chapa!Tente outro numero.\n\n",numero);
            return 1;
        }
        
    }
    
    return 0;
    
}

int verificaData(char dataNascimento[]) {
    int dia, mes, ano;

    if (sscanf(dataNascimento, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        printf("Erro: Formato de data inválido! Use o formato dd/mm/aaaa.\n\n");
        return 1;
    }

    time_t hoje = time(NULL);
    struct tm *dataAtual = localtime(&hoje);
    int anoAtual = dataAtual->tm_year + 1900;
    int mesAtual = dataAtual->tm_mon + 1;
    int diaAtual = dataAtual->tm_mday;

    printf("Ano atual: %d, Mês atual: %d, Dia atual: %d\n", anoAtual, mesAtual, diaAtual);

    if (ano > anoAtual || (ano == anoAtual && (mes > mesAtual || (mes == mesAtual && dia > diaAtual)))) {
        printf("Erro: Data inválida! Essa pessoa ainda Nao nasceu.\n\n");
        return 1;
    }

    if (mes < 1 || mes > 12) {
        printf("Erro: Mês inválido!\n\n");
        return 1;
    }

    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasPorMes[1] = 29; 
    }

    if (dia < 1 || dia > diasPorMes[mes - 1]) {
        printf("Erro: Dia inválido para o mês informado!\n\n");
        return 1;
    }

    return 0;
}

Chapa *cadastarChapas(Chapa *chapas) {
    
    chapas = (Chapa *) malloc(quantidadeChapas * sizeof(Chapa));
    if (chapas == NULL) {
        perror("Erro ao alocação de memória.");
        exit(1);
    }

    
    for (int i = 0; i < quantidadeChapas; i++) {
        limparTerminal();
        limparBuffer();

        printf("Insira o nome do candidato a prefeito: \n");
        fgets(chapas[i].nomeCandidato, TAM_NOME, stdin);
        chapas[i].nomeCandidato[strcspn(chapas[i].nomeCandidato, "\n")] = 0; 

        printf("Insira o nome do vice: \n");
        fgets(chapas[i].nomeVice, TAM_NOME, stdin);
        chapas[i].nomeVice[strcspn(chapas[i].nomeVice, "\n")] = 0;
          
        do {
            printf("Insira o numero do candidato (1 a 99): \n");
            scanf("%d", &chapas[i].numeroCandidato);  
            while (getchar() != '\n');
        } while (verificaNumero(chapas[i].numeroCandidato,chapas, i));  

        
        do {
            printf("Insira a data de nascimento do candidato (dd/mm/aaaa): \n");
            fgets(chapas[i].data, TAM_DATA, stdin);
            chapas[i].data[strcspn(chapas[i].data, "\n")] = 0;

        } while (verificaData(chapas[i].data));

        
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
            printf("Para o segundo turno, a quantidade de eleitores deve ser no minimo 10.\n\n");
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

        printf("Eleitor %d, digite o numero do candidato para prefeito (ou 0 para branco): ", i + 1);
        scanf("%d", &numeroVotado);

        Votar(chapas, numeroVotado, votosBrancos, votosNulos, quantidade);

        printf("Seu voto foi registrado com sucesso!\n\n");
        printf("Pressione a tecla ENTER para o próximo eleitor.\b");
        getchar(); 
        getchar(); 
    }

    limparTerminal();
    printf("Fim da votacao!\n\n");
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

    fprintf(boletim, "\nVotos validos: %.2f%%\n", porcentagemValidos);
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
        fprintf(boletim, "Candidato %s: %.2f%% dos votos validos\n", chapas[i].nomeCandidato, porcentagemValidosCandidato);
    }
}

void boletimDeUrna(FILE *boletim, Chapa *chapas, int *votosBrancos, int *votosNulos, int *votosValidos, int *votosTotais, int quantidade) {
    
    int totalVotosValidos = 0; 

    for (int i = 0; i < quantidade; i++) {
        totalVotosValidos += chapas[i].votos; 
        fprintf(boletim, "Candidato: %s | Vice: %s | Votos: %d\n",
         chapas[i].nomeCandidato,chapas[i].nomeVice, chapas[i].votos);
    }

    *votosValidos = totalVotosValidos;
    
    *votosTotais = *votosBrancos + *votosNulos + *votosValidos;

    if (*votosTotais < 0) {
        fprintf(boletim, "Erro: O numero total de votos nao pode ser negativo.\n");
        return; 
    }

    fprintf(boletim, "Total de votos validos: %d\n", *votosValidos);
    fprintf(boletim, "Total de votos brancos: %d\n", *votosBrancos);
    fprintf(boletim, "Total de votos nulos: %d\n", *votosNulos);
    fprintf(boletim, "Total de votos: %d\n\n", *votosTotais);

    porcentagemVotos(boletim, chapas, votosBrancos, votosNulos, votosValidos, votosTotais, quantidade);
}

int verificarSegundoTurno(FILE *boletim1Turno, Chapa *chapas, int *votosValidos) {
   float maiorPorcentagem = 0.0;
    int indiceVencedor = -1;

    for (int i = 0; i < quantidadeChapas; i++) {
        float porcentagem = ((float)chapas[i].votos / *votosValidos) * 100;

        if (porcentagem > maiorPorcentagem) {
            maiorPorcentagem = porcentagem;
            indiceVencedor = i;
        }
    }

    if (maiorPorcentagem > 50.0) {
        fprintf(boletim1Turno, "Candidato %s venceu no primeiro turno com %.2f%% dos votos validos!\n", chapas[indiceVencedor].nomeCandidato, maiorPorcentagem);
        return 0;
    } else {
        int primeiro = -1, segundo = -1;
        for (int i = 0; i < quantidadeChapas; i++) {
            if (primeiro == -1 || chapas[i].votos > chapas[primeiro].votos) {
                segundo = primeiro;
                primeiro = i;
            } else if (segundo == -1 || chapas[i].votos > chapas[segundo].votos) {
                segundo = i;
            }
        }

        if (primeiro != -1 && segundo != -1 && primeiro != segundo) {
            printf(boletim1Turno, "Segundo turno com os candidatos %s e %s\n", chapas[primeiro].nomeCandidato, chapas[segundo].nomeCandidato);
        } else {
            fprintf(boletim1Turno, "Erro ao calcular os candidatos do segundo turno.\n");
        }
        return 1;
    }
}


Chapa* candidatosSegundoTurno(FILE *boletim, Chapa *chapas, Chapa *chapas2Turno) {
 
    chapas2Turno = (Chapa *) malloc(2 * sizeof(Chapa));
    if (chapas2Turno == NULL) {
        perror("Erro na alocação de memória");
        exit(EXIT_FAILURE);
    }

    int primeiro = -1, segundo = -1;

    for (int i = 0; i < quantidadeChapas; i++) {
        if (primeiro == -1 || chapas[i].votos > chapas[primeiro].votos) {
            segundo = primeiro;
            primeiro = i;
        } else if (segundo == -1 || chapas[i].votos > chapas[segundo].votos) {
            segundo = i;
        }
    }

    if (primeiro != -1 && segundo != -1 && primeiro != segundo) {
        fprintf(boletim, "Segundo turno com os candidatos %s e %s\n", 
                chapas[primeiro].nomeCandidato, chapas[segundo].nomeCandidato);
        chapas2Turno[0] = chapas[primeiro];
        chapas2Turno[1] = chapas[segundo];
    } else {
        fprintf(boletim, "Erro ao selecionar candidatos para o segundo turno.\n");
    }

    chapas2Turno[0].votos = 0;
    chapas2Turno[1].votos = 0;

    return chapas2Turno;
}

void defineCandidatoEleito(FILE *boletim2Turno, Chapa *chapas2Turno, int *votosValidos) {
    if (*votosValidos == 0) {
        fprintf(boletim2Turno, "Erro: Nao ha votos validos para determinar um vencedor.\n");
        printf("Erro: Nao ha votos validos para determinar um vencedor.\n");
        return;
    }

    double porcentagemCandidato1 = (chapas2Turno[0].votos * 100.0) / (*votosValidos);
    double porcentagemCandidato2 = (chapas2Turno[1].votos * 100.0) / (*votosValidos);

    Chapa candidatoEleito;

    if (chapas2Turno[0].votos > chapas2Turno[1].votos) {
        candidatoEleito = chapas2Turno[0];
    } else if (chapas2Turno[1].votos > chapas2Turno[0].votos) {
        candidatoEleito = chapas2Turno[1];
    } else {
        candidatoEleito = (comparaIdade(chapas2Turno[0].data, chapas2Turno[1].data) > 0) 
                            ? chapas2Turno[0] 
                            : chapas2Turno[1];
    }

    fprintf(boletim2Turno, "Prefeito eleito: %s e Vice: %s\n", 
            candidatoEleito.nomeCandidato, candidatoEleito.nomeVice);
    printf("Prefeito eleito: %s e Vice: %s\n", 
            candidatoEleito.nomeCandidato, candidatoEleito.nomeVice);
}

int comparaIdade(int data1[3], int data2[3]) {

    if (data1[2] < data2[2]) return 0; 
    if (data1[2] > data2[2]) return 1; 

    if (data1[1] < data2[1]) return 0;
    if (data1[1] > data2[1]) return 1; 

   
    if (data1[0] < data2[0]) return 0; 
    return 1; 
}

void limparTerminal(){
    system("clear || cls");
}

void limparBuffer(){
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int main(){
    limparTerminal();

    FILE *boletim1Turno = fopen("Boletim_primeiro_Turno.txt", "w");
    if (!boletim1Turno) {
        perror("Erro ao abrir o arquivo do boletim do primeiro turno");
        return EXIT_FAILURE;
    }

    int votosBrancos = 0, votosNulos = 0, votosValidos = 0, votosTotais = 0;
    quantidadeChapas = quantChapas();
    Chapa *chapas = cadastarChapas(NULL); 

    votacao(chapas, &votosBrancos, &votosNulos, quantidadeChapas);
    boletimDeUrna(boletim1Turno, chapas, &votosBrancos, &votosNulos, &votosValidos, &votosTotais, quantidadeChapas);

    if (verificarSegundoTurno(boletim1Turno, chapas, &votosValidos)) {
        limparTerminal();
        printf("Vai ter Segundo Turno!\n");

        votosBrancos = votosNulos = votosValidos = votosTotais = 0;

        FILE *boletim2Turno = fopen("Boletim_segundo_Turno.txt", "w");
        if (!boletim2Turno) {
            perror("Erro ao abrir o arquivo do boletim do segundo turno");
            free(chapas);
            fclose(boletim1Turno);
            return EXIT_FAILURE;
        }

        Chapa *chapas2Turno = candidatosSegundoTurno(boletim1Turno, chapas, NULL);

        sleep(4); 

        votacao(chapas2Turno, &votosBrancos, &votosNulos, 2); 
        boletimDeUrna(boletim2Turno, chapas2Turno, &votosBrancos, &votosNulos, &votosValidos, &votosTotais, 2);
        defineCandidatoEleito(boletim2Turno, chapas2Turno, &votosValidos);

        free(chapas2Turno);
        fclose(boletim2Turno);
    }

    free(chapas);
    fclose(boletim1Turno);

    return 0;
}
