/******************************************************************************

 Scrivere un programma ANSI C che consente di leggere due vettori di interi da tastiera,
 e di ottenere in uscita un terzo vettore di interi contenente solo gli interi
 di ognuno dei vettori che non sono presenti nell'altro (unione delle differenze).
 I vettori in ingresso hanno lunghezza fissa, mentre il vettore in uscita
 deve avere dimensione opportuna, restituita come parametro.

 Es.
     Vettore A: 1 2 3 4
     Vettore B: 3 4 5 6 7 8
     Vettore C: 1 2 5 6 7 8

 Es 2.
    Vettore A (input): 1 2 3 4
    Vettore B (input): 5 6 7 8 9 10
    Vettore C (output): 1 2 3 4 5 6 7 8 9 10

 Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare
 quello esistente tranne quando espressamente richiesto.
 L'esercizio si considera corretto se il programma compila correttamente ed esegue
 senza errori run-time dando i risultati attesi.

*******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define DIM_A 4
#define DIM_B 6

/* Funzione ausiliaria che restituisce l'indice del numero cercato, se trovato.
 *
 * trova: restituisce l'indice del numero cercato, se trovato, altrimenti -1
 * Parametri:
 *     vettore: vettore in cui cercare
 *     dimensione: dimensione del vettore
 *     numero_cercato: numero da cercare
 * Ritorno:
 *    indice del numero cercato, se trovato, altrimenti -1
 */
int trova(int *vettore, int dimensione, int numero_cercato) {
    // IMPLEMENTAZIONE A CURA DELLO STUDENTE
}

/* unione_differenze: produce l'unione dei numeri di ognuno dei due vettori in ingresso
 *                  che non fanno parte dell'altro vettore.
 *                  Il vettore in uscita deve essere allocato dinamicamente e la sua dimensione
 *                  deve essere restituita come parametro.
 *
 * Parametri:
 *    vettore1: primo vettore in ingresso
 *    vettore2: secondo vettore in ingresso
 *    vettore1_dim: dimensione del primo vettore
 *    vettore2_dim: dimensione del secondo vettore
 *    uscita: puntatore al vettore in uscita
 *    dimensione: puntatore alla dimensione del vettore in uscita
 * Ritorno:
 *   Nessuno
*/
void unione_differenze(int *vettore1, int *vettore2, int vettore1_dim, int vettore2_dim,
                       int **uscita, int *dimensione) {
    // IMPLEMENTAZIONE A CURA DELLO STUDENTE
}



/**** MAIN *****/
int main(void) {

    // Dichiarare i vettori e le variabili
    int a[DIM_A];
    int b[DIM_B];

    int *c;
    int dim_c;

    int valore;

    // Richiedere i numeri in input all'utente
    // IMPLEMENTAZIONE A CURA DELLO STUDENTE


    // Stampa dei vettori in input
    printf("\nVettore A: ");
    for (int i = 0; i < DIM_A; i++) {
        printf("%d ", a[i]);
    }
    printf("\nVettore B: ");
    for (int i = 0; i < DIM_B; i++) {
        printf("%d ", b[i]);
    }

    // Invocare la funzione unione_differenze
    // IMPLEMENTAZIONE A CURA DELLO STUDENTE


    // Visualizzarne il risultato
    printf("\nVettore C: ");
    for (int i = 0; i < dim_c; i++) {
        printf("%d ", c[i]);
    }

    // Deallocare il vettore di output
    // TODO STUDENTE

    return 0;
}
