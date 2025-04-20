/* II prova in itinere - A.A. 2022/2023 */

/*
* Sviluppare un programma per la gestione degli eventi di un centro scommesse sportive. Gli eventi sono inizialmente memorizzati in un file di testo in cui ogni riga contiene i seguenti dati:
- sport (stringa come specificato in seguito)
- Codice Evento (stringa)
- Squadra 1 (stringa)
- Squadra 2 (stringa)
- Quota vittoria squadra 1 (reale)
- Quota vittoria squadra 2 (reale)

Gli sport che il centro gestisce sono 5 e ai fini del vettore sono identificati da un intero con la seguente corrispondenza:
CALCIO 0
BASKET 1
PALLAVOLO 2
RUGBY 3
PALLANUOTO 4

Implementare le seguenti funzioni:

1) CaricaDatiDaFile:
Carica i dati degli eventi sportivi dal file e le memorizza in un array di liste. L'elemento i-esimo dell'array contiene la lista degli eventi sportivi relativi allo sport i-esimo. La funzione restituisce il numero totale di eventi sportivi caricati o -1 in caso di errore durante il caricamento.

2) EventiQuoteMax:
Dato l'array di liste di eventi sportivi, calcola e restituisce in un opportuno vettore gli eventi aventi il valore massimo per una delle quote per ciascuno sport. Il vettore ha quindi un numero di elementi pari al numero di sport presenti.


3) EventiSportSquadra:
Dato l'array di liste di eventi sportivi, uno sport ed una squadra, estrae e restituisce in una lista di eventi sportivi, tutti gli eventi dello sport fornito che coinvologno la squadra fornita in ingresso come parametro.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

/*
COGNOME NOME Musumeci Venerando Pio 
N. MATRICOLA 1000015141
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SPORT 5
#define DIMS 32

char TipoSport[NUM_SPORT][DIMS] = {"CALCIO", "BASKET", "PALLAVOLO", "RUGBY", "PALLANUOTO"};

#define CALCIO 0
#define BASKET 1
#define PALLAVOLO 2
#define RUGBY 3
#define PALLANUOTO 4

typedef struct Evento {
	char codice_evento[DIMS];
	char squadra1[DIMS];
	char squadra2[DIMS];
	float quota1;
	float quota2;
} TEvento;

typedef struct NodoListaEventi
{
	TEvento                 info;
	struct NodoListaEventi* next;
} TNodoListaEventi;

typedef TNodoListaEventi* T_ListaEventi;

// Visualizza i dati di una lista di eventi sportivi
void VisualizzaDatiLista(T_ListaEventi lista) {
	//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
	T_ListaEventi aux = lista;
	while (aux != NULL) 
	{
		printf("%s %s %s %.3f %.3f\n", aux->info.codice_evento, aux->info.squadra1, aux->info.squadra2, aux->info.quota1, aux->info.quota2);
		aux = aux->next;
	}
}

// Aggiunge un evento alla lista di eventi, restituisce 1
// se l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiNodoLista(T_ListaEventi* plista, TEvento elem) {
	T_ListaEventi p;

	p = (T_ListaEventi)malloc(sizeof(TNodoListaEventi));
	if (p == NULL)
		return 0;

	p->info = elem;
	p->next = *plista;
	*plista = p;

	return 1;
}

int RestituisciIndice(char* evento) 
{
	if (strcmp(evento, "CALCIO") == 0)
		return CALCIO;
	else if (strcmp(evento, "BASKET") == 0)
		return BASKET;
	else if (strcmp(evento, "PALLAVOLO") == 0)
		return PALLAVOLO;
	else if (strcmp(evento, "RUGBY") == 0)
		return RUGBY;
	else if (strcmp(evento, "PALLANUOTO") == 0)
		return PALLANUOTO;
}

/*
1) CaricaDatiDaFile:
Carica i dati degli eventi sportivi dal file e le memorizza in un array di liste. L'elemento i-esimo dell'array contiene la lista degli eventi sportivi relativi allo sport i-esimo. La funzione restituisce il numero totale di eventi sportivi caricati o -1 in caso di errore durante il caricamento.

Parametri: nome del file, array di liste di eventi sportivi
Restituisce: il numero totale di di eventi sportivi caricati, -1 in caso di
errore durante il caricamento

*/
int CaricaDatiDaFile(char* nome_file, T_ListaEventi* eventi) {
	//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
	FILE* fp = fopen(nome_file, "r");
	if (fp == NULL)
		return -1;
	char evento[DIMS];
	TEvento aux;
	int n = 0;
	int indice;
	while (fscanf(fp, "%s%s%s%s%f%f", evento, aux.codice_evento, aux.squadra1, aux.squadra2, &aux.quota1, &aux.quota2) == 6)
	{
		indice = RestituisciIndice(evento);
		if (!AggiungiNodoLista(&eventi[indice], aux))
			return -1;
		else n++;
	}
	return n;
}


/*
2) EventiQuoteMax:
Dato l'array di liste di eventi sportivi, calcola e restituisce in un opportuno vettore gli eventi aventi il valore massimo per una delle quote per ciascuno sport.
Il vettore ha quindi un numero di elementi pari al numero di sport presenti.

Parametri: array di liste di eventi sportivi
Restituisce: Vettore di eventi sportivi in cui l'elemento i-esimo rappresenta l'evento avente quota di valore massimo per lo sport i-esimo
*/
// siccome mi dice per una delle quote, trovo il massimo solo per quota 1
TEvento* EventiQuoteMax(T_ListaEventi* eventi) {
	//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
	T_ListaEventi lista;
	TEvento* vettore = malloc(sizeof(TEvento)*NUM_SPORT);
	float massimo;
	TEvento aux = {NULL};
	for (int i = 0; i < NUM_SPORT; i++) 
	{
		lista = eventi[i];
		massimo = lista->info.quota1;
		while (lista != NULL) 
		{
			if (lista->info.quota1 > massimo)
			{
				massimo = lista->info.quota1;
				aux = lista->info;
			}
			lista = lista->next;
		}
		vettore[i] = aux;
	}
	return vettore;
}


/*
3) EventiSportSquadra:
Dato l'array di liste di eventi sportivi, uno sport ed una squadra, la funzione estrae e restituisce in una lista
di eventi sportivi tutti gli eventi dello sport fornito che coinvolgono la squadra fornita in ingresso come parametro.

Parametri in ingresso: array di liste di eventi sportivi, codice sport, squadra
Restituisce: lista di eventi sportivi, con i dati degli eventi dello sport fornito in ingresso che contengono la squadra fornita in ingresso come parametro
*/

T_ListaEventi EventiSportSquadra(T_ListaEventi *vettore, int sport, char * squadra) 
{
	//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
	T_ListaEventi lista_out = NULL;
	char evento[DIMS];
	strcpy(evento, TipoSport[sport]);
	T_ListaEventi aux;
	for (int i = 0; i < NUM_SPORT; i++) 
	{
		aux = vettore[i];
		while (aux != NULL) 
		{
			if ((strcmp(aux->info.squadra1, squadra) == 0) || (strcmp(aux->info.squadra2, squadra) == 0) && (strcmp(aux->info.codice_evento, evento) == 0))
			{
				AggiungiNodoLista(&lista_out, aux->info);
			}
			aux = aux->next;
		}
	}
	return lista_out;
}


//  Disalloca una lista di eventi sportivi
void DisallocaLista(T_ListaEventi lista) {
	//  IMPLEMENTARE IL CORPO DELLA FUNZIONE
	T_ListaEventi aux;
	while (lista != NULL) 
	{
		aux = lista;
		lista = lista->next;
		free(aux);
	}
}

//menù di scelta
int Menu() {
	int scelta;

	printf("*** MENU ***\n"
		"1. Carica dati dal file\n"
		"2. Calcola eventi sportivi con quote max\n"
		"3. Eventi di uno sport e di una squadra\n"
		"0. Esci\n\n"
		"Scelta: ");
	scanf("%d", &scelta);

	return scelta;
}


/*************** MAIN *****************/
int main(void) {
	int scelta;
	T_ListaEventi vettore[NUM_SPORT];
	char nomefile[DIMS];
	int n;
	TEvento* vmax;
	T_ListaEventi nuovalista;
	int codicesport;
	char squadra[DIMS];

	for (int i = 0; i < NUM_SPORT; i++)
		vettore[i] = NULL;

	do {
		scelta = Menu();

		switch (scelta) {
		case 1:
			// Invocare la funzione CaricaDatiDaFile e visualizzare il numero di
			// eventi sportivi caricati o gli eventuali errori
			printf("Inserisci nome file: ");
			scanf("%s", nomefile);
			n = CaricaDatiDaFile(nomefile, vettore);
			printf("Sono stati caricati %d file...", n);
			printf("\n\n");
			break;

		case 2:
			// invocare la funzione EventiQuoteMax e visualizzare per ciascuno sport 
			// gli eventi con quote max
			vmax = EventiQuoteMax(vettore);
			printf("-----------------RISULTATO-----------------\n");
			for (int i = 0; i < NUM_SPORT; i++)
				printf("SPORT: %s - CODICE: %s - QUOTA 1: %.3f\n", TipoSport[i], vmax[i].codice_evento, vmax[i].quota1);
			printf("\n\n");
			break;

		case 3:
			// acquisire da input i dati necessari 
			// e poi invocare la funzione EventiSportSquadra
			printf("Inserisci il codice dello sport: ");
			scanf("%d", &codicesport);
			printf("Inserisci il nome della squadra: ");
			scanf("%s", squadra);
			nuovalista = EventiSportSquadra(vettore, codicesport, squadra);
			// Dopodichè visualizzare i risultati ottenuti
			printf("Lista RISULTANTE\n");
			VisualizzaDatiLista(nuovalista);
			printf("\n\n");
			break;
		}
	} while (scelta != 0);

	//disallocare la memoria
	for (int i = 0; i < NUM_SPORT; i++)
		DisallocaLista(vettore[i]);

	return 0;
}
