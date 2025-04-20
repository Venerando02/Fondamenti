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
  La funzione AcquisisciCoefficienti alloca un array di grado+1
  elementi e acquisisce i coefficienti del polinomio di grado
  'grado'
 */
float* AcquisisciCoefficienti(int grado)
{
  float* coeff;

  coeff = (float*)malloc((grado+1) * sizeof(float));
  if (coeff != NULL)
    {
      for (int i=0; i<grado; i++)
	{
	  printf("Inserisci il corfficiente di grado %d: ", i);
	  scanf("%f", &coeff[i]);
	}
      
    }
  
  return coeff;
}

/*
  La funzione Eleva restituisce 'x' elevato a 'n'. Si assuma n >= 0
 */
float Eleva(float x, int n)
{
  float p = 1;

  for (int i=0; i<n; i++)
    p *= x;
  
  return p;
}


/*
  La funzione ValutaPolinomioX valuta un polinomio di grado 'grado'
  con coefficienti 'coeff' nel punto 'x' 
*/
float ValutaPolinomioX(float x, int grado, float* coeff)
{
  float y = 0;

  for (int i=0; i<=grado; i++)
    y += coeff[i] * Eleva(/* specificare i parametri attuali */);

  return y;
}

/*
  La funzione ValutaPolinomio restitusce un vettore contente i valori
  del polinomio con coefficienti 'coeff' valutato in 'npunti'
  uniformemente distribuiti all'interno dell'intervallo [min max]. 
  Per calcolare npunti distribuiti uniformemente tra min e max, 
  basta procedere con passo (max-min)/npunti a partire da min
  per npunti volte.
 */
float* ValutaPolinomio(float min, float max, int npunti, int grado,
		       float* coeff)
{
  /* Implementare la funzione */
}

/*
  La funzione VisualizzaValori visualizza gli 'npunti' valori del
  vettore 'polinomio'
 */
void VisualizzaValori(float* polinomio, int npunti)
{
  for (int i=0; i<npunti; i++)
    printf("%f\n", polinomio[i]);
}

int main(void)
{
  float* coefficienti;
  float* polinomio;
  float  min, max;
  int    grado, npunti;

  // Questo programma valuta un polinomio di grado qualiasi in un
  // numero di punti all'interno di un intervallo fornito dall'utente.

  printf("Grado del polinomio: ");
  scanf("%d", &grado); // il polinomio avrà grado+1 coefficienti

  coefficienti = AcquisisciCoefficienti(/* parametri attuali */);
  if (coefficienti == NULL)
    return 1; // esce se non riesce ad allocare l'array dei coefficienti
  
  printf("Intervallo di varizione di x (min, max): ");
  scanf("%f %f", &min, &max);

  printf("In quanti punti vuoi valutare il polinomio? ");
  scanf("%d", &npunti);
  
  polinomio = ValutaPolinomio(/* parametri attuali */);
  if (polinomio == NULL)
    return 1; // esce se non riesce ad allocare l'array dei punti del polinomio
  
  VisualizzaValori(/* parametri attuali */);

  free(coefficienti);
  free(polinomio);
  
  return 0;
}
