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
COGNOME: Musumeci
NOME: Venerando Pio
MATRICOLA: 1000015141
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/*
  La funzione AcquisisciArray deve allocare un array di dim elementi double positivi e
  acquisisce i valori reali che verranno inseriti nell'array
  La funzione deve accertarsi che i valori inseriti siano positivi
 */
double* AcquisisciArray(int dim) 
{
    // DA IMPLEMENTARE A CURA DELLO STUDENTE
    double* v = malloc(sizeof(double) * dim);
    int i = 0;
    while (i < dim) 
    {
        printf("Inserisci il valore %d: ", i);
        scanf("%lf", &v[i]);
        if (v[i] >= 0) 
        {
            i++;
        }
    }
    return v;
}

/* La funzione MinoriMedia ha come parametro in ingresso un vettore v di double.
Essa calcola e restituisce un vettore in cui vengono inseriti gli elementi del vettore v che sono strettamente inferiori alla media.
La funzione restituisce anche il numero di tali elementi (nminori)
*/

double* MinoriMedia(double* v, int dim, int* nminori) 
{
    // DA IMPLEMENTARE A CURA DELLO STUDENTE
    double somma = 0;
    int i;
    for (i = 0; i < dim; i++) 
    {
        somma += v[i];
    }
    double media = (double)(somma) / (double)(i);
    (*nminori) = 0;
    for (i = 0; i < dim; i++) 
    {
        if (v[i] < media)
            (*nminori)++;
    }
    double* vout = malloc(sizeof(double) * (*nminori));
    int index = 0;
    for (i = 0; i < dim; i++)
    {
        if (v[i] < media)
            vout[index++] = v[i];
    }
    return vout;
}


/*
  La funzione VisualizzaArray visualizza il contenuto di un vettore
  di double di dim elementi
 */
void VisualizzaArray(double vettore[], int dim) {

    for (int i = 0; i < dim; i++)
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
    do {
        printf("Inserisci la dimensione del vettore: ");
        scanf("%d", &dim);
    } while (dim < 0);
    // chiamare la funzione AcquisisciArray  
     v = AcquisisciArray(dim);
    // chiamare la funzione MinoriMedia
     v_minori = MinoriMedia(v, dim, &nmin);
    // visualizzare gli elementi del vettore restituito al punto precedente
     printf("\nRisultato:\n");
     VisualizzaArray(v_minori, nmin);
    // deallocare la memoria dei due vettori
     free(v);
     free(v_minori);
    return 0;
}
