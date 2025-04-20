/*
  Sviluppo di applicazione in ANSI C per gestire 
  le prenotazioni delle aule universitarie.

  In un file di testo ("prenotazioni.txt"), è memorizzato 
  l'elenco delle prenotazioni effettuate dei docenti.
  Così come visibile nel file, per ciascuna prenotazione
  sono memorizzate le seguenti informazioni:
  - aula (numero intero)
  - nome del docente che ha prenotato quell'aula (stringa di 15 caratteri utili senza spazi)
  - data prenotazione (nel formato aaaa/mm/gg)
  - orario inizio e orario fine prenotazione (nel formato hh:mm)

  Implementare le seguenti funzioni:

  1. CaricaPrenotazioni: carica l'elenco delle prenotazioni in una
  lista di prenotazioni.

  2. CreaListaAule: a partire dalla lista delle prenotazioni,
  costruisce una lista di stanze in cui, per ogni aula, ci sia
  il numero di prenotazioni e la lista delle prenotazioni per quella
  specifica aula.

  3. AulePrenotate: date una data ed un orario restituisce un array
  contenente l'elenco delle aule prenotate in quel giorno e a
  quell'ora.

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funzione.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE  "prenotazioni.txt"

typedef struct Prenotazione
{
  int  id_aula;
  char nome_docente[16];
  char data[11];
  char ora_inizio[6];
  char ora_fine[6];
} TPrenotazione;

typedef struct NodoListaPrenotazioni
{
  TPrenotazione                 prenotazione;
  struct NodoListaPrenotazioni* succ;
} TNodoListaPrenotazioni;

typedef TNodoListaPrenotazioni* PNodoListaPrenotazioni;

typedef struct NodoListaAule
{
  int                    id_aula;
  int                    num_prenotazioni;
  PNodoListaPrenotazioni lista_prenotazioni;
  struct NodoListaAule*  succ;
} TNodoListaAule;

typedef TNodoListaAule* PNodoListaAule;


/* AggiungiPrenotazione inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiPrenotazione(PNodoListaPrenotazioni* prenotazioni, TPrenotazione prenotazione)
{
  PNodoListaPrenotazioni aux;

  aux = (PNodoListaPrenotazioni)malloc(sizeof(TNodoListaPrenotazioni));

  if (aux == 0)
    return 0;
  
  aux->prenotazione = prenotazione;
  aux->succ = *prenotazioni;

  *prenotazioni = aux;
  
  return 1;
}

/*
  1. CaricaPrenotazioni: carica l'elenco delle prenotazioni in una
  lista di prenotazioni.

  Parametri di ingresso: nome del file
  Parametri di uscita: lista delle prenotazioni (PNodoListaPrenotazioni)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
 */
int CaricaPrenotazioni(char* nome_file, PNodoListaPrenotazioni* prenotazioni)
{
  // implementare la funzione
}

/* 
   AggiungiAula inserisce un elemento in testa alla lista passata
   come parametro. Restituisce la nuova testa della lista
*/
PNodoListaAule AggiungiAula(PNodoListaAule aule, int id_aula)
{
  PNodoListaAule aux;

  aux = (PNodoListaAule)malloc(sizeof(TNodoListaAule));
  
  aux->id_aula = id_aula;
  aux->num_prenotazioni = 0;
  aux->lista_prenotazioni = NULL;
  aux->succ = aule;
  
  return aux;
}

/*
  CercaAula restituisce il puntatore al nodo della lista delle aule
  per una specifica aula. Restituisce NULL se quella aula non è
  presente nella lista delle aule.
 */
PNodoListaAule CercaAula(PNodoListaAule aule, int id_aula)
{
  // Implementare la funzione
}

/*
  AggiungiPrenotazioneInAula aggiunge una prenotazione nella lista delle
  prenotazioni relative alla specifica aula.
 */
void AggiungiPrenotazioneInAula(PNodoListaAule* plista_aule, TPrenotazione prenotazione)
{
  PNodoListaAule p;
  
  p = CercaAula(*plista_aule, prenotazione.id_aula);
  if (p == NULL)
    {
      p = AggiungiAula(*plista_aule, prenotazione.id_aula);
      *plista_aule = p;
    }

  if (AggiungiPrenotazione(&p->lista_prenotazioni, prenotazione))
    (p->num_prenotazioni)++;
}

/* 
   2. CreaAule: a partire dalla lista delle prenotazioni, costruisce una
   lista di aule in cui, per ogni aula, ci sia il numero e
   la lista delle prenotazioni per quella specifica aula.

   Parametri di ingresso: lista delle prenotazioni
   Parametri di uscita: lista delle aule
*/
PNodoListaAule CreaAule(PNodoListaPrenotazioni prenotazioni)
{
  // Implementare la funzione
}

int OrarioInPrenotazione(char* orario, char* ora_inizio, char* ora_fine)
{
  return (strcmp(orario, ora_inizio) >= 0 &&
	  strcmp(orario, ora_fine) < 0);
}


/*
  3. AulePrenotate: date una data ed un orario restituisce un array
  contenente l'elenco delle aule prenotate in quel giorno e a
  quell'ora.

  Parametri di ingresso: lista delle aule, data, orario
  Parametri di uscita: array delle aule
*/
int* AulePrenotate(PNodoListaAule aule,
		   char* data, char* orario, int* n)
{
  // Implementare la funzione
}


int Menu()
{
  int scelta;
  
  printf("*** M E N U ***\n"
	 "1 - Carica prenotazioni\n"
	 "2 - Crea aule\n"
	 "3 - Aule prenotate\n"
	 "0 - Uscita\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

void DisallocaListaPrenotazioni(PNodoListaPrenotazioni lista)
{
  PNodoListaPrenotazioni p;

  while (lista != NULL)
    {
      p = lista;
      lista = lista->succ;
      free(p);
    }
}

void DisallocaListaAule(PNodoListaAule lista)
{
  PNodoListaAule p;

  while (lista != NULL)
    {
      DisallocaListaPrenotazioni(lista->lista_prenotazioni);
      p = lista;
      lista = lista->succ;
      free(p);
    }
}

int main(void)
{
  PNodoListaPrenotazioni prenotazioni = NULL;
  PNodoListaAule         aule = NULL;
  int                    scelta, n;
  char                   orario[6];
  char                   data[11];
  int*                   id_aule;

  
  do {
    scelta = Menu();

    switch (scelta)
      {
      case 1:
	// Invocare la funzione CaricaPrenotazioni e visualizzare un
	// messaggio di errore se il caricamento non va a buon fine    
	break;

      case 2:
	// Invocare la funzione CreaAule
	break;

      case 3:
	// Acquisire data e orario, invocare la funzione AulePrenotate
	// e visualizzare l'elenco delle aule prenotate in quella data
	// e a quell'orario.
	break;
      }
    
  } while (scelta != 0);

  // Didsallocare le lista
  DisallocaListaPrenotazioni(/* parametri */);
  DisallocaListaAule(/* parametri */);

  return 0;
}
