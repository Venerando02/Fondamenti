/*
Implementare una applicazione console in linguaggio ANSI C per la gestione degli iscritti in una palestra. La palestra propone 5 turni.
Le informazioni di ogni iscritto sono memorizzate in un file (specificato nel seguito) e caricate in una lista di iscritti. In un momento
successivo, l’applicazione dovrà organizzare le informazioni degli iscritti in una lista di turni in cui ogni elemento della lista contiene,
oltre all’identificativo del turno, anche l’elenco degli iscritti a quel turno ed il loro numero.
Specifica della struttura dati:
Iscritto:
1. Cognome (stringa di 15 caratteri)
2. Data di nascita (stringa nel formato anno-mese-giorno) // aaaa-mm-gg
3. Numero Turno (numero intero)
Turno:
1. Numero turno (numero intero)
2. Numero di iscritti (numero intero)
3. Elenco degli iscritti (lista di Iscritto)
Elenco delle operazioni/funzioni che devono essere implementate:
1. Funzione di caricamento da file di testo degli iscritti nella lista degli iscritti. La funzione da implementare deve avere la
seguente struttura:
nome della funzione: CaricaIscritti;
valore restituito: numero di iscritti caricati;
parametri: nome del file, lista degli iscritti.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
2. Funzione di modifica turno di un iscritto. La funzione da implementare deve avere la seguente struttura:
nome della funzione: ModificaTurno;
valore restituito: esito operazione (0: operazione fallita, 1: modifica effettuata con successo);
parametri: lista degli iscritti, cognome iscritto, nuovo turno.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
3. Funzione di eliminazione di un iscritto dalla lista. La funzione da implementare deve avere la seguente struttura:
nome della funzione: EliminaIscritto;
valore restituito: esito operazione (0: operazione fallita, 1: eliminazione effettuata con successo);
parametri: lista degli iscritti, cognome iscritto.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
4. CreazioneTurni: Crea la lista dei turni a partire dalla lista degli iscritti. Ogni elemento della lista dei turni dovrà contenere
l’identificativo del turno, il numero degli iscritti a quel turno e la lista degli iscritti a quel turno. Lo studente scelga la struttura
della funzione, il tipo dei dati ed i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
5. TurnoPiuAffollato: Funzione che, operando sulla lista dei turni, restituisca il turno con il maggior numero di iscritti.
6. EtaMedia: Funzione che, operando sulla lista dei turni, e preso in ingresso un numero di turno, restituisca l’età media degli
iscritti a quel turno.
7. Funzione che visualizza il contenuto dell’intera lista dei turni.
8. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni implementate ed
eventualmente di inserire i parametri necessari ad eseguire le operazioni richieste.
Struttura del file degli iscritti
Le informazioni nel file per ciascun iscritto si trovano distribuite su una riga:
Cognome DataDiNascita Turno

Esempio di file:

Rossi 1980-12-11 3
Ferrari 1975-06-15 1
Esposito 1990-10-27 2
Bianchi 1965-09-01 2
Romano 1992-11-15 4
Marino 1985-02-15 5
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 5

typedef struct IscrittoS 
{
	char Cognome[15];
	char DataNascita[11];
	int NumeroTurno;
} IscrittoT;

typedef struct NodoIscrittoS 
{
	IscrittoT info;
	struct NodoIscrittoS* next;
} NodoIscrittoT, * ListaIscritti;

typedef struct TurnoS 
{
	int NumeroTurno;
	int NumeroIscritti;
	ListaIscritti ElencoIscritti;
} TurnoT;

int InserisciNodoIscritto(ListaIscritti* PLista, IscrittoT Iscritto) 
{
	NodoIscrittoT* aux = (NodoIscrittoT*)malloc(sizeof(NodoIscrittoT));
	if (aux == NULL)
		return 0;
	aux->info = Iscritto;
	aux->next = (*PLista);
	(*PLista) = aux;
	return 1;
}

/*
1. Funzione di caricamento da file di testo degli iscritti nella lista degli iscritti. La funzione da implementare deve avere la
seguente struttura:
nome della funzione: CaricaIscritti;
valore restituito: numero di iscritti caricati;
parametri: nome del file, lista degli iscritti.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/

int CaricaIscritti(ListaIscritti* PLista, char* NomeFile) 
{
	FILE* fp = fopen(NomeFile, "r");
	if (fp == NULL)
		return 0;
	int Num = 0;
	IscrittoT I;
	while (fscanf(fp, "%s%s%d", I.Cognome, I.DataNascita, &I.NumeroTurno) == 3) 
	{
		if (!InserisciNodoIscritto(PLista, I))
			return 0;
		else 
			Num++;
	}
	return Num;
}

/*
2. Funzione di modifica turno di un iscritto. La funzione da implementare deve avere la seguente struttura:
nome della funzione: ModificaTurno;
valore restituito: esito operazione (0: operazione fallita, 1: modifica effettuata con successo);
parametri: lista degli iscritti, cognome iscritto, nuovo turno.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/

int ModificaTurno(ListaIscritti Lista, char* CognomeIscritto, int NuovoTurno) 
{
	if (Lista == NULL)
		return 0;
	while (Lista != NULL) 
	{
		if (strcmp(Lista->info.Cognome, CognomeIscritto) == 0) 
		{
			Lista->info.NumeroTurno = NuovoTurno;
		}
		Lista = Lista->next;
	}
	return 1;
}

/*
3. Funzione di eliminazione di un iscritto dalla lista. La funzione da implementare deve avere la seguente struttura:
nome della funzione: EliminaIscritto;
valore restituito: esito operazione (0: operazione fallita, 1: eliminazione effettuata con successo);
parametri: lista degli iscritti, cognome iscritto.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/

int EliminaIscritto(ListaIscritti* Lista, char* CognomeIscritto) 
{
	if ((*Lista) == NULL)
		return 0;
	NodoIscrittoT* aux;
	if (strcmp((*Lista)->info.Cognome, CognomeIscritto) == 0)
	{
		aux = (*Lista);
		(*Lista) = (*Lista)->next;
		free(aux);
		return 1;
	}
	else
		return EliminaIscritto(&((*Lista)->next), CognomeIscritto);
}

/*
4. CreazioneTurni: Crea la lista dei turni a partire dalla lista degli iscritti. Ogni elemento della lista dei turni dovrà contenere
l’identificativo del turno, il numero degli iscritti a quel turno e la lista degli iscritti a quel turno. Lo studente scelga la struttura
della funzione, il tipo dei dati ed i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/


// Siccome dai dati sapevamo che i turni fossero un numero definito ovvero 5, decidiamo di implementare un vettore di Liste

int CreazioneTurni(TurnoT Vettore[], ListaIscritti Lista) 
{
	NodoIscrittoT* aux = Lista;
	if (Lista == NULL)
		return 0;
	while (aux != NULL) 
	{
		Vettore[(aux->info.NumeroTurno - 1)].NumeroTurno = aux->info.NumeroTurno;
		if (!InserisciNodoIscritto(&(Vettore[(aux->info.NumeroTurno - 1)].ElencoIscritti), aux->info))
			return 0;
		else
			Vettore[(aux->info.NumeroTurno - 1)].NumeroIscritti++;
		aux = aux->next;
	}
	return 1;
}
/*
5. TurnoPiuAffollato: Funzione che, operando sulla lista dei turni, restituisca il turno con il maggior numero di iscritti.
*/
int TurnoPiuAffollato(TurnoT v[], int dim) 
{
	int TurnoAffollato;
	int n = v[0].NumeroIscritti;
	for (int i = 0; i < dim; i++) 
	{
		if (v[i].NumeroIscritti > n) 
		{
			n = v[i].NumeroIscritti;
			TurnoAffollato = v[i].NumeroTurno;
		}
	}
	return TurnoAffollato;
}

int TrovaEta(char* DataNascita) 
{
	char Anno[5];
	strncpy(Anno, DataNascita, 4);
	Anno[4] = "\0";
	int Eta = 2024 - atoi(Anno);
	return Eta;
}

/*
6. EtaMedia: Funzione che, operando sulla lista dei turni, e preso in ingresso un numero di turno, restituisca l’età media degli
iscritti a quel turno.
*/

float EtaMedia(TurnoT v[], int dim, int turno) 
{
	NodoIscrittoT* aux;
	int etatot = 0;
	int cont = 0;
	int Eta;
	for (int i = 0; i < dim; i++) 
	{
		if (v[i].NumeroTurno == turno) 
		{
			aux = v[i].ElencoIscritti;
			while (aux != NULL) 
			{
				Eta = TrovaEta(aux->info.DataNascita);
				etatot += Eta;
				aux = aux->next;
				cont++;
			}
		}
	}
	float MediaEta = (float)(etatot)/(float)(cont);
	return MediaEta;
}

int Menu() 
{
	int scelta;
	printf("******** MENU ********\n"
		"1. Carica dati da file.\n"
		"2. Modifica turno.\n"
		"3. Elimina iscritto\n"
		"4. Crea turni.\n"
		"5. Trova turno piu' affollato.\n"
		"6. Trova qual e' l'eta' media.\n"
		"7. Visualizza tutto.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

void VisualizzaListaIscritti(ListaIscritti Iscritti) 
{
	while (Iscritti != NULL) 
	{
		printf("%s %s %d\n", Iscritti->info.Cognome, Iscritti->info.DataNascita, Iscritti->info.NumeroTurno);
		Iscritti = Iscritti->next;
	}
}

void VisualizzaTurni(TurnoT Vettore[], int dim) 
{
	ListaIscritti aux;
	for (int i = 0; i < dim; i++) 
	{
		printf("NUMERO TURNO: %d // NUMERO ISCRITTI: %d\n\nELENCO ISCRITTI:\n", Vettore[i].NumeroTurno, Vettore[i].NumeroIscritti);
		aux = Vettore[i].ElencoIscritti;
		VisualizzaListaIscritti(aux);
		printf("\n");
	}
}


int main() 
{
	int scelta;
	ListaIscritti ElencoIscritti = NULL;
	TurnoT Vettore[N];
	for (int i = 0; i < N; i++)
	{
		Vettore[i].ElencoIscritti = NULL;
		Vettore[i].NumeroIscritti = 0;
		Vettore[i].NumeroTurno = 0;
	}
	float MediaEta;
	char NomeFile[64];
	char CognomeIscritto[15];
	int NumIscritti;
	int NumTurno;
	int Turno;
	int esito;
	do 
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			NumIscritti = CaricaIscritti(&ElencoIscritti, NomeFile);
			if (NumIscritti != 0)
				printf("Sono stati caricati %d iscritti.\n", NumIscritti);
			break;
		case 2:
			do {
				printf("Inserisci il numero di turno: ");
				scanf("%d", &Turno);
			} while (Turno >= 5);
			printf("Inserisci il cognome dell'iscritto: ");
			scanf("%s", CognomeIscritto);
			esito = ModificaTurno(ElencoIscritti, CognomeIscritto, Turno);
			if (esito == 1)
				printf("Turno modificato con successo.\n");
			break;
		case 3:
			printf("Inserisci il cognome dell'iscritto: ");
			scanf("%s", CognomeIscritto);
			esito = EliminaIscritto(&ElencoIscritti, CognomeIscritto);
			if (esito == 1)
				printf("Utente eliminato con successo.\n");
			VisualizzaListaIscritti(ElencoIscritti);
			break;
		case 4:
			esito = CreazioneTurni(Vettore, ElencoIscritti);
			if (esito == 1)
				printf("Turni creati con successo.\n");
			break;
		case 5:
			NumTurno = TurnoPiuAffollato(Vettore, N);
			printf("Il turno piu' affollato e' %d.\n", NumTurno);
			break;
		case 6:
			do {
				printf("Inserisci il numero di turno: ");
				scanf("%d", &Turno);
			} while (Turno >= 5);
			MediaEta = EtaMedia(Vettore, N, Turno);
			printf("l'eta' media e' %.3f.\n", MediaEta);
			break;
		case 7:
			VisualizzaTurni(Vettore, N);
			break;
		}
	} while (scelta != 0);
}