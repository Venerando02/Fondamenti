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
COGNOME NOME
N. MATRICOLA
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
void VisualizzaDatiLista(T_ListaEventi lista) {
//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
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
Carica i dati degli eventi sportivi dal file e le memorizza in un array di liste. L'elemento i-esimo dell'array contiene la lista degli eventi sportivi relativi allo sport i-esimo. La funzione restituisce il numero totale di eventi sportivi caricati o -1 in caso di errore durante il caricamento.

Parametri: nome del file, array di liste di eventi sportivi
Restituisce: il numero totale di di eventi sportivi caricati, -1 in caso di
errore durante il caricamento

*/
int CaricaDatiDaFile(char* nome_file, T_ListaEventi* eventi) {
//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
	
}


/*
2) EventiQuoteMax:
Dato l'array di liste di eventi sportivi, calcola e restituisce in un opportuno vettore gli eventi aventi il valore massimo per una delle quote per ciascuno sport. Il vettore ha quindi un numero di elementi pari al numero di sport presenti.

Parametri: array di liste di eventi sportivi
Restituisce: Vettore di eventi sportivi in cui l'elemento i-esimo rappresenta l'evento avente quota di valore massimo per lo sport i-esimo
*/

TEvento* EventiQuoteMax(T_ListaEventi* eventi) {
//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
}


/*
3) EventiSportSquadra:
Dato l'array di liste di eventi sportivi, uno sport ed una squadra, la funzione estrae e restituisce in una lista di eventi sportivi tutti gli eventi dello sport fornito che coinvolgono la squadra fornita in ingresso come parametro.

Parametri in ingresso: array di liste di eventi sportivi, codice sport, squadra
Restituisce: lista di eventi sportivi, con i dati degli eventi dello sport fornito in ingresso che contengono la squadra fornita in ingresso come parametro
*/

T_ListaEventi EventiSportSquadra(/* INSERIRE I PARAMETRI OPPORTUNI */) {
//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
}


//  Disalloca una lista di eventi sportivi
void DisallocaLista(T_ListaEventi lista) {
//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
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
	TEvento *vmax;
	T_ListaEventi nuovalista;
	int codicesport;
	char squadra[DIMS];

	for (int i = 0; i < NUM_SPORT; i++)
		vettore[i] = NULL;

	do {
		scelta = Menu();

		switch (scelta) {
		case 1:
			// Invocare la funzione CaricaDatiDaFile e visualizzare il numero di
			// eventi sportivi caricati o gli eventuali errori

			break;

		case 2:
			// invocare la funzione EventiQuoteMax e visualizzare per ciascuno sport 
			// gli eventi con quote max

			break;

		case 3:
			// acquisire da input i dati necessari 
			// e poi invocare la funzione EventiSportSquadra

			// Dopodichè visualizzare i risultati ottenuti

			break;
		}
	} while (scelta != 0);

	//disallocare la memoria
	for (int i = 0; i < NUM_SPORT; i++)
		DisallocaLista(vettore[i]);

	return 0;
}
