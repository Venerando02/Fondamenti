/*
Un file contiene una raccolta di 10 frasi (il file contiene esattamente 10 frasi).
Ogni frase � composta da un numero di parole generico.
Non si usano in queste frasi simboli separatori come l'apostrofo e non si utilizza nessun simbolo di
interpunzione ad eccezione del punto che viene utilizzato come separatore fra una frase e la successiva.
Tutte le parole sono separate da uno spazio bianco (o da un ritorno a capo) e anche il punto � preceduto e
seguito da uno spazio bianco o da un ritorno a capo.

Scrivere un programma C che effettui le seguenti operazioni:
1. Funzione Carica che consente di copiare il contenuto del file in un vettore di frasi. Ciascuna frase � 
realizzata come una lista di parole;
2. Funzione che restituisce il numero di volte che compare una data parola (passata come argomento in ingresso) in ciascuna
delle frasi
3. Funzione che restituisce la lunghezza (numero di parole) della frase pi� breve e della frase pi� lunga
*/
#define _CRT_SECURE_NO_WARNINGS
//inserire qua le istruzioni di precompilazione necessarie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DIM 10  //numero delle frasi contenute nel file
#define LM 20   //lunghezza stringhe

//definizione struttura dati lista

typedef struct n {
    char parola[LM];
    struct n* next;
}nodo, *lista;

/***** Funzioni primitive per uso lista1 ******/

//makenullList restituisce la lista vuota
lista makenullList() {
    return NULL;
}
//test lista vuota
int emptyLista(lista l) {
    if (l == NULL) return 1;
    return 0;
}
/*InserisciTestaLista: permette di inserire un elemento (parola) in testa alla lista; 
restituisce 0 se l�operazione � avvenuta con successo, 1 altrimenti*/
int InserisciTestaLista(lista* plis, char* word) {
    lista paux;

    if ((paux = (lista)malloc(sizeof(nodo))) == NULL) {
        printf("Errore: impossibile allocare memoria");
        return 1;
    }
    strcpy(paux->parola, word);
    paux->next = *plis;
    *plis = paux;

    return 0;
}

/*funzione che restituisce il numero di elementi contenuti nella lista*/
int lunghezza(lista L) {
    int cont = 0;
    while (L != NULL) {
        cont++;
        L = L->next;
    }
    return cont;
}

/*funzione per la gestione del menu*/
int menu(void) {
    int scelta;
    printf("\n 1) esegui quesito 1");
    printf("\n 2) esegui quesito 2");
    printf("\n 3) esegui quesito 3");
    printf("\n 0) esci dal programma");
    scanf("%d", &scelta);
    return scelta;
}


//definizione dei quesiti
/* 
quesito 1, consente il carimamente delle informazioni presenti nel file
in un vettore di liste. 
Il nome del file � acquisito all'interno della funzione
La funzion restituisce un tipo void
*/
void quesito1(/*inserire gli argomenti della funzione*/) {
    char nomefile[LM], parola[LM];
    FILE* fp;
    int indice = 0;
    printf("\n inserisci il nome del file ");
    scanf("%s", nomefile);
    fp = fopen(nomefile, "r");
    if (fp == NULL) return;
    /* lettura del file e trasferimento dei dati nel vettore di liste */
}

//stampaLista: la funzione stampa il contenuto di una lista
void stampaLista(lista L1) {
    printf("\n");
    for (; L1 != NULL; L1 = L1->next) 
        printf("%s ", L1->parola);
}

//stampaArchivio: la funzione deve stampare il contenuto del vettore di liste
void stampaArchivio(lista* vettoreListe) {
    /*scrivere l'implementazione della funzione* */
}

//occorrenze: Funzione che restituisce il numero totale di volte che una data parola compare in una frase
int occorrenze(lista L1, char* word) {

}

int quesito2(lista* vettoreListe, char* word) {
    int conta = 0;
    for (int i = 0; i < DIM; i++)
        conta += occorrenze(vettoreListe[i], word);
    return conta;
}

//quesito2: restituire la lunghezza (numero di parole) della frase pi� breve e della frase pi� lunga
void quesito3(/*inserire i parametri*/) {

}

//main
int main(void) {
    lista archivio[DIM];  //archivio � il vettore di liste in cui copiare il contenuto del file
    //aggiungere definizione di eventuali altre variabili necessarie ed inizializzazioni
    int scelta = 0, minimo, massimo;
    for (int i = 0; i < DIM; i++)
        archivio[i] = makenullList(); //inizializza l'archivio vuoto
    char parola[LM];
    do {
        scelta = menu();
        switch (scelta) {
        case 1: 
            quesito1(/*argomenti della funzione*/);
            stampaArchivio(archivio);
            break;
        case 2: 
            printf("inserisci la parola di cui vuoi calcolare il numero delle occorrenze");
            scanf("%s", parola);
            //aggiungere la chiamata della funzione quesito 2 e la stampa dei risultati
            break;
        case 3: 
            quesito3(/*inserire argomenti*/);
            printf("\nlunghezza minima %d, lunghezzza massima %d", minimo, massimo);
        }
    } while (scelta != 0);
}