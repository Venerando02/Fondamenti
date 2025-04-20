/*
* Implementare una applicazione che elabora gli eventi meteorologici ricevuti da una agenzia
* di rilevazione quotidiana.
* I dati vengono ricevuti in un file in formato testo in cui ogni riga rappresenta un evento 
* dove il primo campo contiene la data, il secondo il tipo di evento codificato con un intero ed 
* il terzo la rilevanza (vedere l'esempio allegato).
* Il programma svolge le seguenti operazioni:
* 1. caricamento dei dati dal file in una coda in memoria centrale,
* 2. trasferimento dei dati dalla coda ad un vettore di liste organizzate in base al tipo di evento, 
*	nota che il dato, dopo essere stato trasferito deve essere cancellato dalla coda
* 3. Stampa il numero di eventi presenti nella struttura di ingresso
* 4. stampa di tutti gli eventi di un certo tipo che superano una soglia di rilevanza, usando
*	i dati contenuti nel vettore di liste. Sia il tipo che che la rilevanza sono letti da console.
* 
* Le funzioni da implementare sono:
*	carica_file		: la funzione carica i dati presenti nel file in una coda passata come
*						parametro, restituendo 0 in caso di fallimento altrimenti 1
*	coda_primo		: restituisce il primo elemento della coda senza cancellarlo dalla coda
*	visita_lista	: la funzione accetta in ingresso una lista di eventi e la soglia sopra la
*						quale selezionare i valori e restituisce tutti i valori trovati in 
*						una nuova lista (i valori vengono copiati e non cancellati dalla lista
*						di origine)
*
*	completare il main
* 
* Specifiche:
*	gli attributi dell'evento sono i seguenti:
*		data :		stringa nel formato AAAA-MM-GG
*		tipo:		intero che codifica il tipo di evento (vedi il codice per il significato dei valori)
*		rilevanza:	intero appartenente all'intervallo chiuso [0,9]
* 
* La coda deve anche mantenere il numero degli elementi contenuti
* 
* Esempio:
*	Con i dati presenti nel file di testo fornito 
*		il numero di dati caricati e' pari a 99 (esecuzione del punto 1 e 3)
*		dopo l'esecuzione del punto 2 la dimensione della coda deve diventare 0
*		l'esecuzione del punto 4, scegliendo il tipo 4 e la soglia 7 da un solo evento in data 2023-01-13 di tipo 3 e rilevanza 8
* 
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Costanti usate per codificare gli eventi
#define ALLUVIONE 1
#define TEMPESTA 2
#define TROMBA_DARIA 3
#define TEMPESTA_DI_NEVE 4
#define TORNADO 5
#define INCENDIO_BOSCHIVO 6
#define SICCIATÀ 7
#define TEMPESTA_DI_SABBIA 8
#define TEMPESTA_DI_GRANDINE 9
#define TEMPESTA_DI_FULMINI 10

#define DATA_LUNGHEZZA		16

//tipi strutture dati

typedef struct evento_s {
	char data[DATA_LUNGHEZZA];
	int	tipo;
	int rilevanza;
} evento_t;

typedef struct nodo_s {
	evento_t evento;
	struct nodo_s* successivo;
} nodo_t;

typedef struct coda_s {
	nodo_t* primo, * ultimo;
	int numero_nodi;
} coda_t;

typedef nodo_t* lista_t;

// Implementazione della struttura dati coda
// Funzione coda_aggiungi
// La funzione coda_aggiungi permette di aggiungere un elemento alla coda
// restituisce il valore 0 in caso di errore, altrimenti restituisce 1
int coda_aggiungi(coda_t* pc, evento_t ev) {
	nodo_t* nuovoNodo = (nodo_t*)malloc(sizeof(nodo_t));
	if (nuovoNodo == NULL) {
		printf("Errore: memoria esaurita.\n");
		return 0;
	}

	nuovoNodo->evento = ev;
	nuovoNodo->successivo = NULL;

	if (pc->primo == NULL) {
		pc->primo = nuovoNodo;
		pc->ultimo = nuovoNodo;
	}
	else {
		pc->ultimo->successivo = nuovoNodo;
		pc->ultimo = nuovoNodo;
	}

	pc->numero_nodi++;
	return 1;
}

// Funzione coda_rimuovi
// Funzione per rimuovere il primo elemento dalla coda
int coda_rimuovi(coda_t* pc) {
	if (pc->primo == NULL) {
		return 0;
	}

	nodo_t* nodoRimosso = pc->primo;
	pc->primo = pc->primo->successivo;

	if (pc->primo == NULL) {
		pc->ultimo = NULL;
	}

	free(nodoRimosso);
	pc->numero_nodi--;
	return 1;
}

// Implementazione della struttura dati lista
// Funzione lista_aggiungi_ordine
// Funzione per aggiungere un elemento in ordine nella lista
int lista_aggiungi_ordine(lista_t* pl, evento_t ev) {
	nodo_t* nuovoNodo = (nodo_t*)malloc(sizeof(nodo_t));
	if (nuovoNodo == NULL) {
		printf("Errore: memoria esaurita.\n");
		return 0;
	}

	nuovoNodo->evento = ev;

	if (*pl == NULL || (*pl)->evento.rilevanza <= ev.rilevanza) {
		nuovoNodo->successivo = *pl;
		*pl = nuovoNodo;
	}
	else {
		nodo_t* nodoCorrente = *pl;
		while (nodoCorrente->successivo != NULL && nodoCorrente->successivo->evento.rilevanza > ev.rilevanza) {
			nodoCorrente = nodoCorrente->successivo;
		}
		nuovoNodo->successivo = nodoCorrente->successivo;
		nodoCorrente->successivo = nuovoNodo;
	}

	return 1;
}

// Funzione lista_rimuovi
// Funzione per rimuovere il primo elemento dalla lista
int lista_rimuovi(lista_t* pl) {
	if (*pl == NULL) {
		return 0;
	}

	nodo_t* nodoRimosso = *pl;
	*pl = (*pl)->successivo;
	free(nodoRimosso);
	return 1;
}

// Funzione lista_svuota
// Funzione per svuotare la lista
int lista_svuota(lista_t* pl) {
	while (*pl != NULL) {
		lista_rimuovi(pl);
	}
	return 1;
}

// Funzione lista_stampa
// Funzione per stampare gli eventi della lista
int lista_stampa(lista_t l) {
	nodo_t* nodoCorrente = l;
	while (nodoCorrente != NULL) {
		printf("Data: %s\n", nodoCorrente->evento.data);
		printf("Tipo: %d\n", nodoCorrente->evento.tipo);
		printf("Rilevanza: %d\n", nodoCorrente->evento.rilevanza);
		printf("\n");
		nodoCorrente = nodoCorrente->successivo;
	}
	return 1;
}


/******** FUNZIONI DA IMPLEMENTARE *************/

/*
Funzione carica_file
Questa funzione carica i dati presenti nel file in una coda passata come
parametro, restituendo 0 in caso di fallimento altrimenti 1

Parametri: nome del file, coda di eventi
Restituisce: 1 se il caricamento è andato a buon fine,
			 0 in caso di errore durante il caricamento
*/

int carica_file(const char* nomefile, coda_t* pc) {
	// DA IMPLEMENTARE A CURA DELLO STUDENTE

}

/*
Funzione coda_primo
 La funzione coda_primo restituisce il primo elemento della coda senza cancellarlo,
 Nota che poiche' la coda e' una struttura di tipo FIFO l'elemento letto e' quello
 che e' stato inserito per primo

 parametri:
		coda_t	c		: coda da cui leggere il primo elemento
		evento_t * pev	: evento letto dalla coda, nota che pev deve puntare all'elemento
							presente in coda non deve restituire una copia dell'evento

 Restituisce: 1 se la coda contiene almeno un elemento,
			 0 se la coda è vuota
*/

int coda_primo(coda_t c, evento_t* pev) {
	// DA IMPLEMENTARE A CURA DELLO STUDENTE

}


/*
Funzione crealista_maggiorisoglia
Questa funzione prende in input una lista di eventi e un valore di soglia
e crea e restituisce una nuova lista contenente gli eventi aventi una rilevanza
maggiore del valore soglia fornito
Parametri:
 - lista: la lista di eventi in ingresso
 - soglia: il valore soglia
Restituisce: la nuova lista creata
*/

/* INSERIRE TIPO DI RITORNO */  crealista_maggiorisoglia(/* INSERIRE PARAMETRI FORMALI */) {
	// DA IMPLEMENTARE A CURA DELLO STUDENTE

}


/******** MAIN ************/
int main(void) {
	lista_t v[10]; // Dichiarazione del vettore di liste
	coda_t c = { NULL, NULL, 0 };
	int scelta = 0;

	// Inizializzazione delle liste nel vettore
	for (int i = 0; i < 10; i++) {
		v[i] = NULL;
	}

	do {
		printf("\n\n\n");
		printf("1. Carica i dati da file nella struttura di ingresso\n");
		printf("2. Crea struttura dati per tipo, cancellando la coda\n");
		printf("3. Stampa il numero di eventi presenti nella struttura di ingresso\n");
		printf("4. Stampa tutti gli eventi di un certo tipo con rilevanza superiore ad una soglia data\n");
		printf("0. Esci\n");
		printf("\n\n>> ");
		scanf("%d", &scelta);

		switch (scelta) {
		case 1: {
			// Il primo caso implementa il caricamento dei dati nella coda, 
			// Acquisire il nome del file da console e richiamare la funzione carica_file
			// DA COMPLETARE A CURA DELLO STUDENTE

			break;
		}
		case 2: {
			// il caso 2 implementa il trasferimento dei dati dalla coda al vettore di liste.
			// Per l'implementazione di questo caso bisogna usare le funzioni
			// coda_primo	: prototipo e struttura forniti, implementazione a cura dello studente
			// coda_rimuovi	: fornita
			// lista_aggiugi_ordine : fornita 
			// La struttura di destinazione e' un vettore di liste in cui ciascuna lista
			// contiene solo gli eventi di un determinato tipo
			// L'evento, dopo essere stato trasferito nel vettore di liste, deve essere cancellato dalla coda
			// DA COMPLETARE A CURA DELLO STUDENTE

			break;
		}
		case 3: {
			// Visualizza il numero di eventi presenti nella coda
			// DA COMPLETARE A CURA DELLO STUDENTE

			break;
		}
		case 4: {
			// Stampa tutti gli eventi di un determinato tipo che superano un valore di 
			// soglia. 
			// Acquisire da console il tipo e la soglia ......
			// Invocare la funzione crealista_maggiorisoglia e visualizzare la nuova lista ottenuta
						// DA COMPLETARE A CURA DELLO STUDENTE

			break;
		}
		default: {
			break;
		}
		}
	} while (scelta != 0);

	// Deallocazione delle liste nel vettore
	for (int i = 0; i < 10; i++) {
		lista_svuota(&(v[i]));
	}

	return 0;
}
