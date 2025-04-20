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
  La funzione AcquisisciArray alloca un array di dim
  elementi e acquisisce i valori float che verranno inseriti nell'array
  
 */
float* AcquisisciArray(int dim){
  float* vettore;

  vettore = (float*)malloc(dim * sizeof(float));
  if (vettore != NULL){
      for (int i=0; i<dim; i++) {
	  printf("Inserisci l'elemento %d: ", i);
	  scanf("%f", &vettore[i]);
      }
  }
  return vettore;
}

/*la funzione genera dato un vettore di dim elementi crea un nuovo vettore che contiene la somma del primo elemento con l'ultimo elemento,
la somma del secondo con il penultino e cosi via. Se il numero di elementi è dispari per l'elemento centrale viene inserito lo stesso
elemento
La funzione restituisce il vettore che è stato creato e la dimensione del nuovo vettore*/
float * genera(/*inserire i parametri formali*/){
      
      
      /*inserire l'implementazione
      return V;
  }


/*
  La funzione VisualizzaValori visualizza il contenuto di un vettore di float di dim elementi
 */
void VisualizzaValori(float* vettore, int dim)
{
  for (int i=0; i<dim; i++)
    printf("%f\n", vettore[i]);
}

int main(void)
{
  float* vettore;
  float* vettoreNew;
  int dimV;
  int dimNew;
  
  
  /*acquisire la dimensione del vettore */
  
  /*allocare il vettore e inizializzarlo */
  
  /*stampare il contenuto del vettore*/
  
  /*usare la funzione genera per creare il vettoreNw*/
  
  /*stampare il contenuto del vettoreNew*/
  

 
  /*liberare la memoria occupata dai due vettori*/
  
  return 0;
}