/*
I prodotti di una azienda (allegato all'attività 'prodotti.txt') sono memorizzati in un file testo.
 Per ogni prodotto è memorizzato:
 - il codice del prodotto
 - la tipologia del prodotto
 - la descrizione
 - la data di scadenza nel formato YYYY/MM/AA
I prodotti possono essere di tre tipologie identificate da un valore intero compreso
 tra 0 e 2.
 Il contenuto dell'archivio viene caricato in un vettore di liste.
 Ciascuna lista del vettore contiene una tipologia di prodotti
 ed e' ordinata secondo la data di scadenza.

Implementare le seguenti funzioni:

1. CaricaProdotti: carica l'elenco dei prodotti nel vettore di liste ordinate di prodotti

2. EliminaProdotto: data una tipologia di prodotto e un intero K estrae  dal vettore di prodotti i K
prodotti più vicini alla scadenza della tipologia selezionata e li restituisce
 in un vettore contenente i prodotti estratti.

3. ProdottiInScadenza: data una data restituisce la lista dei prodotti in scadenza entro la data fornita.

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funione.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE  "prodotti.txt"

typedef struct prodotti {
    char  codice[8];
    int   tipoProdotto;
    char  descrizione[200];
    char  data[11];
} Tprodotto;

typedef struct NodoListaProdotto {
    Tprodotto prodotto;
    struct NodoListaProdotto* succ;
} TNodoListaProdotti, * PNodoListaProdotti;


/* AggiungiProdottoInTesta inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiProdottoInTesta(PNodoListaProdotti* prodotti, Tprodotto prodotto) {
    PNodoListaProdotti aux;
    aux = (PNodoListaProdotti)malloc(sizeof(TNodoListaProdotti));
    if (aux == 0) return 0;
    aux->prodotto = prodotto;
    aux->succ = *prodotti;
    *prodotti = aux;
    return 1;
}

/* AggiungiProdottoOrdinato inserisce un elemento nella lista in modo
   ordinato rispetto alla data di scadenza.
   Restituisce 1 se l'operazione va a buon fine, 0 altrimenti */
int AggiungiProdottoOrdinato(PNodoListaProdotti* PListaprodotti, Tprodotto prodotto) {
    if (*PListaprodotti == NULL || strcmp((*PListaprodotti)->prodotto.data, prodotto.data) > 0)
        return AggiungiProdottoInTesta(PListaprodotti, prodotto);
    else return AggiungiProdottoOrdinato((&(*PListaprodotti)->succ), prodotto);
}

/* estraiTesta estrae un elemento dalla testa della lista,
   restituendolo nel parametro px e rimuovendolo dalla lista
   Resituisce 0 se la lista e' vuota
*/
int estraiTesta(PNodoListaProdotti* prodotti, Tprodotto* px) 
{
    /* implementazione a cura dello studente */
    if ((*prodotti) == NULL)
        return 0;
    PNodoListaProdotti aux;
    aux = (*prodotti);
    (*px) = aux->prodotto;
    (*prodotti) = (*prodotti)->succ;
    free(aux);
    return 1;
}


void stampaProdotto(Tprodotto p) {
    printf("\n%s   %d %s  %s", p.codice, p.tipoProdotto, p.descrizione, p.data);
}

/* stampaListaProdotti:
   visualizza i prodotti di una lista fornita come parametro di ingresso
*/
void stampaListaProdotti(PNodoListaProdotti lista) {
    while (lista != NULL) {
        stampaProdotto(lista->prodotto);
        lista = lista->succ;
    }
}

/*
  1. CaricaProdotti: carica l'elenco dei prodotti nel vettore di liste ordinate di prodotti.

  Parametri di ingresso: nome del file
  Parametri di uscita: vettore dei prodotti
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
 */
int CaricaProdotti(char* nome_file, PNodoListaProdotti* vettoreProdotti) {
    /* implementazione a cura dello studente */
    FILE* fp = fopen(nome_file, "r");
    if (fp == NULL)
        return 0;
    Tprodotto Pr;
    while (fscanf(fp, "%s%d%s%s", Pr.codice, &Pr.tipoProdotto, Pr.descrizione, Pr.data) == 4) 
    {
        if (!AggiungiProdottoOrdinato(&vettoreProdotti[Pr.tipoProdotto], Pr))
            return 0;
    }
    return 1;
}

/*  
    2. Ingresso: EliminaProdotto: data una tipologia di prodotto e un intero K estrae
    dal vettore di prodotti i K prodotti più vicini alla scadenza della tipologia selezionata e li restituisce
    in un vettore contenente i prodotti estratti.
    Parametri di ingresso: vettore di liste, tipologia di prodotto, numero di elementi da estrarre
    Parametreo di uscita: numero di elementi realmente estratti
    Valore restituito: vettore dei prodotti in scadenza
*/

Tprodotto* EliminaProdotto(PNodoListaProdotti* vettoreProdotti, int tipo, int k, int* num) {
    /* implementazione a cura dello studente */
    (*num) = 0;
    PNodoListaProdotti lista = vettoreProdotti[tipo];
    if (lista == NULL)
        return NULL;
    Tprodotto* vout = (Tprodotto*)malloc(sizeof(Tprodotto) * k);
    if (vout == NULL)
        return NULL;
    int cont = 0;
    int index = 0;
    Tprodotto aux;
    while (cont < k) 
    {
      if (!estraiTesta(&lista, &aux))
          return 0;
       vout[index++] = aux;
       cont++;
    }
    (*num) = cont;
    return vout;
}

/*   3. ProdottiInScadenza: data una data restituisce la lista dei prodotti in scadenza entro la data fornita.
    Parametri di ingresso: vettore di liste, la dimensione del vettore di liste, data
    Valore restituito: lista dei prodotti in scadenza
*/

PNodoListaProdotti ProdottiInScadenza(PNodoListaProdotti* vettoreProdotti, int dimensione, char* data) 
{
    /* implementazione a cura dello studente */
    PNodoListaProdotti listaout = NULL;
    PNodoListaProdotti listatipo;
    for (int i = 0; i < dimensione; i++) 
    {
        listatipo = vettoreProdotti[i];
        while (listatipo != NULL) 
        {
            if (strcmp(listatipo->prodotto.data, data) < 0) 
            {
                if (!AggiungiProdottoInTesta(&listaout, listatipo->prodotto))
                    return NULL;
            }
            listatipo = listatipo->succ;
        }
    }
    return listaout;
}

//funzioni di utilita

void stampaVettoreProdotti(Tprodotto* vettoreProdotti, int dimensione) 
{
    for (int i = 0; i < dimensione; i++) stampaProdotto(vettoreProdotti[i]);
}




int Menu()
{
    int scelta;

    printf("\n\n*** M E N U ***\n"
        "1 - Carica prodotti\n"
        "2 - EliminaProdotto\n"
        "3 -Prodotti in scadenza\n"
        "0 - Uscita\n\n"
        "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}

void DisallocaListaProdotti(PNodoListaProdotti* lista) {
    PNodoListaProdotti p;

    while (*lista != NULL)
    {
        p = *lista;
        *lista = (*lista)->succ;
        free(p);
    }
}

void DisallocaVettoreProdotti(PNodoListaProdotti* vet, int dimensione)
{
    /* implementazione a cura dello studente */
    for (int i = 0; i < dimensione; i++) 
    {
        DisallocaListaProdotti(vet[i]);
    }
}

int main(void)
{
    PNodoListaProdotti vettoreListeProdotti[3];
    for (int i = 0; i < 3; i++)
        vettoreListeProdotti[i] = NULL;
    Tprodotto* vettoreProdotti;
    PNodoListaProdotti listaProdottiInScadenza;
    int        scelta;
    int dimensione = 3;
    int tipo, numeroElementi;
    int n;
    char data[11];
    int esito;

    do {
        scelta = Menu();

        switch (scelta)
        {
        case 1:
            // Invocare la funzione CaricaProdotti e visualizzare un messaggio
            //in caso di errore
            esito = CaricaProdotti(NOME_FILE, vettoreListeProdotti);
            // visualizzare i dati caricati nel vettore di prodotti
            if (esito == 1) 
            {
                for (int i = 0; i < dimensione; i++)
                {
                    stampaListaProdotti(vettoreListeProdotti[i]);
                    printf("\n");
                }
            }
            break;

        case 2:
            // Acquisire il tipo del prodotto e il numero di elementi da scaricare
            printf("Inserisci il tipo del prodotto: ");
            scanf("%d", &tipo);
            printf("Inserisci il numero di Elementi da scaricare: ");
            scanf("%d", &numeroElementi);
            //invocare la funzione EliminaProdotto
            vettoreProdotti = EliminaProdotto(vettoreListeProdotti, tipo, numeroElementi, &n);
            //stampare il vettore restituito dalla funzione EliminaProdotto
            stampaVettoreProdotti(vettoreProdotti, n);
            break;

        case 3:
            //acquisire la data
            printf("Inserisci la data: ");
            scanf("%s", data);
            // Invocare la funzione ProdottiInScadenza
            listaProdottiInScadenza = ProdottiInScadenza(vettoreListeProdotti, dimensione, data);
            // Visualizzare l'elenco dei prodotti in scadenza
            stampaListaProdotti(listaProdottiInScadenza);
            //Disallocare la lista dei prodotti in scadenza
            DisallocaListaProdotti(&listaProdottiInScadenza);
            break;
        }

    } while (scelta != 0);

    // Disallocare il vettore dei prodotti;
    DisallocaVettoreProdotti(vettoreListeProdotti, dimensione);
    return 0;
}
