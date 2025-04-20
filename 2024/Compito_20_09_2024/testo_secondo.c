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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE  "prodotti.txt"

typedef struct prodotti {
    char codice[8];
    char descrizione[15];
    int quantita;
} Tprodotto;

typedef struct NodoListaProdotto {
    Tprodotto prodotto;
    struct NodoListaProdotto *next;
} TNodoListaProdotti, *PNodoListaProdotti;


/* AggiungiProdottoInTesta inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiProdottoInTesta(PNodoListaProdotti *prodotti, Tprodotto prodotto) {
    PNodoListaProdotti aux;
    aux = (PNodoListaProdotti) malloc(sizeof(TNodoListaProdotti));
    if (aux == 0) return 0;
    aux->prodotto = prodotto;
    aux->next = *prodotti;
    *prodotti = aux;
    return 1;
}

/* AggiungiProdottoOrdinato inserisce un elemento nella lista in modo
   ordinato rispetto alla quantita
   Restituisce 1 se l'operazione va a buon fine, 0 altrimenti */
int AggiungiProdottoOrdinato(PNodoListaProdotti *PListaprodotti, Tprodotto prodotto) {
    //DA IMPLEMENTARE
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

PNodoListaProdotti cercaProdotto(PNodoListaProdotti L, char *codiceProdotto) {
    while (L) {
        if (strcmp(L->prodotto.codice, codiceProdotto) == 0) return L;
        L = L->next;
    }
    return NULL;
}

int CaricaProdotti(char *nome_file, PNodoListaProdotti *vettoreProdotti) {
    Tprodotto p;
    FILE *f;
    int n = 0;
    //DA COMPLETARE
}


/*   2.Restituisce in un vettore l'elenco dei prodotti la cui quantita venduta e maggiore di un valore 
passato come parametro
    Parametri di ingresso: vettore di liste, codice prodotto, prodotto quantita
    Parametro di uscita: dimensione vettore di prodotti
    Valore restituito: Vettore prodotti
*/

Tprodotto *QuantitaProdotti(/*DA COMPLETARE*/) {
    //DA COMPLETARE

}

/*   3. Dato un codice prodotto e un numero intero procede alla vendita del prodotto.
Se il prodotto è disponibile decrementa la quantità del prodotto nella lista dei disponibili e incrementa il prodotto nella
lista dei venduti aggiungendolo se non presente
Se il prodotto non è disponibile ed è nella lista dei prodotti ordinati modifica la quantità del prodotto
Se il prodotto non è disponibile e non è nella lista dei prodotti ordinati inserisce il prodotto nella lista dei prodotti
a de-ordinati.
    Parametri di ingresso: vettore di liste, codice prodotto, prodotto quantità
    Valore restituito: void

*/


void Vendita_prodotto(PNodoListaProdotti *vettoreProdotti, char *codiceProdotto) {
    //DA implementare
}



//funzioni di utilita

void stampaVettoreProdotti(Tprodotto *vettoreProdotti, int dimensione) {
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

void DisallocaListaProdotti(PNodoListaProdotti *lista) {
    PNodoListaProdotti p;

    while (*lista != NULL) {
        p = *lista;
        *lista = (*lista)->next;
        free(p);
    }
}

void DisallocaVettoreListaProdotti(PNodoListaProdotti *vet, int dimensione) {
    //DA COMPLETARE
}

int main(void) {
    PNodoListaProdotti vettoreListeProdotti[3];
    Tprodotto *vettoreProdotti;
    PNodoListaProdotti listaProdottiBassaDisponibilita;
    Tprodotto p;
    int scelta;
    int dimensione = 3;
    char codiceProdotto[8];
    int pminimo;
    int dim;

    do {
        scelta = Menu();

        switch (scelta) {
            case 1:
                // Invocare la funzione CaricaProdotti e visualizzare un messaggio
                //in caso di errore
                // e il numero di prodotti non corretti

                // visualizzare i dati caricati nel vettore di prodotti

                break;

            case 2:
                // Acquisire il numero minimo prodotti venduto
                printf("\ninserisci il numero di prodotto minimo  ");
                scanf("%d", &pminimo);

                //invocare la funzione QuantitaProdotti

                // stampa vettoreProdotti

                break;

            case 3:
                //// Acquisire il  codice prodotto da
                printf("\ninserisci il docide del  prodotto   ");
                scanf("%s", codiceProdotto);

                //invocare la funzione Vendita_prodotto

                //stampare il vettore dei prodotti

                break;
        }

    } while (scelta != 0);

    // Disallocare il vettore dei prodotti;


    return 0;
}
