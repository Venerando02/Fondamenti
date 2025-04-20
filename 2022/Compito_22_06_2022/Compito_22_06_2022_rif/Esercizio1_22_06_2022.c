/*
  Scaricare l'esercizio e completarlo inserendo il codice necessario
  senza modificare quello esistente tranne quando espressamente
  richiesto.

  L'esercizio si considera corretto se il programma compila
  correttamente ed esegue senza errori run-time dando i risultati
  attesi.

  Il file sorgente deve essere consegnato allegandolo a questa
  attività.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


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
    int i = 0;
    while (i < n) 
    {
        printf("Inserisci il valore %d: ", i);
        scanf("%d", &v[i]);
        if ((v[i] == 0) || (v[i] == 1))
        {
            i++;
        }
    }
    return;
}


/*
  La funzione And  dato due vettore 'v1' e 'v2', di uguale dimensione restituisce un
  vettore cotenente l'and dei due valori contenuti nel vettore v1 e v2

 */
int* And(int* v1, int* v2, int n) {
    //da sviluppare
    int* and = (int*)malloc(sizeof(int) * n);
    if (and == NULL)
        return NULL;
    for (int i = 0; i < n; i++) 
    {
        and[i] = (v1[i] * v2[i]);
    }
    return and;
}


/*
  La funzione CambiaBase dato un vettore di bit di dimensione n
  restituisce il valore in base 10 che rappresenta la suddetta
  sequenza di bit.
 */
int CambiaBase(int* v, int dimensione) {
    //da sviluppare
    int valore = 0;
    int PotenzaDue = 2;
    int PotTot;
    for (int i = (dimensione - 1); i >= 0; i--) 
    {
        PotTot = 1;
        for (int j = 0; j < i; j++) 
        {
            PotTot = PotTot * PotenzaDue;
        }
        if (i == 0) 
        {
            PotTot = 1;
        }
        valore += v[i] * PotTot;
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
    do 
    {
        printf("Inserisci la dimensione: ");
        scanf("%d", &dimensione);
    } while (dimensione <= 0);
    vettore1 = (int*)malloc(sizeof(int) * dimensione);
    if (vettore1 == NULL)
        return 0;
    vettore2 = (int*)malloc(sizeof(int) * dimensione);
    if (vettore2 == NULL)
        return 0;
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
    stampa_vettore(vettore_risultato, dimensione);
    /*convertire in base 10 la sequenza di bit presente in vettore_risultato e stamparla*/
    valore = CambiaBase(vettore_risultato, dimensione);
    printf("Il valore in base 10 e': %d", valore);

    /*liberare la memoria heap*/
    free(vettore1);
    free(vettore2);
    free(vettore_risultato);
    return 0;
}
