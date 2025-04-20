/*
    Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare quello
    esistente tranne quando espressamente richiesto.
    L'esercizio si considera corretto se il programma compila correttamente ed esegue senza errori
    run-time dando i risultati attesi.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 20

/* AcquisisciVettore
   Acquisisce un vettore di float. La funzione legge due numeri interi
   e inserisce nel vettore la media dei due valori
*/
void AcquisisciVettore(float* v, int n) 
{
    //da completate
    int i;
    int Numero1, Numero2;
    for (i = 0; i < n; i++)
    {
        printf("Inserisci il primo numero: ");
        scanf("%d", &Numero1);
        printf("Inserisci il secondo numero: ");
        scanf("%d", &Numero2);
        v[i] = ((float)(Numero1 + Numero2) / 2.0);
    }
}

/* CreaVettori
La funzione prende in ingresso un vettore di float e restituisce
due vettori di float uno che contiene i valori positivi e uno che contiene
i valori negativi. Eventuali 0 vengono tralasciati.
*/
void DividiVettore(float * VettoreIniziale, int dim, float ** Positivi, float ** Negativi, int * dimPos, int * dimNeg) 
{
    /*da completare*/
    (*dimPos) = 0;
    (*dimNeg) = 0;
    (*Positivi) = (int*)malloc(sizeof(int) * dim);
    (*Negativi) = (int*)malloc(sizeof(int) * dim);
    for (int i = 0; i < dim; i++) 
    {
        if (VettoreIniziale[i] > 0)
            (*Positivi)[(*dimPos)++] = VettoreIniziale[i];
        else if (VettoreIniziale[i] < 0)
            (*Negativi)[(*dimNeg)++] = VettoreIniziale[i];
    }
    return;
}


/* La funzione restituisce un float contenente il minimo
di un vettore di float */
float CalcolaMinimo(float* v, int n) 
{
    //da completare
    int pos = 0;
    for (int i = 1; i < n; i++) 
    {
        if (v[i] < v[pos])
            pos = i;
    }
    return v[pos];
}

/*la funzione StampaVettore stampa il contenuto di un vettore di interi di
una prefissata dimensione*/
void StampaVettore(float v[], int n) 
{
    for (int i = 0; i < n; i++)
        printf("%f\n", v[i]);
}

int main(void) {
    float  vett[N];
    float* positivi, * negativi;
    int  dim = N;

    /*
      Caricare i dati nel vettore  di float  'vett'

      chiamando la funzione AcquisisciVettore.
      Quindi stampare il vettore
    */
    AcquisisciVettore(vett, dim);
    StampaVettore(vett, dim);
    /*
    Generare i vettoro dei numeri positivi e dei numeri negativi
    continenuti in vett  utilizzando la
    funzione DividiVettore e stampare i due vettori
    */
    int dimpos;
    int dimneg;
    
    //chiama la funzioen DividiVettore
    DividiVettore(vett, dim, &positivi, &negativi, &dimpos, &dimneg);
    printf("\n----------------\n");
    StampaVettore(positivi, dimpos);
    printf("\n----------------\n");
    StampaVettore(negativi, dimneg);
    /*
    Invocare la funzione CalcolaMinimo e quindi visualizzare
    il valore minimo dei due vettori (positivi e negativi)
    */

    printf("Il minimo per i positivi e' %.2f, per i negativi e' %.2f.\n", CalcolaMinimo(positivi, dimpos), CalcolaMinimo(negativi, dimneg));
    /* Disallocate la memoria allocata */
    free(positivi);
    free(negativi);
    return 0;
}
