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
        int qtdeMedicos, qtdeMedDispo, ut = 0, duracaoSimulacao, tempoExec = 0;

        inicializar(verde);
        inicializar(amarelo);
        inicializar(vermelho);

        printf("Digite a quantidade de medicos disponiveis: ");
        scanf("%d", &qtdeMedicos);
        qtdeMedDispo = qtdeMedicos;
        printf("Digite a limite de tempo da simulacao: ");
        scanf("%d", &duracaoSimulacao);

        do
        {
            ut++;

            tpPaciente novo;
            fscanf(arq, "%[^,],%d,%[^,],%[^,],%[^,]\n", novo.categoria, &novo.tempoTratamento, novo.nome, novo.queixa, novo.data);
            if (strcmp(novo.categoria, "vermelho") == 0)
            {
                novo.prioridade = 1;
                inserirOrdenado(vermelho, novo);
            }
            else if (strcmp(novo.categoria, "amarelo") == 0)
            {
                novo.prioridade = 2;
                inserirOrdenado(amarelo, novo);
            }
            else
            {
                novo.prioridade = 3;
                inserirOrdenado(verde, novo);
            }

            if (qtdeMedDispo > 0)
            {
                if (vermelho.qtde > 0)
                {
                }
                else if (amarelo.qtde > 0)
                {
                }
                else if (verde.qtde > 0)
                {
                }
                else
                {
                    // nenhum paciente na fila
                }
            }
            else
            {
                // nao ha medicos disponiveis
            }
        } while (ut != duracaoSimulacao);
    }

    return 0;
}