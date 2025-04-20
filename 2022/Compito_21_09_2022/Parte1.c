/*
  Scaricare l'esercizio e completarlo inserendo il codice necessario
  senza modificare quello esistente tranne quando espressamente
  richiesto.

  L'esercizio si considera corretto se il programma compila
  correttamente ed esegue senza errori run-time dando i risultati
  attesi.

  TESTO
  =====
  Acquisire un vettore di float 'vett'. Creare un nuovo array inserendo un nuovo valore ogni coppia
  di numeri pari al valor medio .

  ESEMPIO INPUT/OUTPUT
  ====================
  Dimensione del vettore da acquisire: 5
  Valori acquisiti da console: 10.50 5.00 -20.40 8.00 0.00
  Vettore risultante dopo la trasformazione (tra parentesi i valori aggiunti):
  10.50 (7.75) 5.00 (-7.70) -20.40 (-6.20) 8.00 (4.00) 0.00
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
La funzione carica alloca un vettore di float di dimensione n e legge i valori dalla console.
parametri:
	int n	: numero di valori da leggere/ dimensione del vettore
	return	: vettore di float che contiene i valori letti
*/

float* carica(int n)
{
	// A cura dello studente
	float* vettore = malloc(sizeof(float) * n);
	for (int i = 0; i < n; i++)
	{
		printf("Inserisci il valore %d: ", i);
		scanf("%f", &vettore[i]);
	}
	return vettore;
}

/*
La funzione espandi inserisce un nuovo valore ogni coppia di numeri (vedi esempio nell'introduzione) aggiungendo
il valor medio degli estremi
parametri:
	float v[]	: vettore in ingresso
	int n		: dimensione del vettore in ingresso
	int *m		: dimensione del vettore risultante
	return		: vettore risultante
*/
float* espandi(float v[], int n, int* m)
{
	// A cura dello studente
	*m = n + (n - 1);
	int dim = *m;
	float* v_out = malloc(sizeof(float) * dim);
	int index = 0;
	int j = 0;
	while (index < dim) 
	{
		v_out[index] = v[j];
		index++;
		j++;
		if (index % 2 != 0 && j<=(n-1)) 
		{
			v_out[index] = ((v[j] + v[j - 1]) / 2.0F);
			index++;
		}
	}
	return v_out;
}

/*
La funzione stampa stampa il contenuto di un vettore di float in cui ogni elemento è approssmato
alla seconda cifra decimale
parametri:
	float v[]	: vettore in ingresso
	int n		: numero di elementi
	return		: non previsto
*/
void stampa(float v[], int n) {
	for (int i = 0; i < n; ++i)
		printf("%.2f\n", v[i]);
}

int main(void)
{
	// Chiede all'utente le dimensioni del vettore, controllando che il valore sia compreso fra 1 e 50 
	int dim, dim_out;
	float* v_in;
	float* v_out;
	// Inserire il codice
	printf("Inserisci la dimensione del vettore: ");
	scanf("%d", &dim);
	if ((dim < 1) && (dim > 50))
	{
		printf("La dimensione del vettore deve essere compresa tra 1 e 50.");
		return -1;
	}
	// chiama la funzione di lettura e stampa il vettore acquisito
	// Inserire il codice
	v_in = carica(dim);
	stampa(v_in, dim);

	// chiama la funzione espandi e stampa il risultato
	// Inserire il codice
	v_out = espandi(v_in, dim, &dim_out);
	printf("----------VETTORE FINALE----------\n");
	stampa(v_out, dim_out);
	// libera la memoria allocata
	// Inserire il codice
	free(v_in);
	free(v_out);
}