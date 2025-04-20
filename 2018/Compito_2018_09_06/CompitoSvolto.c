/*
Implementare una applicazione console in linguaggio ANSI C per la gestione delle iscrizioni in una palestra. L’applicazione ha il compito di gestire le iscrizioni, le organizzazione dei corsi e i relativi incassi.
Ogni iscrizione è univocamente identificata da un codiceIscrizione Il programma carica inizialmente l’archivio dei dati da un file di testo (un esempio è fornito nel seguito) in una lista semplice (lista_iscrizione) e successivamente copia il contenuto in una lista (lista_attivita) in cui ogni nodo contiene il nome dell’attività e gli iscritti di quella attività.
Il codiceTessera individua unicamente una persona. Per la stessa persona possono essere presenti più iscrizioni a diverse attività con codiceIscrizione diverso.
Specifica della struttura dati:
Iscrizione, (elemento della lista_iscrizione):
 codiceIscrizione (stringa di 12 caratteri utili)
 eta (intero)
 Cognome (stringa di 20 caratteri utili senza spazi)
 codiceTessera (stringa di 6 caratteri)
 attivita (stringa di 12 caratteri utili)
Elemento della lista_attivita:
 attività (stringa di 12 caratteri utili)
 elenco degli iscritti per tale attività (lista degli iscritti a tale attività)
 numero degli iscritti con meno di 18 anni
Elenco delle operazioni/funzioni che devono essere implementate:
(Lo studente noti che il non rispetto delle specifiche nei quesiti 1 e 2, quindi la scelta di un nome della funzione diverso, di parametri differenti o di valori di ritorno differenti sono considerati errori gravi a prescindere del fatto che la funzione svolga quanto richiesto).
1. Funzione di caricamento da file di testo dei dati contenuti nel file. La funzione da implementare deve rispettare la seguente specifica:
nome della funzione: carica_iscrizioni;
valore restituito: numero di elementi caricati
parametri: nome del file, lista delle iscrizioni
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica
2. Funzione di modifica dell’attività (devono essere aggiornate tutte le istanze della attività, cioè tutte quelle con lo stesso nome attività). Specifica della funzione:
nome della funzione: modifica_iscrizioni
valore restituito: 0 se non sono state effettuate modifiche 1 se è stata effettuata almeno una modifica;
parametri: lista_info, attivitaVecchia, nuovaAttività, numero di istanze modificate.
(NB: il numero di istanze modificate è un parametro di uscita che la funzione deve produrre e non visualizzare).
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
3. Funzione di creazione della lista di liste: Crea la lista delle iscrizioni separate per attività (lista_attivita) a partire dalla lista_iscrizione. Ogni elemento della lista delle attività contiene il nome dell’attività, il numero degli iscritti con meno di 18 anni e la lista completa degli iscritti a tale attività.
4. Ricerca della attività con più iscritti Funzione che, operando sulla lista delle attività restituisce il nome dell’attività con più iscritti
e quella con più iscritti con meno di 18 anni. Nell’ipotesi di più attività con lo stesso valore di iscritti restituisce la prima trovata;
5. Funzione che visualizza il contenuto dell’intera lista_attività
6. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni implementate ed eventualmente di inserire i parametri necessari ad eseguire le operazioni richieste.


I123 pallavolo
T1 12 Amato
I234 basket
T3 20 Pappalardo
I345 calcio
T34 23 Papale
T789 calcio
T1 12 Amato
I989 pallavolo
T2 21 Dante
I231 hockey
T56 13 Manzoni
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct IscrittoS 
{
	char codiceIscrizione[13];
	int eta;
	char Cognome[21];
	char codiceTessera[6];
	char attivita[13];
} IscrittoT;

typedef struct NodoIscrittoS 
{
	IscrittoT info;
	struct NodoIscrittoS* next;
} NodoIscrittoT, *lista_iscrizione;

typedef struct NodoAttivitaS 
{
	char attivita[13];
	lista_iscrizione elenco;
	int numero_minorenni;
	struct NodoAttivitaS* next;
} NodoAttivitaT, *lista_attivita;

int InserisciNodoIscritto(lista_iscrizione* plista, IscrittoT i) 
{
	NodoIscrittoT* aux = (NodoIscrittoT*)malloc(sizeof(NodoIscrittoT));
	if (aux == NULL)
		return 0;
	aux->info = i;
	aux->next = (*plista);
	(*plista) = aux;
	return 1;
}

int carica_iscrizioni(lista_iscrizione* plista, char* nomefile) 
{
	FILE* fp = fopen(nomefile, "r");
	if (fp == NULL)
		return 0;
	int num = 0;
	IscrittoT i;
	while (fscanf(fp, "%s%s", i.codiceIscrizione, i.attivita) == 2)
	{
		if (fscanf(fp, "%s%d%s", i.codiceTessera, &i.eta, i.Cognome) != 3) 
		{
			fclose(fp);
			return 0;
		}
		if (!InserisciNodoIscritto(plista, i))
			return 0;
		else
			num++;
	}
	return num;
}

/*
2. Funzione di modifica dell’attività (devono essere aggiornate tutte le istanze della attività, cioè tutte quelle con lo stesso nome attività).
Specifica della funzione:
nome della funzione: modifica_iscrizioni
valore restituito: 0 se non sono state effettuate modifiche 1 se è stata effettuata almeno una modifica;
parametri: lista_info, attivitaVecchia, nuovaAttività, numero di istanze modificate.
(NB: il numero di istanze modificate è un parametro di uscita che la funzione deve produrre e non visualizzare).
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/

int modifica_iscrizioni(lista_iscrizione listaIscrizioni, char* vecchiaAttivita, char* nuovaAttivita, int *NumeroIstanze) 
{
	(*NumeroIstanze) = 0;
	while (listaIscrizioni != NULL) 
	{
		if (strcmp(listaIscrizioni->info.attivita, vecchiaAttivita) == 0) 
		{
			strcpy(listaIscrizioni->info.attivita, nuovaAttivita);
			(*NumeroIstanze)++;
		}
		listaIscrizioni = listaIscrizioni->next;
	}
	return 1;
}

/*
3. Funzione di creazione della lista di liste: Crea la lista delle iscrizioni separate per attività (lista_attivita) a partire dalla lista_iscrizione. 
Ogni elemento della lista delle attività contiene il nome dell’attività, il numero degli iscritti con meno di 18 anni e la lista completa degli iscritti 
a tale attività.
*/

int CreazioneListaIscrizioni(lista_attivita* attivita, lista_iscrizione Lista)
{
	lista_iscrizione iscrizioni = Lista;
	lista_attivita corrente = NULL;
	while (iscrizioni != NULL) 
	{
		corrente = (*attivita);
		int trovato = 0;
		while (corrente != NULL) 
		{
			if (strcmp(corrente->attivita, iscrizioni->info.attivita) == 0) 
			{
				trovato = 1;
				break;
			}
			corrente = corrente->next;
		}
		if (trovato == 1) 
		{
			if (iscrizioni->info.eta < 18)
				corrente->numero_minorenni++;
			if(!InserisciNodoIscritto(&(corrente->elenco), iscrizioni->info))
				return 0;
		}
		else 
		{
			NodoAttivitaT* aux = (NodoAttivitaT*)malloc(sizeof(NodoAttivitaT));
			if (aux == NULL)
				return 0;
			aux->elenco = NULL;
			if(!InserisciNodoIscritto(&(aux->elenco), iscrizioni->info))
				return 0;
			aux->numero_minorenni = 0;
			if (iscrizioni->info.eta < 18)
				aux->numero_minorenni++;
			strcpy(aux->attivita, iscrizioni->info.attivita);
			aux->next = (*attivita);
			(*attivita) = aux;
		}
		iscrizioni = iscrizioni->next;
	}
	return 1;
}

/*
4. Ricerca della attività con più iscritti Funzione che, operando sulla lista delle attività restituisce il nome dell’attività con più iscritti
e quella con più iscritti con meno di 18 anni. Nell’ipotesi di più attività con lo stesso valore di iscritti restituisce la prima trovata;
*/

int AttivitaPiuIscritti(lista_attivita attivita, lista_attivita* MaxNumIscritti, lista_attivita* MaxNumMin) 
{
	lista_attivita aux = attivita;

	strcpy(((*MaxNumIscritti)->attivita), "");
	(*MaxNumIscritti)->next = NULL;
	(*MaxNumIscritti)->elenco = NULL;
	(*MaxNumIscritti)->numero_minorenni = 0;

	strcpy(((*MaxNumMin)->attivita), "");
	(*MaxNumMin)->next = NULL;
	(*MaxNumMin)->elenco = NULL;
	(*MaxNumMin)->numero_minorenni = 0;

	int contatore;
	int max = 0;
	int maxmin = aux->numero_minorenni;


	while (aux != NULL)
	{
		contatore = 0;
		while (aux->elenco != NULL)
		{
			contatore++;
			aux->elenco = aux->elenco->next;
		}
		if (contatore > max)
		{
			max = contatore;
			strcpy((*MaxNumIscritti)->attivita, aux->attivita);
			(*MaxNumIscritti)->next = NULL;
			(*MaxNumIscritti)->elenco = NULL;
			(*MaxNumIscritti)->numero_minorenni = aux->numero_minorenni;
		}
		if (aux->numero_minorenni > maxmin)
		{
			maxmin = aux->numero_minorenni;
			strcpy((*MaxNumMin)->attivita, aux->attivita);
			(*MaxNumMin)->next = NULL;
			(*MaxNumMin)->elenco = NULL;
			(*MaxNumMin)->numero_minorenni = aux->numero_minorenni;
		}
		aux = aux->next;
	}
	return 1;
}

void VisualizzaLista(lista_iscrizione lista) 
{
	while (lista != NULL) 
	{
		printf("%s %s %s %s %d\n", lista->info.Cognome, lista->info.attivita, lista->info.codiceIscrizione, lista->info.codiceTessera, lista->info.eta);
		lista = lista->next;
	}
}

void VisualizzaAttivita(lista_attivita attivita) 
{
	while (attivita != NULL) 
	{
		printf("ATTIVITA: %s // NUMERO MINORENNI: %d\n\nELENCO ISCRITTI:\n", attivita->attivita, attivita->numero_minorenni);
		VisualizzaLista(attivita->elenco);
		printf("\n");
		attivita = attivita->next;
	}
}

int Menu() 
{
	int scelta;
	printf("******** MENU ********\n"
		"1. Carica iscrizioni.\n"
		"2. Modifica iscrizioni.\n"
		"3. Crea lista iscrizioni.\n"
		"4. Ricerca attività con piu' iscritti.\n"
		"5. Visualizza tutto.\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

int main() 
{
	int scelta;
	lista_attivita ListaAttivita = NULL;
	lista_iscrizione ListaIscrizioni = NULL;
	char NomeFile[64];

	lista_attivita MaxNumMinorenni = (NodoAttivitaT*)malloc(sizeof(NodoAttivitaT));
	lista_attivita MaxNumIscritti = (NodoAttivitaT*)malloc(sizeof(NodoAttivitaT));

	int NumIscritti;
	char VecchiaAttivita[13];
	char NuovaAttivita[13];
	int Istanze = 0;
	int esito;

	do
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			NumIscritti = carica_iscrizioni(&ListaIscrizioni, NomeFile);
			if (NumIscritti != 0) 
			{
				printf("Sono stati caricati %d iscritti.\n", NumIscritti);
			}
			break;
		case 2:
			if (ListaIscrizioni != NULL) 
			{
				printf("Inserisci la vecchia attivita': ");
				scanf("%s", VecchiaAttivita);
				printf("Inserisci la nuova attivita': ");
				scanf("%s", NuovaAttivita);
				esito = modifica_iscrizioni(ListaIscrizioni, VecchiaAttivita, NuovaAttivita, &Istanze);
				if (esito == 1)
					printf("Sono state modificate %d istanze.\n", Istanze);
			}
			break;
		case 3:
			esito = CreazioneListaIscrizioni(&ListaAttivita, ListaIscrizioni);
			if (esito == 1)
				printf("Creazione lista avvenuta con successo.\n");
			break;
		case 4:
			if (ListaAttivita != NULL) 
			{
				esito = AttivitaPiuIscritti(ListaAttivita, &MaxNumIscritti, &MaxNumMinorenni);
				if (esito == 1)
				{
					printf("L'attivita' con piu' iscritti e' %s, quella con piu' minorenni e' %s.\n", MaxNumIscritti->attivita, MaxNumMinorenni->attivita);
				}
			}
			break;
		case 5:
			if (ListaAttivita != NULL)
				VisualizzaAttivita(ListaAttivita);
			break;
		}
	} while (scelta != 0);

}