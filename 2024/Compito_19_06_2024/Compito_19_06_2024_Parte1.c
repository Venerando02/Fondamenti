/*
    Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare quello
    esistente tranne quando espressamente richiesto.
    L'esercizio si considera corretto se il programma compila correttamente ed esegue senza errori
    run-time dando i risultati attesi.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 5

/* AcquisisciVettore
   Acquisisce un vettore di float. La funzione legge due numeri interi
   e inserisce nel vettore la media dei due valori
*/
void AcquisisciVettore(float* v, int n)
{
    //da completate
    int Num1, Num2;
    for (int i = 0; i < n; i++) 
    {
        printf("Inserisci valore 1: ");
        scanf("%d", &Num1);
        printf("Inserisci valore 2: ");
        scanf("%d", &Num2);
        v[i] = ((Num1 + Num2) / 2.0);
    }
}

/* CreaVettori
La funzione prende in ingresso un vettore di float e restituisce
due vettori di float uno che contiene i valori positivi e uno che contiene
i valori negativi. Eventuali 0 vengono tralasciati.
*/
void DividiVettore(float v1[], int dim, float * positivi[], float * negativi[], int * dimpos, int * dimneg)
{
    /*da completare*/
    int DimPositivi = 0;
    int DimNegativi = 0;
    for (int i = 0; i < dim; i++) 
    {
        if (v1[i] > 0) 
        {
            DimPositivi++;
        }
        else if (v1[i] < 0) 
        {
            DimNegativi++;
        }
    }
    if (DimPositivi != 0) 
    {
        (*positivi) = (int*)malloc(sizeof(int) * DimPositivi);
    }
    else
    {
        (*positivi) = NULL;
    }
    if (DimNegativi != 0) 
    {
        (*negativi) = (int*)malloc(sizeof(int) * DimNegativi);
    }
    else 
    {
        (*negativi) = NULL;
    }
    (*dimpos) = DimPositivi;
    (*dimneg) = DimNegativi;
    int j, k;
    j = 0;
    k = 0;
    for (int i = 0; i < dim; i++)
    {
        if (v1[i] > 0)
        {
            (*positivi)[j++] = v1[i];
        }
        else if (v1[i] < 0)
        {
            (*negativi)[k++] = v1[i];
        }
    }
    return;
}


/* La funzione restituisce un float contenente il minimo
di un vettore di float */
float CalcolaMinimo(float* v, int n) 
{
    //da completare
    int pos = 0;
    for (int i = 0; i < n; i++) 
    {
        if (v[i] < v[pos])
            pos = i;
    }
    return v[pos];
}

/*la funzione StampaVettore stampa il contenuto di un vettore di interi di
una prefissata dimensione*/
void StampaVettore(float v[], int n) {
    for (int i = 0; i < n; i++)
        printf("%f\n", v[i]);
}

int main(void) {
    float  vett[N];
    float* positivi, * negativi;
    int  dim = N;
    int dimpos;
    int dimneg;


    /*
      Caricare i dati nel vettore  di float  'vett'

      chiamando la funzione AcquisisciVettore.
      Quindi stampare il vettore
    */
    AcquisisciVettore(vett, N);
    StampaVettore(vett, N);
    /*
    Generare i vettoro dei numeri positivi e dei numeri negativi
    continenuti in vett  utilizzando la
    funzione DividiVettore e stampare i due vettori
    */

    //chiama la funzioen DividiVettore
    DividiVettore(vett, N, &positivi, &negativi, &dimpos, &dimneg);
    
    if (dimpos != 0)
    {
        printf("\nVettore positivi:\n");
        StampaVettore(positivi, dimpos);
    }
    else
        printf("Non ci sono valori positivi nel vettore iniziale.\n");
    if (dimneg != 0) 
    {
        printf("\nVettore negativi:\n");
        StampaVettore(negativi, dimneg);
    }
    else
        printf("Non ci sono valori negativi nel vettore iniziale.\n");
    /*
    Invocare la funzione CalcolaMinimo e quindi visualizzare
    il valore minimo dei due vettori (positivi e negativi)
    */
    if((dimpos != 0) && (dimneg != 0))
        printf("Il minimo per i positivi e' %.3f, per i negativi e' %.3f.\n", CalcolaMinimo(positivi, dimpos), CalcolaMinimo(negativi, dimneg));
    else if ((dimpos == 0) && (dimneg != 0))
        printf("Il minimo per i negativi e' %.3f.\n", CalcolaMinimo(negativi, dimneg));
    else if ((dimpos != 0) && (dimneg == 0))
        printf("Il minimo per i positivi e' %.3f.\n", CalcolaMinimo(positivi, dimpos));
    /* Disallocate la memoria allocata */
    free(positivi);
    free(negativi);
    return 0;
}
