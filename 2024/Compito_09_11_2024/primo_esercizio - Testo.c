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
*		w	: vettore gi� allocato nel programma chiamante
*		dim	: dimensione del vettore
*	return:
*		numero di elementi effettivamente caricati (sempre <= dim)
*/
int acquisisci_dati(int* w, int dim) {
	// Completare la funzione
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

float* elabora_vettore(int* v1, int *v2, int n, int *dim) {
	// Completare la funzione
}

/*funzione che salva un vettore su un file testo*/
void salva(char* nomefile /*,inserire altri parametri*/)

/*
*	La funzione stampa il contenuto di un vettore
*	I parametri in ingresso devono essere definiti
*	dallo studente
*/
void stampa_vettore(/* inserire i parametri*/) {
}

int main(void) {
	int * v1,  * v2;
	int dim; //dimensione di v1 e v2
	float* v = NULL;
	int dimR;  //dimensione del vettore v3

	// 1. Inserire il codice necessario ad acquisire il valore verificando che sia >= 0
	printf("Inserire la dimensione del vettore da allocare: ");

	// 2. Allocare i vettori

	// 3. Chiamare la funzione acquisisci_dati, dichiarando se necessario le variabili
	// necessarie a gestire i valori restituiti per leggere i vettori v1 e v2

	//4. stampare v1 e v2

	// 5. Creare il vettore v3  dichiarando se necessario le variabili
	// necessarie a gestire i valori restituiti

	// 6. salvare su file testo il vettore v3 su in file con un nome scelto dall'utente


	// 7. liberare i vettori se necessario
}