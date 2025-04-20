/*
Sviluppare un programma per la gestione dei dati raccolti da 10
stazioni meteorologiche. Ogni stazione è identificata da un codice
numerico (un numero intero compreso tra 0 e 9) e fornisce ad un
concentratore i dati meteo acquisiti. Il concentratore memorizza su un
file di testo le informazioni ricevute dalle stazioni (una riga per
ogni misurazione ricevuta) come di seguito:

- Codice della stazione (numero intero)
- Temperatura giornaliera media (numero intero)
- Temperatura giornaliera massima (numero intero)
- Temperatura giornaliera minima (numero intero)
- Umidità giornaliera media (numero intero)
- Data della misurazione (nel formato aaaa-mm-gg)

Implementare le seguenti funzioni:

1) CaricaMisurazioni: Carica le misurazioni dal file 'misurazioni.txt'
e le memorizza in un array di liste. L'elemento di indice 'i'
dell'array contiene il puntatore alla lista delle misurazioni
trasmesse dalla stazione di codice 'i'. La funzione restituisce il
numero di misurazioni caricate o -1 in caso di errore durante il
caricamento.

2) MisurazioniStazioneMese: Dato l'array di liste di misurazioni, un
anno di riferimento ed il codice di una stazione, restituisce la ista
delle misurazioni di quella stazione relative all'anno di riferimento.

3) EscursioneTermica: Dato l'array di liste di misurazioni, ed un anno
di riferimento, restituisce un array in cui l'elemento di posizione
'i' rappresenta l'escursione massima di temperatura giornaliera
rilevata dalla stazione di codice 'i' nell'anno di riferimento. Se una
generica stazione non ha effettuato misurazioni nell'anno di
riferimento, restituisce -1.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_STAZIONI 10

typedef struct Misurazione
{
  int  temp_media;
  int  temp_min;
  int  temp_max;
  int  umidita;
  char data[16];
} TMisurazione;

typedef struct NodoListaMisurazioni
{
  TMisurazione                 misurazione;
  struct NodoListaMisurazioni* succ;
} TNodoListaMisurazioni;

typedef TNodoListaMisurazioni* PNodoListaMisurazioni;


// Visualizza le misurazioni di una lista di misurazioni
void VisualizzaMisurazioni(PNodoListaMisurazioni lista)
{
  printf("temp_media temp_min temp_max umidita data\n");
  while (lista != NULL)
    {
      printf("%d %d %d %d %s\n", lista->misurazione.temp_media,
	     lista->misurazione.temp_max, lista->misurazione.temp_min,
	     lista->misurazione.umidita, lista->misurazione.data);
      lista = lista->succ;
    }
}

// Aggiunge una misurazione alla lista di misurazioni, restituisce 1
// se l'inserimento in lista è avvenuto correttamente, 0 altrimenti
int AggiungiMisurazione(PNodoListaMisurazioni* plista,
			TMisurazione misurazione)
{
  PNodoListaMisurazioni p;

  p = (PNodoListaMisurazioni)malloc(sizeof(TNodoListaMisurazioni));
  if (p == NULL)
    return 0;

  p->misurazione = misurazione;
  p->succ = *plista;
  *plista = p;
  
  return 1;
}

/*
1) CaricaMisurazioni: Carica le misurazioni dal file 'misurazioni.txt'
e le memorizza in un array di liste. L'elemento di indice 'i'
dell'array contiene il puntatore alla lista delle misurazioni
trasmesse dalla stazione di codice 'i'. La funzione restituisce il
numero di misurazioni caricate o -1 in caso di errore durante il
caricamento.

Parametri: nome del file, array di liste di misurazioni
Restituisce: il numero totale di misurazioni acquisite, -1 in caso di
errore durante il caricamento
*/
int CaricaMisurazioni(char* nome_file,
		      PNodoListaMisurazioni* stazioni)
{
  // implementazione a cura dello studente
}

/*
2) MisurazioniStazioneMese: Dato l'array di liste di misurazioni, un
anno di riferimento ed il codice di una stazione, restituisce la lista
delle misurazioni di quella stazione relative all'anno di riferimento.

Parametri: array di liste di misurazioni, anno di riferimento, numero
stazione 
Restituisce: Lista di misurazioni della stazione nell'anno di
riferimento
*/
PNodoListaMisurazioni MisurazioniStazioneMese(PNodoListaMisurazioni* stazioni,
					      char* anno, int num_stazione)
{
  // implementazione a cura dello studente
}

/*
3) EscursioneTermica: Dato l'array di liste di misurazioni, ed un anno
di riferimento, restituisce un array in cui l'elemento di posizione
'i' rappresenta l'escursione massima di temperatura giornaliera
rilevata dalla stazione di codice 'i' nell'anno di riferimento. Se una
generica stazione non ha effettuato misurazioni nell'anno di
riferimento, restituisce -1.

Parametri: array di liste di misurazioni, anno di riferimento
Restituisce: array delle escursioni termiche per ogni stazione
nell'anno di riferimento
*/
int* EscursioneTermica(PNodoListaMisurazioni* stazioni,
		       char* anno)
{
  // implementazione a cura dello studente
}

//  Disalloca una lista di misurazioni
void DisallocaMisurazioni(PNodoListaMisurazioni misurazioni)
{
  PNodoListaMisurazioni p;
  
  while (misurazioni != NULL)
    {
      p = misurazioni;
      misurazioni = misurazioni->succ;
      free(p);
    }
}

// Disalloca le liste nell'array di liste
void DisallocaStazioni(PNodoListaMisurazioni* stazioni)
{
  // implementazione a cura dello studente (suggerimento: sfruttare la
  // funzione DisallocaMisurazioni)
}

int Menu()
{
  int scelta;
  
  printf("*** MENU ***\n"
	 "1. Carica misurazioni\n"
	 "2. Misurazioni stazione mese\n"
	 "3. Escursione termica\n"
	 "0. Esci\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

int main(void)
{
  int scelta;
  /* dichiarare le altre variabili necessarie */
  
  do {
    scelta = Menu();

    switch (scelta)
      {
      case 1:
	// Invocare la funzione CaricaMisurazioni e visualizzare il
	// numero totale di misurazioni acquisite od un messaggio di
	// errore in caso di errore durante il caricamento
	break;

      case 2:
	// Acquisire l'anno ed il numero della stazione, invocare la
	// funzione MisurazioniStazioneMese e visualizzare la lista
	// delle misurazioni restituita dalla funzione
	break;

      case 3:
	// Acquisire l'anno, invocare la funzione EscursioneTermica e
	// visualizzare l'array delle escursioni massime restituito
	// dalla funzione
	break;
      }
  } while (scelta != 0);

  DisallocaStazioni(/* parametri */);
  
  return 0;
}
