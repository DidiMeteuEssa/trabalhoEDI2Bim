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
#include "TADMoldura.h"

tpListaMedicos *menuPausa(tpListaMedicos *lista)
{
    int opc;

    do
    {
        limparPainel(3, 4, 104, 8);
        gotoxy(3, 4);
        printf("=== SIMULACAO PAUSADA ===");
        gotoxy(3, 5);
        printf("1 - Adicionar medico");
        gotoxy(3, 6);
        printf("2 - Remover primeiro medico");
        gotoxy(3, 7);
        printf("3 - Continuar simulacao");
        gotoxy(3, 8);
        printf("Opcao: ");

        scanf("%d", &opc);

        gotoxy(3, 9);
        if (opc == 1)
        {
            lista = Inserir(lista, 1);
            printf("Medico adicionado!\n");
        }
        else if (opc == 2)
        {
            lista = removerMedico(lista);
            printf("Medico removido.");
        }

    } while (opc != 3);

    limparPainel(3, 4, 104, 8);

    gotoxy(3, 9);
    printf("Simulacao retomada...\n");

    return lista;
}

int main()
{

    printf("Este e um sistema para rodar em tela cheia, ou com zoom reduzido. Pressione qualquer tecla para iniciar...");
    getch();

    molduraSistema();
    limparPainel(12, 6, 58, 6);

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
        tpPaciente novo, retirado, alta;

        retirado.chegada = 0;
        strcpy(retirado.categoria, "");
        strcpy(retirado.nome, "");
        retirado.tempoTratamento = 0;

        int qtdeMedicos, temPaciente = 0, ut = 0, duracaoSimulacao, tempoInserirPaciente = 0,
                         atendidosVerde = 0, atendidosAmarelo = 0, atendidosVermelho = 0, somaEsperaVerde = 0,
                         somaEsperaAmarelo = 0, somaEsperaVermelho = 0, x, y, temInsercao, xPaciente, yPaciente, xAlta, yAlta;

        inicializar(verde);
        inicializar(amarelo);
        inicializar(vermelho);

        do
        {
            gotoxy(3, 14);
            printf("Digite a quantidade de medicos disponiveis (max 18): ");
            scanf("%d", &qtdeMedicos);
        } while (qtdeMedicos < 0 || qtdeMedicos > 18);

        gotoxy(3, 15);
        printf("Digite o limite de tempo da simulacao: ");
        scanf("%d", &duracaoSimulacao);

        limparPainel(12, 6, 58, 6);
        limparPainel(3, 13, 104, 35);

        listaMedico = Inserir(listaMedico, qtdeMedicos);

        tempoInserirPaciente = rand() % 10 + 1;

        xPaciente = 3;
        yPaciente = 13;

        xAlta = 107;
        yAlta = 6;

        do
        {
            ut++;
            temInsercao = 0;

            limparPainel(3, 37, 208, 48);

            gotoxy(200, 4);
            printf("UT: %d", ut);

            gotoxy(78, 13);
            printf("Proximo paciente em: %d UT. ", tempoInserirPaciente);

            gotoxy(3, 4);
            printf("Tecle [P] para pausar a simulacao");

            alta = AtualizarMedicos(listaMedico, atendidosVerde, atendidosAmarelo, atendidosVermelho);

            if (alta.tempoTratamento != -1)
            {
                gotoxy(xAlta, yAlta);
                printf("%s [%s] recebeu alta!", alta.nome, alta.categoria);
                yAlta++;

                if (yAlta > 35)
                {

                    yAlta = 6;
                    if (xAlta < 156)
                        xAlta = 156;
                    else
                    {
                        xAlta = 106;
                        limparPainel(106, 6, 204, 35);
                    }
                }
            }

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
                        temInsercao = 1;
                    }
                    else if (strcmp(novo.categoria, "Amarelo") == 0)
                    {
                        novo.prioridade = 2;
                        inserirOrdenado(amarelo, novo);
                        temInsercao = 1;
                    }
                    else if (strcmp(novo.categoria, "Verde") == 0)
                    {
                        novo.prioridade = 3;
                        inserirOrdenado(verde, novo);
                        temInsercao = 1;
                    }

                    if (temInsercao)
                    {
                        gotoxy(xPaciente, yPaciente);
                        printf("%s chegou na fila com categoria %s", novo.nome, novo.categoria);
                        yPaciente++;

                        if (yPaciente > 35)
                        {
                            limparPainel(3, 13, 104, 35);
                            yPaciente = 13;
                        }
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

            p = listaMedico;

            x = 3;
            y = 37;
            while (p != NULL)
            {
                gotoxy(x, y);
                printf("Medico %d:", p->medico.id);

                gotoxy(x, y + 1);
                if (p->medico.ocupado == 1)
                {
                    printf("Status: ocupado");
                    gotoxy(x, y + 2);
                    printf("Atendendo: %s", p->medico.pacienteAtual.nome);

                    gotoxy(x, y + 3);
                    printf("Urgencia: %s", p->medico.pacienteAtual.categoria);

                    gotoxy(x, y + 4);
                    printf("T. restante %d:", p->medico.tempoRestante);
                }

                else
                {
                    printf("Status: livre");
                    gotoxy(x, y + 2);
                    printf("Atendendo: N/A");

                    gotoxy(x, y + 3);
                    printf("Urgencia: N/A");

                    gotoxy(x, y + 4);
                    printf("T. restante: N/A");
                }

                p = p->prox;
                x = x + 32;

                if (x > 190)
                {
                    x = 3;
                    y = 44;
                }
            }

            if (kbhit())
            {
                char tecla = getch();
                if (tecla == 'p' || tecla == 'P')
                {
                    menuPausa(listaMedico);
                }
            }

            Sleep(500);
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