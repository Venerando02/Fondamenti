/*
Implementare una applicazione console in linguaggio ANSI C che permetta di gestire gli articoli in un negozio di generi alimentari. 
Le informazioni di ciascun articolo sono memorizzate in un file (specificato nel seguito) e caricate in una lista degli articoli ordinata 
in base al codice dell’articolo. In un momento successivo, l’applicazione dovrà organizzare le informazioni di tali articoli in una lista 
di generi alimentari in cui ogni elemento della lista contiene, oltre al genere alimentare, anche l’elenco degli articoli di quel genere.
Specifica della struttura dati:
Articolo:
1. Codice (stringa, di al più 7 caratteri)
2. Nome prodotto (stringa, di al più 63 caratteri utili)
3. Genere alimentare (stringa senza spazi, che può contenere al più 15 caratteri utili)
4. Prezzo (reale)
5. Quantità (intero)
Genere Alimentare:
1. Genere alimentare (stringa senza spazi, che può contenere al più 15 caratteri utili)
2. Numero prodotti (numero di prodotti diversi di quel genera alimentare)
3. Elenco dei prodotti di quel genere alimentare, (implementato mediante una lista di Articolo)
Elenco delle operazioni/funzioni che devono essere implementate:
1. Funzione di caricamento da file di testo degli articoli nella lista degli articoli. La lista degli articoli deve essere mantenuta 
ordinata in modo crescente in base al codice dell’articolo. La funzione da implementare deve avere la seguente struttura:
nome della funzione: CaricaArticoli;
valore restituito: numero di articoli caricati;
parametri: nome del file, lista degli articoli.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
2. Funzione di modifica del prezzpodi un determinato prodotto. La funzione da implementare deve avere la seguente struttura:
nome della funzione: ModificaPrezzo;
valore restituito: esito operazione (0: operazione fallita, 1: modifica effettuata con successo);
parametri: lista dei prodotti, codice prodotto, nuovo prezzo.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
3. Funzione di eliminazione di un prodotto dalla lista. La funzione da implementare deve avere la seguente struttura:
nome della funzione: EliminaProdotto;
valore restituito: esito operazione (0: operazione fallita, 1: eliminazione effettuata con successo);
parametri: lista dei prodotti, codice del prodotto da eliminare.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
4. CopiaProdottiInListaGeneriAlimentari: Funzione di copia delle informazioni contenute nella lista dei prodotti nella lista dei generi alimentari,
facendo in modo che ogni genere alimentare contenga soltanto i prodotti appartenenti a quel genere. Lo studente scelga la struttura della funzione,
il tipo dei dati ed i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
5. PrezzoMedio: Funzione che, operando sulla lista dei generi alimentari e fornito come parametro di ingresso un genere alimentare, calcoli 
e restituisca il prezzo medio degli articoli di quel genere.
6. VisualizzaArticoliFasciaPrezzo: Funzione che, operando sulla lista dei generi alimentari e forniti come parametri di ingresso un prezzo
minimo e massimo, visualizzi i dati di tutti gli articoli il cui prezzo è compreso nell’intervallo fornito (estremi inclusi). 
La funzione deve inoltre restituire il numero di articoli visualizzati.
7. Funzione che visualizza il contenuto dell’intera lista di generi alimentari.
8. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni implementate ed eventualmente di
inserire i parametri necessari ed eseguire le operazioni richieste.

Esempio di file:
0000001
Acqua naturale
Bibite
0.30 200
0000012
Coca cola
Bibite
1.00 100
0000031
Biscotti ai cereali
Dolci
3.50 300
0001070
Zucchine
Frutta e verdura
1.50 50
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct SArticolo 
{
	char Codice[8];
	char NomeProdotto[64];
	char GenereAlimentare[16];
	float Prezzo;
	int Quantita;
}TArticolo;

typedef struct NodoArticoloS 
{
	TArticolo info;
	struct NodoArticoloS* next;
} NodoArticoloT, * ListaArticolo;

typedef struct NodoGenereAlimentareS
{
	ListaArticolo Elenco;
	char GenereAlimentare[16];
	int NumeroProdotti;
	struct NodoGenereAlimentare* Next;
} NodoGenereAlimentareT, * ListaGeneriAlimentari;

int InserisciNodoLista(ListaArticolo* PLista, TArticolo Articolo) 
{
	NodoArticoloT* aux = (NodoArticoloT*)malloc(sizeof(NodoArticoloT));
	if (aux == NULL)
		return 0;
	aux->info = Articolo;
	aux->next = (*PLista);
	(*PLista) = aux;
	return 1;
}

/*
1. Funzione di caricamento da file di testo degli articoli nella lista degli articoli. La lista degli articoli deve essere mantenuta
ordinata in modo crescente in base al codice dell’articolo. La funzione da implementare deve avere la seguente struttura:
nome della funzione: CaricaArticoli;
valore restituito: numero di articoli caricati;
parametri: nome del file, lista degli articoli.
*/
int CaricaArticoli(ListaArticolo* PLista, char* NomeFile) 
{
	int num = 0;
	FILE* fp = fopen(NomeFile, "r");
	if (fp == NULL)
		return 0;
	TArticolo art;
	while (fscanf(fp, "%s%s%s%f%d", art.Codice, art.NomeProdotto, art.GenereAlimentare, &art.Prezzo, &art.Quantita) != EOF)
	{
		if (!InserisciNodoLista(PLista, art))
			return 0;
		else
			num++;
	}
	fclose(fp);
	return num;
}

/*
2. Funzione di modifica del prezzo di un determinato prodotto. La funzione da implementare deve avere la seguente struttura:
nome della funzione: ModificaPrezzo;
valore restituito: esito operazione (0: operazione fallita, 1: modifica effettuata con successo);
parametri: lista dei prodotti, codice prodotto, nuovo prezzo.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/

int ModificaPrezzo(ListaArticolo prodotti, char* CodiceProdotto, float NuovoPrezzo) 
{
	if (prodotti == NULL)
		return 0;
	while (prodotti != NULL) 
	{
		if (strcmp(prodotti->info.Codice, CodiceProdotto) == 0) 
		{
			prodotti->info.Prezzo = NuovoPrezzo;
		}
		prodotti = prodotti->next;
	}
	return 1;
}

/*
3. Funzione di eliminazione di un prodotto dalla lista. La funzione da implementare deve avere la seguente struttura:
nome della funzione: EliminaProdotto;
valore restituito: esito operazione (0: operazione fallita, 1: eliminazione effettuata con successo);
parametri: lista dei prodotti, codice del prodotto da eliminare.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/

int EliminaProdotto(ListaArticolo* Articoli, char* CodiceProdotto) 
{
	ListaArticolo Aux;
	if ((*Articoli) == NULL)
		return 0;
	if (strcmp((*Articoli)->info.Codice, CodiceProdotto) == 0)
	{
		Aux = (*Articoli);
		(*Articoli) = (*Articoli)->next;
		free(Aux);
		return 1;
	}
	else
		return EliminaProdotto(&((*Articoli)->next), CodiceProdotto);
}

/*
4. CopiaProdottiInListaGeneriAlimentari: Funzione di copia delle informazioni contenute nella lista dei prodotti nella lista dei generi alimentari,
facendo in modo che ogni genere alimentare contenga soltanto i prodotti appartenenti a quel genere. Lo studente scelga la struttura della funzione,
il tipo dei dati ed i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/

int CopiaProdottiInListaGeneriAlimentari(ListaGeneriAlimentari* GeneriAlimentari, ListaArticolo Articoli) 
{
	if (Articoli == NULL)
		return 0;
	ListaArticolo Art = Articoli;
	ListaGeneriAlimentari Corrente = NULL;
	while(Art != NULL)
	{
		Corrente = (*GeneriAlimentari);
		int trovato = 0;
		while (Corrente != NULL) 
		{
			if (strcmp(Corrente->GenereAlimentare, Art->info.GenereAlimentare) == 0) 
			{
				trovato = 1;
				break;
			}
			Corrente = Corrente->Next;
		}
		if (trovato == 1) 
		{
			Corrente->NumeroProdotti += Art->info.Quantita;
			InserisciNodoLista(&(Corrente->Elenco), Art->info);
		}
		else 
		{
			NodoGenereAlimentareT* aux = (NodoGenereAlimentareT*)malloc(sizeof(NodoGenereAlimentareT));
			if (aux == NULL)
				return 0;
			aux->NumeroProdotti = 0;
			strcpy(aux->GenereAlimentare, Art->info.GenereAlimentare);
			aux->Elenco = NULL;
			if (!InserisciNodoLista(&(aux->Elenco), Art->info))
				return 0;
			aux->NumeroProdotti = Art->info.Quantita;
			aux->Next = (*GeneriAlimentari);
			(*GeneriAlimentari) = aux;
		}
		Art = Art->next;
	}
	return 1;
}

/*
6. VisualizzaArticoliFasciaPrezzo: Funzione che, operando sulla lista dei generi alimentari e forniti come parametri di ingresso un prezzo
minimo e massimo, visualizzi i dati di tutti gli articoli il cui prezzo è compreso nell’intervallo fornito (estremi inclusi).
La funzione deve inoltre restituire il numero di articoli visualizzati.
*/

int VisualizzaArticoliFasciaPrezzo(ListaGeneriAlimentari Generi, float PrezzoMinimo, float PrezzoMassimo) 
{
	ListaArticolo aux;
	int NumArticoli = 0;
	while (Generi != NULL) 
	{
		aux = Generi->Elenco;
		while (aux != NULL) 
		{
			if ((aux->info.Prezzo >= PrezzoMinimo) && (aux->info.Prezzo <= PrezzoMassimo)) 
			{
				printf("%s %s %s %d %.3f\n", aux->info.Codice, aux->info.GenereAlimentare, aux->info.NomeProdotto, aux->info.Prezzo, aux->info.Quantita);
				NumArticoli++;
			}
			aux = aux->next;
		}
		Generi = Generi->Next;
	}
	return NumArticoli;
}

/*
5. PrezzoMedio: Funzione che, operando sulla lista dei generi alimentari e fornito come parametro di ingresso un genere alimentare, calcoli
e restituisca il prezzo medio degli articoli di quel genere.
*/
float PrezzoMedio(ListaGeneriAlimentari Lista, char * GenereAlimentare) 
{
	float Somma = 0;
	int cont = 0;
	ListaArticolo aux;
	while (Lista != NULL) 
	{
		if (strcmp(Lista->GenereAlimentare, GenereAlimentare) == 0) 
		{
			aux = Lista->Elenco;
			while (aux != NULL) 
			{
				Somma += aux->info.Prezzo;
				cont++;
				aux = aux->next;
			}
		}
		Lista = Lista->Next;
	}
	float media = (float)(Somma) / (float)(cont);
	return media;
}

int Menu() 
{
	int scelta;
	printf("******** MENU ********\n"
		"1. Carica dati da file.\n"
		"2. Modifica prezzo di un prodotto.\n"
		"3. Elimina prodotto.\n"
		"4. Copia prodotti in generi alimentari.\n"
		"5. Visualizza articoli nella fascia di prezzo.\n"
		"6. Calcola il prezzo medio per un genere alimentare.\n"
		"7. Visualizza contenuto lista.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

void StampaArticoli(ListaArticolo Articolo)
{
	while (Articolo != NULL)
	{
		printf("%s %s %s %d %.3f\n", Articolo->info.Codice, Articolo->info.GenereAlimentare, Articolo->info.NomeProdotto, Articolo->info.Quantita, Articolo->info.Prezzo);
		Articolo = Articolo->next;
	}
}

void StampGeneriAlimentari(ListaGeneriAlimentari Generi)
{
	while (Generi != NULL)
	{
		printf("NOME GENERE: %s // NUMERO ARTICOLI: %d\nELENCO:\n", Generi->GenereAlimentare, Generi->NumeroProdotti);
		StampaArticoli(Generi->Elenco);
		Generi = Generi->Next;
	}
}


int main(void) 
{
	ListaArticolo Articoli = NULL;
	ListaGeneriAlimentari GeneriAlimentari = NULL;
	char NomeFile[64];
	char GenereAlimentare[16];
	char Codice[8];
	float media;
	float PrezzoMin, PrezzoMax;
	int NumeroArticoli;
	float NuovoPrezzo;
	int esito, n;
	int scelta;
	do 
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			NumeroArticoli = CaricaArticoli(&Articoli, NomeFile);
			if (NumeroArticoli != 0)
				printf("Sono stati caricati %d articoli.\n", NumeroArticoli);
			StampaArticoli(Articoli);
			break;
		case 2:
			printf("Inserisci il codice del prodotto: ");
			scanf("%s", Codice);
			printf("Inserisci il nuovo prezzo: ");
			scanf("%f" , &NuovoPrezzo);
			esito = ModificaPrezzo(Articoli, Codice, NuovoPrezzo);
			if (esito == 1)
				printf("Modifica effettuata con successo.\n");
			break;
		case 3:
			printf("Inserisci il codice del prodotto da eliminare: ");
			scanf("%s", Codice);
			esito = EliminaProdotto(&Articoli, Codice);
			if (esito == 1)
				printf("Prodotto eliminato con successo.\n");
			break;
		case 4:
			esito = CopiaProdottiInListaGeneriAlimentari(&GeneriAlimentari, Articoli);
			if (esito == 1) 
			{
				printf("Inserimento avvenuto con successo.\n");
			}
			break;
		case 5:
			printf("Inserisci prezzo minimo: ");
			scanf("%f", &PrezzoMin);
			printf("Inserisci prezzo massimo: ");
			scanf("%f", &PrezzoMax);
			n = VisualizzaArticoliFasciaPrezzo(GeneriAlimentari, PrezzoMin, PrezzoMax);
			printf("\n\nSono stati visualizzati %d articoli.\n", n);
			break;
		case 6:
			printf("Inserisci il genere alimentare: ");
			scanf("%s", GenereAlimentare);
			media = PrezzoMedio(GeneriAlimentari, GenereAlimentare);
			printf("Il prezzo medio e' %.3f.\n", media);
			break;
		case 7:
			if (GeneriAlimentari != NULL) 
			{
				StampGeneriAlimentari(GeneriAlimentari);
			}
			break;
		}
	} while (scelta != 0);
}