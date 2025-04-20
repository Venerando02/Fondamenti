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


/*
    La funzione AcquisisciVettore legge una sequenza di numeri interi
    positivi terminata dal valore 0 caricandoli in un vettore
    precedentemente allocato le cui dimensioni massime sono passate
    come parametro. La funzione restituisce il numero di valori
    effettivamente letti
 */
int AcquisisciVettore(int* v, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Inserisci elemento di posizione %d (0 per finire): ", (i + 1));
        scanf("%d", &v[i]);
        if (v[i] == 0)
            return i;
    }
    return n;
}


/*
  La funzione Espandi dato un vettore 'v', la sua dimensione
  'dimensione_in' ed un numero intero positivo 'n', alloca e
  restituisce un vettore contenente gli elementi di 'v' ognuno dei
  quali ripetuto 'n' volte. Restituisce altresì in 'dimensione_out' la
  dimensione di tale vettore.
 */
int* Espandi(int* v, int dimensione_in, int n, int* dimensione_out)
{
    //  ...implementare la funzione...
    (*dimensione_out) = dimensione_in * n;
    int* vout = (int*)malloc(sizeof(int) * (*dimensione_out));
    if (vout == NULL)
        return NULL;
    int index = 0;
    for (int i = 0; i < dimensione_in; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            vout[index++] = v[i];
        }
    }
    return vout;
}


/*
  La funzione VisualizzaVettore visualizza tutti gli elementi di un
  vettore di interi passato come parametro.
 */
void VisualizzaVettore(int v[], int dim)
{
    //  ...implementare la funzione...
    printf("Vettore:");
    for (int i = 0; i < dim; i++) 
    {
        printf("%5d", v[i]);
    }
}


int main(void)
{
    int* vettore;
    int* vettore_espanso;
    int  dimensione, dimensione_espanso, espansione;

    /*
      Acquisire la dimensione del vettore e verificare che sia un numero
      positivo
    */
    // ...istruzioni...
    do 
    {
        printf("Inserisci la dimensione del vettore: ");
        scanf("%d", &dimensione);
    } while (dimensione <= 0);

    /*
       Allocare il vettore 'vettore' della dimensione acquisita al punto precedente
    */
    // ...istruzioni...

    vettore = (int*)malloc(sizeof(int) * dimensione);
    if (vettore == NULL)
        return 0;

    /*
       Invocare la funzione AcquisisciVettore per acquisire i valori di vettore
    */
    // ... = AcquisisciVettore(...);
    int n;
    n = AcquisisciVettore(vettore, dimensione);

    /*
      Acquisire un numero strettamente maggiore di zero e memorizzarlo
      nella variabile 'espansione'
     */
     // ...istruzioni...
    printf("Inserisci di quanto vuoi espandere il vettore: ");
    scanf("%d", &espansione);

     /*
       Invocare la funzione Espandi in cui il parametro formale 'n' è rappresentato dalla variabile 'espansione'
     */
     // vettore_espanso = Espandi(...);

    vettore_espanso = Espandi(vettore, dimensione, espansione, &dimensione_espanso);

     /*
       Visualizzare il contenuto del vettore 'vettore_espanso'
      */
      // VisualizzaVettore(...);
    VisualizzaVettore(vettore_espanso, dimensione_espanso);

      /*
        Disallocare i vettori 'vettore' e 'vettore_espanso'
      */
      // ...istruzioni...
    free(vettore);
    free(vettore_espanso);
    return 0;
}
