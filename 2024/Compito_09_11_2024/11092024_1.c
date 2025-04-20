/*  ESERCIZIO 1  - Fondamenti di Informatica - Appello del 11/09/2024
**
**  Scaricare l'esercizio e completarlo inserendo il codice necessario
**  senza modificare quello esistente tranne quando espressamente
**  richiesto.
**
**  L'esercizio si considera corretto se il programma compila
**  correttamente ed esegue senza errori run-time dando i risultati
**  attesi.
**
**
*	Il programma deve acquisire due vettori v1 e v2 di uguale dimensione contenenti interi.
*   La dimensione è scelta dall'utente e i vettori devono essere allocati della dimensione
*   corretta dinamicamente.
*	Successivamente viene costruito un vettore che contiene valori reali che sono calcolati
*   dividento il doppio del valore del vettore v1 con il valore corrispondente del valore v2.
*   Se il vettore v2 contiene il valore zero il corrispondente valore v3 va omesso.
*   Pertanto il vettor v3 deve contenere solo gli elementi validi e quindi potrà avere
*   una dimensione che puo essere minore di quella dei vettori v1 e v2.
*   Salvare i valori del vettore v3 in un file testo inserendo un valore per ogni riga.
*	Al termine stampa il contenuto del vettore in ingresso e quello del vettore risultante
*	disallocando, se necessario, le risorse.
*
**	Esempio
*	dimensione dei vettori v1 v2: 10
*	valori immessi da tastiera per il vettore v1:
			[0]     = 4
			[1]     = 5
			[2]     = 1
			[3]     = 0
			[4]     = 0
			[5]     = 7
			[6]     = 12
			[7]     = 0
			[8]     = 9
			[9]     = 13
*valori immessi da tastiera per il vettore v2:
			[0]     = 2
			[1]     = 3
			[2]     = 0
			[3]     = 0
			[4]     = 0
			[5]     = 7
			[6]     = 1
			[7]     = 4
			[8]     = 5
			[9]     = 3
	vettore v3 risultante: dimensione 7
	valori risultato:
			[0]     = 4.00
			[1]     = 3.33
			[2]     = 2.00
			[3]     = 24.00
			[4]     = 0.00
			[5]     = 3.60
			[6]     = 8.66

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

/*
*	La funzione acquisisce una sequenza di valori reali positivi di dimensione
*	massima dim.
*   La funzione restituisce il numero di valori effettivamente letti da console
*	parametri:
*		w	: vettore già allocato nel programma chiamante
*		dim	: dimensione del vettore
*	return:
*		numero di elementi effettivamente caricati (sempre <= dim)
*/
int acquisisci_dati(int* w, int dim) 
{
	// Completare la funzione
	int i;
	for (i = 0; i < dim; i++) 
	{
		printf("Inserisci il valore %d: ", i);
		scanf("%d", &w[i]);
		if (w[i] < 0)
			i--;
	}
	return i;
}

/*
*	La funzione costruisce un vettore contenere solo gli elementi validi e quindi potrà avere
*   una dimensione che puo essere minore di quella dei vettori v1 e v2.
*	parametri:
*		v1, v2			: vettori in ingresso
*		n			: elementi dei vettori v1 e v2
*		dim 	: numero di valori del vettore risultato
*
*	return:
*		vettore contenente il risultato
*/

float* elabora_vettore(int* v1, int* v2, int n, int* dim) 
{
	// Completare la funzione
	(*dim) = 0;
	int dim_uscita = 0;
	for (int i = 0; i < n; i++) 
	{
		if (v2[i] > 0) 
		{
			dim_uscita++;
		}
	}
	float* vout = (float*)malloc(sizeof(float) * dim_uscita);
	if (vout == NULL)
		return NULL;
	for (int i = 0; i < n; i++) 
	{
		if (v2[i] > 0) 
		{
			vout[(*dim)++] = (float)(2 * v1[i]) / (float)(v2[i]);
		}
	}
	return vout;
}

/*funzione che salva un vettore su un file testo*/
void salva(char* nomefile, float v[], int dim) 
{
	FILE* fp = fopen(nomefile, "w");
	if (fp == NULL) return;
	for (int i = 0; i < dim; i++) 
	{
		fprintf(fp, "%f\n", v[i]);
	}
}

/*
*	La funzione stampa il contenuto di un vettore
*	I parametri in ingresso devono essere definiti
*	dallo studente
*/
void stampa_vettore(float v[], int dim)
{
	printf("\n-----------------\n");
	for (int i = 0; i < dim; i++)
		printf("v[%d] = %.2f\n", i, v[i]);
}

int main(void) {
	int* v1, * v2;
	int dim; //dimensione di v1 e v2
	float* v = NULL;
	int dimR;  //dimensione del vettore v3
	char NomeFile[64];

	// 1. Inserire il codice necessario ad acquisire il valore verificando che sia >= 0
	do
	{
		printf("Inserire la dimensione del vettore da allocare: ");
		scanf("%d", &dim);
	} while (dim <= 0);

	// 2. Allocare i vettori
	v1 = (int*)malloc(sizeof(int) * dim);
	if (v1 == NULL)
		return 0;
	v2 = (int*)malloc(sizeof(int) * dim);
	if (v2 == NULL)
		return 0;
	// 3. Chiamare la funzione acquisisci_dati, dichiarando se necessario le variabili
	// necessarie a gestire i valori restituiti per leggere i vettori v1 e v2
	dim = acquisisci_dati(v1, dim);
	dim = acquisisci_dati(v2, dim);
	//4. stampare v1 e v2
	printf("\n------------------\n");
	for (int i = 0; i < dim; i++)
		printf("v[%d] = %d\n", i, v1[i]);
	printf("\n------------------\n");
	for (int i = 0; i < dim; i++)
		printf("v[%d] = %d\n", i, v2[i]);
	printf("\n------------------\n");
	// 5. Creare il vettore v3  dichiarando se necessario le variabili
	// necessarie a gestire i valori restituiti
	v = elabora_vettore(v1, v2, dim, &dimR);
	// 6. salvare su file testo il vettore v3 su in file con un nome scelto dall'utente
	printf("Inserisci il nome del file: ");
	scanf("%s", NomeFile);
	salva(NomeFile, v, dimR);

	// 7. liberare i vettori se necessario
	free(v1);
	free(v2);
	free(v);
}