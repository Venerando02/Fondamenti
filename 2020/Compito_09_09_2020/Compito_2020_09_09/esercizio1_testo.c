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
    for (int i=0; i<n; i++)
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
}


/*
  La funzione VisualizzaVettore visualizza tutti gli elementi di un
  vettore di interi passato come parametro.
 */
void VisualizzaVettore(/* definire i parametri formali */)
{
  //  ...implementare la funzione...
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

  
  /* 
     Allocare il vettore 'vettore' della dimensione acquisita al punto precedente
  */
  // ...istruzioni...

  
  /* 
     Invocare la funzione AcquisisciVettore per acquisire i valori di vettore
  */
  // ... = AcquisisciVettore(...);


  /*
    Acquisire un numero strettamente maggiore di zero e memorizzarlo
    nella variabile 'espansione'
   */
  // ...istruzioni...


  /*
    Invocare la funzione Espandi in cui il parametro formale 'n' è rappresentato dalla variabile 'espansione'
  */
  // vettore_espanso = Espandi(...);


  /*
    Visualizzare il contenuto del vettore 'vettore_espanso'
   */
  // VisualizzaVettore(...);

  
  /*
    Disallocare i vettori 'vettore' e 'vettore_espanso'
  */
  // ...istruzioni...
  
  return 0;
}
