/*
  Scaricare l'esercizio e completarlo inserendo il codice necessario
  senza modificare quello esistente tranne quando espressamente
  richiesto.

  L'esercizio si considera corretto se il programma compila
  correttamente ed esegue senza errori run-time dando i risultati
  attesi.

  Il file sorgente deve essere consegnato allegandolo a questa
  attivita'.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    La funzione AcquisisciVettore legge una sequenza di valori 0 e 1
    caricandoli in un vettore precedentemente allocato le cui dimensione
    è passata come parametro.
    La funzione non restituisce nulla.
    Nel caso vengano inseriti valori diversi dal valore 1 e 0 questi non
    vengono inseriti nel vettore
 */
void AcquisisciVettorediBit(int* v, int n) {
    //da sviluppare
    for(int i = 0;i<n; i++)
    {
        printf("Inserisci il valore %d (0 o 1): ", i);
        scanf("%d", &v[i]);
        if ((v[i] != 0) && (v[i] != 1)) 
        {
            printf("Inserisci o 0 o 1.");
            break;
        }
    };
}


/*
  La funzione And  dato due vettore 'v1' e 'v2', di uguale dimensione restituisce un
  vettore cotenente l'and dei due valori contenuti nel vettore v1 e v2
 */
int* And(int* v1, int* v2, int n) 
{
    //da sviluppare
    int* vettore_and;
    vettore_and = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) 
    {
        vettore_and[i] = v1[i] * v2[i];
    }
    return vettore_and;
}


/*
  La funzione CambiaBase dato un vettore di bit di dimensione n
  restituisce il valore in base 10 che rappresenta la suddetta
  sequenza di bit.
 */

// in maniera alternativa 
// int potenza_2 = 1 cioè 2^0
// for(int i = dimensione-1; i>=0;i--)
// valore = valore + v[i] * potenza_2
// potenza_2*=2;

int CambiaBase(int* v, int dimensione) {
    //da sviluppare
    int valore = 0;
    for (int i = 0; i < (dimensione); i++) 
    {
        valore = valore + v[i]*pow(2, (dimensione-1-i));
    }
    return valore;
}

/*stampa_vettore stampa un vettore di interi di dimensione n*/
void stampa_vettore(int* v, int n) {
    printf("\n");
    for (int i = 0; i < n; i++) printf("%d", v[i]);
    printf("\n");
}
int main(void)
{
    int* vettore1;
    int* vettore2;
    int* vettore_risultato;
    int  dimensione, valore;

    //leggere la dimensione dei vettori controllando che sia un valore positivo
    printf("Inserisci la dimensione dei vettori: ");
    scanf("%d", &dimensione);
    if (dimensione < 0) {
        printf("Inserisci una dimensione positiva.");
        return;
    }
    vettore1 = malloc(sizeof(int) * dimensione);
    vettore2 = malloc(sizeof(int) * dimensione);
    /*chiamare la funzione AcquisisciVettorediBit per leggere vettore1
    e stampare il contenuto del vettore1*/
    AcquisisciVettorediBit(vettore1, dimensione);
    stampa_vettore(vettore1, dimensione);

    /*chiamare la funzione AcquisisciVettorediBit per leggere vettore2
    e stampare il contenuto del vettore2*/
    AcquisisciVettorediBit(vettore2, dimensione);
    stampa_vettore(vettore2, dimensione);

    /*calcolare il vettore And dei vettori1 e vettore2 e stampare il
    vettore risultante*/
    
    vettore_risultato = And(vettore1, vettore2, dimensione);
    printf("------------VETTORE RISULTATO-------------\n");
    stampa_vettore(vettore_risultato, dimensione);

    /*convertire in base 10 la sequenza di bit presente in vettore_risultato e stamparla*/
    valore = CambiaBase(vettore_risultato, dimensione);
    printf("\nValore in base 10: %d", valore);

    /*liberare la memoria heap*/
    free(vettore1);
    free(vettore2);
    free(vettore_risultato);
    return 0;
}
