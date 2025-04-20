/******************************************************************************

Scrivere un programma ANSI C che consente di leggere un stringa contenente anche caratteri bianchi.
Calcola il numero di vocali presenti nella stringa e genera una nuova stringa uguale a quella letta
ma nella quale sono state eliminate le vocali minuscole

L'unica funzione utilizzabile della libreria string.h e la funzione strlen
*******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// La funzione contaVocali data una generica stringa conta il numero di volte che compare 
// ciascuna vocale e memorizza tali valori nel vettore. 
// Si suppone che la stringa contenga solo caratteri minuscoli
void contaVocali(char* stringa20, int* vettore) {
    for (int i = 0; i < 5; i++) vettore[i] = 0;
    for (int i = 0; stringa20[i] != '\0'; i++) 
    {
        if (stringa20[i] == 'a')
            vettore[0]++;
        if (stringa20[i] == 'e')
            vettore[1]++;
        if (stringa20[i] == 'i')
            vettore[2]++;
        if (stringa20[i] == 'o')
            vettore[3]++;
        if (stringa20[i] == 'u')
            vettore[4]++;
    }
}

// La funzione cancellaVocali genera una nuova stringa newS uguale alla stringa s 
// ma dalla quale sono state eliminate le vocali minuscole
void cancellaVocali(char* s, char* newS) 
{
    int i, j;
    i = 0;
    j = 0;
    while (s[i] != '\0') 
    {
        if (s[i] == 'a')
            i++;
        else if (s[i] == 'e')
            i++;
        else if (s[i] == 'i')
            i++;
        else if (s[i] == 'o')
            i++;
        else if (s[i] == 'u')
            i++;
        else 
        {
            newS[j] = s[i];
            j++;
            i++;
        }
    }
    newS[j] = s[i];
}

int main() {

    char stringa20[21];  //
    //leggere una stringa di dimensione massima 20 caratteri
    printf("inserisci una stringa di al massimo 20 caratteri anche con caratteri bianchi: ");
    fgets(stringa20, 20, stdin);  //

    //allocare un vettore di cinque interi che possa contenere
    //il numero di ciascuna vocale presente nella stringa letta
    //utilizzare la funzione contaVocali per inserire i dati nel
    //vettore
    int vettore[5];
    contaVocali(stringa20, vettore);

    // stampare per ciascuna vocale il numero di volte che è presente nella stringa 
    // ed il numero totali di vocali presenti
    int tot = 0;
    for (int i = 0; i < 5; i++) 
    {
        tot += vettore[i];
    }
    printf("La lettera 'a' e' presente %d volte.\n", vettore[0]);
    printf("La lettera 'e' e' presente %d volte.\n", vettore[1]);
    printf("La lettera 'i' e' presente %d volte.\n", vettore[2]);
    printf("La lettera 'o' e' presente %d volte.\n", vettore[3]);
    printf("La lettera 'u' e' presente %d volte.\n", vettore[4]);

    //creare una seconda stringa uguale alla prima nella quale 
    //sono state cancellate le vocali 
    //usare la funzione cancellaVocali
    char* newString = (char*)malloc(sizeof(char) * ((strlen(stringa20)-tot)+1));
    cancellaVocali(stringa20, newString);

    //stampare la nuova stringa
    //stampare la lunghezza della nuova stringa
    printf("%s", newString);

    printf("%d", strlen(newString));
    return 0;
}
