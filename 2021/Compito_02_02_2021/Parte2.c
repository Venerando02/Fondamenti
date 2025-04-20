/*
** Scrivere un programma in ANSI C che risolva il seguente problema.

I dati rilevati durante un controllo di alcuni prodotti sono memorizzati in un
file testo (allegato all'attività 'prodotti.txt').
 Per ogni prodotto è memorizzato:
 - il codice del prodotto
 - la categoria del prodotto
 - quantita' Disponibile

Il codice del prodotto è rappresentato da una stringa che deve esser univoca mentre
la categoria del prodotto puo' assumere sono uno dei tre valori seguenti:
     "novita"
     "esaurito"
     "disponibile"

 Nel caso di prodotti esauriti la quantita' deve essere necessariamente uguale a 0.

 Il contenuto dell'archivio viene caricato in un vettore di liste, una per ciascuna
 categoria del prodotto, quindi ogni lista del vettore contiene una sola categoria di prodotti

Implementare le seguenti funzioni:

1. CaricaProdotti: carica l'elenco dei prodotti nel vettore di liste verificando che per i
prodotti di tipo "esaurito la quantita' sia uguale a zero. Elementi di tipologia diversa da
quelle previste vanno trascurati.
Si supponga per semplicita che non ci siano duplicati nei codici dei prodotti.

2. Inserisce un prodotto della categoria "novita" aggiungendo l'elemento se il codice non e' presente o
aggiornando la quantita' nel caso contrario.

3. EliminaProdotto: estrae  dal vettore tutti i prodotti che hanno in magazzino una quantita
disponibile < K e li restituisce in una lista ordinata rispetto alla quantita disponibile.

La descrizione dettagliata di ogni funzione è riportata come commento immediatamente prima della
definizione della funione.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE  "prodotti.txt"
#define N 3

typedef struct prodotti {
    char  codice[8];
    char  descrizione[15];
    int quantita;
} Tprodotto;

typedef struct NodoListaProdotto {
    Tprodotto prodotto;
    struct NodoListaProdotto* succ;
} TNodoListaProdotti, * PNodoListaProdotti;


/* AggiungiProdottoInTesta inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiProdottoInTesta(PNodoListaProdotti* prodotti, Tprodotto prodotto) 
{
    PNodoListaProdotti aux;
    aux = (PNodoListaProdotti)malloc(sizeof(TNodoListaProdotti));
    if (aux == 0) return 0;
    aux->prodotto = prodotto;
    aux->succ = *prodotti;
    *prodotti = aux;
    return 1;
}

/* AggiungiProdottoOrdinato
   inserisce un elemento nella lista in modo
   ordinato rispetto alla quantita'.
   Restituisce 1 se l'operazione va a buon fine, 0 altrimenti */
int AggiungiProdottoOrdinato(PNodoListaProdotti* PListaprodotti, Tprodotto prodotto) 
{
    // Implementazione a cura dello studente
    if ((*PListaprodotti) == NULL || (*PListaprodotti)->prodotto.quantita >prodotto.quantita)
    {
        return AggiungiProdottoInTesta(&((*PListaprodotti)), prodotto);
    }
    else
    {
        return AggiungiProdottoOrdinato(&((*PListaprodotti)->succ), prodotto);
    }
}

/* presente
   Ricerca di un elemento dato il codice, ritorna il puntatore all'elemento se esiste NULL altrimenti.
*/
PNodoListaProdotti  presente(PNodoListaProdotti PListaprodotti, Tprodotto prodotto) 
{
    // Implementazione a cura dello studente     
    PNodoListaProdotti aux = PListaprodotti;
    while (aux != NULL)
    {
        if (strcmp(aux->prodotto.codice, prodotto.codice) == 0)
        {
            return aux;
        }
        aux = aux->succ;
    }
    return NULL;
}

/* 
estraiTesta
estrae un elemento dalla testa della lista rimuovendolo, il valore trovato e restituito usando il parametro px,
Resituisce 0 se la lista e' vuota
*/
int estraiTesta(PNodoListaProdotti* prodotti, Tprodotto* px) 
{
    PNodoListaProdotti aux;
    if (*prodotti == NULL) return 0;
    else {
        *px = (*prodotti)->prodotto;
        aux = *prodotti;
        *prodotti = (*prodotti)->succ;
        free(aux);
        return 1;
    }
}

void stampaProdotto(Tprodotto p) 
{
    printf("\n%s : %s %d", p.codice, p.descrizione, p.quantita);
}

/* stampaListaProdotti:
   visualizza i prodotti di una lista fornita come parametro di ingresso
*/
void stampaListaProdotti(PNodoListaProdotti lista) 
{
    while (lista != NULL) 
    {
        printf("%s: %s %d\n", lista->prodotto.codice, lista->prodotto.descrizione, lista->prodotto.quantita);
        lista = lista->succ;
    }
}

int RestituisciIndice(Tprodotto v) 
{
    if (strcmp(v.descrizione, "novita") == 0)
        return 0;
    else if (strcmp(v.descrizione, "esaurito") == 0)
        return 1;
    else if (strcmp(v.descrizione, "disponibile") == 0)
        return 2;
}

/*
  1. CaricaProdotti: carica l'elenco dei prodotti nel vettore di liste ordinate di prodotti.

  Parametri di ingresso: nome del file
  Parametri di uscita: vettore dei prodotti
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
 */
int CaricaProdotti(char* nome_file, PNodoListaProdotti* vettoreProdotti) 
{
    // inserire il corpo della funzione    
    FILE* fp;
    Tprodotto aux;
    fp = fopen(nome_file, "r");
    if (fp == NULL) 
    {
        printf("IMPOSSIBILE APRIRE IL FILE.");
        return 0;
    }
    int indice;
    while (fscanf(fp, "%s%s%d", aux.codice, aux.descrizione, &aux.quantita) == 3)
    {
        if ((strcmp(aux.descrizione, "esaurito") == 0) && aux.quantita != 0)
        {
            continue;
        }
        indice = RestituisciIndice(aux);
        if (!AggiungiProdottoOrdinato(&vettoreProdotti[indice], aux)) 
        {
            fclose(fp);
            return 0; 
        }
    }
    fclose(fp);
    return 1;
}

/*   2.Inserisce un nuovo prodotto della categoria "novita" verificando che il codice non sia stato
    gia' utilizzando. Nel caso sia presente nella lista novita' aggiorna la quantita'

    Parametri di ingresso: vettore di liste, prodotto
    Parametro di uscita: nessuno
    Valore restituito: 1 se è stato inserito, 0 se non è stato inserito perche gia presente,
                      -1 se non è stato inserito perchè di categoria errata
*/

int NuovoProdotto(PNodoListaProdotti* vettoreProdotti, Tprodotto p) 
{
    // inserire il corpo della funzione  
    if (strcmp(p.descrizione, "novita") != 0)
        return -1;
    int indice = RestituisciIndice(p);
    PNodoListaProdotti aux = vettoreProdotti[indice];
    PNodoListaProdotti lista;
    while (aux != NULL)
    {
        lista = presente(aux, p);
        if (lista == NULL)
        {
            return AggiungiProdottoOrdinato(&aux, p);
        }
        else 
        {
            aux->prodotto.quantita+=p.quantita;
            return 0;
        }
        aux = aux->succ;
    }
}

/*  3. EliminaProdotto: estrae  dal vettore tutti i prodotti che hanno in magazzino una
    quantita' disponibile maggiore di K e li restituisce in una lista ordinata rispetto alla quantita disponibile.

    Parametri di ingresso: vettore di liste, intero (parametro K)
    Parametro di uscita: nessuno
    Valore restituito: lista prodotti
*/

PNodoListaProdotti ProdottiK(PNodoListaProdotti* vettoreProdotti, int k) {
    // inserire il corpo della funzione    
    PNodoListaProdotti lista = NULL;
    Tprodotto prodotto;
    for (int i = 0; i < N; i++) 
    {
        while (vettoreProdotti[i] != NULL) 
        {
            if (vettoreProdotti[i]->prodotto.quantita > k)
            {
                estraiTesta(&vettoreProdotti[i], &prodotto);
                AggiungiProdottoOrdinato(&lista, prodotto);
            }
            else
            {
                vettoreProdotti[i] = vettoreProdotti[i]->succ;
            }
        }
    }
    return lista;
}

//funzioni di utilita

void stampaVettoreProdotti(Tprodotto* vettoreProdotti, int dimensione) {
    for (int i = 0; i < dimensione; i++)
        stampaProdotto(vettoreProdotti[i]);
}

int Menu()
{
    int scelta;

    printf("*** M E N U ***\n"
        "1 - Carica prodotti\n"
        "2 - Inserisce un nuovo prodotto\n"
        "3 - EliminaProdotto\n"
        "0 - Uscita\n\n"
        "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}

void DisallocaListaProdotti(PNodoListaProdotti* lista)
{
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
    for (int i = 0; i < dimensione; i++)
        DisallocaListaProdotti(&vet[i]);
}

int main(void)
{
    PNodoListaProdotti vettoreListeProdotti[N] = { NULL };
    Tprodotto* vettoreProdotti;
    PNodoListaProdotti listaProdottiBassaDisponibilita;
    Tprodotto p;
    int scelta;
    int k;
    int n;

    do {
        scelta = Menu();

        switch (scelta)
        {
        case 1:
            // Invocare la funzione CaricaProdotti e visualizzare un messaggio
            //in caso di errore
            if (!CaricaProdotti(NOME_FILE, vettoreListeProdotti))
                printf("Errore durante il caricamento di %s\n", NOME_FILE);
            // visualizzare i dati caricati nel vettore di prodotti
            for (int i = 0; i < N; i++)
            {
                printf("TIPOLOGIA %d\n", i);
                stampaListaProdotti(vettoreListeProdotti[i]);
            }
            printf("\n");
            break;

        case 2:
            // Acquisire il  prodotto
            printf("\ninserisci il codice del prodotto  ");
            scanf("%s", p.codice);
            printf("\ninserisci la quantita'  ");
            scanf("%d", &p.quantita);
            strcpy(p.descrizione, "novita");
            //invocare la funzione NuovoProdotto
            n = NuovoProdotto(vettoreListeProdotti, p);
            printf("\nRISULTATO:\n");
            for (int i = 0; i < N; i++)
            {
                printf("TIPOLOGIA %d\n", i);
                stampaListaProdotti(vettoreListeProdotti[i]);
            }
            printf("\n");
            break;
        case 3:
            //
            printf("\ninserisci il valore k:  ");
            scanf("%d", &k);
            // Invocare la funzione ProdottiInScadenza
            listaProdottiBassaDisponibilita = ProdottiK(vettoreListeProdotti, k);
            // Stampa la lista restituita
            stampaListaProdotti(listaProdottiBassaDisponibilita);
            break;
        }

    } while (scelta != 0);

    // Disallocare il vettore dei prodotti;
    DisallocaVettoreProdotti(vettoreListeProdotti, N);

    return 0;
}
