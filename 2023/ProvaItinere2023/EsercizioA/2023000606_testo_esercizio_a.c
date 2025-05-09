/*
Sviluppare un applicazione in ANSI C che permette di gestire i turni di lavoro in  una azienda.
Gli attributi di ogni dipendente sono i seguenti:
Cognome (senza spazi bianchi)
Nome (senza spazi bianchi)
Ore (numero di ore di lavoro)
sesso (0 : non fornito, 1 : donna, 2 uomo)

L'azienda � organizzata in 10 differenti sezioni numerate da 1 a 10.

L'applicazione legge i dati da un file in formato testo che contiene, uno per riga, le seguenti informazioni:
Cognome Nome Ore Sesso Sezione e carica i dati in un vettore di liste la cui chiave di accesso e' il numero della sezione.
(vedi esempio allegato per maggiori chiarimenti)

Sviluppare i seguenti punti:
1. caricare i dati dal file il cui nome � fornito da console
2. stampare il contenuto della struttura dati (vettore di liste)
3. calcolare il numero di dipendenti in ogni sezione, il valore deve essere restituito in un vettore di valori
4. scrivere una funzione che restituisce il numero di dipendenti donne e uomini.

Usando il file dato come esempio
_ vengono caricati 70 dipendenti
_ tutte le sezioni hanno 7 dipendenti
_ sono presenti 35 uomini e 33 donne
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN	128

#define SEZIONE_VENDITE 1
#define SEZIONE_MARKETING 2
#define SEZIONE_RISORSE_UMANE 3
#define SEZIONE_FINANZIARIA 4
#define SEZIONE_SVILUPPO 5
#define SEZIONE_QUALIT� 6
#define SEZIONE_LOGISTICA 7
#define SEZIONE_AMMINISTRATIVA 8
#define SEZIONE_ACQUISTI 9
#define SEZIONE_REPARTO_PRODUZIONE 10

#define SESSO_DONNA	1
#define SESSO_UOMO	2
#define SESSO_IGNOTO	0
typedef struct dipendente_s {
	char cognome[MAXSTRLEN];
	char nome[MAXSTRLEN];
	int ore;
	int sesso;
} dipendente_t;
typedef struct nodo_dipendente_s {
	dipendente_t dato;
	struct nodo_dipendente_s* prossimo;
} nodo_dipendente_t, *lista_dipendente_t;

//	La funzione aggiunge un dipendente nella lista, restituisce
//	0 in caso di errore
int lista_dipendenti_aggiungi(lista_dipendente_t* pl, dipendente_t d) {
	nodo_dipendente_t* aux = (nodo_dipendente_t *) malloc(sizeof(nodo_dipendente_t));
	if (aux == 0)
		return 0;
	aux->dato = d;
	aux->prossimo = *pl;
	*pl = aux; // *** istruzione mancante nel testo dato agli studenti
	return 1;
}

// la funzione svuota una lista
void lista_svuota(lista_dipendente_t* pl) {
	if (*pl == NULL)
		return;
	lista_dipendente_t aux = NULL;
	while (*pl != NULL) {
		aux = *pl;
		(*pl) = (*pl)->prossimo;
		free(aux);
	}
}

// la funzione stampa il contenuto del vettore di liste
//  parametri in ingresso:
//      vettore di liste
//      dimensione del vettore
//  restituisce:
//      0 in caso di errore
//      1 altrimenti
int archivio_stampa(lista_dipendente_t* vl, int n) {
	// DA IMPLEMENTARE A CURA DELLO STUDENTE
}

// La funzione carica i dati dal file di testo verificando che il valore
// della sezione sia compreso nell'intervallo corretto, nel caso il valore fosse
// scorretto la riga non viene considerata e si prosegue con la riga successiva
// parametri in ingresso: 
//		nome del file
//		vettore di liste
// parametri in uscita:
//		0 in caso di errore
//		numero di elementi letti e caricati con successo
int carica_dati(char* nome_file, lista_dipendente_t* vl, int n) {
	// DA IMPLEMENTARE A CURA DELLO STUDENTE
}

// La funzione calcola il numero di dipendenti inn ogni sezione, il valore
// viene restituito in un vettore che viene allocato all'interno della funzione
// parametri in ingresso:
//		vettore di liste
//	parametri in uscita
//		vettore di interi che contiene i valori richiesti o NULL in caso di fallimento
int* calcola_numero_dipendenti_sezioni(lista_dipendente_t* vl, int n) {
	// DA IMPLEMENTARE A CURA DELLO STUDENTE
}

// La funzione calcola_numero_dipendenti_per_genere calcola il numero
// di dipendenti presenti del vettore di liste che sono uomini e donne
//	parametro in ingresso:	vettore di liste
//	parametri in uscita: numero di donne, numero di uomini
//
void calcola_numero_dipendenti_per_genere(/* inserire i parametri necessari*/) {
	// DA IMPLEMENTARE A CURA DELLO STUDENTE
}



int main(void) {
	int scelta = 0;
	//	Definire le strutture dati necessarie al funzionamento del programma
	do {
		printf("1. carica da file i dati\n");
		printf("2. stampa il contenuto dell'archivio\n");
		printf("3. calcola e stampa il numero di dipendenti per sezione\n");
		printf("4. calcola e stampa il numero di dipendenti divisi per genere\n");
		printf("0. fine\n");
		printf(">>>> ");
		scanf("%d", &scelta);
		switch (scelta) {
		case 1: {
			// gestione del caricamento dei dati:
			// le operazione da svolgere sono:
			//	1.	svuotamento delle strutture esistenti se non vuote
			//	2.	richiesta del nome del file
			//	3.	caricamento dei dati USANDO la funzione prevista nel testo
			//	4.	stampa del numero di elementi letti
			break;
		}
		case 2: {
			// gestione della stampa del contenuto della struttura dati
			// le operazioni da svolgere sono:
			//	1.	stampa del contenuto della struttura dati USANDO la funzione 
			//		prevista nel testo
			break;
		}
		case 3: {
			// gestione della stampa del numero di dipendenti presenti in ogni sezione
			// le operazioni da fare sono:
			//	1.	calcolo del numero USANDO la funzione prevista nel testo
			//	2.	stampa del risultato
			//	3.	liberazione dello spazio in memoria centrale
			break;
		}
		case 4: {
			// gestione della stampa del numero di dipendenti diviso per genere
			//	le operazioni da fare sono:
			//	1.	calcolo del numero di donne e uomini USANDO la funzione prevista 
			//		nel testo
			//	2.	stampa del risultato
			break;
		}
		case 0:
			printf("Chiusura del programma\n");
			break;
		}

	} while (scelta != 0);
}