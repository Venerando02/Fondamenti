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

#define _CRT_SECURE_NO_WARNINGS
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
        for (int i = 0; i < dim; i++) {
            printf("Inserisci l'elemento %d: ", i);
            scanf("%d", &vettore[i]);
        }
    }

    return vettore;
}

/* La funzione Amplifica amplifica il segnale v di un fattore amp e
   satura al valore sat. Cioè, restituisce un array della stessa
   dimensione di v in cui ogni elemento è il prodotto del
   corrispondente elemento di v moltiplicato amp. Se il valore supera
   sat il valore è saturato a sat. La funzione restituisce inoltre il
   numero di volte in cui si è verificata una saturazione del segnale
   (nsaturazioni) */
int* Amplifica(int* v, int dim, int amp, int sat, int* nsaturazioni)
{
    // Sviluppare il corpo della funzione
    (*nsaturazioni) = 0;
    int* vout = malloc(sizeof(int) * dim);
    for (int i = 0; i < dim; i++) 
    {
        vout[i] = v[i] * amp;
        if ((v[i] * amp) >= sat)
        {
            vout[i] = sat;
            (*nsaturazioni)++;
        }
    }
    return vout;
}


/*
  La funzione VisualizzaArray visualizza il contenuto di un vettore
  di int di dim elementi
 */
void VisualizzaArray(int* vettore, int dim)
{
    // Sviluppare il corpo della funzione
    printf("---------RISULTATO---------\n");
    for (int i = 0; i < dim; i++)
        printf("v[%d] = %d\n", i, vettore[i]);
}

int main(void)
{
    int* vettore;     // array dei valori acquisiti
    int* vettore_amp; // array dei valori amplificati
    int dim;          // dimensione dell'array dei valori acquisiti
    int amplificazione, saturazione;
    int nsaturazioni; // numero di volte che è avvenuta la saturazione


    printf("Inserire la dimensione del vettore: ");
    scanf("%d", &dim);

    // Invocare la funzione AcquisisciArray
    vettore = AcquisisciArray(dim);
    printf("Inserire il fattore di amplificazione ed il valore di saturazione: ");
    scanf("%d %d", &amplificazione, &saturazione);

    // Invocare la funzione Amplifica
    vettore_amp = Amplifica(vettore, dim, amplificazione, saturazione, &nsaturazioni);
    printf("%d punti di saturazione\n", nsaturazioni);

    // Invocare la funzione VisualizzaArray
    VisualizzaArray(vettore_amp, dim);
    // Disallocare tutta la memoria allocata
    free(vettore);
    free(vettore_amp);
    return 0;
}
