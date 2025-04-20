/*
Sviluppare un programma per la gestione dei dati raccolti da una rete
di sensori di umidità del terreno e di temperatura in ambto
agricoltura di precisione. Ogni sensore trasmette periodicamente le
seguenti informazioni che sono memorizzate in un file unitamente alla
data e all'orario di ricezione.

- Codice del sensore (numero intero)
- Temperatura attuale (numero intero)
- Umidità attuale (numero intero)
- Data della misurazione (nel formato aaaa-mm-gg)
- Orario della misurazione (nel formato hh:mm:ss)

L'area monitorata è suddivisa in 10 sotto-aree ciascuna delle quali è
monitorata da al più 10 sensori. Il codice del sensore identifica
l'area. Es. Sensori con codice da 0 a 9 identificano la prima area,
quelli da 10 a 19 la seconda area, ..., quelli da 90 a 99 la
decima area.

Implementare le seguenti funzioni:

1) CaricaMisurazioni: Carica le misurazioni dal file 'misurazioni.txt'
e le memorizza in un array di liste. L'elemento i-esimo dell'array
contiene la lista delle misurazioni dei sensori relativi all'area
i-esima (sensori con codice da i*10 a i*10+10-1). La funzione
restituisce il numero totale di misurazioni caricate o -1 in caso di
errore durante il caricamento.

2) MisurazioniAnno: Dato l'array di liste di misurazioni, un
anno di riferimento ed il codice di un sensore, restituisce la lista
delle misurazioni di quel sensore relativo all'anno di riferimento.

3) VisualizzaMisureIntervallo: Dato l'array di liste di misurazioni,
un intervallo di temperature ed un intervallo di umidità, visualizza
tutte le misurazioni con temperatura e umidità compresi negli
intervalli dati.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_AREE 10
#define NOMEFILE "misurazioni.txt"

typedef struct Misurazione
{
	int  codice;
	int  temperatura;
	int  umidita;
	char data[16];
	char orario[16];
} TMisurazione;

typedef struct NodoListaMisurazioni
{
	TMisurazione                 misurazione;
	struct NodoListaMisurazioni* succ;
} TNodoListaMisurazioni;

typedef TNodoListaMisurazioni* PNodoListaMisurazioni;


// Visualizza una misurazione
void VisualizzaMisurazione(TMisurazione misurazione)
{
	printf("%d %d %d %s %s\n", misurazione.codice,
		misurazione.temperatura, misurazione.umidita,
		misurazione.data, misurazione.orario);
}


// Visualizza le misurazioni di una lista di misurazioni
void VisualizzaMisurazioni(PNodoListaMisurazioni lista)
{
	printf("codice temperatura umidità data orario\n");
	while (lista != NULL)
	{
		VisualizzaMisurazione(lista->misurazione);
		lista = lista->succ;
	}
}

// Aggiunge una misurazione alla lista di misurazioni, restituisce 1
// se l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiMisurazione(PNodoListaMisurazioni* plista,
	TMisurazione misurazione)
{
	PNodoListaMisurazioni p;

	p = (PNodoListaMisurazioni)malloc(sizeof(TNodoListaMisurazioni));
	if (p == NULL)
		return 0;

	p->misurazione = misurazione;
	p->succ = *plista;
	*plista = p;

	return 1;
}

int RestituisciIndice(TMisurazione p)
{
	if ((p.codice >= 0) && (p.codice < 10)) 
	{
		return 0;
	}
	if ((p.codice >= 10) && (p.codice < 20))
	{
		return 1;
	}
	if ((p.codice >= 20) && (p.codice < 30))
	{
		return 2;
	}
	if ((p.codice >= 30) && (p.codice < 40))
	{
		return 3;
	}
	if ((p.codice >= 40) && (p.codice < 50))
	{
		return 4;
	}
	if ((p.codice >= 50) && (p.codice < 60))
	{
		return 5;
	}
	if ((p.codice >= 60) && (p.codice < 70))
	{
		return 6;
	}
	if ((p.codice >= 70) && (p.codice < 80))
	{
		return 7;
	}
	if ((p.codice >= 80) && (p.codice < 90))
	{
		return 8;
	}
	if ((p.codice >= 90) && (p.codice < 100))
	{
		return 9;
	}
	
}

/*
1) CaricaMisurazioni: Carica le misurazioni dal file 'misurazioni.txt'
e le memorizza in un array di liste. L'array è composto da 5
elementi. L'elemento i-esimo dell'array contiene la lista delle
misturazioni dei sensori dal codice i*10 al codice i*10+10-1. La
funzione restituisce il numero totale di misurazioni caricate o -1 in
caso di errore durante il caricamento.

Parametri: nome del file, array di liste di misurazioni
Restituisce: il numero totale di misurazioni acquisite, -1 in caso di
errore durante il caricamento
*/
int CaricaMisurazioni(char* nome_file, PNodoListaMisurazioni* misurazioni)
{
	// Sviluppare il corpo della funzione
	// ...
	FILE* fp = fopen(nome_file, "r");
	if (fp == NULL)
	{
		printf("Impossibile aprire il file.");
		return -1;
	}
	TMisurazione aux;
	int indice;
	int r = -1;
	while (fscanf(fp, "%d%d%d%s%s", &aux.codice, &aux.temperatura, &aux.umidita, aux.data, aux.orario) == 5)
	{
		if (aux.codice >= 100)
			continue;
		indice = RestituisciIndice(aux);
		if (AggiungiMisurazione(&misurazioni[indice], aux) == 1)
		{
			r++;
		}
	}
	return r;
}

/*
2) MisurazioniAnno: Dato l'array di liste di misurazioni, un anno di
riferimento ed il codice di un sensore, restituisce la lista delle
misurazioni di quel sensore relativo all'anno di riferimento.

Parametri: array di liste di misurazioni, anno di riferimento, codice
sensore
Restituisce: Lista di misurazioni del sensore nell'anno di riferimento
*/
PNodoListaMisurazioni MisurazioniAnno(PNodoListaMisurazioni* misurazioni, char* anno, int codice)
{
	// Sviluppare il corpo della funzione
	// ...
	PNodoListaMisurazioni aux;
	PNodoListaMisurazioni lista = NULL;
	char buffer[5];
	for (int i = 0; i < NUM_AREE; i++) 
	{
		aux = misurazioni[i];
		while (aux != NULL)
		{
			strncpy(buffer, aux->misurazione.data, 4);
			buffer[4] = '\0';
			if ((strcmp(buffer, anno) == 0) && (aux->misurazione.codice == codice)) 
			{
				AggiungiMisurazione(&lista, aux->misurazione);
			}
			aux = aux->succ;
		}
	}
	return lista;
}

/*
3) VisualizzaMisureIntervallo: Dato l'array di liste di misurazioni,
un intervallo di temperature ed un intervallo di umidità, visualizza
tutte le misurazioni con temperatura e umidità compresi negli
intervalli dati.

Parametri: array di liste di misurazioni, temperatura minima,
temperatura massima, umidità minima, umidità massima
*/
void VisualizzaMisureIntervallo(PNodoListaMisurazioni* misurazioni, int temperatura_min, int temperatura_max, int umidita_min, int umidita_max)
{
	// Sviluppare il corpo della funzione
	// ...
	PNodoListaMisurazioni aux;
	printf("MISURAZIONI\n");
	for (int i = 0; i < NUM_AREE; i++)
	{
		aux = misurazioni[i];
		while (aux != NULL) 
		{
			if ((aux->misurazione.temperatura >= temperatura_min)
				&& (aux->misurazione.temperatura < temperatura_max) 
				&& (aux->misurazione.umidita >= umidita_min) 
				&& (aux->misurazione.umidita < umidita_max))
			{
				printf("%d %d %d %s %s\n", aux->misurazione.codice, aux->misurazione.temperatura, aux->misurazione.umidita, aux->misurazione.data, aux->misurazione.orario);
			}
			aux = aux->succ;
		}
	}
}

//  Disalloca una lista di misurazioni
void DisallocaMisurazioni(PNodoListaMisurazioni misurazioni)
{
	PNodoListaMisurazioni p;

	while (misurazioni != NULL)
	{
		p = misurazioni;
		misurazioni = misurazioni->succ;
		free(p);
	}
}

int Menu()
{
	int scelta;

	printf("*** MENU ***\n"
		"1. Carica misurazioni\n"
		"2. Misurazioni anno\n"
		"3. Misurazioni intervallo\n"
		"0. Esci\n\n"
		"Scelta: ");
	scanf("%d", &scelta);

	return scelta;
}

int main(void)
{
	int                   scelta;
	// dichiarare le variabili necessarie
	PNodoListaMisurazioni vettore[NUM_AREE] = { NULL };
	PNodoListaMisurazioni lista_out = NULL;
	TMisurazione misurazione;
	int n;
	char anno[5];
	int codice_sensore;
	int temp_min;
	int temp_max;
	int um_min;
	int um_max;

	do {
		scelta = Menu();

		switch (scelta)
		{
		case 1:
			// Invocare la funzione CaricaMisurazioni e visualizzare il
			// numero di misurazioni caricate o l'eventuale messaggio di
			// errore
			n = CaricaMisurazioni(NOMEFILE, vettore);
			if (n == -1) 
			{
				printf("Errore durante il caricamento.");
			}
			else 
			{
				printf("Sono stati caricate %d misurazioni.", n);
			}
			printf("\n");
			break;

		case 2:
			// Acquisire l'anno ed il codice del sensore, invocare la
			// funzione MisurazioniAnno, visualizzare la lista delle
			// misurazioni ottenuta e disallocare la lista.
			printf("Inserisci anno: ");
			scanf("%s", anno);
			printf("\nInserisci codice: ");
			scanf("%d", &codice_sensore);
			lista_out = MisurazioniAnno(vettore, anno, codice_sensore);
			printf("---------------LISTA FINALE---------------\n");
			VisualizzaMisurazioni(lista_out);
			printf("\n");
			break;

		case 3:
			// Acquisire gli intervalli di temperatura e di umidità ed
			// invocare la funzione VisualizzaMisureIntervallo
			printf("Inserisci la temperatura minima: ");
			scanf("%d", &temp_min);
			printf("\nInserisci la temperatura massima: ");
			scanf("%d", &temp_max);
			printf("\nInserisci l'umidita' minima: ");
			scanf("%d", &um_min);
			printf("\nInserisci l'umidita' massima: ");
			scanf("%d", &um_max);
			VisualizzaMisureIntervallo(vettore, temp_min, temp_max, um_min, um_max);
			break;
		}
	} while (scelta != 0);

	// Disallocare le liste nel vettore delle misurazioni
	DisallocaMisurazioni(lista_out);
	for (int i = 0; i < NUM_AREE; i++) 
	{
		DisallocaMisurazioni(vettore[i]);
	}
	return 0;
}
