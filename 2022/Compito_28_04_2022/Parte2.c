/*
Sviluppare un programma per l'analisi delle spese effettuate dai
clienti di una farmacia in una giornata. Le informazioni delle
spese effettuate dai clienti, monitorate da una batteria di 5 casse,
sono salvate in un file di testo in cui ogni riga contiene le seguenti
informazioni:

- Numero cassa (da 0 a 4)
- Orario (formato (hh:mm)
- Ricetta medica (si/no)
- Scarico fiscale (si/no)
- Totale spesa

Implementare le seguenti funzioni:

1) CaricaDati: Carica i dati contenuti nel file in un array di
liste. L'elemento dell'array di indice 'i' contiene la lista delle
informazioni di spesa effettuate dai clienti alla cassa numero 'i'. La
funzione restituisce il numero totale di clienti.

2) ContaRicette: Data una fascia oraria, restituisce un array in cui
l'elemento di indice 'i' contiene il numero di clienti che presentano
la ricetta medica rilevato dalla cassa numero i.

3) VisualizzaPercentualeClienti: Visualizza, per ogni cassa, la
percentuale di clienti che effettuano lo scarico fiscale sul totale
dei clienti transitati da quella cassa.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CASSE 5
#define NOME_FILE "acquisti.txt"

typedef struct Acquisto
{
	char  orario[16];
	int   ricetta_medica; // 1 = si, 0 = no
	int   scarico_fiscale; // 1 = si, 0 = no
	float totale;
} TAcquisto;

typedef struct NodoAcquisto
{
	TAcquisto            acquisto;
	struct NodoAcquisto* succ;
} TNodoAcquisto;

typedef TNodoAcquisto* PNodoAcquisto;


// Aggiunge un acquisto alla lista degli acquisti, restituisce 1 se
// l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiAcquisto(PNodoAcquisto* plista,TAcquisto acquisto)
{
	PNodoAcquisto p;

	p = (PNodoAcquisto)malloc(sizeof(TNodoAcquisto));
	if (p == NULL)
		return 0;

	p->acquisto = acquisto;
	p->succ = *plista;
	*plista = p;

	return 1;
}

/*
1) CaricaDati: Carica i dati contenuti nel file in un array di
liste. L'elemento dell'array di indice 'i' contiene la lista delle
informazioni di spesa effettuate dai clienti alla cassa numero 'i'. La
funzione restituisce il numero totale di clienti.

Parametri: nome del file, array di liste di acquisti in cassa
Restituisce: il numero totale di clienti, -1 in caso di errore
durante il caricamento
*/
int CaricaDati(char* nome_file,PNodoAcquisto* acquisti)
{
	// Implementare il corpo della funzione
	FILE* fp;
	int numero_cassa;
	TAcquisto aux;
	fp = fopen(nome_file, "r");
	if (fp == NULL) 
	{
		printf("Impossibile aprire il file.");
		return -1;
	}
	int num_clienti_tot = 0;
	while (fscanf(fp, "%d%s%d%d%f", &numero_cassa, aux.orario, &aux.ricetta_medica, &aux.scarico_fiscale, &aux.totale) == 5) 
	{
		if (!AggiungiAcquisto(&acquisti[numero_cassa], aux))
		{
			return -1;
		}
		else
			num_clienti_tot++;
	}
	return num_clienti_tot;
}

/*
2) ContaRicette: Data una fascia oraria, restituisce un array in cui
l'elemento di indice 'i' contiene il numero di clienti che presentano
la ricetta medica rilevato dalla cassa numero i.

Parametri: fascia oraria (orario inizio e orario fine), array di liste

Restituisce un array con il numero di clienti che presentano la
ricetta medica rilevati in ogni cassa
*/
int* ContaRicette(PNodoAcquisto* acquisti, char* orario_inizio, char* orario_fine)
{
	// Implementare il corpo della funzione
	int* vettore_clienti = malloc(sizeof(int)*NUM_CASSE);
	PNodoAcquisto aux;
	int contatore;
	for (int i = 0; i < NUM_CASSE; i++) 
	{
		aux = acquisti[i];
		contatore = 0;
		while (aux != NULL) 
		{
			// considero l'intervallo comprendendo orario inizio ed essendo strettamente minore di orario fine
			if ((strcmp(aux->acquisto.orario, orario_inizio) >= 0) && (strcmp(aux->acquisto.orario, orario_fine) < 0) && (aux->acquisto.ricetta_medica == 1))
			{
				contatore++;
			}
			aux = aux->succ;
		}
		vettore_clienti[i] = contatore;
	}
	return vettore_clienti;
}

/*
3) VisualizzaPercentualeClienti: Visualizza, per ogni cassa, la
percentuale di clienti che effettuano lo scarico fiscale sul totale
dei clienti transitati da quella cassa.
*/
void VisualizzaPercentualeClienti(PNodoAcquisto* acquisti)
{
	// Implementare il corpo della funzione
	PNodoAcquisto aux;
	int contatore_totali;
	int num_clienti;
	float percentuale[NUM_CASSE];
	for (int i = 0; i < NUM_CASSE; i++) 
	{
		aux = acquisti[i];
		contatore_totali = 0;
		num_clienti = 0;
		while (aux != NULL) 
		{
			if (aux->acquisto.scarico_fiscale == 1)
			{
				num_clienti++;
			}
			contatore_totali++;
			aux = aux->succ;
		}
		percentuale[i] = (((float)num_clienti / (float)contatore_totali) * 100.0);
	}
	printf("-------PERCENTUALI PER CIASCUNA CASSA-------\n");
	for (int i = 0; i < NUM_CASSE; i++) 
	{
		printf("CASSA %d : %.2f\n", i + 1, percentuale[i]);
	}
}

//  Disalloca una lista di acquisti
void DisallocaAcquisti(PNodoAcquisto acquisti)
{
	PNodoAcquisto p;

	while (acquisti != NULL)
	{
		p = acquisti;
		acquisti = acquisti->succ;
		free(p);
	}
}

int Menu()
{
	int scelta;

	printf("*** MENU ***\n"
		"1. Carica dati\n"
		"2. Conta ricette\n"
		"3. Visualizza percentuale clienti\n"
		"0. Esci\n\n"
		"Scelta: ");
	scanf("%d", &scelta);

	return scelta;
}

int main(void)
{
	int           scelta, n;
	PNodoAcquisto acquisti[NUM_CASSE];
	int* totale_ricette;
	char          ora_inizio[16], ora_fine[16];
	// Inizializzazione vettore di liste
	for (int i = 0; i < NUM_CASSE; i++) 
	{
		acquisti[i] = NULL;
	}

	do {
		scelta = Menu();

		switch (scelta)
		{
		case 1:
			// Invocare la funzione CaricaDati e visualizzare il numero di
			// acquisti effettuati o gli eventuali errori
			n = CaricaDati(NOME_FILE, &acquisti);
			printf("Sono stati effettuati %d acquisti.\n", n);
			break;

		case 2:
			// Acquisire la fascia oraria
			printf("Inserisci un orario di inizio: ");
			scanf("%s", ora_inizio);
			printf("Inserisci un orario di fine: ");
			scanf("%s", ora_fine);
			// Invocare la funzione ContaRicette
			totale_ricette = ContaRicette(acquisti, ora_inizio, ora_fine);
			// Visualizzare il numeri di acquisti con ricetta medica
			printf("VETTORE RISULTANTE:\n");
			for (int i = 0; i < NUM_CASSE; i++) 
			{
				printf("CASSA %d : %d\n", i + 1, totale_ricette[i]);
			}
			break;

		case 3:
			// Invocare la funzione VisualizzaPercentualeClienti
			VisualizzaPercentualeClienti(acquisti);
			break;
		}
	} while (scelta != 0);

	// Disallocare la memoria

	for (int i = 0; i < NUM_CASSE; i++)
	{
		DisallocaAcquisti(acquisti[i]);
	}
	return 0;
}
