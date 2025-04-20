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

/* 
La funzione ContaMaggiori riceve come parametro un vettore 'vett' e la sua dimensione 'dim' e restituisce un vettore di dimensione 'dim' in cui il generico elemento di posione 'i' rappresenta il numero di elementi in 'vett' che sono strettamente maggiori di vett[i]. 

Esempio
vett = {5, 3, 1, 4, 2} 
La funzione restituirà il vettore {0, 2, 4, 1, 3}
*/
int* ContaMaggiori(int* vett, int dim)
{
    // Implementare il corpo della funzione
}


/*
  La funzione VisualizzaArray visualizza il contenuto di un vettore
  di int di dim elementi
 */
void VisualizzaArray(int* vettore, int dim)
{
  // Implementare il corpo della funzione
}

int main(void)
{
  int* ingresso;    // array dei valori di input
  int* uscita;      // array dei valori di uscita
  int  n;           // dimensione dell'array
  
  printf("Inserire il numero di elementi dell'array input: ");
  // Acquisire la dimensione dell'array nella variabile 'n'

  ingresso = AcquisisciArray(n);
  if (ingresso ==  NULL) return 0;

  // Invocare la funzione AcquisisciArray e verificare se l'array è
  // stato allocato

  // Invocare la funzione ContaMaggiori

  // Visualizzare il vettore restituito dalla funzione ContaMaggiori

  // Disallocare la memoria allocata
  
  return 0;
}
