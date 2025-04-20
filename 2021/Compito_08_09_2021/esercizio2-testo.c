/*
Sviluppare un programma per la gestione dei dati raccolti da una rete
di sensori di umidità del terreno e di temperatura in ambto
agricoltura di precisione. Ogni sensore trasmette periodicamente le
seguenti informazioni che sono memorizzate in un file unitamente alla
data e all'orario di ricezione.

- Codice del sensore (numero intero)
- Temperatura attuale (numero intero)
- Umidità attuale (numero intero)
- Data della misurazione (nel formato aaaa-mm-gg)
- Orario della misurazione (nel formato hh:mm:ss)

L'area monitorata è suddivisa in 10 sotto-aree ciascuna delle quali è
monitorata da al più 10 sensori. Il codice del sensore identifica
l'area. Es. Sensori con codice da 0 a 9 identificano la prima area,
quelli da 10 a 19 la seconda area, ..., quelli da 90 a 99 la
decima area.

Implementare le seguenti funzioni:

1) CaricaMisurazioni: Carica le misurazioni dal file 'misurazioni.txt'
e le memorizza in un array di liste. L'elemento i-esimo dell'array
contiene la lista delle misurazioni dei sensori relativi all'area
i-esima (sensori con codice da i*10 a i*10+10-1). La funzione
restituisce il numero totale di misurazioni caricate o -1 in caso di
errore durante il caricamento.

2) MisurazioniAnno: Dato l'array di liste di misurazioni, un
anno di riferimento ed il codice di un sensore, restituisce la lista
delle misurazioni di quel sensore relativo all'anno di riferimento.

3) VisualizzaMisureIntervallo: Dato l'array di liste di misurazioni,
un intervallo di temperature ed un intervallo di umidità, visualizza
tutte le misurazioni con temperatura e umidità compresi negli
intervalli dati.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funzione nello scheletro
di programma fornito.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_AREE 10

typedef struct Misurazione
{
  int  codice;
  int  temperatura;
  int  umidita;
  char data[16];
  char orario[16];
} TMisurazione;

typedef struct NodoListaMisurazioni
{
  TMisurazione                 misurazione;
  struct NodoListaMisurazioni* succ;
} TNodoListaMisurazioni;

typedef TNodoListaMisurazioni* PNodoListaMisurazioni;


// Visualizza una misurazione
void VisualizzaMisurazione(TMisurazione misurazione)
{
  printf("%d %d %d %s %s\n", misurazione.codice,
	 misurazione.temperatura, misurazione.umidita,
	 misurazione.data, misurazione.orario);
}


// Visualizza le misurazioni di una lista di misurazioni
void VisualizzaMisurazioni(PNodoListaMisurazioni lista)
{
  printf("codice temperatura umidità data orario\n");
  while (lista != NULL)
    {
      VisualizzaMisurazione(lista->misurazione);
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
e le memorizza in un array di liste. L'array è composto da 5
elementi. L'elemento i-esimo dell'array contiene la lista delle
misturazioni dei sensori dal codice i*10 al codice i*10+10-1. La
funzione restituisce il numero totale di misurazioni caricate o -1 in
caso di errore durante il caricamento.

Parametri: nome del file, array di liste di misurazioni
Restituisce: il numero totale di misurazioni acquisite, -1 in caso di
errore durante il caricamento
*/
int CaricaMisurazioni(char* nome_file,
		      PNodoListaMisurazioni* misurazioni)
{
  // Sviluppare il corpo della funzione
  // ...
}

/*
2) MisurazioniAnno: Dato l'array di liste di misurazioni, un anno di
riferimento ed il codice di un sensore, restituisce la lista delle
misurazioni di quel sensore relativo all'anno di riferimento.

Parametri: array di liste di misurazioni, anno di riferimento, codice
sensore
Restituisce: Lista di misurazioni del sensore nell'anno di riferimento
*/
PNodoListaMisurazioni MisurazioniAnno(PNodoListaMisurazioni* misurazioni,
				      char* anno, int codice)
{
  // Sviluppare il corpo della funzione
  // ...
}

/*
3) VisualizzaMisureIntervallo: Dato l'array di liste di misurazioni,
un intervallo di temperature ed un intervallo di umidità, visualizza
tutte le misurazioni con temperatura e umidità compresi negli
intervalli dati.

Parametri: array di liste di misurazioni, temperatura minima,
temperatura massima, umidità minima, umidità massima
*/
void VisualizzaMisureIntervallo(PNodoListaMisurazioni* misurazioni,
				int temperatura_min, int temperatura_max,
				int umidita_min, int umidita_max)
{
  // Sviluppare il corpo della funzione
  // ...
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

int Menu()
{
  int scelta;
  
  printf("*** MENU ***\n"
	 "1. Carica misurazioni\n"
	 "2. Misurazioni anno\n"
	 "3. Misurazioni intervallo\n"
	 "0. Esci\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

int main(void)
{
  int                   scelta;
  // dichiarare le variabili necessarie
  
  do {
    scelta = Menu();

    switch (scelta)
      {
      case 1:
	// Invocare la funzione CaricaMisurazioni e visualizzare il
	// numero di misurazioni caricate o l'eventuale messaggio di
	// errore
	break;

      case 2:
	// Acquisire l'anno ed il codice del sensore, invocare la
	// funzione MisurazioniAnno, visualizzare la lista delle
	// misurazioni ottenuta e disallocare la lista.
	break;

      case 3:
	// Acquisire gli intervalli di temperatura e di umidità ed
	// invocare la funzione VisualizzaMisureIntervallo
	break;
      }
  } while (scelta != 0);

  // Disallocare le liste nel vettore delle misurazioni
  
  return 0;
}
