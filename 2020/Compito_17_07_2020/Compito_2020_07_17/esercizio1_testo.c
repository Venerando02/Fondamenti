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
void leggi_console(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Inserisci elemento di posizione %d: ", (i + 1));
        scanf("%d", &v[i]);
        if (v[i] %2 != 0) i--;
    }
}

//
// la funzione costruisce un vettore di float a partire da quello passato come argomento
// dove ogni elemento di posizione i e' la media dei valori da quello di indice 0 a quello di indice i.

// Lo studente deve implementare la seguente funzione
void calcolo_media(int v[], float w[], int dimensione) {
    //inserire l'implementazione della funzione
}

//
// Visualizza tutti i valori di un vettore di float passato come parametro e ne restituisce la somma
// la funzione si dovra' chiamare stampa_vettore
// Lo studente deve implementare la funzione e definire i parametri formali necessari
??? stampa_vettore(????????) {
    //inserire l'implementazione della funzione
}

int main(void)
{
    float *vettore_float;
    int *vettore_interi;
    int dimensione;

    // lo studente inserisca il codice necessario a richiedere la dimensione
    // ed allocare correttamente il vettore di interi. Lo studente si assicuri
    // che il valore inserito sia maggiore di zero
    
    //inserire eventuali allocazioni necessarie
    
    // Lo studente deve completare la chiamata della funzione inserendo i parametri attuali corretti
    leggi_console(    );
    // lo studente deve chiamare la funzione calcolo_media usando i parametri attuali corretti.
    calcolo_media(     );
    // lo studente deve chiamare la funzione stampa per stampare il vettore contenente float con i parametri 
    // corretti e stampare la somma dei valori contenuti nel vettore di float
    
    // lo studente deve deallocare tutta la memoria heap (dinamica) precedentemente allocata
    // prima di terminare il programma.
    
    return 0;
}
