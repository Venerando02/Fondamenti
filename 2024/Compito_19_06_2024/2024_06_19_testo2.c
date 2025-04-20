/*
  Sviluppo di applicazione in ANSI C per gestire 
  un servizio i brani musicali di una playlist.

  In un file di testo ("brani.txt"), è memorizzato 
  l'elenco dei brani di una playlist.
  Così come visibile nel file, per ciascun brano
  musicale sono memorizzate le seguenti informazioni:
  - codice brano
  - titolo brano
  - cantante
  - anno pubblicazione

  Si assuma che il titolo del brano ed il nome del cantante non contengano spazi.

  Implementare le seguenti funzioni:

  1. CaricaBrani: carica i brani presenti nel file in una 
  lista di brani ordinata in base all'anno di pubblicazione.

  2. EliminaBrano: dato il codice di un brano, rimuove tale brano (se
  esiste) dalla lista.

  3. EstraiBraniCantante: dato il nome di un cantante,
  seleziona dalla lista i brani di quel cantante e li 
  inserisce in un apposito vettore di brani.

  4. MaxBraniAnno: restituisce il numero massimo di brani pubblicati in 
  un anno compreso tra l'anno corrente (2024) e gli N anni precedenti

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funzione.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Brano {
  char  codice[8];
  char  titolo[64];
  char  cantante[64];
  int anno;
} TBrano;

typedef struct NodoBrano{
  TBrano           info;
  struct NodoBrano *next;
} TNodoBrano;

typedef TNodoBrano* TListaBrani;


/* AggiungiBranoInOrdine: inserisce un brano nella lista 
   in ordine rispetto all'anno di pubblicazione
 */
int AggiungiBranoInOrdine(TListaBrani* plis, TBrano elem) {
	// DA IMPLEMENTARE
}

/*
  1.  CaricaBrani: carica i brani presenti nel file in una 
  lista di brani ordinata in base all'anno di pubblicazione.
  Parametri di ingresso: nome del file
  Parametri di uscita: lista dei brani musicali
  Valore restituito: numero di elementi caricati
*/
int CaricaBrani(char *nomefile, TListaBrani* lista) {
	// DA IMPLEMENTARE
}

/*
  2. EliminaBrano: dato il codice di un brano, rimuove tale brano (se
  esiste) dalla lista.
  Parametri di ingresso: lista dei brani musicali, codice del brano da cancellare
*/
void EliminaBrano(TListaBrani* lis, char* codice) {
	// DA IMPLEMENTARE

}  

/*
  3. EstraiBraniCantante: dato il nome di un cantante,
  seleziona dalla lista i brani di quel cantante e li 
  inserisce in un apposito vettore di brani
  Parametri di ingresso:
    lis - lista dei brani musicali,
    cantante - nome del cantante
  Parametri di uscita:
    dim - numero di brani del cantante
  Valore restituito: 
    TBrano* - vettore dei brani selezionati
*/
TBrano* EstraiBraniCantante(TListaBrani lis,char* cantante, int* dim) {
	// DA IMPLEMENTARE
	
}

/*
4. MaxBraniAnno: restituisce il numero massimo di brani pubblicati in
un anno compreso tra l'anno corrente (2024) e gli N anni precedenti
  Parametri di ingresso:
    lista - lista dei brani musicali,
    N - numero di anni precedenti al 2024 da considerare
  Parametri di uscita:
    anno - anno in cui si è registrato il numero massimo di brani
  Valore restituito:
    int - numero massimo di brani
*/
int MaxBraniAnno(TListaBrani lista, int N, int* anno) {
	// DA IMPLEMENTARE

}

/*
  VisualizzaLista: visualizza le informazioni dei brani
  nella lista passata come parametro
*/
void VisualizzaLista(TListaBrani lis) {
  while (lis != NULL){
      printf("%s %s %s %d\n",
	     lis->info.codice,
	     lis->info.titolo,
	     lis->info.cantante,
	     lis->info.anno);
      lis = lis->next;
    }
}

/*
  VisualizzaVettoreBrani: visualizza le informazioni dei brani
  contenute nel vettore passato come parametro
*/
void VisualizzaVettoreBrani(TBrano v[], int dim) {
  int i;
  for (i = 0; i < dim; i++) 
    printf("%s %s %s %d\n",
	   v[i].codice,
	   v[i].titolo,
	   v[i].cantante,
	   v[i].anno);
}

int Menu() {
  int scelta;
  
  printf("\n*** M E N U ***\n"
	 "1 - Carica brani musicali\n"
	 "2 - Elimina brano\n"
	 "3 - Estrai brani cantante \n"
	 "4 - Massimo numero brani in un anno \n"
	 "0 - Uscita\n\n"
	 "Scelta:   ");
  scanf("%d", &scelta);

  return scelta;
}

void DisallocaLista(TListaBrani lista) {
  TListaBrani paux;

  while (lista != NULL) {
      paux = lista;
      lista = lista->next;
      free(paux);
    }
}

/******** MAIN **********/
int main(void) {
  TListaBrani listabrani = NULL;

  int         scelta,n;
  char        nomefile[32];
  char        codice[8];
  char        nomecantante[64];
  int         dim=0;
  TBrano*     vett;
  int massimo, annomax;

  do {
    scelta = Menu();

    switch (scelta) {
      case 1:
		  printf("Immetti il nome del file di testo: ");
		  scanf("%s", nomefile);
		  // invocare la funzione CaricaBrani e visualizzare la lista ottenuta
 
		break;
	  case 2:
		  // inserire un codice ed invocare la funzione EliminaBrano per rimuovere quel brano dalla lista
 
		break;
	  case 3:
		  printf("Inserisci il nome del cantante: ");
		  scanf("%s", nomecantante);
		  // invocare la funzione EstraiBraniCantante
		  // e successivamente visualizzare il contenuto del vettore ottenuto

		  break;
	  case 4:
		  printf("Inserisci il numero di anni precedenti l'anno corrente: ");
		  scanf("%d", &n);
		  // invocare la funzione MaxBraniAnno e visualizzare i risultati ottenuti

		  break;
      }

  } while (scelta != 0);

  // Disallocare la lista


  return 0;
}