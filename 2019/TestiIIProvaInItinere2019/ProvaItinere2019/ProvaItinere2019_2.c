/*
Dato un archivio contenente le informazioni sugli atleti partecipanti ad una gara podistica (numero di gara, cognome, nome, categoria, tempo in secondi), 
implementare un programma in ANSI C che esponga le funzioni di seguito elencate.
Progettare la struttura dati adatta a mantenere in memoria centrale le informazioni utilizzando strutture e puntatori per le liste.
Scrivere un opportuno main in cui sia previsto un menu di scelta delle operazioni richieste. Tutti i valori necessari al funzionamento devono essere
passati utilizzando parametri, non è permesso l’uso di variabili globali.
1. Caricamento dati da file (vedi di seguito) in una lista semplice ordinata rispetto al cognome.
2. Conteggio degli atleti appartenenti ad una categoria il cui valore è fornito come parametro alla funzione.
3. Calcolo della classifica in base ad una categoria fornita come parametro, il risultato deve essere restituito in una seconda lista ordinata 
(che contiene, quindi, tutti e solo gli atleti che appartengono ad una specifica categoria) in modo decrescente rispetto al tempo,
N.B. il contenuto della lista in ingresso NON deve essere ne modificato ne cancellato, la lista in uscita contiene una copia di tutti gli elementi
4. Funzione che restituisce in un vettore di interi (passato come parametro) il numero di atleti iscritto in ogni categoria;

Esempio di file
100 BIANCHI GIUSEPPE SENIOR 654
12 ROSSI CARMELO JUNIOR 513
14 VERDI GIOVANNI JUNIOR 495
120 ARANGIO AGATINO SENIOR 712
25 AZZURRO SALVATORE JUNIOR 501
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PartecipanteS 
{
	int NumeroGara;
	char Cognome[32];
	char Nome[32];
	char Categoria[32];
	int TempoSecondi;
} PartecipanteT;

typedef struct NodoPartecipanteS 
{
	PartecipanteT info;
	struct NodoPartecipanteS* next;
} NodoPartecipanteT, * ListaPartecipanti;

int InserisciNodoPartecipante(ListaPartecipanti* PLista, PartecipanteT P) 
{
	NodoPartecipanteT* aux = (NodoPartecipanteT*)malloc(sizeof(NodoPartecipanteT));
	if (aux == NULL)
		return 0;
	aux->info = P;
	aux->next = (*PLista);
	(*PLista) = aux;
	return 1;
}

int InserisciPartecipanteOrdinato(ListaPartecipanti* PLista, PartecipanteT P) 
{
	if ((*PLista) == NULL) 
	{
		return InserisciNodoPartecipante(PLista, P);
	}
	if (strcmp(P.Cognome, (*PLista)->info.Cognome) > 0) 
	{
		return InserisciNodoPartecipante(PLista, P);
	}
	else 
	{
		return InserisciPartecipanteOrdinato(&((*PLista)->next), P);
	}
}

int CaricaDatiDaFile(ListaPartecipanti* PLista, char* NomeFile) 
{
	FILE* fp = fopen(NomeFile, "r");
	if (fp == NULL)
		return 0;
	int n = 0;
	PartecipanteT P;
	while (fscanf(fp, "%d%s%s%s%d", &P.NumeroGara, P.Cognome, P.Nome, P.Categoria, &P.TempoSecondi) == 5) 
	{
		if (!InserisciPartecipanteOrdinato(PLista, P))
			return 0;
		else
			n++;
	}
	return n;
}

int ConteggioAtleti(ListaPartecipanti Lista, char* Categoria) 
{
	if (Lista == NULL)
		return 0;
	int n = 0;
	while (Lista != NULL) 
	{
		if (strcmp(Lista->info.Categoria, Categoria) == 0)
		{
			n++;
		}
		Lista = Lista->next;
	}
	return n;
}

/*
3. Calcolo della classifica in base ad una categoria fornita come parametro, il risultato deve essere restituito in una seconda lista ordinata
(che contiene, quindi, tutti e solo gli atleti che appartengono ad una specifica categoria) in modo decrescente rispetto al tempo,
N.B. il contenuto della lista in ingresso NON deve essere ne modificato ne cancellato, la lista in uscita contiene una copia di tutti gli elementi
*/

int InserisciNodoPartecipantePerTempo(ListaPartecipanti* PLista, PartecipanteT P) 
{
	if ((*PLista) == NULL)
	{
		return InserisciNodoPartecipante(PLista, P);
	}
	if (P.TempoSecondi < ((*PLista)->info.TempoSecondi))
	{
		return InserisciNodoPartecipante(PLista, P);
	}
	else
		return InserisciNodoPartecipantePerTempo(&((*PLista)->next), P);
}

ListaPartecipanti CreaClassifica(ListaPartecipanti ListaIniziale, char* Categoria) 
{
	ListaPartecipanti Classifica = NULL;
	while (ListaIniziale != NULL) 
	{
		if (strcmp(ListaIniziale->info.Categoria, Categoria) == 0) 
		{
			InserisciNodoPartecipantePerTempo(&Classifica, ListaIniziale->info);
		}
		ListaIniziale = ListaIniziale->next;
	}
	return Classifica;
}

int Menu() 
{
	int scelta;
	printf("******** MENU ********\n"
		"1. Carica dati da file.\n"
		"2. Conteggio atleti appartenenti ad una categoria.\n"
		"3. Classifica in base alla categoria.\n"
		"4. Numero di atleti per categoria.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

void RestituisciVettore(ListaPartecipanti Lista, int v[])
{
	int cont1, cont2;
	cont1 = 0;
	cont2 = 0;
	while (Lista != NULL) 
	{
		if (strcmp(Lista->info.Categoria, "JUNIOR") == 0) 
		{
			cont1++;
		}
		if (strcmp(Lista->info.Categoria, "SENIOR") == 0) 
		{
			cont2++;
		}
		Lista = Lista->next;
	}
	int index = 0;
	v[index] = cont1;
	index++;
	v[index] = cont2;
}

void VisualizzaClassifica(ListaPartecipanti Lista) 
{
	int posto = 1;
	while (Lista != NULL) 
	{
		printf("POSTO %d:\n%s %s %s %d %d\n", posto, Lista->info.Categoria, Lista->info.Cognome, Lista->info.Nome, Lista->info.NumeroGara, Lista->info.TempoSecondi);
		Lista = Lista->next;
		posto++;
	}
}

int main() 
{
	int scelta;
	char Categoria[32];
	char NomeFile[64];
	int num;
	char Categorie[2][32] = { "JUNIOR", "SENIOR" };
	ListaPartecipanti Lista = NULL;
	ListaPartecipanti Classifica = NULL;
	int Vettore[2] = { 0 };
	do 
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			num = CaricaDatiDaFile(&Lista, NomeFile);
			if (num != 0)
				printf("Sono stati caricati %d dati da file.\n", num);
			break;
		case 2:
			printf("Inserisci il nome di una categoria: ");
			scanf("%s", Categoria);
			num = ConteggioAtleti(Lista, Categoria);
			if (num != 0)
				printf("Sono stati contati %d atleti.\n", num);
			break;
		case 3:
			printf("Inserisci il nome di una categoria: ");
			scanf("%s", Categoria);
			Classifica = CreaClassifica(Lista, Categoria);
			if (Classifica != NULL) 
			{
				VisualizzaClassifica(Classifica);
			}
			break;
		case 4:
			RestituisciVettore(Lista, Vettore);
			for (int i = 0; i < 2; i++) 
			{
				printf("CATEGORIA %s: %2d\n", Categorie[i], Vettore[i]);
			}
			printf("\n");
			break;
		}
 	} while (scelta != 0);
}