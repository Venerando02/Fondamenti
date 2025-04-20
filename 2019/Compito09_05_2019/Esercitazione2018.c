#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void LeggiVettore(int* v, int n) 
{ 
	for (int i=0; i<n; i++) 
	{
		printf("Inserisci elemento di posizione %d: ", i);
		scanf("%d", &v[i]); 
	} 
}
/* 
Restituisce un vettore di n elementi. L’elemento di posizione i è la somma degli elementi di posizione da i a n-1 di v.
Cioè detto w il vettore da restituire, w[i] = v[i]+v[i+1]+…+v[n-1] 
*/

int* SommaElementi(int* v, int n) 
{
	int * vout = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)
		vout[i] = 0;
	int somma = 0;
	int i = 0;
	int j = 0;
	while (i < n) 
	{
		j = 0;
		while (j < n) 
		{
			vout[i] += v[j];
			j++;
		}
		i++;
	}
	return vout;
} 


// Visualizza gli elementi di un array passato come parametro  void Visualizza(...) {...}

void Visualizza(int v[], int dim) 
{
	printf("VETTORE RISULTANTE:\n");
	for (int i = 0; i < dim; i++) 
	{
		printf("v[%d] = %d\n", i, v[i]);
	}
}

int main(void) 
{ 
	int *vett1, *vett2; 
	int dim;
	vett1 = vett2 = NULL;
	do 
	{
		printf("Inserisci la dimensione del vettore: ");
		scanf("%d", &dim);
	} while (dim <= 0);
	// Assicurarsi che dim sia un numero >0 e se non lo è ripetere l’inserimento vett1 = ...;
	vett1 = (int*)malloc(sizeof(int) * dim);
	if (vett1 == NULL)
		return 1;
	LeggiVettore(vett1, dim);
	// Alloca un array di 'dim' elementi interi LeggiVettore(...); 

	// Acquisisce gli elementi in vett1 vett2 = SommaElementi(...); Visualizza(...); 
	// Visualizza vett2 ...;
	vett2 = SommaElementi(vett1, dim);
	Visualizza(vett2, dim);
	// Disalloca vett1 ...;
	// Disalloca vett2 
	free(vett1);
	free(vett2);
	return 0; 

}  