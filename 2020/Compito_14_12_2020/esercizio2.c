/*
  Sviluppo di applicazione in ANSI C per gestire un sistema di
  un termostato che opera come di seguito.

  Su un archivio (allegato all'attività 'termostato.txt') è
  memorizzato l'elenco delle fasce orarie in cui attivare il
  riscaldamento nelle diversa stanze di un edificio. Ogni rga del file
  contiene le segienti informazioni: ora_attivazione,
  ora_disattivazione, id_stanza.

  Implementare le seguenti funzioni:

  1. CaricaFasceOrarie: carica l'elenco delle fasce orarie in una
  lista di fasce orarie.

  2. CreaListaStanze: a partire dalla lista delle fasce orarie,
  costruisce una lista di stanze in cui, per ogni area stanza, ci sia
  il numero di fasce orarie e la lista delle fasce orarie per quella
  specifica stanza.

  3. RiscaldamentoAttivo: dato un orario restituisce un array
  contenente l'id delle stanze che a quell'orario hanno il
  riscaldamento attivato.

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funione.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE  "termostato.txt"

typedef struct FasciaOraria
{
  int  id_stanza;
  char ora_inizio[6]; // formato hh:mm
  char ora_fine[6];   // formato hh:mm
} TFasciaOraria;

typedef struct NodoListaFasceOrarie
{
  TFasciaOraria                fascia_oraria;
  struct NodoListaFasceOrarie* succ;
} TNodoListaFasceOrarie;

typedef TNodoListaFasceOrarie* PNodoListaFasceOrarie;

typedef struct NodoListaStanze
{
  int                     id_stanza;
  int                     num_fasce_orarie;
  PNodoListaFasceOrarie   lista_fasce_orarie;
  struct NodoListaStanze* succ;
} TNodoListaStanze;

typedef TNodoListaStanze* PNodoListaStanze;


/* AggiungiFasciaOraria inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiFasciaOraria(PNodoListaFasceOrarie* fasce_orarie, TFasciaOraria fascia_oraria)
{
  PNodoListaFasceOrarie aux;

  aux = (PNodoListaFasceOrarie)malloc(sizeof(TNodoListaFasceOrarie));

  if (aux == 0)
    return 0;
  
  aux->fascia_oraria = fascia_oraria;
  aux->succ = *fasce_orarie;

  *fasce_orarie = aux;
  
  return 1;
}

/*
  1. CaricaFasceOrarie: carica l'elenco delle fasce orarie in una lista
  di fasce orarie.

  Parametri di ingresso: nome del file
  Parametri di uscita: lista delle fasce orarie (PNodoListaFasceOrarie)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
 */
int CaricaFasceOrarie(char* nome_file, PNodoListaFasceOrarie* fasce_orarie)
{
  // ...a cura dello studente...
}

/* 
   AggiungiStanza inserisce un elemento in testa alla lista passata
   come parametro. Restituisce la nuova testa della lista
*/
PNodoListaStanze AggiungiStanza(PNodoListaStanze stanze, int id_stanza)
{
  PNodoListaStanze aux;

  aux = (PNodoListaStanze)malloc(sizeof(TNodoListaStanze));
  
  aux->id_stanza = id_stanza;
  aux->num_fasce_orarie = 0;
  aux->lista_fasce_orarie = NULL;
  aux->succ = stanze;
  
  return aux;
}

/*
  CercaStanza restituisce il puntatore al nodo della lista delle stanze
  per una specifica stanza. Restituisce NULL se quella stanza non è
  presente nella lista delle stanze.
 */
PNodoListaStanze CercaStanza(PNodoListaStanze stanze, int id_stanza)
{
  while (stanze != NULL)
    {
      if (stanze->id_stanza == id_stanza)
	return stanze;

      stanze = stanze->succ;
    }

  return NULL;
}

/*
  AggiungiFascia_OrariaInStanza aggiunge una fascia_oraria nella lista delle
  fasce_orarie relative alla specifica stanza.
 */
void AggiungiFasciaOrariaInStanza(PNodoListaStanze* plista_stanze, TFasciaOraria fascia_oraria)
{
  PNodoListaStanze p;
  
  p = CercaStanza(*plista_stanze, fascia_oraria.id_stanza);
  if (p == NULL)
    {
      p = AggiungiStanza(*plista_stanze, fascia_oraria.id_stanza);
      *plista_stanze = p;
    }

  if (AggiungiFasciaOraria(&p->lista_fasce_orarie, fascia_oraria))
    (p->num_fasce_orarie)++;
}

/* 
   2. CreaStanze: a partire dalla lista delle fasce_orarie, costruisce una
   lista di stanze in cui, per ogni stanza, ci sia il numero e
   la lista delle fasce_orarie per quella specifica stanza.

   Parametri di ingresso: lista delle fasce_orarie
   Parametri di uscita: lista delle stanze
*/
PNodoListaStanze CreaStanze(PNodoListaFasceOrarie fasce_orarie)
{
  // ...a cura dello studente...
}

// Restituisce 1 se orario è all'interno della fascia oraria da
// ora_inizio a ora_fine. Restituise 0 altrimenti
int OrarioInFasciaOraria(char* orario, char* ora_inizio, char* ora_fine)
{
  // ...a cura dello student ...
}


/*
  3. RiscaldamentoAttivo: dato un orario restituisce un array
  contenente l'id delle stanze in cui è attivo il riscaldamento a
  quell'ora.

  Parametri di ingresso: lista delle stanze, orario
  Parametri di uscita: array delle stanze
*/
int* RiscaldamentoAttivo(PNodoListaStanze stanze,
			 char* orario, int* n)
{
  // ...a cura dello studente...
}


int Menu()
{
  int scelta;
  
  printf("*** M E N U ***\n"
	 "1 - Carica dati termostato\n"
	 "2 - Crea stanze\n"
	 "3 - Stanze riscaldate\n"
	 "0 - Uscita\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

void DisallocaListaFasceOrarie(PNodoListaFasceOrarie lista)
{
  PNodoListaFasceOrarie p;

  while (lista != NULL)
    {
      p = lista;
      lista = lista->succ;
      free(p);
    }
}

void DisallocaListaStanze(PNodoListaStanze lista)
{
  // ...a cura dello studente...
}

int main(void)
{
  PNodoListaFasceOrarie fasce_orarie = NULL;
  PNodoListaStanze      stanze = NULL;
  int                   scelta, n;
  char                  orario[16];
  int*                  id_stanze;

  
  do {
    scelta = Menu();

    switch (scelta)
      {
      case 1:
	if (!CaricaFasceOrarie(/* a cura dello studente */))
	  printf("Errore durante il caricamento di %s\n", NOME_FILE);
	break;

      case 2:
	stanze = CreaStanze(/* a cura dello studente */);
	break;

      case 3:
	printf("Inserisci l'orario (hh:mm): ");
	scanf("%s", orario);
	id_stanze = RiscaldamentoAttivo(/* a cura dello studente */);
	for (int i=0; i<n; i++)
	  printf("%d, ", id_stanze[i]);
	printf("\n");
	free(id_stanze);
	break;
      }
    
  } while (scelta != 0);

  // Disallocare le lista
  DisallocaListaFasceOrarie(fasce_orarie);
  DisallocaListaStanze(stanze);

  return 0;
}
