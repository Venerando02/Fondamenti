/*
  Sviluppo di applicazione in ANSI C per gestire 
  le autovetture di una società di autonoleggio.

  In un file di testo ("autovetture.txt"), è memorizzato 
  l'elenco delle autovetture possedute dalla società.
  Così come visibile nel file, per ciascuna autovettura
  sono memorizzate le seguenti informazioni:
  - targa
  - nome categoria (es: citycar, berlina, SUV, sportive, monovolume, etc)
  - costo giornaliero
  - km percorsi
  - stato (disponibile/noleggiata).

  Implementare le seguenti funzioni:
  1. CaricaVetture: 
        carica le autovetture presenti nel file in due liste 
        rispettivamente una contenente quelle disponibili
        e l'altra contenente quelle noleggiate.

  2. Noleggia: 
        data una targa, rimuove tale vettura (se esiste) 
        dalla lista delle auto disponibili e la aggiunge 
        a quella delle auto noleggiate. 

  3. EstraiVettureDiInteresse:
        dato un valore massimo di km percorsi ed una categoria,
        seleziona dalla lista delle vetture disponibili
        quelle che soddisfano tali criteri e le inserisce
        in un apposito vettore di autovetture.

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funione.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Autovettura {
  char  targa[8];
  char categoria[16];
  float costo;
  long km;
} TAutovettura;

typedef struct NodoAutovettura{
  TAutovettura info;
  struct NodoAutovettura *next;
} TNodoAutovettura;

typedef TNodoAutovettura* TListaAutovetture;


/* AggiungiVettura inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiVettura(TListaAutovetture* plis, TAutovettura elem) {
  TListaAutovetture paux;

  paux = (TListaAutovetture)malloc(sizeof(TNodoAutovettura));

  if (paux == NULL)
    return 0;
  
  paux->info = elem;
  paux->next = *plis;

  *plis = paux;
  
  return 1;
}

/*
  1. CaricaVetture: carica le autovetture presenti nel file
  in due liste rispettivamente una contenente quelle disponibili
  e l'altra contenente quelle noleggiate.


  Parametri di ingresso: nome del file
  Parametri di uscita: lista delle autovetture disponibili (disponibili),
                       lista delle autovetture noleggiate (noleggiate)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
 */
int CaricaVetture(char* nome_file, TListaAutovetture* disponibili, 
                                   TListaAutovetture* noleggiate) {
  // Implementare il corpo della funzione

}
/*
  RicercaVettura: ricerca nella lista lis l'autovettura con la targa fornita in ingresso (targa). Restituisce NULL se la vettura con quella targa non è
  presente nella lista lis.
 */
TListaAutovetture RicercaVettura(TListaAutovetture lis, char* targa) {

    while (lis != NULL) {
        if (strcmp(targa, lis->info.targa) == 0)
            return (lis);
        lis = lis->next;
    }
    return(NULL);
}

/*
  CancellaVettura: ricerca nella lista lis l'autovettura con la targa 
  fornita in ingresso (targa) e la rimuove dalla lista. 
 */
void CancellaVettura(TListaAutovetture* lis, char* targa) {
  // Implementare il corpo della funzione

}  

/*
    2. Noleggia: data una targa, rimuove tale vettura(se esiste)
    dalla lista delle auto disponibili e la aggiunge a quella delle
    auto noleggiate.
    Parametri di ingresso: 
            targa autovettura,
  Parametri di ingresso/uscita: 
            lista delle autovetture disponibili (disponibili),
            lista delle autovetture noleggiate (noleggiate)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
*/

int Noleggia(char* targa, TListaAutovetture* disponibili, 
                          TListaAutovetture* noleggiate) {
  // Implementare il corpo della funzione

}

/*
    3. EstraiVettureDiInteresse:
        dato un valore massimo di km percorsi ed una categoria, 
        seleziona dalla lista delle vetture disponibili 
        quelle che soddisfano tali criteri e le inserisce
        in un apposito vettore di autovetture.

    Parametri di ingresso:
            lis - lista delle autovetture disponibili,
            maxkm - numero massimo di km percorsi,
            categoria - categoria di autovettura
  Parametri di uscita:
            dim - numero di autovetture che soddisfano i criteri
  Valore restituito: 
            TAutoVettura - vettore delle autovetture selezionate
*/

TAutovettura* EstraiVettureDiInteresse(TListaAutovetture lis, long maxkm, char* categoria, int* dim) {
   // Implementare il corpo della funzione

}


/*
  VisualizzaVetture visualizza le informazioni delle vetture
  nella lista passata come parametro
 */
void VisualizzaVetture(TListaAutovetture lis) {
  while (lis != NULL)     {
      printf("%s %s %.2f %ld\n",
          lis->info.targa,
          lis->info.categoria,
          lis->info.costo,
          lis->info.km);    
      lis = lis->next;
    }
}

/*
  VisualizzaVettoreAuto visualizza le informazioni delle vetture
  contenute nel vettore passato come parametro
 */
void VisualizzaVettoreAuto(TAutovettura v[], int dim) {
  // Implementare il corpo della funzione

}



int Menu() {
  int scelta;
  
  printf("*** M E N U ***\n"
	 "1 - Carica vetture\n"
	 "2 - Noleggia vettura\n"
	 "3 - Cerca Vetture di interesse \n"
	 "0 - Uscita\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

void DisallocaLista(TListaAutovetture lista) {
  TListaAutovetture paux;

  // Implementare il corpo della funzione

}


int main(void) {
  TListaAutovetture disponibili = NULL;
  TListaAutovetture noleggiate = NULL;

  int  scelta;
  char nomefile[32];
  char targa[8];
  long km;
  char cat[16];
  int dim;
  TAutovettura* vett;
  
  do {
    scelta = Menu();

    switch (scelta)       {
      case 1:
	  // acquisire il nome del file
	  // invocare la funzione CaricaVetture
	  // visualizzare le liste ottenute
	        break;

      case 2:
	  // acquisire la targa dell'auto da noleggiare
	  // invocare la funzione Noleggia
	  // visualizzare le liste modificate
            break;

      case 3:
	  // acqusire i km max
	  // acquisire una categorai auto
	  // invocare la funzione EstraiVettureDiInteresse
	  // visualizzare il vettore restituito

            break;
      }

  } while (scelta != 0);

  // Disallocare le liste


  return 0;
}

