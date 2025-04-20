/******************************************************************************
Implementare una applicazione per la gestione del “carrello” in un sistema di acquisto online.
La struttura dati da utilizzare è una lista di articoli, 
ove ogni articolo è caratterizzato dai seguenti attributi (il codice è univoco):
- Codice (intero)
- Valore (in euro)
- Quantità (intero senza segno)
La lista di articoli è ordinata in base al campo Valore.
Implementare le seguenti funzioni:
1. creazione di una lista ordinata leggendo i dati dal file testo che contiene le informazioni 
una per riga e stampa del contenuto della lista.
2. modifica della quantita per un articolo selezionato attraverso il codice (passato come parametro di ingresso)
3. funzione che restituisce la lista degli articoli la cui quantità è minore di un valore fornito da console e passato come parametro alla funzione
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define LM 15

/*struttura lista */
typedef struct a{
    int codice, quantita;
    float valore;
} articolo;

typedef struct n{
    articolo info;
    struct n *next;
} t_nodo, *t_lista;

void crea_lista_vuota(t_lista *pL){
    *pL=NULL;
}

/* inserimento_ordinato: 
   inserisce un articolo in lista in maniera ordinata rispetto al campo valore */
int inserimento_ordinato(t_lista *pL, articolo A){
    t_lista aux,p,q;
    aux =(t_lista)malloc(sizeof(t_nodo));
    if (aux==NULL) return 0;
    aux->info=A;
    aux->next =NULL;
    if (*pL==NULL || (*pL)->info.valore>A.valore) {
        //inserimento in testa
        aux->next = *pL;
        *pL = aux;
    }
    else {
     //inserimento dell'elemnento in un posto diverso dal primo
	 // completare il codice
    return 1;
}

/* cerca:
   dato il codice, cerca un elemento e restituisce il puntatore all'elemento */
t_lista cerca(t_lista L, int codice){
  // ... da completare a cura dello studente ...
}

/* stampa:
   visualizza gli elementi della lista */
void stampa(t_lista L){
    printf("\n");
    while (L!=NULL){
        printf("codice = %d, valore = %f, quantita =%d \n",L->info.codice,L->info.valore,L->info.quantita);
        L=L->next;
    }
}

/*funzioni di utilita*/
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
/*quesito1:
  funzione che carica da file (il cui nome viene fornito come parametro) gli articoli in una lista ordinata in base al campo valore */
void quesito1(t_lista *pL, char *nomefile){
  // ... da completare a cura dello studente ...

}

/* quesito2:
   funzione che, dato in ingresso il codice di un articolo ed una quantità,
   permette di modificare la quantità dell'articolo selezionato.
   restituisce 0 se l'articolo non è stato trovato, 
   oppure 1 se la modifica è andata a buon fine */
int quesito2(/*argomenti della funzione*/){
  // ... da completare a cura dello studente ...
}

/* quesito3:
   funzione che restituisce la lista degli articoli la cui quantità è minore di un valore passato in ingresso come parametro*/

... quesito3(/*argomenti della funzione*/){
  // ... da completare a cura dello studente ...
}

//main
int main(void) {
    t_lista Archivio;  //Archivio è la lista in cui verranno caricati i dati del file
    int scelta = 0
	
	/* inserire le ulteriori variabili necessarie */
	
    crea_lista_vuota(&Archivio);
    do {
        scelta = menu();
        switch (scelta) {
        case 1: 
		  // Acquisire il nome del file
          // Invocare la funzione quesito1 
          // Visualizzare i dati caricati nella lista
			break;
        case 2: 
			// acquisire da console i valori necessari per il quesito 2
			//invocare la funzione quesito2
			// visualizzare un opportuno messaggio se l'aggiornamento è avvenuto con successo oppure no
            break;
        case 3: 
			// acquisire da console i valori necessari per il quesito 3
			// invocare la funzione quesito3
			// visualizzare i dati della lista restituita dalla funzione quesito3
        }
    } while (scelta != 0);
}
