/*
  Scaricare l'esercizio e completarlo inserendo il codice necessario
  senza modificare quello esistente tranne quando espressamente
  richiesto.
  
  L'esercizio si considera corretto se il programma compila
  correttamente ed esegue senza errori run-time dando i risultati
  attesi.


 * Acquisire un vettore di float, creare un nuovo array con soltanto i valori > 0
 * scalati per la somma di tutti i valori > 0, trovare l'indice del
 * valore massimo e disallocare gli array.
 *
 * Esempio di elaborazione:
 *  Dimensione del vettore da acquisire: 4
    Inserisci il prossimo valore (float) 0: 0
    Inserisci il prossimo valore (float) 1: 3.
    Inserisci il prossimo valore (float) 2: 8.5
    Inserisci il prossimo valore (float) 3: 2.5

    Vettore acquisito:
    0.000000
    3.000000
    8.500000
    2.500000

    Vettore scalato:
    0.214286
    0.607143
    0.178571

    L'indice dell'elemento massimo è 1 (0.607143)
 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/*
 * La funzione acquisisce un vettore di dim float e lo restituisce.
 * Esempio:
 * Input: 4
 * Input da tastiera: 0.0 ,  3.0,    8.5,    2.5
 * Output:  [    0.0,    3.0,    8.5,    2.5     ]
 */
float *acquisisci(int dim) {
    // TODO Implementazione a cura dello studente
}

/*
 * Dato un vettore di float in ingresso, la funzione crea_vettore alloca un nuovo
 * vettore contenente i valori > 0 divisi per la somma di tutti gli elementi.
 * Il nuovo numero di elementi viene restituito tramite parametro.
 * Se l'array è vuoto o non contiene valori positivi, viene restituito NULL e dim_out settato a 0.
 * Esempio:
 * Input:  [    0.0,    3.0,    8.5,    2.5     ]
 * Output: [    0.21,   0.60,   0.17    ]
*/
float *crea_vettore(float *vettore_in, int dim, int *dim_out) {
    // TODO Implementazione a cura dello studente
}


/*
 * La funzione cerca_massimo restituisce l'indice del valore più grande
 * presente all'interno del vettore, o -1 se l'array è vuoto.
 * Esempio:
 * Input:  [    0.0,    3.0,    8.5,    2.5     ]
 * Output: 2
  */
int cerca_massimo(float *vettore, int dim) {
    // TODO Implementazione a cura dello studente
}

/*
  La funzione visualizza_vettore e VisualizzaVettore2 visualizza vettore
 */
void visualizza_vettore(float *vettore, int dim) {
    for (int i = 0; i < dim; i++)
        printf("%f\n", vettore[i]);
}

int main(void) {
    float *vettore;
    float *vettore_positivi_scalati;
    int indice_max;
    int dimensione_array, dim_array_positivi_scalati;

    // Leggere la dimensione del vettore di float, verificando che sia un valore positivo
    do {
        printf("Dimensione del vettore da acquisire: ");
        scanf("%d", &dimensione_array);
    } while (dimensione_array <= 0);

    // Acquisire il vettore utilizzando la funzione acquisisci.
    vettore = acquisisci(dimensione_array);

    // Verificare che l'acquisizione sia andata a buon fine, nel caso contrario uscire dal programma
    if (vettore == NULL) return 0;

    // Stampare il vettore
    visualizza_vettore(vettore, dimensione_array);

    // Crea il vettore degli elementi positivi scalati utilizzando la funzione crea_vettore
    // TODO STUDENTE

    // Se il vettore non e' stato allocato, esce
    // TODO STUDENTE


    // Stampa il vettore
    visualizza_vettore(vettore_positivi_scalati, dim_array_positivi_scalati);

    // Cerca l'indice del massimo del vettore di elementi positivi scalati
    // TODO STUDENTE


    printf("L'indice dell'elemento massimo è %d (%f)", indice_max, vettore_positivi_scalati[indice_max]);

    // Disallocare i due vettori
    // TODO STUDENTE


    return 0;
}
