/*Un uffico vuole realizzare un sistema per il monitoraggio delle operazioni effettuate.
Le operazioni che possono essere effettuate sono caratterizzate dalle seguenti informazioni
-	Tipo di operazione (un intero compreso tra 0 e 3)
-	Un codice del cliente che effettua l’operazione (una stringa di 7 caratteri utili)
-	Un tempo richiesto per l’operazione espresso in secondi
L’archivio è organizzato in un  file testo in cui in ogni riga sono inserite separate da spazio bianco le informazioni relative ad una operazione.
Lo studente implementi un programma ANSI C con un opportuno main in cui sia previsto un menu di scelta delle operazioni richieste. Tutti i valori necessari al funzionamento devono essere passati utilizzando parametri, non è permesso l’uso di variabili globali.
Le funzioni 2 e 3 e 4 devono essere implementate utilizzando le informazioni presenti in memoria centrale
1.	Funzione Carica che consente di copiare i dati presenti nel file in un vettore di liste ordinate rispetto al codice del cliente. 
Ogni lista contiene un tipo specifico di operazione.
2.	Funzione che stampa il contenuto della struttura presente in memoria centrale
3. Funzione che restituisce il numero totale di minuti di operazioni relative ad un cliente il cui codice è passato come parametro
4.  Funzione che restituisce un vettore che contiene le liste delle operazioni effettuate da ciascun cliente. In ogni elemento del vettore sarà quindi presente la lista delle operazioni effettuate da un cliente.
*/

//nome e cognome e numero di matricola
// Venerando Pio Musumeci 1000015141
//inserire qua le istruzioni di precompilazione necessarie

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//definizione struttura dati
typedef struct op {
    int tipo, durata;
    char codice[8];
} operazione;
typedef struct n {
    operazione info;
    struct n* next;
}TipoNodo;
typedef TipoNodo* TipoLista;

/***** Funzioni primitive per uso lista ******/

/* InserisciTestaLista: Inserisce l'elemento elem in testa alla lista lis. */
void InserisciTestaLista(TipoLista* lis, operazione elem) {
    TipoLista paux;

    if ((paux = (TipoLista)malloc(sizeof(TipoNodo))) == NULL) {	/* 1 */
        printf("Errore: impossibile allocare memoria");
        exit(1);
    }
    paux->info = elem;                      /* 2 */
    paux->next = *lis;                      /* 3 */
    *lis = paux;                            /* 4 */
}  /* InserisciTestaLista */

/* InserisciInListaOrdinata:
Inserisce l'elemento elem nella lista lis ordinata per elementi crescenti, mantenendo l'ordinamento.*/
void InserisciInListaOrdinata(TipoLista* lis, operazione elem) {
    TipoLista paux;

    if (*lis == NULL) {
        if ((paux = (TipoLista)malloc(sizeof(TipoNodo))) == NULL) {	/* 1 */
            printf("Errore: impossibile allocare memoria");
            exit(1);
        }
        paux->info = elem;
        paux->next = NULL;
        *lis = paux;
    }
    else if (strcmp((*lis)->info.codice, elem.codice) < 0) {
        /* l'elemento in testa e` maggiore o uguale a elem */
        if ((paux = (TipoLista)malloc(sizeof(TipoNodo))) == NULL) {
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
    printf("\n 0) esci dal programma\n\n");
    printf(">>> ");
    scanf("%d", &scelta);
    return scelta;
}

//definizione dei prototipi delle funzioni quesito1, quesito2,quesito3 e quesito4
void Carica(TipoLista* vettoreListe, char* nomefile);
void Stampa(TipoLista* vettoreListe);

int quesito3(TipoLista* vettoreListe, char* cliente);

TipoLista* quesito4(TipoLista* vettoreListe, int* clienti);

//main
int main(void) {
    int scelta;
    TipoLista archivio[4];
    TipoLista* vout = NULL;
    char Cliente[8];
    int n;
    for (int i = 0; i < 4; i++) 
    {
        archivio[i] = NULL;
    }
    char NomeFile[64];
    int minuti;
    //aggiungere definizione di eventuali altre variabili necessarie ed inizializzazioni

    do {
        scelta = menu();
        switch (scelta) {
        case 1: { //inserire qua le istruzioni per l'esecuzione della funzione del quesito 1 e la stampa dei risultati
            printf("Inserisci il nome del file: ");
            scanf("%s", NomeFile);
            Carica(archivio, NomeFile);
            Stampa(archivio);
            break;
        }
        case 2: {
            //inserire qua le istruzioni per l'esecuzione della funzione del quesito 2 e la stampa dei risultati
            Stampa(archivio);
            break;
        }
        case 3: {//inserire qua le istruzioni per l'esecuzione della funzione del quesito 3 e la stampa dei risultati
            printf("Inserisci il codice del cliente: ");
            scanf("%s", Cliente);
            minuti = quesito3(archivio, Cliente);
            printf("Per il cliente %s sono stati contati in totale %d minuti.\n", Cliente, minuti);
            break;
        }
        case 4: 
        {//inserire qua le istruzioni per l'esecuzione della funzione del quesito 4 e la stampa dei risultati
            vout = quesito4(archivio, &n);
            for (int i = 0; i < n; i++) 
            {
                printf("CLIENTE %d:\n", i);
                while (vout[i] != NULL) 
                {
                    printf("%s %d %d\n", vout[i]->info.codice, vout[i]->info.durata, vout[i]->info.tipo);
                    vout[i] = vout[i]->next;
                }
                printf("\n");
            }
        }
        }
    } while (scelta != 0);
}


//scrivere di seguito le implementazioni delle funzioni relative ai quesito1, quesito2, quesito3 e quesito4

void Carica(TipoLista* vettoreListe, char* nomefile)
{
    FILE* fp = fopen(nomefile, "r");
    if (fp == NULL)
        return;
    operazione Op;
    while (fscanf(fp, "%d%s%d", &Op.tipo, Op.codice, &Op.durata) == 3) 
    {
        InserisciInListaOrdinata(&vettoreListe[Op.tipo], Op);
    }
}

void Stampa(TipoLista* vettoreListe) 
{
    TipoLista aux;
    for (int i = 0; i < 4; i++) 
    {
        printf("OPERAZIONE %d:\nELENCO:\n", i);
        aux = vettoreListe[i];
        while (aux != NULL) 
        {
            printf("%d %d %s\n", aux->info.tipo, aux->info.durata, aux->info.codice);
            aux = aux->next;
        }
        printf("\n");
    }
}


int quesito3(TipoLista* vettoreListe, char* cliente) 
{
    TipoLista aux;
    int accumulatore = 0;
    for (int i = 0; i < 4; i++) 
    {
        aux = vettoreListe[i];
        while (aux != NULL) 
        {
            if (strcmp(aux->info.codice, cliente) == 0)
            {
                accumulatore += aux->info.durata;
            }
            aux = aux->next;
        }
    }
    return accumulatore;
}

TipoLista* quesito4(TipoLista* vettoreListe, int * clienti) {
    TipoLista* vout = NULL; // Vettore dinamico per clienti
    int numClienti = 0;     // Numero di clienti univoci
    TipoLista aux;
    (*clienti) = 0;
    // Itera su tutte le liste delle operazioni
    for (int i = 0; i < 4; i++) {
        aux = vettoreListe[i];
        while (aux != NULL) {
            // Cerca il cliente nel vettore
            int trovato = -1;
            for (int j = 0; j < numClienti; j++) {
                if (strcmp(vout[j]->info.codice, aux->info.codice) == 0) {
                    trovato = j;
                    break;
                }
            }

            if (trovato == -1) { // Cliente nuovo
                // Alloca spazio per un nuovo elemento nel vettore
                TipoLista* nuovoVout = (TipoLista*)malloc((numClienti + 1) * sizeof(TipoLista));
                if (nuovoVout == NULL) {
                    printf("Errore: Memoria insufficiente\n");
                    exit(1);
                }

                // Copia i clienti esistenti nel nuovo vettore
                for (int k = 0; k < numClienti; k++) {
                    nuovoVout[k] = vout[k];
                }
                nuovoVout[numClienti] = NULL; // Inizializza la nuova lista per il nuovo cliente

                // Libera la memoria del vecchio vettore e aggiorna il puntatore
                free(vout);
                vout = nuovoVout;

                // Inserisci l'operazione per il nuovo cliente
                InserisciTestaLista(&vout[numClienti], aux->info);

                // Incrementa il numero di clienti
                numClienti++;
            }
            else { // Cliente già esistente
                // Aggiungi l'operazione alla lista del cliente
                InserisciTestaLista(&vout[trovato], aux->info);
            }

            aux = aux->next;
        }
    }
    (*clienti) = numClienti;
    return vout;
}
