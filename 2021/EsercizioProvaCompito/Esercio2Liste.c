/*
  Sviluppo di applicazione in ANSI C per gestire
  un servizio di prestito libri di una libreria.

  In un file di testo ("libri.txt"), è memorizzato
  l'elenco dei libri della biblioteca.
  Così come visibile nel file, per ciascun  libro
  sono memorizzate le seguenti informazioni:
  - codice libro
  - titolo libro
  - genere libro (es: biografia, romanzo, giallo, thriller, avventura, fantascienza, etc)
  - costo settimanale

  Si assuma che il titolo del libro non contenga spazi.

  Implementare le seguenti funzioni:

  1. CaricaLibri: carica i libri presenti nel file in due
  liste rispettivamente una contenente quelli disponibili e l'altra
  contenente quelli prestati.

  2. Prestito: dato il codice libro, rimuove tale libro (se
  esiste) dalla lista deli libri disponibili e lo aggiunge a
  quella deli libri prestati.

  3. EstraiLibriDiInteresse: dato un costo massimo settimanale,
  seleziona dalla lista dei libri disponibili quelli che
  soddisfano tale criterio e li inserisce in un apposito vettore di
  libri.

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funzione.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Libro
{
	char  codice[9];
	char  titolo[64];
	char  genere[16];
	float costo;
} TLibro;

typedef struct NodoLibro {
	TLibro           info;
	struct NodoLibro* next;
} TNodoLibro;

typedef TNodoLibro* TListaLibri;


/* AggiungiLibro inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiLibro(TListaLibri* plis, TLibro elem)
{
	TListaLibri paux;

	paux = (TListaLibri)malloc(sizeof(TNodoLibro));

	if (paux == NULL)
		return 0;

	paux->info = elem;
	paux->next = *plis;

	*plis = paux;

	return 1;
}

/*
  1. CaricaLibri: carica i libri presenti nel file in due
  liste rispettivamente una contenente quelli disponibili e l'altra
  contenente quelli prestati.


  Parametri di ingresso: nome del file
  Parametri di uscita: lista deli libri disponibili (disponibili),
  lista deli libri prestati (prestati)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
*/
int CaricaLibri(char* nome_file, TListaLibri* disponibili, TListaLibri* prestati)
{
	// Implementare il corpo della funzione
	FILE* fp = fopen(nome_file, "r");
	if (fp == NULL)
		return 0;
	char tipo[128];
	TLibro L;
	while (fscanf(fp, "%s%s%s%f%s", L.codice, L.titolo, L.genere, &L.costo, tipo) == 5) 
	{
		if (strcmp(tipo, "disponibile") == 0) 
		{
			if(!AggiungiLibro(disponibili, L))
				return 0;
		}
		else if(strcmp(tipo, "prestato") == 0)
		{
			if (!AggiungiLibro(prestati, L))
				return 0;
		}
	}
	return 1;
}

/*
  RicercaLibro: ricerca nella lista lis il libro con il
  codice fornito in ingresso (codice). Restituisce NULL se
  il libro con quel codice non è presente nella lista
  lis.
*/
TListaLibri RicercaLibro(TListaLibri lis, char* codice)
{
	while (lis != NULL)
	{
		if (strcmp(codice, lis->info.codice) == 0)
			return (lis);
		lis = lis->next;
	}
	return(NULL);
}

/*
  CancellaLibro: ricerca nella lista lis il libro con numero
  di codice fornito in ingresso (codice) e lo rimuove dalla lista.
*/
void CancellaLibro(TListaLibri* lis, char* codice)
{
	// Implementare il corpo della funzione
	TNodoLibro* aux;
	if ((*lis) == NULL)
	{
		return;
	}
	if (strcmp((*lis)->info.codice, codice) == 0)
	{
		aux = (*lis);
		(*lis) = (*lis)->next;
		free(aux);
		return;
	}
	else
		return CancellaLibro(&((*lis)->next), codice);
}

/*
  2. Prestito: dato il codice libro, rimuove tale libro (se
  esiste) dalla lista dei libri disponibili e la aggiunge a quella
  dei libri prestati.

  Parametri di ingresso:
  numero codice libro,

  Parametri di ingresso/uscita:
  lista dei libri disponibili (disponibili),
  lista dei libri prestati (prestati)

  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
*/

int Prestito(char* codice, TListaLibri* disponibili, TListaLibri* prestati)
{
	// Implementare il corpo della funzione
	if ((*disponibili) == NULL)
		return 0;
	TLibro LibroAux;
	if (strcmp((*disponibili)->info.codice, codice) == 0)
	{
		LibroAux = (*disponibili)->info;
		AggiungiLibro(prestati, LibroAux);
		CancellaLibro(disponibili, codice);
		return 1;
	}
	else
		return Prestito(codice, &((*disponibili)->next), prestati);
}

/*
  3. EstraiLibriDiInteresse: dato un costo massimo giornaliero,
  seleziona dalla lista deli libri disponibili quelli che
  soddisfano tale criterio e li inserisce in un apposito vettore di
  libri.

  Parametri di ingresso:
  lis - lista deli libri disponibili,
  genere - genere libro

  Parametri di uscita:
  dim - numero di libri che soddisfano i criteri

  Valore restituito:
  TLibro* - vettore deli libri selezionate
*/
TLibro* EstraiLibriDiInteresse(TListaLibri lis, float max_costo, char* genere, int* dim)
{
	// Implementare il corpo della funzione
	TLibro* vettore = NULL;
	(*dim) = 0;
	TListaLibri Corrente = lis;
	while (Corrente != NULL) 
	{
		if ((strcmp(Corrente->info.genere, genere) == 0) && (Corrente->info.costo <= max_costo))
		{
			(*dim)++;
		}
		Corrente = Corrente->next;
	}
	vettore = (TLibro*)malloc(sizeof(TLibro) * (*dim));
	int index = 0;
	Corrente = lis;
	while (Corrente != NULL)
	{
		if ((strcmp(Corrente->info.genere, genere) == 0) && (Corrente->info.costo <= max_costo))
		{
			vettore[index++] = Corrente->info;
		}
		Corrente = Corrente->next;
	}
	return vettore;
}


/*
  VisualizzaLibri visualizza le informazioni dei libri
  nella lista passata come parametro
*/
void VisualizzaLibri(TListaLibri lis)
{
	while (lis != NULL)
	{
		printf("%s %s %s %.3f\n", lis->info.codice, lis->info.titolo, lis->info.genere, lis->info.costo);
		lis = lis->next;
	}
}

/*
  VisualizzaVettoreLibri visualizza le informazioni dei libri
  contenute nel vettore passato come parametro
*/
void VisualizzaVettoreLibri(TLibro v[], int dim)
{
	// Implementare il corpo della funzione
	for (int i = 0; i < dim; i++) 
	{
		printf("%s %s %s %.2f\n", v[i].codice, v[i].genere, v[i].titolo, v[i].costo);
	}
}



int Menu()
{
	int scelta;

	printf("*** M E N U ***\n"
		"1 - Carica libri\n"
		"2 - Prestito libro\n"
		"3 - Cerca libri di interesse \n"
		"0 - Uscita\n\n"
		"Scelta: ");
	scanf("%d", &scelta);

	return scelta;
}

void DisallocaLista(TListaLibri* lista)
{
	// Implementare il corpo della funzione
	TListaLibri aux;
	while ((*lista) != NULL) 
	{
		aux = (*lista);
		(*lista) = (*lista)->next;
		free(aux);
	}
}


int main(void)
{
	TListaLibri disponibili = NULL;
	TListaLibri prestati = NULL;

	int         scelta;
	char        nomefile[32];
	char        codice[8];
	char        cat[16];
	int         dim;
	float       costo_max;
	TLibro* vett = NULL;
	int e;

	do {
		scelta = Menu();

		switch (scelta)
		{
		case 1:
			// acquisire il nome del file
			// invocare la funzione CaricaLibri
			// visualizzare le liste ottenute
			printf("Inserisci il nome del file: ");
			scanf("%s", nomefile);
			e = CaricaLibri(nomefile, &disponibili, &prestati);
			if (e == 1) 
			{
				printf("-------------------\n");
				VisualizzaLibri(disponibili);
				printf("-------------------\n");
				VisualizzaLibri(prestati);
			}
			printf("\n");
			break;

		case 2:
			// acquisire il codice libro da prestare
			// invocare la funzione Prestito
			// visualizzare le liste modificate
			printf("Inserisci il codice del libro: ");
			scanf("%s", codice);
			Prestito(codice, &disponibili, &prestati);
			printf("-------------------\n\n");
			VisualizzaLibri(disponibili);
			printf("-------------------\n\n");
			VisualizzaLibri(prestati);
			printf("\n");
			break;
		case 3:
			// acqusire il costo massimo
			// acquisire una categora
			// invocare la funzione EstraiLibriDiInteresse
			// visualizzare il vettore restituito
			printf("Inserisci il costo massimo: ");
			scanf("%f", &costo_max);
			printf("Inserisci una categoria: ");
			scanf("%s", cat);
			vett = EstraiLibriDiInteresse(disponibili, costo_max, cat, &dim);
			VisualizzaVettoreLibri(vett, dim);
			break;
		}

	} while (scelta != 0);

	// Didsallocare le liste
	free(vett);
	DisallocaLista(&disponibili);
	DisallocaLista(&prestati);
	return 0;
}

