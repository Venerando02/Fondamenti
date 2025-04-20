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
liste. L'elemento dell'array di inidice 'i' contiene la lista delle
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
liste. L'elemento dell'array di inidice 'i' contiene la lista delle
informazioni di transito relativi al casello numero 'i'. La funzione
restituisce il numero totale di transiti.

Parametri: nome del file, array di liste di transiti
Restituisce: il numero totale di transiti, -1 in caso di errore
durante il caricamento
*/
int CaricaDati(char* nome_file, PNodoTransito* transiti)
{
	// Implementare il corpo della funzione
	FILE* fp;
	int casello;
	TTransito aux;
	fp = fopen(nome_file, "r");
	if (fp == NULL)
		return -1;
	int n = 0;
	while (fscanf(fp, "%d%s%s%s", &casello, aux.orario, aux.tipo_vettura, aux.ingresso) == 4)
	{
		if (!AggiungiTransito(&transiti[casello], aux))
			return -1;
		else
			n++;
	}
	return n;
}


float CalcoloPedaggio(TTransito transito)
{
	if (strcmp(transito.ingresso, "messina") == 0)
		return 4.00;
	else if (strcmp(transito.ingresso, "roccalumera") == 0)
		return 3.00;
	else if (strcmp(transito.ingresso, "taormina") == 0)
		return 2.00;
	else if (strcmp(transito.ingresso, "giardini_naxos") == 0)
		return 1.50;
	else if (strcmp(transito.ingresso, "fiumefreddo") == 0)
		return 1.20;
	else if (strcmp(transito.ingresso, "giarre") == 0)
		return 0.70;
	else if (strcmp(transito.ingresso, "acireale") == 0)
		return 0.50;
}

/*
2) CalcolaPedaggi: Data una fascia oraria, restituisce un array in cui
l'elemento di indice 'i' contiene il costo totale deii pedaggi
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
float* CalcolaPedaggi(PNodoTransito* transiti, char* orario_inizio, char* orario_fine)
{
	// Implementare il corpo della funzione
	float* vout = malloc(sizeof(float) * NUM_CASELLI);
	PNodoTransito aux;
	float costo_transito;
	float somma;
	for (int i = 0; i < NUM_CASELLI; i++) 
	{
		somma = 0.0F;
		costo_transito = 0.0F;
		aux = transiti[i];
		while (aux != NULL) 
		{
			if ((strcmp(aux->transito.orario, orario_inizio) >= 0) && (strcmp(aux->transito.orario, orario_fine) < 0))
			{
				costo_transito = CalcoloPedaggio(aux->transito);
				somma += costo_transito;
			}
			aux = aux->succ;
		}
		vout[i] = somma;
	}
	return vout;
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
	int n;
	PNodoTransito aux;
	float* vout = malloc(sizeof(float) * NUM_CASELLI);
	int ntot;
	for (int i = 0; i < NUM_CASELLI; i++)
	{
		ntot = 0;
		n = 0;
		aux = transiti[i];
		while (aux != NULL) 
		{
			if (strcmp(aux->transito.tipo_vettura, "autovettura")) 
			{
				n++;
			}
			ntot++;
			aux = aux->succ;
		}
		vout[i] = (float)((float)(n) / (float)(ntot))*100.0F;
	}
	printf("---------------VETTORE PERCENTUALI----------------\n");
	for (int i = 0; i < NUM_CASELLI; i++) 
	{
		printf("CASELLO %d : %.3f percento\n", i+1, vout[i]);
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
	int scelta;
	PNodoTransito vettore[NUM_CASELLI] = { NULL };
	char orario_inizio[16];
	char orario_fine[16];
	char nome_file[32];
	float* vout;
	int num_dati;
	do {
		scelta = Menu();

		switch (scelta)
		{
		case 1:
			// Invocare la funzione CaricaDati
			printf("Inserisci nome file: ");
			scanf("%s", nome_file);
			num_dati = CaricaDati(nome_file, vettore);
			printf("\nSono stati caricati %d transiti.", num_dati);
			printf("\n");
			break;

		case 2:
			// Acquisire la fascia oraria
			printf("Inserisci ora inizio: ");
			scanf("%s", orario_inizio);
			printf("Inserisci ora fine: ");
			scanf("%s", orario_fine);
			// Invocare la funzione CalcolaPedaggi
			vout = CalcolaPedaggi(vettore, orario_inizio, orario_fine);
			// Visualizzare il totale dei pedaggi per ogni casello
			printf("--------------VETTORE FINALE------------------\n");
			for (int i = 0; i < NUM_CASELLI; i++)
				printf("CASELLO %d: %.3f\n", i + 1, vout[i]);
			printf("\n");
			break;

		case 3:
			// Invocare la funzione VisualizzaPercentualeAuto
			VisualizzaPercentualeAuto(vettore);
			printf("\n");
			break;
		}
	} while (scelta != 0);

	// Disallocare la memoria allocata sfruttando la funzione
	// DisallocaTransiti
	for (int i = 0; i < NUM_CASELLI; i++)
		DisallocaTransiti(vettore[i]);

	return 0;
}
