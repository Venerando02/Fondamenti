/*
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
  La funzione AcquisisciArray deve allocare un array di dim elementi interi e
  acquisisce i valori int che verranno inseriti nell'array
 */
int* AcquisisciArray(int dim) 
{
    // Sviluppare il corpo della funzione
    int* v = malloc(sizeof(int) * dim);
    for (int i = 0; i < dim; i++) 
    {
        printf("Inserisci il valore %d: ", i);
        scanf("%d", &v[i]);
    }
    return v;
}

/* La funzione RaddoppiaConSoglia raddoppia gli elementi di v assicurandosi
    però di non superare il valore soglia.
   Cioè, restituisce un array della stessa dimensione di v in cui ogni
   elemento è il doppio del corrispondente elemento di v. Se il valore
   supera soglia, allora il valore è posto uguale a soglia.
   La funzione restituisce inoltre il numero di volte in cui si è superato
   il valore soglia (nsuperamenti)
   (nsaturazioni) */
int* RaddoppiaConSoglia(int* v, int dim, int soglia, int* nsuperamenti) 
{
    // Sviluppare il corpo della funzione
    int* vout = malloc(sizeof(int) * dim);
    int valore = 0;
    *nsuperamenti = 0;
    for (int i = 0; i < dim; i++) 
    {
        valore = v[i] * 2;
        if (valore > soglia) 
        {
            (*nsuperamenti)++;
            valore = soglia;
            vout[i] = valore;
        }
        vout[i] = valore;
    }
    return vout;
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
    vettore = AcquisisciArray(dim);
    printf("Inserire il valore soglia: ");
    scanf("%d", &soglia);

    // Invocare la funzione RaddoppiaConSoglia con gli opportuni parametri
    vettore_raddoppiato = RaddoppiaConSoglia(vettore, dim, soglia, &nsup);
    printf("Numero di volte in cui si è superata la soglia: %d \n", nsup);

    printf("Vettore con elementi raddoppiati\n");
    // Invocare la funzione VisualizzaArray
    VisualizzaArray(vettore_raddoppiato, dim);
  // Disallocare tutta la memoria allocata
    free(vettore);
    free(vettore_raddoppiato);
    return 0;
}
