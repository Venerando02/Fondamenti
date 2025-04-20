/*

 In un file sono memorizzati il risultato di alcune partite di calcio.
 Per ogni partita sono memorizzati
 - nome squadra 1 (senza spazi bianchi)
 - nome squadra 2 (senza spazi bianchi)
 - numero goal segnati nella prima squadra
 - numero goal segnati dalla seconda squadra.
 
Implementare un programma in ANSI C che contiene le seguenti funzioni:
1)  CaricaDaFile: lettura e caricamento dei dati contenuti nel file nella lista_partite.  
    La funzione deve inoltre restituire il numero di elementi letti e caricati nella lista;
2)  ElencoSquadre: funzione che restituisce un vettore contenente l'elenco delle squadre;
3)  PartiteSquadra: funzione che dato il nome di una squadra restituisce la lista delle partite giocate da tale squadra. 

Si implementi inoltre un main che richiami in maniera opportuna le funzioni sopra elencate, seguendo lo schema fornito nel codice.

La descrizione dettagliata di ogni funzione è riportata come commento immediatamente prima della definizione della funzione nello scheletro di programma fornito
 */

 // Includere gli header di libreria necessari

 #include <stdio.h>  
 #include <stdlib.h>
 #include <string.h>

 // Dichiarazione Struttura dati

 typedef struct partita {
     char  squadra1[32], squadra2[32];
     int  goal1, goal2;
 } TPartita;

 typedef struct nodo {
     TPartita    info;
     struct nodo *next;
 } TNodo;

 typedef TNodo *TLista;


 /* InserisciTestaLista
     inserisce un elemento in testa alla lista passata come primo parametro.
     Restituisce 1 se l'operazione va a buon fine, 0 altrimenti 
 */
 int InserisciTestaLista(TLista* lis, TPartita elem) {
     TLista paux;

     if ((paux = (TLista)malloc(sizeof(TNodo))) == NULL)
         return 0;

     paux->info = elem;
     paux->next = *lis;
     *lis = paux;

     return 1;
 }
 
 

 /* Inizializzazione della lista a lista vuota, nota che questa lista non deve contenere elementi */
 void inizializzaLista(TLista *pl){
     *pl = NULL;
 }

//---------------
typedef struct p{
    char  squadra[32];
    int  numero_partite;
}TSquadra;

/*
La funzione cerca una squadra nel vettore delle squadre e restituisce l'indice dell'elemento se trovato, 
-1 se non trovato
*/
int cerca (TSquadra*vettore, char *squadra, int dim){
     // ... corpo della funzione da completare a cura dello studente ...
 }
 
 /*
 la funzione aggiunge una nuova squadra nel vettore delle squadre o incrementa il numero delle partite
 se la squadra è gia presente
 la funzione restuisce il numero degli elementi presenti nel vettore al termine dell'operazione
 */

 void aggiungi(TSquadra*vettore, char *squadra, int *dim){
      // ... corpo della funzione da completare a cura dello studente ...
 }
 
 //----------------
 
 
 /*
    1. CaricaDaFile:
    carica da file i date delle partite e li inserisce in una lista.
    Restituisce il numero di elementi letti da file e caricati nella lista
 */
 int CaricaDaFile(TLista *plis, char *nomefile) {
   // ... corpo della funzione da completare a cura dello studente ...
        
 }


 /*
     2. ElencoSquadre: funzione che restituisce un vettore contenente l'elenco delle squadre presenti nella lista delle partite. 
     Per ogni squadra e' memorizzato anche il numero di partite.
     
     La funzione ha come parametro d'ingresso la lista delle partire e la dimensione della lista e come parametro d'uscita il numero di squadre che hanno disputato almeno una partita.
 */
 
 TSquadra* ElencoSquadre(TLista lis, int numeroPartite, int *dimensione) {
     int dim = 0;
     TSquadra *vettore,*aux;
     // Nota: il numero di squadre non può essere superiore al numero di partite / 2, il vettore
     // allocato è sicuramente maggiore di quanto necessario
     vettore = (TSquadra*)malloc(sizeof(TSquadra)*numeroPartite);
     while (lis!=NULL){
         aggiungi (vettore, lis->info.squadra1, &dim);
         aggiungi (vettore, lis->info.squadra2, &dim);
         lis = lis->next;
     }
     (*dimensione)=dim;
/*     aux = (TSquadra*)realloc(vettore,dim*sizeof(TSquadra));
     if (aux != NULL)
         vettore = aux;
     else {
         free(vettore);
         return NULL;
     }
        
     return aux; */
	 return vettore;
 }


 /*
     3. Partite squadra:
     funzione che prevede come parametri di ingresso: la lista delle partite e il nome di una squadra.
     Essa deve restituire la lista delle partite che hanno coinvolto la squadra
 */
 TLista PartiteSquadra(TLista lis, char* sq) {
   // ... corpo della funzione da completare a cura dello studente ...
     
 }

 /*******menu' di scelta *********/
 int Menu() {
   int scelta;
   
   printf("*** M E N U ***\n"
      "1 - Carica dati da file\n"
      "2 - Elenco squadre\n"
      "3 - partite di una squadra\n"
      "0 - Uscita\n\n"
      "Scelta: ");
   scanf("%d", &scelta);

   return scelta;
 }


 /*** funzione di utilità per visualizzare i dati della lista ***/
 void VisualizzaLista(TLista lis) {
   // ... corpo della funzione da completare a cura dello studente ...
       
     }

 
 void VisualizzaVettore(TSquadra *vettore, int dim){
     // ... corpo della funzione da completare a cura dello studente ...
       
 }


 /****** main *********/
 int main(void) {
   TLista listaPartite;
   TSquadra *vettore;
   int scelta;
   TLista listaSq;
   /* inserire le ulteriori variabili necessarie */
   char nomefile[20], sq[32];
   int numElementi=0; //contiene il numero di elementi caricati nella lista
   int dim=0;
   inizializzaLista(&listaPartite);
     
   do {
     scelta = Menu();

     switch (scelta) {
       case 1:
           // Acquisire il nome del file
             
           // Invocare la funzione CaricaDaFile e visualizzare il numero di elementi caricati o un messaggio in caso di errore
            
           // Visualizzare i dati caricati nella lista
             
         break;

       case 2:
           // Invocare la funzione ElencoSquadre
            
           // Visualizzare i dati restituiti dalla funzione
            
        break;

       case 3:
           // Acquisire il nome della squadra
             
           // Invocare la funzione 
             
             // Visualizzare i dati della lista restituita dalla funzione
             
         break;
      }
     
   } while (scelta != 0);

   // disallocare la lista
   
   return 0;
 }


