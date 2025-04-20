/*
    FONDAMENTI DI INFORMATICA - Esercizio 1
	Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare quello esistente 
    tranne quando espressamente richiesto.
    L'esercizio si considera corretto se il programma compila correttamente ed esegue senza errori 
    a run-time dando i risultati attesi.

    Consegnare esclusivamente il file sorgente .c rinominandolo: CognomeNome_1.c
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define N 20

/* AcquisisciVettore
   Acquisisce un vettore di interi di dimensione n inserendo in questo vettore solo valori maggiori del 
   valore intero soglia passato come parametro. Gli eventuali valori inseriti minori o uguali alla soglia 
   devono essere tralasciati 
*/
int AcquisisciVettore(int v[], int n, int soglia) {
    //funzione da implementare da parte dello studente    
}

/* DividiVettore
La funzione DividiVettore accetta come parametro di ingresso un vettore V di interi di dimensione n.
Essa deve generare e restituire, utilizzando i parametri della funzione, due vettori V3 e V5 che 
contengoo rispettivamente i valori d V che sono multipli di 3 e di 5. 
La funzione restituisce, sempre utilizzando i parametri, la dimensione dei due vettori N3 e N5.
Attenzione: un intero puo essere contemporaneamente multiplo di 3 e multiplo di 5
*/

void DividiVettore(int *V, int n, int *V3[], int *V5[], int *N3, int *N5) {

// funzione da implementare da parte dello studente

    return;
}


/*
la funzione StampaVettore stampa il contenuto di un vettore di interi di
una prefissata dimensione
 */
void StampaVettore(int v[], int dim) {
    for (int i = 0; i < dim; i++)
        printf("%d  ", v[i]);
    printf("\n");
}

/****** main ******/
int main(void) {

    int vettore[N];
    int dim = N;
    int *vettore3;
    int dim3;
    int *vettore5;
    int dim5;
    int soglia = 0;
    int somma = 0;

    /*
      Acquisire un valore soglia maggiore di 0*/
    do {
        printf("Inserire il valore che limita inferiormente i valori da leggere e inserire nel vettore (deve essere positivo)/n");
        scanf("%d", &soglia);
    } while (soglia <= 0);

    /* 
	Acquisire vettore  usando la funzione AcquisisciVettore 
	e visualizzare il vettore inserito 
	*/
    AcquisisciVettore(/*inserire i parametri*/);
    StampaVettore(/*inserire i parametri*/);

    /*
	Generare i vettore contenente i multipli di 3 e 5 presenti in vettore utilizzando la
    funzione dividiVettore  */
    DividiVettore(/*inserire i parametri*/)

    //stampare i due vettori 

    //calcolare la media dei multipli di 3

    /* Disallocate la memoria heap allocata */


    return 0;
}
