/*
Sviluppo di applicazione in ANSI C per gestire l'operazione cashback dei pagamenti elettronici

In un file di testo ("operazioni.txt"), è memorizzato uno storico delle transazioni degli utenti,
nel quale ciascuna riga contiene le seguenti informazioni:
- codice cliente, data operazione, importo del pagamento.

Ogni utente a fronte di ogni pagamento effettuato riceve un bonus pari al 10% del pagamento con un
limite massimo di 15 euro per ogni singola transazione.
Esempio:
1) importo pagamento 85,00 euro --> bonus spettante 8,50 euro
2) importo pagamento 200,00 euro --> bonus spettante 15,00 euro

Implementare le seguenti funzioni:

1. CaricaOperazioni: carica l'elenco dei pagamenti in una lista di operazioni in cui, in ciascun elemento della 
lista, oltre ai campi contenuti nella riga del file, viene anche inserito il bonus spettante per quell'operazione.

2. BonusTotaleCliente: calcola il bonus totale spettante per un cliente

3. EstraiOperazioniCliente: estrae le operazioni di un cliente in un vettore

La descrizione dettagliata di ogni funzione è riportata come commento
immediatamente prima della definizione della funione.
*/

// Includere gli header di libreria necessari

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE "op.txt"

typedef struct Operazione {
    char  codicecliente[8];
    char  data[11]; // nel formato gg/mm/aaaa
    float importo;
    float   bonus;
} TOperazione;

typedef struct NodoLista {
    TOperazione      info;
    struct NodoLista* next;
} TNodoLista;

typedef TNodoLista* TipoLista;

/* InserisciInLista inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int InserisciInLista(TipoLista* plista, TOperazione op)
{
    TipoLista aux;

    aux = (TipoLista)malloc(sizeof(TNodoLista));

    if (aux == 0)
        return 0;

    aux->info = op;
    aux->next = *plista;

    *plista = aux;

    return 1;
}

/*
   1. CaricaOperazioni: carica l'elenco dei pagamenti in una lista di operazioni in cui, in ciascun elemento della lista,
   oltre ai campi contenuti nella riga del file, viene anche inserito il bonus spettante per quell'operazione.
   Restituisce 1 se l'operazione va a buon fine, 0 altrimenti.
*/
int CaricaOperazioni(TipoLista* plista, char* nome_file)
{
    // inserire il corpo della funzione  
    TOperazione op;
    FILE* fp = fopen(nome_file, "r");
    if (fp == NULL)
        return -1;
    while (fscanf(fp, "%s%s%f", op.codicecliente, op.data, &op.importo) == 3) 
    {
        op.bonus = 0.10 * op.importo;
        if (op.bonus > 15)
            op.bonus = 15;
        if (!InserisciInLista(plista, op))
            return 0;
    }
    fclose(fp);
    return 1;
}

/*
2. BonusTotaleCliente: Dato il codice di un cliente, la funzione calcola il valore del bonus totale spettante per quel cliente.

   Parametri di ingresso: lista delle operazioni, codice cliente
    Parametro di uscita: bonus totale per il cliente
    Valore restituito: 1 se il cliente è stato trovato, 0 se il cliente non è presente nella lista
*/
int BonusTotaleCliente(TipoLista lis, char* cliente, float* totale) 
{
    // inserire il corpo della funzione    
    TipoLista L = lis;
    (*totale) = 0;
    while (L != NULL) 
    {
        if (strcmp(L->info.codicecliente, cliente) == 0)
        {
            (*totale) += L->info.bonus;
        }
        L = L->next;
    }
    return 1;
}

/*
3. EstraiOperazioniCliente: estrae le operazioni di un cliente contenute nella lista in un vettore

 Parametri di ingresso: lista delle operazioni, codice cliente
 Parametri di uscita: numero di operazioni di quel cliente
 Valore restituito: vettore delle operazioni di quel cliente
*/
TOperazione* EstraiOperazioniCliente(TipoLista lis, char* cliente, int* dim) 
{
    // inserire il corpo della funzione    
    (*dim) = 0;
    TOperazione* vout = NULL;
    TipoLista ListaAux = lis;
    while (ListaAux != NULL) 
    {
        if (strcmp(ListaAux->info.codicecliente, cliente) == 0) 
        {
            (*dim)++;
        }
        ListaAux = ListaAux->next;
    }
    ListaAux = lis;
    vout = (TOperazione*)malloc(sizeof(TOperazione) * (*dim));
    if (vout == NULL)
        return NULL;
    int index = 0;
    while (ListaAux != NULL)
    {
        if (strcmp(ListaAux->info.codicecliente, cliente) == 0)
        {
            vout[index++] = ListaAux->info;
        }
        ListaAux = ListaAux->next;
    }
    return vout;
}

/*
  VisualizzaListaOperazioni:
  visualizza le informazioni delle operazioni nella lista passata come parametro
*/
void VisualizzaListaOperazioni(TipoLista lis) 
{
    // inserire il corpo della funzione 
    printf("\n-----------------------------\n");
    while (lis != NULL) 
    {
        printf("%s %s %.2f %.2f\n", lis->info.codicecliente, lis->info.data, lis->info.importo, lis->info.bonus);
        lis = lis->next;
    }
}

/*
VisualizzaVettoreOperazioni:
visualizza le informazioni delle operazioni contenute nel vettore passato come parametro
*/
void VisualizzaVettoreOperazioni(TOperazione v[], int dim) {
    // inserire il corpo della funzione    
    printf("\n---------------------------\n");
    for (int i = 0; i < dim; i++) 
    {
        printf("%s %s %.2f %.2f\n", v[i].codicecliente, v[i].data, v[i].importo, v[i].bonus);
    }
}

int Menu() {
    int scelta;

    printf("*** M E N U ***\n"
        "1 - CaricaOperazioni\n"
        "2 - BonusTotaleCliente\n"
        "3 - EstraiOperazioniCliente\n"
        "0 - Uscita\n\n"
        "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}

void DisallocaLista(TipoLista lista) {
    TipoLista p;

    while (lista != NULL) {
        p = lista;
        lista = lista->next;
        free(p);
    }
}

int main(void) {
    TipoLista lista = NULL;
    int        scelta;
    int esito;

    float   btotale;
    char    codice[8];
    int dim;
    TOperazione* vett = NULL;

    do {
        scelta = Menu();

        switch (scelta) {
        case 1:

            // Invocare la funzione CaricaOperazioni 
            // e visualizzare un messaggio in caso di errore
            esito = CaricaOperazioni(&lista, NOME_FILE);
            if (esito == -1)
                printf("Errore nell'apertura del file.\n");
            else if (esito == 0)
                printf("Errore durante il caricamento dei dati.\n");
            else
            {
                printf("Dati caricati in lista\n");
                VisualizzaListaOperazioni(lista);
            }
            // visualizzare i dati caricati nella lista delle operazioni
            break;

        case 2:
            // Acquisire un codice cliente
            printf("Inserisci un Codice cliente: ");
            scanf("%s", codice);
            // Invocare la funzione BonusTotaleCliente 
            if (BonusTotaleCliente(lista, codice, &btotale) == 1)
                printf("Il bonus totale di %s e' %.2f.\n", codice, btotale);
            else
                printf("Cliente non trovato.\n");
            // o un messaggio di errore in caso contrario
            
            break;

        case 3:
            // Acquisire un codice cliente
            printf("Inserisci un Codice cliente: ");
            scanf("%s", codice);
            // Invocare la funzione EstraiOperazioniCliente 
            vett = EstraiOperazioniCliente(lista, codice, &dim);
            // visualizzare i dati del vettore ottenuto in precedenza
            
            VisualizzaVettoreOperazioni(vett, dim);
            printf("\n");
            free(vett);
            break;
        }

    } while (scelta != 0);

    DisallocaLista(lista);

    return 0;
}
