/*  ESERCIZIO 1  - Fondamenti di Informatica - Appello del 15/07/2024
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
int LeggiDati(int v[], int n) {
    // DA IMPLEMENTARE
}


/* UnisciVettori
* La funzione UnisciVettori, accetta in ingresso due vettori di interi v1 e v2 di dimensione rispettivamente dim1 e dim2.
* Essa deve fondere i due vettori in un terzo vettore alternando gli elementi di v1 e v2; ossia inserendo gli elementi 
* di v1 in posizione pari e di v2 in posizione dispari. Se uno dei due vettori termina prima, gli elementi dell'altro
* vanno comunque accodati nel nuovo vettore creato.
*/

int* UnisciVettori(int v1[], int dim1, int v2[], int dim2, int* dim3) {
    // DA IMPLEMENTARE

}


/* StampaVettore
    La funzione StampaVettore stampa il contenuto di un vettore di interi di una prefissata dimensione
*/
void StampaVettore(int v[], int dim){
    for (int i = 0; i < dim; i++)
        printf("%d\n",v[i]);
}


/***** MAIN *****/
int main(void) {
    int va[N];
    int vb[N];

    int* vc;
    int dim_a, dim_b, dim_c;


/*
   Acquisire il primo vettore va usando la funzione LeggiDati
   e visualizzare il vettore inserito
*/


/*
   Acquisire il secondo vettore vb usando la funzione LeggiDati
   e visualizzare il vettore inserito
*/



/*
Generare il terzo vettore vc richiamando la funzione UnisciVettori 
(a cui vanno passati i due vettori va e vb) e visualizzarlo
*/


/* Disallocate la memoria allocata */

    return 0;
}
