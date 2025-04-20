/* II prova in itinere - A.A. 2022/2023 */

/*
* Sviluppare un programma per la gestione degli eventi di un centro scommesse sportive. Gli eventi sono inizialmente memorizzati in un file di testo in cui ogni riga contiene i seguenti dati:
- sport (stringa come specificato in seguito)
- Codice Evento (stringa)
- Squadra 1 (stringa)
- Squadra 2 (stringa)
- Quota vittoria squadra 1 (reale)
- Quota vittoria squadra 2 (reale)

Gli sport che il centro gestisce sono 5 e ai fini del vettore sono identificati da un intero con la seguente corrispondenza:
CALCIO 0
BASKET 1
PALLAVOLO 2
RUGBY 3
PALLANUOTO 4

Implementare le seguenti funzioni:

1) CaricaDatiDaFile:
Carica i dati degli eventi sportivi dal file e le memorizza in un array di liste. L'elemento i-esimo dell'array contiene la lista degli eventi sportivi relativi allo sport i-esimo. La funzione restituisce il numero totale di eventi sportivi caricati o -1 in caso di errore durante il caricamento.

2) EventiQuoteMax:
Dato l'array di liste di eventi sportivi, calcola e restituisce in un opportuno vettore gli eventi aventi il valore massimo per una delle quote per ciascuno sport. Il vettore ha quindi un numero di elementi pari al numero di sport presenti.


3) EventiSportSquadra:
Dato l'array di liste di eventi sportivi, uno sport ed una squadra, estrae e restituisce in una lista di eventi sportivi, tutti gli eventi dello sport fornito che coinvologno la squadra fornita in ingresso come parametro.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

/*
COGNOME NOME Musumeci Venerando Pio
N. MATRICOLA 1000015141
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SPORT 5
#define DIMS 32

typedef struct Evento {
	char codice_evento[DIMS];
	char squadra1[DIMS];
	char squadra2[DIMS];
	float quota1;
	float quota2;
} TEvento;

typedef struct NodoListaEventi
{
	TEvento                 info;
	struct NodoListaEventi* next;
} TNodoListaEventi;

typedef TNodoListaEventi* T_ListaEventi;

// Visualizza i dati di una lista di eventi sportivi
void VisualizzaDatiLista(T_ListaEventi lista) 
{
	//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
	while (lista != NULL) 
	{
		printf("%s %s %s %.3f %.3f\n", lista->info.codice_evento, lista->info.squadra1, lista->info.squadra2, lista->info.quota1, lista->info.quota2);
		lista = lista->next;
	}
}

// Aggiunge un evento alla lista di eventi, restituisce 1
// se l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiNodoLista(T_ListaEventi* plista, TEvento elem) {
	T_ListaEventi p;

	p = (T_ListaEventi)malloc(sizeof(TNodoListaEventi));
	if (p == NULL)
		return 0;

	p->info = elem;
	p->next = *plista;
	*plista = p;

	return 1;
}

/*
1) CaricaDatiDaFile:
Carica i dati degli eventi sportivi dal file e le memorizza in un array di liste. 
L'elemento i-esimo dell'array contiene la lista degli eventi sportivi relativi allo sport i-esimo.
La funzione restituisce il numero totale di eventi sportivi caricati o -1 in caso di errore durante il caricamento.

Parametri: nome del file, array di liste di eventi sportivi
Restituisce: il numero totale di di eventi sportivi caricati, -1 in caso di
errore durante il caricamento

*/

int RitornaIndice(char* sport) 
{
	if (strcmp(sport, "CALCIO") == 0)
		return 0;
	if (strcmp(sport, "BASKET") == 0)
		return 1;
	if (strcmp(sport, "PALLAVOLO") == 0)
		return 2;
	if (strcmp(sport, "RUGBY") == 0)
		return 3;
	if (strcmp(sport, "PALLANUOTO") == 0)
		return 4;
}

char* RitornaSport(int indice)
{
	if (indice == 0)
		return "CALCIO";
	if (indice == 1)
		return "BASKET";
	if (indice == 2)
		return "PALLAVOLO";
	if (indice == 3)
		return "RUGBY";
	if (indice == 4)
		return "PALLANUOTO";
}


int CaricaDatiDaFile(char* nome_file, T_ListaEventi* eventi) {
	//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
	FILE* fp = fopen(nome_file, "r");
	if (fp == NULL)
		return -1;
	int num = 0;
	TEvento Evento;
	int i;
	char Sport[DIMS];
	while (fscanf(fp, "%s%s%s%s%f%f", Sport , Evento.codice_evento, Evento.squadra1, Evento.squadra2, &Evento.quota1, &Evento.quota2) == 6) 
	{
		i = RitornaIndice(Sport);
		if (!AggiungiNodoLista(&eventi[i], Evento))
			return -1;
		else
			num++;
	}
	fclose(fp);
	return num;
}


/*
2) EventiQuoteMax:
Dato l'array di liste di eventi sportivi, calcola e restituisce in un opportuno vettore gli eventi aventi il valore massimo 
per una delle quote per ciascuno sport.
Il vettore ha quindi un numero di elementi pari al numero di sport presenti.

Parametri: array di liste di eventi sportivi
Restituisce: Vettore di eventi sportivi in cui l'elemento i-esimo rappresenta l'evento avente quota di valore massimo per lo sport i-esimo
*/

TEvento* EventiQuoteMax(T_ListaEventi* eventi) {
	//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
	TEvento* Vout = (TEvento*)malloc(sizeof(TEvento)*NUM_SPORT);
	if (Vout == NULL)
		return NULL;
	TEvento EventoMax;
	T_ListaEventi ListaAux;
	for (int i = 0; i < NUM_SPORT; i++) 
	{
		ListaAux = eventi[i];
		EventoMax = ListaAux->info;
		while (ListaAux != NULL) 
		{
			if ((ListaAux->info.quota1 > EventoMax.quota1) || (ListaAux->info.quota2 > EventoMax.quota2)) 
			{
				EventoMax = ListaAux->info;
			}
			ListaAux = ListaAux->next;
		}
		Vout[i] = EventoMax;
	}
	return Vout;
}


/*
3) EventiSportSquadra:
Dato l'array di liste di eventi sportivi, uno sport ed una squadra,
la funzione estrae e restituisce in una lista di eventi sportivi tutti gli eventi dello sport fornito
che coinvolgono la squadra fornita in ingresso come parametro.

Parametri in ingresso: array di liste di eventi sportivi, codice sport, squadra
Restituisce: lista di eventi sportivi, con i dati degli eventi dello sport fornito in ingresso 
che contengono la squadra fornita in ingresso come parametro
*/

T_ListaEventi EventiSportSquadra(T_ListaEventi * Vettore, char * Squadra, int Sport) 
{
	//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
	T_ListaEventi ListaSport = Vettore[Sport];
	T_ListaEventi ListaOut = NULL;
	while (ListaSport != NULL) 
	{
		if ((strcmp(ListaSport->info.squadra1, Squadra) == 0) || (strcmp(ListaSport->info.squadra2, Squadra) == 0)) 
		{
			if (!AggiungiNodoLista(&ListaOut, ListaSport->info))
				return NULL;
		}
		ListaSport = ListaSport->next;
	}
	return ListaOut;
}


//  Disalloca una lista di eventi sportivi
void DisallocaLista(T_ListaEventi lista) 
{
	//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
	T_ListaEventi aux;
	while (lista != NULL) 
	{
		aux = lista;
		lista = lista->next;
		free(aux);
	}
}

//menù di scelta
int Menu() {
	int scelta;

	printf("*** MENU ***\n"
		"1. Carica dati dal file\n"
		"2. Calcola eventi sportivi con quote max\n"
		"3. Eventi di uno sport e di una squadra\n"
		"0. Esci\n\n"
		"Scelta: ");
	scanf("%d", &scelta);

	return scelta;
}


/*************** MAIN *****************/
int main(void) {
	int scelta;
	T_ListaEventi vettore[NUM_SPORT];
	char nomefile[DIMS];
	int n;
	TEvento* vmax;
	T_ListaEventi nuovalista = NULL;
	int codicesport;
	char squadra[DIMS];
	char* Sport = NULL;
	for (int i = 0; i < NUM_SPORT; i++)
		vettore[i] = NULL;

	do {
		scelta = Menu();

		switch (scelta) {
		case 1:
			// Invocare la funzione CaricaDatiDaFile e visualizzare il numero di
			// eventi sportivi caricati o gli eventuali errori
			printf("Inserisci nome del file: ");
			scanf("%s", nomefile);
			n = CaricaDatiDaFile(nomefile, vettore);
			if (n != -1)
				printf("Sono stati caricati %d eventi.\n", n);
			else
				printf("Si e' verificato un errore.\n");
			break;

		case 2:
			// invocare la funzione EventiQuoteMax e visualizzare per ciascuno sport 
			// gli eventi con quote max
			vmax = EventiQuoteMax(vettore);
			for (int i = 0; i < NUM_SPORT; i++) 
			{
				Sport = RitornaSport(i);
				printf("EVENTO: %s\n", Sport);
				printf("%s %s %s %.2f %.2f\n", vmax[i].codice_evento, vmax[i].squadra1, vmax[i].squadra2, vmax[i].quota1, vmax[i].quota2);
			}
			break;

		case 3:
			// acquisire da input i dati necessari 
			// e poi invocare la funzione EventiSportSquadra
			printf("Inserisci lo sport: ");
			scanf("%d", &codicesport);
			printf("Inserisci la squadra: ");
			scanf("%s", squadra);
			nuovalista = EventiSportSquadra(vettore, squadra, codicesport);
			// Dopodichè visualizzare i risultati ottenuti
			if(nuovalista != NULL)
				VisualizzaDatiLista(nuovalista);
			break;
		}
	} while (scelta != 0);

	//disallocare la memoria
	for (int i = 0; i < NUM_SPORT; i++)
		DisallocaLista(vettore[i]);
	DisallocaLista(nuovalista);
	return 0;
}
