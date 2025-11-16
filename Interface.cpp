#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include "conio2.h"

#include "TADLDSEDesc.h"
#include "TADLDDE.h"

int main()
{
    FILE *arq = fopen("Pacientes.txt", "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        getch();
    }
    else
    {
        srand(time(NULL));

        tpListaMedicos *listaMedico = NULL;
        tpListaMedicos *p = listaMedico;
        tpFilaPaciente verde, amarelo, vermelho;
        tpPaciente novo, retirado;

        retirado.chegada = 0;
        strcpy(retirado.categoria, "");
        strcpy(retirado.nome, "");
        retirado.tempoTratamento = 0;

        int qtdeMedicos, temPaciente = 0, ut = 0, duracaoSimulacao, tempoInserirPaciente = 0,
                         atendidosVerde = 0, atendidosAmarelo = 0, atendidosVermelho = 0, somaEsperaVerde = 0,
                         somaEsperaAmarelo = 0, somaEsperaVermelho = 0;

        inicializar(verde);
        inicializar(amarelo);
        inicializar(vermelho);

        printf("Digite a quantidade de medicos disponiveis: ");
        scanf("%d", &qtdeMedicos);

        printf("Digite a limite de tempo da simulacao: ");
        scanf("%d", &duracaoSimulacao);

        listaMedico = Inserir(listaMedico, qtdeMedicos);

        tempoInserirPaciente = rand() % 10 + 1;
        do
        {
            ut++;

            AtualizarMedicos(listaMedico, atendidosVerde, atendidosAmarelo, atendidosVermelho);

            if (!feof(arq))
            {
                if (tempoInserirPaciente > 0)
                    tempoInserirPaciente--;

                if (tempoInserirPaciente == 0)
                {
                    fscanf(arq, " %[^,],%d,%[^,],%[^,],%s", novo.categoria, &novo.tempoTratamento, novo.nome, novo.queixa, novo.data);
                    novo.chegada = ut;
                    if (strcmp(novo.categoria, "Vermelho") == 0)
                    {
                        novo.prioridade = 1;
                        inserirOrdenado(vermelho, novo);
                    }
                    else if (strcmp(novo.categoria, "Amarelo") == 0)
                    {
                        novo.prioridade = 2;
                        inserirOrdenado(amarelo, novo);
                    }
                    else if (strcmp(novo.categoria, "Verde") == 0)
                    {
                        novo.prioridade = 3;
                        inserirOrdenado(verde, novo);
                    }

                    tempoInserirPaciente = rand() % 10 + 1;
                }
            }

            p = listaMedico;
            while (p != NULL)
            {
                temPaciente = 0;
                if (p->medico.ocupado == 0 && (vermelho.qtde + amarelo.qtde + verde.qtde > 0))
                {
                    if (vermelho.qtde > 0)
                    {
                        retirado = retirar(vermelho);
                        temPaciente = 1;
                    }
                    else if (amarelo.qtde > 0)
                    {
                        retirado = retirar(amarelo);
                        temPaciente = 1;
                    }

                    else if (verde.qtde > 0)
                    {
                        retirado = retirar(verde);
                        temPaciente = 1;
                    }
                    if (temPaciente)
                    {
                        p->medico.pacienteAtual = retirado;
                        p->medico.ocupado = 1;
                        p->medico.tempoRestante = retirado.tempoTratamento;

                        int tempoEspera = ut - retirado.chegada;

                        if (strcmp(retirado.categoria, "Verde") == 0)
                            somaEsperaVerde += tempoEspera;
                        else if (strcmp(retirado.categoria, "Amarelo") == 0)
                            somaEsperaAmarelo += tempoEspera;
                        else if (strcmp(retirado.categoria, "Vermelho") == 0)
                            somaEsperaVermelho += tempoEspera;
                    }
                }
                p = p->prox;
            }

            printf("\n=== UT %d ===\n", ut);
            p = listaMedico;
            while (p != NULL)
            {
                printf("Medico %d: %s (%d) [%d] %s - %s\n", p->medico.id, p->medico.ocupado ? "ocupado" : "livre", p->medico.tempoRestante, tempoInserirPaciente, p->medico.pacienteAtual.nome, p->medico.pacienteAtual.categoria);
                p = p->prox;
            }

            Sleep(200);
        } while (ut < duracaoSimulacao);

        printf("\n\n");
        printf("RELATORIO FINAL\n");
        printf("Total de pacientes atendidos por classificacao: \n");
        printf("Verde: [%d], Amarelo: [%d], Vermelho: [%d]", atendidosVerde, atendidosAmarelo, atendidosVermelho);
        printf("\nTotal de pacientes atendidos por medico: \n");

        p = listaMedico;
        while (p != NULL)
        {
            printf("Medico %d: %d |  ", p->medico.id, p->medico.pacientesAtendidos);
            p = p->prox;
        }

        printf("\nTempo médio de espera:\n");
        printf("Verde: %.2f UT\n", (float)somaEsperaVerde / atendidosVerde);
        printf("Amarelo: %.2f UT\n", (float)somaEsperaAmarelo / atendidosAmarelo);
        printf("Vermelho: %.2f UT\n", (float)somaEsperaVermelho / atendidosVermelho);

        int naoAtendidos = verde.qtde + amarelo.qtde + vermelho.qtde;
        printf("\nPacientes na fila que não foram atendidos: %d\n", naoAtendidos);

        if (vermelho.qtde > 0)
            printf("Vermelho: %d\n", vermelho.qtde);
        if (amarelo.qtde > 0)
            printf("Amarelo: %d\n", amarelo.qtde);
        if (verde.qtde > 0)
            printf("Verde: %d\n", verde.qtde);

        printf("\nStatus dos medicos\n");

        p = listaMedico;
        while (p != NULL)
        {
            printf("Medico %d: %s\n", p->medico.id, p->medico.ocupado ? "ocupado" : "livre");
            p = p->prox;
        }

        fclose(arq);
    }

    return 0;
}