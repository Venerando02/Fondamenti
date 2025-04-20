/*Un uffico vuole realizzare un sistema per il monitoraggio delle operazioni effettuate.
Le operazioni che possono essere effettuate sono caratterizzate dalle seguenti informazioni
-	Tipo di operazione (un intero compreso tra 0 e 3)
-	Un codice del cliente che effettua l’operazione (una stringa di 7 caratteri utili)
-	Un tempo richiesto per l’operazione espresso in secondi
L’archivio è organizzato in un  file testo in cui in ogni riga sono inserite separate da spazio bianco le informazioni relative ad una operazione.
Lo studente implementi un programma ANSI C con un opportuno main in cui sia previsto un menu di scelta delle operazioni richieste. Tutti i valori necessari al funzionamento devono essere passati utilizzando parametri, non è permesso l’uso di variabili globali.
Le funzioni 2 e 3 e 4 devono essere implementate utilizzando le informazioni presenti in memoria centrale
1.	Funzione Carica che consente di copiare i dati presenti nel file in un vettore di liste ordinate rispetto al codice del cliente. Ogni lista contiene un tipo specifico di operazione.
2.	Funzione che stampa il contenuto della struttura presente in memoria centrale
3. Funzione che restituisce il numero totale di minuti di operazioni relative ad un cliente il cui codice è passato come parametro
4.  Funzione che restituisce un vettore che contiene le liste delle operazioni effettuate da ciascun cliente. In ogni elemento del vettore sarà quindi presente la lista delle operazioni effettuate da un cliente.
*/

//nome e cognome e numero di matricola

//inserire qua le istruzioni di precompilazione necessarie


//definizione struttura dati
typedef struct op {
    int tipo, durata;
    char codice[8];
} operazione;
typedef struct n {
    operazione info;
    struct n* next;
}TipoNodo;
typedef TipoNodo * TipoLista;          

/***** Funzioni primitive per uso lista ******/

/* InserisciTestaLista: Inserisce l'elemento elem in testa alla lista lis. */
void InserisciTestaLista(TipoLista *lis, operazione elem) {
  TipoLista paux;

  if ((paux = (TipoLista)malloc(sizeof(TipoNodoLista))) == NULL) {	/* 1 */
	  printf("Errore: impossibile allocare memoria");
	  exit(1);
  }
  paux->info = elem;                      /* 2 */
  paux->next = *lis;                      /* 3 */
  *lis = paux;                            /* 4 */
}  /* InserisciTestaLista */

/* InserisciInListaOrdinata: 
Inserisce l'elemento elem nella lista lis ordinata per elementi crescenti, mantenendo l'ordinamento.*/
void InserisciInListaOrdinata(TipoLista *lis, operazione elem) {
  TipoLista paux;

  if (*lis == NULL) {
	if ((paux = (TipoLista)malloc(sizeof(TipoNodoLista))) == NULL) {	/* 1 */
		  printf("Errore: impossibile allocare memoria");
		  exit(1);
	}
	paux->info = elem;
    paux->next = NULL;
    *lis = paux;
  }
  else if (strcmp((*lis)->info.codice, elem.codice)<0) {
                          /* l'elemento in testa e` maggiore o uguale a elem */
	if ((paux = (TipoLista)malloc(sizeof(TipoNodoLista))) == NULL) {	
		  printf("Errore: impossibile allocare memoria");
		  exit(1);
	}    
	paux->info = elem;
    paux->next = *lis;
    *lis = paux;
  }
  else                              /* l'elemento in testa e` minore di elem */
    InserisciInListaOrdinata(&(*lis)->next, elem);
}  /* InserisciInListaOrdinata */


int menu(void) {
    int scelta;
    printf("\n 1) esegui quesito 1");
    printf("\n 2) esegui quesito 2");
    printf("\n 3) esegui quesito 3");
    printf("\n 4) esegui quesito 4");
    printf("\n 0) esci dal programma");
    scanf("%d", &scelta);
    return scelta;
}

//definizione dei prototipi delle funzioni quesito1, quesito2,quesito3 e quesito4
void Carica(TipoLista *vettoreListe, char *nomefile);
void Stampa(TipoLista *vettoreListe);

int quesito3(TipoLista *vettoreListe, char* cliente);

TipoLista* quesito4(TipoLista * vettoreListe);

//main
int main(void) {
    lista archivio[4];
    //aggiungere definizione di eventuali altre variabili necessarie ed inizializzazioni
    
    do {
        scelta = menu();
        switch (scelta) {
        case 1: { //inserire qua le istruzioni per l'esecuzione della funzione del quesito 1 e la stampa dei risultati
            break;
        }
        case 2: { //inserire qua le istruzioni per l'esecuzione della funzione del quesito 2 e la stampa dei risultati
            break;
        }
        case 3: {//inserire qua le istruzioni per l'esecuzione della funzione del quesito 3 e la stampa dei risultati
            break;
        }
        case 4: {//inserire qua le istruzioni per l'esecuzione della funzione del quesito 4 e la stampa dei risultati

        }
        }
    } while (scelta != 0);
}


//scrivere di seguito le implementazioni delle funzioni relative ai quesito1, quesito2, quesito3 e quesito4

