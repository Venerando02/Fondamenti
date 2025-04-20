/*  ESERCIZIO 2  - Fondamenti di Informatica - Appello del 15/07/2024

  Sviluppo di applicazione in ANSI C per gestire
  le prenotazioni e le registrazione esami degli
  studenti di un corso universitario.

  In un file di testo ("prenotati.txt"), è memorizzato
  l'elenco degli studenti prenotati ad un appello.
  Così come visibile nel file, per ciascun studente
  sono memorizzate le seguenti informazioni:
  - matricola
  - cognome
  - nome

  Si assuma che cognome e nome dello studente non contengano spazi.

  Implementare le seguenti funzioni:

  1. CaricaPrenotazioni: carica gli studenti presenti nel file in una
  lista di studenti prenotati.

  2. RegistraEsame: dato il numero di matricola di uno studente ed un voto,
  rimuove tale studente dalla lista dei prenotati (se esiste) e lo
  inserisce in una seconda lista di esami sostenuti
  (nella quale viene valorizzato il campo voto)

  3. EstraiStudentiMigliori:
  seleziona dalla lista esami sostenuti gli studenti che hanno
  riportato un voto maggiore della media dei voti presenti,
  e li copia in un apposito vettore di studenti
  La funzione deve resituire anche il numero di studenti copiati nel vettore

  4. IstogrammaVoti: data la lista esami sostenuti,
  restituisce un vettore di 13 elementi in cui ogni elemento
  contiene il numero di studenti che ha ottenuto quel voto (da 18 a 30)

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funzione.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Esame {
	char  matricola[10];
	char  cognome[64];
	char  nome[64];
	int voto;   /* intero  da 18 a 30 - per semplicità non si considerano lodi */
} TEsame;

typedef struct NodoEsame {
	TEsame           info;
	struct NodoEsame* next;
} TNodoEsame;

typedef TNodoEsame* TListaEsami;

/* InserisciInTesta: inserisce un elemento in
   testa alla lista passata
*/
int InserisciInTesta(TListaEsami* plis, TEsame elem) {
	TListaEsami paux;

	paux = (TListaEsami)malloc(sizeof(TNodoEsame));

	if (paux == NULL)
		return 0;

	paux->info = elem;
	paux->next = *plis;

	*plis = paux;

	return 1;
}


/*
  1. CaricaPrenotazioni: carica gli studenti presenti nel file in una
  lista di studenti prenotati.
  In questa lista, si setti il campo voto di ogni studente prenotato a 0 (zero).
  Parametri di ingresso: nome del file
  Parametri di uscita: lista degli studenti prenotati
  Valore restituito: numero di elementi caricati
*/
int CaricaPrenotazioni(char* nomefile, TListaEsami* lista) 
{
	// DA IMPLEMENTARE
	FILE* fp = fopen(nomefile, "r");
	if (fp == NULL)
		return -1;
	TEsame exam;
	int n = 0;
	while (fscanf(fp, "%s%s%s", exam.matricola, exam.cognome, exam.nome) == 3)
	{
		exam.voto = 0;
		if (!InserisciInTesta(lista, exam))
			return 0;
		else
			n++;
	}
	fclose(fp);
	return n;
}

/*
  2. RegistraEsame: dato il numero di matricola di uno studente ed un voto,
  rimuove tale studente dalla lista dei prenotati (se esiste) e lo
  inserisce in una seconda lista di esami sostenuti
  (nella quale viene valorizzato il campo voto)
  Parametri di ingresso: lista degli studenti prenotati, numero matricola, voto
  Parametri di uscita: lista degli esami sostenuti
  Valore restituito: 1 se lo studente era presente nella lista dei prenotati
  e l'esame è stato registrato, 0 altrimenti
*/
int RegistraEsame(TListaEsami* listaprenotati, char* matricola, int voto, TListaEsami* listaesami) 
{
	// DA IMPLEMENTARE
	if ((voto < 18) && (voto > 30))
	{
		printf("Inserisci un voto tra 18 e 30.");
		return 0;
	}
	if ((*listaprenotati) == NULL)
		return 0;
	TListaEsami aux;
	TEsame Exam;
	if (strcmp((*listaprenotati)->info.matricola, matricola) == 0)
	{
		Exam = (*listaprenotati)->info;
		Exam.voto = voto;
		if (!InserisciInTesta(listaesami, Exam))
			return -1;
		aux = (*listaprenotati);
		(*listaprenotati) = (*listaprenotati)->next;
		free(aux);
		return 1;
	}
	else
		return RegistraEsame(&((*listaprenotati)->next), matricola, voto, listaesami);
}


/*
  3. EstraiStudentiMigliori: seleziona dalla lista esami sostenuti gli studenti
  che hanno riportato un voto maggiore della media dei voti presenti,
  e li copia in un apposito vettore di studenti
  La funzione deve resituire anche il numero di studenti copiati nel vettore

  Parametri di ingresso:
	lis - lista degli studenti prenotati,
  Parametri di uscita:
	dim - dimensione del vettore resitutito
  Valore restituito:
	TEsame* - vettore degli studenti con voto maggiore della media
*/
TEsame* EstraiStudentiMigliori(TListaEsami lis, int* dim)
{
	// DA IMPLEMENTARE
	TEsame* vettore = NULL;
	(*dim) = 0;
	TListaEsami Lista = lis;
	float Media;
	int voto = 0;
	int cont = 0;
	while (Lista != NULL) 
	{
		cont++;
		voto += Lista->info.voto;
		Lista = Lista->next;
	}
	Media = (float)((float)(voto) / cont);
	Lista = lis;
	int dimvettore = 0;
	while (Lista != NULL) 
	{
		if (Lista->info.voto >= Media) 
		{
			dimvettore++;
		}
		Lista = Lista->next;
	}
	vettore = (TEsame*)malloc(sizeof(TEsame) * dimvettore);
	if (vettore == NULL)
		return NULL;
	Lista = lis;
	while (Lista != NULL)
	{
		if (Lista->info.voto >= Media)
		{
			vettore[(*dim)++] = Lista->info;
		}
		Lista = Lista->next;
	}
	return vettore;
}

/*
  4. IstogrammaVoti: data la lista esami sostenuti,
  restituisce un vettore di 13 elementi in cui ogni elemento
  contiene il numero di studenti che ha ottenuto quel voto (da 18 a 30)
  Parametri di ingresso:
	lista - lista degli esami sostenuti,
  Valore restituito:
	vettore con numero di studenti per ogni voto
*/
int* IstogrammaVoti(TListaEsami lis) 
{
	// DA IMPLEMENTARE
	int* vout = (int*)malloc(sizeof(int) * 13);
	for (int i = 0; i < 13; i++)
		vout[i] = 0;
	if (vout == NULL)
		return NULL;
	int voto = 18;
	TListaEsami lista;
	int cont;
	int index = 0;
	while (voto <= 30) 
	{
		cont = 0;
		lista = lis;
		while (lista != NULL) 
		{
			if (lista->info.voto == voto) 
			{
				cont++;
			}
			lista = lista->next;
		}
		vout[index++] = cont;
		voto++;
	}
	return vout;
}


/*
  VisualizzaLista: visualizza le informazioni delle prenotazioni/esami
  contenuti nella lista passata come parametro
*/
void VisualizzaLista(TListaEsami lis) 
{
	while (lis != NULL) {
		printf("%s %s %s %d\n",
			lis->info.matricola,
			lis->info.cognome,
			lis->info.nome,
			lis->info.voto);
		lis = lis->next;
	}
}

/*
  VisualizzaVettore: visualizza le informazioni degli studenti
  contenute nel vettore passato come parametro
*/
void VisualizzaVettoreStudenti(TEsame v[], int dim) {
	int i;
	for (i = 0; i < dim; i++)
		printf("%s %s %s %d\n",
			v[i].matricola,
			v[i].cognome,
			v[i].nome,
			v[i].voto);
}

int Menu() {
	int scelta;

	printf("\n*** M E N U ***\n"
		"1 - Carica prenotazioni da file\n"
		"2 - Registra esito esame\n"
		"3 - Estrai studenti migliori \n"
		"4 - Istogramma voti \n"
		"0 - Uscita\n\n"
		"Scelta:   ");
	scanf("%d", &scelta);

	return scelta;
}

void DisallocaLista(TListaEsami lista) 
{
	// DA IMPLEMENTARE
	TNodoEsame* aux;
	while (lista != NULL) 
	{
		aux = lista;
		lista = lista->next;
		free(aux);
	}
}

/******** MAIN **********/
int main(void) {
	TListaEsami listaprenotazioni = NULL;
	TListaEsami listaesami = NULL;

	int         scelta, n;
	char        nomefile[32];
	char	matricola[10];
	int voto;
	int esito;
	int         dim = 0;
	TEsame* vett = NULL;
	int* vettvoti;


	do {
		scelta = Menu();

		switch (scelta) {
		case 1:
			printf("Immetti il nome del file di testo: ");
			scanf("%s", nomefile);
			// invocare la funzione CaricaPrenotazioni e visualizzare la lista ottenuta
			n = CaricaPrenotazioni(nomefile, &listaprenotazioni);
			if (n != 0)
				VisualizzaLista(listaprenotazioni);
			break;
		case 2:
			// inserire da input matricola e voto di uno studente
			// ed invocare la funzione RegistraEsame
			printf("Inserisci matricola: ");
			scanf("%s", matricola);
			printf("Inserisci il voto: ");
			scanf("%d", &voto);
			esito = RegistraEsame(&listaprenotazioni, matricola, voto, &listaesami);
			if (esito == 1)
				printf("Esame registrato con successo.\n");
			else
				printf("Matricola non trovata.\n");
			printf("\n------------------\n");
			VisualizzaLista(listaesami);
			printf("\n------------------\n");
			VisualizzaLista(listaprenotazioni);
			break;
		case 3:
			// invocare la funzione EstraiStudentiMigliori
			// e successivamente visualizzare il contenuto del vettore ottenuto
			vett = EstraiStudentiMigliori(listaesami, &dim);
			VisualizzaVettoreStudenti(vett, dim);
			free(vett);
			break;
		case 4:
			// invocare la funzione IstogrammaVoti e visualizzare i risultati ottenuti
			vettvoti = IstogrammaVoti(listaesami);
			int voto = 18;
			for (int i = 0; i < 13; i++)
			{
				printf("Voto %d: %d\n", voto, vettvoti[i]);
				voto++;
			}
			break;
		}

	} while (scelta != 0);

	// Didsallocare le liste
	DisallocaLista(listaprenotazioni);
	DisallocaLista(listaesami);

	return 0;
}