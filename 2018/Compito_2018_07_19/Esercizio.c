/*
Implementare una applicazione console in linguaggio ANSI C per la gestione di un servizio di noleggio biciclette.
L’applicazione ha il compito di gestire il parco biciclette e i relativi incassi. Ogni bicicletta è univocamente identificata
dal numero di serie ed è caratterizzata dal tipo di telaio, dalle dimensioni e dal tipo. Il programma carica inizialmente 
l’archivio dei dati da un file di testo (un esempio è fornito nel seguito) in una lista semplice (lista_noleggi) e successivamente
copia il contenuto in una lista organizzata in base alle biciclette (lista_bici) in cui ogni nodo contiene i dati di ogni bicicletta
ed una lista (secondaria) che contiene tutti i dati relativi ai noleggi calcolati in base ai costi orari.
Specifica della struttura dati:

Noleggi, (elemento della lista_noleggi):
1 numero_serie (stringa di 12 caratteri utili)
2 tipo (“city”,”mountain”,”fat”,”gravel”,”elettrica”)
3 dimensioni (“small”,”medium”,”large”)
4 durata (durata, espressa in ore, di un singolo noleggio)
5 Costo (costo in euro, questo campo è calcolato al momento della creazione della lista secondaria)

Elemento della lista_bici:
1 numero_serie (stringa di 12 caratteri utili)
2 tipo (“city”,”mountain”,”fat”,”gravel”,”elettrica”)
3 dimensioni (“small”,”medium”,”large”)
4 totale_guadagno (valore espresso in euro che rappresenta quanto ricavato dal noleggio di questa bicicletta)
5 elenco dei noleggi (lista dei noleggi di questa bicicletta)

Costo orario per tipo di bici necessario per il calcolo del costo del noleggio poiché il costo non è presente nel file:
1 city: 10 euro/ora
2 mountain: 12 euro/ora
3 fat 12 euro/ora
4 gravel 14 euro/ora
5 elettrica 20 euro/ora

Elenco delle operazioni/funzioni che devono essere implementate:
(Lo studente noti che il non rispetto delle specifiche nei quesiti 1 e 2, quindi la scelta di un nome della funzione diverso, di parametri differenti
o di valori di ritorno differenti sono considerati errori gravi a prescindere del fatto che la funzione svolga quanto richiesto).
1. Funzione di caricamento da file di testo dei dati contenuti nel file. La funzione da implementare deve rispettare la seguente specifica:
nome della funzione: carica_noleggi;
valore restituito: numero di elementi caricati
parametri: nome del file, lista dei noleggi
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica
2. Funzione di modifica del tipo di bicicletta (devono essere aggiornate tutte le istanze della stessa bicicletta, cioè tutte quelle 
con lo stesso numero di serie). Specifica della funzione:
nome della funzione: modifica_bici;
valore restituito: numero di istanze modificate;
parametri: lista_info, numero di serie, nuovo tipo di bicicletta, numero di istanze modificate.
(NB: il numero di istanze modificate è un parametro di uscita che la funzione deve produrre e non visualizzare).
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
3. Funzione di creazione della lista di liste: Crea la lista delle biciclette (lista_biciclette) a partire dalla lista_noleggi. 
Ogni elemento della lista delle biciclette contiene gli attributi della bicicletta oltre al campo totale guadagno che deve essere
calcolato in base al numero totale di ore di noleggio e alla tabella di costo orario fornita). Nota che una bicicletta potrbbe non 
essere mai stata noleggiata, quindi è possibile trovare il valore numero di ore pari a 0 (zero).
4. Ricerca della bici con il guadagno maggiore: Funzione che, operando sulla lista delle bicicletta restituisce tutte
le informazioni della bicicletta con il valore massimo di totale_guadagno;
5. Funzione che visualizza il contenuto dell’intera lista_bici
6. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni implementate ed eventualmente 
di inserire i parametri necessari ad eseguire le operazioni richieste.
Struttura del file dei giocatori

Le informazioni nel file per ciascun dato si trovano distribuite su una riga:
Numero di Serie tipo dimensioni durata

Esempio di file:
C433 city medium 2
G0001 gravel large 8
C433 city medium 4
MB01 mountain small 6
E045 elettrica medium 3
MB01 mountain small 2
G0001 gravel large 18
G0011 gravel medium 0
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BiciclettaS 
{
	char NumeroSerie[13];
	char Tipo[32];
	char Dimensioni[32];
	int Durata;
	int Costo;
} BiciclettaT;

typedef struct NodoNoleggioS 
{
	BiciclettaT info;
	struct NodoNoleggioS* next;
} NodoNoleggioT, *ListaNoleggi;

typedef struct NodoBiciS 
{
	ListaNoleggi ElencoNoleggi;
	int TotaleGuadagno;
	char NumeroSerie[13];
	char Tipo[32];
	char Dimensioni[32];
	struct NodoBiciS* next;
} NodoBiciT, * ListaBici;

int InserisciNodoNoleggio(ListaNoleggi* PLista, BiciclettaT B) 
{
	NodoNoleggioT* aux = (NodoNoleggioT*)malloc(sizeof(NodoNoleggioT));
	if (aux == NULL)
		return 0;
	aux->info = B;
	aux->next = (*PLista);
	(*PLista) = aux;
	return 1;
}

/*
1. Funzione di caricamento da file di testo dei dati contenuti nel file. La funzione da implementare deve rispettare la seguente specifica:
nome della funzione: carica_noleggi;
valore restituito: numero di elementi caricati
parametri: nome del file, lista dei noleggi
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica
*/

int ConvertiTipoInDenaro(char* Tipo) 
{
	if (strcmp(Tipo, "city") == 0)
		return 10;
	else if (strcmp(Tipo, "mountain") == 0)
		return 12;
	else if (strcmp(Tipo, "fat") == 0)
		return 12;
	else if (strcmp(Tipo, "gravel") == 0)
		return 14;
	else if (strcmp(Tipo, "elettrica") == 0)
		return 20;
}

int Carica_Noleggi(ListaNoleggi* PLista, char* NomeFile) 
{
	int n = 0;
	FILE* fp = fopen(NomeFile, "r");
	if (fp == NULL)
		return 0;
	int costoSingolo;
	int CostoTot;
	BiciclettaT B;
	while (fscanf(fp, "%s%s%s%d", B.NumeroSerie, B.Tipo, B.Dimensioni, &B.Durata) == 4) 
	{
		costoSingolo = ConvertiTipoInDenaro(B.Tipo);
		CostoTot = costoSingolo * B.Durata;
		B.Costo = CostoTot;
		if (!InserisciNodoNoleggio(PLista, B))
			return 0;
		else
			n++;
	}
	fclose(fp);
	return n;
}

int Menu() 
{
	int scelta;
	printf("******** MENU ********\n"
		"1. Carica dati da file.\n"
		"2. Modifica il tipo della bicicletta.\n"
		"3. Crea lista delle biciclette.\n"
		"4. Bici con guadagno maggiore.\n"
		"5. Visualizza contenuto.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

/*
2. Funzione di modifica del tipo di bicicletta (devono essere aggiornate tutte le istanze della stessa bicicletta, cioè tutte quelle
con lo stesso numero di serie). Specifica della funzione:
nome della funzione: modifica_bici;
valore restituito: numero di istanze modificate;
parametri: lista_info, numero di serie, nuovo tipo di bicicletta, numero di istanze modificate.
(NB: il numero di istanze modificate è un parametro di uscita che la funzione deve produrre e non visualizzare).
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/

int ModificaTipoBicicletta(ListaNoleggi Noleggi, char* NumeroSerie, char* NuovoTipo, int NumeroIstanze) 
{
	NumeroIstanze = 0;
	while (Noleggi != NULL) 
	{
		if (strcmp(Noleggi->info.NumeroSerie, NumeroSerie) == 0) 
		{
			strcpy(Noleggi->info.Tipo, NuovoTipo);
			NumeroIstanze++;
		}
		Noleggi = Noleggi->next;
	}
	return NumeroIstanze;
}

/*
3. Funzione di creazione della lista di liste: Crea la lista delle biciclette (lista_biciclette) a partire dalla lista_noleggi.
Ogni elemento della lista delle biciclette contiene gli attributi della bicicletta oltre al campo totale guadagno che deve essere
calcolato in base al numero totale di ore di noleggio e alla tabella di costo orario fornita). Nota che una bicicletta potrbbe non
essere mai stata noleggiata, quindi è possibile trovare il valore numero di ore pari a 0 (zero).
*/

int CreaListaBiciclette(ListaBici* PListaBiciclette, ListaNoleggi Noleggi) 
{
	ListaNoleggi N = Noleggi;
	ListaBici Corrente = NULL;
	while (N != NULL) 
	{
		Corrente = (*PListaBiciclette);
		int trovato = 0;
		while ((Corrente != NULL)) 
		{
			if (strcmp(Corrente->NumeroSerie, N->info.NumeroSerie) == 0) 
			{
				trovato = 1;
				break;
			}
			Corrente = Corrente->next;
		}
		if (trovato == 1) 
		{
			Corrente->TotaleGuadagno += N->info.Costo;
			if(!InserisciNodoNoleggio(&(Corrente->ElencoNoleggi), N->info))
				return 0;
		}
		else
		{
			NodoBiciT* aux = (NodoBiciT*)malloc(sizeof(NodoBiciT));
			if (aux == NULL)
				return 0;
			strcpy(aux->NumeroSerie, N->info.NumeroSerie);
			strcpy(aux->Tipo, N->info.Tipo);
			strcpy(aux->Dimensioni, N->info.Dimensioni);
			aux->ElencoNoleggi = NULL;
			if (!InserisciNodoNoleggio(&(aux->ElencoNoleggi), N->info))
				return 0;
			aux->TotaleGuadagno = 0;
			int Guadagno = 0;
			Guadagno += N->info.Costo;
			aux->TotaleGuadagno += Guadagno;
			aux->next = (*PListaBiciclette);
			(*PListaBiciclette) = aux;
		}
		N = N->next;
	}
	return 1;
}

/*
4. Ricerca della bici con il guadagno maggiore: Funzione che, operando sulla lista delle bicicletta restituisce tutte
le informazioni della bicicletta con il valore massimo di totale_guadagno
*/

BiciclettaT RicercaBici(ListaBici ListaBiciclette) 
{
	int Guadagno;
	int MaxGuadagno = 0;
	BiciclettaT MaxBici;
	MaxBici.Costo = 0;
	strcpy(MaxBici.Dimensioni, "");
	strcpy(MaxBici.NumeroSerie, "");
	strcpy(MaxBici.Tipo, "");
	MaxBici.Durata = 0;
	while (ListaBiciclette != NULL) 
	{
		Guadagno = ListaBiciclette->TotaleGuadagno;
		if (Guadagno > MaxGuadagno) 
		{
			MaxGuadagno = Guadagno;
			strcpy(MaxBici.Dimensioni, ListaBiciclette->Dimensioni);
			strcpy(MaxBici.Tipo, ListaBiciclette->Tipo);
			strcpy(MaxBici.NumeroSerie, ListaBiciclette->NumeroSerie);
			MaxBici.Costo = ListaBiciclette->TotaleGuadagno;
		}
		ListaBiciclette = ListaBiciclette->next;
	}
	return MaxBici;
}

void VisualizzaNoleggi(ListaNoleggi Noleggi) 
{
	while (Noleggi != NULL) 
	{
		printf("%s %s %s %d %d\n", Noleggi->info.NumeroSerie, Noleggi->info.Tipo, Noleggi->info.Dimensioni, Noleggi->info.Durata, Noleggi->info.Costo);
		Noleggi = Noleggi->next;
	}
}

void VisualizzaBici(ListaBici Biciclette) 
{
	while (Biciclette != NULL) 
	{
		printf("NUMERO SERIE: %s // TIPOLOGIA: %s // GUADAGNO TOTALE: %d\n\nELENCO BICICLETTE NOLEGGIATE:\n", Biciclette->NumeroSerie, Biciclette->Tipo, Biciclette->TotaleGuadagno);
		VisualizzaNoleggi(Biciclette->ElencoNoleggi);
		printf("\n\n");
		Biciclette = Biciclette->next;
	}
}

int main() 
{
	int scelta;
	char NomeFile[64];
	int Istanze = 0;
	char NumeroSerie[64];
	char NuovoTipo[32];
	ListaNoleggi ListaNoleggiBiciclette = NULL;
	ListaBici Biciclette = NULL;
	BiciclettaT BiciMax;
	int esito;
	int n;
	do 
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci nome file: ");
			scanf("%s", NomeFile);
			n = Carica_Noleggi(&ListaNoleggiBiciclette, NomeFile);
			if (n != 0)
				printf("Sono stati caricati %d noleggi.\n", n);
			break;
		case 2:
			printf("Inserisci il numero di serie della bicicletta: ");
			scanf("%s", NumeroSerie);
			printf("Inserisci il nuovo tipo della bicicletta: ");
			scanf("%s", NuovoTipo);
			Istanze = ModificaTipoBicicletta(ListaNoleggiBiciclette, NumeroSerie, NuovoTipo, Istanze);
			if (Istanze != 0)
				printf("Sono state modificate %d istanze.\n", Istanze);
			break;
		case 3:
			esito = CreaListaBiciclette(&Biciclette, ListaNoleggiBiciclette);
			break;
		case 4:
			if (Biciclette != NULL)
			{
				BiciMax = RicercaBici(Biciclette);
				printf("La bici con il massimo guadagno e' %s.\n", BiciMax.NumeroSerie);
			}
			break;
		case 5:
			if (Biciclette != NULL)
				VisualizzaBici(Biciclette);
			printf("\n");
			break;
		}
	} while (scelta != 0);
}