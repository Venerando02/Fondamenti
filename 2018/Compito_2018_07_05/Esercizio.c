/*
Implementare un’applicazione console in linguaggio ANSI C per la gestione di una ludoteca adibita a feste di compleanno. Una festa di compleanno è caratterizzata dal nome del 
festeggiato, dalla data in cui si tiene la festa, dal numero di invitati, e da un menu festa. I menu festa sono tre ed hanno rispettivamente un costo di 5 €, 8 € e 10 € per invitato.
Le informazioni relative alle feste sono memorizzate in un file di testo (un esempio di file è riportato alla fine del testo) e vengono caricate in una lista di feste. Successivamente,
a partire da tale lista, viene costruita un’altra lista in cui ogni nodo rappresenta uno specifico menu festa. Per ogni menu festa, sono contenuti il numero totale di feste e 
l’elenco delle feste per quello specifico menu festa.
Specifica della struttura dati
Festa
• Festeggiato (stringa di 16 caratteri utili senza spazi)
• Data (stringa di 8 caratteri utili nel formato aaaammgg)
• Numero di invitati (intero)
• Menu (intero)
MenuFesta
• Menu (intero)
• Numero di feste (intero)
• Feste (lista di Festa)
Elenco delle operazioni/funzioni che devono essere implementate
(Lo studente noti che il non rispetto delle specifiche nei quesiti 1 e 2, quindi la scelta di un nome della funzione diverso, di parametri differenti o di valori di ritorno 
differenti sono considerati errori gravi a prescindere del fatto che la funzione svolga quanto richiesto).
1. Funzione di caricamento da file di testo delle feste nella lista delle feste. La funzione da implementare deve avere la seguente struttura:
 nome della funzione: CaricaFeste
 valore restituito: numero di feste caricate
 parametri: nome del file, lista di feste
2. Funzione di ricerca della festa più costosa. La funzione da implementare deve avere la seguente struttura:
 nome della funzione: FestaPiuCostosa
 valore restituito: 0 se la lista delle feste è vuota, 1 altrimenti
 parametri: lista di feste, festa più costosa (NB: festa più costosa è un parametro - contenente tutti i dati della festa - di uscita che la funzione deve produrre e non visualizzare,
in caso di più feste con lo stesso costo restituire solo una di tali feste).
3. CreazioneListaMenuFesta: Crea la lista dei menu festa a partire dalla lista delle feste. Ogni elemento della lista dei menu festa contiene l’identificativo del menu, il numero di 
feste e l'elenco delle feste con quello specifico menu.
4. VisualizzaTutto: Visualizza, per ogni menu festa, l’elenco delle feste con quel menu.
5. MaxMinInvitati: Dato un menu ed una data (parametri di ingresso della funzione), fornisce (come parametri di uscita) la festa con il maggior numero di invitati e quella con il 
minor numero di inviati, comunque con data posteriore a quella fornita attraverso parametro (nel caso esistano più feste che rispondono ai requisiti minimi o massimi se ne deve
restituire una sola). La funzione deve restituire (return) 0 nel caso in cui non ci sono feste con quel menu ed 1 altrimenti.
6. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni implementate ed eventualmente di inserire i parametri necessari ed eseguire
le operazioni richieste.
Esempio dei dati nel file di ingresso
Alberto 20180831 15 2
Valentina 20180615 10 1
Giacomo 20180724 20 1
Annalisa 20180913 12 3
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct FestaS 
{
	char Festeggiato[17];
	char Data[9];
	int NumeroInvitati;
	int Menu;
} FestaT;

typedef struct NodoFestaS 
{
	FestaT info;
	struct NodoFestaS* next;
} NodoFestaT, *ListaFesta;

typedef struct NodoMenuFestaS 
{
	ListaFesta Feste;
	int Menu;
	int NumeroFeste;
} NodoMenu;

int InserisciNodoFesta(ListaFesta* PListaFeste, FestaT f) 
{
	NodoFestaT* aux = (NodoFestaT*)malloc(sizeof(NodoFestaT));
	if (aux == NULL)
		return 0;
	aux->info = f;
	aux->next = (*PListaFeste);
	(*PListaFeste) = aux;
	return 1;
}

/*
1. Funzione di caricamento da file di testo delle feste nella lista delle feste. La funzione da implementare deve avere la seguente struttura:
nome della funzione: CaricaFeste
valore restituito: numero di feste caricate
parametri: nome del file, lista di feste
*/

int TraduciCostoMenu(int Menu) 
{
	if (Menu == 1)
		return 5;
	else if (Menu == 2)
		return 8;
	else if(Menu == 3)
		return 10;
}

int CaricaFeste(ListaFesta* PListaFeste, char* NomeFile) 
{
	int num = 0;
	FestaT f;
	FILE* fp = fopen(NomeFile, "r");
	if (fp == NULL)
		return 0;
	while (fscanf(fp, "%s%s%d%d", f.Festeggiato, f.Data, &f.NumeroInvitati, &f.Menu) == 4) 
	{
		if (!InserisciNodoFesta(PListaFeste, f))
			return 0;
		else
			num++;
	}
	return num;
}

/*
2. Funzione di ricerca della festa più costosa. La funzione da implementare deve avere la seguente struttura:
 nome della funzione: FestaPiuCostosa
 valore restituito: 0 se la lista delle feste è vuota, 1 altrimenti
 parametri: lista di feste, festa più costosa (NB: festa più costosa è un parametro - contenente tutti i dati della festa - di uscita che la funzione deve
produrre e non visualizzare,
in caso di più feste con lo stesso costo restituire solo una di tali feste)
*/

int FestaPiuCostosa(ListaFesta ListaFesta, FestaT * FestaUscita) 
{
	// Inizializzazione 
	(*FestaUscita).Menu = 0;
	(*FestaUscita).NumeroInvitati = 0;
	strcpy((*FestaUscita).Festeggiato, "");
	strcpy((*FestaUscita).Data, "");
	// Controllo se la lista non è vuota
	if (ListaFesta == NULL)
		return 0;
	int costo;
	int singolocostofesta;
	int max = 0;
	while (ListaFesta != NULL) 
	{
		costo = 0;
		singolocostofesta = TraduciCostoMenu(ListaFesta->info.Menu);
		costo = singolocostofesta * ListaFesta->info.NumeroInvitati;
		if (costo > max) 
		{
			max = costo;
			(*FestaUscita).Menu = ListaFesta->info.Menu;
			(*FestaUscita).NumeroInvitati = ListaFesta->info.NumeroInvitati;
			strcpy((*FestaUscita).Data, ListaFesta->info.Data);
			strcpy((*FestaUscita).Festeggiato, ListaFesta->info.Festeggiato);
		}
		ListaFesta = ListaFesta->next;
	}
	return 1;
}

/*
3. CreazioneListaMenuFesta: Crea la lista dei menu festa a partire dalla lista delle feste. Ogni elemento della lista dei menu festa contiene l’identificativo del menu, il numero di
feste e l'elenco delle feste con quello specifico menu.
*/

int CreazioneListaMenuFesta(NodoMenu ListaMenu[], ListaFesta ListaFeste)
{
	ListaFesta aux = ListaFeste;
	while (aux != NULL) 
	{
		ListaMenu[(aux->info.Menu-1)].NumeroFeste = 0;
		ListaMenu[(aux->info.Menu-1)].Menu = aux->info.Menu;
		if (!InserisciNodoFesta(&(ListaMenu[(aux->info.Menu-1)].Feste), aux->info))
			return 0;
		else
			ListaMenu[(aux->info.Menu-1)].NumeroFeste++;
		aux = aux->next;
	}
	return 1;
}

int Menu() 
{
	int scelta;
	printf("******** MENU ********\n"
		"1. Carica dati da file.\n"
		"2. Trova festa piu' costosa.\n"
		"3. Crea lista menu festa.\n"
		"4. Visualizza lista menu.\n"
		"5. Indicare massimo e minimo numero di invitati.\n"
		"6. Disalloca Lista e Vettore.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

/*
5. MaxMinInvitati: Dato un menu ed una data (parametri di ingresso della funzione), fornisce (come parametri di uscita) la festa con il maggior numero di invitati e quella con il
minor numero di inviati, comunque con data posteriore a quella fornita attraverso parametro (nel caso esistano più feste che rispondono ai requisiti minimi o massimi se ne deve
restituire una sola). La funzione deve restituire (return) 0 nel caso in cui non ci sono feste con quel menu ed 1 altrimenti.
*/

int MaxMinInvitati(NodoMenu VMenu[], int Menu, char* Data, FestaT* FestaMax, FestaT* FestaMin) 
{
	NodoMenu v = VMenu[Menu];
	int max = v.Feste->info.NumeroInvitati;
	int min = v.Feste->info.NumeroInvitati;
	
	strcpy((*FestaMax).Festeggiato, "");
	strcpy((*FestaMax).Data, "");
	(*FestaMax).Menu = 0;
	(*FestaMax).NumeroInvitati = 0;
	
	strcpy((*FestaMin).Festeggiato, "");
	strcpy((*FestaMin).Data, "");
	(*FestaMin).Menu = 0;
	(*FestaMin).NumeroInvitati = 0;

	if (v.Feste == NULL)
		return 0;

	while (v.Feste != NULL) 
	{
		if (strcmp(v.Feste->info.Data, Data) >= 0) 
		{
			if (v.Feste->info.NumeroInvitati > max) 
			{
				max = v.Feste->info.NumeroInvitati;
				strcpy((*FestaMax).Festeggiato, v.Feste->info.Festeggiato);
				strcpy((*FestaMax).Data, v.Feste->info.Data);
				(*FestaMax).Menu = v.Feste->info.Menu;
				(*FestaMax).NumeroInvitati = v.Feste->info.NumeroInvitati;
			}
			else if(v.Feste->info.NumeroInvitati < min) 
			{
				min = v.Feste->info.NumeroInvitati;
				strcpy((*FestaMin).Festeggiato, v.Feste->info.Festeggiato);
				strcpy((*FestaMin).Data, v.Feste->info.Data);
				(*FestaMin).Menu = v.Feste->info.Menu;
				(*FestaMin).NumeroInvitati = v.Feste->info.NumeroInvitati;
			}
		}
		else 
		{
			return 0;
		}
		v.Feste = v.Feste->next;
	}

	return 1;
}


void VisualizzaListaFeste(ListaFesta ListaFeste) 
{
	while (ListaFeste != NULL) 
	{
		printf("%s %s %d\n", ListaFeste->info.Festeggiato, ListaFeste->info.Data, ListaFeste->info.NumeroInvitati);
		ListaFeste = ListaFeste->next;
	}
}

void VisualizzaVettore(NodoMenu v[], int dim) 
{
	for (int i = 0; i < dim; i++) 
	{
		printf("MENU: %d // NUMERO FESTE: %d // FESTE:\n", (v[i].Menu), v[i].NumeroFeste);
		VisualizzaListaFeste(v[i].Feste);
	}
}

void DisallocaLista(ListaFesta lista)
{
	ListaFesta aux;
	while (lista != NULL) 
	{
		aux = lista;
		lista = lista->next;
		free(aux);
	}
}

int main() 
{
	int scelta;
	char NomeFile[64];
	ListaFesta ListaFeste = NULL;
	NodoMenu VettoreListe[3] = { NULL };
	int MenuDaInserire;
	char DataDaInserire[9];
	FestaT FestaCostosa;
	FestaT MaxFesta;
	FestaT MinFesta;
	int esito;
	int NumFesteCaricate;
	do 
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			NumFesteCaricate = CaricaFeste(&ListaFeste, NomeFile);
			if (NumFesteCaricate != 0)
				printf("Sono state caricate %d feste.\n", NumFesteCaricate);
			break;
		case 2:
			esito = FestaPiuCostosa(ListaFeste, &FestaCostosa);
			if (esito == 1)
				printf("La festa piu' costosa e' di %s.\n", FestaCostosa.Festeggiato);
			break;
		case 3:
			esito = CreazioneListaMenuFesta(VettoreListe, ListaFeste);
			if (esito == 1)
				VisualizzaVettore(VettoreListe, 3);
			break;
		case 4:
			VisualizzaVettore(VettoreListe, 3);
			break;
		case 5:
			printf("Inserisci Menu: ");
			scanf("%d", &MenuDaInserire);
			printf("Inserisci una data: ");
			scanf("%s", DataDaInserire);
			esito = MaxMinInvitati(VettoreListe, MenuDaInserire, DataDaInserire, &MaxFesta, &MinFesta);
			if (esito == 1)
				printf("La festa con il maggior numero di invitati e' di %s mentre quella con il minimo e' %s.\n", MaxFesta.Festeggiato, MinFesta.Festeggiato);
			else
				printf("Non ci sono feste in quella data o si e' verificato un errore.\n");
			break;
		case 6:
			DisallocaLista(ListaFeste);
			for (int i = 0; i < 3; i++) 
			{
				DisallocaLista(VettoreListe[i].Feste);
			}
			break;
		}
	}while(scelta != 0);
}