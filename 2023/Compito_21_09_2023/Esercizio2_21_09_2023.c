/*
Sviluppare un programma in ANSI C per l'elaborazione di polinomi di qualsiasi grado.
Le informazioni relative al grado dei polinomi ed ai loro coefficienti sono memorizzate in un file di testo
in cui ogni riga contiene le seguenti informazioni:

- Grado del polinomio (numero intero positivo)
- Coefficienti (elenco dei coefficienti del polinomio rappresentati
  come numeri reali separati da spazi)

Implementare le seguenti funzioni:

1) CaricaPolinomi:
Funzione che carica i dati contenuti nel file in una lista. Un nodo della lista contiene due campi:
il grado del polinomio ed un vettore contenente i coefficienti del polinomio.
La funzione restituisce il numero di polinomi caricati in memoria.

Esempio di riga del file di input:

4 2.2 1.5 3.2 -4.0 -7

rappresenta il polinomio di 4 grado: 2.2x^4 + 1.5x^3 + 3.2x^2 -4.0x -7


2) MoltiplicaPolinomi:
Funzione che, dato in ingresso la lista dei polinomi ed un parametro a reale, moltiplica tutti i polinomi presenti nella
lista per il valore a, restituendo la lista modificata.


3) SommaPolinomi:
Funzione che, dato in ingresso la lista dei polinomi ed un parametro g intero, calcola la somma di tutti i polinomi
di grado g presenti nella lista, restituendo il polinomio risultante.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Polinomio {
	int grado;
	float* coefficienti;
} TPolinomio;

typedef struct NodoListaPolinomi {
	TPolinomio polinomio;
	struct NodoListaPolinomi* next;
} TNodoListaPolinomi;

typedef TNodoListaPolinomi* TListaPolinomi;


// Aggiunge un polinomio alla lista dei polinomi, restituisce 1 se
// l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiPolinomio(TListaPolinomi* plista, TPolinomio polinomio) {
	TListaPolinomi p;

	p = (TListaPolinomi)malloc(sizeof(TNodoListaPolinomi));
	if (p == NULL)
		return 0;

	p->polinomio = polinomio;
	p->next = *plista;
	*plista = p;

	return 1;
}

/*
1) CaricaPolinomi:
Funzione che carica i dati contenuti nel file in una lista. Un
nodo della lista contiene due campi: il grado del polinomio ed un
vettore contenente i coefficienti del polinomio. La funzione
restituisce il numero di polinomi caricati in memoria.
Parametri in ingresso:
	- polinomi: lista dei polinomi
	- nome_file: nome del file da leggere
Valore di ritorno:
	- numero di polinomi caricati in memoria o -1 se si verifica un errore

*/
int CaricaPolinomi(char* nome_file, TListaPolinomi* polinomi) {
	// implementazione a cura dello studente
	FILE* fp = fopen(nome_file, "r");
	if (fp == NULL)
		return -1;
	TPolinomio P;
	int num = 0;
	while (!feof(fp)) 
	{
		if (fscanf(fp, "%d", &P.grado) != 1) 
		{
			fclose(fp);
			return -1;
		}
		else 
		{
			P.coefficienti = (float*)malloc(sizeof(float) * (P.grado + 1));
			if (P.coefficienti == NULL)
				return -1;
			for (int i = 0; i < (P.grado + 1); i++) 
			{
				fscanf(fp, "%f", &P.coefficienti[i]);
			}

			if (!AggiungiPolinomio(polinomi, P))
				return -1;
			else
				num++;
		}
	}
	fclose(fp);
	return num;
}

/*
2) MoltiplicaPolinomi:
Funzione che, dato in ingresso la lista dei polinomi ed un parametro a reale, moltiplica tutti i
polinomi presenti nella lista per il valore a, restituendo la lista modificata.
Parametri in ingresso:
	- lista: lista dei polinomi
	- a: valore reale
*/
void MoltiplicaPolinomi(TListaPolinomi lista, float a) {
	// implementazione a cura dello studente
	while (lista != NULL) 
	{
		for (int i = 0; i < (lista->polinomio.grado+1);i++)
		{
			lista->polinomio.coefficienti[i] = lista->polinomio.coefficienti[i] * a;
		}
		lista = lista->next;
	}
}

/*
3) SommaPolinomi: Funzione che, dato in ingresso la lista dei polinomi ed un parametro g intero,
calcola la somma di tutti i polinomi di grado g presenti nella lista, restituendo il polinomio risultante.
Parametri in ingresso:
	- lista: lista dei polinomi
	- g: grado dei polinomi di cui calcolare la somma
Valore di ritorno:
	- polinomio risultante dall'operazione di somma
*/
TPolinomio SommaPolinomi(TListaPolinomi lista, int g) {
	// implementazione a cura dello studente
	TPolinomio PolinomioSomma = {0, NULL};
	PolinomioSomma.coefficienti = (float*)malloc(sizeof(float) * (g + 1));
	if (PolinomioSomma.coefficienti == NULL)
		return PolinomioSomma;
	for (int i = 0; i < (g + 1); i++)
		PolinomioSomma.coefficienti[i] = 0;
	while (lista != NULL) 
	{
		if (lista->polinomio.grado == g)
		{
			PolinomioSomma.grado = lista->polinomio.grado;
			for (int i = 0; i < (lista->polinomio.grado + 1); i++) 
			{
				PolinomioSomma.coefficienti[i] += lista->polinomio.coefficienti[i];
			}
		}
		lista = lista->next;
	}
	return PolinomioSomma;
}

// visualizza un polinomio
void VisualizzaPolinomio(TPolinomio p) {
	for (int i = 0; i < p.grado; i++)
		printf("%.2f x^%d + ", p.coefficienti[i], p.grado - i);
	printf("%.2f\n", p.coefficienti[p.grado]);
}

// visualizza una lista di polinomi
void VisualizzaLista(TListaPolinomi lista) {
	// implementazione a cura dello studente
	while (lista != NULL) 
	{
		printf("GRADO POLINOMIO: %d\n", lista->polinomio.grado);
		VisualizzaPolinomio(lista->polinomio);
		lista = lista->next;
	}
}

//  Disalloca una lista dei polinomi
void DisallocaLista(TListaPolinomi polinomi) {
	TListaPolinomi p;

	while (polinomi != NULL) {
		p = polinomi;
		polinomi = polinomi->next;
		free(p);
	}
}

int Menu() {
	int scelta;

	printf("*** MENU ***\n"
		"1. Carica polinomi\n"
		"2. Moltiplica polinomi per un fattore\n"
		"3. Somma polinomi di ugual grado\n"
		"0. Esci\n\n"
		"Scelta: ");
	scanf("%d", &scelta);

	return scelta;
}

int main(void) {
	int  scelta;
	TListaPolinomi lista = NULL;
	char nomefile[30];
	int esito;
	float fattore;
	int grado;
	TPolinomio polinomio;

	do {
		scelta = Menu();

		switch (scelta) {
		case 1:
			// Invocare la funzione CaricaPolinomi
			// e riportare l'esito del caricamento: errore o numero di polinomi caricati
			printf("Inserisci il nome del file: ");
			scanf("%s", nomefile);
			esito = CaricaPolinomi(nomefile, &lista);
			if (esito != -1)
				printf("Sono stati caricati %d polinomi.\n", esito);
			// visualizza la lista dei polinomi caricati
			VisualizzaLista(lista);
			break;

		case 2:
			// Acquisire il valore del fattore moltiplicativo
			printf("Inserisci un fattore moltiplicativo: ");
			scanf("%f", &fattore);
			// Invocare la funzione MoltiplicaPolinomi
			MoltiplicaPolinomi(lista, fattore);
			//Visualizzare la lista dei polinomi
			VisualizzaLista(lista);
			break;

		case 3:
			// Acquisire un grado
			printf("Inserisci un grado: ");
			scanf("%d", &grado);
			// Invocare la funzione SommaPolinomi
			polinomio = SommaPolinomi(lista, grado);
			// visualizzare il polinomio calcolato
			VisualizzaPolinomio(polinomio);
			break;
		}
	} while (scelta != 0);

	// Disallocare la memoria allocata invocando la funzione DisallocaLista
	DisallocaLista(lista);
	return 0;
}
