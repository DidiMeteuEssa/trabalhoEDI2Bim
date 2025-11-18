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
	return m;
}

tpListaMedicos *Inserir(tpListaMedicos *L, int qtde)
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

tpListaMedicos *removerMedico(tpListaMedicos *lista)
{
	if (lista == NULL)
	{
		printf("Nao ha medicos para remover.\n");
	}
	else
	{
		tpListaMedicos *remover = lista; // primeiro nó
		lista = lista->prox;			 // avança lista

		if (lista != NULL)
			lista->ant = NULL; // se for lista dupla

		delete remover;
	}

	return lista;
}

tpListaMedicos *BuscarMedicoLivre(tpListaMedicos *L)
{
	tpListaMedicos *aux = L;

	while (aux != NULL && aux->medico.ocupado != 0)
		aux = aux->prox;

	return aux;
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
