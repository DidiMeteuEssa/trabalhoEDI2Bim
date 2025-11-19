// ---------------------------//
// LISTA DUPLAMENTE ENCADEADA //
// ---------------------------//
struct tpMedico
{
	int id;
	int tempoRestante;
	int pacientesAtendidos;
	tpPaciente pacienteAtual;
	int ocupado;
	int marcarRemocao;
};

struct tpListaMedicos
{
	tpMedico medico;
	tpListaMedicos *ant, *prox;
};

tpListaMedicos *NovaCaixa(int id)
{
	tpListaMedicos *m = new tpListaMedicos;
	m->medico.id = id;
	m->medico.tempoRestante = 0;
	m->medico.pacientesAtendidos = 0;
	m->medico.ocupado = 0;
	m->ant = m->prox = NULL;
	m->medico.marcarRemocao = 0;
	return m;
}

tpListaMedicos *Inicializar(tpListaMedicos *L, int qtde)
{
	tpListaMedicos *NC, *P;

	for (int i = 0; i < qtde; i++)
	{
		NC = NovaCaixa(i + 1);

		if (L == NULL)
			L = NC;
		else if ((i + 1) <= L->medico.id)
		{
			NC->prox = L;
			L->ant = NC;
			L = NC;
		}
		else
		{
			P = L;

			while (P->prox != NULL && P->prox->medico.id < (i + 1))
				P = P->prox;

			if (P->prox == NULL)
			{
				P->prox = NC;
				NC->ant = P;
			}
			else
			{
				NC->prox = P->prox;
				NC->ant = P;
				P->prox->ant = NC;
				P->prox = NC;
			}
		}
	}

	return L;
}

tpListaMedicos *Inserir(tpListaMedicos *L, int id)
{
	tpListaMedicos *NC, *P;

	P = L;
	while (P != NULL && P->medico.id != id)
		P = P->prox;

	if (P != NULL)
	{
		textcolor(12);
		limparPainel(3, 9, 104, 9);
		gotoxy(3, 9);
		printf("Este ID ja existe!");
		textcolor(15);
	}
	else
	{
		NC = NovaCaixa(id);

		if (L == NULL)
			L = NC;
		else if (id <= L->medico.id)
		{
			NC->prox = L;
			L->ant = NC;
			L = NC;
		}
		else
		{
			P = L;

			while (P->prox != NULL && P->prox->medico.id < id)
				P = P->prox;

			if (P->prox == NULL)
			{
				P->prox = NC;
				NC->ant = P;
			}
			else
			{
				NC->prox = P->prox;
				NC->ant = P;
				P->prox->ant = NC;
				P->prox = NC;
			}
		}
	}

	return L;
}

tpListaMedicos *removerMedico(tpListaMedicos *lista, int id)
{
	if (lista == NULL)
	{
		textcolor(12);
		limparPainel(3, 9, 104, 9);
		gotoxy(3, 9);
		printf("Nao ha medicos para remover.\n");
		textcolor(15);
	}
	else
	{
		tpListaMedicos *aux = lista;

		while (aux != NULL && aux->medico.id != id)
			aux = aux->prox;

		if (aux == NULL)
		{
			textcolor(12);
			limparPainel(3, 9, 104, 9);
			gotoxy(3, 9);
			printf("Medico com ID %d nao encontrado.\n", id);
			textcolor(15);
		}
		else if (aux->medico.ocupado == 1)
		{
			aux->medico.marcarRemocao = 1;

			textcolor(14);
			limparPainel(3, 9, 104, 9);
			gotoxy(3, 9);
			printf("Medico %d esta atendendo. Remocao pendente.\n", id);
			textcolor(15);
		}
		else
		{
			if (aux->ant != NULL)
				aux->ant->prox = aux->prox;
			else
				lista = aux->prox;

			if (aux->prox != NULL)
				aux->prox->ant = aux->ant;

			limparPainel(3, 9, 104, 9);
			gotoxy(3, 9);
			textcolor(10);
			printf("Medico %d removido.\n", id);
			textcolor(15);

			delete aux;
		}
	}

	return lista;
}

tpPaciente AtualizarMedicos(tpListaMedicos *L, int &atendidosVerde, int &atendidosAmarelo, int &atendidosVermelho)
{
	tpPaciente aux;
	aux.tempoTratamento = -1;
	while (L != NULL)
	{
		if (L->medico.ocupado == 1)
		{
			L->medico.tempoRestante--;

			if (L->medico.tempoRestante <= 0)
			{
				L->medico.ocupado = 0;
				aux = L->medico.pacienteAtual;

				if (strcmp(L->medico.pacienteAtual.categoria, "Vermelho") == 0)
					atendidosVermelho++;
				else if (strcmp(L->medico.pacienteAtual.categoria, "Amarelo") == 0)
					atendidosAmarelo++;
				else if (strcmp(L->medico.pacienteAtual.categoria, "Verde") == 0)
					atendidosVerde++;

				L->medico.pacientesAtendidos++;

				strcpy(L->medico.pacienteAtual.nome, "");
				strcpy(L->medico.pacienteAtual.categoria, "");
				L->medico.pacienteAtual.tempoTratamento = 0;
				L->medico.pacienteAtual.chegada = 0;
			}
		}

		L = L->prox;
	}

	return aux;
}
