/*  ESERCIZIO 1  - Fondamenti di Informatica - Appello del 20/09/2024
    Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare quello
    esistente tranne quando espressamente richiesto.
    L'esercizio si considera corretto se il programma compila correttamente ed esegue senza errori
    run-time dando i risultati attesi.
    Consegnare esclusivamente il file sorgente .c rinominandolo: CognomeNome_1.c
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 10


/* LeggiDati
    La funzione LeggiDati deve acquisire un vettore di numeri interi fino all'inserimento del valore 0
    o al raggiungimento del numero massimo di elementi n.
    La funzione restituisce il numero dei valori effettivamente letti
*/
int LeggiDati(int v[], int dim) 
{
    // DA IMPLEMENTARE
    int i;
    for (i = 0; i < dim; i++) 
    {
        printf("Inserisci il valore %d: ", i);
        scanf("%d", &v[i]);
        if (v[i] == 0)
            return i;
    }
    return i;
}

/* ControllaMaggiore
* La funzione ControllaMaggiore accetta in ingresso un vettore di interi v di dimensione dim, ed un valore soglia.
* Essa deve generare e restituire un vettore di interi in cui ogni l'elemento i-esimo dovrà essere:
- pari a 1 se l'elemento v[i] è maggiore di soglia
- pari a -1 se l'elemento v[i] è minore di soglia
- pari a 0 se l'elemento v[i] è uguale a soglia
*/

int* ControllaMaggiore(int v[], int dim, int soglia) 
{
    // DA IMPLEMENTARE
    int* vout = (int*)malloc(sizeof(int) * dim);
    if (vout == NULL)
        return NULL;
    int index = 0;
    for (int i = 0; i < dim; i++) 
    {
        if (v[i] > soglia)
        {
            vout[index++] = 1;
        }
        else if (v[i] < soglia)
            vout[index++] = -1;
        else
            vout[index++] = 0;
    }
    return vout;
}


/* StampaVettore
    La funzione StampaVettore stampa il contenuto di un vettore di interi di una prefissata dimensione
*/
void StampaVettore(int v[], int dim) {
    // DA IMPLEMENTARE
    printf("---------------------------\n");
    printf("Vettore risultato: ");
    for (int i = 0; i < dim; i++) 
    {
        printf("%4d", v[i]);
    }
}


/***** MAIN *****/
int main(void) {
    int vett[N];
    int x;

    int* result;
    int dim;

    /*
       Acquisire il vettore vett usando la funzione LeggiDati e visualizzarlo
    */
    dim = LeggiDati(vett, N);
    StampaVettore(vett, dim);

    /*
        Inserire un valore soglia x
        Generare il vettore result richiamando la funzione ControllaMaggiore e visualizzarlo
    */
    printf("\nInserisci un valore soglia: ");
    scanf("%d", &x);
    result = ControllaMaggiore(vett, dim, x);
    StampaVettore(result, dim);

    return 0;
}
