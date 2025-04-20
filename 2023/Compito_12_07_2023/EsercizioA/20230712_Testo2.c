/*
* Implementare in ANSI C una applicazione che elabora le informazioni geometriche
* relative ad un insieme di segmenti contenuto in un file di testo.
* Ogni segmento è rappresentato mediante i suoi estremi.
* 
* Implementare le seguenti operazioni utilizzando, quando possibile, le funzioni già disponibili
* nel testo:
*	1. completare il programma principale;
*	2. implementare una funzione che divide in due la lista in ingresso in base ad una soglia data
*		come parametro, nella prima lista devono essere presenti i segmenti la cui lunghezza e'
*		non superiore alla soglia altrimenti i valori vanno inseriti nella seconda
*	3. stampa la lunghezza di tutti i segmenti
* 
* I dettagli delle funzioni e dei parametri sono specificati nella descrizione puntuale delle
* funzioni. 
* 
* Usando il file di dati allegati vengono caricati 10 segmenti,
* inserendo un valore di soglia pasri ad 8.00 il terzo punto divide l'elenco in una lista
* di 6 elementi ed una di 4. La lunghezza dei segmenti e' la seguente:
*  8.32
 4.58
 7.77
 2.62
 7.07
 6.07
11.28
10.47
 8.70
 7.04
* 
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// tipo che definisce un punto nel piano
//
typedef struct punto_s {
	float coordinata_x;
	float coordinata_y;
} punto_t;

// tipo che definisce un segmento nel piano e, contemporaneamente, un nodo della catena 
// necessario a definire un sequenza
//
typedef struct segmento_s {
	punto_t estremo_a;
	punto_t estremo_b;
	struct segmento_s *successivo;
} segmento_t;

// tipo che definisce la radice della lista a cui vengono associati il numero di elementi
// presenti.
//
typedef struct lista_s {
	segmento_t* radice;
	int numero_elementi;
} lista_segmenti;

// Funzione che permette di stampare un segmento.
//
void segmento_stampa(const segmento_t *ps) {
	printf("(%5.2f, %5.2f) - (%5.2f, %5.2f)\n", ps->estremo_a.coordinata_x,
		ps->estremo_a.coordinata_y,
		ps->estremo_b.coordinata_x,
		ps->estremo_b.coordinata_y);
}

// Funzione che stampa il contenuto della lista dei segmenti
// //
void segmenti_stampa(lista_segmenti l) {
	printf("---\n");
	printf("numero di elementi in lista %d\n", l.numero_elementi);
	segmento_t* aux;
	for (aux = l.radice; aux != NULL; aux = aux->successivo)
		segmento_stampa(aux);
	printf("---\n");
}
// Prototipo della funzione che deve essere implementata dallo studente, per i dettagli 
// vedi la definizione presente nel testo nella sezione "funzioni da implementare"
//
void lista_segmenti_aggiungi(lista_segmenti* pl, segmento_t segmento);

// La funzione carica i dati contenuti in un file di testo il cui nome e' passato
// come parametro e restituisce una lista di segmenti
lista_segmenti segmenti_carica(const char* filename) {
	FILE* f = NULL;
	lista_segmenti risultato; 
	risultato.radice = NULL;
	risultato.numero_elementi = 0;
	if ((f = fopen(filename, "r")) == NULL) {
		printf("%s non valido, verifica nome ed estensione\n", filename);
		return risultato; // Nota che in questo caso la lista e' vuota
	}
	punto_t a, b;
	segmento_t s;
	while (fscanf(f, "%f%f%f%f", &a.coordinata_x, &a.coordinata_y, &b.coordinata_x, &b.coordinata_y) == 4) {
		s.estremo_a = a;
		s.estremo_b = b;
		lista_segmenti_aggiungi(&risultato, s);
	}
	fclose(f);
	return risultato;
}

// La funzione svuota una lista deallocando la memoria
// 
void segmenti_libera(lista_segmenti* p_lista) {
	segmento_t* aux;
	while (p_lista->radice != NULL) {
		aux = p_lista->radice;
		p_lista->radice = p_lista->radice->successivo;
		free(aux);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
// 
// Funzioni da implementare 
//
/////////////////////////////////////////////////////////////////////////////////////////

// La funzione lista_segmenti_aggiungi aggiunge un elemento in testa ad una lista di
// segmenti.
// Nota che la lista e' definita da una struttura dati che contiene sia la radice della
// sequenza che un contatore del numero di elementi contenuti che deve essere aggiornato.
// parametri:
//		lista_segmenti*	: lista in cui inserire i dati
// return:
//		void
void lista_segmenti_aggiungi(lista_segmenti* pl, segmento_t segmento) {
	// Funzione da implementare a cura dello studente
}

// La funzione segmenti_lunghezza calcola la lunghezza di un segmento usando la formula
// della distanza, dati due punti A = (xa, ya) e B = (xb, yb) la distanza e':
// d = radice_quadrata( (xa - xb) * (xa - xb) + (ya - yb) * (ya - yb)) 
// la funzione che in ANSI C calcola la radice quadrata e' sqrt, quindi l'istruzione
// per calcolare la distanza dato un segmento s e'
// d = sqrt( (s.)
// parametri :
//		devono essere scelti dallo studenti
// return
//		void
#include <math.h>
void segmenti_lunghezza(/* parametri da inserire in base alla descrizione */) {
	// Funzione da implementare a cura dello studente
}

// La funzione segmenti_dividi divide il contenuto della lista in ingresso in base al valore di 
// soglia passato come parametro. Gli elementi sono copiati nella prima lista se la lunghezza
// e' non superiore alla soglia altrimenti sono copiati nella seconda lista
// parametri:
//		lista_segmenti lista_in : lista in ingresso
//		lista_segmenti *p_lista_uno : lista in uscita (valori non superiori alla soglia) 
//		lista_segmenti *p_lista_due : lista in uscita (valori superiori alla soglia) 
// return
//		void
//
void segmenti_dividi(lista_segmenti lista_in, lista_segmenti* p_lista_uno, lista_segmenti* p_lista_due, float soglia) {
	// Funzione da implementare a cura dello studente
}


int main(void) {
	lista_segmenti segmenti = { NULL, 0 };
	int selezione;
	do {
		printf("\n\n\n1. carica i dati da file\n");
		printf("2. stampa il numero di segmenti presenti nella lista\n");
		printf("3. dividi i segmenti in base alla loro lunghezza\n");
		printf("4. calcola la lunghezza di tutti i segmenti\n");

		printf("\n>>> ");
		scanf("%d", &selezione);
		switch (selezione) {
		case 0:
			printf("Fine del programma\n");
			break;
		case 1: {
			// Lo studente implementi le seguenti operazioni usando le funzioni date nel testo
			// quando possibile
			// 1. richiesta nome del file
			// 2. caricamento dei dati nella variabile segmenti
			// 3. stampa gli elementi presenti nella lista
			char filename[128];
			printf("Inserisci il nome del file: ");
			scanf("%s", filename);

			// Completamento a cura dello studente

			break;
		}
		case 2:
			// Lo studente stampi il numero di elementi presenti nella lista

			// Completamento a cura dello studente

			break;
		case 3: {
			// Lo studente usando quando possibile le funzioni presenti nel testo divida
			// l'elenco in base alla soglia da richiedere all'utente, stampi il contenuto 
			// delle due liste e liberi lo spazio occupato

			// Completamento a cura dello studente

			break;
		}
		case 4: {
			// stampa le lunghezze di tutti i segmenti contenuti nella lista

			// Completamento a cura dello studente

			break;
		}
		}
	} while (selezione != 0);
}