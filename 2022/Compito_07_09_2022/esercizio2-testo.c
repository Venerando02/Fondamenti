/*
Sviluppare un programma per la gestione dei dati delle precipitazioni piovose giornaliere raccolti da una rete di sensori distribuiti su un'area suddivisa in 10 settori.
Ogni sensore trasmette giornalmente le seguenti informazioni che sono memorizzate in un file unitamente all'identificativo del settore ed alla data:
- Identificativo settore (numero intero da 0 a 9)
- Codice del sensore (numero intero)
- Valore mm pioggia (numero intero)
- Data della misurazione (nel formato aaaa-mm-gg)


Implementare le seguenti funzioni:

1) CaricaMisure: 
Carica le misurazioni dal file 'datiprecipitazioni.txt' e le memorizza in un array di liste. L'elemento i-esimo dell'array contiene la lista delle misurazioni dei sensori relativi al settore i-esimo. La funzione restituisce il numero totale di misurazioni caricate o -1 in caso di errore durante il caricamento.

2) TotaleSettori:
Dato l'array di liste di misurazioni ed un giorno, calcola e restituisce in un vettore il totale delle precipitazioni avvenute quel giorno per ogni singolo settore.

3) ValoriOltreSoglia:
Dato l'array di liste di misurazioni ed un valore soglia, estrae e restituisce in una lista di misurazioni, tutti i dati dei sensori aventi un valore di precipitazioni maggiore del valore soglia fornito come parametro.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SETTORI 10

typedef struct Misura
{
  int  codice;
  int  valore;
  char data[16];
} TMisura;

typedef struct NodoListaMisura
{
  TMisura                 info;
  struct NodoListaMisura* next;
} TNodoListaMisura;

typedef TNodoListaMisura* PNodoListaMisura;


// Visualizza una misurazione
void VisualizzaMisura(TMisura misura) {
  printf("%d %d %s\n", misura.codice,
	 misura.valore, misura.data);
}


// Visualizza le misurazioni di una lista di misurazioni
void VisualizzaDatiLista(PNodoListaMisura lista) {
	// Implementare il corpo della funzione
}

// Aggiunge una misurazione alla lista di misurazioni, restituisce 1
// se l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiNodoLista(PNodoListaMisura* plista, TMisura elem) {
  PNodoListaMisura p;

  p = (PNodoListaMisura)malloc(sizeof(TNodoListaMisura));
  if (p == NULL)
    return 0;

  p->info = elem;
  p->next = *plista;
  *plista = p;
  
  return 1;
}

/*
1) CaricaMisure:
Carica le misurazioni dal file 'datiprecipitazioni.txt' e le memorizza in un array di liste. L'array è composto da 10 elementi. L'elemento i-esimo dell'array contiene la lista delle misurazioni dei sensori relativi al settore i-esimo. La funzione restituisce il numero totale di misurazioni caricate o -1 in caso di errore durante il caricamento.

Parametri: nome del file, array di liste di misurazioni
Restituisce: il numero totale di misurazioni acquisite, -1 in caso di
errore durante il caricamento
*/
int CaricaMisure(char* nome_file, PNodoListaMisura* misure) {
	// Implementare il corpo della funzione

}

/*
2) TotaleSettori:
Dato l'array di liste di misurazioni ed un giorno, calcola e restituisce in un vettore il totale delle precipitazioni avvenute quel giorno per ogni singolo settore.

Parametri: array di liste di misurazioni, giorno
Restituisce: Vettore in l'elemento i-esimo rappresenta il totale delle precipitazioni avvenute quel giorno per il settore i-esimo.
*/

int* TotaleSettori(PNodoListaMisura* misure, char* giorno) {
	// Implementare il corpo della funzione

}


/*
3) ValoriOltreSoglia:
Dato l'array di liste di misurazioni ed un valore soglia, estrae e restituisce in una lista di misurazioni, tutti i dati dei sensori aventi un valore di precipitazioni maggiore del valore soglia fornito come parametro.

Parametri: array di liste di misurazioni, valore soglia di precipitazioni
Restituisce: lista con i dati dei sensori aventi un valore di precipitazioni maggiore del valore soglia fornito come parametro
*/

PNodoListaMisura ValoriOltreSoglia(PNodoListaMisura* misure, int soglia) {
	// Implementare il corpo della funzione

}


//  Disalloca una lista di misurazioni
void DisallocaLista(PNodoListaMisura lista) {
  PNodoListaMisura paux;
  
  while (lista != NULL)
    {
      paux = lista;
      lista = lista->next;
      free(paux);
    }
}

int Menu() {
  int scelta;
  
  printf("*** MENU ***\n"
	 "1. Carica dati dal file\n"
	 "2. Totale settori\n"
	 "3. Valori superiori alla soglia\n"
	 "0. Esci\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

int main(void) {
  int                   scelta;
  PNodoListaMisura vettore[NUM_SETTORI];
  int n;
  char giorno[16];
  int* totalesettori;
  int vsoglia;
  PNodoListaMisura listamaggiori;

  for (int i = 0; i < NUM_SETTORI; i++)
	  vettore[i] = NULL;
  
  do {
    scelta = Menu();

    switch (scelta) {
      case 1:
		  // Invocare la funzione CaricaMisure e visualizzare il numero di
		  // misure caricate o gli eventuali errori

		  break;

      case 2:
		  // acquisire il giorno

		  // invocare la funzione TotaleSettori e visualizzare la pioggia totale per ogni settore

			  
		break;

      case 3:
		  // acquisire il valore soglia di precipitazioni

		  // invocare la funzione ValoriOltreSoglia

		  // visualizzare i risultati ottenuti
		  
		  break;
      }
  } while (scelta != 0);

  //disallocare la memoria

  
  return 0;
}
