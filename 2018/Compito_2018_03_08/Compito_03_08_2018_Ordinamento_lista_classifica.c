/*
SEZIONE 1: PROVA AL CALCOLATORE (VALORE MAX 23 PUNTI)
Implementare una applicazione console in linguaggio ANSI C per la gestione di un campo di bowling. 
Ciascun giocatore è identificato da un codice tesserino costituito da una stringa di 6 caratteri 
(identifica il giocatore in modo univoco) e il suo nome. Per ciascun giocatore vengono memorizzati 
i punti ottenuti e la squadra di appartenenza. Un giocatore può partecipare alla gara anche se non 
è associato ad una squadra in questo caso il campo squadra è uguale alla stringa “$$$”.
Ogni squadra sarà costituita dal nome della squadra e dalla lista dei giocatori della squadra
Specifica della struttura dati:
Giocatore :
1. Codice (stringa di 6 caratteri)
2. Cognome (stringa di 15 caratteri)
3. Nome (stringa di 15 caratteri)
4. Squadra (stringa di 15 caratteri)
5. Punteggio (un intero positivo)
Squadra
1. Nome squadra (stringa di 15 caratteri)
2. Elenco giocatori (lista di Giocatore)
3. PunteggioSquadra (un intero)
Elenco delle operazioni/funzioni che devono essere implementate:
1. Funzione di caricamento da file di testo dei prenotati nella lista dei giocatori.
La funzione da implementare deve avere la seguente struttura:
nome della funzione: CaricaGIOCATORI;
valore restituito: numero di giocatori caricati;
parametri: nome del file, lista dei giocatori.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per
rispettare la specifica.
2. Funzione Vincitore. Questa funzione trova e restituisci il giocatore singolo con il punteggio più alto,
in caso di parità restituisce il primo trovato.
nome della funzione: Vincitore;
valore restituito: codice, nome e cognome del vincitore
parametri: lista dei giocatori.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare
la specifica.
3. Funzione di modifica di un Punteggio. La funzione da implementare deve avere la seguente struttura:
nome della funzione: ModificaPunteggio;
valore restituito: esito operazione (0: operazione fallita, 1: modifica effettuata con successo);
parametri: lista dei giocatori, codice, nuovo_punteggio.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare
la specifica.
4. CreazioneLISTASquadre: Crea la lista delle squadre a partire dalla lista dei GIOCATORI. Ogni elemento della lista 
delle squadre contiene l’identificativo della squadra, la lista dei giocatori afferenti a quella squadra e il punteggio
della squadra. Se il giocatore non appartiene a nessuna squadra (valore campo $$$) non deve essere preso in 
considerazione. Il punteggio è pari alla somma dei primi migliori tre elementi della squadra (la squadra può 
contenere meno di tre elementi in questo caso verranno considerati tutti gli elementi per calcolare il punteggio della
squadra).
5. RicercaDelleSquadreNumerose: Funzione che, operando sulla lista delle squadre stampa i nomi delle squadre che hanno
presentato più di tre elementi.
6. StampaClassificaASquadre: Funzione che, operando sulla lista delle squadre stampa la classifica
7. Funzione che visualizza il contenuto dell’intera lista delle squadre
8. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni implementate ed
eventualmente di inserire i parametri necessari ad eseguire le operazioni richieste.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOMEFILE "DatiCompito2018.txt"

typedef struct GiocatoreS 
{
	char Codice[7];
	char Cognome[16];
	char Nome[16];
	char Squadra[16];
	int Punteggio;
} GiocatoreT;

typedef struct NodoGiocatoreS 
{
	GiocatoreT info;
	struct NodoGiocatoreS* next;
} NodoGiocatoreT, * ListaGiocatori;

typedef struct SquadraS 
{
	char NomeSquadra[16];
	int PunteggioSquadra;
} SquadraT;

typedef struct NodoSquadraS 
{
	SquadraT info;
	ListaGiocatori elenco;
	struct NodoSquadraS* next;
} NodoSquadraT, * ListaSquadre;

int AggiungiNodoGiocatore(ListaGiocatori* plista, GiocatoreT G) 
{
	NodoGiocatoreT* aux = (NodoGiocatoreT*)malloc(sizeof(NodoGiocatoreT));
	if (aux == NULL)
		return 0;
	aux->info = G;
	aux->next = (*plista);
	(*plista) = aux;
	return 1;
}

int AggiungiGiocatoreOrdinatoPunteggio(ListaGiocatori* plista, GiocatoreT G) 
{
	if (((*plista) == NULL) || (G.Punteggio > (*plista)->info.Punteggio))
		return AggiungiNodoGiocatore(plista, G);
	else
		return AggiungiGiocatoreOrdinatoPunteggio(&((*plista)->next), G);
}

/*
2. Funzione Vincitore. Questa funzione trova e restituisci il giocatore singolo con il punteggio più alto,
in caso di parità restituisce il primo trovato.
nome della funzione: Vincitore;
valore restituito: codice, nome e cognome del vincitore
parametri: lista dei giocatori.
*/


GiocatoreT* RitornaPrimoElemento(ListaGiocatori lista) 
{
	if (lista == NULL)
		return NULL;
	else
		return &(lista->info);
}

void CancellaGiocatore(ListaGiocatori* plista) 
{
	if ((*plista) == NULL)
		return;
	NodoGiocatoreT* aux;
	aux = (*plista);
	(*plista) = (*plista)->next;
	free(aux);
}

/*
1. Funzione di caricamento da file di testo dei prenotati nella lista dei giocatori.
La funzione da implementare deve avere la seguente struttura:
nome della funzione: CaricaGIOCATORI;
valore restituito: numero di giocatori caricati;
parametri: nome del file, lista dei giocatori.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per
rispettare la specifica.
*/

int CaricaGIOCATORI(ListaGiocatori* plista, char* NomeFile) 
{
	FILE* fp = fopen(NomeFile, "r");
	if (fp == NULL)
		return 0;
	int n = 0;
	GiocatoreT G;
	while (fscanf(fp, "%s%s%s%s%d", G.Codice, G.Cognome, G.Nome, G.Squadra, &G.Punteggio) == 5) 
	{
		if (!AggiungiGiocatoreOrdinatoPunteggio(plista, G))
			return 0;
		else
			n++;
	}
	fclose(fp);
	return n;
}

/*
3. Funzione di modifica di un Punteggio. La funzione da implementare deve avere la seguente struttura:
nome della funzione: ModificaPunteggio;
valore restituito: esito operazione (0: operazione fallita, 1: modifica effettuata con successo);
parametri: lista dei giocatori, codice, nuovo_punteggio.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare
la specifica.
*/

int ModificaPunteggio(ListaGiocatori lista, char* Codice, int punteggio)
{
	if (lista == NULL)
		return 0;
	ListaGiocatori l = lista;
	while (l != NULL)
	{
		if (strcmp(l->info.Codice, Codice) == 0)
		{
			l->info.Punteggio = punteggio;
			return 1;
		}
		l = l->next;
	}
	return 0;
}

/*
4. CreazioneLISTASquadre: Crea la lista delle squadre a partire dalla lista dei GIOCATORI. Ogni elemento della lista
delle squadre contiene l’identificativo della squadra, la lista dei giocatori afferenti a quella squadra e il punteggio
della squadra. Se il giocatore non appartiene a nessuna squadra (valore campo $$$) non deve essere preso in
considerazione. Il punteggio è pari alla somma dei primi migliori tre elementi della squadra (la squadra può
contenere meno di tre elementi in questo caso verranno considerati tutti gli elementi per calcolare il punteggio della
squadra).
*/

NodoSquadraT* CercaSquadra(ListaSquadre lista, char * NomeSquadra) 
{
	if (lista == NULL)
		return NULL;
	NodoSquadraT* aux = NULL;
	while (lista != NULL) 
	{
		if (strcmp(lista->info.NomeSquadra, NomeSquadra) == 0) 
		{
			aux = lista;
		}
		lista = lista->next;
	}
	return aux;
}

int CreazioneLISTASquadre(ListaSquadre* plista, ListaGiocatori listag) 
{
	ListaGiocatori G = listag;
	NodoSquadraT* aux;
	while (G != NULL) 
	{
		if (strcmp(G->info.Squadra, "$$$") != 0) 
		{
			aux = CercaSquadra((*plista), G->info.Squadra);
			if (aux == NULL)
			{
				NodoSquadraT* aux2 = (NodoSquadraT*)malloc(sizeof(NodoSquadraT));
				if (aux2 == NULL)
					return 0;
				strcpy(aux2->info.NomeSquadra, G->info.Squadra);
				aux2->info.PunteggioSquadra = G->info.Punteggio;
				aux2->elenco = NULL;
				if (!AggiungiGiocatoreOrdinatoPunteggio(&(aux2->elenco), G->info))
					return 0;
				aux2->next = (*plista);
				(*plista) = aux2;
			}
			else
			{
				aux->info.PunteggioSquadra += G->info.Punteggio;
				if (!AggiungiGiocatoreOrdinatoPunteggio((&aux->elenco), G->info))
					return 0;
			}
		}
		G = G->next;
	}
	return 1;
}

void DisallocaLista(ListaGiocatori* plista) 
{
	NodoGiocatoreT* aux;
	while ((*plista) != NULL) 
	{
		aux = (*plista);
		(*plista) = (*plista)->next;
		free(aux);
	}
}

NodoSquadraT* RestituisciPrimo(ListaSquadre Lista) 
{
	if (Lista == NULL)
		return NULL;
	else
		return Lista;
}

void CancellaNodoSquadra(ListaSquadre* plista) 
{
	if ((*plista) == NULL)
		return NULL;
	NodoSquadraT* aux;
	aux = (*plista);
	DisallocaLista(&((*plista)->elenco));
	(*plista) = (*plista)->next;
	free(aux);
}

ListaSquadre AggiungiNodoSquadra(ListaSquadre lista, SquadraT Sq) 
{
	NodoSquadraT* aux = (NodoSquadraT*)malloc(sizeof(NodoSquadraT));
	if (aux == NULL)
		return NULL;
	aux->info = Sq;
	aux->elenco = NULL;
	aux->next = lista;
	return aux;
}

ListaSquadre AggiungiNodoSquadraOrdinato(ListaSquadre lista, SquadraT Sq) 
{
	if ((lista == NULL) || (Sq.PunteggioSquadra > lista->info.PunteggioSquadra))
	{
		return AggiungiNodoSquadra(lista, Sq);
	}
	else
		return AggiungiNodoSquadraOrdinato(lista->next, Sq);
}

void CreaClassifica(ListaSquadre* plista) 
{
	ListaSquadre Classifica = NULL;
	int cont;
	NodoSquadraT* aux;
	while ((*plista) != NULL) 
	{
		cont = 0;
		aux = RestituisciPrimo((*plista));
		Classifica = AggiungiNodoSquadraOrdinato(Classifica, aux->info);
		while (aux->elenco != NULL) 
		{
			if (!AggiungiGiocatoreOrdinatoPunteggio(&(Classifica->elenco), aux->elenco->info))
				return;
			aux->elenco = aux->elenco->next;
			cont++;
			if (cont == 3)
				break;
		}
		CancellaNodoSquadra(plista);
	}
	(*plista) = Classifica;
}

/*
5. RicercaDelleSquadreNumerose: Funzione che, operando sulla lista delle squadre stampa i nomi delle squadre che hanno
presentato più di tre elementi.
*/

void RicercaDelleSquadreNumerose(ListaSquadre Lista)
{
	int cont;
	int n_elementi = 3;
	ListaGiocatori Players;
	ListaSquadre Corrente = Lista;
	while (Corrente != NULL) 
	{
		cont = 0;
		Players = Corrente->elenco;
		while (Players != NULL) 
		{
			cont++;
			Players = Players->next;
		}
		if (cont >= n_elementi) 
		{
			printf("%s\n", Corrente->info.NomeSquadra);
		}
		Corrente = Corrente->next;
	}
}

int Menu() 
{
	int scelta;
	printf(
		"******** MENU ********\n"
		"1. Carica dati da file.\n"
		"2. Determina vincitore.\n"
		"3. Modifica punteggio.\n"
		"4. Crea lista squadre.\n"
		"5. Ricerca squadre numerose.\n"
		"6. Stampa classifica squadre.\n"
		"7. Visualizza liste.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

void StampaListaGiocatori(ListaGiocatori lista) 
{
	while (lista != NULL) 
	{
		printf("%s %s %s %s %d\n", lista->info.Codice, lista->info.Cognome, lista->info.Nome, lista->info.Squadra, lista->info.Punteggio);
		lista = lista->next;
	}
}

void StampaListaSquadre(ListaSquadre lista) 
{
	while (lista != NULL) 
	{
		printf("%s %d\nELENCO:\n", lista->info.NomeSquadra, lista->info.PunteggioSquadra);
		StampaListaGiocatori(lista->elenco);
		printf("\n");
		lista = lista->next;
	}
}

void StampaClassificaSquadre(ListaSquadre lista)
{
	int Posizione = 1;
	while (lista != NULL)
	{
		printf("%d POSTO:\n", Posizione);
		printf("%s %d\nELENCO:\n", lista->info.NomeSquadra, lista->info.PunteggioSquadra);
		StampaListaGiocatori(lista->elenco);
		printf("\n\n");
		Posizione++;
		lista = lista->next;
	}
}


int main() 
{
	ListaGiocatori Giocatori = NULL;
	ListaSquadre Squadre = NULL;
	GiocatoreT* Vincitore = NULL;
	char Codice[7];
	int Punteggio;
	int scelta;
	char NomeFile[64];
	int n;
	do
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			n = CaricaGIOCATORI(&Giocatori, NOMEFILE);
			if (n != 0)
				printf("Sono stati caricati %d giocatori.\n", n);
			break;
		case 2:
			Vincitore = RitornaPrimoElemento(Giocatori);
			printf("Il vincitore e' %s %s con punteggio %d.\n", (*Vincitore).Cognome, (*Vincitore).Nome, (*Vincitore).Punteggio);
			break;
		case 3:
			printf("Inserisci il codice: ");
			scanf("%s", Codice);
			printf("Inserisci il punteggio: ");
			scanf("%d", &Punteggio);
			n = ModificaPunteggio(Giocatori, Codice, Punteggio);
			if (n == 1)
				printf("Modifica avvenuta con successo.\n");
			break;
		case 4:
			n = CreazioneLISTASquadre(&Squadre, Giocatori);
			if (n == 1)
				printf("Lista creata con successo.\n");
			break;
		case 5:
			RicercaDelleSquadreNumerose(Squadre);
			break;
		case 6:
			CreaClassifica(&Squadre);
			StampaClassificaSquadre(Squadre);
			break;
		case 7:
			StampaListaSquadre(Squadre);
			break;
		}
	} while (scelta != 0);
}