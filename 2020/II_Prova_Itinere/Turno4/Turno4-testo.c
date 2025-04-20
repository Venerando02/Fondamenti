/*
Sviluppo di applicazione in ANSI C per gestire i viaggi di una flotta aziendale di veicoli

In un archivio memorizzato su un file di testo (allegato "viaggi.txt") è memorizzato 
l'elenco dei viaggi effettuati dai diversi veicoli.
Ogni viaggio è memorizzato su una riga del file, con i campi: 
id viaggio, targa veicolo, km percorsi, costo viaggio.

Implementare le seguenti funzioni:

1. CaricaViaggi: carica l'elenco dei viaggi effettuati dalla flotta (lettura del file; ogni id viaggio è presente solo una volta nel file).
2. AggiungiViaggio: dato un id viaggio, km e costo, se l'id esiste già in lista si sommano ai valori già presenti in lista, 
in caso contrario inserisce un nuovo viaggio nella lista 
(fornendo da tastiera in tal caso anche la targa)
3. TotaleVeicolo: Data una targa, stampa il totale dei km percorsi ed il costo medio per km di tutti i viaggi ad essa associati

*/


#include ... // Includere gli header di libreria necessari

typedef struct Viaggio {
  char  id_viaggio[5]; 
  char  targa[9];
  int   km;
  float costo;
} TViaggio;

typedef struct NodoLista {
  TViaggio info;
  struct NodoLista* next;
} TNodoLista;

typedef TNodoLista* TipoLista;

/* ListaAggiungi inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int ListaAggiungi(TipoLista* plista, TViaggio viaggio) {
  TipoLista aux;

  aux = (TipoLista)malloc(sizeof(TNodoLista));

  if (aux == NULL)
    return 0;
  
  aux->info = viaggio;
  aux->next = *plista;

  *plista = aux;
  
  return 1;
}

/* 
   1. CaricaViaggi: carica l'elenco dei viaggi effettuati dalla flotta (lettura del file; ogni id viaggio è presente solo una volta nel file) in una lista di viaggi
  Restituisce 1 se l'operazione va a buon fine, 0 altrimenti.
*/
int CaricaViaggi(TipoLista* plista, char* nome_file)
{
  // ... da completare a cura dello studente ...
}

/* 
 2. AggiungiViaggio: dati come parametri di ingresso un id_viaggio, km e costo, 
 se l'id_viaggio esiste già in lista, i km ed il costo si sommano ai valori già presenti in lista, 
	in caso contrario si inserisce un nuovo viaggio nella lista (fornendo da tastiera in tal caso la targa)
*/
void AggiungiViaggio(/* inserire i parametri */)
{
    // ... da completare a cura dello studente ...
}

/*
3. TotaleVeicolo: Data in ingresso una targa, restituisce il totale dei km percorsi di quell'auto 
ed il costo medio per km di tutti i viaggi ad essa associati
*/
void TotaleVeicolo(/* inserire i parametri */)
{
  // ... da completare a cura dello studente ...
}


int Menu() {
  int scelta;
  
  printf("*** M E N U ***\n"
	 "1 - CaricaViaggi\n"
	 "2 - AggiungiViaggio\n"
	 "3 - TotaleVeicolo\n"
	 "0 - Uscita\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

void VisualizzaLista(TipoLista lista) {
    // ... da completare a cura dello studente ...
}


void DisallocaLista(TipoLista lista) {
    // ... da completare a cura dello studente ...
}

int main(void) {
  TipoLista lista;
  int        scelta;
 // allocare le variabili necessarie...

  
  do {
    scelta = Menu();

    switch (scelta)
      {
      case 1:
          // Acquisire il nome del file
          // Invocare la funzione CaricaViaggi e visualizzare un messaggio in caso di errore
          // Visualizzare i dati caricati nella lista
	break;

      case 2:
	// Invocare la funzione AggiungiViaggio, caricando prima da tastiera i valori da passare come parametri
	break;

      case 3:
	// Invocare la funzione TotaleVeicolo, acquisendo preventivamente la targa da tastiera
	// Visualizzare km totali e costo medio per km (restituiti dalla funzione)
	break;
      }
    
  } while (scelta != 0);

  // disallocare la lista
  DisallocaLista(...); // passare il parametro opportuno
  
  return 0;
}

