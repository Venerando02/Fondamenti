/*
Sviluppare un programma per la gestione dei dati delle precipitazioni piovose giornaliere raccolti da una rete di
sensori distribuiti su un'area suddivisa in 10 settori.
Ogni sensore trasmette giornalmente le seguenti informazioni che sono memorizzate in un file unitamente 
all'identificativo del settore ed alla data:
- Identificativo settore (numero intero da 0 a 9)
- Codice del sensore (numero intero)
- Valore mm pioggia (numero intero)
- Data della misurazione (nel formato aaaa-mm-gg)


Implementare le seguenti funzioni:

1) CaricaMisure:
Carica le misurazioni dal file 'datiprecipitazioni.txt' e le memorizza in un array di liste. 
L'elemento i-esimo dell'array contiene la lista delle misurazioni dei sensori relativi al settore i-esimo. 
La funzione restituisce il numero totale di misurazioni caricate o -1 in caso di errore durante il caricamento.

2) TotaleSettori:
Dato l'array di liste di misurazioni ed un giorno, calcola e restituisce in un vettore il totale delle precipitazioni
avvenute quel giorno per ogni singolo settore.

3) ValoriOltreSoglia:
Dato l'array di liste di misurazioni ed un valore soglia, estrae e restituisce in una lista di misurazioni,
tutti i dati dei sensori aventi un valore di precipitazioni maggiore del valore soglia fornito come parametro.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SETTORI 10

typedef struct Misura
{
	int  codice;
	int  valore;
	char data[16];
} TMisura;

typedef struct NodoListaMisura
{
	TMisura                 info;
	struct NodoListaMisura* next;
} TNodoListaMisura;

typedef TNodoListaMisura* PNodoListaMisura;


// Visualizza una misurazione
void VisualizzaMisura(TMisura misura) {
	printf("%d %d %s\n", misura.codice,
		misura.valore, misura.data);
}


// Visualizza le misurazioni di una lista di misurazioni
void VisualizzaDatiLista(PNodoListaMisura lista) 
{
	// Implementare il corpo della funzione
	while (lista != NULL) 
	{
		VisualizzaMisura(lista->info);
		lista = lista->next;
	}
	printf("\n");
}

// Aggiunge una misurazione alla lista di misurazioni, restituisce 1
// se l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiNodoLista(PNodoListaMisura* plista, TMisura elem) 
{
	PNodoListaMisura p;

	p = (PNodoListaMisura)malloc(sizeof(TNodoListaMisura));
	if (p == NULL)
		return 0;

	p->info = elem;
	p->next = *plista;
	*plista = p;

	return 1;
}

/*
1) CaricaMisure:
Carica le misurazioni dal file 'datiprecipitazioni.txt' e le memorizza in un array di liste. L'array è composto da 10 elementi. L'elemento i-esimo dell'array contiene la lista delle misurazioni dei sensori relativi al settore i-esimo. La funzione restituisce il numero totale di misurazioni caricate o -1 in caso di errore durante il caricamento.

Parametri: nome del file, array di liste di misurazioni
Restituisce: il numero totale di misurazioni acquisite, -1 in caso di
errore durante il caricamento
*/
int CaricaMisure(char* nome_file, PNodoListaMisura* misure) 
{
	// Implementare il corpo della funzione
	int n = 0;
	int id;
	TMisura m;
	FILE* fp = fopen(nome_file, "r");
	if (fp == NULL)
		return -2;
	while (fscanf(fp, "%d%d%d%s", &id, &m.codice, &m.valore, m.data) == 4) 
	{
		if (!AggiungiNodoLista(&misure[id], m))
			return -1;
		else
			n++;
	}
	fclose(fp);
	return n;
}

/*
2) TotaleSettori:
Dato l'array di liste di misurazioni ed un giorno, calcola e restituisce in un vettore il totale delle 
precipitazioni avvenute quel giorno per ogni singolo settore.

Parametri: array di liste di misurazioni, giorno
Restituisce: Vettore in l'elemento i-esimo rappresenta il totale delle precipitazioni avvenute quel giorno per 
il settore i-esimo.
*/

int* TotaleSettori(PNodoListaMisura* misure, char* giorno) 
{
	// Implementare il corpo della funzione
	PNodoListaMisura ListaAux;
	int* vet = (int*)malloc(sizeof(int)*NUM_SETTORI);
	if (vet == NULL)
		return NULL;
	int cont;
	for (int i = 0; i < NUM_SETTORI; i++) 
	{
		cont = 0;
		ListaAux = misure[i];
		while (ListaAux != NULL) 
		{
			if (strcmp(ListaAux->info.data, giorno) == 0) 
			{
				cont++;
			}
			ListaAux = ListaAux->next;
		}
		vet[i] = cont;
	}
	return vet;
}


/*
3) ValoriOltreSoglia:
Dato l'array di liste di misurazioni ed un valore soglia, estrae e restituisce in una lista di misurazioni, 
tutti i dati dei sensori aventi un valore di precipitazioni maggiore del valore soglia fornito come parametro.

Parametri: array di liste di misurazioni, valore soglia di precipitazioni
Restituisce: lista con i dati dei sensori aventi un valore di precipitazioni maggiore del valore soglia fornito come
parametro
*/

PNodoListaMisura ValoriOltreSoglia(PNodoListaMisura* misure, int soglia) 
{
	// Implementare il corpo della funzione
	PNodoListaMisura ListaOut = NULL;
	PNodoListaMisura ListaAux;
	for (int i = 0; i < NUM_SETTORI; i++) 
	{
		ListaAux = misure[i];
		while (ListaAux != NULL) 
		{
			if (ListaAux->info.valore > soglia) 
			{
				if(!AggiungiNodoLista(&ListaOut, ListaAux->info))
					return NULL;
			}
			ListaAux = ListaAux->next;
		}
	}
	return ListaOut;
}


//  Disalloca una lista di misurazioni
void DisallocaLista(PNodoListaMisura lista) {
	PNodoListaMisura paux;

	while (lista != NULL)
	{
		paux = lista;
		lista = lista->next;
		free(paux);
	}
}

int Menu() {
	int scelta;

	printf("*** MENU ***\n"
		"1. Carica dati dal file\n"
		"2. Totale settori\n"
		"3. Valori superiori alla soglia\n"
		"0. Esci\n\n"
		"Scelta: ");
	scanf("%d", &scelta);

	return scelta;
}

int main(void) {
	int                   scelta;
	PNodoListaMisura vettore[NUM_SETTORI];
	int n;
	char giorno[16];
	int* totalesettori = NULL;
	int vsoglia;
	PNodoListaMisura listamaggiori = NULL;
	char Buffer[64];

	for (int i = 0; i < NUM_SETTORI; i++)
		vettore[i] = NULL;

	do {
		scelta = Menu();

		switch (scelta) {
		case 1:
			// Invocare la funzione CaricaMisure e visualizzare il numero di
			// misure caricate o gli eventuali errori
			printf("Inserisci il nome del file: ");
			scanf("%s", Buffer);
			n = CaricaMisure(Buffer, vettore);
			if (n == -2)
				printf("Impossibile apire il file.\n");
			else if (n == -1)
				printf("Errore durante il caricamento dei dati su array di liste.\n");
			else
				printf("Sono stati caricati %d elementi.\n", n);
			break;

		case 2:
			// acquisire il giorno
			printf("Inserisci un giorno: ");
			scanf("%s", giorno);
			// invocare la funzione TotaleSettori e visualizzare la pioggia totale per ogni settore
			totalesettori = TotaleSettori(vettore, giorno);
			printf("\n-----------\n");
			for (int i = 0; i < NUM_SETTORI; i++)
				printf("Settore %d: %d\n", i, totalesettori[i]);
			printf("\n");
			free(totalesettori);
			break;

		case 3:
			// acquisire il valore soglia di precipitazioni
			printf("Inserisci un valore di soglia: ");
			scanf("%d", &vsoglia);
			// invocare la funzione ValoriOltreSoglia
			listamaggiori = ValoriOltreSoglia(vettore, vsoglia);
			// visualizzare i risultati ottenuti
			VisualizzaDatiLista(listamaggiori);
			printf("\n");
			DisallocaLista(listamaggiori);
			break;
		}
	} while (scelta != 0);

	//disallocare la memoria
	for (int i = 0; i < NUM_SETTORI; i++)
		DisallocaLista(vettore[i]);

	return 0;
}
