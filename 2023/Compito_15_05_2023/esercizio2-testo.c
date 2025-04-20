/*
* Compito del 15/05/2023
*
 * Si vuole scrivere un programma per gestire gli ingressi e le uscite giornaliere in un parcheggio multipiano.
 * I dati delle autovetture che transitano nel parcheggio sono memorizzati in un vettore di N liste,
 * in cui la lista i-esima contiene solo le autovetture del piano i-esimo;
 * Per ogni autovettura presente e/o transitata nel parcheggio si desidera memorizzare:
 * - targa
 * - orario ingresso
 * - orario uscita
 * - id del posto occupato (intero positivo)
 *
 * Quando un'autovettura entra nel parcheggio viene settato l'orario di ingresso ed il posto occupato.
 * Quando un'autovettura esce dal parcheggio viene settato l'orario di uscita ed il posto occupato viene posto a -1
 *
 * Scrivere un programma ANSI C che permetta di implementare le seguenti operazioni:
 * 1. ParcheggioAuto: inserimento di una nuova autovettura nella struttura del parcheggio
 * 2. ContaAuto: conteggio del numero di auto attualmente presenti nel parcheggio
 * 3. UscitaAuto: uscita di un auto dal parcheggio (aggiornamento dei relativi dati)
 * 4. VisualizzaDatiLista: visualizza i dati di auto presenti e/o uscite 
 * 
 * La specifica dettagliata delle funzioni è riportata nel seguito
 *
 * NOTA: il numero N di piani presenti nel parcheggio è pari a 5, numerati da 0 a N-1
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5  //numero di piani presenti

typedef struct postoauto {
	char  targa[8];
	char oraingresso[6]; // nel formato hh:mm
	char orauscita[6];   // nel formato hh:mm - vuota se l'auto è ancora presente
	int idposto;		// intero positivo, vale -1 se l'auto non è più presente
} TPostoAuto;

typedef struct nodolista {
	TPostoAuto        info;
	struct nodolista *next;
} TNodoLista;

typedef TNodoLista* TListaParcheggio;


// Aggiunge una nuova auto alla lista delle auto nel parcheggio, 
// restituisce 1 se l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiNodoLista(TListaParcheggio* plista, TPostoAuto elem) { 
	TListaParcheggio p;

	p = (TListaParcheggio)malloc(sizeof(TNodoLista));
	if (p == NULL)
		return 0;

	p->info = elem;
	p->next = *plista;
	*plista = p;

	return 1;
}

/* TrovaPostoDisponibile
* La funzione TrovaPostoDisponibile deve individuare un posto disponibile secondo il seguente algoritmo: 
* le auto vanno parcheggiate sequenzialmente, occupando quindi prima il posto 1, poi il 2 e così via.
* Per ogni idposto considerato, bisogna però controllare che il posto sia libero, ossia non occupato da un'auto parcheggiata in quel medesimo posto. La funzione deve quindi restituire il primo idposto disponibile.
* 
* Parametri: lista delle auto parcheggiate
* Restituisce: il primo idposto disponibile
*/

int TrovaPostoDisponibile(TListaParcheggio p) {  
	// DA IMPLEMENTARE A CURA DELLO STUDENTE
}

/*
1) ParcheggioAuto:
 inserimento di una nuova autovettura nella struttura del parcheggio, dati in ingresso la targa e l'orario di ingresso
 e il piano in cui parcheggiare

 Parametri: array di liste parcheggio, dim array, targa autovettura, orario ingresso, piano
 Restituisce: il posto in cui l'auto è stata parcheggiata (o -1 se vi è stato un errore)

 NOTA: per generare il posto bisogna usare la funzione TrovaPostoDisponibile secondo le specifiche descritte
 */

int ParcheggioAuto(TListaParcheggio v[], int dim, char* targa, char* orario, int piano) { 
	// DA IMPLEMENTARE A CURA DELLO STUDENTE
}

/*
2) ContaAuto: 
funzione che, dato in ingresso il vettore dei parcheggi, restituisca in un opportuno vettore di interi il numero di auto attualmente presenti per ciascun piano

 Parametri: array di liste parcheggio, dim array
 Restituisce: vettore i cui elementi rappresentanto il numero di auto attualmente presenti in quel piano del parcheggio 
*/

int* ContaAuto(TListaParcheggio v[], int dim) { 
	// DA IMPLEMENTARE A CURA DELLO STUDENTE
}


/*
3) UscitaAuto: 
 funziona data la targa di un auto ed un orario di uscita, aggiorna i relativi dati nella struttura del parcheggio
 NOTA: per un'auto uscita l'idposto dell'auto deve essere posto al valore -1

 Parametri: array di liste parcheggio, dim array, targa autovettura, orario uscita, piano
 Restituisce: 1 se l'auto è stata trovata nel parcheggio ed i dati correttamente aggiornati, 
			  0 nel caso in cui l'auto non è presente
*/

int UscitaAuto(TListaParcheggio v[], int dim, char* targa, char* orario) { 
	// DA IMPLEMENTARE A CURA DELLO STUDENTE
}


// Visualizza i dati di una lista di auto 
void VisualizzaDatiLista(TListaParcheggio lis) {
	printf("Targa  OraIngresso OraUscita IDposto\n");
	while (lis != NULL) {
		printf("%s %s %s %d\n", lis->info.targa,
			lis->info.oraingresso,
			lis->info.orauscita,
			lis->info.idposto);
		lis = lis->next;
	}
}

// menù di scelta
int Menu() {
	int scelta;

	printf("\n*** MENU ***\n"
		"1. Parcheggia auto\n"
		"2. Conta auto presenti\n"
		"3. Uscita auto\n"
		"4. Visualizza auto presenti e/o uscite\n"
		"0. Esci\n\n"
		"Scelta: ");
	scanf("%d", &scelta);

	return scelta;
}

int main(void) {
	int  scelta;
	TListaParcheggio vettore[N];
	int n;
	char targa[8];
	char orario[6];
	int piano;
	int *nauto;
	int esito;

	for (int i = 0; i < N; i++)
		vettore[i] = NULL;

	do {
		scelta = Menu();

		switch (scelta) {
		case 1:
			// Acquisire i dati necessari per poter invocare la funzione ParcheggioAuto
			// quindi invocarla e visualizzare il posto in cui l'auto è stata parcheggiata

			break;

		case 2:
			// Invocare la funzione ContaAuto e visualizzare il numero di auto presenti in ogni piano del parcheggio

			break;

		case 3:
			// Acquisire i dati necessari per poter invocare la funzione UscitaAutoquindi invocarla. 
			// Se l'auto non era presente nel parcheggio visualizzare un opportuno messaggio di errore
			
			break;

		case 4:
			// Visualizzare i dati di tutte le autovettore presenti e/o uscite da tutti i piani del parcheggio
			// invocando opporunamente la funzione VisualizzaDatiLista

			break;
		}
	} while (scelta != 0);

	return 0;
}