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
float* calcolo_media_mobile(int v[], int dimensione) {
}

//
// Questa funzione visualizza tutti i valori di un vettore di float maggiori 
// di una soglia passata come parametro
//
// Lo studente deve implementare la funzione e definire i parametri formali necessari 
void stampa_vettore( /* da completare */) {
}

int main(void)
{
    float *vettore_media;
    int *vettore_interi;
    int dimensione;
    float soglia;

    // lo studente inserisca il codice necessario a richiedere la dimensione
    // ed allocare correttamente il vettore di interi. Lo studente si assicuri
    // che il valore inserito sia maggiore di zero

    // Lo studente deve inserire i parametri attuali corretti
    dimensione = leggi_console( /**/);
  
    // lo studente deve chiamare la funzione calcolo_media_moile usando i parametri attuali corretti.
    vettore_media = calcolo_media_mobile(/**/);

    // lo studente inserisca il codice necessario a richiedere la soglia

    // lo studente richiami la funzione stampa con i parametri corretti
    stampa_vettore( /**/);

    // lo studente deve deallocare tutta la memoria heap (dinamica) precedentemente allocata
    // prima di terminare il programma.

    return 0;
}
