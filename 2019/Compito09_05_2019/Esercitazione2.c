/*
Un hamburgeria propone un menu di N diversi hamburger (N costante definito a scelta dallo studente).
Ogni hamburger è caratterizzato da un nome, un costo, e dall’elenco degli ingredienti. 
Le informazioni di ogni hamburger sono memorizzate in un elemento di un array di N elementi.
Gli ingredienti di un hamburger sono organizzati secondo una lista semplice in cui ogni nodo contiene il nome dell’ingrediente ed il suo costo. 
Il costo dell’hamburger è calcolato sommando il costo di ogni suo ingrediente. 
Lo studente implementi un programma ANSI C con un opportuno main in cui sia previsto un menu di scelta delle operazioni richieste e che provvede
alla visualizzazione dei risultati quando necessario. Tutti i valori necessari al funzionamento devono essere passati utilizzando parametri,
non è permesso l’uso di variabili globali.
1. Acquisizione da tastiera di N hamburger. Il primo hamburger inserito viene memorizzato nell’elemento 0 dell’array degli hamburger,
il secondo hamburger inserito viene memorizzato nell’elemento 1 dell’array degli hamburger, e così via. 
2. Funzione che restituisce un vettore che contiene il numero di ingredienti di ogni hamburger.  
3. Funzione che data una fascia di prezzo (passata come parametro) restituisca (e non visualizzi) gli indici dell’array degli hamburger corrispondenti 
agli hamburger il cui costo cade nella suddetta fascia. 
4. Funzione che restituisce l’hamburger di costo massimo, quello di costo minimo ed il costo medio di un hamburger.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 10

typedef struct IngredienteS 
{
	char NomeIngrediente[255];
	float Costo;
} IngredienteT;

typedef struct NodoIngredienteS 
{
	IngredienteT info;
	struct NodoIngredienteS* next;
} NodoIngredienteT, *ListaIngredienti;

typedef struct HamburgerS 
{
	ListaIngredienti ingredienti;
	char Nome[32];
	float costo;
} HamburgerT;



int Menu()
{
	int scelta;
	printf("******* MENU *******\n"
		"1. Inserisci Hamburger.\n"
		"2. Ingredienti per Hamburger.\n"
		"3. Hamburger nella fascia di prezzo indicata.\n"
		"4. Hamburger di costo massimo, minimo e medio.\n\n"
		">>>>> "
	);
	scanf("%d", &scelta);
	return scelta;
} 

void InizializzaListaIngredienti(ListaIngredienti* lista) 
{
	(*lista) = NULL;
}

int InserisciIngrediente(ListaIngredienti* lista, IngredienteT i) 
{
	NodoIngredienteT* aux = (NodoIngredienteT*)malloc(sizeof(NodoIngredienteT));
	if (aux == NULL)
		return 0;
	aux->info = i;
	aux->next = (*lista);
	(*lista) = aux;
	return 1;
}

void InizializzaVettore(HamburgerT v[], int dim) 
{
	for (int i = 0; i < dim; i++) 
	{
		strcpy(v[i].Nome, "");
		InizializzaListaIngredienti(&(v[i].ingredienti));
		v[i].costo = 0.0;
	}
}

void DisallocaLista(ListaIngredienti* lista) 
{
	ListaIngredienti aux;
	while ((*lista) != NULL) 
	{
		aux = (*lista);
		(*lista) = (*lista)->next;
		free(aux);
	}
}

int InserisciHamburger(HamburgerT v[], int dim, char * NomeHamburger, ListaIngredienti ingredienti) 
{
	int i = 0;
	while (i < dim) 
	{
		if (strcmp(v[i].Nome, "") == 0) 
		{
			strcpy(v[i].Nome, NomeHamburger);
			float costoi = 0.0F;
			while (ingredienti != NULL) 
			{
				costoi += ingredienti->info.Costo;
				InserisciIngrediente(&(v[i].ingredienti), ingredienti->info);
				ingredienti = ingredienti->next;
			}
			v[i].costo = costoi;
			return 1;
		}
		else 
		{
			i++;
		}
		if ((i == dim - 1) && (strcmp(v[i].Nome, "") != 0))
			return 0;
	}
}

void VisualizzaIngredienti(ListaIngredienti ingredienti) 
{
	while (ingredienti != NULL) 
	{
		printf("%s %.3f\n", ingredienti->info.NomeIngrediente, ingredienti->info.Costo);
		ingredienti = ingredienti->next;
	}
}

int* VettoreNumIngredienti(HamburgerT vh[], int dim)
{
	int* vout = (int*)malloc(sizeof(int) * dim);
	if (vout == NULL)
		return NULL;
	int cont;
	for (int i = 0; i < dim; i++) 
	{
		cont = 0;
		while (vh[i].ingredienti != NULL) 
		{
			cont++;
			vh[i].ingredienti = vh[i].ingredienti->next;
		}
		vout[i] = cont;
	}
	return vout;
}

int* TrovaHamburgerConveniente(HamburgerT vh[],int dim, float valmax, float valmin, int* nindici) 
{
	int* vout;
	(*nindici) = 0;
	int cont = 0;
	for (int i = 0; i < dim; i++) 
	{
		if ((vh[i].costo < valmax) && (vh[i].costo > valmin)) 
		{
			cont++;
		}
	}
	(*nindici) = cont;
	vout = (int*)malloc(sizeof(int) * cont);
	int index = 0;
	for (int i = 0; i < dim; i++)
	{
		if ((vh[i].costo < valmax) && (vh[i].costo > valmin))
		{
			vout[index++] = i;
		}
	}
	return vout;
}

HamburgerT* Analisi(HamburgerT vh[], int dim, float* costomedio) 
{
	(*costomedio) = 0.0;
	HamburgerT* v = (HamburgerT*)malloc(sizeof(HamburgerT) * 2);
	if (v == NULL)
		return NULL;
	float massimo = vh[0].costo;
	float minimo = vh[0].costo;

	int index = 0;
	float costotot = 0.0;

	for (int i = 0; i < dim; i++) 
	{
		costotot += vh[i].costo;
		if (vh[i].costo > massimo) 
		{
			massimo = vh[i].costo;
			v[index] = vh[i];
		}
	}
	index++;
	for (int i = 0; i < dim; i++)
	{
		if (vh[i].costo < minimo)
		{
			minimo = vh[i].costo;
			v[index] = vh[i];
		}
	}
	(*costomedio) = ((float)(costotot) / (float)(N));
	return v;
}

int main() 
{
	HamburgerT vHamburger[N];
	InizializzaVettore(vHamburger, N);
	ListaIngredienti Ingredienti = NULL;
	IngredienteT ing;
	int* vout = NULL;
	int* indici = NULL;
	int index;
	char NomeHamburger[32];
	float costo;
	float valmax, valmin;
	int esito;
	int NumIngredienti = 0;
	int scelta;
	HamburgerT* vettoreuscita = NULL;
	float CostoMedioHamburger;
	do
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci il nome dell'Hamburger: ");
			scanf("%s", NomeHamburger);
			printf("Da quanti ingredienti e' composto: ");
			scanf("%d", &NumIngredienti);
			int i = 0;
			while (i < NumIngredienti) 
			{
				printf("Inserisci il nome dell'ingrediente: ");
				scanf("%s", ing.NomeIngrediente);
				printf("Inserisci il costo dell'ingrediente: ");
				scanf("%f", &ing.Costo);
				if (InserisciIngrediente(&Ingredienti, ing) == 1)
					i++;
			}
			esito = InserisciHamburger(vHamburger, N, NomeHamburger, Ingredienti);
			if (esito == 1)
				printf("Hamburger inserito con successo.\n\n");
			for (int i = 0; i < N; i++) 
			{
				printf("NOME: %s, COSTO: %.3f\n", vHamburger[i].Nome, vHamburger[i].costo);
				printf("INGREDIENTI:\n");
				VisualizzaIngredienti(vHamburger[i].ingredienti);
				printf("\n");
			}
			DisallocaLista(&Ingredienti);
			break;
		case 2:
			vout = VettoreNumIngredienti(vHamburger, N);
			for (int i = 0; i < N; i++) 
			{
				printf("HAMBURGER %d: %d\n", i, vout[i]);
			}
			printf("\n");
			break;
		case 3:
			printf("Inserisci il valore massimo: ");
			scanf("%f", &valmax);
			printf("Inserisci il valore minimo: ");
			scanf("%f", &valmin);
			indici = TrovaHamburgerConveniente(vHamburger, N, valmax, valmin, &index);
			for (int i = 0; i < index; i++) 
			{
				printf("Indice: %d\n", indici[i]);
			}
			printf("\n");
			break;
		case 4: 
			vettoreuscita = Analisi(vHamburger, N, &CostoMedioHamburger);
			printf("Il costo massimo si ha per l'hamburger %s con il prezzo di %.3f\n"
				"Il costo minimo si ha per l'hamburger %s con il prezzo di %.3f\n"
				"Il prezzo medio e' di %.3f\n\n", vettoreuscita[0].Nome, vettoreuscita[0].costo, vettoreuscita[1].Nome, vettoreuscita[1].costo, CostoMedioHamburger);
			break;
		}
	} while (scelta != 0);
	free(vettoreuscita);
	free(indici);
	free(vout);
	for (int i = 0; i < N; i++) 
	{
		DisallocaLista(&vHamburger[i].ingredienti);
	}
}