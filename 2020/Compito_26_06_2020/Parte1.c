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
// Questa funzione legge una sequenza di numeri interi positivi terminata da un valore 
// negativo caricandoli in un vettore precedentemente allocato le cui dimensioni massime 
// sono passate come parametro
// La funzione restituisce il numero di valori effettivamente letti
int leggi_console(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Inserisci elemento di posizione %d: ", (i + 1));
        scanf("%d", &v[i]);
        if (v[i] < 0)
            return i;
    }
    return n;
}

//
// Questa funzione deve costruire un vettore di float a partire da quello passato come argomento 
// dove ogni elemento è la media dei precedenti due valori. 
// Nel caso del primo elemento la media coincide con il valore stesso.
// Il vettore risultante deve essere allocato all'interno della funzione.
//
// Lo studente deve implementare la funzione
float* calcolo_media_mobile(int v[], int dimensione) 
{
    float* vout = malloc(sizeof(float) * dimensione);
    for (int i = 1; i < dimensione; i++) 
    {
        vout[0] = v[0];
        vout[i] = (((float)(v[i]) + (float)(v[i - 1]))) / 2.0F;
    }
    return vout;
}

//
// Questa funzione visualizza tutti i valori di un vettore di float maggiori 
// di una soglia passata come parametro
//
// Lo studente deve implementare la funzione e definire i parametri formali necessari 
void stampa_vettore(float v[], int dim, float soglia) 
{
    printf("VETTORE RISULTANTE:\n");
    for (int i = 0; i < dim; i++) 
    {
        if (v[i] > soglia) 
        {
            printf("%.3f ", v[i]);
        }
    }
}

int main(void)
{
    float* vettore_media;
    int* vettore_interi;
    int dim, dimensione;
    float soglia;


    // lo studente inserisca il codice necessario a richiedere la dimensione
    // ed allocare correttamente il vettore di interi. Lo studente si assicuri
    // che il valore inserito sia maggiore di zero
    do {
        printf("Inserisci la dimensione: ");
        scanf("%d", &dim);
    } while (dim <= 0);
    vettore_interi = malloc(sizeof(int) * dim);
    
    // Lo studente deve inserire i parametri attuali corretti
    dimensione = leggi_console(vettore_interi, dim);
    printf("----------VETTORE RISULTANTE------------\n");
    for (int i = 0; i < dim; i++)
        printf("%5d", vettore_interi[i]);
    // lo studente deve chiamare la funzione calcolo_media_moile usando i parametri attuali corretti.
    vettore_media = calcolo_media_mobile(vettore_interi, dim);

    // lo studente inserisca il codice necessario a richiedere la soglia
    printf("\nInserisci la soglia: ");
    scanf("%f", &soglia);
    // lo studente richiami la funzione stampa con i parametri corretti
    stampa_vettore(vettore_media, dim, soglia);

    // lo studente deve deallocare tutta la memoria heap (dinamica) precedentemente allocata
    // prima di terminare il programma.
    free(vettore_interi);
    free(vettore_media);
    return 0;
}
