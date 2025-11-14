#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include "conio2.h"

#include "TADLDDE.h"
#include "TADLDSEDesc.h"

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

        tpEmAtendimento *lista = NULL;
        tpFilaPaciente verde, amarelo, vermelho;
        tpPaciente retirado;
        int qtdeMedicos, qtdeMedDispo, ut = 0, duracaoSimulacao, tempoExec = 0, tempoInserirPaciente = 0, tempoRestante = 0;;

        inicializar(verde);
        inicializar(amarelo);
        inicializar(vermelho);

        printf("Digite a quantidade de medicos disponiveis: ");
        scanf("%d", &qtdeMedicos);
        qtdeMedDispo = qtdeMedicos;
        printf("Digite a limite de tempo da simulacao: ");
        scanf("%d", &duracaoSimulacao);

        tempoInserirPaciente = rand() % 3 + 1;
        do
        {
            ut++;

            if (!feof(arq))
            {
                if (tempoInserirPaciente > 0)
                    tempoInserirPaciente--;

                if (tempoInserirPaciente == 0)
                {
                    // insere paciente
                    tpPaciente novo;
                    fscanf(arq, " %[^,],%d,%[^,],%[^,],%s", novo.categoria, &novo.tempoTratamento, novo.nome, novo.queixa, novo.data);
                    //   printf("Categoria: %s\n", novo.categoria);
                    if (strcmp(novo.categoria, "Vermelho") == 0)
                    {
                        novo.prioridade = 1;
                        inserirOrdenado(vermelho, novo);
                        //  printf("Inserido em vermelo\n");
                    }
                    else if (strcmp(novo.categoria, "Amarelo") == 0)
                    {
                        novo.prioridade = 2;
                        inserirOrdenado(amarelo, novo);
                        //  printf("Inserido em amarelo\n");
                    }
                    else if (strcmp(novo.categoria, "Verde") == 0)
                    {
                        novo.prioridade = 3;
                        inserirOrdenado(verde, novo);
                        //  printf("Inserido em verde\n");
                    }

                    // printf("Paciente retirado: %s \t %s\n", novo.categoria, novo.nome);

                    tempoInserirPaciente = rand() % 3 + 1;
                }
            }
//FAZER LOGICA DE LIBERAR MEDICO BASEADO NO TEMPO DO PACIENTE
            if (qtdeMedDispo != 0)
            {
                if (vermelho.qtde > 0)
                {
                    retirado = retirar(vermelho);
                    qtdeMedDispo--;
                }
                else if (amarelo.qtde > 0)
                {
                    retirado = retirar(amarelo);
                    qtdeMedDispo--;
                }
                else if (verde.qtde > 0)
                {
                    retirado = retirar(verde);
                    qtdeMedDispo--;
                }
                
             //   printf("UT, verde, amarelo, vermelho, medicos\n");
               // printf("%d \t %d \t %d \t %d \t %d\n", ut, verde.qtde, amarelo.qtde, vermelho.qtde, qtdeMedDispo);
            } 
            Sleep(200);
        } while (ut != duracaoSimulacao);
        fclose(arq);
    }

    return 0;
}