/*
*
* Scrivere un programma in ANSI C che
* 1.    conta le eventuali lettere ripetute (doppie, triple, e..)
*       presenti in una stringa che può contenere caratteri bianchi (spazio) letta da console (ad esempio data
*       la stringa "sequenza con doppie, trrriple e quaaaadruple" il numero risultante e' 6 e la stringa viene
*       modificata in "sequenza con dopie, triple e quadruple". Nota che il conteggio rigyarda solo il numero 
*       eventuali ripetizioni e quindi non comprende la prima lettera, ad esempio nella parola doppie il numero
*       di ripetizioni è pari ad 1 (dopPie), nella parola trrriple il numero di ripetizioni è 2 (trRRiple) e 
*       parola quaaaadruple è 3 (quaAAAdruple).
* 2.    copia in una seconda stringa allocata nel corpo di una funzione la sringa senza le ripetizioni, 
*       ad esempio se la strtinga sorgente è la stringa "sequenza con doppie, trrriple e quaaaadruple" 
*       il risultato è la stringa "sequenza con dopie, triple e quadruple" 
*       N.B. il carattere minuscole è diverso da quello maiuscolo.
* L'unica funzione utilizzabile della libreria string.h e' la funzione strlen()
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int conta_numero_sequenze(const char* s) {
}

char* copia_senza_ripetizioni(const char* s) {
}

int main() {

    //leggere una stringa la cui massima dimensione e' 100 caratteri (compreso il fine stringa)
    char stringa[ ???? ];

    printf("inserisci una stringa (sono ammessi anche i caratteri bianchi): ");
    // Scrivere il codice necessario a leggere una stringa che possa contenere anche
    // caratteri bianchi (spazio)
    
    // Calcolare il numero di sequenze di caratteri ripetuti presenti nella stringa in ingresso
    // usando la funzione conta_numero_sequenze(stringa)
    int numero_ripetizioni;
    // Inserire il codice necessario a risolvere il problema
    
    printf("Numero di ripetizioni: %d\n", numero_ripetizioni);

    // Creare una nuova stringa che elimini le sequenze di caratteri ripetuti usando la funzione
    // copia_senza_ripetizioni(stringa)
    char* r = NULL;
    // Inserire il codice necessario a risolvere il problema

    printf("Stringa risultante: <%s>\n", r);

    // deallocazione
}
