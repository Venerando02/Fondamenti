/*
Sviluppare un programma per l'analisi delle spese effettuate dai
clienti di un supermercato in una giornata. Le informazioni delle
spese effettuate dai clienti, monitorate da una batteria di 10 casse,
sono salvate in un file di testo in cui ogni riga contiene le seguenti
informazioni:

- Numero cassa (da 0 a 9)
- Orario (formato (hh:mm)
- Tessera fedeltà (si/no)
- Provincia di provenienza cliente
- Totale spesa

Implementare le seguenti funzioni:

1) CaricaDati: Carica i dati contenuti nel file in un array di
liste. L'elemento dell'array di inidice 'i' contiene la lista delle
informazioni di spesa effettuate dai clienti alla cassa numero 'i'. La
funzione restituisce il numero totale di clienti.

2) ContaProvenienze: Data una fascia oraria, ed una provincia di
provenienza restituisce un array in cui l'elemento di indice 'i'
contiene il numero di clienti provenienti da una certa provincia
rilevato dalla cassa numero i.

3) VisualizzaPercentualeClienti: Visualizza, per ogni cassa, la
percentuale di clienti in possesso di tesserà di fedeltà sul totale
dei clienti transitati da quella cassa.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CASSE 10

typedef struct Transito
{
  char  orario[16];
  int   tessera; // 1 = si, 0 = no
  char  cap[16]; // CAP della provincia di provenienza
  float totale;
} TTransito;

typedef struct NodoTransito
{
  TTransito            transito;
  struct NodoTransito* succ;
} TNodoTransito;

typedef TNodoTransito* PNodoTransito;


// Aggiunge un transito alla lista dei transiti, restituisce 1
// se l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiTransito(PNodoTransito* plista,
		     TTransito transito)
{
  PNodoTransito p;

  p = (PNodoTransito)malloc(sizeof(TNodoTransito));
  if (p == NULL)
    return 0;

  p->transito = transito;
  p->succ = *plista;
  *plista = p;
  
  return 1;
}

/*
1) CaricaDati: Carica i dati contenuti nel file in un array di
liste. L'elemento dell'array di inidice 'i' contiene la lista delle
informazioni di spesa effettuate dai clienti alla cassa numero 'i'. La
funzione restituisce il numero totale di clienti.

Parametri: nome del file, array di liste di transiti in cassa 
Restituisce: il numero totale di clienti, -1 in caso di errore
durante il caricamento
*/
int CaricaDati(char* nome_file,
	       PNodoTransito* transiti)
{
  // Implementare il corpo della funzione
}

/*
2) ContaProvenienze: Data una fascia oraria, ed una provincia di
provenienza restituisce un array in cui l'elemento di indice 'i'
contiene il numero di clienti provenienti da una certa provincia
rilevato dalla cassa numero i.

Parametri: fascia oraria (orario inizio e orario fine), provincia di
provenienze, array di liste

Restituisce un array con il numero di clienti provenienti da quella
provincia rilevati in ogni cassa
*/
int* ContaProvenienze(PNodoTransito* transiti,
		      char* orario_inizio, char* orario_fine,
		      char* cap)
{
  // Implementare il corpo della funzione
}

/*
3) VisualizzaPercentualeClienti: Visualizza, per ogni cassa, la
percentuale di clienti in possesso di tesserà di fedeltà sul totale
dei clienti transitati da quella cassa.
*/
void VisualizzaPercentualeClienti(PNodoTransito* transiti)
{
  // Implementare il corpo della funzione
}

//  Disalloca una lista di transiti
void DisallocaTransiti(PNodoTransito transiti)
{
  PNodoTransito p;
  
  while (transiti != NULL)
    {
      p = transiti;
      transiti = transiti->succ;
      free(p);
    }
}

int Menu()
{
  int scelta;
  
  printf("*** MENU ***\n"
	 "1. Carica dati\n"
	 "2. Conta provenienze\n"
	 "3. Visualizza percentuale clienti\n"
	 "0. Esci\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

int main(void)
{
  int           scelta, n;
  PNodoTransito transiti[NUM_CASSE];
  int*          totale_provenienze;
  char          ora_inizio[16], ora_fine[16];
  char          provincia[16];
  

  do {
    scelta = Menu();

    switch (scelta)
      {
      case 1:
	// Invocare la funzione CaricaDati e visualizzare il numero di
	// transiti caricato o gli eventuali errori
	break;

      case 2:
	// Acquisire la fascia oraria e la provincia di provenienza
	// Invocare la funzione ContaProvenienze
	// Visualizzare le provenienze
	break;

      case 3:
	// Invocare la funzione VisualizzaPercentualeClienti
	break;
      }
  } while (scelta != 0);

  // Disallocare la memoria
  
  return 0;
}
