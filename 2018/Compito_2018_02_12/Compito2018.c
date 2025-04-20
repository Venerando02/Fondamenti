/*
Implementare una applicazione console in linguaggio ANSI C per la gestione dei turni in un laboratorio composto da 50 postazioni con PC per gli studenti prenotati
all’esame di fondamenti di informatica. 
Le generalità degli studenti prenotati sono memorizzate in un file (specificato nel seguito) e caricate in una lista di prenotati. In un momento successivo, 
l’applicazione dovrà allocare gli studenti in una lista di turni in cui ogni elemento della lista contiene, oltre all’identificativo del turno, 
anche l’elenco degli studenti allocati in quel turno.
Specifica della struttura dati:
Prenotato:
1. Cognome (stringa di 15 caratteri)
2. Nome (stringa di 15 caratteri)
3. Matricola (stringa di 10 caratteri)
Turno:
1. Numero turno (numero intero)
2. Elenco dei prenotati (lista di Prenotato)

Elenco delle operazioni/funzioni che devono essere implementate:
1. Funzione di caricamento da file di testo dei prenotati nella lista degli studenti. La funzione da implementare deve avere la seguente struttura:
nome della funzione: CaricaPrenotati;
valore restituito: numero di prenotati caricati;
parametri: nome del file, lista dei prenotati.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
2. Funzione di modifica turno tra due studenti. Scambia tra loro due studenti (appartenenti a turni diversi). La funzione da implementare deve avere la seguente struttura:
nome della funzione: ScambioTurno;
valore restituito: esito operazione (0: operazione fallita, 1: modifica effettuata con successo);
parametri: lista dei prenotati, matricola studente 1, matricola studente 2.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
3. Funzione di eliminazione di un prenotato dalla lista. La funzione da implementare deve avere la seguente struttura:
nome della funzione: EliminaPrenotato;
valore restituito: esito operazione (0: operazione fallita, 1: eliminazione effettuata con successo);
parametri: lista dei prenotati, matricola.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
4. CreazioneTurni: Crea la lista dei turni a partire dalla lista dei prenotati. Ogni elemento della lista dei turni dovrà contenere 
l’identificativo del turno e la lista dei prenotati afferenti a quel turno. I prenotati vengono allocati secondo
l’ordine in cui appaiono nella lista dei prenotati a partire dal primo turno. 
Quando il numero di prenotati allocati al primo turno raggiunge la capienza del laboratorio (50 postazioni),
si procede l’allocazione al secondo turno e così via. Lo studente scelga la struttura della funzione, il tipo dei dati
ed i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
5. CambioTurno: Funzione che, operando sulla lista dei turni, effettui lo spostamento di uno studente da un turno ad un altro solo se tale spostamento rispetti il vincolo di capienza del laboratorio.
6. OccupazioneMedia: Funzione che, operando sulla lista dei turni, restituisca l’occupazione media del laboratorio.
7. Funzione che visualizza il contenuto dell’intera lista dei turni.
8. Programma principale dotato di un menù testuale che permetta all’utente di usare tutte le funzioni implementate ed eventualmente di inserire i parametri necessari ad eseguire le operazioni richieste.
Struttura del file dei prenotati
Le informazioni nel file per ciascun iscritto si trovano distribuite su una riga:
Cognome Nome Matricola
Esempio di file:
Rossi Giuseppe O46000123
Bianchi Luigi O45000321
Russo Giovanna O46000213
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50

typedef struct PrenotatoS 
{
	char Cognome[15];
	char Nome[15];
	char Matricola[10];
} PrenotatoT;

typedef struct NodoPrenotatoS 
{
	PrenotatoT info;
	struct NodoPrenotatoS* next;
} NodoPrenotatoT, * ListaPrenotati;

typedef struct NodoTurnoS 
{
	int NumeroTurno;
	ListaPrenotati prenotati;
	struct NodoTurnoS* next;
} NodoTurnoT, *ListaTurni;

int InserisciStudenteLista(ListaPrenotati* prenotati, PrenotatoT studente) 
{
	NodoPrenotatoT* aux = (NodoPrenotatoT*)malloc(sizeof(NodoPrenotatoT));
	if (aux == NULL)
		return 0;
	aux->info = studente;
	aux->next = (*prenotati);
	(*prenotati) = aux;
	return 1;
}

int CaricaDatiFile(ListaPrenotati* prenotati, char* NomeFile) 
{
	int n = 0;
	FILE* fp = fopen(NomeFile, "r");
	if (fp == NULL)
		return 0;
	PrenotatoT p;
	while (fscanf(fp, "%s%s%s", p.Cognome, p.Nome, p.Matricola) == 3) 
	{
		if (!InserisciStudenteLista(prenotati, p))
			return 0;
		else
			n++;
	}
	fclose(fp);
	return n;
}

/*
2. Funzione di modifica turno tra due studenti. Scambia tra loro due studenti (appartenenti a turni diversi). 
La funzione da implementare deve avere la seguente struttura:
nome della funzione: ScambioTurno;
valore restituito: esito operazione (0: operazione fallita, 1: modifica effettuata con successo);
parametri: lista dei prenotati, matricola studente 1, matricola studente 2.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/

int ScambioTurno(ListaTurni* lista, char * CodiceStudente1, char * CodiceStudente2) 
{
	ListaTurni turni;
	if ((*lista) == NULL)
		return 0;
	turni = (*lista);
	ListaPrenotati pren;
	PrenotatoT st1, st2;
	strcpy(st1.Cognome, "");
	strcpy(st1.Matricola, "");
	strcpy(st1.Nome, "");
	strcpy(st2.Cognome, "");
	strcpy(st2.Matricola, "");
	strcpy(st2.Nome, "");
	while (turni != NULL) 
	{
		pren = turni->prenotati;
		while (pren != NULL) 
		{
			if (strcmp(pren->info.Matricola, CodiceStudente1) == 0)
			{
				st1 = pren->info;
			}
			else if (strcmp(pren->info.Matricola, CodiceStudente2) == 0)
			{
				st2 = pren->info;
			}
			pren = pren->next;
		}
		turni = turni->next;
	}
	if ((strcmp(st1.Cognome, "") == 0) || (strcmp(st2.Cognome, "") == 0))
		return 0;
	turni = (*lista);
	pren = NULL;
	while (turni != NULL)
	{
		pren = turni->prenotati;
		while (pren != NULL)
		{
			if (strcmp(pren->info.Matricola, CodiceStudente1) == 0)
			{
				pren->info = st2;
			}
			else if (strcmp(pren->info.Matricola, CodiceStudente2) == 0)
			{
				pren->info = st1;
			}
			pren = pren->next;
		}
		turni = turni->next;
	}
	(*lista) = turni;
	return 1;
}

/*
3.
Funzione di eliminazione di un prenotato dalla lista. La funzione da implementare deve avere la seguente struttura:
nome della funzione: EliminaPrenotato;
valore restituito: esito operazione (0: operazione fallita, 1: eliminazione effettuata con successo);
parametri: lista dei prenotati, matricola.
Lo studente scelga sia il tipo dei dati che i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/

int EliminaPrenotato(ListaPrenotati* Prenotati, char* Matricola) 
{
	if ((*Prenotati) == NULL)
		return 0;
	ListaPrenotati aux;
	while ((*Prenotati) != NULL) 
	{
		if (strcmp((*Prenotati)->info.Matricola, Matricola) == 0) 
		{
			aux = (*Prenotati);
			(*Prenotati) = (*Prenotati)->next;
			free(aux);
			return 1;
		}
		else 
		{
			(*Prenotati) = (*Prenotati)->next;
		}
	}
}

/*
4. CreazioneTurni: Crea la lista dei turni a partire dalla lista dei prenotati. Ogni elemento della lista dei turni dovrà contenere
l’identificativo del turno e la lista dei prenotati afferenti a quel turno. I prenotati vengono allocati secondo
l’ordine in cui appaiono nella lista dei prenotati a partire dal primo turno.
Quando il numero di prenotati allocati al primo turno raggiunge la capienza del laboratorio (50 postazioni),
si procede l’allocazione al secondo turno e così via. Lo studente scelga la struttura della funzione, il tipo dei dati
ed i meccanismi di passaggio dei parametri più opportuni per rispettare la specifica.
*/


int CreazioneTurni(ListaTurni* lista, ListaPrenotati prenotati) 
{
	NodoTurnoT* NodoCorrente = (NodoTurnoT*)malloc(sizeof(NodoTurnoT));
	ListaPrenotati l = NULL;
	if (NodoCorrente == NULL)
		return 0;
	int id_turno = 1;
	NodoCorrente->next = NULL;
	NodoCorrente->NumeroTurno = id_turno++;
	NodoCorrente->prenotati = NULL;
	int n = 0;
	NodoCorrente->next = (*lista);
	(*lista) = NodoCorrente;
	while (prenotati != NULL) 
	{
		if(InserisciStudenteLista(&(NodoCorrente->prenotati), prenotati->info) == 1) 
			n++;
		prenotati = prenotati->next;
		if ((n == N))
		{
			n = 0;
			NodoTurnoT* NuovoTurno = (NodoTurnoT*)malloc(sizeof(NodoTurnoT));
			if (NuovoTurno == NULL)
				return 0;
			NuovoTurno->NumeroTurno = id_turno++;
			NuovoTurno->next = NULL;
			NuovoTurno->prenotati = NULL;
			NodoCorrente->next = NuovoTurno;
			NodoCorrente = NuovoTurno;
		}
	}
	return 1;
}
/*
5. CambioTurno: Funzione che, operando sulla lista dei turni, effettui lo spostamento di uno studente da un turno ad un altro
solo se tale spostamento rispetti il vincolo di capienza del laboratorio.
*/

int CambioTurno(ListaTurni* Turni, char* MatricolaStudente, int TurnoDesiderato) 
{
	int StudentiTurno = 0;
	ListaTurni t = (*Turni);
	NodoTurnoT* aux;
	ListaPrenotati pr = NULL;
	PrenotatoT studente;
	while (t != NULL) 
	{
		pr = t->prenotati;
		while (pr != NULL) 
		{
			if (strcmp(pr->info.Matricola, MatricolaStudente) == 0) 
			{
				studente = pr->info;
				aux = t;
				t = t->next;
				free(aux);
			}
			else 
			{
				pr = pr->next;
			}
		}
		t = t->next;
	}
	t = (*Turni);
	pr = NULL;
	while (t != NULL) 
	{
		if (t->NumeroTurno == TurnoDesiderato) 
		{
			pr = t->prenotati;
			while (pr != NULL) 
			{
				StudentiTurno++;
				pr = pr->next;
			}
		}
		else 
		{
			t = t->next;
		}
	}
	if (StudentiTurno >= N) 
	{
		printf("Impossibile effettuare il cambio turno, postazioni occupate.\n");
		return 1;
	}
	t = (*Turni);
	pr = NULL;
	while (t != NULL)
	{
		if (t->NumeroTurno == TurnoDesiderato)
		{
			pr = t->prenotati;
			InserisciStudenteLista(&t->prenotati, studente);
		}
		else
		{
			t = t->next;
		}
	}
	(*Turni) = t;
	return 1;
}

int Menu() 
{
	int scelta;
	printf("******* MENU *******\n"
		"1) Carica dati da file.\n"
		"2) Modifica turno.\n"
		"3) Elimina prenotato.\n"
		"4) Crea turni.\n"
		"5) Cambio turno.\n"
		"6) Occupazione media.\n"
		"7) Visualizza turni.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

void VisualizzaListaPrenotati(ListaPrenotati prenotati) 
{
	while (prenotati != NULL) 
	{	
		printf("%s %s %s\n", prenotati->info.Matricola, prenotati->info.Cognome, prenotati->info.Nome);
		prenotati = prenotati->next;
	}
}

void VisualizzaTurni(ListaTurni turni) 
{
	ListaPrenotati p = NULL;
	while (turni != NULL) 
	{
		printf("CODICE TURNO: %d\n"
			"PRENOTATI:\n", turni->NumeroTurno);
		p = turni->prenotati;
		VisualizzaListaPrenotati(p);
		turni = turni->next;
	}
}

void DisallocaLista(ListaPrenotati* prenotati) 
{
	ListaPrenotati aux;
	while ((*prenotati) != NULL) 
	{
		aux = (*prenotati);
		(*prenotati) = (*prenotati)->next;
		free(aux);
	}
}

float* OccupazioneMedia(ListaTurni lturni, int* dim)
{
	int turni = 0;
	(*dim) = 0;
	ListaTurni t = lturni;
	ListaPrenotati p = NULL;
	while (t != NULL) 
	{
		p = t->prenotati;
		while (p != NULL) 
		{
			p = p->next;
		}
		turni++;
		t = t->next;
	}
	t = lturni;
	(*dim) = turni;
	int cont;
	p = NULL;
	float* VettoreOccupazioneMediaPerTurno = (float*)malloc(sizeof(float) * turni);
	int index = 0;
	while (t != NULL)
	{
		p = t->prenotati;
		cont = 0;
		while (p != NULL)
		{
			cont++;
			p = p->next;
		}
		VettoreOccupazioneMediaPerTurno[index++] = ((float)(cont) / (N))*100.0;
		t = t->next;
	}
	return VettoreOccupazioneMediaPerTurno;
}

void DisallocaTurni(ListaTurni* turni) 
{
	NodoTurnoT* aux;
	while ((*turni) != NULL) 
	{
		DisallocaLista(&((*turni)->prenotati));
		aux = (*turni);
		(*turni) = (*turni)->next;
		free(aux);
	}
}

int main()
{
	ListaPrenotati prenotati = NULL;
	int scelta;
	float* vout = NULL;
	char matricola1[10], matricola2[10];
	int e;
	int CodiceTurno;
	ListaTurni turni = NULL;
	int EsitoScambioTurno;
	int EsitoCreazioneTurni;
	int CancellazionePrenotazione;
	char NomeFile[32];
	int NumeroPrenotati;
	int dimout;
	do 
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			NumeroPrenotati = CaricaDatiFile(&prenotati, NomeFile);
			if (NumeroPrenotati != 0) 
			{
				printf("Sono stati caricati %d prenotati.\n", NumeroPrenotati);
				VisualizzaListaPrenotati(prenotati);
				printf("\n");
			}
			else 
			{
				printf("Si e' verificato un errore.\n");
			}
			break;
		case 2:
			printf("Inserisci la matricola del primo studente: ");
			scanf("%s", matricola1);
			printf("Inserisci la matricola del secondo studente: ");
			scanf("%s", matricola2);
			if (strcmp(matricola1, matricola2) == 0)
				printf("Inserisci due matricole diverse.");
			EsitoScambioTurno = ScambioTurno(&turni, matricola1, matricola2);
			if (EsitoScambioTurno == 1)
				printf("Scambio turno avvenuto.\n");
			else
				printf("Si e' verificato un errore.\n");
			break;
		case 3:
			printf("Inserisci la matricola dello studente da eliminare: ");
			scanf("%s", matricola1);
			CancellazionePrenotazione = EliminaPrenotato(&prenotati, matricola1);
			if (CancellazionePrenotazione == 1)
				printf("Cancellazione prenotazione avvenuta con successo.\n");
			VisualizzaListaPrenotati(prenotati);
			break;
		case 4:
			EsitoCreazioneTurni = CreazioneTurni(&turni, prenotati);
			if (EsitoCreazioneTurni == 1)
			{
				printf("Turni creati con successo.\n");
				VisualizzaTurni(turni);
			}
			printf("\n");
			break;
		case 5:
			printf("Inserisci la matricola dello studente a cui vuoi cambiare turno: ");
			scanf("%s", matricola1);
			printf("In quale turno vuoi metterlo: ");
			scanf("%d", &CodiceTurno);
			e = CambioTurno(&turni, matricola1, CodiceTurno);
			if (e == 1)
				printf("Operazione effettuata con successo.\n");
			break;
		case 6:			
			vout = OccupazioneMedia(turni, &dimout);
			for (int i = 0; i < dimout; i++) 
			{
				printf("TURNO %d --- OCCUPAZIONE MEDIA = %.3f\n", i+1, vout[i]);
			}
			printf("\n");
			break;
		case 7:
			VisualizzaTurni(turni);
			break;
		}
	} while (scelta != 0);

	DisallocaLista(&prenotati);
	DisallocaTurni(&turni);
	free(vout);
}