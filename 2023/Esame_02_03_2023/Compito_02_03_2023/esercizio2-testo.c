/*
* In un impianto domotico di controllo di un edificio gli eventi degli N ambienti presenti 
* vengono registrati in un file "datieventi.txt" in cui in ogni riga vengono riportati: 
* - nome evento (stringa senza caratteri bianchi)
* - identificativo dell'ambiente (intero appartenente all'intervallo [0,N-1])
* - timestamp (in formato aa-mm-gg-hh-mm)
* 
* Scrivere un programma C che permetta di compiere le seguenti operazioni:
* 1. CaricaEventi: caricamento dei dati da file in un vettore di N liste, in cui la lista i-esima contiene solo gli eventi dell'ambiente i-esimo;
* 2. EstraiEvento: dato in ingresso l'identificativo di un ambiente, estrazione del primo evento presente nella corrispondente lista
* 3. CercaEvento: dato il nome di un evento, ricercare tutti gli eventi con quel nome nel vettore di liste e ricopiarli in un opportuno vettore fornito in uscita

NOTA: il numero N di ambienti presenti è pari a 5
*
*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5  //numero di ambienti presenti

typedef struct Evento {
	char  nome[32];
	int  ambiente;
	char data[20];
} TEvento;

typedef struct NodoListaEvento {
	TEvento                 info;
	struct NodoListaEvento* next;
} TNodoListaEvento;

typedef TNodoListaEvento* PNodoListaEvento;

// Visualizza un evento
void VisualizzaEvento(TEvento e) {
	printf("%s \t %d \t %s\n", e.nome,
		e.ambiente, e.data);
}

// Visualizza gli eventi di una lista di eventi
void VisualizzaDatiLista(PNodoListaEvento lis) {  
	printf("Codice_Evento  ID_ambiente  Data\n");
	while (lis != NULL) {
		VisualizzaEvento(lis->info);
		lis = lis->next;
	}
}

// Visualizza gli eventi di un vettore di eventi
void VisualizzaDatiVettore(TEvento v[], int dim) {  
// La funzione deve essere implementata dallo studente

}

// Aggiunge un evento alla lista degli eventi, restituisce 1
// se l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiNodoLista(/* I parametri devono essere definiti dallo studente */) { 
	// La funzione deve essere implementata dallo studente

}

/*
1) CaricaEventi: 
	Carica i dati dal file in un vettore di N liste, in cui la lista i-esima contiene solo gli eventi dell'ambiente i-esimo. La funzione restituisce il numero totale di eventi caricati o -1 in caso di errore durante il caricamento.

Parametri: nome del file, array di liste di eventi
Restituisce: il numero totale di eventi acquisito, -1 in caso di errore durante il caricamento
*/

int CaricaEventi(char* nome_file, PNodoListaEvento* veventi) {
	// La funzione deve essere implementata dallo studente

}


/*
2) EstraiEvento:
 Dato il vettore di liste di eventi ed un identificativo di ambiente, estrae e restituisce il primo evento presente nella corrispondente lista.
 L'evento estratto deve essere eliminato dalla lista ed opportunamente restituito dalla funzione (se la lista non ha eventi restituire NULL) 

Parametri: array di liste di eventi, identificativo intero dell'ambiente
Restituisce: puntatore al nodo contenente l'evento estratto (NULL se la lista non contiene eventi)
 */


TNodoListaEvento* Estrai_Evento(PNodoListaEvento veventi[], int ambiente) { 
	// La funzione deve essere implementata dallo studente

}


/*
3) CercaEvento:
	dato il nome di un evento, ricercare tutti gli eventi con quel nome nel vettore di liste e ricopiarli in un opportuno vettore fornito in uscita.

Parametri: nome dell'evento da cercare, array di liste di eventi, numero di eventi trovati
Restituisce: un vettore contenente gli eventi corrispondenti

*/

TEvento* CercaEvento(char* nome_evento, PNodoListaEvento veventi[], int *n_eventi ) {
	// La funzione deve essere implementata dallo studente

}


int Menu() {
	int scelta;

	printf("*** MENU ***\n"
		"1. Carica dati dal file\n"
		"2. Estrai Evento\n"
		"3. Cerca Evento\n"
		"0. Esci\n\n"
		"Scelta: ");
	scanf("%d", &scelta);

	return scelta;
}

int main(void) {
	int  scelta;
	PNodoListaEvento vettore[N];
	int n,k;
	int ambiente;
	TNodoListaEvento *eventoestratto;
	char nome_evento[32];

	TEvento* vett_eventi;


	for (int i = 0; i < N; i++)
		vettore[i] = NULL;

	do {
		scelta = Menu();

		switch (scelta) {
		case 1:
			// Invocare la funzione CaricaEventi e visualizzare il numero di
			// eventi caricati o gli eventuali errori

			// visualizza tutti gli eventi caricati nel vettore di liste

			break;

		case 2:
			// acquisire l'identificativo dell'ambiente
			printf("Inserisci l'identificativo dell'ambiente ");
			scanf("%d", &ambiente);
			// invocare la funzione Estrai_Evento e visualizzare i dati dell'evento estratto

			break;

		case 3:
			// acquisire il nome di un evento
			printf("Inserisci nome evento da cercare: ");
			scanf("%s", nome_evento);
			// invocare la funzione CercaEvento

			// visualizzare i risultati ottenuti


			break;
		}
	} while (scelta != 0);

	return 0;
}