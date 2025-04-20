/*
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
  La funzione AcquisisciArray deve allocare un array di dim elementi interi e
  acquisisce i valori int che verranno inseriti nell'array
 */
int* AcquisisciArray(int dim) {

    // Sviluppare il corpo della funzione

}

/* La funzione RaddoppiaConSoglia raddoppia gli elementi di v assicurandosi
    però di non superare il valore soglia.
   Cioè, restituisce un array della stessa dimensione di v in cui ogni
   elemento è il doppio del corrispondente elemento di v. Se il valore
   supera soglia, allora il valore è posto uguale a soglia.
   La funzione restituisce inoltre il numero di volte in cui si è superato
   il valore soglia (nsuperamenti)
   (nsaturazioni) */
int* RaddoppiaConSoglia(int* v, int dim, int soglia, int* nsuperamenti) {
   
    // Sviluppare il corpo della funzione

}


/*
  La funzione VisualizzaArray visualizza il contenuto di un vettore
  di int di dim elementi
 */
void VisualizzaArray(int* vettore, int dim)
{
    if (vettore == NULL) return;

    for (int i = 0; i < dim; i++)
        printf("%d, ", vettore[i]);

    printf("\n");
}

int main(void)
{
    int* vettore;             // array dei valori acquisiti
    int* vettore_raddoppiato; // array dei valori raddoppiati
    int dim;          // dimensione dell'array dei valori acquisiti
    int soglia;
    int nsup; // numero di volte che è avvenuta il superamento della soglia


    printf("Inserire la dimensione del vettore: ");
    scanf("%d", &dim);

    // Invocare la funzione AcquisisciArray

    printf("Inserire il valore soglia: ");
    scanf("%d", &soglia);

    // Invocare la funzione RaddoppiaConSoglia con gli opportuni parametri

    printf("Numero di volte in cui si è superata la soglia: %d \n", /* inserire la variabile opportuna */);

    printf("Vettore con elementi raddoppiati\n");
    // Invocare la funzione VisualizzaArray

  // Disallocare tutta la memoria allocata

    return 0;
}
