/*
  Compito del 15/05/2023
  Scaricare l'esercizio e completarlo inserendo il codice necessario
  senza modificare quello esistente tranne quando espressamente
  richiesto.
  
  L'esercizio si considera corretto se il programma compila
  correttamente ed esegue senza errori run-time dando i risultati
  attesi.

*/
/*
COGNOME: 
NOME:
MATRICOLA:
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/*
  La funzione AcquisisciArray deve allocare un array di dim elementi double positivi e
  acquisisce i valori reali che verranno inseriti nell'array
  La funzione deve accertarsi che i valori inseriti siano positivi
 */
double* AcquisisciArray(int dim) {
// DA IMPLEMENTARE A CURA DELLO STUDENTE
}

/* La funzione MinoriMedia ha come parametro in ingresso un vettore v di double.
Essa calcola e restituisce un vettore in cui vengono inseriti gli elementi del vettore v che sono strettamente inferiori alla media.
La funzione restituisce anche il numero di tali elementi (nminori)
*/
  
double* MinoriMedia(double *v, int dim, int *nminori){
    // DA IMPLEMENTARE A CURA DELLO STUDENTE
}


/*
  La funzione VisualizzaArray visualizza il contenuto di un vettore
  di double di dim elementi
 */
void VisualizzaArray(double vettore[], int dim) {

  for (int i=0; i<dim; i++)
    printf("%lf \n", vettore[i]);

  printf("\n");
}

int main(void)
{
  double* v;            // array dei valori acquisiti
  double* v_minori; 	// array dei valori inferiori alla media
  int dim;        		// dimensione dell'array dei valori acquisiti
  int nmin; 	        // numero di elementi minori della media
    
// acquisire la dimensione del vettore 

// chiamare la funzione AcquisisciArray  

// chiamare la funzione MinoriMedia

// visualizzare gli elementi del vettore restituito al punto precedente

// deallocare la memoria dei due vettori

  return 0;
}
