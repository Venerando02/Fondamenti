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
  La funzione AcquisisciArray alloca un array di dim
  elementi e acquisisce i valori int che verranno inseriti nell'array

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

/*
la funzione dividi suddivide il vettore in due vettori: uno contenente i valori positivi e uno i valori minori o uguali
a zero. La funzione restituisce la dimensione del vettore contenente i valori positivi.
Come parametro d'ingresso prende il vettore v e la sua dimensione dim da suddividere e restituisce 
i due vettori vPositivi e vNegativi */
int dividi(int v[], int** vPositivi, int** vNegativi, int dim) 
{
    // da sviluppare a cura dello studente
    (*vPositivi) = (int*)malloc(sizeof(int) * dim);
    (*vNegativi) = (int*)malloc(sizeof(int) * dim);
    int dimpos = 0;
    int dimneg = 0;
    for (int i = 0; i < dim; i++) 
    {
        if (v[i] > 0)
            (*vPositivi)[dimpos++] = v[i];
        else if (v[i] <= 0)
            (*vNegativi)[dimneg++] = v[i];
    }
    return dimpos;
}

/*
La funzione VisualizzaValori visualizza il contenuto di un vettore di int di dim elementi
*/
void VisualizzaValori(int* vettore, int dim) 
{
      //da sviluppare a cura dello studente
    printf("\n------------------------\n");
    for (int i = 0; i < dim; i++) 
    {
        printf("v[%d] = %d\n", i, vettore[i]);
    }
}

  int main(void)
  {
      int* vettore;
      int* vettorePos, * vetNegativi;
      int dim;
      int dimP, dimN;



      printf("Inserire la demensione del vettore: ");
      scanf("%d", &dim);

      // crea il vettore di dimensione dim utilizzando la funzione AcquisisciArray
      vettore = AcquisisciArray(dim);
      //stampa il vettore  utilizzando la funzione VisualizzaValori
      VisualizzaValori(vettore, dim);
      //crea i vettori vettorePos e vetNegativi invocando la funzione dividi
      dimP = dividi(vettore, &vettorePos, &vetNegativi, dim);
      dimN = dim - dimP;
      VisualizzaValori(vettorePos, dimP);
      VisualizzaValori(vetNegativi, dimN);

      //libera la memoria
      free(vettore);
      free(vettorePos);
      free(vetNegativi);
      return 0;
  }
