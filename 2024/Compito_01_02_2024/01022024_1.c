/*
    Esercizio 1
    Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare quello esistente tranne quando espressamente richiesto.
    L'esercizio si considera corretto se il programma compila correttamente ed esegue senza errori a run-time dando i risultati attesi.

    Consegnare esclusivamente il file sorgente .c rinominandolo: CognomeNome_1.c
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* AcquisisciVettore
   Acquisisce un vettore di interi di dimensione n  */
void AcquisisciVettore(int v[], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        printf("Inserisci elemento di posizione %d: ", i);
        scanf("%d", &v[i]);
    }
}

/* CompattaVettore
La funzione CompattaVettore accetta come parametro di ingresso un vettore vi di interi.
Essa deve generare e restituire un secondo vettore w ottenuto compattando i numeri contenuti nel primo vettore. In particolare:
- ogni numero che compare ripetuto più volte nel primo vettore deve comparire una sola volta nel secondo vettore
- ogni numero uguale a zero presente nel primo vettore non deve comparire nel secondo vettore
*/

int* CompattaVettore(int v[], int dim, int* dimw) 
{
    // funzione da implementare da parte dello studente
    int* w = (int*)malloc(sizeof(int) * dim);
    if (w == NULL)
        return NULL;
    (*dimw) = 0;
    int trovato;
    for (int i = 0; i < dim; i++) 
    {
        if (v[i] != 0) 
        {
            trovato = 0;
            for (int j = 0; j < dim; j++) 
            {
                if (v[i] == w[j]) 
                {
                    trovato = 1;
                    break;
                }
            }
            if (trovato == 0) 
            {
                w[(*dimw)++] = v[i];
            }
        }
    }
    return w;
}


/*
la funzione StampaVettore stampa il contenuto di un vettore di interi di
una prefissata dimensione
 */
void StampaVettore(int v[], int dim)
{
    for (int i = 0; i < dim; i++)
        printf("%d  ", v[i]);
    printf("\n");
}

/****** main ******/
int main(void) {

    int* vett;
    int  dim;
    int* vettcompatto;
    int dimcompatto = 0;

    /*
      Acquisire la dimensione dim di un vettore ed assicurarsi che essa sia un numero positivo. 
      Quindi allocare un vettore 'vett' di interi di tale dimensione.
    */
    do 
    {
        printf("Inserisci la dimensione: ");
        scanf("%d", &dim);
    } while (dim <= 0);
    /*
    Acquisire il vettore vett usando la funzione AcquisisciVettore
    e visualizzare il vettore inserito
    */
    vett = (int*)malloc(sizeof(int) * dim);
    if (vett == NULL)
        return 0;
    AcquisisciVettore(vett, dim);
    StampaVettore(vett, dim);
    /*
    Generare il vettore compattato 'vettcompatto' utilizzando la
    funzione CompattaVettore e visualizzarlo */
    vettcompatto = CompattaVettore(vett, dim, &dimcompatto);
    StampaVettore(vettcompatto, dimcompatto);
    /* Disallocate la memoria allocata */
    free(vett);
    free(vettcompatto);
    return 0;
}
