/*
  Scaricare l'esercizio e completarlo inserendo il codice necessario
  senza modificare quello esistente tranne quando espressamente
  richiesto.

  L'esercizio si considera corretto se il programma compila
  correttamente ed esegue senza errori run-time dando i risultati
  attesi.

  Il file sorgente deve essere consegnato allegandolo a questa
  attivit�.

  La descrizione delle funzioni e del programma e' nei
  commenti presenti nel testo 

  Esempio di elaborazione
  numero di elementi: 5
  dati in ingresso: 1.2 -> 1.3 -> 1.301 -> 0.2 -> 0.2 -> 3.0
  soglia: 0.01
  stampa del risultato:
    1.2000  1.3000  1
    1.3000  1.3010  0
    1.3010  0.2000  -1
    0.2000  0.3000  1

*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/*
  La funzione acquisisci_elevazione alloca un vettore di dim elementi e
  acquisisce i valori reali (float) che devono essere inseriti nel vettore.
  I valori rappresentanp rappresentano l'elevazione di una serie
  di punti di un percorso
  nome: acquisisci_array
  parametri: 
    dim: numero di valori da acquisire
  return:
    vettore contentente i valori
  vincoli:
    i valori devono essere non inferiori a 0 (zero)

 */
float* acquisisci_elevazione(int dim) {
}

/*
* la funzione stampa_elevazioni stampa il contenuto di un vettore
* di numeri reali con due cifre decimali
*/
void stampa_elevazioni(float *v, int dim) {
    for (int i = 0; i < dim; ++i)
        printf("%.2f - ", v[i]);
    printf("\n");
}

/*
La funzione calcola_pendenza calcola la pendenza del segmento dipercorso dal punto
attuale al punto successivo e ne memorizza in un vettore di interi i seguenti valori:
0  se la pendenza - neutra (punto successivo - punto attuale < soglia)
+1 se la pendenza e' positiva (punto successivo - punto attuale > soglia)
-1  se la pendenza e' negativa (punto successivo - punto attuale < soglia)

vedi esempio dei risultati nel commento introduttivo
*/

int* calcola_pendenza(float* vett, int dim, float soglia)
{
}



int main(void)
{
    float* ingresso;    // array dei valori di input
    int* pendenza;      // array dei valori di uscita
    int    n, numero_elementi;
    float soglia;

    printf("Inserire il numero di elementi dell'array input: ");
    // Acquisire la dimensione dell'array nella variabile numero_elementi


    // Invocare la funzione acquisci_elevazione e verificare se l'array �
    // stato allocato


    // Stamoa dei valori acquisiti
    stampa_elevazioni(ingresso, numero_elementi); 
    
    printf("Inserire la soglia? ");
    // Acquisire la soglia (numero reale)

    // Invocare la funzione calcola_pendenza con i parametri corretti

    // Visualizzare il vettore contenente le pendenze e i dati di ingresso
    // nel formato (vedi esempio nel commento introduttivo):
    // primo punto del segmento, secondo punto pendenza

    // Disallocare la memoria allocata

    return 0;
}
