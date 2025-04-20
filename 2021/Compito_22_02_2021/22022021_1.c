/*
    Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare quello esistente tranne quando espressamente richiesto.
    L'esercizio si considera corretto se il programma compila correttamente ed esegue senza errori
    run-time dando i risultati attesi.

    Il file sorgente deve essere consegnato allegandolo a questa attività.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* AcquisisciVettore
   Acquisisce un vettore di interi dimensione n */
void AcquisisciVettore(int* v, int n) 
{
    for (int i = 0; i < n; i++) {
        printf("Inserisci elemento di posizione %d: ", i);
        scanf("%d", &v[i]);
    }
}

/* CreaVettorePositivi
Crea e restituisce un vettore che contiene i soli valori positivi del vettore v passato come argomento
*/
int* CreaVettorePositivi(int v[], int n, int* dimpos) 
{
    // ...da implementare a cura dello studente...
    (*dimpos) = 0;
    int* vout = (int*)malloc(sizeof(int) * n);
    if (vout == NULL)
        return NULL;
    for (int i = 0; i < n; i++) 
    {
        if (v[i] > 0)
        {
            vout[(*dimpos)++] = v[i];
        }
    }
    return vout;
}


/* VisualizzaCalcolaMedia
Visualizza il contenuto di un vettore di interi di dimensione n
e ne restituisce il valor medio */
float VisualizzaCalcolaMedia(int v[], int n) 
{
    // ...da implementare a cura dello studente...
    int somma = 0;
    printf("\n------------------\n");
    for (int i = 0; i < n; i++) 
    {
        printf("v[%d] = %d\n", i, v[i]);
        somma += v[i];
    }
    float media = ((float)(somma) / n);
    return media;
}

int main(void) {

    int* vett1;
    int* vett2;
    int  dim1, dim2;
    float media;

    /*
      Acquisire la dimensione di un vettore ed assicurarsi che la
      dimensione sia un numero positivo. Quindi allocare un vettore 'vett1'  di interi di tale dimensione.
    */
    //...istruzioni...
    do 
    {
        printf("Inserisci la dimensione: ");
        scanf("%d", &dim1);
    } while (dim1 <= 0);
    vett1 = (int*)malloc(sizeof(int) * dim1);
    if (vett1 == NULL)
        return NULL;
    AcquisisciVettore(vett1, dim1);
    /*
    Generare il vett2 chiamando la funzione CreaVettorePositivi
    */
    vett2 = CreaVettorePositivi(vett1, dim1, &dim2);

    /* Invocare la funzione VisualizzaCalcolaMedia per visualizzare il vettore vett2
       e successivamente visualizzare la sua media
    */
    media = VisualizzaCalcolaMedia(vett2, dim2);
    printf("Media: %f", media);

    /* Disallocare la memoria allocata */
    //...istruzioni....
    free(vett1);
    free(vett2);
    return 0;
}
