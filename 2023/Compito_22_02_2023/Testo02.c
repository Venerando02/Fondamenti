/*
* Scrivere un programma in ANSI C che implementa un sistema di code prioritarie di eventi. Il sistema
* carica i dati da un file di testo (un evento per ogni riga) e carica i dati in tre code distinte
* in base al valore di priorità, appartenente all'intervallo [0,2].
* Le operazioni da compiere sono le seguenti:
* 1. caricamento dei dati da file, qualora le code non siano vuote gli eventi devono essere aggiunti;
* 2. estrazione del primo evento in base alle priorità, questo implica che il dato deve essere estratto
* prima dalla coda di maggiore priorità e successivamente, sempre in ordine di priorità, dalle code successive;
* 3. Ricerca degli eventi in base al nome, nota che possono esistere più eventi con lo stesso nome
* 4. spostamento degli eventi da una coda ad un'altra.
*
* Esempio file ingresso
*	accensione_caldaia	1
*	accensione_lampada	2
*	spegnimento_caldaiao 1
*	allarme_intrusione	0
*	temperatura_bassa	1
*	accensione_illiminazione 2
*	apertura_garage	2
* 
* con i dati in ingresso richiamare l'opzione 3 con il termine caldaia da i seguenti valori
* accensione_caldaia
* spegnimento_caldaia
* 
* richiamare l'opzione 2 due volte consecutive
* allarme_intrusione
* accensione_caldaia
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAXSTRLEN	80
typedef struct evento_s {
	char nome[MAXSTRLEN];
	int priorita;
	struct evento_s* n;
} evento_t;

// Lo studente implementi il tipo di dato coda e le funzioni di
// inserimento e estrazione

typedef struct coda_s {
	// Da completare
} coda_t;

int carica_file(char* nomefile, coda_t coda[], int numero_code) {
	FILE* f = NULL;
	evento_t ev;
	f = fopen(nomefile, "r");
	if (f == NULL)
		return 0;		// Il valore 0 significa errore
	while (fscanf(f, "%s%d", ev.nome, &ev.priorita) == 2) {
		// Lo studente inserisca il codice necessario ad inserire i dati
		// nelle code appropriate
	}
	fclose(f);
	return 1;			// Il valore 1 significa successo
}

/*
*	estrai_elemento
*
*	la funzione estrai il primo elemento dal gruppo di code, l'algoritmo di estrazione
*	prevede che si estragga (e quindi elemini dalla coda corrispondente) il primo elemento
*	della coda a maggiore priorità, se esiste,
*	altrimenti si procede ad estrarre l'elemwnto dalle code successive
*
*	parametri:
*		vettore delle code
*		dimensione del vettore di code
*	return
*		puntatore all'elemento estratto che assume il valore NULL se non sono presenti
*		elementi in nessuna delle code
*/

evento_t* estrai_elemento(/* I parametri devono essere definiti dallo studente */) {}
// La funzione deve essere implementata dallo studente

/*
*	ricerca_elementi
*
*	la funzione restituisce una copia di tutti gli elementi che hanno il nome specificato nei parametri
*	tramite un vettore di eventi fino ad un
*	numero massimo specificato nei parametri
*
*	parametri:
*		vettore delle code
*		dimensione del vettore di code
*		vettore di puntatori agli elementi trovati
*		dimensione del vettore di puntatori che rappresenta anche il massimo numero
*			du elementi che può essere restituito
*
*	return
*		numero di elementi trocato
*/

/*
*	contenuta
*
*	la funzione restituisce 1 se una stringa passata come secondo paramtero e' contenuta
*	nella stringa passata come primo parametro
*	FUNZIONE DA USARE NELLE ricerca_elementi
*/
int contenuta(char* frase, char* parola) {
	return strstr(frase, parola) != NULL;
}
int ricerca_elementi(/* I parametri devono essere definiti dallo studente */) {}

/*
*	sposta_elementi
*
*	la funzione sposta un numero N di elementi dalla coda sorgente alla coda di destinazione
*
*	parametri
*		coda sorgente
*		coda destinazione
*		numero di elementi da spostare
*	return
*		nessuno
*/

void sposta_elementi(coda_t* coda_sorgente, coda_t* coda_destinazione, int numero_elementi) {
	// Il corpo della funzione deve essere definito dallo studente
}

int menu(void) {
	printf("1. Carica i dati da file\n");
	printf("2. Estrai l'elemento affiorante\n");
	printf("3. Ricerca degli eventi\n");
	printf("4. Sposta elementi");
	printf("0. uscita");

	printf("\n\n>>> ");
	int selezione;
	scanf("%d", &selezione);
	return selezione;
}
#define NUMERO_CODE 3
#define NUMERO_ELEMENTI_DA_CERCARE 5
int main(void) {
	coda_t vettore_code[NUMERO_CODE] = { {NULL,NULL} };
	FILE* f = NULL;
	char buffer[MAXSTRLEN];
	evento_t ev;
	evento_t* pev = NULL;
	evento_t vettore_uscita[NUMERO_ELEMENTI_DA_CERCARE];

	do {
		switch (menu()) {
		case 1: // Caricamento dei dati da file
			printf("Inserisci il nome del file: ");
			scanf("%s", buffer);
			// Lo studente chiami la funzione passando i parametri necessari		
			break;
		case 2:
			pev = estrai_elemento(/* Lo studente inserisca i parametri attesi*/);
			if (pev != NULL)
				printf("Elemento affiorante %s\n", pev->nome);
			else
				printf("Nessun elemento \n");
			pev = NULL;
			break;
		case 3:
			printf("Inserisci il termine da cercare: ");
			scanf("%s", buffer);
			int n = ricerca_elementi(/* lo studente inserica i parametri necessari*/);
			for (int i = 0; i < n; i++)
				printf("%s\n", vettore_uscita[i].nome);
			break;
		case 4: {
			int indice_coda_sorgente;
			int indice_coda_destinazione;
			int numero_elementi;
			printf("Inserisci l'indice della coda di ingresso e della coda di uscita: ");
			scanf("%d%d", &indice_coda_sorgente, &indice_coda_destinazione);
			printf("Inserisci il numero di elementi da copiare: ");
			scanf("%d", &numero_elementi);
			sposta_elementi(/* Inserisci i parametri */);
			break;
		}
		case 0:
			return 1;
		}
	} while(1)
}