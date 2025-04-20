
/*

Un’agenzia di un servizio corriere espresso vuole realizzare un programma per la gestione delle spedizioni. In particolare, 
le richieste giornaliere di ritiro di pacchi da spedire sono inizialmente memorizzate in un file di testo (un esempio di file è fornito come allegato all'attivita').
Nel file ogni riga riporta, separati da spazio le seguenti informazioni:
- l'identificativo del mittente (stringa senza spazi)
- l'orario in cui è stata effettuata la richiesta (stringa in formato HH:MM)
- la sigla della provincia di destinazione (stringa) 


Implementare un programma in ANSI C che contiene le seguenti funzioni:
1) lettura e caricamento dei dati contenuti nel file in una lista ordinata in base all'orario della richiesta. La funzione deve inoltre restituire il numero di elementi letti e caricati nella lista

2) funzione che restituisce il numero di spedizioni richieste nelle seguenti 3 fasce orarie: mattina (fino alle 11:59), pomeriggio (dalle 12:00 alle 17:59), sera (dopo le 18:00). 

3) funzione che, fornita in ingresso una provincia, restituisca la lista delle spedizioni per quella provincia 

Si implementi inoltre un main che richiami in maniera opportuna le funzioni sopra elencate, seguendo lo schema fornito nel codice.

La descrizione dettagliata di ogni funzione è riportata come commento immediatamente prima della definizione della funzione nello scheletro di programma fornito
*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  // Includere gli header di libreria necessari
#include <stdlib.h>
#include <string.h>

// Dichiarazione Struttura dati

typedef struct spedizione {
    char  mittente[32];
    char  orario[6];
    char  provincia[3];
} TSpedizione;

typedef struct nodo {
    TSpedizione	info;
    struct nodo *next;
} TNodo;

typedef TNodo *TLista;


/* InserisciTestaLista
    inserisce un elemento in testa alla lista passata come primo parametro. 
    Restituisce 1 se l'operazione va a buon fine, 0 altrimenti */
int InserisciTestaLista(TLista* lis, TSpedizione elem) {
    TLista paux;

    if ((paux = (TLista)malloc(sizeof(TNodo))) == NULL)
        return 0;

    paux->info = elem;                      
    paux->next = *lis;                      
    *lis = paux;                            

    return 1;
}

/* InserisciInListaOrdinata
    inserisce un elemento in lista in maniera ordinata rispetto al campo orario */
void InserisciInListaOrdinata(TLista* lis, TSpedizione elem) {

    if (*lis == NULL || strcmp((*lis)->info.orario, elem.orario) > 0)
        InserisciTestaLista(lis, elem);
    else
        InserisciInListaOrdinata(&((*lis)->next), elem);
}


/*
   1. CaricaDaFile: 
   carica da file la richieste in una lista di spedizioni (ordinata in base all'orario).
   Restituisce il numero di elementi letti da file e caricati nella lista
*/
int CaricaDaFile(TLista *plis, char *nomefile) {
    FILE* fp;
    TSpedizione sped;
    int cont = 0;

    *plis = NULL;

    fp = fopen(nomefile, "r");
    if (fp == NULL)
        return 0;

    while (!feof(fp)) {
        if (fscanf(fp, "%s%s%s", sped.mittente, sped.orario, sped.provincia) == 3) {
            InserisciInListaOrdinata(plis, sped);
            cont++;
        }
    }

    fclose(fp);

    return cont;
}


/*
    2. NumeroSpedizioni
    funzione che restituisce il numero di spedizioni richieste nelle fasce orarie: mattina (fino alle 11:59), pomeriggio (dalle 12:00 alle 17:59), sera (dopo le 18:00). Tali risultati vengono restituiti in un opportuno vettore di tre elementi:0 mattina, 1 pomeriggio, 2 sera.
*/
void NumeroSpedizioni(TLista lis, int* vett) {
    int i;

    for (i = 0; i < 3; i++)
        vett[i] = 0;
    while (lis != NULL) {
        if (strcmp(lis->info.orario, "12:00") < 0)
            vett[0]++;
        else if ((strcmp(lis->info.orario, "12:00") > 0) && (strcmp(lis->info.orario, "18:00") < 0))
            vett[1]++;
        else
            vett[2]++;
        lis = lis->next;
    }
}
/*
    SpedizioniProvincia:
    funzione che prevede come parametri di ingresso: la lista delle spedizioni, ed una provincia.
    Essa deve restituire la lista delle spedizioni per la provincia data
*/
TLista SpedizioniProvincia(TLista lis, char* prov) {
    TLista paux = NULL;

    while (lis != NULL) {
        if (strcmp(lis->info.provincia, prov)==0) {
            InserisciTestaLista(&paux, lis->info);
        }
        lis = lis->next;
    }

    return paux;
}

/*******menu' di scelta *********/
int Menu() {
  int scelta;
  
  printf("*** M E N U ***\n"
	 "1 - Carica dati da file\n"
	 "2 - Numero spedizioni per fasce orarie\n"
	 "3 - Spedizioni per provincia\n"
	 "0 - Uscita\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

void VisualizzaLista(TLista lis) {

    while (lis != NULL) {
        printf("Mittente: %s\n", lis->info.mittente);
        printf("Orario richiesta: %s\n", lis->info.orario);
        printf("Provincia destinazione: %s\n\n", lis->info.provincia);
        lis = lis->next;
    }
}


void DisallocaLista(TLista lista) {
  TLista p;

  while (lista != NULL)     {
      p = lista;
      lista = lista->next;
      free(p);
    }
}

/****** main *********/
int main(void) {
  TLista listaspedizioni=NULL;
  TLista listaprovincia = NULL;
  int scelta;

  char nomefile[32];
  int n,i;
  int v[3];
  char provincia[3];


  
  do {
    scelta = Menu();

    switch (scelta) {
      case 1:
          // Acquisire il nome del file
          // Invocare la funzione CaricaDaFile e visualizzare il numero di elementi caricati o un messaggio in caso di errore
          // Visualizzare i dati caricati nella lista
          printf("Inserisci il nome del file:  ");
          scanf("%s", nomefile);
          n = CaricaDaFile(&listaspedizioni, nomefile);
          printf("Sono stati caricati %d spedizioni\n", n);
          VisualizzaLista(listaspedizioni);
	    break;

      case 2:
          // Invocare la funzione NumeroSpedizioni
          // Visualizzare i dati restituiti dalla funzione 
          NumeroSpedizioni(listaspedizioni, v);
          for (i = 0; i < 3; i++)
              printf("Numero spedizioni fascia oraria %d: %d\n", i, v[i]);
	    break;

      case 3:
          // Acquisire la provincia
	      // Invocare la funzione SpedizioniProvincia
          // Visualizzare i dati della lista restituita dalla funzione
          printf("Inserisci la sigla di una provincia:  ");
          scanf("%s", provincia);
          listaprovincia=SpedizioniProvincia(listaspedizioni, provincia);
          VisualizzaLista(listaprovincia);
	    break;
     }
    
  } while (scelta != 0);

  DisallocaLista(listaspedizioni); // disallocare la lista
  
  return 0;
}