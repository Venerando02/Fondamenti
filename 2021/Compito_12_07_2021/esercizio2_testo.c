/*
Al pronto soccorso gli uetnti iningresso vengono gestiti in base alla criticità ella situazione 
definita, in ordine crescente di gravità, bianco, verde, giallo, rosso e al momento dell'arrivo.

Scrivere un programma che gestisce le code di attesa utilizzando una coda nella quale vengono
inseriti gli utenti al momento dell'arrivo, indipendentemente dal loro codice, e poi li distribuisce
in un vettore di code in cui ognuna di esse è relativa al codice di gravità.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CODICE_BIANCO	0
#define CODICE_VERDE	1
#define CODICE_GIALLO	2
#define CODICE_ROSSO	3

#define NUMERO_CODICI	4

const char CONVERSIONE[4][16] = { "Bianco", "Verde", "Giallo", "Rosso" };
const int TEMPO_ATTESA_PER_CODICE[4] = { 15, 30, 45, 90 };

#define LUNGHEZZA_STRINGA	128
/*
	Implementazione della struttura che rappresenta il paziente
*/
typedef struct paziente_s {
	char cognome[LUNGHEZZA_STRINGA];
	char nome[LUNGHEZZA_STRINGA];
	int  codice;
	char ora[6];		// formato AAAA-MM-GG HH:MM, 
							// 15:46 
	struct paziente_s* successivo;
} paziente_t;

//
//	confronta_paziente : confronta due pazienti (ipotesi: non esistono due pazienti con lo stesso nome e cognome)
//	parametri:
//				a,b : pazienti da confrontare
//	return
//				stessa convenzione di strcmp

int confronta_pazienti(paziente_t a, paziente_t b) {
	int k = strcmp(a.cognome, b.cognome);
	if (k != 0)
		return k;
	return strcmp(a.nome, b.nome);
}
typedef struct coda_pazienti_s {
	struct paziente_s *primo, *ultimo;
} coda_pazienti_t;

//
//	coda_vuota:	verifica se la coda è vuota
//	parametri:
//				c : coda da verificarer
//	return:
//				vero se la coda è vuota
int coda_vuota(coda_pazienti_t c) {
	return c.primo == NULL;
}

//
//	coda_inserisci:	inserisce un nuovo elemento in coda
//	parametri:
//				c : coda in cui inserire il nuovo elemento
//				p : nuovo paziente da inserire
void coda_inserisci(coda_pazienti_t *c, paziente_t p) {
	paziente_t* elemento = (paziente_t*)malloc(sizeof(paziente_t));
	*elemento = p;
	elemento->successivo = NULL;
	if (coda_vuota(*c))
		c->primo = c->ultimo = elemento;
	else {
		c->ultimo->successivo = elemento;
		c->ultimo = elemento;
	}
}

// coda_primo : restituisce il puntatore al primo elemento senza cancellarlo
// parametri:
//				c : coda in ingesso
// return:
//		restuirsce il puntatore all'elemento affiorante (primo elemento della coda) o NULL
//		in caso di coda vuota
paziente_t * coda_primo(coda_pazienti_t c) {
	if (coda_vuota(c))
		return NULL;
	return c.primo;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// FUNZIONE DA IMPLEMENTARE A CURA DELLO STUDENTE
////////////////////////////////////////////////////////////////////////////////////////////////
// coda_cancella_primo : cancella il primo elemento
// parametri:
//				c : coda in ingesso
void coda_cancella_primo(coda_pazienti_t *c) {
	// FUNZIONE DA IMPLEMENTARE A CURA DELLO STUDENTE
}
////////////////////////////////////////////////////////////////////////////////////////////////

//
//	stampa_coda : stampa il contenuto della coda dal primo all'ultimo elemento
//	parametri:
//				c : coda da stampare
coda_stampa(coda_pazienti_t c) {
	paziente_t* aux = c.primo;
	while (aux != NULL) {
		printf("%-20s %-20s %10s\n", aux->cognome, aux->nome, CONVERSIONE[aux->codice]);
		aux = aux->successivo;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
// FUNZIONE DA IMPLEMENTARE A CURA DELLO STUDENTE
////////////////////////////////////////////////////////////////////////////////////////////////
//
// coda_svuota : svuota la coda
// parametri:
//				c : coda da svuotare
void coda_svuota(/* Inserire i parametri richiesti - vedi specifica */) {
	// FUNZIONE DA IMPLEMENTARE A CURA DELLO STUDENTE

}
////////////////////////////////////////////////////////////////////////////////////////////////

//
//	carica_da_file:	legge i dati contenuti nel file
//	parametri:
//		c : coda in cui caricare i dati
//		f : desrittore del file aperto in precedenza
//	return:
//		numero di elementi letti o -1 in caso di errore
int	carica_da_file(/* Inserire i parametri richiesti - vedi specifica */) {
	paziente_t	p;
	int contatore = 0;
	if (f == NULL)
		return -1;

	while (fscanf(f, "%s%s%d%s", p.cognome, p.nome, &p.codice, p.ora) == 4) {
		coda_inserisci(c, p);
		++contatore;
	}
	return contatore;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// FUNZIONE DA IMPLEMENTARE A CURA DELLO STUDENTE
////////////////////////////////////////////////////////////////////////////////////////////////
//
//	costruisci_coda_attesa: crea il vettore di code di attesa distribuendo i pazienti rispetto al codice di
//			ingresso. Il vettore è allocato dinamicamente all'interno della funzione. La coda di ingresso
//			deve essere svuotata
//	parametri:
//			c : coda in ingresso
//	return:
//			vettore di code di attesa
/* Inserire il tipo richiesto - vedi specifica */ costruisci_coda_attesa(/* Inserire i parametri richiesti - vedi specifica */) {
	// FUNZIONE DA IMPLEMENTARE A CURA DELLO STUDENTE
}
////////////////////////////////////////////////////////////////////////////////////////////////

void stampa_lista_attesa(coda_pazienti_t l[]) {
	for (int codice = 0; codice < NUMERO_CODICI; ++codice) {
		printf("Codice %s\n", CONVERSIONE[codice]);
		coda_stampa(l[codice]);
		printf("-----\n");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
// FUNZIONE DA IMPLEMENTARE A CURA DELLO STUDENTE
////////////////////////////////////////////////////////////////////////////////////////////////
//
// calcolo_tempo_attesa : calcola il tempo stimato di attesa tenendo conto delle priorità aquisite e del tempo
//			medio di servizio fornito come costante (vedi dichiarazione delle costanti all'inizio del file)
// return:
//		restituisce il tempo in minuti o un valore -1 se il paziente non è stato trovato

int calcolo_tempo_attesa(/* Inserire i parametri richiesti - vedi specifica */) {
	// FUNZIONE DA IMPLEMENTARE A CURA DELLO STUDENTE
}
////////////////////////////////////////////////////////////////////////////////////////////////
// 

////////////////////////////////////////////////////////////////////////////////////////////////
// FUNZIONE DA IMPLEMENTARE A CURA DELLO STUDENTE
////////////////////////////////////////////////////////////////////////////////////////////////
//
//	calcola_lunghezza_code : restutuisce un vettore i cui elementi cointengono il numero di pazienti in attesa in ogni coda
//	parametri:
//				c : lista di attesa
//				v : vettore che contiene il risultato (allocazione da gestire nel main)

void calcola_lunghezza_code( /* Inserire i parametri richiesti - vedi specifica */ ) {
	// FUNZIONE DA IMPLEMENTARE A CURA DELLO STUDENTE
}
////////////////////////////////////////////////////////////////////////////////////////////////

int main(void) {
	coda_pazienti_t coda_ingresso = { NULL, NULL };
	coda_pazienti_t	*lista_attesa = NULL;
	paziente_t paziente;
	int numero_pazienti_in_attesa[NUMERO_CODICI];
	char nome_file[LUNGHEZZA_STRINGA];
	FILE* f = NULL;
	int scelta;
	do {
		printf("1. Carica da file i dati nella coda di ingresso\n");
		printf("2. Sposta i dati nella coda di attesa\n");
		printf("3. Calcola il tempo di attesa di un paziente\n");
		printf("4. numero di pazienti in attesa\n");
		printf("10. Stampa la lista di attesa\n");
		printf(">>> ");
		scanf("%d", &scelta);
		switch (scelta) {
		case 0:
			printf("Uscita dal programma\n");
			break;
		default:
			printf("Scelta non valida\n");
			break;
		case 1:
			// Inserire le istruzioni necessarie a richiedere il nome del file e caricare
			// i dati usando la funzione carica_da_file
			printf("Inserisci il nome del file dati: ");

			// Inserire il codice

			printf("letti %d elementi\n", n);
			coda_stampa(coda_ingresso);
			break;
		case 2:
			// Inserire le istruzioni necessarie a creare il vettore di code usando la funzione
			// costruisci_coda_attesa

			if (coda_vuota(coda_ingresso)) {
				printf("Nessun dato nella coda di ingresso\n");
				break;
			}

			// Inserire il codice

			break;
		case 3:
			// Inserire le istruzioni necessarie per leggere da tastiera i dati del paziente usano la variabile "paziente"
			// dichiarata all'inmizio del main, calcolare il tempo di attesa in secondi usando la funzione calcolo_tempo_di attesa
			// e stampare il risultato nel formato HH:MM
			printf("Inserisci cognome e nome: ");

			// Inserire il codice

			int t_in_secondi = calcolo_tempo_attesa(/* inserire i parametri attuali corretti*/);
			// Attenzione il tempo deve essere stampato nel formato ORA:MINUTI

			// Inserire il codice

			break;
		case 4:
			// Inserire le istruzioni necessarie per calcolare il numenro di elementi in ogni coda usando
			// la funzione calcola_lunghezza_code. Nota la variabile numero_pazienti in attesa
			// dichiarata all'inizio del maim
			calcola_lunghezza_code(/* inserire i parametri attuali corretti*/);
			for (int codice = 0; codice < NUMERO_CODICI; ++codice)
				printf("Codice %s : %d\n", CONVERSIONE[codice], numero_pazienti_in_attesa[codice]);
			break;
		case 10:
			if (lista_attesa != NULL)
				stampa_lista_attesa(lista_attesa);
			break;
		}
	} while (scelta != 0);

	// Inserire il codice necessario a liberare tutte le risorse allocate dinamicamente usando le funzioni 
	// definite ove possibile.
}