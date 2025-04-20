/*
  Scaricare l'esercizio e completarlo inserendo il codice necessario
  senza modificare quello esistente tranne quando espressamente
  richiesto.
  
  L'esercizio si considera corretto se il programma compila
  correttamente ed esegue senza errori run-time dando i risultati
  attesi.

  Il file sorgente deve essere consegnato allegandolo a questa
  attivit�.
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
void AcquisisciVettorediBit(int* v, int n){
    //da sviluppare
    
    return;
}


/*
  La funzione And  dato due vettore 'v1' e 'v2', di uguale dimensione restituisce un
  vettore cotenente l'and dei due valori contenuti nel vettore v1 e v2
  
 */
int* And(int* v1, int *v2, int n) {
  //da sviluppare
  
}


/*
  La funzione CambiaBase dato un vettore di bit di dimensione n 
  restituisce il valore in base 10 che rappresenta la suddetta 
  sequenza di bit.
 */
int CambiaBase(int *v, int dimensione) {
    //da sviluppare
   
    return valore;
}

/*stampa_vettore stampa un vettore di interi di dimensione n*/
void stampa_vettore(int *v, int n){
    printf("\n");
    for (int i=0;i<n;i++) printf("%d",v[i]);
    printf("\n");
}
int main(void)
{
  int* vettore1;
  int* vettore2;
  int *vettore_risultato;
  int  dimensione, valore;
  
  //leggere la dimensione dei vettori controllando che sia un valore positivo
  
  
  /*chiamare la funzione AcquisisciVettorediBit per leggere vettore1
  e stampare il contenuto del vettore1*/
  
  
  /*chiamare la funzione AcquisisciVettorediBit per leggere vettore2
  e stampare il contenuto del vettore2*/
  
  
  /*calcolare il vettore And dei vettori1 e vettore2 e stampare il 
  vettore risultante*/
  
  
  /*convertire in base 10 la sequenza di bit presente in vettore_risultato e stamparla*/
  
  

  /*liberare la memoria heap*/
  
  
  return 0;
}
