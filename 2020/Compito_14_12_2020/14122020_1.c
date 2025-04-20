/*
  Scaricare l'esercizio e completarlo inserendo il codice necessario
  senza modificare quello esistente tranne quando espressamente
  richiesto.

  L'esercizio si considera corretto se il programma compila
  correttamente ed esegue senza errori run-time dando i risultati
  attesi.

  Il file sorgente deve essere consegnato allegandolo a questa
  attività.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Acqusisce un vettore di interi dimensione n */
void AcquisisciVettore(int* v, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Inserisci elemento di posizione %d: ", i);
        scanf("%d", &v[i]);
    }
}

/* Restituisce un vettore i cui elementi sono la ripetizione degli
   elementi di posizioni dispari di vett_comp un numero di volte pari
   agli elementi di posizione pari. Esempio, se vett_comp = {2, 3, 5,
   1, 3, 4} allora deve restituire {3, 3, 1, 1, 1, 1, 1, 4, 4, 4}.
   n è la dimensione di vett_comp e *dim la dimensione del vettore
   generato */
int* Espandi(int* vett_comp, int n, int* dim)
{
    // ...da implementare a cura dello studente...
    (*dim) = 0;
    for (int i = 0; i < n; i++) 
    {
        if (i % 2 == 0) 
        {
            (*dim) += vett_comp[i];
        }
    }
    int* vout = (int*)malloc(sizeof(int) * (*dim));
    if (vout == NULL)
        return NULL;
    int valore;
    int n_rip;
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            n_rip = vett_comp[i];
        }
        if (i % 2 != 0) 
        {
            valore = vett_comp[i];
            for (int j = 0; j < n_rip; j++) 
            {
                vout[index++] = valore;
            }
        }
    }
    return vout;
}

/* Visualizza il contenuto di un vettore di dimensione n */
void Visualizza(int v[], int dim)
{
    // ...da implementare a cura dello studente...
    printf("\n---------------\n");
    for (int i = 0; i < dim; i++) 
    {
        printf("v[%d] = %d\n", i, v[i]);
    }
}

int main(void)
{
    int* vett1;
    int* vett2;
    int  dim1, dim2;

    /*
      Acquisire la dimensione di un vettore ed assicurarsi che la
      dimensione sia un numero pari. Quindi allocare un vettore 'vett1'
      di interi di tale dimensione.
    */
    do {
        printf("Quanti elementi ha il vettore (deve essere un numero pari)? ");
        scanf("%d", &dim1);
    } while (dim1 % 2 != 0);

    // Allocare vett1 di dimensione dim1
    vett1 = (int*)malloc(sizeof(int) * dim1);
    if (vett1 == NULL)
        return 0;

    AcquisisciVettore(vett1, dim1);
    Visualizza(vett1, dim1);

    /* Generare il vett2 ripetendo gli elementi delle posizioni dispari
       di vett1 un numero di valte pari agli elementi di posizione
       pari. Esempio, se vett1 = {2, 3, 5, 1, 3, 4} allora
       vett2 = {3, 3, 1, 1, 1, 1, 1, 4, 4, 4}. */
    vett2 = Espandi(vett1, dim1, &dim2);

    /* Visualizzare vett2 */
    Visualizza(vett2, dim2);

    /* Disallocare la memoria allocata */
    // ...a cura dello dtudente...
    free(vett1);
    free(vett2);
    return 0;
}
