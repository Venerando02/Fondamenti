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
// Questa funzione legge una sequenza di numeri interi fino a caricare n valori in un vettore precedentemente allocato.
void leggi_console(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Inserisci elemento di posizione %d: ", (i + 1));
        scanf("%d", &v[i]);
    }
}

//
// la funzione costruisce un vettore di float w che contiene tutti i valori dispari presenti in v 
// diviso due. Nota bene che il vettore w potrebbe essere vuoto. 
//

// Lo studente deve implementare la seguente funzione
float* crea_nuovo_vettore(int v[], int dim_v, int *dim_w) {
    //inserire l'implementazione della funzione    
}

//
// Visualizza tutti i valori di un vettore di float passato come parametro e ne restituisce la somma
// la funzione si chiama stampa_vettore
// Lo studente deve implementare la funzione e definire sia i parametri formali necessari che il tipo della
// funzione
?????? stampa_vettore(?????????) {
    //inserire l'implementazione della funzione    
}

int main(void)
{
    float *vettore_float;
    int *vettore_interi;
    int dimensione1;
    int dimensione2;

    // lo studente inserisca il codice necessario a richiedere la dimensione
    // ed allocare correttamente il vettore di interi. Lo studente si assicuri
    // che il valore inserito sia maggiore di zero
    
    
    

    leggi_console(vettore_interi, dimensione1);

    // lo studente chiami la funzione crea_nuvo_vettore inserendo  i parametri attuali corretti.
    ??????? = crea_nuovo_vettore(????????);

    // lo studente chiami la funzione stampa per stampare il vettore contenente float con i parametri 
    // corretti e stampi il valore restituito dalla funzione
       
    // Inserire codice
    
    // lo studente deallochi tutta la memoria heap (dinamica) precedentemente allocata e termini
    // il programma.
    
    // Inserire codice
    
    
    return 0;
}
