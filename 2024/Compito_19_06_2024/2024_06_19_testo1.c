/*
    Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare quello 
    esistente tranne quando espressamente richiesto.
    L'esercizio si considera corretto se il programma compila correttamente ed esegue senza errori
    run-time dando i risultati attesi.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 20

/* AcquisisciVettore
   Acquisisce un vettore di float. La funzione legge due numeri interi 
   e inserisce nel vettore la media dei due valori 
*/
void AcquisisciVettore(float* v, int n) {
    //da completate
}

/* CreaVettori
La funzione prende in ingresso un vettore di float e restituisce
due vettori di float uno che contiene i valori positivi e uno che contiene
i valori negativi. Eventuali 0 vengono tralasciati.
*/
void DividiVettore(/*da completare*/) {

    /*da completare*/
    
    return;
}


/* La funzione restituisce un float contenente il minimo
di un vettore di float */
float CalcolaMinimo(float *v, , int n) {
    //da completare
}

/*la funzione StampaVettore stampa il contenuto di un vettore di interi di
una prefissata dimensione*/
void StampaVettore(float v[],int n){
    for (int i = 0; i < n; i++)
        printf("%f\n",v[i]);
}

int main(void) {
   float  vett[N];
   float *positivi, *negativi;
   int  dim = N;
  
  

    /*
      Caricare i dati nel vettore  di float  'vett'
       
      chiamando la funzione AcquisisciVettore.
      Quindi stampare il vettore 
    */
    
    /*
    Generare i vettoro dei numeri positivi e dei numeri negativi
    continenuti in vett  utilizzando la 
    funzione DividiVettore e stampare i due vettori 
    */
    
    //chiama la funzioen DividiVettore
    
    /* 
    Invocare la funzione CalcolaMinimo e quindi visualizzare 
    il valore minimo dei due vettori (positivi e negativi)  
    */
    
    
    /* Disallocate la memoria allocata */
   
    return 0;
}
