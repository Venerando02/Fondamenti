/*
Sviluppare un programma per l'analisi dei pedaggi monitorati da un
casello autostradale in 24 ore. Le informazioni sul transito delle
vetture, monitorato da una batteria di 10 caselli, sono salvate in un
file di testo in cui ogni riga contiene le seguenti informazioni:

- Numero casello (da 0 a 9)
- Orario (formato (hh:mm:ss)
- Tipo vettura (es., "autovettura", "autobus", "autocarro",
  "autotreno", "motoveicolo")
- Località di ingresso ("messina", "roccalumera", "taormina",
  "giardini_naxos", "fiumefreddo", "giarre", "acireale")

Implementare le seguenti funzioni:

1) CaricaDati: Carica i dati contenuti nel file in un array di
liste. L'elemento dell'array di indice 'i' contiene la lista delle
informazioni di transito relative al casello numero 'i'. La funzione
restituisce il numero totale di transiti.

2) CalcolaPedaggi: Data una fascia oraria, restituisce un array in cui
l'elemento di indice 'i' contiene il costo totale dei pedaggi rilevato
dal casello numero i. Si assuma per semplicità che il costo del
pedaggio sia indipendente dal tipo di vettura. Si assumino i seguenti
costi in euro dei pedaggi:

Casello di ingresso | Costo pedaggio (Euro)
messina               4,00
roccalumera           3,00
taormina              2,00
giardini_naxos        1,50
fiumefreddo           1,20
giarre                0,70
acireale              0,50

3) VisualizzaPercentualeAuto: Visualizza, per ogni casello, la
percentuale di autovetture transitate sul totale delle vetture
transitate da quel casello.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CASELLI 10

typedef struct Transito
{
	char orario[16];
	char tipo_vettura[16];
	char ingresso[32];
} TTransito;

typedef struct NodoTransito
{
	TTransito            transito;
	struct NodoTransito* succ;
} TNodoTransito;

typedef TNodoTransito* PNodoTransito;


// Aggiunge un transito alla lista dei transiti, restituisce 1
// se l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiTransito(PNodoTransito* plista, TTransito transito)
{
	PNodoTransito p;

	p = (PNodoTransito)malloc(sizeof(TNodoTransito));
	if (p == NULL)
		return 0;

	p->transito = transito;
	p->succ = *plista;
	*plista = p;

	return 1;
}

/*
1) CaricaDati: Carica i dati contenuti nel file in un array di
liste. L'elemento dell'array di indice 'i' contiene la lista delle
informazioni di transito relativi al casello numero 'i'. La funzione
restituisce il numero totale di transiti.

Parametri: nome del file, array di liste di transiti
Restituisce: il numero totale di transiti, -1 in caso di errore
durante il caricamento
*/
int CaricaDati(char* nome_file, PNodoTransito* transiti)
{
	// Implementare il corpo della funzione
	int casello;
	TTransito t;
	FILE* fp = fopen(nome_file, "r");
	if (fp == NULL)
		return -1;
	int n = 0;
	while (fscanf(fp, "%d%s%s%s", &casello, t.orario, t.tipo_vettura, t.ingresso) == 4) 
	{
		if (!(AggiungiTransito(&transiti[casello], t))) 
		{
			return -1;
		}
		else 
		{
			n++;
		}
	}
	fclose(fp);
	return n;
}

/*
2) CalcolaPedaggi: Data una fascia oraria, restituisce un array in cui
l'elemento di indice 'i' contiene il costo totale dei pedaggi
rilevato dal casello numero i. Si assuma per semplicità che il
pedaggio sia indipendente dal tipo di vettura. Si assumino i seguenti
costi in euro dei pedaggi:

Casello di ingresso | Costo pedaggio (Euro)
messina               4,00
roccalumera           3,00
taormina              2,00
giardini_naxos        1,50
fiumefreddo           1,20
giarre                0,70
acireale              0,50

Parametri: fascia oraria (orario inizio e orario fine), array di liste
Restituisce un array con il totale dei dei costi di pedaggio rilevati
in ogni casello
*/

float pedaggio(char* casello) 
{
	if (strcmp("messina", casello) == 0)
		return 4.00;
	else if (strcmp("roccalumera", casello) == 0)
		return 3.00;
	else if (strcmp("taormina", casello) == 0)
		return 2.00;
	else if (strcmp("giardini_naxos", casello) == 0)
		return 1.50;
	else if (strcmp("fiumefreddo", casello) == 0)
		return 1.20;
	else if (strcmp("giarre", casello) == 0)
		return 0.70;
	else if (strcmp("acireale", casello) == 0)
		return 0.50;
}

float* CalcolaPedaggi(PNodoTransito* transiti, char* orario_inizio, char* orario_fine)
{
	// Implementare il corpo della funzione
	float* tot_transiti = malloc(sizeof(float) * NUM_CASELLI);
	PNodoTransito l;
	float somma;
	float valore;
	for (int i = 0; i < NUM_CASELLI; i++) 
	{
		l = transiti[i];
		somma = 0.0;
		while (l != NULL)
		{
			if ((strcmp(l->transito.orario, orario_inizio) >= 0) && (strcmp(l->transito.orario, orario_fine) < 0)) 
			{
				valore = pedaggio(l->transito.ingresso);
				somma += valore;
			}
			l = l->succ;
		}
		tot_transiti[i] = somma;
	}
	return tot_transiti;
}


/*
3) VisualizzaPercentualeAuto: Visualizza, per ogni casello, la
percentuale di autovetture transitate sul totale delle vetture
transitate da quel casello.

Parametri: array di liste di transiti
*/
void VisualizzaPercentualeAuto(PNodoTransito* transiti)
{
	// Implementare il corpo della funzione
	PNodoTransito l;
	float* vpercentuali = malloc(sizeof(float) * NUM_CASELLI);
	int ntot;
	int nvet;
	for (int i = 0; i < NUM_CASELLI; i++) 
	{
		l = transiti[i];
		ntot = 0;
		nvet = 0;
		while (l != NULL)
		{
			ntot++;
			if (strcmp(l->transito.tipo_vettura, "autovettura") == 0) 
			{
				nvet++;
			}
			l = l->succ;
		}
		vpercentuali[i] = ((float)(nvet) / (float)(ntot)) * 100.0;
	}
	printf("PERCENTUALI PER CASELLO:\n");
	for (int i = 0; i < NUM_CASELLI; i++)
	{
		printf("CASELLO %d = %.3f\n", i+1 , vpercentuali[i]);
	}
}


//  Disalloca una lista di transiti
void DisallocaTransiti(PNodoTransito transiti)
{
	PNodoTransito p;

	while (transiti != NULL)
	{
		p = transiti;
		transiti = transiti->succ;
		free(p);
	}
}

int Menu()
{
	int scelta;

	printf("*** MENU ***\n"
		"1. Carica dati\n"
		"2. Calcola pedaggi\n"
		"3. Visualizza percentuale auto\n"
		"0. Esci\n\n"
		"Scelta: ");
	scanf("%d", &scelta);

	return scelta;
}

int main(void)
{
	// Dichiarare le variabili opportune
	PNodoTransito vettore[NUM_CASELLI] = { NULL };
	float* transiti = NULL;
	char buffer[64];
	char ora_inizio[32];
	char ora_fine[32];
	int scelta;
	int n;
	do {
		scelta = Menu();

		switch (scelta)
		{
		case 1:
			// Invocare la funzione CaricaDati
			printf("Inserisci il nome del file: ");
			scanf("%s", buffer);
			n = CaricaDati(buffer, vettore);
			printf("Sono stati caricati %d transiti\n", n);
			break;

		case 2:
			// Acquisire la fascia oraria
			// Invocare la funzione CalcolaPedaggi
			// Visualizzare il totale dei pedaggi per ogni casello
			printf("Inserire l'orario di inizio: ");
			scanf("%s", ora_inizio);
			printf("Inserire l'orario di fine: ");
			scanf("%s", ora_fine);
			transiti = CalcolaPedaggi(vettore, ora_inizio, ora_fine);
			printf("VETTORE PEDAGGI:\n");
			for (int i = 0; i < NUM_CASELLI; i++) 
			{
				printf("CASELLO %d: %.3f $\n", i, transiti[i]);
			}
			break;
		case 3:
			// Invocare la funzione VisualizzaPercentualeAuto
			VisualizzaPercentualeAuto(vettore);
			break;
		}
	} while (scelta != 0);

	// Disallocare la memoria allocata sfruttando la funzione
	// DisallocaTransiti
	for (int i = 0; i < NUM_CASELLI; i++)
		DisallocaTransiti(vettore[i]);
	free(transiti);
	return 0;
}
