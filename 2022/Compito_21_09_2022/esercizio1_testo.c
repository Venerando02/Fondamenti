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

/*
La funzione carica alloca un vettore di float di dimensione n e legge i valori dalla console.
parametri:
	int n	: numero di valori da leggere/ dimensione del vettore
	return	: vettore di float che contiene i valori letti
*/

float* carica(int n) {
	// A cura dello studente
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
float* espandi(float v[], int n, int* m) {
	// A cura dello studente
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
# 
int main(void) {
	// Chiede all'utente le dimensioni del vettore, controllando che il valore sia compreso fra 1 e 50 
	int dim;

	// Inserire il codice

	// chiama la funzione di lettura e stampa il vettore acquisito

	// Inserire il codice

	// chiama la funzione espandi e stampa il risultato

	// Inserire il codice

	// libera la memoria allocata

	// Inserire il codice
}