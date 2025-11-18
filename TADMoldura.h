void DesenhaMoldura(int LI, int CI, int LF, int CF)
{
    int a;
    gotoxy(CI, LI);
    printf("%c", 201);

    gotoxy(CF, LF);
    printf("%c", 188);

    gotoxy(CI, LF);
    printf("%c", 209);

    gotoxy(CF, LI);
    printf("%c", 187);

    for (a = CI + 1; a < CF; a++)
    {
        gotoxy(a, LI);
        printf("%c", 205);
        gotoxy(a, LF);
        printf("%c", 205);
    }

    for (a = LI + 1; a < LF; a++)
    {
        gotoxy(CI, a);
        printf("%c", 186);
        gotoxy(CF, a);
        printf("%c", 186);
    }
}

void centralizarTexto(int linha, int colInicio, int colFim, const char *texto)
{
    int largura = colFim - colInicio + 1;
    int tam = strlen(texto);
    int coluna = colInicio + (largura - tam) / 2;
    gotoxy(coluna, linha);
    printf("%s", texto);
}

void molduraSistema()
{

    textcolor(10);
    // cabecalho, rodape e moldura principal
    DesenhaMoldura(1, 1, 3, 209);
    DesenhaMoldura(3, 1, 10, 105);
    DesenhaMoldura(49, 1, 51, 209);
    DesenhaMoldura(1, 1, 51, 209);
    DesenhaMoldura(36, 1, 51, 209);
    DesenhaMoldura(10, 1, 12, 105);
    DesenhaMoldura(3, 198, 5, 209);
    DesenhaMoldura(3, 105, 5, 209);
    DesenhaMoldura(3, 1, 36, 105);

    gotoxy(1, 3);
    printf("%c", 204);
    gotoxy(1, 10);
    printf("%c", 204);
    gotoxy(1, 12);
    printf("%c", 204);
    gotoxy(1, 36);
    printf("%c", 204);
    gotoxy(1, 49);
    printf("%c", 204);
    gotoxy(1, 51);
    printf("%c", 200);

    gotoxy(105, 3);
    printf("%c", 203);
    gotoxy(105, 5);
    printf("%c", 204);
    gotoxy(105, 10);
    printf("%c", 185);
    gotoxy(105, 12);
    printf("%c", 185);
    gotoxy(105, 36);
    printf("%c", 202);

    gotoxy(198, 3);
    printf("%c", 203);
    gotoxy(198, 5);
    printf("%c", 202);

    gotoxy(209, 3);
    printf("%c", 185);
    gotoxy(209, 5);
    printf("%c", 185);
    gotoxy(209, 36);
    printf("%c", 185);
    gotoxy(209, 49);
    printf("%c", 185);

    gotoxy(200, 4);
    printf("UT: 0");

    textcolor(13);
    centralizarTexto(2, 1, 209, "TRABALHO DE ED1 - SISTEMA DE TRIAGEM");

    centralizarTexto(50, 1, 209, "DIEGO FELIPPE DA F. CALESCO / JOAO GABRIEL DA SILVA");

    textcolor(14);
    centralizarTexto(11, 1, 104, "Pacientes na Fila");

    centralizarTexto(4, 105, 209, "Pacientes que receberam alta");
}

void limparPainel(int xInicio, int yInicio, int xFinal, int yFinal)
{
    int largura = xFinal - xInicio + 1;

    // Cria manualmente uma linha de espaços
    char linha[300];
    for (int i = 0; i < largura; i++)
    {
        linha[i] = ' ';
    }
    linha[largura] = '\0'; // fim da string

    // Agora imprime uma linha inteira por vez
    for (int y = yInicio; y <= yFinal; y++)
    {
        gotoxy(xInicio, y);
        printf("%s", linha);
    }
}