 // ---------------------------//
// LISTA DUPLAMENTE ENCADEADA //
// ---------------------------//

struct tpEmAtendimento
{
	int info;			
	tpEmAtendimento *ant, *prox; 
};


tpEmAtendimento *NovaCaixa(int valor)
{
	tpEmAtendimento *caixa = new tpEmAtendimento;
	caixa->ant = NULL;			
	caixa->prox = NULL;
	caixa->info = valor; 
	return caixa;		
}

tpEmAtendimento *InsOrdenada(tpEmAtendimento *L)
{
	int elemento;	
	tpEmAtendimento *NC, *P; 
	printf("\nInsercao ordenada Lista dinamica duplamente encadeada");

	printf("\nElemento: ");
	scanf("%d", &elemento); 
	
	while (elemento != 0)
	{
		NC = NovaCaixa(elemento);

		if (L == NULL)
			L = NC;
		else if (elemento <= L->info)
		{
			NC->prox = L;
			L->ant = NC;
			L = NC;
		}
		else
		{
			P = L;

			while (P->prox != NULL && P->prox->info < elemento)
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

		printf("\nElemento: ");
		scanf("%d", &elemento);
	}

	return L; 
}

void Exibir(tpEmAtendimento *L)
{
	if (L == NULL)
	{
		printf("\nLista vazia!\n");
		return;
	}

	tpEmAtendimento *P = L; 
	printf("\n--- Exibindo lista do início ao fim ---\n");

	while (P != NULL)
	{
		printf("%d ", P->info);

		if (P->prox == NULL)
			break; 
		P = P->prox;
	}

	printf("\n--- Exibindo lista do fim ao inicio ---\n");

	while (P != NULL)
	{
		printf("%d ", P->info);
		P = P->ant;
	}

	printf("\n");
}