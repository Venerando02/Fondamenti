//inserire Cognome, Nome e Numero di matricola

/* Questo esercizio prevede l’uso di codice esistente da integrare e completare in modo da risolvere il problema proposto. 
Lo studente deve utilizzare il codice proposto intervenendo solo nelle parti richieste ed integrandolo se necessario. 
Perché l’esercizio sia sufficiente è necessario che il codice compili senza errori, il programma esegua senza errori run-time, e fornisca il risultato previsto. */

#include <stdio.h> 
#include <stdlib.h>

void Carica(int* v, int n){
//la funzione deve consentire di leggere un vettore di n interi positivi e pari. I valori che non soddisfano il requisito vanno scartati   
}

int* Select(int* v, int dim1, int *dim2) {
/* A partire dal vettore v di dimensione dim1, restituisce un nuovo vettore contenente tutti gli elementi del vettore v che sono multipli di 5. La dimensione del nuovo vettore deve essere calcolata e fornita dalla funzione Select come parametro dim2 */
}

void Display(int *v, int n) {
// Visualizza tutti gli elementi di un array v passato come parametro avente dimensione n
}
 
int main(void){
  int *v1, *v2;
  int dim1, dim2 = 0;
  printf("Inserisci la dimensione del vettore v1: ");
  scanf("%d", &dim1);   // Assicurarsi che la dimensione dim1 sia un numero positivo, se non lo è ripetere l’inserimento
  v1 = ...;             // Alloca un array di dim1 elementi int
  Carica(...);          // Acquisisce gli elementi in v1
  v2 = Select (...);
  Display(...);         // Visualizza il vettore v2  
  ...; // Disalloca v1
  ...; // Disalloca v2
  return 0;
} 

