/*  ESERCIZIO 2  - Fondamenti di Informatica - Appello del 11/09/2024

Un sistema di monitoraggio del traffico dispone di un certo numero di sensori in grado di
 registrare il passaggio di autoveicoli memorizzando in particolare targa dell'auto ed orario di transito.
 Si assuma che il numero di sensori presenti sia pari a N=10.

 Tali informazioni vengono fornite sotto forma di file di testo ("transiti.txt") in cui in ogni riga
 sono memorizzare le seguenti informazioni:
 - id sensore (intero da 1 a N)
 - targa auto (stringa di 7 caratteri)
 - ora transito
 - minuto transito

 Sviluppare una applicazione ANSI C in cui vengono implementate le seguenti funzioni:

  1. CaricaTransiti: carica le informazioni presenti nel file in un
  vettore di liste di transiti.

  2. ContaVetture: dato un intervallo orario (sotto forma di orario di inizio e fine)
  conta il numero di vetture transitate per ogni sensore in quell'intervallo, restituendo tali informazioni
  in un apposito vettore di interi

  3. EstraiDatiVettura: data una targa di una vettura, estrarre in un'unica lista di transiti tutti i suoi
  passaggi presenti nel vettore di liste

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funzione.
*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NSENSORI 10    // numero di sensori

typedef struct Transito {
  char  targa[8];
  int ora;
  int minuto;
} TTransito;

typedef struct NodoTransito{
    TTransito           info;
  struct NodoTransito *next;
} TNodoTransito;

typedef TNodoTransito* TListaTransiti;


/* InserisciInTesta: inserisce un elemento in testa alla lista passata */
int InserisciInTesta(TListaTransiti* plis, TTransito elem) {
    TListaTransiti paux;

	paux = (TListaTransiti)malloc(sizeof(TNodoTransito));

	if (paux == NULL)
		return 0;

	paux->info = elem;
	paux->next = *plis;

	*plis = paux;

	return 1;
}

/* 1) CaricaTransiti: 
 *	la funzione deve caricare le informazioni presenti nel file in un apposito vettore di liste di transiti,
 *  in cui ciascun elemento del vettore contiene i dati di un sensore.
 *  Parametri: nome del file, vettore di liste di transiti, dim vettore
 *  Restituisce: il numero di elementi caricati nella struttura dati (o -1 se vi è stato un errore)
 */
int CaricaTransiti(char* nomefile, TListaTransiti v[], int dim){
 // DA IMPLEMENTARE
}


/*
  2. ContaVetture: 
  dato un intervallo orario (sotto forma di orario di inizio e fine)
  conta il numero di vetture transitate per ogni sensore in quell'intervallo, restituendo tali informazioni
  in un apposito vettore di interi
  (in cui ciascun elemento contiene il numero di auto transitate per quel sensore)
  Parametri di ingresso: vettore di liste di transiti e sua dimensione, ora inizio, minuto inizio, ora fine, minuto fine
  Restituisce: vettore di numero di transiti per sensore
*/


int* ContaVetture(TListaTransiti vett[], int dim, int orainizio, int minutoinizio, int orafine, int minutofine) {
	// DA IMPLEMENTARE
}


/*
  3. EstraiDatiVettura:
  data una targa di una vettura, estrarre in un'unica lista di transiti tutti i 
  passaggi di quella vettura presenti nel vettore di liste
  
  Parametri di ingresso: vettore di liste di transiti e sua dimensione, targa vettura
  Valore restituito: 
    lista di transiti della vettura inserita
*/
TListaTransiti EstraiDatiVettura(TListaTransiti vett[], int dim, char* targa) {
	// DA IMPLEMENTARE
}


/*
  VisualizzaLista: visualizza le informazioni dei transiti
  contenuti nella lista passata come parametro
*/
void VisualizzaLista(TListaTransiti lis) {
  while (lis != NULL){
      printf("%s %d %d\n",
	     lis->info.targa,
	     lis->info.ora,
	     lis->info.minuto);
      lis = lis->next;
    }
}


int Menu() {
  int scelta;
  
  printf("\n*** M E N U ***\n"
	 "1 - Carica dati transiti da file\n"
	 "2 - Conta vetture in intervallo orario\n"
	 "3 - Estrai transiti vettura \n"
	 "0 - Uscita\n\n"
	 "Scelta:   ");
  scanf("%d", &scelta);

  return scelta;
}

void DisallocaLista(TListaTransiti lista) {
  TListaTransiti paux;

  while (lista != NULL) {
      paux = lista;
      lista = lista->next;
      free(paux);
    }
}

/******** MAIN **********/
int main(void) {
  TListaTransiti vettore[NSENSORI];

  int         scelta,n=0;
  char        nomefile[32];
  int* nvett;
  char targa[8];
  TListaTransiti listavettura = NULL;

  for (int i = 0; i < NSENSORI; i++)
	  vettore[i] = NULL;

  do {
    scelta = Menu();

    switch (scelta) {
      case 1:
		  printf("Immetti il nome del file di testo: ");
		  scanf("%s", nomefile);
		  // invocare la funzione CaricaTransiti e visualizzare il vettore di liste ottenuto

		  }
		break;
	  case 2:
		  // inserire da input un intervallo orario (sotto forma di orario di inizio e fine)
		  // invocare la funzione ContaVetture
		  // visualizzare i dati restituti dalla funzione ContaVetture


		break;
	  case 3:
		  printf("Inserisci una targa:   ");
		  scanf("%s", targa);
		  // invocare la funzione EstraiDatiVettura
		  // e successivamente visualizzare i dati della lista restituita


		  break;
      }

  } while (scelta != 0);

  // Disallocare le liste


  return 0;
}