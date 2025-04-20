/*
Implementare una applicazione console in linguaggio ANSI C per la gestione di archivio di film. L’archivio dei film memorizza le proiezioni di film in un alcuni 
cinema. 
Tali informazioni sono memorizzate in un file di testo (un esempio di file è riportato alla fine del testo) e vengono caricate in una lista di programmazioni.
Successivamente, a partire da tale lista, viene costruito l’elenco dei cinema organizzato come una lista in cui ogni nodo riporta l’elenco dei film proiettati
presso lo specifico cinema.
Specifica della struttura dati
Programmazione
1 Titolo del film (stringa di 80 caratteri utili senza spazi, gli spazi sono sostituiti da un carattere _)
2 Nome del cinema (stringa di 15 caratteri utili senza spazi)
3 DataInizioProgrammazione (stringa nel formato aaaammgg)
4 DataFineProgrammazione (stringa nel formato aaaammgg)
Cinema
1 Nome del cinema (stringa di 15 caratteri utili senza spazi)
2 Elenco dei film proiettati presso il cinema (lista di Programmazioni)
3 Numero dei giorni totali nei quali è proiettato un film presso il cinema (un intero)
Elenco delle operazioni/funzioni che devono essere implementate
(Lo studente noti che il non rispetto delle specifiche nei quesiti 1 e 2, quindi la scelta di un nome della funzione diverso, di parametri differenti
o di valori di ritorno differenti sono considerati errori gravi a prescindere del fatto che la funzione svolga quanto richiesto).
1. Funzione di caricamento da file di testo delle presenze nella lista delle programmazioni. La funzione da implementare deve avere la seguente struttura:
nome della funzione: CaricaProgrammazioni
valore restituito: numero degli elementi caricati
parametri: nome del file, lista delle programmazioni
2. Funzione di ricerca del numero di cinema presso cui è stato proiettato un dato film. La funzione da implementare deve avere la seguente struttura:
nome della funzione: ContaCinema
valore restituito: 0 se la lista delle presenze è vuota, 1 altrimenti
parametri: lista delle presenze, titolo del film, numero di cinema in cui è stato proiettato il film
(NB: numero di cinema è un parametro di uscita che la funzione deve produrre e non visualizzare).
3. CreazioneElencoCinema: Crea la lista dei cinema a partire dalla lista delle programmazioni.
4. VisualizzaTutto: Visualizza, per ogni giorno, l’elenco dei film proiettati presso ciascun cinema utilizzando la lista dei cinema
5. CinemaPiu: La funzione deve fornire (come parametri d’uscita) il cinema che ha avuto più giorni di proiezioni e il numero dei giorni in cui in questo
cinema è stato proiettato un qualsiasi film.
6. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni implementate ed eventualmente di inserire i parametri 
necessari ed eseguire le operazioni richieste.

Esempio dei dati nel file di ingresso
Star_trek Alfieri 20180917 20180920
Mamma_Mia CineStar 20180917 20180925
Star_trek Ariston 20180917 20181020
Una_Storia_Senza_Nome Cinestar 20180918 20181020
Lucia Alfieri 20180918 20181025
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ProgrammazioneS
{
	char Titolo[80];
	char Cinema[15];
	char DataInizioProgrammazione[9];
	char DataFineProgrammazione[9];
} ProgrammazioneT;

typedef struct NodoFilmS
{
	ProgrammazioneT film;
	struct NodoFilmS* next;
} NodoFilmT, * ListaProgrammazione;

typedef struct CinemaS
{
	char NomeCinema[15];
	ListaProgrammazione Film;
	int NumeroGiorni;
	struct CinemaS* next;
} CinemaNodo, * ListaCinema;

/*
1. Funzione di caricamento da file di testo delle presenze nella lista delle programmazioni. La funzione da implementare deve avere la seguente struttura:
nome della funzione: CaricaProgrammazioni
valore restituito: numero degli elementi caricati
parametri: nome del file, lista delle programmazioni
*/

int InserisciNodoFilm(ListaProgrammazione* plista, ProgrammazioneT f)
{
	NodoFilmT* aux = (NodoFilmT*)malloc(sizeof(NodoFilmT));
	if (aux == NULL)
		return 0;
	aux->film = f;
	aux->next = (*plista);
	(*plista) = aux;
	return 1;
}

int CaricaDatiDaFile(ListaProgrammazione* plista, char* NomeFile)
{
	FILE* fp = fopen(NomeFile, "r");
	if (fp == NULL)
		return 0;
	ProgrammazioneT f;
	int n = 0;
	while (fscanf(fp, "%s%s%s%s", f.Titolo, f.Cinema, f.DataInizioProgrammazione, f.DataFineProgrammazione) == 4)
	{
		if (!InserisciNodoFilm(plista, f))
			return 0;
		else
			n++;
	}
	fclose(fp);
	return n;
}

/*
2. Funzione di ricerca del numero di cinema presso cui è stato proiettato un dato film. La funzione da implementare deve avere la seguente struttura:
nome della funzione: ContaCinema
valore restituito: 0 se la lista delle presenze è vuota, 1 altrimenti
parametri: lista delle presenze, titolo del film, numero di cinema in cui è stato proiettato il film
(NB: numero di cinema è un parametro di uscita che la funzione deve produrre e non visualizzare).
*/

int ContaCinema(ListaProgrammazione film, char* TitoloFilm, int* Ncinema)
{
	(*Ncinema) = 0;
	ListaProgrammazione l = film;
	while (l != NULL)
	{
		if (strcmp(l->film.Titolo, TitoloFilm) == 0)
		{
			(*Ncinema)++;
		}
		l = l->next;
	}
	if ((*Ncinema) == 0)
		return 0;
	else
		return 1;
}

/*
3. CreazioneElencoCinema: Crea la lista dei cinema a partire dalla lista delle programmazioni.
*/

int ContaGiorni(char* datafine, char* datainizio) 
{
	int Inizio = atoi(datainizio);
	int Fine = atoi(datafine);
	int differenza = Fine - Inizio;
	return differenza;
}

int CreazioneElencoCinema(ListaCinema* cinema, ListaProgrammazione film)
{
	ListaProgrammazione ListaFilm = film;
	while (ListaFilm != NULL) 
	{
		int trovato = 0;
		ListaCinema Corrente = (*cinema);

		while (Corrente != NULL) 
		{
			if (strcmp(Corrente->NomeCinema, ListaFilm->film.Cinema) == 0) 
			{
				trovato = 1;
				break;
			}
			Corrente = Corrente->next;
		}
		if (trovato == 1) 
		{
			Corrente->NumeroGiorni += ContaGiorni(ListaFilm->film.DataFineProgrammazione, ListaFilm->film.DataInizioProgrammazione);
			InserisciNodoFilm(&(Corrente->Film), ListaFilm->film);
		}
		else 
		{
			CinemaNodo* NuovoNodo = (CinemaNodo*)malloc(sizeof(CinemaNodo));
			if (NuovoNodo == NULL)
				return 0;
			strcpy(NuovoNodo->NomeCinema, ListaFilm->film.Cinema);
			NuovoNodo->NumeroGiorni = ContaGiorni(ListaFilm->film.DataFineProgrammazione, ListaFilm->film.DataInizioProgrammazione);
			NuovoNodo->Film = NULL;
			InserisciNodoFilm(&(NuovoNodo->Film), ListaFilm->film);
			NuovoNodo->next = (*cinema);
			(*cinema) = NuovoNodo;
		}
		ListaFilm = ListaFilm->next;
	}
	return 1;
}



void VisualizzaFilm(ListaProgrammazione film) 
{
	while (film != NULL)
	{
		printf("%s %s %s %s\n", film->film.Cinema, film->film.Titolo, film->film.DataInizioProgrammazione, film->film.DataFineProgrammazione);
		film = film->next;
	}
}

void VisualizzaCinema(ListaCinema cinema) 
{
	while (cinema != NULL) 
	{
		printf("CINEMA: %s\nFILM:\n", cinema->NomeCinema);
		VisualizzaFilm(cinema->Film);
		cinema = cinema->next;
	}
}

ListaCinema CinemaPiu(ListaCinema cinema)
{
	ListaCinema out = (CinemaNodo*)malloc(sizeof(CinemaNodo));
	if (out == NULL) 
	{
		return NULL;
	}
	int contatore;
	int max = 0;
	while (cinema != NULL) 
	{
		contatore = 0;
		while (cinema->Film != NULL) 
		{
			contatore++;
			cinema->Film = cinema->Film->next;
		}
		if (contatore > max) 
		{
			max = contatore;
			out->Film = NULL;
			strcpy(out->NomeCinema, cinema->NomeCinema);
			out->NumeroGiorni = cinema->NumeroGiorni;
			out->next = NULL;
		}
		cinema = cinema->next;
	}
	return out;
}

void DisallocaFilm(ListaProgrammazione* film) 
{
	ListaProgrammazione aux;
	while ((*film) != NULL) 
	{
		aux = (*film);
		(*film) = (*film)->next;
		free(aux);
	}
}

void DisallocaCinema(ListaCinema* cinema) 
{
	ListaCinema aux;
	while ((*cinema) != NULL) 
	{
		DisallocaFilm(&((*cinema)->Film));
		aux = (*cinema);
		(*cinema) = (*cinema)->next;
		free(aux);
	}
}

int Menu() 
{
	int scelta;
	printf("********* Menu *********\n"
		"1. Carica dati da file.\n"
		"2. Numero cinema in cui e' stato proiettato un film.\n"
		"3. Crea elenco cinema.\n"
		"4. Visualizza cinema.\n"
		"5. Cinema con piu' proiezioni.\n"
		"6. Disalloca Liste.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

int main() 
{
	int scelta;
	ListaProgrammazione film = NULL;
	ListaCinema cinema = NULL;
	char titolofilm[80];
	int n;
	ListaCinema cineOut = NULL;
	int esito;
	int NCinema;
	char NomeFile[32];
	do
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			n = CaricaDatiDaFile(&film, NomeFile);
			if (n != 0)
				printf("Sono stati caricati %d dati da file.\n", n);
			break;
		case 2:
			printf("Inserisci il nome del film: ");
			scanf("%s", titolofilm);
			n = ContaCinema(film, titolofilm, &NCinema);
			if (n == 1)
				printf("Sono stati trovati %d cinema.\n", NCinema);
			break;
		case 3:
			esito = CreazioneElencoCinema(&cinema, film);
			break;
		case 4:
			VisualizzaCinema(cinema);
			break;
		case 5:
			cineOut = CinemaPiu(cinema);
			if(cineOut != NULL)
				printf("Il cinema con piu' proiezione e' %s.\n", cineOut->NomeCinema);
			break;
		case 6:
			DisallocaFilm(&film);
			DisallocaCinema(&cinema);
			DisallocaCinema(&cineOut);
			break;
		}
	} while (scelta != 0);
}