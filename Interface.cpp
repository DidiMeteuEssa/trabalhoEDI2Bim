// --------------------------------------------------------------------------------------------- //
// TRABALHO ED1 2 BIMESTRE - DIEGO F. F. CALESCO (262516187) E JOAO GABRIEL DA SILVA (262227380) //
// --------------------------------------------------------------------------------------------- //

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <conio2.h>

#include "TADMoldura.h"
#include "TADLDSEDesc.h"
#include "TADLDDE.h"

void encerrarSimulacao(tpListaMedicos *lista, int &encerrarSim, int atendidosVerde, int atendidosAmarelo,
                       int atendidosVermelho, int somaEsperaVerde, int somaEsperaAmarelo,
                       int somaEsperaVermelho, tpFilaPaciente verde,
                       tpFilaPaciente amarelo, tpFilaPaciente vermelho)
{
    limparPainel(3, 4, 104, 8);
    limparPainel(3, 37, 205, 48);

    tpListaMedicos *aux = lista;
    int naoAtendidos = verde.qtde + amarelo.qtde + vermelho.qtde;
    int x = 103, y = 40;

    textcolor(9);
    centralizarTexto(37, 3, 204, "-------- RELATORIO FINAL --------");
    gotoxy(3, 39);
    printf("Total de pacientes atendidos por classificacao: ");
    gotoxy(3, 40);
    printf("# Verde: [%d]", atendidosVerde);
    gotoxy(3, 41);
    printf("# Amarelo: [%d]", atendidosAmarelo);
    gotoxy(3, 42);
    printf("# Vermelho: [%d]", atendidosVermelho);

    gotoxy(3, 44);
    printf("Tempo medio de espera por classificacao:");
    gotoxy(3, 45);
    printf("# Verde: %.2f UT", (float)somaEsperaVerde / atendidosVerde);
    gotoxy(3, 46);
    printf("# Amarelo: %.2f UT", (float)somaEsperaAmarelo / atendidosAmarelo);
    gotoxy(3, 47);
    printf("# Vermelho: %.2f UT", (float)somaEsperaVermelho / atendidosVermelho);

    gotoxy(53, 39);
    printf("Pacientes na fila que não foram atendidos: %d", naoAtendidos);
    gotoxy(53, 40);
    printf("# Verde: [%d]", verde.qtde);
    gotoxy(53, 41);
    printf("# Amarelo: [%d]", amarelo.qtde);
    gotoxy(53, 42);
    printf("# Vermelho: [%d]", vermelho.qtde);

    gotoxy(103, 39);
    printf("Total de pacientes atendidos por medico: ");
    while (lista != NULL)
    {
        gotoxy(x, y);
        printf("# Medico [%d]: [%d]", lista->medico.id, lista->medico.pacientesAtendidos);
        lista = lista->prox;

        y++;

        if (y > 48)
        {
            y = 40;
            x = x + 19;
        }
    }

    x = 153;
    y = 40;
    gotoxy(153, 39);
    printf("Status dos medicos");
    lista = aux;
    while (lista != NULL)
    {
        gotoxy(x, y);
        printf("# Medico %d: %s", lista->medico.id, lista->medico.ocupado ? "ocupado" : "livre");
        lista = lista->prox;

        y++;

        if (y > 48)
        {
            y = 40;
            x = x + 21;
        }
    }

    encerrarSim = 1;
    getch();
}

tpListaMedicos *menuPausa(tpListaMedicos *lista, int &encerrarSim, int atendidosVerde, int atendidosAmarelo,
                          int atendidosVermelho, int somaEsperaVerde, int somaEsperaAmarelo,
                          int somaEsperaVermelho, tpFilaPaciente verde,
                          tpFilaPaciente amarelo, tpFilaPaciente vermelho)
{
    int opc, id;
    limparPainel(3, 4, 104, 8);

    do
    {
        gotoxy(3, 4);
        printf("--------- SIMULACAO PAUSADA ---------");
        gotoxy(3, 5);
        printf("1 - Adicionar medico");
        gotoxy(3, 6);
        printf("2 - Remover medico");
        gotoxy(3, 7);
        printf("3 - Continuar simulacao");
        gotoxy(3, 8);
        printf("4 - Encerrar simulacao");
        gotoxy(3, 9);
        scanf("%d", &opc);

        if (opc == 1)
        {
            limparPainel(3, 9, 104, 9);
            gotoxy(3, 9);
            printf("Digite o ID do medico: ");
            scanf("%d", &id);
            lista = Inserir(lista, id);
        }
        else if (opc == 2)
        {
            limparPainel(3, 9, 104, 9);
            gotoxy(3, 9);
            printf("Digite o ID do medico: ");
            scanf("%d", &id);
            lista = removerMedico(lista, id);
        }
        else if (opc == 4)
        {
            encerrarSimulacao(lista, encerrarSim, atendidosVerde, atendidosAmarelo, atendidosVermelho, somaEsperaVerde, somaEsperaAmarelo, somaEsperaVermelho, verde, amarelo, vermelho);
        }

    } while (opc != 3);

    limparPainel(3, 4, 104, 9);

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
        gotoxy(3, 14);
        printf("Erro ao abrir o arquivo.");
        getch();
    }
    else
    {

        srand(time(NULL));

        tpListaMedicos *listaMedico = NULL;
        tpListaMedicos *p = listaMedico;
        tpFilaPaciente verde, amarelo, vermelho;
        tpPaciente novo, retirado, alta;
        tpPaciente *exibirFila;

        retirado.chegada = 0;
        strcpy(retirado.categoria, "");
        strcpy(retirado.nome, "");
        retirado.tempoTratamento = 0;

        int qtdeMedicos, temPaciente = 0, ut = 0, duracaoSimulacao, tempoInserirPaciente = 0,
                         atendidosVerde = 0, atendidosAmarelo = 0, atendidosVermelho = 0, somaEsperaVerde = 0,
                         somaEsperaAmarelo = 0, somaEsperaVermelho = 0, x, y, xAlta, yAlta, encerrarSim = 0,
                         yPaciente;

        inicializar(verde);
        inicializar(amarelo);
        inicializar(vermelho);

        do
        {
            gotoxy(3, 4);
            printf("Digite a quantidade de medicos disponiveis (max 18): ");
            scanf("%d", &qtdeMedicos);
        } while (qtdeMedicos < 0 || qtdeMedicos > 18);

        gotoxy(3, 5);
        printf("Digite o limite de tempo da simulacao: ");
        scanf("%d", &duracaoSimulacao);

        limparPainel(3, 4, 104, 8);

        listaMedico = Inicializar(listaMedico, qtdeMedicos);

        tempoInserirPaciente = rand() % 3 + 1;

        xAlta = 107;
        yAlta = 6;

        do
        {

            ut++;

            limparPainel(3, 37, 205, 48);

            limparPainel(3, 13, 34, 35);
            limparPainel(37, 13, 69, 35);
            limparPainel(71, 13, 104, 35);

            exibirFila = verde.inicio;
            yPaciente = 13;
            textcolor(10);
            while (exibirFila != NULL)
            {
                centralizarTexto(yPaciente, 3, 35, exibirFila->nome);
                exibirFila = exibirFila->prox;
                yPaciente++;
            }

            exibirFila = amarelo.inicio;
            yPaciente = 13;
            textcolor(14);
            while (exibirFila != NULL)
            {
                centralizarTexto(yPaciente, 37, 69, exibirFila->nome);
                exibirFila = exibirFila->prox;
                yPaciente++;
            }

            exibirFila = vermelho.inicio;
            yPaciente = 13;
            textcolor(12);
            while (exibirFila != NULL)
            {
                centralizarTexto(yPaciente, 71, 104, exibirFila->nome);
                exibirFila = exibirFila->prox;
                yPaciente++;
            }

            textcolor(14);
            gotoxy(200, 4);
            printf("UT: %d", ut);

            gotoxy(76, 4);
            printf("Proximo paciente em: %d UT. ", tempoInserirPaciente);

            gotoxy(3, 4);
            printf("Tecle [P] para pausar a simulacao");

            alta = AtualizarMedicos(listaMedico, atendidosVerde, atendidosAmarelo, atendidosVermelho);

            tpListaMedicos *iter = listaMedico;
            while (iter != NULL)
            {
                tpListaMedicos *proximo = iter->prox;
                if (iter->medico.marcarRemocao == 1 && iter->medico.ocupado == 0)
                {
                    int idRem = iter->medico.id;
                    listaMedico = removerMedico(listaMedico, idRem);
                }
                iter = proximo;
            }

            textcolor(15);
            if (alta.tempoTratamento != -1)
            {
                gotoxy(xAlta, yAlta);
                printf("%s ", alta.nome);

                if (strcmp(alta.categoria, "Verde") == 0)
                    textcolor(10);
                else if (strcmp(alta.categoria, "Amarelo") == 0)
                    textcolor(14);
                else if (strcmp(alta.categoria, "Vermelho") == 0)
                    textcolor(12);

                printf("[%s]", alta.categoria);

                textcolor(15);
                printf(" recebeu");

                textcolor(10);
                printf(" alta!");

                textcolor(15);

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
                        inserir(vermelho, novo);
                    }
                    else if (strcmp(novo.categoria, "Amarelo") == 0)
                    {
                        novo.prioridade = 2;
                        inserir(amarelo, novo);
                    }
                    else if (strcmp(novo.categoria, "Verde") == 0)
                    {
                        novo.prioridade = 3;
                        inserir(verde, novo);
                    }

                    tempoInserirPaciente = rand() % 3 + 1;
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
            textcolor(15);
            while (p != NULL)
            {
                gotoxy(x, y);
                printf("Medico %d:", p->medico.id);

                gotoxy(x, y + 1);
                if (p->medico.ocupado == 1)
                {
                    textcolor(14);
                    printf("Status: ocupado");
                    gotoxy(x, y + 2);
                    textcolor(15);
                    printf("Atendendo: %s", p->medico.pacienteAtual.nome);

                    if (strcmp(p->medico.pacienteAtual.categoria, "Verde") == 0)
                        textcolor(10);
                    else if (strcmp(p->medico.pacienteAtual.categoria, "Amarelo") == 0)
                        textcolor(14);
                    else if (strcmp(p->medico.pacienteAtual.categoria, "Vermelho") == 0)
                        textcolor(12);

                    gotoxy(x, y + 3);
                    printf("Urgencia: %s", p->medico.pacienteAtual.categoria);

                    textcolor(15);
                    gotoxy(x, y + 4);
                    printf("T. restante %d:", p->medico.tempoRestante);
                }

                else
                {
                    textcolor(10);
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
                    menuPausa(listaMedico, encerrarSim, atendidosVerde, atendidosAmarelo, atendidosVermelho, somaEsperaVerde, somaEsperaAmarelo, somaEsperaVermelho, verde, amarelo, vermelho);
                }
            }

            p = listaMedico;

            while (p != NULL && p->medico.ocupado == 0)
                p = p->prox;

            if (ut >= duracaoSimulacao || feof(arq) && verde.qtde == 0 && amarelo.qtde == 0 && vermelho.qtde == 0 && p == NULL)
            {
                encerrarSimulacao(listaMedico, encerrarSim, atendidosVerde, atendidosAmarelo, atendidosVermelho, somaEsperaVerde, somaEsperaAmarelo, somaEsperaVermelho, verde, amarelo, vermelho);
                encerrarSim = 1;
            }

            Sleep(250);
        } while (encerrarSim != 1);
        fclose(arq);
    }

    return 0;
}
