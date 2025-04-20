/*
Implementare una applicazione console in linguaggio ANSI C che permetta di gestire la coda di attesa di un pronto
soccorso: le attese sono gestite con diverse priorità da 1 a 10. Tutte le operazioni richieste devono essere svolte
utilizzando la struttura dati creata in memoria eccetto le operazioni di caricamento e salvataggio.
L’applicazione prevede i pazienti vengano inseriti in una singola coda per essere poi smistati alle code associate alla
priorità corretta.
I dati vengono letti da un file di testo (descritto nel seguito).
La struttura dati da implementare è un vettore di code o, in alternativa una lista di code.
In ogni elemento del vettore (o del vettore) è contenuta una coda di pazienti.
Specifica della struttura dati:
Paziente:
1. Codice fiscale,
2. Priorità iniziale,
3. Ora di arrivo (codificate come stringa nel formato HH:MM)
4. Ora di Uscita (codificate come stringa nel formato HH:MM)
Priorità:
1. Numero totale di pazienti presenti;
2. Elenco dei pazienti presenti
Elenco delle operazioni/funzioni che devono essere implementate:
1. Funzione di inserimento dei dati da tastiera. La funzione da implementare deve avere la seguente struttura:
<coda> inserisci_coda(<coda>, <paziente>).
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la
specifica;
2. Funzione di caricamento dei dati da un file di testo. La funzione da implementare ha la seguente struttura:
<coda> carica_lista(<descrittore del file>, <coda>, <numero pazienti presenti>).
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la
specifica;
3. Funzione di assegnazione dei pazienti alla coda di appartenenza. Lo studente scelga la struttura della funzione, il
tipo dei dati ed i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica;
4. Funzione che restituisce il numero medio di pazienti presenti, il numero massimo ed il numero minimo. Lo
studente scelga la struttura della funzione, il tipo dei dati ed i meccanismi di passaggio dei parametri più
opportuni per rispettare la specifica;
5. Funzione che stampa il contenuto dell’intera struttura dati. Lo studente scelga la struttura della funzione, il tipo
dei dati ed i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica
6. Funzione che restituisce l’insieme dei pazienti che attendono da un tempo maggiore di quello dato (passato
come parametro alla funzione);
7. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni
implementate ed eventualmente di inserire i parametri necessari ed eseguire le operazioni richieste.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 10

typedef struct PazienteS 
{
	char CodiceFiscale[17];
	int PrioritaIniziale;
	char OraArrivo[6];
	char OraUscita[6];
} PazienteT;

typedef struct NodoPazienteS 
{
	PazienteT info;
	struct NodoPazienteS* next;
} NodoPazienteT;

typedef struct CodaPazientiS
{
	NodoPazienteT* primo;
	NodoPazienteT* ultimo;
} CodaPazienti;

typedef struct VPazienti 
{
	int NumeroTotalePazienti;
	CodaPazienti Pazienti;
} PrioritaV;

void InizializzaCoda(CodaPazienti* PCoda) 
{
	(*PCoda).primo = (*PCoda).ultimo = NULL;
}

CodaPazienti inserisci_coda(CodaPazienti Coda, PazienteT paziente)
{
	NodoPazienteT* aux = (NodoPazienteT*)malloc(sizeof(NodoPazienteT));
	if (aux == NULL)
		return Coda;
	aux->info = paziente;
	aux->next = NULL;
	if (Coda.primo == NULL) 
	{
		Coda.primo = Coda.ultimo = aux;
	}
	else
	{
		Coda.ultimo->next = aux;
		Coda.ultimo = aux;
	}
	return Coda;
}

/*
2. Funzione di caricamento dei dati da un file di testo. La funzione da implementare ha la seguente struttura:
<coda> carica_lista(<descrittore del file>, <coda>, <numero pazienti presenti>).
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la
specifica;
*/

CodaPazienti carica_lista(char* NOMEFILE, CodaPazienti Coda, int* NumeroPazienti) 
{
	FILE* fp = fopen(NOMEFILE, "r");
	if (fp == NULL)
		return Coda;
	PazienteT p;
	(*NumeroPazienti) = 0;
	while (fscanf(fp, "%s%s%s%d", p.CodiceFiscale, p.OraArrivo, p.OraUscita, &p.PrioritaIniziale) == 4) 
	{
		Coda = inserisci_coda(Coda, p);
		(*NumeroPazienti)++;
	}
	fclose(fp);
	return Coda;
}

/*
3. Funzione di assegnazione dei pazienti alla coda di appartenenza. Lo studente scelga la struttura della funzione, il
tipo dei dati ed i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica;
*/
int CreaListaPriorita(PrioritaV v[], CodaPazienti coda) 
{
	NodoPazienteT* C = coda.primo;
	while (C != NULL) 
	{
		v[(C->info.PrioritaIniziale - 1)].Pazienti = inserisci_coda(v[(C->info.PrioritaIniziale - 1)].Pazienti, C->info);
		v[(C->info.PrioritaIniziale - 1)].NumeroTotalePazienti++;
		C = C->next;
	}
	return 1;
}

/*
4. Funzione che restituisce il numero medio di pazienti presenti, il numero massimo ed il numero minimo. Lo
studente scelga la struttura della funzione, il tipo dei dati ed i meccanismi di passaggio dei parametri più
opportuni per rispettare la specifica;
*/

int RestituisciNumeroMedioMaxMinPazienti(PrioritaV vettore[], int dim, int* Max, float* NumeroMedio, int* Min) 
{
	(*Max) = vettore[0].NumeroTotalePazienti;
	(*NumeroMedio) = 0.0;
	(*Min) = vettore[0].NumeroTotalePazienti;
	
	NodoPazienteT* aux;

	int contatore;
	int somma_pazienti = 0;

	for (int i = 0; i < dim; i++) 
	{
		aux = vettore[i].Pazienti.primo;
		contatore = 0;
		while (aux != NULL) 
		{
			contatore++;
			aux = aux->next;
		}
		if (contatore > (*Max))
		{
			(*Max) = contatore;
		}
		if (contatore < (*Min))
		{
			(*Min) = contatore;
		}
		somma_pazienti += contatore;
	}

	float Media = (float)(somma_pazienti) / (float)(dim);
	(*NumeroMedio) = Media;
	return 1;
}

int Menu() 
{
	int scelta;
	printf("******** MENU ********\n"
		"1. Carica dati paziente da tastiera.\n"
		"2. Carica dati da file di testo.\n"
		"3. Crea lista priorita'.\n"
		"4. Trova numero massimo, minimo e medio di pazienti.\n"
		"5. Visualizza lista priorita'.\n"
		"6. Pazienti che aspettano piu' del tempo dato.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

void VisualizzaCoda(CodaPazienti Pazienti) 
{
	NodoPazienteT* aux = Pazienti.primo;
	while (aux != NULL) 
	{
		printf("%s %s // %s %d\n", aux->info.CodiceFiscale, aux->info.OraArrivo, aux->info.OraUscita, aux->info.PrioritaIniziale);
		aux = aux->next;
	}
}

void VisualizzaVettorePriorita(PrioritaV Vett[], int dim) 
{
	for (int i = 0; i < dim; i++) 
	{
		printf("PRIORITA' %d // NUMERO PAZIENTI: %d\nCODA:\n", i + 1, Vett[i].NumeroTotalePazienti);
		VisualizzaCoda(Vett[i].Pazienti);
		printf("\n");
	}
}

int ContaTempoMinuti(char* OraArrivo, char* OraUscita) 
{
	char OraA[3];
	char OraP[3];
	strncpy(OraA, OraArrivo, 2);
	OraA[2] = "\0";
	strncpy(OraP, OraUscita, 2);
	OraA[2] = "\0";

	int differenza = atoi(OraP) - atoi(OraA);
	int MinutiOre = differenza * 60;
	
	char MinutiA[3];
	char MinutiP[3];
	strncpy(MinutiA, OraArrivo+3, 2);
	MinutiA[2] = "\0";
	strncpy(MinutiP, OraUscita + 3, 2);
	MinutiP[2] = "\0";
	
	int diffrenzaM = atoi(MinutiP) - atoi(MinutiA);
	int SommaTot = MinutiOre + diffrenzaM;

	return SommaTot;
}

int NumPazientiConTempoAttesa(PrioritaV v[] ,CodaPazienti * PCoda,int dim, int tempo) 
{
	NodoPazienteT* aux = NULL;

	InizializzaCoda(PCoda);
	int TempoAttesa;
	for (int i = 0; i < dim; i++) 
	{
		aux = v[i].Pazienti.primo;
		while (aux != NULL) 
		{
			TempoAttesa = ContaTempoMinuti(aux->info.OraArrivo, aux->info.OraUscita);
			if (TempoAttesa > tempo) 
			{
				(*PCoda) = inserisci_coda((*PCoda), aux->info);
			}
			aux = aux->next;
		}
	}
	return 1;
}

void DisallocaCoda(CodaPazienti* PCoda) 
{
	NodoPazienteT* aux;
	while ((*PCoda).primo != NULL) 
	{
		aux = (*PCoda).primo;
		(*PCoda).primo = (*PCoda).primo->next;
		free(aux);
	}
}

int main() 
{
	int scelta;
	CodaPazienti CodaPazientiL;
	CodaPazienti listaOut;
	char NomeFile[64];
	PazienteT paziente;
	int NumeroMax, NumeroMin;
	float Media;
	int PazientiCaricati;
	int tempo;
	int esito;
	InizializzaCoda(&CodaPazientiL);
	PrioritaV VettorePriorita[10];
	for (int i = 0; i < 10; i++) 
	{
		VettorePriorita[i].NumeroTotalePazienti = 0;
		InizializzaCoda(&(VettorePriorita[i].Pazienti));
	}
	do 
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci i dati del paziente (Codice Fiscale, Orario Arrivo e Uscita e priorita'): ");
			scanf("%s %s %s %d", paziente.CodiceFiscale, paziente.OraArrivo, paziente.OraUscita, &paziente.PrioritaIniziale);
			CodaPazientiL = inserisci_coda(CodaPazientiL, paziente);
			break;
		case 2:
			printf("Inserisci nome del file: ");
			scanf("%s", NomeFile);
			CodaPazientiL = carica_lista(NomeFile, CodaPazientiL, &PazientiCaricati);
			if (CodaPazientiL.primo != NULL) 
			{
				VisualizzaCoda(CodaPazientiL);
			}
			break;
		case 3:
			esito = CreaListaPriorita(VettorePriorita, CodaPazientiL);
			break;
		case 4:
			esito = RestituisciNumeroMedioMaxMinPazienti(VettorePriorita, N, &NumeroMax, &Media, &NumeroMin);
			if (esito == 1)
				printf("Il numero massimo di pazienti e' %d, il minimo e' %d, il numero medio e' %.3f.\n", NumeroMax, NumeroMin, Media);
			break;
		case 5:
			VisualizzaVettorePriorita(VettorePriorita, N);
			break;
		case 6:
			printf("Inserisci la durata del tempo massima (in minuti): ");
			scanf("%d", &tempo);
			esito = NumPazientiConTempoAttesa(VettorePriorita, &listaOut, N, tempo);
			if (esito == 1)
				VisualizzaCoda(listaOut);
			printf("\n");
			break;
		}
	} while (scelta != 0);
}

