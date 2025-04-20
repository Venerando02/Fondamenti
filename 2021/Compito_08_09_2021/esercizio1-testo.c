/*
  Scaricare l'esercizio e completarlo inserendo il codice necessario
  senza modificare quello esistente tranne quando espressamente
  richiesto.
  
  L'esercizio si considera corretto se il programma compila
  correttamente ed esegue senza errori run-time dando i risultati
  attesi.

  Il file sorgente deve essere consegnato allegandolo a questa
  attivit�.
*/

#include <stdio.h>
#include <stdlib.h>

/*
  La funzione AcquisisciArray alloca un array di dim elementi e
  acquisisce i valori int che verranno inseriti nell'array
 */
int* AcquisisciArray(int dim)
{
  int* vettore;

  vettore = (int*)malloc(dim * sizeof(int));

  if (vettore != NULL)
    {
      for (int i=0; i<dim; i++) {
	printf("Inserisci l'elemento %d: ", i);
	scanf("%d", &vettore[i]);
      }
    }
  
  return vettore;
}

/* La funzione MassimiLocali restituisce un array contenente i massimi
   locali dell'array passato come parametro. Un massimo locale è un
   valore tale che i valori alla sua sinsistra ed alla sua destra sono
   inferiori. Si tralascino il primo e l'ultimo valore dell'array */
int* MassimiLocali(int* v, int dim_v, int* num_massimi_locali)
{
  // Sviluppare il corpo della funzione
  // ...
}


/*
  La funzione VisualizzaValori visualizza il contenuto di un vettore di int di dim elementi
 */
void VisualizzaValori(int* vettore, int dim)
{
  // Sviluppare il corpo della funzione
  // ...
}

int main(void)
{
  int* vettore;     // array dei valori acquisiti
  int *vettore_max; // array dei massimi locali
  int dim;          // dimensione dell'array dei valori acquisiti
  int n_max;        // dimensione dell'array dei massimi locali
    
  
  printf("Inserire la dimensione del vettore: ");
  scanf("%d", &dim); 

  // Invocare la funzione AcquisisciArray

  // Invocare la funzione MassimiLocali
  
  // Invocare la funzione VisualizzaValori

  // Disallocare la memoria allocata
  
  return 0;
}
