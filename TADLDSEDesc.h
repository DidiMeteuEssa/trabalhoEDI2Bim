// ------------------------------------------ //
// LISTA SIMPLESMENTE ENCADEADA COM DESCRITOR //
// ------------------------------------------ //

struct tpPaciente
{
	char categoria[20], nome[30], queixa[50], data[11];
	int tempoTratamento, prioridade, chegada;
	tpPaciente *prox;
};

struct tpFilaPaciente
{
	int qtde;
	tpPaciente *inicio, *fim;
};

void inicializar(tpFilaPaciente &d)
{
	d.inicio = d.fim = NULL;
	d.qtde = 0;
}

tpPaciente *novaCaixa(tpPaciente novo)
{
	tpPaciente *NC = new tpPaciente;

	strcpy(NC->categoria, novo.categoria);
	strcpy(NC->nome, novo.nome);
	strcpy(NC->queixa, novo.queixa);
	strcpy(NC->data, novo.data);
	NC->tempoTratamento = novo.tempoTratamento;
	NC->prioridade = novo.prioridade;
	NC->chegada = 0;
	NC->prox = NULL;
	return NC;
}

void inserirOrdenado(tpFilaPaciente &d, tpPaciente novo)
{
	tpPaciente *caixa;
	tpPaciente *ant, *atual;
	
		caixa = novaCaixa(novo);
		if (d.qtde == 0)
			d.inicio = d.fim = caixa;
		else if (novo.prioridade <= d.inicio->prioridade)
		{
			caixa->prox = d.inicio;
			d.inicio = caixa;
		}
		else if (novo.prioridade >= d.fim->prioridade)
		{
			d.fim->prox = caixa;
			d.fim = caixa;
		}
		else
		{
			ant = d.inicio;
			atual = d.inicio->prox;

			while (atual->prioridade < novo.prioridade)
			{
				ant = atual;
				atual = atual->prox;
			}

			caixa->prox = atual;
			ant->prox = caixa;
		}
		d.qtde++;
}

tpPaciente retirar(tpFilaPaciente &d)
{
	tpPaciente *aux = d.inicio;
	tpPaciente retirado = *aux;
	d.inicio = aux->prox;
	delete aux;
	d.qtde--;
	return retirado;
}

void exibir(tpFilaPaciente d)
{
	tpPaciente *aux = d.inicio;
	printf("\nLista: ");

	while (aux != NULL)
	{
		printf("%s ", aux->nome);
		aux = aux->prox;
	}
}