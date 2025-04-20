/*
* Implementare in ANSI C una applicazione che elabora le informazioni anagrafiche (persone) presenti
* in un file di testo in cui ogni riga contiene il codice fiscale, il sesso (codificato come 1: maschio,
* 2: femmina e 0: non fornito),  e la data di nascita nel format AAAAMMGG (ad esempio 5 settembre 2023
* viene codificato in 20230905).
*
* Le operazioni che il programma deve svolgere sono le seguenti:
* 1. Caricamento dei dati in una lista ordinata rispetto alla data di nascita
* 2. Stampa del più giovane e del più vecchio elemento presente
* 3. Copia degli elementi in un vettore di stringhe in base al sesso
*
* Usando il file di dati fornito
* 1. gli elementi caricati sono 100 e l'ultimo elemento è J9JJVT1K2J13NX4W
* 2. il più giovano è MRUPK1OKPTVERI0S ed il più vecchio J9JJVT1K2J13NX4W
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MASCHIO	1
#define	FEMMINA 2
#define ALTRO	0

char* CONVERSIONE_SESSO[3] = { "Altro", "Maschio", "Femmina" };

// Definizione del record che contiene le informazioni anagrafiche e degli elementi
// necessari a costruire la sequenza concatenata
//
typedef struct anagrafe_s {
	char	cf[20];
	int		sesso;
	char	data[20];
	struct anagrafe_s* p;
} anagrafe_t;

// Definizione del tipo lista di record anagrafici che contiene anche il numero di
// elementi pr4esenti
typedef struct anagrafe_lista_s {
	anagrafe_t* radice;
	int numero_elementi;
} anagrafe_lista;

// Funzione di stampa di un elemento.
//
void anagrafe_stampa(const anagrafe_t* pa) {
	char anno[8] = "";
	char giorno[8] = "";
	char mese[8] = "";
	strncpy(giorno, pa->data + 6, 2);
	strncpy(mese, pa->data + 4, 2);
	strncpy(anno, pa->data, 4);

	printf("Codice fiscale  : %s\nSesso           : %s\nData di nascita : %s/%s/%4s\n\n",
		pa->cf,
		CONVERSIONE_SESSO[pa->sesso],
		giorno,
		mese,
		anno);
}

// Funzione di stampa del contenuto di una lista
// 
void lista_anagrafe_stampa(anagrafe_lista l) {
	printf("---\n");
	printf("numero di elementi in lista %d\n", l.numero_elementi);
	for (anagrafe_t* aux = l.radice; aux != NULL; aux = aux->p)
		anagrafe_stampa(aux);
	printf("---\n");
}

// Funzione di inserimento in testa
// La funzione restituisce il numero di valori presenti nella lista in caso di successo
// altrimenti restituisce un valore negativo. 
int lista_anagrafe_aggiungi(anagrafe_lista* pl, anagrafe_t a) {
	anagrafe_t* aux = malloc(sizeof(anagrafe_t));
	if (aux == 0)
		return -1;

	*aux = a;

	aux->p = pl->radice;
	pl->radice = aux;
	++(pl->numero_elementi);
	return pl->numero_elementi;
}
// Prototipo delle funzioni di inserimento ordinato che deve essere implementate dallo studente, 
// per i dettagli vedi la definizione presente nel testo nella sezione "funzioni da implementare"
//
int lista_anagrafe_aggiungi_ordinato(anagrafe_lista* pl, anagrafe_t a);

// La funzione carica i dati contenuti in un file di cui viene passato il descrittore in una 
// lista ordinata.
anagrafe_lista anagrafe_carica(FILE* fp) {
	anagrafe_lista lista = { .radice = NULL, .numero_elementi = 0 };
	anagrafe_t a;
	while (fscanf(fp, "%s%d%s", a.cf, &a.sesso, a.data) == 3)
		lista_anagrafe_aggiungi_ordinato(&lista, a);

	return lista;
}


/////////////////////////////////////////////////////////////////////////////////////////
// 
// Funzioni da implementare 
//
/////////////////////////////////////////////////////////////////////////////////////////

// La funzione svuota una lista deallocando la memoria
// Lo studente deve scegliere i parametri e la modalità di passaggio corretta per svuotare
// una lista di elementi
void lista_libera( /* Da inserire */) {
	// Da implementare
}

// Questa funzione aggiunge un elemento in modo ordinato rispetto alla data di nascita. 
// parametri:
//		p_lista (anagrafe_lista*)	: lista in cui inserire i dati
//		a		(anagrafe_t)		: elemento da inserire
// return:
//		numero di elementi presenti o un valore negativo in caso di errore
int lista_anagrafe_aggiungi_ordinato(anagrafe_lista* p_lista, anagrafe_t a) {
	// Da implementare a cura dello studente
}

// La funzione estrai_elementi (senza cancellarli) estrae da una lista in ingresso 
// tutti gli elementi di un determinato sesso, passato come parametro, copiando 
// gli elementi trovati in una nuova lista (anch'essa passata come parametro)
// parametri:
//		lista_ingresso	: lista in ingresso da cui copiare gli elementi
//		lista_uscita	: lista in uscita in cui copiare gli elementi
//		sesso			:
void estrai_elementi(/* lo studente inserisca i parametro formali corretti in base alla specifica */) {
	// FUNZIONE DA IMPLEMENENTARE, IL TIPO DEI PARAMETRI DEVE ESSERE SCELTO DALLO
	// STUDENTE
}

// La funzione crea_vettore crea un vettore di liste partendo da un lista in ingresso.
// N.B. LO STUDENTE DEVE USARE LA FUNZIONE estrai_elementi PER RISOLVERE IL PROBLEMA
// parametri:
//		lista_ingresso	: (anagrafe_lista) lista in ingresso da cui copiare gli elementi
//		vettore_uscita	: (anagrafe_lista **) vettore delle liste in cui salvare i dati (il vettore 
//							deve essere allocato nella funzione)
//		
void crea_vettore(anagrafe_lista lista_ingresso, anagrafe_lista** vettore_uscita) {
	// Da implementare usando le funzioni disponibili
}

// La funzione, data un alista ordinata in ingresso, restituisce un puntatore al più
// giovane ed un puntatore al più vecchio
// parametri:
//		lista_ingresso	: lista in ingresso da cui copiare gli elementi
//		giovane			: puntatore al più giovane
//		vecchio			: puntatore al più vecchio
//		
void estrai_giovane_vecchio(/* lo studente definisca i parametri formali in base alla specifica */) {
	// Da implementare
}

int main(void) {
	anagrafe_lista anagrafe = { .numero_elementi = 0, .radice = NULL };
	int selezione;
	do {
		printf("\n\n\n1. Caricamento dei dati in una lista ordinata rispetto alla data di nascita\n");
		printf("2. Stampa del più giovane e del più vecchio elemento presente\n");
		printf("3. Copia degli elementi in un vettore di stringhe in base al sesso\n");
		printf("0. uscita\n");
		printf("\n>>> ");
		scanf("%d", &selezione);
		switch (selezione) {
		case 0:
			printf("Fine del programma\n");
			break;
		case 1: {
			// Lo studente implementi le seguenti operazioni usando le funzioni date nel testo
			// quando possibile (Non usare le funzioni, se disponibili, è considerato errore)
			// 1. richiesta nome del file
			// 2. svuotamento della lista anagrafe nel caso contenga elementi
			// 3. caricamento dei dati nella lista anagrafe
			// 4. stampa gli elementi presenti nella lista
			char filename[128];
			printf("Inserisci il nome del file: ");
			scanf("%s", filename);

			// Da completare in base alla descrizione e alle specifiche
			break;
		}
		case 2:
			//Lo studente deve completare il codice in modo da stampare l'elemento più
			// giovano e quello più vecchio operazioni usando, quando presenti, le funzioni date 
			// nel testo (non usare le funzioni, se disponibili, è considerato errore)

			// Da completare in base alla descrizione e alle specifiche
			break;
		case 3:
			//Lo studente deve completare il codice in modo riempire il vettore di stringhe e 
			// stamparne il contenuto usando, quando presenti, le funzioni date 
			// nel testo (non usare le funzioni, se disponibili, è considerato errore)	
			// Il vettore deve essere liberato al termine del case
		{
			// 1. Dichiarazione delle variabili (se necessario)
			// Inserire il codice necessario 

			// 2. Creazione del vettore
			// Inserire il codice necessario 

			// 3. Stampa del vettore
			// Inserire il codice necessario 

			// 4. Liberazione dello spazio allocato per il vettore di liste
			// Inserire il codice necessario 
			break;
		}
		}
	} while (selezione != 0);
}
