#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*
La funzione legge un vettore di numeri interi fino all'inserimento del valore 0 o il raggiungimento del numero massimo di elementi n. 
La funzione restituisce il numero dei valori effettivamente letti
*/
int lettura_dati(int* v, int n) 
{
	for (int i = 0; i < n; ++i) 
	{
		scanf("%d", &v[i]);
		if (v[i] == 0)
			return i;
	}
	return n;
}
/*
La funzione dato un vettore di ingresso che contiene valori diversi da zero restituisce un vettore contenente tutti i valori positivi presenti nel vettore di ingresso.
Il vettore deve essere allocato all’interno della funzione della dimensione esattamente uguale al numero di valori positivi presenti nel vettore di ingresso
la funzione restituisce (return) il vettore generato
dim è la dimensione del vettore di ingresso
vettoreIngresso è il vettore di ingresso
*dim2 consente di restituire la dimensione del vettore
*/
int* estrae_numeri_positivi(int* vettoreIngresso, int dim, int* dim2) 
{
	// Il codice deve essere inserito dallo studente
	int* vout = NULL;
	(*dim2) = 0;
	for (int i = 0; i < dim; i++) 
	{
		if (vettoreIngresso[i] > 0)
			(*dim2)++;
	}
	vout = (int*)malloc(sizeof(int) * (*dim2));
	int index = 0;
	for (int i = 0; i < dim; i++) 
	{
		if (vettoreIngresso[i] > 0)
			vout[index++] = vettoreIngresso[i];
	}
	return vout;
}
/*
La funzione stampa su console il contenuto di un vettore
*/
void stampa(int v[], int dim ) 
{
	// Il codice deve essere inserito dallo studente
	for (int i = 0; i < dim; i++) 
	{
		printf("v[%d] = %d\n", i, v[i]);
	}
}
int main(void) {
	int* v1 = NULL; // vettore allocato dinamicamente
	int* v2; // vettore allocato dinamicamente
	int dim; // dimensione del vettore v1
	int dim2;
	// Inserire il codice per implementare la lettura da tastiera del numero massimo di elementi inseribili nel vettore v1
	// Lettura da tastiera del primo vettore utilizzando la funzione lettura_dati
	do 
	{
		printf("Inserisci il numero max di elementi inseribili: ");
		scanf("%d", &dim);
	} while (dim <= 0);
	v1 = (int*)malloc(sizeof(int) * dim);
	dim = lettura_dati(v1, dim);
	// Lo studente deve chiamare la funzione estrae_numeri_positivi salvando i valori nel vettore v2 allocato
	// all’interno della funzione.
	v2 = estrae_numeri_positivi(v1, dim, &dim2);
	printf("Risultato estrazione:\n");
	// lo studente, usando la funzione stampa, stampa il risultato contenuto in v2
	stampa(v2, dim2);
	// disallocazione
	free(v1);
	free(v2);
}
