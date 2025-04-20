/*Un file contiene la raccolta di 10 frasi. 
Ogni frase è composta da un numero di parole generico.
Non si usano in queste frasi simboli separatori come l'apostrofo e non si utilizza nessun simbolo di 
interpunzione ad eccezione del punto che viene utilizzato come separatore fra una frase e la successiva.
Tutte le parole sono separate da uno spazio bianco (o da un ritorno a capo) e anche il punto è preceduto e 
seguito da uno spazio bianco o da un ritorno a capo.
Ogni frase è separata dalla successiva uffico vuole realizzare un sistema per il monitoraggio delle operazioni 
effettuate. 
Scrivere un programma C che effettui le seguenti operazioni:
1. Funzione Carica che consente di copiare il contenuto del file in un vettore di frasi. Ciascuna frase è una
realizzata come una lista di parole e stampa il contenuto della struttura presente in memoria centrale 
2.   Funzione che restituisce il numero di volte che compare una data parola (acquisita da console) in ciascuna 
delle frasi
3.  Funzione che restituisce la lunghezza della frase più breve e della frase più lunghezza
*/

//inserire qua le istruzioni di precompilazione necessarie
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DIM 10
#define LM 20

//definizione struttura dati

typedef struct n {
    char parola[LM];
    struct n* next;
}nodo, * lista;          

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
restituisce 0 se l’operazione è avvenuta con successo, 1 altrimenti*/
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

int lunghezza(lista L){
    int cont=0;
    while (L!=NULL){
        cont++;
        L=L->next;
    }
    return cont;
}


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
void quesito1(lista * vettoreListe){
    char nomefile [LM], parola[LM];
    FILE *fp;
    int indice =0;
    printf("\n inserisci il nome del file ");
    scanf("%s",nomefile);
    fp = fopen(nomefile,"r");
    if (fp==NULL) return;
    while(fscanf(fp,"%s",parola)==1)
        if(strcmp(parola,".")==0) indice++;
        else InserisciTestaLista(&vettoreListe[indice],parola);
}

//stampa il contenuto del vettore di liste

void stampaLista(lista L1){
    printf("\n");
    for (;L1!=NULL;L1=L1->next) printf("%s   ",L1->parola);
}

void stampaArchivio(lista *vettoreListe){
    for(int i=0;i<DIM;i++) 
        stampaLista(vettoreListe[i]);
}

//Funzione che restituisce il numero totale volte che compare una data parola

int occorrenze(lista L1, char *word){
    int i=0;
    while(L1!=NULL){
        if (strcmp(L1->parola,word)==0) i++;
        L1=L1->next;
    }
    return i;
}

int quesito2(lista * vettoreListe, char* word){
    int conta = 0;
    for (int i =0;i<DIM;i++)
        conta += occorrenze(vettoreListe[i],word);
    return conta;
}

//quesito3: restituire la lunghezza (numero di parole) della frase più breve e della frase più lunga
void quesito3(lista * vettoreListe, int *minL, int *maxL){
    *minL = INT_MAX;
    *maxL = 0;
    int size=0;
    for (int i =0;i<DIM;i++) {
        size = lunghezza(vettoreListe[i]);
        if (size>*maxL) *maxL=size;
        if (size<*minL) *minL=size;
    }
}

//main
int main(void) {
    lista archivio[DIM];  //archivio è il vettore di liste in cui copiare il contenuto del file
    //aggiungere definizione di eventuali altre variabili necessarie ed inizializzazioni
    int scelta = 0, minimo,massimo;
    for (int i=0;i<DIM;i++) 
        archivio[i]=makenullList(); //inizializza l'archivio vuoto
    char parola[LM];
    do {
        scelta = menu();
        switch (scelta) {
        case 1: quesito1(archivio) ;
            stampaArchivio(archivio);
            break;
        case 2: printf("inserisci la parola di cui vuoi calcolare il numero delle occorrenze");
            scanf("%s",parola);
            printf("il numero di occorenze di %s e' %d", parola, quesito2(archivio,parola));
            break;
        case 3: ; quesito3(archivio,&minimo,&massimo);
            printf("\nlunghezza minima %d, lunghezzza massima %d", minimo, massimo);
        }
    } while (scelta != 0);
}


