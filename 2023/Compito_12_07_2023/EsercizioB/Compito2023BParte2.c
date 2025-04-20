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
      PRODOTTO QUANTITA' ORDINE
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
    struct prodotto_struct* successivo;
} NodoProdotto;

typedef NodoProdotto* ListaProdotti;

typedef struct {
    char id_ordine[STRLEN];
    int numero_prodotti;
    ListaProdotti lista_elementi;
} Ordine;

typedef struct ordine_struct {
    Ordine ordine;
    struct ordine_struct* successivo;
} NodoOrdine;

typedef struct 
{
    NodoOrdine* primo_elemento;
    NodoOrdine* ultimo_elemento;
} CodaOrdini;

typedef NodoOrdine* ListaOrdini;


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
NodoOrdine* coda_ordini_aggiungi(CodaOrdini* coda, char* id_ordine)
{
    NodoOrdine* nuovo_nodo = (NodoOrdine*)malloc(sizeof(NodoOrdine));
    if (nuovo_nodo == NULL) {
        printf("Errore di allocazione memoria");
        exit(1);
    }

    strcpy(nuovo_nodo->ordine.id_ordine, id_ordine);
    nuovo_nodo->ordine.numero_prodotti = 0;
    nuovo_nodo->ordine.lista_elementi = NULL;

    nuovo_nodo->successivo = NULL;
    if (coda->primo_elemento == NULL) 
    {
        coda->primo_elemento = nuovo_nodo;
        coda->ultimo_elemento = nuovo_nodo;
    }
    else 
    {
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
void lista_prodotti_aggiungi(ListaProdotti* lista, char* nome_prodotto, int quantita) 
{
    NodoProdotto* nuovo_nodo = malloc(sizeof(NodoProdotto));

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
void lista_ordini_aggiungi(ListaOrdini* lista, Ordine ordine) 
{
    NodoOrdine* nuovo_nodo = malloc(sizeof(NodoOrdine));
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
void trova_ordine(ListaOrdini lista_ordini, char* id_ordine, NodoOrdine** ppNodoOrdine) 
{
    while (lista_ordini != NULL) 
    {
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
void trova_prodotto(ListaProdotti lista_prodotti, char prodotto[STRLEN], NodoProdotto** ppNodoProdotto) 
{
    while (lista_prodotti != NULL) 
    {
        if (strcmp(lista_prodotti->nome, prodotto) == 0) {
            *ppNodoProdotto = lista_prodotti;
            return;
        }
        lista_prodotti = lista_prodotti->successivo;
    }
    *ppNodoProdotto = NULL;
}


void dealloca_lista_ordini(ListaOrdini lista)
{
    NodoOrdine* pNodoOrdine = lista;
    NodoOrdine* pNodoOrdineSuccessivo = NULL;

    while (pNodoOrdine != NULL) {
        pNodoOrdineSuccessivo = pNodoOrdine->successivo;
        free(pNodoOrdine);
        pNodoOrdine = pNodoOrdineSuccessivo;
    }
}


/////////////////////////////////////////////////////////////////////////////////////////
//
// Funzioni da implementare a cura dello studente
// Usare le funzioni definite sopra, dove possibile
//
/////////////////////////////////////////////////////////////////////////////////////////

// Funzione che stampa il contenuto della coda degli ordini
void stampa_ordini(ListaOrdini lista_ordini)
{
    // DA IMPLEMENTARE A CURA DELLO STUDENTE
    while (lista_ordini != NULL) 
    {
        stampa_ordine(lista_ordini->ordine);
        lista_ordini = lista_ordini->successivo;
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
int carica_file(const char* nomefile, CodaOrdini* pc) 
{
    // DA IMPLEMENTARE A CURA DELLO STUDENTE
    FILE* fp = fopen(nomefile, "r");
    if (fp == NULL)
        return 0;
    char Prodotto[STRLEN];
    char O[STRLEN];
    int Quantita;
    ListaOrdini aux = NULL;
    ListaProdotti aux2 = NULL;
    NodoOrdine* CodaAUX = NULL;
    while (fscanf(fp, "%s%d%s", Prodotto, &Quantita, O) == 3) 
    {
        trova_ordine((*pc).primo_elemento, O, &aux);
        if (aux != NULL) 
        {
            trova_prodotto(aux->ordine.lista_elementi, Prodotto, &aux2);
            if (aux2 != NULL) 
            {
                aux2->quantita += Quantita;
            }
            else 
            {
                lista_prodotti_aggiungi(&(aux->ordine.lista_elementi), Prodotto, Quantita);
                aux->ordine.numero_prodotti += Quantita;
            }
        }
        else 
        {
            CodaAUX = coda_ordini_aggiungi(pc, O);
            lista_prodotti_aggiungi(&(CodaAUX->ordine.lista_elementi), Prodotto, Quantita);
            CodaAUX->ordine.numero_prodotti += Quantita;
        }
    }
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
ListaOrdini ordini_contenenti_prodotto(CodaOrdini coda, char prodotto[STRLEN]) 
{
    // DA IMPLEMENTARE A CURA DELLO STUDENTE
    if (coda.primo_elemento == NULL)
        return NULL;
    ListaOrdini ListaOUT = NULL;
    NodoOrdine* CodaPrimo = coda.primo_elemento;
    NodoProdotto* ListaElementi = NULL;
    while (CodaPrimo != NULL) 
    {
        ListaElementi = CodaPrimo->ordine.lista_elementi;
        while (ListaElementi != NULL) 
        {
            if (strcmp(ListaElementi->nome, prodotto) == 0) 
            {
                lista_ordini_aggiungi(&ListaOUT, CodaPrimo->ordine);
            }
            ListaElementi = ListaElementi->successivo;
        }
        CodaPrimo = CodaPrimo->successivo;
    }
    return ListaOUT;
}


/* 3. Riepilogo numero di prodotti totali per ordine
 * Questa funzione restituisce un vettore contenente
 * il numero di prodotti totali per ogni ordine.
 *
 * Parametri: coda di ordini
 * Restituisce: vettore di interi
 */
int* numero_di_prodotti(CodaOrdini codaOrdini, int* numero_ordini) {
    // DA IMPLEMENTARE A CURA DELLO STUDENTE
    int* VettNumProdottiPerOrdine = NULL;
    (*numero_ordini) = 0;
    NodoOrdine* CodaPrimo = codaOrdini.primo_elemento;
    while (CodaPrimo != NULL) 
    {
        (*numero_ordini)++;
        CodaPrimo = CodaPrimo->successivo;
    }
    VettNumProdottiPerOrdine = (int*)malloc(sizeof(int) * (*numero_ordini));
    if (VettNumProdottiPerOrdine == NULL)
        return NULL;
    CodaPrimo = codaOrdini.primo_elemento;
    NodoProdotto* ListaElementi;
    int cont;
    int index = 0;
    while (CodaPrimo != NULL) 
    {
        cont = 0;
        ListaElementi = CodaPrimo->ordine.lista_elementi;
        while (ListaElementi != NULL) 
        {
            cont++;
            ListaElementi = ListaElementi->successivo;
        }
        VettNumProdottiPerOrdine[index++] = cont;
        CodaPrimo = CodaPrimo->successivo;
    }
    return VettNumProdottiPerOrdine;
}


void InizializzaCoda(CodaOrdini* pcoda) 
{
    (*pcoda).primo_elemento = (*pcoda).ultimo_elemento = NULL;
}


int main(int argc, char** argv) {
    CodaOrdini codaOrdini;
    InizializzaCoda(&codaOrdini);
    char prodotto[STRLEN];
    int* vettore = NULL;
    ListaOrdini ListaUscita;
    int numero_ordini = 0;
    char NomeFile[STRLEN];
    int e;
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
            printf("Inserisci il nome del file: ");
            scanf("%s", NomeFile);
            // DA IMPLEMENTARE A CURA DELLO STUDENTE
            e = carica_file(NomeFile, &codaOrdini);
            if (e != 0)
                printf("Caricamento dati sulla coda andato a buon fine.\n");
            break;
        }
        case 2:
            // Lo studente stampi il riepilogo degli ordini
            // usando la funzione stampa_ordini
            // NB: la funzione stampa_ordini e' gia' implementata e accetta
            // come parametro una lista di ordini.
            // La coda è una struttura lineare come la lista, non c'è
            // bisogno di convertirla ma semplicemente di passare il campo corretto...
            // DA IMPLEMENTARE A CURA DELLO STUDENTE
            stampa_ordini(codaOrdini.primo_elemento);
            break;
        case 3:
            // Trova gli ordini contenenti un prodotto
            // Lo studente implementi la funzione ordini_contenenti_prodotto
            // e la usi per stampare gli ordini contenenti un prodotto
            // NB: la funzione stampa_ordini e' gia' implementata e accetta
            // come parametro una lista di ordini.
            printf("Inserisci un prodotto: ");
            scanf("%s", prodotto);
            ListaUscita = ordini_contenenti_prodotto(codaOrdini, prodotto);
            // Deallocare la lista di ordini dopo averla stampata...
            stampa_ordini(ListaUscita);
            dealloca_lista_ordini(ListaUscita);
            // DA IMPLEMENTARE A CURA DELLO STUDENTE

            break;
        case 4:
            // Stampa il numero di elementi per ogni ordine.
            // Quindi deallocare il vettore...
            vettore = numero_di_prodotti(codaOrdini, &numero_ordini);
            printf("Numero totale di ordini: %d\n", numero_ordini);
            for (int i = 0; i < numero_ordini; i++) 
            {
                printf("Ordine %d: %d\n", i, vettore[i]);
            }
            // DA IMPLEMENTARE A CURA DELLO STUDENTE
            free(vettore);
            break;

        default:
            printf("Selezione non valida!\n");
            break;
        }
    } while (selezione != 0);
}