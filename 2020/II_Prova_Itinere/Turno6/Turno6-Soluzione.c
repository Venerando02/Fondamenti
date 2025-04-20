/*
Sviluppo di applicazione in ANSI C per gestire i punti fedeltà di un
supermercato.

Su un archivio (allegato all'attività 'spesa.txt') è memorizzato lo
storico degli acquisti dei clienti di un supermercato
(transazioni). L'archivio è un file di testo in cui ogni riga riporta,
separati da spazio, le seguenti informazioni: codice cliente, data,
importo della spesa, saldo punti. Ogni 10 euro di spesa, il cliente
guadagna 1 punto fedeltà. Il cliente, a fronte di una spesa minima di
50 euro utilizzarà 50 punti fedeltà per ricevere uno sconto di 5 euro
sul totale della spesa. I saldo punti verrà aggiornato in base
all'importo effettivamente pagato. E' possibile utilizzare al più 50
punti per transazione.

Alcuni esempi:

1) Saldo punti 30, Importo spesa 100 euro --> Importo pagato 100 euro, saldo punti 40

2) Saldo punti 200, Importo spesa 100 euro --> Importo pagato 95 euro, saldo punti 200-50+9=159


Implementare le seguenti funzioni:

1. CaricaStorico: carica lo storico in una lista di transazioni.

2. ServizioCassa: aggiunge una transazione alla lista delle
transazioni.

3. SpesaMensile: calcola l'importo mensile per spesa di un cliente

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funione.
*/

// Includere gli header di libreria necessari
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE "spesa.txt"

typedef struct Transazione
{
  char  codice[8];
  char  data[11]; // nel formato gg/mm/aaaa
  float totale_euro;
  int   saldo_punti;
} TTransazione;

typedef struct NodoLista
{
  TTransazione      transazione;
  struct NodoLista* next;
} TNodoLista;

typedef TNodoLista* TipoLista;

/* ListaAggiungi inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int ListaAggiungi(TipoLista* plista, TTransazione transazione)
{
  TipoLista aux;

  aux = (TipoLista)malloc(sizeof(TNodoLista));

  if (aux == 0)
    return 0;
  
  aux->transazione = transazione;
  aux->next = *plista;

  *plista = aux;
  
  return 1;
}

/* 
   1. CaricaStorico: carica lo storico in una lista di
   transazioni. Restituisce 1 se l'operazione va a buon fine, 0
   altrimenti.
*/
int CaricaStorico(TipoLista* plista, char* nome_file)
{
  FILE*        f;
  TTransazione transazione;

  
  *plista = NULL;
  
  f = fopen(nome_file, "r");
  if (f == NULL)
    return 0;

  while (!feof(f))
    {
      if (fscanf(f, "%s %s %f %d",
		 transazione.codice, transazione.data,
		 &transazione.totale_euro, &transazione.saldo_punti) == 4)
	if (!ListaAggiungi(plista, transazione))
	  break;
    }
  
  fclose(f);
  
  return 1;
}

/* 
   2. ServizioCassa: aggiunge una transazione alla lista delle
   transazioni. Dato il codice_cliente, la data, e l'importo della
   spesa, viene aggiunta una nuova transazione in testa alla lista. Il
   campo saldo_punti della transazione aggiunta dovrà essere
   opportunamente aggiornato in base a quanto descritto nel testo del
   compito. Il saldo attuale del cliente è quello dell'ultima
   transizione effettuata dal cliente (quindi quella più vicina alla
   testa della lista).
*/
void ServizioCassa(TipoLista* lista,
		   char* codice_cliente, char* data, float importo)
{
  TipoLista   p;
  int          saldo_punti;
  TTransazione transazione;

  
  // Cerco il saldo punti del cliente
  p = *lista;
  while (p != NULL && strcmp(codice_cliente, p->transazione.codice) != 0)
    p = p->next;

  if (p == NULL)
    saldo_punti = 0;
  else
    saldo_punti = p->transazione.saldo_punti;

  if (importo > 50 && saldo_punti >= 50)
    {
      importo = importo - 5;
      saldo_punti = saldo_punti - 50 + (int)importo/10;
    }

  strcpy(transazione.codice, codice_cliente);
  strcpy(transazione.data, data);
  transazione.totale_euro = importo;
  transazione.saldo_punti = saldo_punti;

  ListaAggiungi(lista, transazione);
}

/*
3. SpesaMensile: calcola l'importo mensile per spesa di un
cliente. Dato il codice cliente, la funzione restituisce un array che
per ogni mese dell'anno riporta il totale degli importi per la spesa
effettuata da quel cliente.
*/
void SpesaMensile(TipoLista lista,
		  char* codice_cliente, float* spesa_per_mese)
{
  int giorno, mese, anno;
  
  for (int i=0; i<12; i++)
    spesa_per_mese[i] = 0.0;
  
  while (lista != NULL)
    {
      if (strcmp(lista->transazione.codice, codice_cliente) == 0)
	{
	  sscanf(lista->transazione.data, "%d/%d/%d", &anno, &mese, &giorno);
	  
	  spesa_per_mese[mese-1] += lista->transazione.totale_euro;
	}
      
      lista = lista->next;
    }
}


int Menu()
{
  int scelta;
  
  printf("*** M E N U ***\n"
	 "1 - CaricaStorico\n"
	 "2 - ServizioCassa\n"
	 "3 - SpesaMensile\n"
	 "0 - Uscita\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

void DisallocaLista(TipoLista lista)
{
  TipoLista p;

  while (lista != NULL)
    {
      p = lista;
      lista = lista->next;
      free(p);
    }
}

int main(void)
{
  TipoLista lista;
  int        scelta;
  float      spesa_mensile[12];
  char       codice[8];
  char       data[11];
  float      importo;

  
  do {
    scelta = Menu();

    switch (scelta)
      {
      case 1:
	if (!CaricaStorico(&lista, NOME_FILE))
	  printf("Errore durante l'apertura di %s\n", NOME_FILE);
	break;

      case 2:
	printf("Codice cliente, data, importo: ");
	scanf("%s %s %f", codice, data, &importo);
	ServizioCassa(&lista, codice, data, importo);
	break;

      case 3:
	printf("Codice cliente: ");
	scanf("%s", codice);
	SpesaMensile(lista, codice, spesa_mensile);
	for (int i=0; i<12; i++)
	  printf("Spesa mese %d: %.2f euro\n", i+1, spesa_mensile[i]);
	break;
      }
    
  } while (scelta != 0);

  DisallocaLista(lista);
  
  return 0;
}
