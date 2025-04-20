/*
    Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare quello esistente
    tranne quando espressamente richiesto.
    L'esercizio si considera corretto se il programma compila correttamente ed esegue senza errori
    run-time dando i risultati attesi.

    Il file sorgente deve essere consegnato allegandolo a questa attività.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//
// Questa funzione legge una sequenza di numeri interi fino a caricare n valori pari in un vettore precedentemente allocato.
void leggi_console(int v[], int n)
{
    for (int i = 0; i < n; i++) 
    {
        printf("Inserisci elemento di posizione %d: ", (i + 1));
        scanf("%d", &v[i]);
        if (v[i] % 2 != 0)
            i--;
    }
}

//
// la funzione costruisce un vettore di float a partire da quello passato come argomento
// dove ogni elemento di posizione i e' la media dei valori da quello di indice 0 a quello di indice i.

// Lo studente deve implementare la seguente funzione
void calcolo_media(int v[], float w[], int dimensione) 
{
    //inserire l'implementazione della funzione
    int cont;
    int valore;
    for (int i = 0; i < dimensione; i++) 
    {
        valore = 0;
        cont = 0;
        if (i == 0) 
        {
            w[i] = v[i];
            continue;
        }
        for (int j = 0; j <= i; j++) 
        {
            valore += v[j];
            cont++;
        }
        w[i] = ((float)(valore) / (float)(cont));
    }
}

//
// Visualizza tutti i valori di un vettore di float passato come parametro e ne restituisce la somma
// la funzione si dovra' chiamare stampa_vettore
// Lo studente deve implementare la funzione e definire i parametri formali necessari
float stampa_vettore(float v[], int dim)
{
    //inserire l'implementazione della funzione
    float somma = 0;
    printf("\n---------------------\n");
    for (int i = 0; i < dim; i++)
    {
        printf("v[%d] = %.3f\n", i, v[i]);
        somma += v[i];
    }
    return somma;
}

int main(void)
{
    float* vettore_float;
    int* vettore_interi;
    int dimensione;
    float somma;
    // lo studente inserisca il codice necessario a richiedere la dimensione
    // ed allocare correttamente il vettore di interi. Lo studente si assicuri
    // che il valore inserito sia maggiore di zero
    do
    {
        printf("Inserisci la dimensione: ");
        scanf("%d", &dimensione);
    } while (dimensione <= 0);
    //inserire eventuali allocazioni necessarie
    vettore_interi = (int*)malloc(sizeof(int) * dimensione);
    if (vettore_interi == NULL)
        return -1;
    vettore_float = (float*)malloc(sizeof(float) * dimensione);
    if (vettore_float == NULL)
        return -1;
    // Lo studente deve completare la chiamata della funzione inserendo i parametri attuali corretti
    leggi_console(vettore_interi, dimensione);
    // lo studente deve chiamare la funzione calcolo_media usando i parametri attuali corretti.
    calcolo_media(vettore_interi, vettore_float, dimensione);
    // lo studente deve chiamare la funzione stampa per stampare il vettore contenente float con i parametri 
    // corretti e stampare la somma dei valori contenuti nel vettore di float
    somma = stampa_vettore(vettore_float, dimensione);
    printf("\nLa somma e' %.3f.\n", somma);
    // lo studente deve deallocare tutta la memoria heap (dinamica) precedentemente allocata
    // prima di terminare il programma.
    free(vettore_interi);
    free(vettore_float);
    return 0;
}
