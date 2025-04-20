/******************************************************************************

 Scrivere un programma ANSI C che consente di leggere, tramite la funzione AcquisisciVettore,
 una sequenza di numeri interi. Il programma deve memorizzare tutti i numeri letti in un vettore,
 la cui dimensione viene fornita dall'utente in fase di esecuzione.

 La funzione quadrato deve poi creare un secondo vettore dinamico che contenga il
 quadrato di ciascun numero positivo presente nel primo vettore.
 Tale funzione deve inoltre creare un terzo vettore di interi in cui ciascun elemento è 1
 se il corrispondente valore nel primo vettore è positivo, 0 altrimenti.
 Il valore di ritorno della funzione deve essere pari al numero di elementi positivi
 presenti nel primo vettore, ossia la dimensione del vettore dei quadrati.

 Infine il programma deve stampare a video i due vettori di output.

    Es.
    Vettore di input:    1 2 -3   4  -5
    Vettore di output 1: 1 4  16
    Vettore di output 2: 1 1  0   1   0

 Scaricare l'esercizio e completarlo inserendo il codice necessario senza modificare
 quello esistente tranne quando espressamente richiesto.
 L'esercizio si considera corretto se il programma compila correttamente ed esegue
 senza errori run-time dando i risultati attesi.

*******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* AcquisisciVettore
   Acquisisce un vettore di interi di dimensione n
   */
void AcquisisciVettore(int* v, int n) {
    // IMPLEMENTARE LA FUNZIONE
    for (int i = 0; i < n; i++) 
    {
        printf("Inserisci il valore %d: ", i);
        scanf("%d", &v[i]);
    }
}

/* Funzione quadrato
La funzione quadrato accetta in ingresso un vettore v di n interi e deve generare:
- quadrati: un vettore che contiene il quadrato di ciascun numero positivo presente nel vettore di ingresso v.
- positivi: un vettore in cui ciascun elemento è 1 se il corrispondente valore nel vettore v è positivo, 0 altrimenti.
La funzione restitusice il numero di elementi positivi del vettore v, ossia la dimensione del vettore quadrati.
*/
int quadrato(int v[], int n, int** quadrati, int** positivi) 
{
    // IMPLEMENTARE LA FUNZIONE
    (*positivi) = (int*)malloc(sizeof(int) * n);
    if ((*positivi) == NULL)
        return -1;
    (*quadrati) = (int*)malloc(sizeof(int) * n);
    if ((*quadrati) == NULL)
        return -1;
    int dim_q = 0;
    for (int i = 0; i < n; i++) 
    {
        if (v[i] > 0) 
        {
            (*positivi)[i] = 1;
            (*quadrati)[dim_q] = (v[i] * v[i]);
            dim_q++;
        }
        else 
        {
            (*positivi)[i] = 0;
        }
    }
    return dim_q;
}

/**** MAIN *****/
int main(void) {
    int n;
    int* v;
    int* quadrati;
    int* positivi;
    int dim_q;
    //leggere la dimensione del vettore e allocare il vettore verificando che la dimensione sia positiva
    do 
    {
        printf("Inserisci la dimensione: ");
        scanf("%d", &n);
    } while (n <= 0);
    //acquisire il contenuto del vettore
    v = (int*)malloc(sizeof(int) * n);
    if (v == NULL)
        return -1;
    AcquisisciVettore(v, n);
    //visualizzare il contenuto del vettore acquisito
    printf("\n-----------------\nVETTORE ACQUISITO:");
    for (int i = 0; i < n; i++)
        printf("%5d", v[i]);
    //utilizzando la funzione quadrato generare i i vettori "quadrati" e "positivi"
    dim_q = quadrato(v, n, &quadrati, &positivi);
    // visualizzare il vettore quadrati
    printf("\n-----------------\nVETTORE ACQUISITO:");
    for (int i = 0; i < dim_q; i++)
        printf("%5d", quadrati[i]);
    // visualizzare il vettore positivi
    printf("\n-----------------\nVETTORE ACQUISITO:");
    for (int i = 0; i < n; i++)
        printf("%5d", positivi[i]);

    return 0;
}
