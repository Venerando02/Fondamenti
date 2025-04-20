/*
    Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare quello 
    esistente tranne quando espressamente richiesto.
    L'esercizio si considera corretto se il programma compila correttamente ed esegue senza errori
    run-time dando i risultati attesi.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 5

/* AcquisisciVettore
   Acquisisce un vettore di float. La funzione legge due numeri interi 
   e inserisce nel vettore la media dei due valori 
*/
void AcquisisciVettore(float* v, int n) {
    int primo,secondo;
    for(int i=0;i<n;i++) {
        printf("\ninserisci un valore intero ");
        scanf("%d",&primo);
        printf("\ninserisci il secondo intero ");
        scanf("%d",&secondo);
        v[i] = (primo + secondo)/2.0;
    }
}

/* CreaVettori
La funzione prende in ingresso un vettore di float e restituisce
due vettori di float uno che contiene i valori positivi e uno che contiene
i valori negativi. Eventuali 0 vengono tralasciati.
*/
void DividiVettore(float *v,float **positivi,float **negativi, int dim, int *dimP, int *dimN) {
    int numP=0,numN = 0;
    float *vettP,*vettN;
    
    //alloco inizialmente i vettori di dimensione dimN 
    vettP = (float*)malloc(sizeof(float)*dim); 
    vettN = (float*)malloc(sizeof(float)*dim); 
    
    for (int i = 0; i<dim; i++) {
        if(v[i]==0) continue;
        if (v[i]>0) vettP[numP++] = v[i];
        else if (v[i]<0) vettN[numN++] = v[i];
    }
    
    //faccio il resize
    *positivi = realloc(vettP,sizeof(float)*numP);
    *negativi = realloc(vettN,sizeof(float)*numN);
    
    *dimP=numP;
    *dimN=numN;
    return;
}


/* La funzione restituisce un float contenente il minimo
di un vettore di float */
float CalcolaMinimo(float *v,  int n) {
    int min = v[0];
    for(int i=1;i<n;i++)
        if (v[i]<min) min = v[i];
    return min;
}

/*la funzione StampaVettore stampa il contenuto di un vettore di interi di
una prefissata dimensione*/
void StampaVettore(float v[],int n){
    printf("STAMPA VETTORE");
    for (int i = 0; i < n; i++)
        printf("%f\n",v[i]);
}

int main(void) {
   float  vett[N];
   float *positivi, *negativi;
   int  dim = N;
   int dimP,dimN;
  
  

    /*
      Caricare i dati nel vettore  di float  'vett'
       
      chiamando la funzione AcquisisciVettore.
      Quindi stampare il vettore 
    */
    AcquisisciVettore(vett,dim);
    StampaVettore(vett,dim);
    
    /*
    Generare i vettoro dei numeri positivi e dei numeri negativi
    continenuti in vett  utilizzando la 
    funzione DividiVettore e stampare i due vettori 
    */
    
    //chiama la funzioen DividiVettore
    DividiVettore(vett,&positivi,&negativi,dim,&dimP,&dimN);
    StampaVettore(positivi,dimP);
    StampaVettore(negativi,dimN);
    /* 
    Invocare la funzione CalcolaMinimo e quindi visualizzare 
    il valore minimo dei due vettori (positivi e negativi)  
    */
    
    printf("minimo = %f", CalcolaMinimo(positivi,dimP));
    printf("minimo = %f", CalcolaMinimo(positivi,dimP));
  
    /* Disallocate la memoria allocata */
    free(positivi);
    free(negativi);
    return 0;
}
