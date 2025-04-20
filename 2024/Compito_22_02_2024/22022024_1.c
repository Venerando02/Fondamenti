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
int AcquisisciVettore(int v[], int n, int soglia)
{
    //funzione da implementare da parte dello studente    
    int i = 0;
    while (i < n)
    {
        printf("Inserisci il valore %d: ", i);
        scanf("%d", &v[i]);
        if (v[i] > soglia)
            i++;
    }
    return i;
}

/* DividiVettore
La funzione DividiVettore accetta come parametro di ingresso un vettore V di interi di dimensione n.
Essa deve generare e restituire, utilizzando i parametri della funzione, due vettori V3 e V5 che
contengoo rispettivamente i valori d V che sono multipli di 3 e di 5.
La funzione restituisce, sempre utilizzando i parametri, la dimensione dei due vettori N3 e N5.
Attenzione: un intero puo essere contemporaneamente multiplo di 3 e multiplo di 5
*/

void DividiVettore(int* V, int n, int* V3[], int* V5[], int* N3, int* N5)
{
    // funzione da implementare da parte dello studente
    (*N3) = 0;
    (*N5) = 0;
    int dim3 = 0;
    int dim5 = 0;
    for (int i = 0; i < n; i++) 
    {
        if (V[i] % 3 == 0) 
        {
            dim3++;
        }
        if (V[i] % 5 == 0) 
        {
            dim5++;
        }
    }
    (*V3) = (int*)malloc(sizeof(int) * dim3);
    (*V5) = (int*)malloc(sizeof(int) * dim5);
    for (int i = 0; i < n; i++)
    {
        if (V[i] % 3 == 0)
        {
            (*V3)[(*N3)++] = V[i];
        }
        if (V[i] % 5 == 0)
        {
            (*V5)[(*N5)++] = V[i];
        }
    }
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
    int* vettore3;
    int dim3;
    int* vettore5;
    int dim5;
    int soglia = 0;
    int somma = 0;

    /*
      Acquisire un valore soglia maggiore di 0*/
    do {
        printf("Inserire il valore che limita inferiormente i valori da leggere e inserire nel vettore (deve essere positivo)\n");
        scanf("%d", &soglia);
    } while (soglia <= 0);

    /*
    Acquisire vettore  usando la funzione AcquisisciVettore
    e visualizzare il vettore inserito
    */
    AcquisisciVettore(vettore, dim, soglia);
    StampaVettore(vettore, dim);

    /*
    Generare i vettore contenente i multipli di 3 e 5 presenti in vettore utilizzando la
    funzione dividiVettore  */
    DividiVettore(vettore, dim, &vettore3, &vettore5, &dim3, &dim5);

    //stampare i due vettori 
    printf("\n-------------------\n");
    StampaVettore(vettore3, dim3);
    printf("\n-------------------\n");
    StampaVettore(vettore5, dim5);
    //calcolare la media dei multipli di 3
    int Somma = 0;
    for (int i = 0; i < dim3; i++) 
    {
        Somma += vettore3[i];
    }
    float Media = (float)(Somma) / (dim3);
    printf("La media dei multipli di 3 e' %.2f.\n", Media);
    /* Disallocate la memoria heap allocata */
    free(vettore3);
    free(vettore5);
    return 0;
}
