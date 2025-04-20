/*
    Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare quello 
    esistente tranne quando espressamente richiesto.
    L'esercizio si considera corretto se il programma compila correttamente ed esegue senza errori
    run-time dando i risultati attesi.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct C {
   int q,c; 
} coppia;

/* AcquisisciVettore
   Acquisisce un vettore di interi positivi di dimensione n, la funzione tralascia 
   il valore nel caso questo sia negativo o uguale a 0 
*/
void AcquisisciVettore(int* v, int n) {
    //da completate
}

/* CreaVettorePositivi
Crea e restituisce due vettori uno contenente il quadrato e uno il 
cubo dei valori  del vettore v passato come argomento. Il vettore 
contenente i quadrati viene allocato nella funzione e restituito come valore 
di ritorno mentre il vettore contenente i cubi è passato (già allocato) come argomento 
della funzione
*/
int* CreaQuadratiCubi(/*da completare*/) {

    /*da completare*/
    
    return quadrato;
}


/* La funzione restituisce una struct coppia contenente il massimo
dei due vettori quadrato e cubo passati come parametri */
coppia CalcolaMassimo(int cubo[], int quadrato[], int n) {
    //da completare
}

/*la funzione StampaVettore stampa il contenuto di un vettore di interi di
una prefissata dimensione*/
void StampaVettore(int v[],int n){
    for (int i = 0; i < n; i++)
        printf("%d\n",v[i]);
}

int main(void) {
   
    int* vett;
    int* Quadrato, * Cubo;
    int  dim;
    coppia Massimo;
  

    /*
      Acquisire la dimensione di un vettore ed assicurarsi che la
      dimensione sia un numero positivo. Quindi allocare un vettore 'vett1'
      di interi di tale dimensione inserendo solo valori positivi 
      chiamando la funzione AcquisisciVettore.
      Quindi stampare il vettore 
    */
    
    /*
    Generare il vettore dei quadrati e dei cubi utilizzando la 
    funzione CreaQuadratiCubi e stampare i vettori contenente i
    quadrati e i cubi
    */
    Cubo = (int*)malloc(sizeof(int) * dim);
    Quadrato = CreaQuadratiCubi(vett, dim, Cubo);
    
    /* 
    Invocare la funzione CalcolaMassimo e visualizzare 
    il valore massimo del valore contenuto nel vettore quadrato
    e nel vettore cubo  
    */
    
    
    /* Disallocate la memoria allocata */
   
    return 0;
}
