/*
Esercizio A4
Scrivere un programma in linguaggio C che riceve in ingresso una sequenza di N numeri interi. Il valore N è inserito dall’utente e deve essere minore di 20.
I numeri sono memorizzati in un vettore. Il programma esegue le seguenti operazioni:
1. visualizza il vettore
2. esegue uno spostamento (shift) a sinistra di una posizione del contenuto del vettore.
Pertanto ogni elemento del vettore deve assumere il valore dell’elemento immediatamente successivo all’interno del vettore.
L’elemento di indice N-1 deve assumere il valore zero. Ad esempio dato il vettore: 1 10 15 18 Il programma deve generare il vettore: 10 15 18 0 
Il programma visualizza il vettore ottenuto.
3. esegue uno spostamento (shift) a destra di una posizione del contenuto del vettore ottenuto nel passo precedente. 
Pertanto ogni elemento del vettore deve assumere il valore dell’elemento immediatamente precedente all’interno del vettore. 
L’elemento di indice 0 deve assumere il valore zero. Ad esempio dato il vettore: 10 15 18 0 Il programma deve generare il vettore: 0 10 15 18 
Il programma visualizza il vettore ottenuto.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void VisualizzaVettore(int v[], int dim) 
{
	printf("-------------VETTORE RISULTANTE--------------\n");
	for (int i = 0; i < dim; i++) {
		printf("%5d", v[i]);
	}
}

int* InserisciValori(int dim)
{
	int* v = malloc(sizeof(int) * dim);
	for (int i = 0; i < dim; i++) 
	{
		printf("Inserisci il valore %d: ", i);
		scanf("%d", &v[i]);
	}
	return v;
}

int main()
{
	int* v;
	int dim;
	do {
		printf("Inserisci la dimensione(>0): ");
		scanf("%d", &dim);
	} while ((dim < 0) && (dim>20));

	v = InserisciValori(dim);

	VisualizzaVettore(v, dim);

	int scelta;
	printf("\nEsegui lo shift del vettore (0 destra, 1 sinistra): ");
	scanf("%d", &scelta);
	if (scelta == 1) 
	{
		for (int i = 0; i < dim; i++) 
		{
			v[i] = v[i + 1];
			if (i == dim - 1) 
			{
				v[i] = 0;
			}
		}
	}
	else 
	{
		for (int i = (dim - 1); i >= 0; i--)
		{
			v[i] = v[i - 1];
			if (i == 0)
				v[i] = 0;
		}
	}
	if (scelta != 1 && scelta != 0) {
		return -1;
	}
	VisualizzaVettore(v, dim);
}