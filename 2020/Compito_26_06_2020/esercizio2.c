/*
Sviluppo di applicazione in ANSI C per gestire i clienti di uno
stabilimento balneare.

Su un archivio (allegato all'attività 'clienti.txt') è memorizzato
l'elenco dei clienti di uno stabilimento balneare con 100 cabine. Ogni
cliente firma un contratto che gli consente l'utilizzo esclusivo di
una cabina e l'ingresso allo stabilimento ad un numero di persone pari
al numero di tesserini acquistati. Il file contiene in ogni riga, il
codice del cliente, il numero di tesserini ed il numero della cabina
(da 0 a 99).

Implementare le seguenti funzioni:

1. CaricaClienti: carica l'elenco dei clienti in una lista clienti.

2. Ingresso: aggiorna un vettore di liste che in ogni posizione
(corrispondente ad una cabina) contiene la lista delle persone
attualmente in quella cabina.

3. CabineVuote: restituisce un array che contiene i numeri di cabine
vuote (cioè quelle per cui nessun tesserino è stato utilizzato).

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funione.
*/


#include ... // includere gli header di libreria necessari

#define NOME_FILE  "clienti.txt"
#define NUM_CABINE 100

typedef struct Cliente
{
  char  codice[8];
  int   n_tesserini;
  int   n_cabina;
} TCliente;

typedef struct NodoListaClienti
{
  TCliente                 cliente;
  struct NodoListaClienti* succ;
} TNodoListaClienti;

typedef TNodoListaClienti* PNodoListaClienti;

typedef struct Persona
{
  char nome[16];
  char cognome[16];
} TPersona;

typedef struct NodoListaPersone
{
  TPersona                 persona;
  struct NodoListaPersone* succ;
} TNodoListaPersone;

typedef TNodoListaPersone* PNodoListaPersone;


/* AggiungiCliente inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiCliente(PNodoListaClienti* clienti, TCliente cliente)
{
  PNodoListaClienti aux;

  aux = (PNodoListaClienti)malloc(sizeof(TNodoListaClienti));

  if (aux == 0)
    return 0;
  
  aux->cliente = cliente;
  aux->succ = *clienti;

  *clienti = aux;
  
  return 1;
}

/*
  1. CaricaClienti: carica l'elenco dei clienti in una lista clienti.

  Parametri di ingresso: nome del file
  Parametri di uscita: lista dei clienti (PNodoListaClienti)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
 */
int CaricaClienti(char* nome_file, PNodoListaClienti* clienti)
{
  // ... a cura dello studente ...
}

/*
  Cerca un cliente nella lista dei clienti in base al codice_cliente.
  Restituisce 1 se cliente trovato, 0 altrimenti
 */
int CercaCliente(PNodoListaClienti clienti, char* codice_cliente,
		 TCliente* cliente)
{
  while (clienti != NULL &&
	 strcmp(clienti->cliente.codice, codice_cliente) != 0)
    clienti = clienti->succ;

  if (clienti != NULL)
    *cliente = clienti->cliente;

  return (clienti != NULL);
}

/*
  Restituisce il numero di persone nella lista delle persone
*/
int ContaPersone(PNodoListaPersone persone)
{
  int conta = 0;

  while (persone != NULL)
    {
      conta++;
      persone = persone->succ;
    }
  
  return conta;
}

/* 
   AggiungiPersona inserisce un elemento in testa alla lista passata
   come parametro. Restituisce la nuova testa della lista
*/
PNodoListaPersone AggiungiPersona(PNodoListaPersone persone, TPersona persona)
{
  PNodoListaPersone aux;

  aux = (PNodoListaPersone)malloc(sizeof(TNodoListaPersone));
  
  aux->persona = persona;
  aux->succ = persone;
  
  return aux;
}

/* 
   2. Ingresso: aggiorna un vettore di liste che in ogni posizione
   (corrispondente ad una cabina) contiene la lista delle persone
   attualmente in quella cabina. La funzione verifica che il numero di
   persone in quella cabina sia inferiore al numero di tesserini prima
   di accettare l'ingresso.

   Parametri di ingresso: lista dei clienti, persona, codice_cliente
   Parametri di uscita: vettore di liste di persone 
   Valore restituito: -1 se codice_cliente non esiste, -2 se tutti i
   tesserini sono stati utilizzati, 0 ingresso accettato
*/
int Ingresso(PNodoListaClienti clienti,
	     TPersona           persona,
	     char*              codice_cliente,
	     PNodoListaPersone* persone_in_cabina)
{
  // ...a cura dello studente...
  // Suggerimento: sfruttare le funzioni CercaCliente, ContaPersone e AggiungiPersona
}

/*
  3. CabineVuote: restituisce un array che contiene i numeri di cabine
  vuote.
*/
int* CabineVuote(PNodoListaPersone* persone_in_cabina,
		 int* ncabine_vuote)
{
  // ...a cura dello studente...
}

int Menu()
{
  int scelta;
  
  printf("*** M E N U ***\n"
	 "1 - Carica clienti\n"
	 "2 - Ingresso\n"
	 "3 - Cabine vuote\n"
	 "0 - Uscita\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

void DisallocaListaClienti(PNodoListaClienti lista)
{
  PNodoListaClienti p;

  while (lista != NULL)
    {
      p = lista;
      lista = lista->succ;
      free(p);
    }
}

void DisallocaListaPersone(PNodoListaPersone lista)
{
  PNodoListaPersone p;

  while (lista != NULL)
    {
      p = lista;
      lista = lista->succ;
      free(p);
    }
}

int main(void)
{
  PNodoListaClienti clienti;
  PNodoListaPersone persone[NUM_CABINE];
  int        scelta;
  int*       cabine_vuote;
  int        ncabine_vuote;
  int        esito;
  TPersona   persona;
  char       codice_cliente[8];

  
  for (int i=0; i<NUM_CABINE; i++)
    persone[i] = NULL;
  
  do {
    scelta = Menu();

    switch (scelta)
      {
      case 1:
	// Invocare la funzione CaricaClienti e visualizzare un messaggio in caso di errore
	// ...
	break;

      case 2:
	// Acquisire i dati della persona, e il codice cliente
	// ...
	
	// Invocare la funzione Ingresso
	// ...
	break;

      case 3:
	// Invocare la funzione CabineVuote
	// ...

	// Visualizzare l'elenco delle cabine vuote
	// ...

	// Disallocare l'array delle cabine vuote
	// ...
	break;
      }
    
  } while (scelta != 0);

  // Didsallocare la lista dei clienti
  DisallocaListaClienti(...); // specificare il parametri opportuni

  // Disallocare il vettore delle liste di persone (sfruttare la
  // funzione DisallicaListaPersone()
  // ...

  return 0;
}

