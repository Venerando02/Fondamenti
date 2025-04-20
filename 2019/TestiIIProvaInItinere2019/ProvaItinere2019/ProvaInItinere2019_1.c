#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
La funzione legge un vettore di numeri interi positivi da tastiera fino all'inserimento del valore 0 o il raggiungimento del numero massimo di elementi n.
Restituisce il numero dei valori effettivamente letti
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
La funzione dato un vettore di ingresso che contiene interi positivi restituisce i valori strettamente maggiori della soglia nel vettore w
v: vettore di ingresso
w: vettore di uscita (allocato nel main)
m: numero di elementi dei vettori v, w
soglia: soglia
la funzione restituisce (return) è uguale al il numero di elementi significativi presenti in w
*/
int estrae_numeri_maggiori_di(const int* v, int* w, int m, int soglia)
{
	// Il codice deve essere inserito dallo studente
	int dim2 = 0;
	for (int i = 0; i < m; i++) 
	{
		if (v[i] > soglia) 
		{
			dim2++;
		}
	}
	int index = 0;
	for (int i = 0; i < m; i++) 
	{
		if (v[i] > soglia)
		{
			w[index++] = v[i];
		}
	}
	return dim2;
}
/* La funzione stampa su console il contenuto del vettore */
void stampa(int v[], int dim)
{
	// Il codice deve essere inserito dallo studente
	printf("Vettore Risultante: ");
	for (int i = 0; i < dim; i++) 
	{
		printf("%3d", v[i]);
	}
}
#define DIMENSIONE 10
int main(void) {
	int v1[DIMENSIONE]; // vettore allocato staticamente
	int* v2; // vettore allocato dinamicamente
	int dim; // dimensione del secondo vettore
	int dim2;
	int s;
	// Lettura da tastiera del primo vettore utilizzando la funzione lettura_dati
	dim = lettura_dati(v1, DIMENSIONE);
	/*
	Lo studente deve allocare dinamicamente il secondo vettore in modo che
	abbia tanti elementi quanti sono i valori letti nella funzione precedente.
	*/
	// inserire il codice corretto per allocare il secondo vettore usando la
	// funzione malloc:
	/*
	Lo studente deve chiamare la funzione estrae_numeri_maggiori_di salvando
	i valori nel vettore w precedentemente allocato.
	*/
	v2 = (int*)malloc(sizeof(int) * dim);
	if (v2 == NULL)
		return 0;
	printf("inserire una soglia: ");
	scanf("%d", &s);
	dim2 = estrae_numeri_maggiori_di(v1, v2, dim, s);
	/*
	lo studente, usando la funzione stampa, stampa il risultato contenuto
	in v2
	*/
	stampa(v2, dim2);
	// disallocazione
	free(v1);
	free(v2);
}