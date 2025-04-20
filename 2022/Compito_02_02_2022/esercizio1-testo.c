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
float* AcquisisciArray(int dim)
{
  float* vettore;

  vettore = (float*)malloc(dim * sizeof(float));

  if (vettore != NULL)
    {
      for (int i=0; i<dim; i++) {
	printf("Inserisci l'elemento %d: ", i);
	scanf("%f", &vettore[i]);
      }
    }
  
  return vettore;
}

/* 
La funzione MediaMobile effettua la media mobile semplice (MMS) di ordine 'o'. La funzione ha come parametri un vettore 'vett', la sua dimensione 'dim', e l'ordine della media mobile semplice 'o'. Restituisce in uscita un vettore contenente la MMS. L'elemento i-esimo del vettore MMS si è la media degli elementi di vett di posizione i, i-1, i-2, ..., i-o+1. Gli indici negativi non vanno considerati nel calcolo della MMS. 

Esempio:
vett = {2, 3, 5, 4, 8, 2}
k = 3
mms = {2, (3+2)/2, (5+3+2)/3, (4+5+3)/3, (8+4+5)/3, (2+8+4)/3}
*/
float* MediaMobile(float* vett, int dim, int o)
{
  // Implementare il corpo della funzione
}


/*
  La funzione VisualizzaArray visualizza il contenuto di un vettore
  di float di dim elementi
 */
void VisualizzaArray(float* vettore, int dim)
{
  // Implementare il corpo della funzione
}

int main(void)
{
  float* ingresso;    // array dei valori di input
  float* uscita;      // array dei valori di uscita
  int    n, ordine;
  
  printf("Inserire il numero di elementi dell'array input: ");
  // Acquisire la dimensione dell'array nella variabile 'n'
  
  // Invocare la funzione AcquisisciArray e verificare se l'array è
  // stato allocato

  printf("Ordine della media mobile? ");
  // Acquisire l'ordine nella variabile 'ordine'

  // Invocare la funzione MediaMobile

  // Visualizzare il vettore contenente la media mobile

  // Disallocare la memoria allocata
  
  return 0;
}
