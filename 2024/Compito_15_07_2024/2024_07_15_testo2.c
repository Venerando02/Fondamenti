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

typedef struct NodoEsame{
  TEsame           info;
  struct NodoEsame *next;
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
int CaricaPrenotazioni(char *nomefile, TListaEsami* lista) {
  
	// DA IMPLEMENTARE

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
int RegistraEsame(TListaEsami* listaprenotati, char* matricola,	int voto, TListaEsami* listaesami) {
	
	// DA IMPLEMENTARE

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
TEsame* EstraiStudentiMigliori(TListaEsami lis, int* dim) {
	// DA IMPLEMENTARE

  }

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
int* IstogrammaVoti(TListaEsami lis) {
	// DA IMPLEMENTARE

}


/*
  VisualizzaLista: visualizza le informazioni delle prenotazioni/esami
  contenuti nella lista passata come parametro
*/
void VisualizzaLista(TListaEsami lis) {
  while (lis != NULL){
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

void DisallocaLista(TListaEsami lista) {
	// DA IMPLEMENTARE

}

/******** MAIN **********/
int main(void) {
  TListaEsami listaprenotazioni = NULL;
  TListaEsami listaesami = NULL;

  int         scelta,n;
  char        nomefile[32];
  char	matricola[10];
  int voto;
  int esito;
  int         dim=0;
  TEsame*     vett;
  int* vettvoti;


  do {
    scelta = Menu();

    switch (scelta) {
      case 1:
		  printf("Immetti il nome del file di testo: ");
		  scanf("%s", nomefile);
		  // invocare la funzione CaricaPrenotazioni e visualizzare la lista ottenuta

		break;
	  case 2:
		  // inserire da input matricola e voto di uno studente
		  // ed invocare la funzione RegistraEsame


		break;
	  case 3:
		  // invocare la funzione EstraiStudentiMigliori
		  // e successivamente visualizzare il contenuto del vettore ottenuto

		  break;
	  case 4:
		  // invocare la funzione IstogrammaVoti e visualizzare i risultati ottenuti

		  break;
      }

  } while (scelta != 0);

  // Didsallocare le liste
  DisallocaLista(listaprenotazioni);
  DisallocaLista(listaesami);

  return 0;
}