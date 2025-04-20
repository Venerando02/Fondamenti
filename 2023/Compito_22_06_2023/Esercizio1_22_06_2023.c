/*
    Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare quello
    esistente tranne quando espressamente richiesto.
    L'esercizio si considera corretto se il programma compila correttamente ed esegue senza errori
    run-time dando i risultati attesi.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct C {
    int q, c;
} coppia;

/* AcquisisciVettore
   Acquisisce un vettore di interi positivi di dimensione n, la funzione tralascia
   il valore nel caso questo sia negativo o uguale a 0
*/
void AcquisisciVettore(int* v, int n) 
{
    //da completate
    int i = 0;
    while (i < n)
    {
        printf("Inserisci il valore %d: ", i);
        scanf("%d", &v[i]);
        if (v[i] > 0) 
        {
            i++;
        }
    }
}

/* CreaVettorePositivi
Crea e restituisce due vettori uno contenente il quadrato e uno il
cubo dei valori  del vettore v passato come argomento. Il vettore
contenente i quadrati viene allocato nella funzione e restituito come valore
di ritorno mentre il vettore contenente i cubi è passato (già allocato) come argomento
della funzione
*/
int* CreaQuadratiCubi(int v1[], int dim, int cubi[]) {

    /*da completare*/
    int* quadrato = (int*)malloc(sizeof(int) * dim);
    for (int i = 0; i < dim; i++) 
    {
        quadrato[i] = (v1[i] * v1[i]);
        cubi[i] = (v1[i] * v1[i] * v1[i]);
    }
    return quadrato;
}


/* La funzione restituisce una struct coppia contenente il massimo
dei due vettori quadrato e cubo passati come parametri */
coppia CalcolaMassimo(int cubo[], int quadrato[], int n) 
{
    //da completare
    int pos_massimo = 0;
    coppia valori_massimi;
    valori_massimi.c = 0;
    valori_massimi.q = 0;
    for (int i = 1; i < n; i++) 
    {
        if (quadrato[i] > quadrato[pos_massimo]) 
        {
            pos_massimo = i;
        }
    }
    valori_massimi.q = quadrato[pos_massimo];
    pos_massimo = 0;
    for (int i = 1; i < n; i++)
    {
        if (cubo[i] > cubo[pos_massimo]) 
        {
            pos_massimo = i;
        }
    }
    valori_massimi.c = cubo[pos_massimo];
    return valori_massimi;
}

/*la funzione StampaVettore stampa il contenuto di un vettore di interi di
una prefissata dimensione*/
void StampaVettore(int v[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d\n", v[i]);
}

int main(void) {

    int* vett;
    int* Quadrato, * Cubo;
    int  dim;
    coppia Massimo;


    /*
      Acquisire la dimensione di un vettore ed assicurarsi che la
      dimensione sia un numero positivo. Quindi allocare un vettore 'vett1'
      di interi di tale dimensione inserendo solo valori positivi
      chiamando la funzione AcquisisciVettore.
      Quindi stampare il vettore
    */
    do 
    {
        printf("Inserisci la dimensione del vettore: ");
        scanf("%d", &dim);
    } while (dim <= 0);
    vett = (int*)malloc(sizeof(int) * dim);
    if (vett == NULL)
        return 0;
    AcquisisciVettore(vett, dim);
    StampaVettore(vett, dim);
    /*
    Generare il vettore dei quadrati e dei cubi utilizzando la
    funzione CreaQuadratiCubi e stampare i vettori contenente i
    quadrati e i cubi
    */
    Cubo = (int*)malloc(sizeof(int) * dim);
    Quadrato = CreaQuadratiCubi(vett, dim, Cubo);

    /*
    Invocare la funzione CalcolaMassimo e visualizzare
    il valore massimo del valore contenuto nel vettore quadrato
    e nel vettore cubo
    */
    Massimo = CalcolaMassimo(Cubo, Quadrato, dim);
    printf("Il valore massimo nei cubi e' %d, nei quadrati %d.\n", Massimo.c, Massimo.q);
    /* Disallocate la memoria allocata */
    free(vett);
    free(Cubo);
    free(Quadrato);
    return 0;
}
