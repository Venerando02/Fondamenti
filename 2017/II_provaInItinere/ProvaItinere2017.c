/*
Implementare una applicazione console in linguaggio ANSI C che permetta di gestire la prenotazione degli esami di un determinato insegnamento.
Le prenotazioni sono salvate in una coda di prenotazioni e possono essere relativi ad appelli differenti, i valori contenuti nella coda devono essere caricati 
da console e salvati su un file di testo preservando l’ordine di inserimento.
In un momento successivo l’applicazione carica i dati dal file in una lista di code, in cui ogni elemento della lista contiene la data dell’appello e la 
coda dei prenotati per quella data (lista di appelli).
Specifica della struttura dati:
Prenotazione:
1. Numero matricola (matricola) implementato con una stringa, senza caratteri bianchi, che può contenere al più 15 caratteri utili;
2. Voto finale implementato con un intero (il valore -1 indica che non è stato assegnato alcun valore);
3. Data dell’appello (data) implementato con una stringa nel formato AAAA-MM-GG, senza caratteri bianchi, che può contenere al più 15 caratteri utili;
Appello:
1. Data dell’appello (data) implementato con una stringa nel formato AAAA-MM-GG, senza caratteri bianchi, che può contenere al più 15 caratteri utili;
2. Numero di studenti prenotati implementato con un intero;
3. Elenco degli studenti prenotati, implementato mediante una coda di prenotati.
Elenco delle operazioni/funzioni che devono essere implementate:
1. Funzione di inserimento dei dati da console. La funzione da implementare deve avere la seguente struttura:
nome della funzione: inserimento_prenotazione;
valore restituito: riferimento all’elemento inserito;
parametri: coda delle prenotazioni, dati della prenotazione.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica;
2. Salvataggio dei dati presenti nella coda delle prenotazione in un file di testo. La funzione da implementare deve avere la seguente struttura:
nome della funzione: salva_prenotazioni;
valore restituito: numero di elementi salvati;
parametri: descrittore del file, coda delle prenotazioni.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica;
3. Funzione di caricamento dei dati da un file di testo nella struttura dati coda delle prenotazioni: La funzione da implementare deve avere la seguente struttura:
nome della funzione: carica_coda_prenotazioni;
valore restituito: numero di elementi caricati;
parametri: dO46000111 -1 20170428
O46000222 -1 20170428
O46000333 -1 20170428
O46000112 -1 20170426
O46000223 -1 20170426
escrittore del file, coda delle prenotazioni.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica;
4. Funzione di caricamento dei dati da un file di testo nella struttura dati lista di appelli. La funzione a partire dai dati presenti nel file crea una lista di appelli e la relativa coda di prenotazioni in base alla data dell’appello. Lo studente scelga la struttura della funzione, il tipo dei dati ed i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica
5. Funzione che calcola e fornisce come parametri il numero medio, minimo e massimo di prenotazioni per appello;
6. Funzione che dato il numero di matricola permette di assegnare il voto dell’esame allo studente. Nota bene che si suppone che lo studente possa avere inserito una sola prenotazione nell’intera struttura dati e che i dati necessari devono essere forniti alla funzione come parametri;
7. Funzione che stampa sulla console il contenuto dell’intera struttura dati;
8. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni implementate ed eventualmente di inserire i parametri necessari ed eseguire le operazioni richieste.
Esempio di file di salvataggio
O46000111 -1 20170428
O46000222 -1 20170428
O46000333 -1 20170428
O46000112 -1 20170426
O46000223 -1 20170426
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PrenotazioneS 
{
	char NumeroMatricola[16];
	int Voto;
	char DataAppello[16];
} PrenotazioneT;

typedef struct NodoPrenotazioneS 
{
	PrenotazioneT info;
	struct NodoPrenotazioneS* next;
} NodoPrenotazioneT;

typedef struct CodaPrenotazioni 
{
	NodoPrenotazioneT* primo;
	NodoPrenotazioneT* ultimo;
} CodaPrenotazioniT;

typedef struct NodoApelloS 
{
	char DataAppello[16];
	int NumStudenti;
	CodaPrenotazioniT Cprenotati;
	struct NodoAppelloS* next;
} NodoAppelloT, * ListaAppelli;

void InizializzaCoda(CodaPrenotazioniT* PCoda)
{
	(*PCoda).primo = (*PCoda).ultimo = NULL;
}

/*
1. Funzione di inserimento dei dati da console. La funzione da implementare deve avere la seguente struttura:
nome della funzione: inserimento_prenotazione;
valore restituito: riferimento all’elemento inserito;
parametri: coda delle prenotazioni, dati della prenotazione.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica;
*/

PrenotazioneT* inserimento_prenotazione(CodaPrenotazioniT* PCoda, PrenotazioneT P) 
{
	NodoPrenotazioneT* aux = (NodoPrenotazioneT*)malloc(sizeof(NodoPrenotazioneT));
	if (aux == NULL)
		return NULL;
	aux->info = P;
	aux->next = NULL;
	if ((*PCoda).primo == NULL) 
	{
		(*PCoda).primo = (*PCoda).ultimo = aux;
	}
	else 
	{
		(*PCoda).ultimo->next = aux;
		(*PCoda).ultimo = aux;
	}
	return &(aux->info);
}

/*
2. Salvataggio dei dati presenti nella coda delle prenotazione in un file di testo. La funzione da implementare deve avere la seguente struttura:
nome della funzione: salva_prenotazioni;
valore restituito: numero di elementi salvati;
parametri: descrittore del file, coda delle prenotazioni.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica;
*/

int salva_prenotazioni(FILE* fp, CodaPrenotazioniT Coda) 
{
	if (Coda.primo == NULL)
		return 0;
	int num = 0;
	PrenotazioneT p;
	while (Coda.primo != NULL) 
	{
		p = Coda.primo->info;
		if (!fprintf(fp, "%s %s %d\n", p.DataAppello, p.NumeroMatricola, p.Voto))
		{
			return 0;
		}
		else
		{
			num++;
		}
		Coda.primo = Coda.primo->next;
	}
	fclose(fp);
	return num;
}

/*
3. Funzione di caricamento dei dati da un file di testo nella struttura dati coda delle prenotazioni: La funzione da implementare deve avere la seguente struttura:
nome della funzione: carica_coda_prenotazioni;
valore restituito: numero di elementi caricati;
parametri: descrittore del file, coda delle prenotazioni.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica;
*/

int carica_coda_prenotazioni(FILE* fp, CodaPrenotazioniT coda) 
{
	int num = 0;
	PrenotazioneT aux;
	PrenotazioneT* pren;
	while (fscanf(fp, "%s%d%s", aux.NumeroMatricola, &aux.Voto, aux.DataAppello) == 3) 
	{
		pren = inserimento_prenotazione(&coda, aux);
		if (pren == NULL)
			return 0;
		else
			num++;
	}
	fclose(fp);
	return num;
}

/*
4. Funzione di caricamento dei dati da un file di testo nella struttura dati lista di appelli.
La funzione a partire dai dati presenti nel file crea una lista di appelli e la relativa coda di prenotazioni in base alla data dell’appello. 
Lo studente scelga la struttura della funzione, il tipo dei dati ed i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica
*/

int CaricaDatiDaFile(ListaAppelli* Appelli, char * NomeFile) 
{
	FILE* fp = fopen(NomeFile, "r");
	if (fp == NULL)
		return 0;
	int num = 0;
	PrenotazioneT p, * nprenotati;
	ListaAppelli Corrente = NULL;
	while (fscanf(fp, "%s%d%s", p.NumeroMatricola, &p.Voto, p.DataAppello) == 3) 
	{
		Corrente = (*Appelli);
		int trovato = 0;
		while (Corrente != NULL) 
		{
			if (strcmp(Corrente->DataAppello, p.DataAppello) == 0) 
			{
				trovato = 1;
				break;
			}
			Corrente = Corrente->next;
		}
		if (trovato == 1) 
		{
			Corrente->NumStudenti++;
			nprenotati = inserimento_prenotazione(&((*Appelli)->Cprenotati), p);
			if (nprenotati == NULL)
				return 0;
			else
				num++;
		}
		else 
		{
			NodoAppelloT* aux = (NodoAppelloT*)malloc(sizeof(NodoAppelloT));
			if (aux == NULL)
				return 0;
			InizializzaCoda(&(aux->Cprenotati));
			strcpy(aux->DataAppello, p.DataAppello);
			aux->NumStudenti = 1;
			nprenotati = inserimento_prenotazione(&(aux->Cprenotati), p);
			if (nprenotati == NULL)
				return 0;
			aux->next = (*Appelli);
			(*Appelli) = aux;
			num++;
		}
	}
	fclose(fp);
	return num;
}

/*
5. Funzione che calcola e fornisce come parametri il numero medio, minimo e massimo di prenotazioni per appello;
*/

void CalcoloStatisticheAppelli(ListaAppelli Appelli, int * minimo, int* massimo, float * NumeroMedio) 
{
	(*minimo) = Appelli->NumStudenti;
	(*massimo) = Appelli->NumStudenti;
	(*NumeroMedio) = 0;
	int cont = 0;
	int nappelli = 0;
	CodaPrenotazioniT Coda;
	while (Appelli != NULL) 
	{
		Coda = Appelli->Cprenotati;
		while (Coda.primo != NULL) 
		{
			cont++;
			Coda.primo = Coda.primo->next;
		}

		if (Appelli->NumStudenti > (*massimo)) 
		{
			(*massimo) = Appelli->NumStudenti;
		}
		if (Appelli->NumStudenti < (*minimo)) 
		{
			(*minimo) = Appelli->NumStudenti;
		}
		
		nappelli++;
		Appelli = Appelli->next;
	}
	(*NumeroMedio) = (float)(cont) / (float)(nappelli);
}

int Menu() 
{
	int scelta;
	printf("******** MENU ********\n"
		"1. Inserisci prenotazione.\n"
		"2. Salva dati coda sul file di testo.\n"
		"3. Carica dati nella coda.\n"
		"4. Carica dati nella lista appelli.\n"
		"5. Numero medio, minimo e massimo.\n"
		"6. Assegna voto esame a studente.\n"
		"7. Visualizza la lista.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

/*
6. Funzione che dato il numero di matricola permette di assegnare il voto dell’esame allo studente.
Nota bene che si suppone che lo studente possa avere inserito una sola prenotazione nell’intera struttura dati e 
che i dati necessari devono essere forniti alla funzione come parametri;
*/

int AssegnaVotoStudente(ListaAppelli Appelli, char* Matricola, int Voto) 
{
	CodaPrenotazioniT c;
	if (Appelli == NULL)
		return 0;
	while (Appelli != NULL) 
	{
		c = Appelli->Cprenotati;
		while (c.primo != NULL) 
		{
			if (strcmp(c.primo->info.NumeroMatricola, Matricola) == 0) 
			{
				c.primo->info.Voto = Voto;
			}
			c.primo = c.primo->next;
		}
		Appelli = Appelli->next;
	}
	return 1;
}


void VisualizzaCoda(CodaPrenotazioniT Coda) 
{
	while (Coda.primo != NULL) 
	{
		printf("%s %s %d\n", Coda.primo->info.NumeroMatricola, Coda.primo->info.DataAppello, Coda.primo->info.Voto);
		Coda.primo = Coda.primo->next;
	}
}

void VisualizzaLista(ListaAppelli appelli) 
{
	while (appelli != NULL) 
	{
		printf("DATA APPELLO: %s // NUMERO STUDENTI: %d\nCODA:\n", appelli->DataAppello, appelli->NumStudenti);
		VisualizzaCoda(appelli->Cprenotati);
		appelli = appelli->next;
	}
}

int main(void) 
{
	int scelta;
	CodaPrenotazioniT CodaP;
	ListaAppelli ListaAppelli = NULL;
	InizializzaCoda(&CodaP);
	PrenotazioneT P, *Ppren;
	char NumeroMatricola[16];
	char NomeFile[64];
	int minimo, massimo, num, voto, esito;
	float NumeroMedio;
	do 
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci i dati della prenotazione (numero matricola, voto e data appello): ");
			scanf("%s %d %s", P.NumeroMatricola, &P.Voto, P.DataAppello);
			Ppren = inserimento_prenotazione(&CodaP, P);
			if ((Ppren) != NULL) 
			{
				printf("E' stato inserito la matricola %s.\n", (*Ppren).NumeroMatricola);
			}
			break;
		case 2:
			if (CodaP.primo != NULL)
			{
				printf("Inserisci il nome del file su cui vuoi salvare i dati: ");
				scanf("%s", NomeFile);
				FILE* fp = fopen(NomeFile, "w");
				if (fp == NULL)
					return 0;
				num = salva_prenotazioni(fp, CodaP);
				if (num != 0)
					printf("Sono stati caricati %d elementi.\n", num);
			}
			else
				printf("Coda vuota.\n");
			break;
		case 3:
			if (CodaP.primo != NULL) 
			{
				printf("Inserisci il nome del file: ");
				scanf("%s", NomeFile);
				FILE* fp = fopen(NomeFile, "r");
				if (fp == NULL)
					return 0;
				num = carica_coda_prenotazioni(fp, CodaP);
				if (num != 0)
					printf("Sono state caricate %d elementi.\n", num);
			}
			else
				printf("Coda vuota.\n");
			break;
		case 4:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			num = CaricaDatiDaFile(&ListaAppelli, NomeFile);
			if (num != 0)
				printf("Sono stati caricati %d elementi.\n", num);
			break;
		case 5:
			if (ListaAppelli != NULL)
			{
				CalcoloStatisticheAppelli(ListaAppelli, &minimo, &massimo, &NumeroMedio);
				printf("Il numero minimo e' di %d, il massimo e' %d, quindi il numero medio e' %.3f.\n", minimo, massimo, NumeroMedio);
			}
			break;
		case 6:
			if (ListaAppelli != NULL)
			{
				printf("Inserisci il numero di matricola: ");
				scanf("%s", NumeroMatricola);
				printf("Inserisci il voto: ");
				scanf("%d", &voto);
				esito = AssegnaVotoStudente(ListaAppelli, NumeroMatricola, voto);
				if (esito == 1)
				{
					printf("Operazione effettuata con successo.\n");
				}
			}
			break;
		case 7:
			if (ListaAppelli != NULL) 
			{
				VisualizzaLista(ListaAppelli);
			}
			break;
		}
	} while (scelta != 0);
}