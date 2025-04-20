/*
Scrivere un programma in ANSI C che, dato un file di testo che contiene in ogni riga una coppia di numeri reali, esegua le seguenti operazioni:
1. Carichi in un array di numeri reali la media aritmetica di ogni coppia 
(ad esempio, se la coppia è 2.3 e 1.7, carica nell’array 2.0 perché la loro media aritmetica è 2).
2. Visualizzi gli elementi dell’array compresi tra un minimo ed un massimo (dove minimo e massimo sono acquisiti da tastiera e gli estremi dell’intervallo sono compresi).
3. Visualizzi l’elemento massimo e la sua posizione all’interno dell’array.
4. Salvi nel file “uscita.txt” gli elementi dell’array
Specifiche:
- La dimensione dell’array è N pari a 10
- Il nome del file di ingresso deve essere inserito da input.
- Il numero di righe (cioè di coppie) nel file non è noto all’inizio. Eventuali coppie di elementi nel file oltre la riga N-esima (cioè oltre la decima riga) non devono essere prese in considerazione
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

int Menu() 
{
	int scelta;
	printf("********* MENU ***********\n"
		"1. Carica numeri reali dentro l'array.\n"
		"2. Visualizza elementi array tra minimo e massimo.\n"
		"3. Visualizza il massimo e la sua posizione.\n"
		"4. Salva dati nel file 'uscita.txt'.\n\n"
		">>> "
	);
	scanf("%d", &scelta);
	return scelta;
}

int CaricaDatiFile(char * NomeFile, float v[])
{
	FILE* fp = fopen(NomeFile, "r");
	if (fp == NULL)
		return -1;
	float valore1, valore2;
	float media;
	int index = 0;
	while (fscanf(fp, "%f%f", &valore1, &valore2) == 2) 
	{
		media = (valore1 + valore2) / 2;
		v[index] = media;
		index++;
	}
	fclose(fp);
	return index;
}

void InserisciValoreMinimoMassimo(float v[], int dim, float minimo, float massimo) 
{
	for (int i = 0; i < dim; i++) 
	{
		if ((v[i] > minimo) && (v[i] < massimo)) 
		{
			printf("VALORE : %.3f\n", v[i]);
		}
	}
}

int RicercaMassimo(float v[], int dim) 
{
	if (dim == 0)
		return -1;
	int posizione = 0;
	for (int i = 0; i < dim; i++) 
	{
		if (v[i] > v[posizione])
			posizione = i;
	}
	return posizione;
}

int SalvaElementi(float v[], int dim, char * NomeFile) 
{
	FILE* fp = fopen(NomeFile, "w");
	if (fp == NULL)
		return -1;
	int n = 0;
	for (int i = 0; i < dim; i++) 
	{
		if (!fprintf(fp, "%f\n", v[i]))
			return -1;
		else
			n++;
	}
	fclose(fp);
	return n;
}

void VisualizzaVettore(float v[], int dim) 
{
	printf("Vettore risultante: ");
	for (int i = 0; i < dim; i++) 
	{
		printf("%10.2f", v[i]);
	}
	printf("\n");
}


int main() 
{
	int scelta;
	char NomeFile[64];
	float v[N] = { 0.0 };
	int NumElementi;
	int n;
	float minimo, massimo;
	int pos;
	do 
	{
		scelta = Menu();
		switch (scelta)
		{
		case 1:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			NumElementi = CaricaDatiFile(NomeFile, v);
			if (NumElementi != -1) 
			{
				printf("Sono stati caricati %d elementi.\n", NumElementi);
				VisualizzaVettore(v, NumElementi);
			}
			break;
		case 2:
			if (NumElementi != -1) 
			{
				printf("Inserisci un valore minimo: ");
				scanf("%f", &minimo);
				printf("Inserisci un valore massimo: ");
				scanf("%f", &massimo);
				InserisciValoreMinimoMassimo(v, NumElementi, minimo, massimo);
			}
			break;
		case 3:
			pos = RicercaMassimo(v, NumElementi);
			printf("Il massimo si trova in posizione %d e con il valore %.3f.\n", pos+1, v[pos]);
			break;
		case 4:
			printf("Inserisci il nome del file: ");
			scanf("%s", NomeFile);
			n = SalvaElementi(v, NumElementi, NomeFile);
			if (n != -1)
				printf("Sono stati caricati %d elementi.\n", n);
			break;
		}
	} while (scelta != 0);

}