/*
Implementare una applicazione console in linguaggio ANSI C per la gestione di un campo di bowling. 
Ciascun giocatore è identificato da un codice tesserino costituito da una stringa di 6 caratteri 
(identifica il giocatore in modo univoco) e il suo nome. Per ciascun giocatore vengono memorizzati i punti ottenuti
e la squadra di appartenenza. Un giocatore può partecipare alla gara anche se non è associato ad una squadra in 
questo caso il campo squadra è uguale alla stringa “$$$”.
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
4. CreazioneLISTASquadre: Crea la lista delle squadre a partire dalla lista dei GIOCATORI. Ogni elemento della
lista delle squadre contiene l’identificativo della squadra, la lista dei giocatori afferenti a quella squadra 
e il punteggio della squadra. Se il giocatore non appartiene a nessuna squadra (valore campo $$$) non deve essere
preso in considerazione. Il punteggio è pari alla somma dei primi migliori tre elementi della squadra (la squadra
può contenere meno di tre elementi in questo caso verranno considerati tutti gli elementi per calcolare il punteggio 
della squadra).
5. RicercaDelleSquadreNumerose: Funzione che, operando sulla lista delle squadre stampa i nomi delle squadre che
hanno presentato più di tre elementi.
6. StampaClassificaASquadre: Funzione che, operando sulla lista delle squadre stampa la classifica
7. Funzione che visualizza il contenuto dell’intera lista delle squadre
8. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni
implementate ed eventualmente di inserire i parametri necessari ad eseguire le operazioni richieste.

Le informazioni nel file per ciascun iscritto si trovano distribuite su una riga:
Codice Cognome Nome Squadra Punteggio
Si suppone che Cognome, Nome e Squadra non contengono caratteri bianchi.
Esempio di file:
c123 Rossi Giuseppe Squadra1 200
C124 Bianchi Luigi Squadra2 187
c125 Russo Giovanna $$$ 234
c002 Verdi Giuseppe Squadra2 201
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct NodoSquadraS 
{
	char Nome[16];
	ListaGiocatori Elenco;
	int PunteggioSquadra;
	struct NodoSquadraS* next;
} NodoSquadraT, * ListaSquadre;

int AggiungiNodoGiocatore(ListaGiocatori* Plista, GiocatoreT player) 
{
	NodoGiocatoreT* aux = (NodoGiocatoreT*)malloc(sizeof(NodoGiocatoreT));
	if (aux == NULL)
		return 0;
	aux->info = player;
	aux->next = (*Plista);
	(*Plista) = aux;
	return 1;
}

int AggiungiNodoGiocatorePerPunteggio(ListaGiocatori* PLista, GiocatoreT player) 
{
	if (((*PLista) == NULL) || (player.Punteggio > (*PLista)->info.Punteggio))
		return AggiungiNodoGiocatore(PLista, player);
	else
		return AggiungiNodoGiocatorePerPunteggio(&((*PLista)->next), player);
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

int CaricaGIOCATORI(ListaGiocatori* PLista, char* NomeFile) 
{
	FILE* fp = fopen(NomeFile, "r");
	if (fp == NULL)
		return 0;
	GiocatoreT G;
	int num = 0;
	while (fscanf(fp, "%s%s%s%s%d", G.Codice, G.Cognome, G.Nome, G.Squadra, &G.Punteggio) == 5) 
	{
		if (!AggiungiNodoGiocatorePerPunteggio(PLista, G))
			return 0;
		else
			num++;
	}
	fclose(fp);
	return num;
}

/*
2. Funzione Vincitore. Questa funzione trova e restituisci il giocatore singolo con il punteggio più alto,
in caso di parità restituisce il primo trovato.
nome della funzione: Vincitore;
valore restituito: codice, nome e cognome del vincitore
parametri: lista dei giocatori.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare
la specifica.
*/

// Secondo l'implementazione che ho portato, il mio vincitore è il primo della lista, restituisco quindi il primo elemento.
GiocatoreT* DeterminaVincitore(ListaGiocatori Lista) 
{
	if (Lista == NULL)
		return NULL;
	else
		return &(Lista->info);
}

/*
3. Funzione di modifica di un Punteggio. La funzione da implementare deve avere la seguente struttura:
nome della funzione: ModificaPunteggio;
valore restituito: esito operazione (0: operazione fallita, 1: modifica effettuata con successo);
parametri: lista dei giocatori, codice, nuovo_punteggio.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare
la specifica.
*/

int ModificaPunteggio(ListaGiocatori Lista, char* Codice, int NuovoPunteggio) 
{
	if (Lista == NULL)
		return 0;
	ListaGiocatori L = Lista;
	while (L != NULL) 
	{
		if (strcmp(L->info.Codice, Codice) == 0)
			L->info.Punteggio = NuovoPunteggio;
		L = L->next;
	}
	return 1;
}

/*
4. CreazioneLISTASquadre: Crea la lista delle squadre a partire dalla lista dei GIOCATORI. Ogni elemento della
lista delle squadre contiene l’identificativo della squadra, la lista dei giocatori afferenti a quella squadra
e il punteggio della squadra. Se il giocatore non appartiene a nessuna squadra (valore campo $$$) non deve essere
preso in considerazione. Il punteggio è pari alla somma dei primi migliori tre elementi della squadra (la squadra
può contenere meno di tre elementi in questo caso verranno considerati tutti gli elementi per calcolare il punteggio
della squadra).
*/

ListaSquadre* CercaSquadra(ListaSquadre Squadre, char* Squadra) 
{
	if (Squadre == NULL)
		return NULL;
	ListaSquadre aux = Squadre;
	while (aux != NULL) 
	{
		if (strcmp(aux->Nome, Squadra) == 0)
			return &(aux);
		aux = aux->next;
	}
	return NULL;
}

int CreazioneLISTASquadre(ListaSquadre* Squadre, ListaGiocatori giocatori) 
{
	if (giocatori == NULL)
		return 0;
	ListaGiocatori ListaAux = giocatori;
	ListaSquadre* Aux2;
	while (ListaAux != NULL) 
	{
		if (strcmp(ListaAux->info.Squadra, "$$$") != 0)
		{
			Aux2 = CercaSquadra((*Squadre), ListaAux->info.Squadra);
			if (Aux2 != NULL)
			{
				(*Aux2)->PunteggioSquadra += ListaAux->info.Punteggio;
				if (!AggiungiNodoGiocatorePerPunteggio(&((*Aux2)->Elenco), ListaAux->info))
					return 0;
			}
			else
			{
				NodoSquadraT* Aux3 = (NodoSquadraT*)malloc(sizeof(NodoSquadraT));
				if (Aux3 == NULL)
					return 0;
				Aux3->Elenco = NULL;
				if (!AggiungiNodoGiocatorePerPunteggio(&(Aux3->Elenco), ListaAux->info))
					return 0;
				strcpy(Aux3->Nome, ListaAux->info.Squadra);
				Aux3->PunteggioSquadra = ListaAux->info.Punteggio;
				Aux3->next = (*Squadre);
				(*Squadre) = Aux3;
			}
		}
		ListaAux = ListaAux->next;
	}
	return 1;
}


/*
5. RicercaDelleSquadreNumerose: Funzione che, operando sulla lista delle squadre stampa i nomi delle squadre che
hanno presentato più di tre elementi.
*/

void RicercaDelleSquadreNumerose(ListaSquadre Squadre) 
{
	int n = 3;
	int cont;
	ListaGiocatori aux;
	while (Squadre != NULL) 
	{
		cont = 0;
		aux = Squadre->Elenco;
		while (aux != NULL) 
		{
			cont++;
			aux = aux->next;
		}
		if (cont > n) 
		{
			printf("%s\n", Squadre->Nome);
		}
		Squadre = Squadre->next;
	}
}

/*
6. StampaClassificaASquadre: Funzione che, operando sulla lista delle squadre stampa la classifica
*/

int RicercaMinimo(ListaSquadre* Vettore, int dim) 
{
	int pos = 0;
	for (int i = 1; i < dim; i++) 
	{
		if (Vettore[i]->PunteggioSquadra < Vettore[pos]->PunteggioSquadra) 
		{
			pos = i;
		}
	}
	return pos;
}

void Scambia(NodoSquadraT** Squadra1, NodoSquadraT** Squadra2) 
{
	NodoSquadraT K = {
		.Elenco = NULL,
		.Nome = "",
		.PunteggioSquadra = 0
	};
	strcpy(K.Nome, (*Squadra1)->Nome);
	K.PunteggioSquadra = (*Squadra1)->PunteggioSquadra;

	strcpy((*Squadra1)->Nome, (*Squadra2)->Nome);
	(*Squadra1)->PunteggioSquadra = (*Squadra2)->PunteggioSquadra;
	
	strcpy((*Squadra2)->Nome, K.Nome);
	(*Squadra2)->PunteggioSquadra = K.PunteggioSquadra;
}

void NaiveSort(ListaSquadre v[], int dim) 
{
	int k;
	for (int i = 0; i < dim; i++) 
	{
		k = RicercaMinimo(&v[i], dim - i) + i;
		Scambia(&v[i], &v[k]);
	}
}

void StampaClassificaSquadre(ListaSquadre squadre) 
{
	ListaSquadre* Vettore = NULL;
	int cont = 0;
	ListaSquadre Corrente = squadre;
	while (Corrente != NULL) 
	{
		cont++;
		Corrente = Corrente->next;
	}
	Vettore = (ListaSquadre*)malloc(sizeof(ListaSquadre) * cont);
	for (int i = 0; i < cont; i++) 
	{
		Vettore[i] = NULL;
	}
	Corrente = squadre;
	int index = 0;
	while (Corrente != NULL) 
	{
		Vettore[index] = Corrente;
		Vettore[index]->Elenco = NULL;
		index++;
		Corrente = Corrente->next;
	}
	NaiveSort(Vettore, cont);
	printf("RISULTATO CLASSIFICA:\n");
	int posizione = 1;
	for (int i = (cont-1); i >= 0; i--) 
	{
		printf("%d POSTO: %s %d\n", posizione, Vettore[i]->Nome, Vettore[i]->PunteggioSquadra);
		posizione++;
	}
}


int Menu()
{
	int scelta;
	printf("*******MENU********\n"
		"1. Carica dati da file.\n"
		"2. Determina il vincitore.\n"
		"3. Modifica il punteggio.\n"
		"4. Crea lista squadre.\n"
		"5. Ricerca squadre numerose.\n"
		"6. Stampa classifica squadre.\n"
		"7. Visualizza contenuto lista squadre.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

void VisualizzaGiocatori(ListaGiocatori giocatori) 
{
	while (giocatori != NULL) 
	{
		printf("%s %s %s %s %d\n", giocatori->info.Codice, giocatori->info.Cognome, giocatori->info.Nome, giocatori->info.Squadra, giocatori->info.Punteggio);
		giocatori = giocatori->next;
	}
}

void VisualizzaSquadre(ListaSquadre squadre) 
{
	while (squadre != NULL) 
	{
		printf("%s %d\nELENCO:\n", squadre->Nome, squadre->PunteggioSquadra);
		VisualizzaGiocatori(squadre->Elenco);
		printf("\n");
		squadre = squadre->next;
	}
}

void DisallocaListaGiocatori(ListaGiocatori* PLista) 
{
	ListaGiocatori aux;
	while ((*PLista) != NULL) 
	{
		aux = (*PLista);
		(*PLista) = (*PLista)->next;
		free(aux);
	}
}

void DisallocaListaSquadre(ListaSquadre* Squadre) 
{
	ListaGiocatori aux2;
	ListaSquadre aux1;
	while ((*Squadre) != NULL) 
	{
		DisallocaListaGiocatori(&((*Squadre)->Elenco));
		aux1 = (*Squadre);
		(*Squadre) = (*Squadre)->next;
		free(aux1);
	}
}

int main() 
{
	char NomeFile[128];
	char Codice[7];
	int NuovoPunteggio;
	ListaGiocatori giocatori = NULL;
	ListaSquadre squadre = NULL;
	GiocatoreT* Vincitore;
	int scelta;
	int n;
	do 
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			n = CaricaGIOCATORI(&giocatori, NomeFile);
			if (n != 0) 
			{
				printf("Sono stati caricati %d giocatori.\n", n);
				VisualizzaGiocatori(giocatori);
			}
			break;
		case 2:
			Vincitore = DeterminaVincitore(giocatori);
			printf("Il vincitore e' %s %s con punteggio %d.\n", (*Vincitore).Nome, (*Vincitore).Cognome, (*Vincitore).Punteggio);
			break;
		case 3:
			printf("Inserisci il codice del giocatore: ");
			scanf("%s", Codice);
			printf("Inserisci il nuovo punteggio: ");
			scanf("%d", &NuovoPunteggio);
			n = ModificaPunteggio(giocatori, Codice, NuovoPunteggio);
			if (n != 0)
			{
				printf("Punteggio modificato con successo.\n");
				VisualizzaGiocatori(giocatori);
			}
			break;
		case 4:
			n = CreazioneLISTASquadre(&squadre, giocatori);
			if (n != 0)
				printf("Creazione squadre avvenuta con successo.\n");
			break;
		case 5:
			RicercaDelleSquadreNumerose(squadre);
			break;
		case 6:
			StampaClassificaSquadre(squadre);
			break;
		case 7:
			VisualizzaSquadre(squadre);
			break;
		}
	} while (scelta != 0);
	DisallocaListaGiocatori(&giocatori);
	DisallocaListaSquadre(&squadre);
}