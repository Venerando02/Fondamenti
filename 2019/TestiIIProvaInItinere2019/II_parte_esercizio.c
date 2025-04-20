/*
Dato un archivio contenente le informazioni sugli atleti partecipanti ad una gara podistica (numero di gara, cognome, nome, categoria, tempo in secondi),
implementare un programma in ANSI C che esponga le funzioni di seguito elencate. Progettare la struttura dati adatta a mantenere in memoria centrale 
le informazioni utilizzando strutture e puntatori per le liste.
Scrivere un opportuno main in cui sia previsto un menu di scelta delle operazioni richieste. Tutti i valori necessari al funzionamento devono essere 
passati utilizzando parametri, non è permesso l’uso di variabili globali.
1. Caricamento dati da file (vedi di seguito) in una lista semplice ordinata rispetto al cognome.
2. Conteggio degli atleti appartenenti ad una categoria il cui valore è fornito come parametro alla funzione.
3. Calcolo della classifica in base ad una categoria fornita come parametro, il risultato deve essere restituito in una seconda lista ordinata (che contiene,
quindi, tutti e solo gli atleti che appartengono ad una specifica categoria) in modo decrescente rispetto al tempo, N.B. il contenuto della lista in ingresso
NON deve essere ne modificato ne cancellato, la lista in uscita contiene una copia di tutti gli elementi
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
#include <string.h>
#include <stdlib.h>

typedef struct AtletaS 
{
	int NumeroGara;
	char Cognome[256];
	char Nome[256];
	char Categoria[32];
	int Tempo;
} AtletaT;

typedef struct NodoS 
{
	AtletaT Info;
	struct NodoS* Next;
} NodoT, * ListaAtleti;

int AggiungiNodoLista(ListaAtleti* lista, AtletaT a)
{
	NodoT* aux = (NodoT*)malloc(sizeof(NodoT));
	if (aux == NULL)
		return 0;
	aux->Info = a;
	aux->Next = (*lista);
	(*lista) = aux;
	return 1;
}

int AggiungiOrdinatoCognome(ListaAtleti* lista, AtletaT a) 
{
	if ((*lista) == NULL)
		AggiungiNodoLista(lista, a);
	else if ((strcmp(a.Cognome, (*lista)->Info.Cognome) < 0))
	{
		AggiungiNodoLista(lista, a);
	}
	else
		return AggiungiOrdinatoCognome(&((*lista)->Next), a);
}

int CaricaDatiFile(ListaAtleti* lista, char* file) 
{
	FILE* fp = fopen(file, "r");
	int NumAtleti = 0;
	if (fp == NULL)
		return 0;
	AtletaT a;
	while (fscanf(fp, "%d%s%s%s%d", &a.NumeroGara, a.Cognome, a.Nome, a.Categoria, &a.Tempo) == 5) 
	{
		if (!AggiungiOrdinatoCognome(lista, a))
			return 0;
		else
			NumAtleti++;
	}
	return NumAtleti;
}

int ConteggioAtleti(ListaAtleti lista, char* Categoria) 
{
	int n = 0;
	while (lista != NULL) 
	{
		if (strcmp(lista->Info.Categoria, Categoria) == 0)
			n++;
		lista = lista->Next;
	}
	return n;
}

void InizializzaLista(ListaAtleti* Lista)
{
	*Lista = NULL;
}


int AggiungiOrdinatoTempo(ListaAtleti* lista, AtletaT a) 
{
	if ((*lista) == NULL)
		return AggiungiNodoLista(lista, a);
	else if (a.Tempo < (*lista)->Info.Tempo)
	{
		return AggiungiNodoLista(lista, a);
	}
	else 
	{
		return AggiungiOrdinatoTempo(&(*lista)->Next, a);
	}
}

ListaAtleti CalcoloClassifica(ListaAtleti lista, char* Categoria) 
{
	ListaAtleti classifica;
	InizializzaLista(&classifica);
	while (lista != NULL) 
	{
		if (strcmp(lista->Info.Categoria, Categoria) == 0) 
		{
			AggiungiOrdinatoTempo(&classifica, lista->Info);
		}
		lista = lista->Next;
	}
	return classifica;
}

int Menu()
{
	int scelta;
	printf("********* MENU *********\n"
		"1) Carica dati da file\n"
		"2) Conta atleti appartenenti alla categoria\n"
		"3) Calcolo Classifica\n"
		"4) Atleti iscritti alla categoria\n"
		"0) Esci\n\n"
		">> "
	);
	scanf("%d", &scelta);
	return scelta;
}

void VisualizzaLista(ListaAtleti lista) 
{
	while (lista != NULL)
	{
		printf("%d %s %s %s %d\n", lista->Info.NumeroGara, lista->Info.Cognome, lista->Info.Nome, lista->Info.Categoria, lista->Info.Tempo);
		lista = lista->Next;
	}
}

int* CalcoloAtletiPerCategoria(ListaAtleti lista) 
{
	// supponiamo ci siano 3 categorie, definiamo un array multidimensionale
	char Categorie[3][32] = { "JUNIOR", "SENIOR", "MASTER" };
	int* ConteggioCategorie = (int*)malloc(sizeof(int)*3);
	if (ConteggioCategorie == NULL)
		return NULL;
	for (int i = 0; i < 3; i++)
		ConteggioCategorie[i] = 0;
	while (lista != NULL)
	{
		for (int i = 0; i < 3; i++)
		{
			if (strcmp(lista->Info.Categoria, Categorie[i]))
			{
				ConteggioCategorie[i]++;
				break;
			}
		}
		lista = lista->Next;
	}
	return ConteggioCategorie;
}

int main() 
{
	int scelta;
	ListaAtleti Listatleti;
	InizializzaLista(&Listatleti);
	ListaAtleti classifica;
	int n;
	char Categorie[3][32] = { "JUNIOR", "SENIOR", "MASTER" };
	int NumAtleti;
	char NomeFile[32];
	int* conteggiocategorie;
	char Categoria[32];
	do 
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			NumAtleti = CaricaDatiFile(&Listatleti, NomeFile);
			if (NumAtleti != 0)
			{
				printf("Sono stati caricati %d atleti.\n", NumAtleti);
				VisualizzaLista(Listatleti);
				printf("\n");
			}
			else
				printf("Errore durante il caricamento dei dati.\n");
			break;
		case 2:
			printf("Inserisci la Categoria (in maiuscolo): ");
			scanf("%s", Categoria);
			n = ConteggioAtleti(Listatleti, Categoria);
			printf("Per la categoria %s sono stati contati %d atleti.\n", Categoria, n);
			break;
		case 3:
			printf("Inserisci la Categoria (in maiuscolo): ");
			scanf("%s", Categoria);
			classifica = CalcoloClassifica(Listatleti, Categoria);
			if (classifica != NULL)
				VisualizzaLista(classifica);
			printf("\n");
			break;
		case 4:
			conteggiocategorie = CalcoloAtletiPerCategoria(Listatleti);
			for (int i = 0; i < 3; i++) 
			{
				printf("CATEGORIA: %s -- NUMERO ATLETI: %d\n", Categorie[i], conteggiocategorie[i]);
			}
			printf("\n");
			break;
		}
	} while (scelta != 0);
}
