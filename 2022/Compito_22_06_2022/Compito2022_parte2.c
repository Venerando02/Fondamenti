/*
  Sviluppo di una applicazione in ANSI C per gestire un autonoleggio.
  Su un archivio (allegato all'attività nel file auto.dat) è
  memorizzato il parco auto di un autonoleggio.
  Per ciascuna delle autovetture (una per riga del file) sono presenti le
  seguenti informazioni
  Modello Targa km_percorsi

  Implementare le seguenti funzioni:

  1. CaricaParcoAuto: carica l'elenco delle autovetture in una lista di modelli,
  La lista dei modelli contiene, per ogni modello, il nome del modello e la lista delle
  auto di quel modello (targa e km percorsi).

  2. CreaListaVetture: a partire dalla lista dei modelli e di una soglia restituisce
  la targa di tutte le autovetture (indipendentemente dal
  modello) che hanno percorso meno km della soglia fornita.

  3. Cancella tutte le vetture di un dato modello

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funzione.
  */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE  "auto.dat"

typedef struct a {
    char  targa[8];
    int km_percorsi;
} TAuto;

typedef struct NodoListaAuto {
    TAuto info;
    struct NodoListaAuto* succ;
} TNodoListaAuto, * ListaAuto;

typedef struct NodoModelli {
    char modello[32];
    ListaAuto listaA;
    struct NodoModelli* succ;
} TNodoListaModelli, * ListaModelli;

/* AggiungiAuto
    inserisce un elemento in testa alla lista delle auto
    passata come primo parametro. Restituisce 1 se l'operazione va a buon fine,
    0 altrimenti
 */
int AggiungiAuto(ListaAuto* pA, TAuto car) {
    ListaAuto aux;

    aux = (ListaAuto)malloc(sizeof(TNodoListaAuto));

    if (aux == 0)
        return 0;

    aux->info = car;
    aux->succ = *pA;

    *pA = aux;

    return 1;
}

/*
*   Svuota la lista delle automobili, restituendo la lista modificata
*/
ListaAuto cancellaLista(ListaAuto L) {
    ListaAuto aux;
    while (L != NULL) {
        aux = L;
        L = L->succ;
        free(aux);
    }
    return NULL;
}

/*
* Aggiunge un modello se non presente e ne restituisce il puntatore, altrimenti
* restituisce il puntatore all'elemento trovato
*/
ListaModelli AggiungiModello(ListaModelli* pM, char* NewModello) {

    ListaModelli aux = *pM;

    while (aux != NULL) {
        if (strcmp(aux->modello, NewModello) == 0)
            return aux;
        aux = aux->succ;
    }
    aux = (ListaModelli)malloc(sizeof(TNodoListaModelli));

    if (aux == 0)
        return 0;

    strcpy(aux->modello, NewModello);
    aux->listaA = NULL;
    aux->succ = *pM;

    *pM = aux;

    return aux;
}

/*
  1. CaricaAuto: carica l'elenco delle auto in una lista di liste. Ciascuna elemento
  della lista dei modelli contiene oltre il nome del modello la lista delle auto del
  dato modello. .
  Per le vetture dello stesso modello viene conservata la lista delle targhe e
  per ciascuna autovetture il numero di km_percorsi.

  Parametri di ingresso: nome del file
  Parametri di uscita: liste di modelli
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
 */
int CaricaAuto(char* nome_file, ListaModelli* pLM) 
{
    //da sviluppare
    FILE* fp = fopen(nome_file, "r");
    if (fp == NULL)
        return 0;
    char Modello[32];
    ListaModelli Lista;
    TAuto vettura;
    while (fscanf(fp, "%s%s%d", Modello, vettura.targa, &vettura.km_percorsi) == 3) 
    {
        Lista = AggiungiModello(pLM, Modello);
        if (!AggiungiAuto(&(Lista->listaA), vettura))
            return 0;
    }
    return 1;
}


/*
   2.
  CreaListaVetture: a partire dalla lista delle autovettura di un certo tipoVettura
  e di una soglia restituisce la targa delle autovetture (indipendentemente dal
  modello) che hanno percorso meno km della soglia fornita.


   Parametri di ingresso: listaModelli e una soglia
   Parametri di uscita: nessuno
   Tipo di ritorno: lista delle autovetture che hanno percorso meno km della soglia fornita.
*/
ListaAuto CreaListaVetture(ListaModelli LM, int soglia) 
{
    //da sviluppare
    ListaAuto ListaOut = NULL;
    ListaAuto Aux;
    while (LM != NULL) 
    {
        Aux = LM->listaA;
        while (Aux != NULL) 
        {
            if (Aux->info.km_percorsi <= soglia) 
            {
                if (!AggiungiAuto(&ListaOut, Aux->info))
                    return NULL;
            }
            Aux = Aux->succ;
        }
        LM = LM->succ;
    }
    return ListaOut;
}

/*
  3. CancellaModello tutte le vetture di un dato modello. Attenzione vanno cancellati
  tutti gli elementi della lista relativa al modello da cancellare



  Parametri di ingresso: lista di modelli, modello
  Parametri di uscita:
  Tipo di ritorno: lista di modelli dal quale sono state eliminate tutte le vetture di un dato modello
*/
/*
ListaModelli CancellaModello(ListaModelli L, char* modelloDaEliminare)
{
    //da sviluppare
    if (L == NULL)
        return L;
    TNodoListaModelli* Corrente = L;
    TNodoListaModelli* Precedente = NULL;
    if (strcmp(Corrente->modello, modelloDaEliminare) == 0) 
    {
        L = Corrente->succ;
        Corrente->listaA = cancellaLista(Corrente->listaA);
        free(Corrente);
        return L;
    }
    while (Corrente != NULL)
    {
        if (strcmp(Corrente->modello, modelloDaEliminare) == 0)
        {
            Precedente->succ = Corrente->succ;
            Corrente->listaA = cancellaLista(Corrente->listaA);
            free(Corrente);
            return L;
        }
        Precedente = Corrente;
        Corrente = Corrente->succ;
    }
    return L;
}
*/

ListaModelli CancellaModello(ListaModelli L, char* modelloDaEliminare)
{
    //da sviluppare
    if (L == NULL)
        return L;
    TNodoListaModelli* aux;
    if (strcmp(L->modello, modelloDaEliminare) == 0)
    {
        L->listaA = cancellaLista(L->listaA);
        aux = L;
        L = L->succ;
        free(aux);
        return L;
    } 
    L->succ = CancellaModello(L->succ, modelloDaEliminare);
    return L;
}

/*visualizza lista Auto*/
void VisualizzaListaAuto(ListaAuto L) {
    while (L != NULL) {
        printf("\n  targa = %s, km = %d", L->info.targa, L->info.km_percorsi);
        L = L->succ;
    }
}
/*
  Visualizza Lista modelli */
void VisualizzaListaModelli(ListaModelli L) 
{
    //da sviluppare
    while (L != NULL) 
    {
        printf("MODELLO: %s\n", L->modello);
        VisualizzaListaAuto(L->listaA);
        printf("\n");
        L = L->succ;
    }
}

int Menu()
{
    int scelta;

    printf("*** M E N U ***\n"
        "1 - Carica auto\n"
        "2 - Crea lista vettura con km minore di soglia\n"
        "3 - Cancella modello\n"
        "0 - Uscita\n\n"
        "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}





int main(void)
{
    ListaModelli LM = NULL;
    ListaAuto la = NULL;

    int   scelta, soglia;
    char modello[20];

    do {
        scelta = Menu();

        switch (scelta)
        {
        case 1:
            /* Invocare la funzione CaricaAuto e se il caricamento è andato a buon fine
            Visualizzare la lista completa della auto caricate*/
            if(CaricaAuto(NOME_FILE, &LM))
                VisualizzaListaModelli(LM);
            printf("\n");
            break;

        case 2:
            //inserire il valore si soglia per i chilometri
            printf("Inserisci il valore di soglia: ");
            scanf("%d", &soglia);
          // Invocare la funzione  per ottenre la lista di auto che soddisfano la condidizione
          //di aver percorso meno chilometri della soglia
            la = CreaListaVetture(LM, soglia);
          //stampare la lista delle auto
            VisualizzaListaAuto(la);
            printf("\n");
            break;

        case 3:
            // acquisire il nome del modello da cancellare
            printf("Inserisci il modello da cancellare: ");
            scanf("%s", modello);
            // Invocare la funzione CancellaModello
            LM = CancellaModello(LM, modello);
            // Visualizzare la lista dei modelli
            VisualizzaListaModelli(LM);
            break;
        }

    } while (scelta != 0);
    return 0;
}

