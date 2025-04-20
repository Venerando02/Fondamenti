/*
i vuole realizzare una applicazione che consente di gestire una prova di esame. Lo studente può effettuare due tipi di prenotazione
- prova pratica
- registrazione
Le prenotazioni vengono raccolte in un vettore di liste, la lista di posto 0 conterrà le prenotazioni per la prova pratica, la lista di posto 1 le prenotazioni per la la registrazione.
Per ogni prenotazione saranno memorizzate le seguenti informazioni: numero di matricola, nome, cognome
Lo studente implementi un programma ANSI C che consente di effettuare le prenotazioni e memorizzare nella struttura dati precedentemente descritta gli esami superati.
Scrivere un opportuno main in cui sia previsto un menu di scelta delle operazioni richieste. Tutti i valori necessari al funzionamento devono essere passati
utilizzando parametri, non è permesso l’uso di variabili globali.
1. Prenotazione di un nuovo studente da console. I dati da inserire sono il tipo di prova, il numero di matricola, il cognome, il nome e il voto nel caso
di registrazione. Nel caso della prenotazione per la prova pratica il valore del voto è -1;
2. Funzione che restituisce un vettore che contiene il numero di prenotati per ciascuna prova;
3. RisultatoProvaPratica, la funzione acquisisce il nome di uno studente e un voto, se lo studente è presente nella lista della prova pratica 
lo trasferisce dalla lista della prova pratica (cancellandolo) nella lista registrazione inserendo il voto inserito;
4. Media, la funzione calcola il voto medio degli esami da registrare
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct StudenteS 
{
	char matricola[11];
	char nome[32];
	char cognome[32];
} StudenteT;

typedef struct PrenotazioniS 
{
	StudenteT info;
	int voto;
	struct PrenotazioniS* next;
} PrenotazioniNodoT, *ListaPrenotazioni;

int InserisciPrenotazione(ListaPrenotazioni* plista, StudenteT st)
{
	PrenotazioniNodoT* aux = (PrenotazioniNodoT*)malloc(sizeof(PrenotazioniNodoT));
	if (aux == NULL)
		return 0;
	aux->info = st;
	aux->next = (*plista);
	(*plista) = aux;
	return 1;
}

int CancellaStudente(ListaPrenotazioni* plista, char* Matricola) 
{
	ListaPrenotazioni aux = NULL;
	if ((*plista) == NULL) 
	{
		return 0;
	}
	if (strcmp((*plista)->info.matricola, Matricola) == 0) 
	{
		aux = (*plista);
		(*plista) = (*plista)->next;
		free(aux);
		return 1;
	}
	else 
		return CancellaStudente(&((*plista)->next), Matricola);
}

int InserisciStudente(ListaPrenotazioni vliste[], StudenteT studente, int tipop, int votos) 
{
	if (tipop == 0) 
	{
		InserisciPrenotazione(&vliste[tipop], studente);
		vliste[tipop]->voto = -1;
	}
	else if (tipop == 1) 
	{
		InserisciPrenotazione(&vliste[tipop], studente);
		vliste[tipop]->voto = votos;
	}
	return 1;
}

int* NumeroPrenotati(ListaPrenotazioni vliste[], int dim) 
{
	int* vettore = (int*)malloc(sizeof(int) * dim);
	if (vettore == NULL)
		return NULL;
	int contatore;
	ListaPrenotazioni l;
	for (int i = 0; i < dim; i++) 
	{
		contatore = 0;
		l = vliste[i];
		while (l != NULL) 
		{
			contatore++;
			l = l->next;
		}
		vettore[i] = contatore;
	}
	return vettore;
}

int InserisciVotoProvaPratica(ListaPrenotazioni* vliste, char* Matricola, int voto) 
{
	StudenteT s;
	if (vliste[0] == NULL)
		return 0;
	while (vliste[0] != NULL) 
	{
		if (strcmp(vliste[0]->info.matricola, Matricola) == 0) 
		{
			s = vliste[0]->info;
			CancellaStudente(&(vliste[0]), Matricola);
			InserisciStudente(vliste, s, 1, voto);
		}
		else 
		{
			vliste[0] = vliste[0]->next;
		}
	}
	return 1;
}

int Menu() 
{
	int scelta;
	printf("********** MENU **********\n"
	"1. Inserisci un nuovo studente nella prenotazione.\n"
	"2. Numero prenotati per prova.\n"
	"3. Inserisci risultato prova pratica.\n"
	"4. Calcolo voto medio.\n\n"
	">>>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

void DisallocaLista(ListaPrenotazioni* lista) 
{
	ListaPrenotazioni aux = NULL;
	while ((*lista) != NULL) 
	{
		aux = (*lista);
		(*lista) = (*lista)->next;
		free(aux);
	}
}

void StampaVettore(ListaPrenotazioni v[], int dim) 
{
	for (int i = 0; i < dim; i++) 
	{
		printf("CODICE %d\nSTUDENTI:\n", i);
		ListaPrenotazioni aux = v[i];
		while (aux != NULL) 
		{
			printf("%s %s %s\n", aux->info.matricola, aux->info.cognome, aux->info.nome);
			aux = aux->next;
		}
	}
}

float CalcoloMediaVoti(ListaPrenotazioni* vliste, int codiceregistrazione) 
{
	ListaPrenotazioni lista = vliste[codiceregistrazione];
	float somma = 0.0;
	float media = 0.0;
	int cont = 0;
	while (lista != NULL) 
	{
		somma += lista->voto;
		cont++;
		lista = lista->next;
	}
	media = ((float)(somma) / (float)(cont));
	return media;
}

int main() 
{
	ListaPrenotazioni vettore[2];
	for (int i = 0; i < 2; i++) 
	{
		vettore[i] = NULL;
	}
	StudenteT st;
	char Prenotazione[2][32] = { "PROVA PRATICA", "REGISTRAZIONE" };
	int* numprenotazioni = NULL;
	int tipoprenotazione;
	int scelta;
	int esito;
	float media;
	int voto;
	char MatricolaStudente[11];
	do 
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci i dati dello studente (Numero matricola, nome e cognome): ");
			scanf("%s %s %s", st.matricola, st.cognome, st.nome);
			do 
			{
				printf("Inserisci il tipo di prenotazione che vuoi effettuare (0 = prova pratica, 1 = registrazione): ");
				scanf("%d", &tipoprenotazione);
				if (tipoprenotazione == 1) 
				{
					printf("Inserisci voto: ");
					scanf("%d", &voto);
				}
			} while ((tipoprenotazione != 0) && (tipoprenotazione != 1));
			esito = InserisciStudente(vettore, st, tipoprenotazione, voto);
			if (esito == 1)
			{
				printf("Prenotazione inserita con successo.\n\n");
				StampaVettore(vettore, 2);
			}
			break;
		case 2:
			numprenotazioni = NumeroPrenotati(vettore, 2);
			for (int i = 0; i < 2; i++) 
			{
				printf("%s. NUMERO PRENOTATI: %d\n", Prenotazione[i], numprenotazioni[i]);
			}
			printf("\n");
			break;
		case 3:
			printf("Inserisci la matricola dello studente: ");
			scanf("%s", MatricolaStudente);
			printf("Inserisci il voto: ");
			scanf("%d", &voto);
			if (InserisciVotoProvaPratica(vettore, MatricolaStudente, voto) == 1)
				printf("Voto inserito con successo.\n");
			break;
		case 4:
			media = CalcoloMediaVoti(vettore, 1);
			printf("La media e' %.3f.\n", media);
			break;
		}
	} while (scelta != 0);
	free(numprenotazioni);
	for (int i = 0; i < 2; i++) 
	{
		DisallocaLista(vettore[i]);
	}
}