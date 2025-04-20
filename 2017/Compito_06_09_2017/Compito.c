/*
Implementare una applicazione console in linguaggio ANSI C per la gestione delle comande in un fastfood. Le informazioni di
ciascuna comanda sono memorizzate in un file (specificato nel seguito) e caricate in una lista di comande ordinata in base all’orario
di acquisizione della comanda. Come ipotesi semplificativa si assuma che una comanda possa fare riferimento ad un unico menù del
fastfood. In un momento successivo, l’applicazione dovrà organizzare le informazioni di tali comande in una lista di menu in cui ogni
elemento della lista contiene, oltre all’identificativo del menu, anche l’elenco delle comande relative a quel menu.
Specifica della struttura dati:
Comanda:
1. Codice (codice univoco della comanda: stringa di 7 caratteri)
2. Orario (hh:mm nel formaro 24 ore)
3. Menu (codice del menu: intero)
4. Takeaway (da portare via o consumare sul posto: intero)
Menu:
1. Menu (codice del menu: intero)
2. Comande (elenco delle comande relative a quel menu: lista di Comanda)
Elenco delle operazioni/funzioni che devono essere implementate:
1. Funzione di caricamento da file di testo degli articoli nella lista delle comande. La lista delle comande deve essere mantenuta
ordinata in base all’orario della comanda (dalla meno recente alla più recente). La funzione da implementare deve avere la
seguente struttura:
nome della funzione: CaricaComanda;
valore restituito: numero di comande caricate;
parametri: nome del file, lista delle comande.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
2. Funzione di modifica del menu di una determinata comanda. La funzione da implementare deve avere la seguente struttura:
nome della funzione: ModificaComanda;
valore restituito: esito operazione (0: operazione fallita, 1: modifica effettuata con successo);
parametri: lista delle comande, codice comanda, nuovo menu.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
3. Funzione di eliminazione di una comanda dalla lista. La funzione da implementare deve avere la seguente struttura:
nome della funzione: EliminaComanda;
valore restituito: esito operazione (0: operazione fallita, 1: eliminazione effettuata con successo);
parametri: lista delle comande, codice della comanda da eliminare.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
4. SpostaComandeInListaMenu: Sposta (cioè copia ed elimina le comande dalla lista di comande) le informazioni contenute
nella lista delle comande nella lista dei menu, facendo in modo che ogni nodo della lista dei menu contenga l’elenco delle
comande riferite a quel menu. Lo studente scelga la struttura della funzione, il tipo dei dati ed i meccanismi di passaggio dei
parametri più opportuni per rispettare la specifica.
5. PercentualeDiComandeTakeAway: Funzione che, operando sulla lista dei menu e fornito come parametro di ingresso un
menu, calcoli e restituisca la percentuale di comande di quel menù takeaway.
6. VisualizzaComandeInAttesa: Funzione che, operando sulla lista dei generi alimentari e fornito come parametro di ingresso
l’orario attuale, visualizzi tutte le comande con un orario anteriore all’orario attuale di 30 minuti. La funzione deve inoltre
restituire il numero di comande visualizzate.
7. Funzione che visualizza il contenuto dell’intera lista di menu.
8. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni implementate ed
eventualmente di inserire i parametri necessari ed eseguire le operazioni richieste.

Struttura del file degli articoli

Le informazioni nel file per ciascuna comanda si trovano distribuite su una riga:

Codice Orario Menu Takeaway

Esempio di file:
0000001 18:00 3 1
0000002 18:13 2 0
0000003 18:25 1 0
0000004 18:40 1 1
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ComandaS 
{
	char Codice[8];
	char Orario[6];
	int Menu;
	int TakeAway;
} ComandaT;

typedef struct NodoComandaS 
{
	ComandaT info;
	struct NodoComandaS* next;
} NodoComandaT, * ListaComande;

typedef struct NodoMenuS 
{
	int Menu;
	ListaComande Comande;
	struct NodoMenuS* Next;
} NodoMenuT, * ListaMenu;

int InserisciNodoComanda(ListaComande* Comande, ComandaT c) 
{
	NodoComandaT* aux = (NodoComandaT*)malloc(sizeof(NodoComandaT));
	if (aux == NULL)
		return 0;
	aux->info = c;
	aux->next = (*Comande);
	(*Comande) = aux;
	return 1;
}

/*
1. Funzione di caricamento da file di testo degli articoli nella lista delle comande.
La lista delle comande deve essere mantenuta
ordinata in base all’orario della comanda (dalla meno recente alla più recente).
La funzione da implementare deve avere la
seguente struttura:
nome della funzione: CaricaComanda;
valore restituito: numero di comande caricate;
parametri: nome del file, lista delle comande.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/

int CaricaComanda(char* NomeFile, ListaComande* Comande) 
{
	int Num = 0;
	FILE* fp = fopen(NomeFile, "r");
	if (fp == NULL)
		return 0;
	ComandaT c;
	while(fscanf(fp, "%s%s%d%d", c.Codice, c.Orario, &c.Menu, &c.TakeAway) == 4)
	{
		if (!InserisciNodoComanda(Comande, c))
			return 0;
		else
			Num++;
	}
	return Num;
}

/*
2. Funzione di modifica del menu di una determinata comanda. La funzione da implementare deve avere la seguente struttura:
nome della funzione: ModificaComanda;
valore restituito: esito operazione (0: operazione fallita, 1: modifica effettuata con successo);
parametri: lista delle comande, codice comanda, nuovo menu.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/

int ModificaComanda(ListaComande Lista, char* CodiceComanda, int NuovoMenu) 
{
	if (Lista == NULL)
		return 0;
	while (Lista != NULL) 
	{
		if (strcmp(Lista->info.Codice, CodiceComanda) == 0) 
		{
			Lista->info.Menu = NuovoMenu;
		}
		Lista = Lista->next;
	}
	return 1;
}

/*
3. Funzione di eliminazione di una comanda dalla lista. La funzione da implementare deve avere la seguente struttura:
nome della funzione: EliminaComanda;
valore restituito: esito operazione (0: operazione fallita, 1: eliminazione effettuata con successo);
parametri: lista delle comande, codice della comanda da eliminare.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/

int EliminaComanda(ListaComande* PListaComande, char* CodiceComanda) 
{
	if ((*PListaComande) == NULL)
		return 0;
	NodoComandaT* aux;
	if (strcmp((*PListaComande)->info.Codice, CodiceComanda) == 0) 
	{
		aux = (*PListaComande);
		(*PListaComande) = (*PListaComande)->next;
		free(aux);
		return 1;
	}
	else 
	{
		return EliminaComanda(&(*PListaComande)->next, CodiceComanda);
	}
}

/*
4. SpostaComandeInListaMenu: Sposta (cioè copia ed elimina le comande dalla lista di comande) le informazioni contenute
nella lista delle comande nella lista dei menu, facendo in modo che ogni nodo della lista dei menu contenga l’elenco delle
comande riferite a quel menu. Lo studente scelga la struttura della funzione, il tipo dei dati ed i meccanismi di passaggio dei
parametri più opportuni per rispettare la specifica.
*/

int SpostaComandeInListaMenu(ListaComande Comande, ListaMenu* ListaMenu) 
{
	ListaComande aux = Comande;
	NodoMenuT* Corrente;
	while (aux != NULL) 
	{
		Corrente = (*ListaMenu);
		int trovato = 0;
		while (Corrente != NULL) 
		{
			if (Corrente->Menu == aux->info.Menu) 
			{
				trovato = 1;
				break;
			}
			Corrente = Corrente->Next;
		}
		if (trovato == 1) 
		{
			InserisciNodoComanda(&(Corrente->Comande), aux->info);
		}
		else 
		{
			NodoMenuT* Nodo = (NodoMenuT*)malloc(sizeof(NodoMenuT));
			if (Nodo == NULL)
				return 0;
			Nodo->Menu = 0;
			Nodo->Menu = aux->info.Menu;
			Nodo->Comande = NULL;
			InserisciNodoComanda(&(Nodo->Comande), aux->info);
			Nodo->Next = (*ListaMenu);
			(*ListaMenu) = Nodo;
		}
		aux = aux->next;
	}
	return 1;
}

/*
5. PercentualeDiComandeTakeAway: Funzione che, operando sulla lista dei menu e fornito come parametro di ingresso un
menu, calcoli e restituisca la percentuale di comande di quel menù takeaway.
*/

float PercentualeDiComandeTakeAway(ListaMenu Menu, int CodiceMenu)
{
	int cont = 0;
	int tot = 0;
	ListaComande aux;
	while (Menu != NULL) 
	{
		if (Menu->Menu == CodiceMenu) 
		{
			aux = Menu->Comande;
			while (aux != NULL) 
			{
				tot++;
				if (aux->info.TakeAway == 1) 
				{
					cont++;
				}
				aux = aux->next;
			}
		}
		Menu = Menu->Next;
	}
	float Percentuale = ((float)(cont) / (float)(tot)) * 100.0F;
	return Percentuale;
}

/*
6. VisualizzaComandeInAttesa: Funzione che, operando sulla lista dei generi alimentari e fornito come parametro di ingresso
l’orario attuale, visualizzi tutte le comande con un orario anteriore all’orario attuale di 30 minuti. La funzione deve inoltre
restituire il numero di comande visualizzate.
*/

int DifferenzaOrario(char* OrarioAttuale, char* OrarioVecchio) 
{
	char OraA[3];
	char OraV[3];
	strncpy(OraA, OrarioAttuale, 2);
	OraA[2] = "\0";
	strncpy(OraV, OrarioVecchio, 2);
	OraV[2] = "\0";
	int differenzaOra = (atoi(OraA) - atoi(OraV))*60;
	char MinutoA[3];
	char MinutoV[3];
	strncpy(MinutoA, OrarioAttuale + 3, 2);
	MinutoA[2] = "\0";
	strncpy(MinutoV, OrarioVecchio + 3, 2);
	MinutoV[2] = "\0";
	int difftot = differenzaOra + (atoi(MinutoA) - atoi(MinutoV));
	return difftot;
}

int VisualizzaComandeInAttesa(ListaMenu Menu, char * NuovoOrario)
{
	int cont = 0;
	if (Menu == NULL)
		return 0;
	int diffminuti;
	ListaComande aux;
	while (Menu != NULL) 
	{
		aux = Menu->Comande;
		while (aux != NULL) 
		{
			diffminuti = DifferenzaOrario(NuovoOrario, aux->info.Orario);
			if (diffminuti <= 30) 
			{
				cont++;
				printf("%s %s %d %d\n", aux->info.Codice, aux->info.Orario, aux->info.Menu, aux->info.TakeAway);
			}
			aux = aux->next;
		}
		Menu = Menu->Next;
	}
	return cont;
}

/*
7. Funzione che visualizza il contenuto dell’intera lista di menu.
*/

void VisualizzaLista(ListaComande lista) 
{
	while (lista != NULL) 
	{
		printf("%s %s %d %d\n", lista->info.Codice, lista->info.Orario, lista->info.Menu, lista->info.TakeAway);
		lista = lista->next;
	}
}

void VisualizzaMenu(ListaMenu menu) 
{
	while (menu != NULL) 
	{
		printf("CODICE MENU: %d\nELENCO:\n", menu->Menu);
		VisualizzaLista(menu->Comande);
		printf("\n");
		menu = menu->Next;
	}
}

/*
8. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni implementate ed
eventualmente di inserire i parametri necessari ed eseguire le operazioni richieste.
*/

int Opzioni() 
{
	int scelta;
	printf("******** MENU ********\n"
		"1. Carica dati da file.\n"
		"2. Modifica comanda.\n"
		"3. Elimina comanda.\n"
		"4. Sposta comande in lista menu.\n"
		"5. Percentuale comande sul menu takeaway.\n"
		"6. Visualizza comande in attesa.\n"
		"7. Visualizza lista menu.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

int main() 
{
	int scelta;
	char NomeFile[64];
	char CodiceComanda[8];
	int NuovoMenu;
	int CodiceMenu;
	int NumComande;
	char OrarioAttuale[6];
	ListaComande Comande = NULL;
	ListaMenu Menu = NULL;
	int NumElementicaricati;
	float Percentuale;
	int esito;
	do 
	{
		scelta = Opzioni();
		switch (scelta)
		{
		case 1:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			NumElementicaricati = CaricaComanda(NomeFile, &Comande);
			if (NumElementicaricati != 0)
				printf("Sono stati caricati %d elementi.\n", NumElementicaricati);
			break;
		case 2:
			printf("Inserisci il codice della Comanda: ");
			scanf("%s", CodiceComanda);
			printf("Inserisci il nuovo Menu: ");
			scanf("%d", &NuovoMenu);
			esito = ModificaComanda(Comande, CodiceComanda, NuovoMenu);
			if (esito == 1)
				printf("Comanda modificata correttamente.\n");
			break;
		case 3:
			printf("Inserisci il codice della Comanda: ");
			scanf("%s", CodiceComanda);
			esito = EliminaComanda(&Comande, CodiceComanda);
			if (esito == 1)
				printf("Comanda eliminata correttamente.\n");
			else 
			{
				printf("Comanda non trovata.\n");
			}
			break;
		case 4:
			esito = SpostaComandeInListaMenu(Comande, &Menu);
			if (esito == 1)
				printf("Operazione eseguita correttamente.\n");
			break;
		case 5:
			printf("Inserisci il codice del menu: ");
			scanf("%d", &CodiceMenu);
			Percentuale = PercentualeDiComandeTakeAway(Menu, CodiceMenu);
			printf("La percentuale e' di %.3f.\n", Percentuale);
			break;
		case 6:
			printf("Inserisci l'orario attuale: ");
			scanf("%s", OrarioAttuale);
			NumComande = VisualizzaComandeInAttesa(Menu, OrarioAttuale);
			if(NumComande != 0)
				printf("Sono state visualizzate %d comande.\n", NumComande);
			break;
		case 7:
			VisualizzaMenu(Menu);
			break;
		}
	} while (scelta != 0);
}