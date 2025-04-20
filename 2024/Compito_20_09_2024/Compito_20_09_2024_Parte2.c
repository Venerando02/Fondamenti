/*
I dati rilevati durante un controllo di alcuni prodotti sono memorizzati in un file
testo (allegato all'attività 'prodotti.txt').
 Per ogni prodotto è memorizzato:
 - il codice del prodotto
 - la categoria del prodotto
 - quantità

Il codice del prodotto e una stringa che deve esser univoca mentre la categoria del prodotto puo' avere solo tre valori:
 "venduto"
 "disponibile"
 "ordinato"

 Il contenuto dell'archivio viene caricato in un vettore di liste, ordinate rispetto alla quantità di
 prodotti, una per ciascuna categoria del prodotto
 Ciascuna lista del vettore contiene una tipologia di prodotti

Implementare le seguenti funzioni:

1. CaricaProdotti: carica l'elenco dei prodotti nel vettore di liste ordinate verificando che la tipologia sia una di quelle
previste, nel caso di elementi di tipologia diversa da quelle previste gli elementi vengono
trascurati.

2. Restituisce in un vettore l'elenco dei prodotti la cui quantità venduta e maggiore di un valore
passato come parametro

3. Dato un codice prodotto e un numero intero procede alla vendita del prodotto.
Se il prodotto è disponibile decrementa la quantità del prodotto nella lista dei disponibili e incrementa
Se il prodotto non è disponibile ed è nella lista dei prodotti ordinati modifica la quantità del prodotto
Se il prodotto non è disponibile e non è nella lista dei prodotti ordinati inserisce il prodotto nella lista dei prodotti
a de-ordinati.


*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE  "prodotti2024.txt"

typedef struct prodotti {
    char codice[8];
    char descrizione[15];
    int quantita;
} Tprodotto;

typedef struct NodoListaProdotto {
    Tprodotto prodotto;
    struct NodoListaProdotto* next;
} TNodoListaProdotti, * PNodoListaProdotti;


/* AggiungiProdottoInTesta inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiProdottoInTesta(PNodoListaProdotti* prodotti, Tprodotto prodotto) {
    PNodoListaProdotti aux;
    aux = (PNodoListaProdotti)malloc(sizeof(TNodoListaProdotti));
    if (aux == 0) return 0;
    aux->prodotto = prodotto;
    aux->next = *prodotti;
    *prodotti = aux;
    return 1;
}

/* AggiungiProdottoOrdinato inserisce un elemento nella lista in modo
   ordinato rispetto alla quantita
   Restituisce 1 se l'operazione va a buon fine, 0 altrimenti */
int AggiungiProdottoOrdinato(PNodoListaProdotti* PListaprodotti, Tprodotto prodotto) {
    //DA IMPLEMENTARE
    if ((*PListaprodotti) == NULL)
    {
        return AggiungiProdottoInTesta(PListaprodotti, prodotto);
    }
    if (prodotto.quantita > ((*PListaprodotti)->prodotto.quantita))
    {
        return AggiungiProdottoInTesta(PListaprodotti, prodotto);
    }
    else
        return AggiungiProdottoOrdinato(&((*PListaprodotti)->next), prodotto);
}


void stampaProdotto(Tprodotto p) {
    printf("\n%s    %s %d", p.codice, p.descrizione, p.quantita);
}

/* stampaListaProdotti:
   visualizza i prodotti di una lista fornita come parametro di ingresso
*/
void stampaListaProdotti(PNodoListaProdotti lista) {
    while (lista != NULL) {
        stampaProdotto(lista->prodotto);
        lista = lista->next;
    }
}

/*
  1. CaricaProdotti: carica l'elenco dei prodotti nel vettore di liste ordinate di prodotti.

  Parametri di ingresso: nome del file
  Parametri di uscita: vettore dei prodotti
  Valore restituito: il numero di prodotti di categoria non riconosciura, -1 se cìeì un errore
 */

PNodoListaProdotti cercaProdotto(PNodoListaProdotti L, char* codiceProdotto) {
    while (L) {
        if (strcmp(L->prodotto.codice, codiceProdotto) == 0) return L;
        L = L->next;
    }
    return NULL;
}

int ritornaIndice(char* descrizione) 
{
    if (strcmp(descrizione, "disponibile") == 0)
        return 0;
    else if (strcmp(descrizione, "ordinato") == 0)
        return 1;
    else if (strcmp(descrizione, "venduto") == 0)
        return 2;
    else
        return -1;
}

int CaricaProdotti(char* nome_file, PNodoListaProdotti* vettoreProdotti) {
    Tprodotto p;
    FILE* f;
    int n = 0;
    //DA COMPLETARE
    f = fopen(nome_file, "r");
    if (f == NULL)
        return -1;
    int indice;
    PNodoListaProdotti aux;
    while (fscanf(f, "%s%s%d", p.codice, p.descrizione, &p.quantita) == 3) 
    {
        if (strcmp(p.descrizione, "disponibile") == 0)
        {
            if (cercaProdotto(vettoreProdotti[0], p.codice) == NULL)
            {
                AggiungiProdottoOrdinato(&vettoreProdotti[0], p);
            }
        }
        else if (strcmp(p.descrizione, "ordinato") == 0)
        {
            if (cercaProdotto(vettoreProdotti[1], p.codice) == NULL)
            {
                AggiungiProdottoOrdinato(&vettoreProdotti[1], p);
            }
        }
        else if (strcmp(p.descrizione, "venduto") == 0)
        {
            if (cercaProdotto(vettoreProdotti[2], p.codice) == NULL)
            {
                AggiungiProdottoOrdinato(&vettoreProdotti[2], p);
            }
        }
        else
            n++;
    }
    fclose(f);
    return n;
}


/*   2.Restituisce in un vettore l'elenco dei prodotti la cui quantita venduta e maggiore di un valore
passato come parametro
    Parametri di ingresso: vettore di liste, codice prodotto, prodotto quantita
    Parametro di uscita: dimensione vettore di prodotti
    Valore restituito: Vettore prodotti
*/

Tprodotto* QuantitaProdotti(PNodoListaProdotti* vettore, int Quantita, int * dimProdotti) 
{
    //DA COMPLETARE
    int dim = 0;
    PNodoListaProdotti aux;
    for (int i = 0; i < 3; i++) 
    {
        aux = vettore[i];
        while (aux != NULL) 
        {
            if ((strcmp(aux->prodotto.descrizione, "venduto") == 0) && (aux->prodotto.quantita > Quantita))
            {
                dim++;
            }
            aux = aux->next;
        }
    }
    (*dimProdotti) = dim;
    Tprodotto* vout = (Tprodotto*)malloc(sizeof(Tprodotto) * dim);
    if (vout == NULL)
        return NULL;
    int index = 0;
    for (int i = 0; i < 3; i++)
    {
        aux = vettore[i];
        while (aux != NULL)
        {
            if ((strcmp(aux->prodotto.descrizione, "venduto") == 0) && (aux->prodotto.quantita > Quantita))
            {
                vout[index++] = aux->prodotto;
            }
            aux = aux->next;
        }
    }
    return vout;
}

/*  
3. Dato un codice prodotto e un numero intero procede alla vendita del prodotto.
Se il prodotto è disponibile decrementa la quantità del prodotto nella lista dei disponibili e incrementa il prodotto nella
lista dei venduti aggiungendolo se non presente
Se il prodotto non è disponibile ed è nella lista dei prodotti ordinati modifica la quantità del prodotto
Se il prodotto non è disponibile e non è nella lista dei prodotti ordinati inserisce il prodotto nella lista dei prodotti
a de-ordinati.
    Parametri di ingresso: vettore di liste, codice prodotto, prodotto quantità
    Valore restituito: void

*/


void Vendita_prodotto(PNodoListaProdotti* vettoreProdotti, char* codiceProdotto)
{
    //DA implementare
    Tprodotto Venduto = {
        .quantita = 1,
        .descrizione = "venduto"
    };
    Tprodotto Ordinato = {
        .quantita = 1,
        .descrizione = "ordinato"
    };
    strcpy(Venduto.codice, codiceProdotto);
    strcpy(Ordinato.codice, codiceProdotto);
    PNodoListaProdotti aux = cercaProdotto(vettoreProdotti[0], codiceProdotto);
    PNodoListaProdotti aux2;
    if (aux != NULL) 
    {
        aux->prodotto.quantita--;
        aux2 = cercaProdotto(vettoreProdotti[2], codiceProdotto);
        if (aux2) aux2->prodotto.quantita--;
        else AggiungiProdottoOrdinato(&vettoreProdotti[2], Venduto);
    }
    else
    {
        aux->prodotto.quantita--;
        aux2 = cercaProdotto(vettoreProdotti[1], codiceProdotto);
        if (aux2) aux2->prodotto.quantita--;
        else AggiungiProdottoOrdinato(&vettoreProdotti[1], Ordinato);
    }
}



//funzioni di utilita

void stampaVettoreProdotti(Tprodotto* vettoreProdotti, int dimensione) {
    for (int i = 0; i < dimensione; i++) stampaProdotto(vettoreProdotti[i]);
}


int Menu() {
    int scelta;

    printf("\n\n*** M E N U ***\n"
        "1 - Carica prodotti\n"
        "2 - Elenco prodotti piu venduti\n"
        "3 - Vendita prodotti\n"
        "0 - Uscita\n\n"
        "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}

void DisallocaListaProdotti(PNodoListaProdotti* lista) {
    PNodoListaProdotti p;

    while (*lista != NULL) {
        p = *lista;
        *lista = (*lista)->next;
        free(p);
    }
}

void DisallocaVettoreListaProdotti(PNodoListaProdotti* vet, int dimensione) {
    //DA COMPLETARE
    for (int i = 0; i < dimensione; i++) 
    {
        DisallocaListaProdotti(&vet[i]);
    }
}

int main(void) 
{
    char VettoreCategorie[3][64] = {"disponibile", "ordinato", "venduto"};
    PNodoListaProdotti vettoreListeProdotti[3];
    for (int i = 0; i < 3; i++)
        vettoreListeProdotti[i] = NULL;
    Tprodotto* vettoreProdotti;
    PNodoListaProdotti listaProdottiBassaDisponibilita;
    Tprodotto p;
    int scelta;
    int dimensione = 3;
    char codiceProdotto[8];
    int pminimo;
    int dim;
    int n;
    do {
        scelta = Menu();

        switch (scelta) {
        case 1:
            // Invocare la funzione CaricaProdotti e visualizzare un messaggio
            //in caso di errore
            // e il numero di prodotti non corretti
            n = CaricaProdotti(NOME_FILE, vettoreListeProdotti);
            if (n == -1)
                printf("Errore durante l'operazione di caricamento dei dati.\n");
            else
                printf("Sono stati trovati %d prodotti non corretti.\n", n);
            // visualizzare i dati caricati nel vettore di prodotti
            for (int i = 0; i < dimensione; i++) 
            {
                printf("CATEGORIA: %s\n", VettoreCategorie[i]);
                stampaListaProdotti(vettoreListeProdotti[i]);
                printf("\n");
            }
            break;

        case 2:
            // Acquisire il numero minimo prodotti venduto
            printf("\ninserisci il numero di prodotto minimo  ");
            scanf("%d", &pminimo);
            //invocare la funzione QuantitaProdotti
            vettoreProdotti = QuantitaProdotti(vettoreListeProdotti, pminimo, &dim);
            // stampa vettoreProdotti
            if (vettoreProdotti != NULL) 
            {
                printf("Risultato:\n");
                for (int i = 0; i < dim; i++)
                {
                    printf("%s %s %d\n", vettoreProdotti[i].codice, vettoreProdotti[i].descrizione, vettoreProdotti[i].quantita);
                }
            }
            break;

        case 3:
            //// Acquisire il  codice prodotto da
            printf("\ninserisci il docide del  prodotto   ");
            scanf("%s", codiceProdotto);

            //invocare la funzione Vendita_prodotto
            Vendita_prodotto(vettoreListeProdotti, codiceProdotto);
            //stampare il vettore dei prodotti
            for (int i = 0; i < dimensione; i++) {
                stampaListaProdotti(vettoreListeProdotti[i]);
                printf("\n");
            }
            break;
        }

    } while (scelta != 0);

    // Disallocare il vettore dei prodotti;
    DisallocaVettoreListaProdotti(vettoreListeProdotti, dimensione);

    return 0;
}
