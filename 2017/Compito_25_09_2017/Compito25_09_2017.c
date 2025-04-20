/*
Implementare una applicazione console in linguaggio ANSI C che permetta di gestire l’organizzazione dei turni in sala operatoria in un ospedale.
In una prima fase i dati vengono raccolti in una lista di richieste (lista_richieste) nella quale è indicato il nome del paziente, 
il tempo previsto e l’urgenza dell’intervento. Poiché l’ospedale ha quattro camere operatorie, in una seconda fase i dati vengono letti
dalla lista delle richieste ed inserite nella coda di attesa (coda_attesa) di ogni sala operatoria garantendo che ogni sala operatoria 
non sia usata per più di 5 ore.
Specifica della struttura dati:
t_richiesta:
1. paziente: nome del paziente, rappresentato con una stringa senza caratteri bianchi, che può contenere al più 31 caratteri utili;
2. urgenza: valore intero positivo nell’intervallo [0,3], a valore maggiore corrisponde urgenza maggiore;
3. durata: indica la durata prevista in minuti dell’intervento.
L’insieme delle sale operatorie è implementato tramite un vettore di code di attesa o, in subordine e con una valutazione inferiore, come lista di sale operatorie.

Elenco delle operazioni/funzioni che devono essere implementate:
1. Funzione di inserimento in lista di una nuova richiesta. La funzione deve rispettare le seguenti specifiche:
nome della funzione: inserimento_richiesta;
valore restituito: nessuno;
parametri: dati della prenotazione, lista delle richieste
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica. La funzione non prevede nessuna interazione diretta con l’utente mediante tastiera, tutte le informazioni devono essere passate mediante gli argomenti della funzione. L’inserimento di un dialogo con l’utente (scanf, printf, ecc.) porta ad una valutazione nulla della funzione.
2. Salvataggio dei dati presenti nella lista delle richieste in un file di testo. La funzione deve rispettare le seguenti specifiche:
nome della funzione: salva_richieste;
valore restituito: numero di richieste salvate nel file;
parametri: descrittore del file (FILE *), coda delle prenotazioni.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica, La funzione non prevede nessuna interazione diretta con l’utente mediante tastiera, tutte le informazioni devono essere passate mediante gli argomenti della funzione. Il descrittore del file contiene il riferimento ad un file che deve essere già stato aperto nel programma chiamante;
3. Funzione di ricerca e di una prenotazione: dato il nome del paziente verificare se è presente in lista fornendo il numero il valore della durata prevista. 
La funzione deve rispettare le seguenti specifiche:
nome della funzione: verifica_richiesta;
valore restituito: 0 se il paziente non è presente, 1 altrimenti;
parametri: nome del paziente, lista delle richieste, durata dell’operazione
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica. La funzione non prevede nessuna interazione diretta con l’utente mediante tastiera, tutte le informazioni devono essere passate mediante gli argomenti della funzione
4. Funzione di riempimento delle code di attesa delle sale operatorie:
nome della funzione: carica_code;
L’algoritmo da implementare è il seguente: si scandisce la lista delle richieste selezionando inizialmente la priorità maggiore, e si procede ad inserire la richiesta nella prima coda dopo aver verificato che il tempo limite non sia stato superato, altrimenti si passa alla coda successiva fino all’esaurimento delle code, dopo l’inserimento in coda la richiesta deve essere cancellata dalla lista delle richieste. Si procede con lo stesso metodo a selezionare i pazienti con priorità inferiore (nota che avendo cancellato gli elementi non sono più presenti richieste con priorità maggiore) fino all’esaurimento delle richieste o del tempo a disposizione. Lo studente scelga i parametri e i valori di ritorno nel modo che ritiene più appropriato. Tutte le operazioni devono essere fatte in memoria centrale e non è prevista nessuna interazione diretta con l’utente mediante console.
5. Funzione che cancella dalla lista delle richieste un paziente dato il nome. 
Tutte le operazioni devono essere fatte in memoria centrale e non è prevista nessuna interazione diretta con l’utente mediante console;
6. Funzione che visualizza sullo schermo il contenuto dell’intera struttura dati implementata: nota che la stampa della struttura dati lista_richieste avrà una valutazione inferiore rispetto alla stampa della struttura che contiene le code di attesa.
7. Calcolo dell’occupazione media delle sale operatorie (deve essere calcolato il rapporto fra l’occupazione media delle quattro sale operatorie e la capienza)
8. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni implementate ed eventualmente di inserire i parametri necessari per eseguire le operazioni richieste.

Note:
1. Le funzioni 1, 2, 3 hanno come ingresso e uscita esclusivamente gli argomenti ed il tipo di ritorno, pertanto qualsiasi interazione con l’utente atta ad acquisire i dati o stampare i risultati deve essere implementata nel programma chiamante;
2. La funzione 2 prevede che venga passato come parametro il descrittore del file che si considera già correttamente aperto nel programma chiamante;
3. La specifica degli argomenti in ingresso o uscita delle funzioni indica quale informazione deve essere fornita non il tipo di dato ed il meccanismo di passaggio che deve essere scelto dallo studente;
4. La funzione 6 deve operare sulla struttura in memoria centrale e stampare il contenuto della struttura annidata, qualora si stampi solo il contenuto della lista dei pazienti la valutazione sarà inferiore;
5. Il file nell’esempio ha la funzione di definire il formato dei dati che deve essere rispettato alla lettera, il numero di elementi presenti non è soggetto ad alcun vincolo.
6. Tutte le operazioni, quando non specificato esplicitamente, devono essere effettuate in memoria centrale.

Esempio di file di di testo:
VERDI_CARLO // nome paziente
0 // urgenza
45 // durata
ROSSI_GUIDO
2
210
BIANCHI_ANGELO
3
60
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4

typedef struct SPaziente 
{
	char NomePaziente[32];
	int Urgenza; // [0;3]
	int durata;
} TPaziente;

typedef struct NodoRichiestaS 
{
	TPaziente info;
	struct NodoRichiestaS* next;
} NodoRichiestaT, * lista_richieste;

typedef struct CodaAttesaS 
{
	NodoRichiestaT* primo;
	NodoRichiestaT* ultimo;
} coda_attesa;

int InserisciElementoCoda(coda_attesa* Pcoda, TPaziente paziente) 
{
	NodoRichiestaT* aux = (NodoRichiestaT*)malloc(sizeof(NodoRichiestaT));
	if (aux == NULL)
		return 0;
	aux->info = paziente;
	aux->next = NULL;
	if ((*Pcoda).primo == NULL) 
	{
		(*Pcoda).primo = (*Pcoda).ultimo = aux;
	}
	else 
	{
		(*Pcoda).ultimo->next = aux;
		(*Pcoda).ultimo = aux;
	}
	return 1;
}

void inserimento_richiesta(lista_richieste * PListaRichieste, TPaziente Paziente) 
{
	NodoRichiestaT* aux = (NodoRichiestaT*)malloc(sizeof(NodoRichiestaT));
	if (aux == NULL)
		return;
	aux->info = Paziente;
	aux->next = (*PListaRichieste);
	(*PListaRichieste) = aux;
}

/*
2. Salvataggio dei dati presenti nella lista delle richieste in un file di testo. La funzione deve rispettare le seguenti specifiche:
nome della funzione: salva_richieste;
valore restituito: numero di richieste salvate nel file;
parametri: descrittore del file (FILE *), coda delle prenotazioni.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica,
La funzione non prevede nessuna interazione diretta con l’utente mediante tastiera, tutte le informazioni devono essere passate 
mediante gli argomenti della funzione. 
Il descrittore del file contiene il riferimento ad un file che deve essere già stato aperto nel programma chiamante;
*/

int salva_richieste(lista_richieste lista, FILE* fp) 
{
	int NumPazientiCaricati = 0;
	TPaziente info;
	while (lista != NULL) 
	{
		info = lista->info;
		if (fprintf(fp, "%s\n%d\n%d\n", info.NomePaziente, info.durata, info.Urgenza))
			NumPazientiCaricati++;
		else
			return 0;
		lista = lista->next;
	}
	fclose(fp);
	return NumPazientiCaricati;
}

/*
3. Funzione di ricerca e di una prenotazione: dato il nome del paziente verificare se è presente in lista fornendo il numero il valore della durata prevista.
La funzione deve rispettare le seguenti specifiche:
nome della funzione: verifica_richiesta;
valore restituito: 0 se il paziente non è presente, 1 altrimenti;
parametri: nome del paziente, lista delle richieste, durata dell’operazione
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
La funzione non prevede nessuna interazione diretta 
con l’utente mediante tastiera, tutte le informazioni devono essere passate mediante gli argomenti della funzione
*/

int verifica_richiesta(lista_richieste richieste, char * nome_paziente, int durata)
{
	if (richieste == NULL)
		return 0;

	int esito = 0;
	while (richieste != NULL) 
	{
		if ((strcmp(richieste->info.NomePaziente, nome_paziente) == 0) && (richieste->info.durata == durata))
		{
			esito = 1;
		}
		richieste = richieste->next;
	}
	return esito;
}

/*
5. Funzione che cancella dalla lista delle richieste un paziente dato il nome.
Tutte le operazioni devono essere fatte in memoria centrale e non è prevista nessuna interazione diretta con l’utente mediante console;
*/

int CancellaPaziente(lista_richieste* Lista, char* NomePaziente) 
{
	NodoRichiestaT* aux;
	if ((*Lista) == NULL)
		return 0;
	if (strcmp((*Lista)->info.NomePaziente, NomePaziente) == 0)
	{
		aux = (*Lista);
		(*Lista) = (*Lista)->next;
		free(aux);
		return 1;
	}
	else
		return CancellaPaziente(&((*Lista)->next), NomePaziente);
}

/*
4. Funzione di riempimento delle code di attesa delle sale operatorie:
nome della funzione: carica_code;
L’algoritmo da implementare è il seguente: si scandisce la lista delle richieste selezionando inizialmente la priorità maggiore,
e si procede ad inserire la richiesta nella prima coda dopo aver verificato che il tempo limite non sia stato superato,
altrimenti si passa alla coda successiva fino all’esaurimento delle code, dopo l’inserimento in coda la richiesta deve
essere cancellata dalla lista delle richieste. Si procede con lo stesso metodo a selezionare i pazienti con priorità inferiore
(nota che avendo cancellato gli elementi non sono più presenti richieste con priorità maggiore) fino all’esaurimento delle richieste o del tempo a disposizione.
Lo studente scelga i parametri e i valori di ritorno nel modo che ritiene più appropriato.
Tutte le operazioni devono essere fatte in memoria centrale e non è prevista nessuna interazione diretta con l’utente mediante console.
*/

int carica_code(lista_richieste* Lista, coda_attesa v[])
{
	if ((*Lista) == NULL)
		return 0;
	lista_richieste corrente;  // utilizzo la variabile corrente che mi permette di confrontare ciascun elemento e vedere se effettivamente rispetti la condizione
	while ((*Lista) != NULL) 
	{
		corrente = (*Lista);
		if (corrente->info.durata <= 300)
		{
			if (InserisciElementoCoda(&v[corrente->info.Urgenza], corrente->info))
			{
				(*Lista) = corrente->next;
				free(corrente);
			}
			else
				return 0;
		}
		else 
		{
			(*Lista) = (*Lista)->next; // faccio puntare Lista all'indirizzo dell'elemento successivo
		}
	}
	return 1;
}

void VisualizzaLista(lista_richieste Lista) 
{
	while (Lista != NULL) 
	{
		printf("%s %d %d\n", Lista->info.NomePaziente, Lista->info.durata, Lista->info.Urgenza);
		Lista = Lista->next;
	}
}

float CalcoloOccupazioneMedia(coda_attesa v[], int dim) 
{
	int Contatore = 0;
	NodoRichiestaT* aux;
	for (int i = 0; i < dim; i++) 
	{
		aux = v[i].primo;
		while (aux != NULL) 
		{
			Contatore++;
			aux = aux->next;
		}
	}
	float media = (float)(Contatore) / (float)(dim);
	return media;
}

void VisualizzaVCode(coda_attesa v[], int dim) 
{
	for (int i = 0; i < dim; i++) 
	{
		printf("Urgenza %d:\n", i);
		while (v[i].primo != NULL) 
		{
			printf("%s %d %d\n", v[i].primo->info.NomePaziente, v[i].primo->info.durata, v[i].primo->info.Urgenza);
			v[i].primo = v[i].primo->next;
		}
		printf("\n");
	}
}

int Menu() 
{
	int scelta;
	printf("******** MENU ********\n"
		"1. Inserisci nuova richiesta.\n"
		"2. Salva dati nel file di testo.\n"
		"3. Ricerca la prenotazione.\n"
		"4. Riempi le code di attesa.\n"
		"5. Cancella un paziente dalla lista delle richieste.\n"
		"6. Visualizza tutto.\n"
		"7. Calcolo occupazione media.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

void InizializzaCoda(coda_attesa* coda) 
{
	(*coda).primo = (*coda).ultimo = NULL;
}

int main() 
{
	int scelta;
	TPaziente paziente;
	char NomePaziente[32];
	lista_richieste Richieste = NULL;
	float OccupazioneMedia;
	coda_attesa VettoreCode[N];
	for (int i = 0; i < N; i++)
	{
		InizializzaCoda(&VettoreCode[i]);
	}
	int NumPazienti;
	char NomeFile[64];
	int Durata;
	int esito;
	do 
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci i dati del paziente (NOME, DURATA E URGENZA): ");
			scanf("%s %d %d", paziente.NomePaziente, &paziente.durata, &paziente.Urgenza);
			inserimento_richiesta(&Richieste, paziente);
			VisualizzaLista(Richieste);
			printf("\n");
			break;
		case 2:
			printf("Inserisci il nome del file su cui vuoi scrivere i dati: ");
			scanf("%s", NomeFile);
			FILE* fp = fopen(NomeFile, "w");
			NumPazienti = salva_richieste(Richieste, fp);
			if (NumPazienti != 0)
				printf("Sono stati caricati %d pazienti.\n", NumPazienti);
			break;
		case 3:
			printf("Inserisci il nome del paziente: ");
			scanf("%s", NomePaziente);
			printf("Inserisci la durata: ");
			scanf("%d", &Durata);
			esito = verifica_richiesta(Richieste, NomePaziente, Durata);
			if (esito == 1)
				printf("Paziente trovato.\n");
			else
				printf("Il paziente non e' presente nella lista.\n");
			break;
		case 4:
			esito = carica_code(&Richieste, VettoreCode);
			if (esito == 1)
			{
				printf("Elementi caricati con successo.\n");
			}
			break;
		case 5:
			printf("Inserisci il nome del paziente: ");
			scanf("%s", NomePaziente);
			esito = CancellaPaziente(&Richieste, NomePaziente);
			if (esito == 1)
			{
				printf("Paziente cancellato con successo.\n");
				VisualizzaLista(Richieste);
			}
			printf("\n");
			break;
		case 6:
			VisualizzaVCode(VettoreCode, N);
			break;
		case 7:
			OccupazioneMedia = CalcoloOccupazioneMedia(VettoreCode, N);
			printf("L'occupazione media e' di %.3f.\n", OccupazioneMedia);
			break;
		}
	} while (scelta != 0);

}