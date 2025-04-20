/******************************************************************************

 Scrivere un programma ANSI C per la gestione di una coda di ordini.
    Ogni ordine è caratterizzato da un codice (intero positivo), da una lista di
    prodotti, la loro quantità e da un importo totale.

    Il programma deve consentire la lettura degli ordini da file e la loro
    memorizzazione in una coda.
    Ogni elemento della coda contiene quindi un ordine, costituito dalla
    lista dei prodotti, il numero totale di elementi nell'ordine e dal numero di ordine.

    Il file di input contiene un numero variabile di ordini, e in particolare per ogni riga
     un prodotto, la sua quantità e l'ordine di appartenenza identificato tramite numero.
     Es.
      // PRODOTTO QUANTITA' ORDINE
      PRODOTTO_1 10 #20
      PRODOTTO_2 5 #20
      ...
      PRODOTTO_1 1 #21
      PRODOTTO_10 1 #21


    Il programma svolge le seguenti operazioni:
    1. caricamento dei dati dal file in una coda in memoria centrale,
    2. reperimento di tutti gli ordini che contengono un certo prodotto. Il prodotto è letto da console.
       Gli ordini corrispondenti vengono inseriti in una lista.
    3. Riepilogo numero di prodotti totali per ordine

 I dettagli delle funzioni e dei parametri sono specificati nella descrizione puntuale
    delle funzioni.

 Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare
    quello esistente tranne quando espressamente richiesto.
 L'esercizio si considera corretto se il programma compila correttamente ed esegue
    senza errori run-time dando i risultati attesi.

 I dettagli delle funzioni e dei parametri sono specificati nella descrizione puntuale
 delle funzioni.

 Si raccomanda di scrivere il codice delle funzioni in modo modulare (scomporre
 il problema in sottoproblemi più semplici).

*******************************************************************************/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define STRLEN 64

typedef struct prodotto_struct {
    char nome[STRLEN];
    int quantita;
    struct prodotto_struct *successivo;
} NodoProdotto;

typedef NodoProdotto *ListaProdotti;

typedef struct {
    char id_ordine[STRLEN];
    int numero_prodotti;
    ListaProdotti lista_elementi;

} Ordine;

typedef struct ordine_struct {
    Ordine ordine;
    struct ordine_struct *successivo;
} NodoOrdine;

typedef struct {
    NodoOrdine *primo_elemento;
    NodoOrdine *ultimo_elemento;
} CodaOrdini;

typedef NodoOrdine *ListaOrdini;


// Funzione che stampa a video il riepilogo di un ordine
void stampa_ordine(Ordine ordine) {
    printf("Ordine %s - numero prodotti %d:\n", ordine.id_ordine, ordine.numero_prodotti);
    ListaProdotti prodotto = ordine.lista_elementi;
    while (prodotto != NULL) {
        printf("\t %s \t\t - %d\n", prodotto->nome, prodotto->quantita);
        prodotto = prodotto->successivo;
    }
}

void stampa_ordini(ListaOrdini lista_ordini);

/* Funzione che, data una coda di ordini, aggiunge un nuovo ordine alla coda.
 * La funzione restituisce il puntatore al nuovo ordine inserito.
 *
 * Parametri:
 * - coda: puntatore alla coda di ordini
 * - id_ordine: stringa che rappresenta l'identificativo dell'ordine
 * Return:
 * - puntatore al nuovo ordine inserito
 */
NodoOrdine *coda_ordini_aggiungi(CodaOrdini *coda, char *id_ordine) {
    NodoOrdine *nuovo_nodo = (NodoOrdine *) malloc(sizeof(NodoOrdine));
    if (nuovo_nodo == NULL) {
        printf("Errore di allocazione memoria");
        exit(1);
    }

    strcpy(nuovo_nodo->ordine.id_ordine, id_ordine);
    nuovo_nodo->ordine.numero_prodotti = 0;
    nuovo_nodo->ordine.lista_elementi = NULL;

    nuovo_nodo->successivo = NULL;
    if (coda->primo_elemento == NULL) {
        coda->primo_elemento = nuovo_nodo;
        coda->ultimo_elemento = nuovo_nodo;
    } else {
        coda->ultimo_elemento->successivo = nuovo_nodo;
        coda->ultimo_elemento = nuovo_nodo;
    }

    return nuovo_nodo;
}


/* Funzione che, data una lista di prodotti, aggiunge un nuovo prodotto alla lista.
 *
 * Parametri:
 * - lista: puntatore alla lista di prodotti
 * - nome_prodotto: stringa che rappresenta il nome del prodotto
 * - quantita: quantità del prodotto
 */
void lista_prodotti_aggiungi(ListaProdotti *lista, char *nome_prodotto, int quantita) {
    NodoProdotto *nuovo_nodo = malloc(sizeof(NodoProdotto));

    if (nuovo_nodo == NULL) {
        printf("Errore di allocazione memoria");
        exit(1);
    }
    strcpy(nuovo_nodo->nome, nome_prodotto);
    nuovo_nodo->quantita = quantita;
    nuovo_nodo->successivo = *lista;
    *lista = nuovo_nodo;
}

/*
 * Funzione che, data una lista di ordini, aggiunge un nuovo ordine alla lista.
 *
 * Parametri:
 * - lista: puntatore alla lista di ordini
 * - ordine: ordine da aggiungere alla lista
 *
 */
void lista_ordini_aggiungi(ListaOrdini *lista, Ordine ordine) {
    NodoOrdine *nuovo_nodo = malloc(sizeof(NodoOrdine));
    if (nuovo_nodo == NULL) {
        printf("Errore di allocazione memoria");
        exit(1);
    }
    nuovo_nodo->ordine = ordine;
    nuovo_nodo->successivo = *lista;
    *lista = nuovo_nodo;
}

/*
 * Funzione che, data una lista di ordini, cerca un ordine con un certo identificativo.
 * La funzione restituisce il puntatore al nodo contenente l'ordine, se non trovato
 * restituisce NULL.
 *
 * parametri:
 * - lista_ordini: lista di ordini
 * - id_ordine: identificativo dell'ordine da cercare
 * - ppNodoOrdine: puntatore al puntatore del nodo contenente l'ordine
 *
 */
void trova_ordine(ListaOrdini lista_ordini, char *id_ordine, NodoOrdine **ppNodoOrdine) {
    while (lista_ordini != NULL) {
        if (strcmp(lista_ordini->ordine.id_ordine, id_ordine) == 0) {
            *ppNodoOrdine = lista_ordini;
            return;
        }
        lista_ordini = lista_ordini->successivo;
    }
    *ppNodoOrdine = NULL;
}

/*
 * Funzione che, data una lista di prodotti, cerca un prodotto con un certo nome.
 * Se lo trova, restituisce il puntatore al nodo contenente il prodotto, altrimenti
 * restituisce NULL
 *
 * parametri:
 * - lista_prodotti: lista di prodotti
 * - prodotto: nome del prodotto da cercare
 * - ppNodoProdotto: puntatore al puntatore del nodo contenente il prodotto
 */
void trova_prodotto(ListaProdotti lista_prodotti, char prodotto[STRLEN], NodoProdotto **ppNodoProdotto) {
    while (lista_prodotti != NULL) {
        if (strcmp(lista_prodotti->nome, prodotto) == 0) {
            *ppNodoProdotto = lista_prodotti;
            return;
        }
        lista_prodotti = lista_prodotti->successivo;
    }
    *ppNodoProdotto = NULL;
}


/////////////////////////////////////////////////////////////////////////////////////////
//
// Funzioni da implementare a cura dello studente
//
/////////////////////////////////////////////////////////////////////////////////////////

// Funzione che stampa il contenuto della coda degli ordini
void stampa_ordini(ListaOrdini lista_ordini) {
    NodoOrdine *nodo_ordine = lista_ordini;
    while (nodo_ordine != NULL) {
        stampa_ordine(nodo_ordine->ordine);
        nodo_ordine = nodo_ordine->successivo;
    }
}


/*
 * 1. Funzione carica_file
 * Questa funzione carica i dati presenti nel file in una coda passata come
 * parametro, restituendo 0 in caso di fallimento altrimenti 1
 *
 * Il formato del file è il seguente:
  // PRODOTTO QUANTITA' ID_ORDINE
  PRODOTTO_1 10 #20
  PRODOTTO_2 5 #20
  ...
  PRODOTTO_1 1 #21
  PRODOTTO_10 1 #21

 * Per ogni riga del file, trovare l'ordine corrispondente (se presente, in caso contrario
 * crearlo tramite la funzione apposita) e aggiungere la quantità del prodotto nella lista dei
 * prodotti dell'ordine (se presente, in caso contrario aggiungerlo tramite la funzione apposita).
 * Ricordarsi di incrementare il numero di prodotti dell'ordine.
 *
 * NOTA BENE: se la coda esiste, non va sovrascritta. I nuovi ordini vanno aggiunti in coda.

 * Parametri: nome del file, coda di eventi
 * Restituisce: 1 se il caricamento è andato a buon fine,
			    0 in caso di errore durante il caricamento
*/
int carica_file(const char *nomefile, CodaOrdini *pc) {
    char ordinestr[STRLEN];
    char prodottostr[STRLEN];
    int quantita;
    NodoOrdine *pNodoOrdine = NULL;
    NodoProdotto *pNodoProdotto = NULL;

    if (pc == NULL) {
        printf("Errore nella coda\n");
        return 0;
    }

    FILE *fp = fopen(nomefile, "r");

    if (fp == NULL) {
        printf("Errore nell'apertura del file %s. Controllare il nome del file e l'estensione e riprovare\n", nomefile);
        return 0;
    }

    while (!feof(fp)) {
        if (fscanf(fp, "%s%d%s", prodottostr, &quantita, ordinestr) != 3) {
            continue;
        }

        trova_ordine(pc->primo_elemento, ordinestr, &pNodoOrdine);

        if (pNodoOrdine == NULL) {
            pNodoOrdine = coda_ordini_aggiungi(pc, ordinestr);
        }

        trova_prodotto(pNodoOrdine->ordine.lista_elementi,
                       prodottostr,
                       &pNodoProdotto
        );

        if (pNodoProdotto == NULL) {
            lista_prodotti_aggiungi(&pNodoOrdine->ordine.lista_elementi,
                                    prodottostr,
                                    quantita
            );
        } else {
            pNodoProdotto->quantita += quantita;
        }

        pNodoOrdine->ordine.numero_prodotti += quantita;

    }

    fclose(fp);
    return 1;
}

/*
 * 2. Ordini che contengono prodotto
 * Questa funzione cerca tutti gli ordini che contengono un certo prodotto e ne restituisce
 * una lista. Il prodotto è passato come parametro.
 *
 * Parametri: coda di ordini, nome del prodotto
 * Restituisce: lista di ordini che contengono il prodotto
 */
ListaOrdini ordini_contenenti_prodotto(CodaOrdini coda, char prodotto[STRLEN]) {
    ListaOrdini lista_ordini = NULL;
    NodoOrdine *pNodoOrdine = coda.primo_elemento;
    NodoProdotto *pNodoProdotto = NULL;

    while (pNodoOrdine != NULL) {
        trova_prodotto(pNodoOrdine->ordine.lista_elementi, prodotto, &pNodoProdotto);

        if (pNodoProdotto != NULL) {
            lista_ordini_aggiungi(&lista_ordini, pNodoOrdine->ordine);
        }
        pNodoOrdine = pNodoOrdine->successivo;
    }

    return lista_ordini;
}


/* 3. Riepilogo numero di prodotti totali per ordine
 * Questa funzione restituisce un vettore contenente
 * il numero di prodotti totali per ogni ordine.
 *
 * Parametri: coda di ordini
 * Restituisce: vettore di interi
 */
int *numero_di_prodotti(CodaOrdini codaOrdini, int *numero_ordini) {

    *numero_ordini = 0;
    for (NodoOrdine *pNodoOrdine = codaOrdini.primo_elemento;
         pNodoOrdine != NULL;
         pNodoOrdine = pNodoOrdine->successivo)
        (*numero_ordini)++;

    int *vettore = (int *) malloc(sizeof(int) * (*numero_ordini));
    if (vettore == NULL) {
        printf("Errore nell'allocazione del vettore\n");
        return NULL;
    }

    int i = 0;
    for (NodoOrdine *pNodoOrdine = codaOrdini.primo_elemento;
         pNodoOrdine != NULL;
         pNodoOrdine = pNodoOrdine->successivo)

        vettore[i++] = pNodoOrdine->ordine.numero_prodotti;

    return vettore;
}

void dealloca_lista_ordini(ListaOrdini lista) {
    NodoOrdine *pNodoOrdine = lista;
    NodoOrdine *pNodoOrdineSuccessivo = NULL;

    while (pNodoOrdine != NULL) {
        pNodoOrdineSuccessivo = pNodoOrdine->successivo;
        free(pNodoOrdine);
        pNodoOrdine = pNodoOrdineSuccessivo;
    }
}


int main(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    CodaOrdini codaOrdini;
    char prodotto[STRLEN];
    int *vettore = NULL;
    int numero_ordini = 0;

    // Lo studente implementi le seguenti opzioni del menu' usando le funzioni date nel testo
    // quando possibile
    int selezione;
    do {
        printf("\n\n\n"
               "1. carica i dati da file\n"
               "2. Stampa il riepilogo degli ordini\n"
               "3. Trova gli ordini contenenti un prodotto\n"
               "4. Calcola il numero di prodotti per ogni ordine\n"
        );

        printf("\n>>> ");
        scanf("%d", &selezione);
        fflush(stdin);
        switch (selezione) {
            case 0:
                printf("Fine del programma\n");
                break;
            case 1: {
                // Caricamento dei dati
                // Legge il nome del file da caricare e chiama la funzione carica_file

                char filename[STRLEN];
                printf("Inserisci il nome del file:\n1");
                scanf("%s", filename);

                printf("\n");
//            carica_file("ordini.txt", &codaOrdini);
                carica_file(filename, &codaOrdini);

                break;
            }
            case 2:
                // Lo studente stampi il riepilogo degli ordini
                // usando la funzione stampa_ordini
                // NB: la funzione stampa_ordini e' gia' implementata e accetta
                // come parametro una lista di ordini.
                // La coda è una struttura lineare come la lista, non c'è
                // bisogno di convertirla ma di passare il campo corretto...

                stampa_ordini(codaOrdini.primo_elemento);

                break;
            case 3:
                // Trova gli ordini contenenti un prodotto
                // Lo studente implementi la funzione ordini_contenenti_prodotto
                // e la usi per stampare gli ordini contenenti un prodotto
                // NB: la funzione stampa_ordini e' gia' implementata e accetta
                // come parametro una lista di ordini.

                // Deallocare la lista di ordini dopo averla stampata...

                printf("Inserisci il nome del prodotto: ");
                if (scanf("%s", prodotto) != 1)
                    printf("Errore nella lettura del prodotto\n");

                ListaOrdini lista = ordini_contenenti_prodotto(codaOrdini, prodotto);
                stampa_ordini(lista);
                dealloca_lista_ordini(lista);
                break;
            case 4:
                // Stampa il numero di elementi per ogni ordine.
                // Quindi deallocare il vettore...

                vettore = numero_di_prodotti(codaOrdini, &numero_ordini);
                for (int i = 0; i < numero_ordini; i++)
                    printf("Ordine posizione %d: %d prodotti\n", i, vettore[i]);

                free(vettore);

                break;

            default:
                printf("Selezione non valida!\n");
                break;
        }
    } while (selezione != 0);
}