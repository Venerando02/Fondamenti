/*
  Sviluppo di applicazione in ANSI C per gestire 
  un servizio i brani musicali di una playlist.

  In un file di testo ("brani.txt"), è memorizzato 
  l'elenco dei brani di una playlist.
  Così come visibile nel file, per ciascun brano
  musicale sono memorizzate le seguenti informazioni:
  - codice brano
  - titolo brano
  - cantante
  - anno pubblicazione

  Si assuma che il titolo del brano ed il nome del cantante non contengano spazi.

  Implementare le seguenti funzioni:

  1. CaricaBrani: carica i brani presenti nel file in una 
  lista di brani ordinata in base all'anno di pubblicazione.

  2. EliminaBrano: dato il codice di un brano, rimuove tale brano (se
  esiste) dalla lista.

  3. EstraiBraniCantante: dato il nome di un cantante,
  seleziona dalla lista i brani di quel cantante e li 
  inserisce in un apposito vettore di brani.

  4. MaxBraniAnno: restituisce il numero massimo di brani pubblicati in 
  un anno compreso tra l'anno corrente (2024) e gli N anni precedenti

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funzione.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Brano {
  char  codice[8];
  char  titolo[64];
  char  cantante[64];
  int anno;
} TBrano;

typedef struct NodoBrano{
  TBrano           info;
  struct NodoBrano *next;
} TNodoBrano;

typedef TNodoBrano* TListaBrani;


int InserisciInTesta(TListaBrani* plis, TBrano elem) {
	TListaBrani paux;

	paux = (TListaBrani)malloc(sizeof(TNodoBrano));

	if (paux == NULL)
		return 0;

	paux->info = elem;
	paux->next = *plis;

	*plis = paux;

	return 1;
}
/* AggiungiBranoInOrdine: inserisce un brano nella lista 
   in ordine rispetto all'anno di pubblicazione
 */
int AggiungiBranoInOrdine(TListaBrani* plis, TBrano elem) {

  if ((*plis == NULL) || (*plis)->info.anno > elem.anno)
	  InserisciInTesta(plis, elem);
  else AggiungiBranoInOrdine(&(*plis)->next, elem);

}

/*
  1.  CaricaBrani: carica i brani presenti nel file in una 
  lista di brani ordinata in base all'anno di pubblicazione.
  Parametri di ingresso: nome del file
  Parametri di uscita: lista dei brani musicali
  Valore restituito: numero di elementi caricati
*/
int CaricaBrani(char *nomefile, TListaBrani* lista) {
  
  TBrano brano;
  FILE* fp;
  int cont = 0;
  
  fp = fopen(nomefile, "r");
  if (fp == NULL) {
	  printf("Errore apertura file\n");
	  return 0;
  }
  
  while (!feof(fp)) {
	  if (fscanf(fp, "%s%s%s%d", 
		  brano.codice, brano.titolo, brano.cantante, &brano.anno) == 4){
			  AggiungiBranoInOrdine(lista, brano);
			  cont++;
		}
  }
  fclose(fp);
  return cont;
}

/*
  2. EliminaBrano: dato il codice di un brano, rimuove tale brano (se
  esiste) dalla lista.
  Parametri di ingresso: lista dei brani musicali, codice del brano da cancellare
*/
void EliminaBrano(TListaBrani* lis, char* codice) {
  TListaBrani paux;

  if (*lis != NULL) {
      if (strcmp((*lis)->info.codice, codice) == 0) {  
		paux = *lis;
		*lis = (*lis)->next;
		free(paux);
	  }
	  else                                          
		  EliminaBrano(&(*lis)->next, codice);
    }
}  


/*
  3. EstraiBraniCantante: dato il nome di un cantante,
  seleziona dalla lista i brani di quel cantante e li 
  inserisce in un apposito vettore di brani
  Parametri di ingresso:
    lis - lista dei brani musicali,
    cantante - nome del cantante
  Parametri di uscita:
    dim - numero di brani del cantante
  Valore restituito: 
    TBrano* - vettore dei brani selezionati
*/
TBrano* EstraiBraniCantante(TListaBrani lis,char* cantante, int* dim) {
  int         conta = 0, i;
  TBrano*     vett;
  TListaBrani paux = lis;

  // conteggio del numero di brani che soddisfano i criteri
  while (paux != NULL) {
    if (strcmp(paux->info.cantante, cantante) == 0)
      conta++;
    paux = paux->next;
  }

  if ((vett = (TBrano*)malloc(conta * sizeof(TBrano))) == NULL) {
    printf("Errore allocazione memoria");
    return(NULL);
  }

  paux = lis;
  i = 0;
  while (paux != NULL) {
    if ((strcmp(paux->info.cantante, cantante) == 0))
      vett[i++] = paux->info;
    paux = paux->next;
  }

  *dim = conta;
  return vett;
}

/*
4. MaxBraniAnno: restituisce il numero massimo di brani pubblicati in
un anno compreso tra l'anno corrente (2024) e gli N anni precedenti
  Parametri di ingresso:
    lista - lista dei brani musicali,
    N - numero di anni precedenti al 2024 da considerare
  Parametri di uscita:
    anno - anno in cui si è registrato il numero massimo di brani
  Valore restituito:
    int - numero massimo di brani
*/
int MaxBraniAnno(TListaBrani lista, int N, int* anno) {
	//il vettore conterra solo il numero di brani degli ultimi N anni 
    //considerando come anno attuale 2024
	// indice 0 --> 2024 , indice 1 --> 2023, indice i --> 2024-i
	int a, i;

	int* vettore;
	vettore = (int*)malloc(sizeof(int) * N);
	if (vettore == NULL) {
		printf("Errore allocazione memoria");
		exit(1);
	}

	//inizializza vettore
	for (int i = 0; i < N; i++) 
		vettore[i] = 0;

	while (lista != NULL) {
		a=lista->info.anno;
		if (a> 2024-N)
			vettore[2024-a]++;
		lista = lista->next;
	}
	// adesso bisogna semplicemente calcolare il massimo del vettore
	int max = 0;
	int posmax = 0;
	for (i = 0; i < N; i++) {
		if (vettore[i] > max) {
			max = vettore[i];
			posmax = i;
		}
	}
	*anno = 2024 - i;
	return max;
}

/*
  VisualizzaLista: visualizza le informazioni dei brani
  nella lista passata come parametro
*/
void VisualizzaLista(TListaBrani lis) {
  while (lis != NULL){
      printf("%s %s %s %d\n",
	     lis->info.codice,
	     lis->info.titolo,
	     lis->info.cantante,
	     lis->info.anno);
      lis = lis->next;
    }
}

/*
  VisualizzaVettoreBrani: visualizza le informazioni dei brani
  contenute nel vettore passato come parametro
*/
void VisualizzaVettoreBrani(TBrano v[], int dim) {
  int i;
  for (i = 0; i < dim; i++) 
    printf("%s %s %s %d\n",
	   v[i].codice,
	   v[i].titolo,
	   v[i].cantante,
	   v[i].anno);
}

int Menu() {
  int scelta;
  
  printf("\n*** M E N U ***\n"
	 "1 - Carica brani musicali\n"
	 "2 - Elimina brano\n"
	 "3 - Estrai brani cantante \n"
	 "4 - Massimo numero brani in un anno \n"
	 "0 - Uscita\n\n"
	 "Scelta:   ");
  scanf("%d", &scelta);

  return scelta;
}

void DisallocaLista(TListaBrani lista) {
  TListaBrani paux;

  while (lista != NULL) {
      paux = lista;
      lista = lista->next;
      free(paux);
    }
}

/******** MAIN **********/
int main(void) {
  TListaBrani listabrani = NULL;

  int         scelta,n;
  char        nomefile[32];
  char        codice[8];
  char        nomecantante[64];
  int         dim=0;
  TBrano*     vett;
  int massimo, annomax;

  do {
    scelta = Menu();

    switch (scelta) {
      case 1:
		  printf("Immetti il nome del file di testo: ");
		  scanf("%s", nomefile);
		  // invocare la funzione CaricaBrani e visualizzare la lista ottenuta
		  n = CaricaBrani(nomefile, &listabrani);
		  printf("Caricati %d brani\n", n);
		  printf("\nElenco brani caricati\n");
		  VisualizzaLista(listabrani);
		break;
	  case 2:
		  // inserire un codice ed invocare la funzione EliminaBrano per rimuovere quel brano dalla lista
		  printf("Inserisci il codice del brano da cancellare: ");
		  scanf("%s", codice);
		  EliminaBrano(&listabrani, codice);
		break;
	  case 3:
		  // inserire un nome di cantante, invocare la funzione EstraiBraniCantante
		  // e successivamente visualizzare il contenuto del vettore ottenuto
		  printf("Inserisci il nome del cantante: ");
		  scanf("%s", nomecantante);
		  vett = EstraiBraniCantante(listabrani, nomecantante, &dim);
		  VisualizzaVettoreBrani(vett, dim);
		  break;
	  case 4:
		  printf("Inserisci il numero di anni precedenti l'anno corrente: ");
		  scanf("%d", &n);
		  // invocare la funzione MaxBraniAnno e visualizzare i risultati ottenuti
		  massimo=MaxBraniAnno(listabrani, n, &annomax);
		  printf("Numero massimo di brani: %d\n Pubblicati nell'anno: %d", massimo, annomax);
		  break;
      }

  } while (scelta != 0);

  // Didsallocare le lista
  DisallocaLista(listabrani);

  return 0;
}