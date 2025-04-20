/******************************************************************************

Scrivere un programma ANSI C che consente di leggere un stringa contenente anche caratteri bianchi. 
Calcola il numero di vocali minuscole presenti nella stringa e genera una nuova stringa 
uguale a quella letta ma nella quale sono state eliminate le vocali.

L'unica funzione utilizzabile della libreria string.h e' la funzione strlen()
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// La funzione contaVocali data una generica stringa conta il numero di volte che compare 
// ciascuna vocale e memorizza tali valori nel vettore. 
// Si suppone che la stringa contenga solo caratteri minuscoli
void contaVocali(char *stringa20, int *vettore){
		//da implementare
}

// La funzione cancellaVocali genera una nuova stringa newS uguale alla stringa in ingresso s 
// ma dalla quale sono state eliminate le vocali minuscole
void cancellaVocali(char *s,char * newS){
    //da implementare
}

int main() {
    
    char stringa20 [21];  
    //leggere una stringa di dimensione massima 20 caratteri
    printf("inserisci una stringa di al massimo 20 caratteri anche con caratteri bianchi");
    // leggere la stringa

    //allocare un vettore di cinque interi che possa contenere
    //il numero di ciascuna vocale presente nella stringa letta
    //utilizzare la funzione contaVocali per inserire i dati nel vettore
    
    //stampare per ciascuna vocale il numero di volte che è presente nella stringa 
    // ed il numero totali di vocali presenti
    
    
    //creare una seconda stringa uguale alla prima nella quale 
    //sono state cancellate le vocali minuscole
    //usare la funzione cancellaVocali
    

    //stampare la nuova stringa
    printf("%s",newString);

    //stampare la lunghezza della nuova stringa
    
    return 0;
}
