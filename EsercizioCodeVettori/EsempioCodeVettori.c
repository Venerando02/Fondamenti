/*
Implementare una applicazione console in linguaggio ANSI C che permetta di gestire la coda di attesa di un pronto soccorso.
I dati vengono letti inizialmente da un file di testo (descritto nel seguito) e/o da console.
L’applicazione prevede che i pazienti vengano inseriti in una singola coda per essere poi smistati in un vettore di 3 liste associate all’esito delle visite effettuate. 
In particolare, in ciascuna elemento del vettore è contenuta una lista che raggruppa i pazienti in base all’esito ricevuto (0=dimesso, 1=in osservazione, 2=ricoverato).
Specifica della struttura dati:
Paziente:
− codice fiscale
− orario di arrivo (codificato come stringa nel formato HH:MM)
− tempo di servizio (intero espresso in minuti) – inizialmente pari a 0
Si implementino le seguenti funzioni:
1. Funzione di caricamento dei dati dei pazienti da un file di testo all’interno della coda. Lo studente scelga sia il tipo dei dati che i meccanismi
di passaggio dei parametri più opportuni.
2. Funzione per aggiungere i dati di un paziente letti da standard input all’interno della coda.
3. Funzione che estrae (rimuovendolo) un paziente dalla coda di ingresso e lo inserisce opportunamente nel vettore di liste.
L’utente dovrà poter inserire da tastiera il tempo di servizio e l’esito (0=dimesso, 1=in osservazione, 2=ricoverato) che dovranno essere forniti alla funzione come parametri.
4. Funzione che, dato in ingresso il vettore di liste di pazienti, restituisca il numero di pazienti nelle tre liste.
5. Funzione che, dato in ingresso un tempo di attesa soglia, restituisca in uscita l’insieme di pazienti dimessi che hanno avuto un tempo di attesa superiore a quello soglia.
Lo studente scelga il tipo dei dati ed i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
6. Funzione che permette di visualizzare il contenuto di tutti i pazienti presenti nel vettore di liste.
Si implementi infine un main dotato di un menù testuale che permetta all’utente di usare tutte le funzioni implementate ed eventualmente di inserire i parametri
necessari ed eseguire le operazioni richieste.

Esempio di file di ingresso
asdcvb63a12c351d 11:31 0 
grdals82d23f218w 11:55 0 
pplald79f14m139z 12:15 0 
rssrzo85e15c351s 12:24 0
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESITI 3

typedef struct PazienteS 
{
	char CF[17];
	char OraArrivo[6];
	int TempoServizio;
	int esito;
} PazienteT;

typedef struct NodoPazienteS 
{
	PazienteT info;
	struct NodoPazienteS* next;
} NodoPazienteT, *ListaPazienti;

typedef struct CodaPazientiS 
{
	NodoPazienteT* primo;
	NodoPazienteT* ultimo;
} CodaPazientiT;

int InserisciCodaPaziente(CodaPazientiT* pcoda, PazienteT p) 
{
	NodoPazienteT* aux = (NodoPazienteT*)malloc(sizeof(NodoPazienteT));
	aux->info = p;
	aux->next = NULL;
	if ((*pcoda).primo == NULL)
	{
		(*pcoda).primo = (*pcoda).ultimo = aux;
	}
	else 
	{
		(*pcoda).ultimo->next = aux;
		(*pcoda).ultimo = aux;
	}
	return 1;
}

int CaricaDatiFile(CodaPazientiT* pcoda, char* NomeFile) 
{
	int n = 0;
	PazienteT p;
	FILE* fp = fopen(NomeFile, "r");
	if (fp == NULL)
		return 0;
	while (fscanf(fp, "%s%s%d", p.CF, p.OraArrivo, &p.TempoServizio) == 3)
	{
		if (!InserisciCodaPaziente(pcoda, p))
			return 0;
		else 
		{
			n++;
		}
	}
	fclose(fp);
	return n;
}

int AggiungiNodoLista(ListaPazienti* plista, PazienteT p) 
{
	NodoPazienteT* aux = (NodoPazienteT*)malloc(sizeof(NodoPazienteT));
	if (aux == NULL)
		return 0;
	aux->info = p;
	aux->next = (*plista);
	(*plista) = aux;
	return 1;
}

/*
3. Funzione che estrae (rimuovendolo) un paziente dalla coda di ingresso e lo inserisce opportunamente nel vettore di liste.
L’utente dovrà poter inserire da tastiera il tempo di servizio e l’esito (0=dimesso, 1=in osservazione, 2=ricoverato) che dovranno essere forniti alla funzione come parametri.
*/

PazienteT EliminaPaziente(CodaPazientiT* pcoda, char* CF) 
{
	PazienteT p = {NULL};
	if ((*pcoda).primo == NULL)
		return p;
	else if (strcmp((*pcoda).primo->info.CF, CF) == 0)
	{
		NodoPazienteT* aux = (*pcoda).primo;
		p = aux->info;
		(*pcoda).primo = (*pcoda).primo->next;
		free(aux);
		return p;
	}
	else {
		return EliminaPaziente(&((*pcoda).primo->next), CF);
	}
}

int InserisciVettoreListe(ListaPazienti* vettore, CodaPazientiT* pcoda, char* CF) 
{
	PazienteT P;
	while ((*pcoda).primo != NULL) 
	{
		if (strcmp((*pcoda).primo->info.CF, CF))
		{
			P = EliminaPaziente(pcoda, CF);
			printf("Inserisci l'esito: ");
			scanf("%d", &P.esito);
			printf("Inserisci tempo servizio: ");
			scanf("%d", &P.TempoServizio);
			AggiungiNodoLista(&vettore[P.esito], P);
			break;
		}
		else 
		{
			(*pcoda).primo = (*pcoda).primo->next;
		}
	}
	return 1;
}

void VisualizzaCoda(CodaPazientiT coda) 
{
	printf("ELEMENTI IN CODA:\n");
	while (coda.primo != NULL) 
	{
		printf("%s %s %d\n", coda.primo->info.CF, coda.primo->info.OraArrivo, coda.primo->info.TempoServizio);
		coda.primo = coda.primo->next;
	}
}

void VisualizzaVettoreListe(ListaPazienti v[]) 
{
	ListaPazienti l;
	for (int i = 0; i < ESITI; i++)
	{
		printf("ESITO %d:\n", i);
		l = v[i];
		while (l != NULL) 
		{
			printf("%s %s %d %d\n", l->info.CF, l->info.OraArrivo, l->info.TempoServizio, l->info.esito);
			l = l->next;
		}
		printf("\n");
	}
}

void InizializzaCoda(CodaPazientiT* pcoda) 
{
	(*pcoda).primo = (*pcoda).ultimo = NULL;
}

int* CreaVettore(ListaPazienti* vettore) 
{
	int* v = malloc(sizeof(int) * 3);
	int contatore;
	for (int i = 0; i < ESITI; i++) 
	{
		contatore = 0;
		while (vettore[i] != NULL)
		{
			contatore++;
			vettore[i] = vettore[i]->next;
		}
		v[i] = contatore;
	}
	return v;
}

int Menu() 
{
	int scelta;
	
	printf("****** MENU ********\n"
		"1) Carica dati da file\n"
		"2) Inserisci dati nel vettore\n"
		"3) Visualizza numero clienti per esito\n"
		"0) Esci\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

int main() 
{
	char NomeFile[32];
	char CF[17];
	CodaPazientiT coda;
	int* numeropazienti = NULL;
	InizializzaCoda(&coda);
	ListaPazienti vettore[3] = {NULL};
	int scelta;
	do 
	{
		scelta = Menu();

		switch (scelta)
		{
		case 1:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			CaricaDatiFile(&coda, NomeFile);
			VisualizzaCoda(coda);
			break;
		case 2:
			printf("Inserisci il codice fiscale del cliente: ");
			scanf("%s", CF);
			InserisciVettoreListe(vettore, &coda, CF);
			printf("RISULTATO\n");
			VisualizzaVettoreListe(vettore);
			break;
		case 3: 
			numeropazienti = CreaVettore(vettore);
			printf("\nNUMERO PAZIENTI PER REPARTO:\n");
			for (int i = 0; i < ESITI; i++)
			{
				printf("ESITO %d: %d\n", i, numeropazienti[i]);
			}
			break;
		}
	} while (scelta != 0);
	free(numeropazienti);

}