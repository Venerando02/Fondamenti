/*
  Scaricare l'esercizio e completarlo inserendo il codice necessario
  senza modificare quello esistente tranne quando espressamente
  richiesto.

  L'esercizio si considera corretto se il programma compila
  correttamente ed esegue senza errori run-time dando i risultati
  attesi.

  Il file sorgente deve essere consegnato allegandolo a questa
  attività.

  Il programma carica ed analizza quattro diversi percorsi rappresentati
  mediante una serie di punti geografici (latitudine, longitudine, altitudine,
  orario).
  Il programma carica quattro percorsi da quattro file diversi il cui nome è,
  rispettivamente: percorso_0.dat, percorso_1.dat, percorso_2.dat e percorso_3.dat
  in un vettore di code (necessario per garantire che il primo punto inserito venga
  memorizzato come primo punto estratto). Nota che per leggere dati di tipo double
  bisogna usare il marcatore %lf

  Le funzioni da sviluppare sono le seguenti:
  1. caricamento dei dati dai quattro file forniti nella struttura dati,
  vettore di code;
  2. calcolo della lunghezza di un percorso, per calcolare il percorso bisogna
  calcolare la distanza fra ogni coppia di punti mediante la funzione
  calcola_distanza_fra_punti() gia' sviluppata nel codice
  3. funzione che fornisce l'indice del percorso più lungo
  4. funzione che restituisce in un vettore di numeri reali la lunghezza di ogni percorso (il
  valore all'indice 0 restituisce la lunghezza del percorso 0, il valore all'indice 1
  la lunghezza del percorso 1, ecc.)

 Valori di test:
  Usando i valori nei file forniti il programma fornisce i seguenti risultati (a meno dell'approssimazione):
  punto 2:
	inserendo l'indice 0: distanza percorsa in km 1.077
  punto 3:
	percorso di maggiore lunghezza: 2
  punto 4:
		lunghezza percorso 0 =      1.077
		lunghezza percorso 1 =      0.181
		lunghezza percorso 2 =      1.177
		lunghezza percorso 3 =      0.168
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Struttura dati
// Definizione del punto
typedef struct punto_s {
	double latitudine, longitudine, altitudine;
	char orario[16];
} punto_t;
// Definizione del nodo della coda
typedef struct nodo_percorso_s {
	punto_t p;
	struct nodo_percorso_s* successivo;
} nodo_percorso_t, * nodo_percorso_pt;
// Definizione della coda che rappresenta il percorso
typedef struct percorso_s {
	nodo_percorso_pt primo, ultimo;
	unsigned int numero_punti;
} percorso_t;


// Funzioni di servizio
// Calcolo della distanza fra due punti (la funzione e' completamente
// sviluppata e non necessita di alcun intervento
// parametri:
//	punto_t a : primo punto
//  punto_t b : secondo punto
// valore restituito
//	float : distanza in metri
double calcola_distanza_fra_punti(punto_t a, punto_t b) {
	const double R = 6372.795477598;
	double lunghezza = R * acos(sin(a.latitudine) * sin(b.latitudine)
		+ cos(a.latitudine) * cos(b.latitudine) * cos(a.longitudine - b.longitudine));
	return (lunghezza > 0) ? lunghezza : 0.0;
}
// Funzioni di gestione del percorso
int percorso_numero_punti(percorso_t c) {
	return c.numero_punti;
}
nodo_percorso_pt percorso_aggiungi_punto(percorso_t* pc, punto_t p) {
	nodo_percorso_pt nuovo_nodo = (nodo_percorso_pt)malloc(sizeof(nodo_percorso_t));
	if (nuovo_nodo == 0)
		return NULL;
	nuovo_nodo->p = p;
	nuovo_nodo->successivo = NULL;
	if (percorso_numero_punti(*pc) == 0)
		pc->primo = pc->ultimo = nuovo_nodo;
	else {
		pc->ultimo->successivo = nuovo_nodo;
		pc->ultimo = nuovo_nodo;
	}
	++(pc->numero_punti);
	return nuovo_nodo;
}


#define NUMERO_PERCORSI 4
// Nota questo e' un semplice vettore di stringhe
#define NOMI_PERCORSI (char[][32]){"percorso_1.dat", "percorso_2.dat", "percorso_3.dat", "percorso_4.dat"} 

// Lo studente definisca la struttuta dati che implementa l'archivio
// dei percorsi come richiesto dal testo

// Questa funzione deve essere implementata dallo studente
// Carica i dati dai file predefiniti nella struttura dati 
//
// parametri:
//	archivio : archivio (struttura dati contenente i percorsi)
// 
// return:
//	0 : in caso di fallimento
//	1 : in caso di successo


int carica_percorsi(percorso_t* Archivio) {
	FILE* f = NULL;
	punto_t punto;
	nodo_percorso_pt aux;
	for (int i = 0; i < NUMERO_PERCORSI; ++i) {
		printf("\tCaricamento dei dati dal percorso %s\n", NOMI_PERCORSI[i]);
		// lo studente completi la funzione, 
		// N.B. il nome del file i-esimo (come e' possibile vedere nell'istruzione
		// precedente) e' contenuto in NOMI_PERCORSI[i]
		f = fopen(NOMI_PERCORSI[i], "r");
		if (f == NULL)
			return 0;
		while (fscanf(f, "%lf%lf%lf%s", &punto.latitudine, &punto.longitudine, &punto.altitudine, punto.orario) == 4) 
		{
			aux = percorso_aggiungi_punto(&Archivio[i], punto);
			if (aux == NULL)
				return 0;
		}
	}
	fclose(f);
	return 1;
}

// Questa funzione deve essere implementata dallo studente
// 
// la funzione calcola la lunghezza dell'intero percorso come sommatoria della
// distanza fra i punti, La distanza fra i punti si calcola con la funzione 
// calcola_distanza_fra_punti fornita gia implementata fra le funzoini di servizio.
// Nota che la funzione restituisce un valore di tipo double
//
// parametri:
//	 la funzione riceve in ingresso un percorso
// valore restituito
//	 lunghezza dell'intero percorso di tipo double
double calcolo_lunghezza_percorso(percorso_t P[], int indice)
{
	double lunghezza = 0.0;
	percorso_t Percorso = P[indice];
	// lo studente completi la funzione
	while ((Percorso.primo != NULL) && (Percorso.primo->successivo != NULL))
	{
		lunghezza += calcola_distanza_fra_punti(Percorso.primo->p, Percorso.primo->successivo->p);
		Percorso.primo = Percorso.primo->successivo;
	}
	return lunghezza;
}

// Questa funzione deve essere implementata dallo studente
// 
// la funzione calcola la lunghezza di tutti i percorsi presenti.
//
// parametri:
//	 la funzione riceve in ingresso l'archivio contenente tutti i percorsi
// valore restituito
//	 vettore di valori di tipo double che rappresentano la lunghezza dei percorsi
//	 di indice corrispondente

double* calcola_lunghezza_percorsi(percorso_t* Archivio, int dim) 
{
	double* Vettore = (double*)malloc(sizeof(percorso_t) * dim);
	if (Vettore == NULL)
		return NULL;
	for (int i = 0; i < dim; i++) 
	{
		Vettore[i] = calcolo_lunghezza_percorso(Archivio, i);
	}
	return Vettore;
}

// Questa funzione deve essere implementata dallo studente
// 
// la funzione calcola il percorso di maggiore lunghezza .
//
// parametri:
//	 la funzione riceve in ingresso l'archivio contenente tutti i percorsi
// valore restituito
//	 valore intero che rappresenta l'inbdice del percorso di maggiore lunghezza

int calcola_percorso_massimo(percorso_t* archivio, int dim) 
{
	// lo studente completi la funzione
	int pos = 0;
	double LunghezzaMax = calcolo_lunghezza_percorso(archivio, 0);
	double L;
	for (int i = 1; i < dim; i++) 
	{
		L = calcolo_lunghezza_percorso(archivio, i);
		if (L > LunghezzaMax) 
		{
			LunghezzaMax = L;
			pos = i;
		}
	}
	return pos;
}

int main(void) {
	int scelta;
	int indice;
	double Lunghezza;
	double* v = NULL;
	percorso_t archivio[NUMERO_PERCORSI] = {NULL};
	// Inserire le eventuali dichiarazioni utili al fine di implementare il programma
	do {
		printf("\n\n\n1. carica i dati\n");
		printf("2. calcolo della lunghezza di un percorso\n");
		printf("3. calcolo del percorso di maggiore lunghezza\n");
		printf("4. calcolo della lunghezza di tutti i percorsi\n\n");
		printf("0. esci\n");
		printf(">> ");
		scanf("%d", &scelta);
		switch (scelta) {
		case 0:
			printf("Programma terminato\n");
			break;
		case 1:
			// Carica i percorsi usando la funziona richiesta. In caso di errore
			// lo segnala all'utente
			if (carica_percorsi(archivio) == 1)
			{
				printf("Caricamento avvenuto con successo.\n");
			}
			else
				printf("Si e' verificato un errore.\n");
			// lo studente completi il codice
			break;
		case 2:
			// Calcola e stampa la lunghezza di un percorso dato l'indice.
			// Nota che deve essere usata la funzione richiesta e che la distanza
			// deve essere rappresentata in chilometri
			// 
			// Acquisisci l'indice del percorso da calcolare verificando
			// che sia compreso nell'intervallo corretto
			do {
				printf("Inserisci l'indice: ");
				scanf("%d", &indice);
			} while ((indice < 0) && (indice >= NUMERO_PERCORSI));
			Lunghezza = calcolo_lunghezza_percorso(archivio, indice);
			printf("La lunghezza massima e' %lf.\n", Lunghezza);
			// lo studente completi il codice

			break;

		case 3:
			// Stampa l'indice del percorso più lungo usando la funzione richiesta
			printf("L'indice massimo e' %d.\n", calcola_percorso_massimo(archivio, NUMERO_PERCORSI));
			// lo studente completi il codice
			break;
		case 4:
			// Stampa la lunghezza (in chilometri) di tutti i percorsi presenti 
			// nell'archivio
			v = calcola_lunghezza_percorsi(archivio, NUMERO_PERCORSI);
			for (int i = 0; i < NUMERO_PERCORSI; i++)
				printf("Percorso %d: %lf\n", i, v[i]);
			// lo studente completi il codice
		}
	} while (scelta != 0);
}