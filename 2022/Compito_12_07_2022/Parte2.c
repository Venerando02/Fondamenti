/*
 * Sviluppo di una applicazione in ANSI C per la gestione delle casse di un ufficio.
 *
 * Ogni cassa � operata da un impiegato, e contiene una coda di clienti prenotati.
 * Ogni operazione presenta una stima del tempo necessario.
 * In particolare:
 * Ogni Cliente presenta un nome e il tempo stimato per l'operazione;
 * Ogni Cassa presenta un ID, il nome dell'impiegato e una coda di Clienti
 *
 *
 * Implementare le seguenti funzioni:
 * 1) carica_casse: carica le casse dal file "data.txt" e le memorizza in un
 * array di casse
 * 2) tempo_stimato: restituisce un array contenente il tempo stimato per ogni cassa
 * 3) operazioni_lunghe: restituisce una lista contenente le operazioni con tempo stimato
 * pi� grande di un valore passato come parametro
 *
 * Completare, inoltre, il main con le variabili e le chiamate alle funzioni necessarie.
 *
 * La descrizione dettagliata di ogni funzione � riportata come commento immediatamente
 * prima della definizione della funzione nello scheletro di programma fornito.
*/

#define _CRT_SECURE_NO_WARNINGS
#define NOME_FILE "data.txt"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente_struct {
    char nome[32];
    float tempo_stimato;
} Cliente;

typedef struct nodo_cliente_struct {
    Cliente cliente;
    struct nodo_cliente_struct* succ;
} NodoCliente, * ListaClienti;

typedef struct coda_clienti {
    int numero_clienti;
    NodoCliente* primo, * ultimo;
} CodaClienti;

typedef struct cassa_struct {
    int id;
    char impiegato[32];
    CodaClienti coda;
} Cassa;


/*
 * Aggiunge un cliente alla coda dei clienti.
 * Restituisce 1 se l'inserimento in lista � avvenuto correttamente, 0 altrimenti
 */
int aggiungi_cliente(CodaClienti* pcoda, Cliente cliente)
{
    NodoCliente* nuovo_nodo = malloc(sizeof(NodoCliente));
    if (nuovo_nodo == NULL) return 0;

    nuovo_nodo->cliente = cliente;
    nuovo_nodo->succ = NULL;

    if (pcoda->primo == NULL) {
        pcoda->primo = pcoda->ultimo = nuovo_nodo;
        pcoda->numero_clienti = 1;
    }
    else {
        pcoda->ultimo->succ = nuovo_nodo;
        pcoda->ultimo = nuovo_nodo;
        pcoda->numero_clienti++;
    }

    return 1;
}

/*
 * Inizializza la coda passata per riferimento.
 */
void inizializza_coda(CodaClienti* pcoda) 
{
    pcoda->numero_clienti = 0;
    pcoda->primo = pcoda->ultimo = NULL;
}

/*
 * 1) carica_casse: carica le casse dal file "data.txt" e le memorizza in un
 * array di casse.
 * L'elemento i-esimo dell'array � una Cassa, contenente:
 * l'id della cassa, il nome dell'impiegato, ed una coda di Clienti
 *
 * L'array � composto da un numero di casse variabile,
 * indicato nella prima riga del file col seguente formato:
    NUMERO_CASSE(int)
 * Le successive NUMERO_CASSE righe avranno formato
    ID_CASSA(int) NOME_IMPIEGATO(string)

 * A seguire, il file contiene il numero atteso di righe, ognuna
 * corrispondente ad un cliente, nel seguente formato:
    NUMERO_CLIENTI(int)
 * Ognuna delle NUMERO_CLIENTI righe successive conterr� quindi:
    ID_CASSA(int) NOME_CLIENTE(string) TEMPO_PREVISTO(float)
 * Aggiungere il cliente alla posizione ID_CASSA-esima dell'array
 *
 * Parametri: nome del file
 * Restituisce: l'array delle casse (o NULL, in caso di errore),
 *               il numero di casse caricate (tramite parametro!)
 */
Cassa* carica_casse(char* nome_file, int* numero_casse) 
{
    // TODO Implementazione a cura dello studente
    FILE* fp = fopen(nome_file, "r");
    Cassa* vettore_casse;
    if (fp == NULL) return NULL;
    if (fscanf(fp, "%d", &(*numero_casse)) != 1) return NULL;
    vettore_casse = malloc(sizeof(Cassa) * (*numero_casse));
    int dim = (*numero_casse);
    for (int i = 0; i < dim; i++) 
    {
        inizializza_coda(&(vettore_casse[i].coda));
        if (fscanf(fp, "%d%s", &vettore_casse[i].id, vettore_casse[i].impiegato) != 2) 
        {
            free(vettore_casse);
            fclose(fp);
            return NULL;
        }
    }
    int numCliente;
    int n;
    if (fscanf(fp, "%d", &numCliente) != 1) return NULL;
    Cliente c;
    if (fscanf(fp, "%d%s%f", &n, c.nome, &c.tempo_stimato) == 3)
    {
        if ((!aggiungi_cliente(&(vettore_casse[n].coda), c)) || (n > (*numero_casse)))
        {
            free(vettore_casse);
            fclose(fp);
            return NULL;
        }
    }
    return vettore_casse;
}

/*
 * 2) tempo_stimato: crea un array contenente il tempo totale stimato per le operazioni di quella cassa
 * In particolare, restituisce un nuovo array che, per ogni cassa i, contiene il tempo totale delle operazioni
 * in coda nella cassa i
 *
 * Parametri: array delle casse e la sua dimensione dim
 * Restituisce: un array di float (di dimensione dim), dove in ogni posizione i � presente il tempo totale per la cassa i
 */
float* tempo_stimato(Cassa* casse, int dim) {
    // TODO Implementazione a cura dello studente
    float* vettore = malloc(sizeof(float)*dim);
    Cassa aux;
    float somma_tempo;
    for (int i = 0; i < dim; i++) 
    {
        somma_tempo = 0.0F;
        aux = casse[i];
        while (aux.coda.primo != NULL) 
        {
            somma_tempo += aux.coda.primo->cliente.tempo_stimato;
            aux.coda.primo = aux.coda.primo->succ;
        }
        vettore[i] = somma_tempo;
    }
    return vettore;
}

/*
 * Data una lista, la funzione aggiunge un cliente.
 * La funzione restituisce 0 se l'operazione fallisce, 1 altrimenti
 */
int aggiungi_cliente_a_lista(ListaClienti* lista_clienti, Cliente cliente) {
    NodoCliente* aux = malloc(sizeof(NodoCliente));
    if (!aux) return 0;

    aux->cliente = cliente;
    aux->succ = *lista_clienti;

    *lista_clienti = aux;

    return 1;
}

/*
 * 3) operazioni_lunghe: crea e restituisce una lista di Clienti che devono effettuare operazioni
 * che prevedono un tempo pi� grande di un tempo minimo.
 * Le operazioni devono essere cercate tra tutte le casse.
 *
 * Parametri: array delle casse e la sua dimensione, tempo minimo
 * Restituisce: la lista risultante dei clienti
 */
ListaClienti operazioni_lunghe(Cassa* casse, int dim, float tempo_minimo) 
{
    // TODO Implementazione a cura dello studente
    ListaClienti lista_out = NULL;
    ListaClienti aux;
    for (int i = 0; i < dim; i++) 
    {
        aux = casse[i].coda.primo;
        while (aux != NULL) 
        {
            if (aux->cliente.tempo_stimato >= tempo_minimo) 
            {
                aggiungi_cliente_a_lista(&lista_out, aux->cliente);
            }
            aux = aux->succ;
        }
    }
    return lista_out;
}

/*
 * Dato un cliente, visualizza le sue informazioni
 */
void visualizza_cliente(Cliente cliente) {
    printf("\t - %s (%f)\n", cliente.nome, cliente.tempo_stimato);
}

/*
 * Data una catena di clienti, li visualizza
 */
void visualizza_clienti(NodoCliente* nodo) {
    while (nodo) {
        visualizza_cliente(nodo->cliente);
        nodo = nodo->succ;
    }
}

/*
 * Visualizza le informazioni di una cassa e i clienti prenotati
 */
void visualizza_cassa(Cassa* cassa) {
    printf("Cassa %d - %s:\n", cassa->id, cassa->impiegato);

    visualizza_clienti(cassa->coda.primo);
}

/*
 * Visualizza l'intero array di casse
 */
void visualizza_casse(Cassa* casse, int dim) {
    printf("Cassa ID - Impiegato\n");
    for (int i = 0; i < dim; i++) visualizza_cassa(&casse[i]);
}

/*
 * Disalloca una catena di nodi cliente
 */
void disalloca_clienti(NodoCliente** nodo) {
    NodoCliente* nodo_aux;

    while (*nodo) {
        nodo_aux = *nodo;
        *nodo = (*nodo)->succ;
        free(nodo_aux);
    }
    *nodo = NULL;
}

/*
 * Disalloca l'array delle casse
 */
void disalloca_casse(Cassa** casse, int dim) {
    for (int i = 0; i < dim; i++) {
        disalloca_clienti(&((*casse)[i].coda.primo));
        (*casse)[i].coda.ultimo = NULL;
    }
    free(*casse);
    *casse = NULL;
}

int Menu() {
    int scelta;

    printf("*** MENU ***\n"
        "1. Carica casse\n"
        "2. Stampa operazioni lunghe\n"
        "3. Totale tempo stimato per cassa\n"
        "0. Esci\n\n"
        "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}

int main(void) {
    int scelta;

    // TODO Implementazione a cura dello studente
    Cassa* casse = NULL;
    int numero_casse;
    char buffer[64];
    float tempomin;
    NodoCliente* lista_out = NULL;
    float* v;

    do {
        scelta = Menu();

        switch (scelta) {
        case 1:
            // Caricare i dati dal file "data.txt".
            // Verificare se il file � stato letto correttamente, e in caso stampare l'array di code
            // Ricordarsi anche di disallocare le casse a monte, per evitare errori in caso di caricamenti multipli!
            // TODO Implementazione a cura dello studente
            printf("Inserisci il nome del file: ");
            scanf("%s", buffer);
            casse = carica_casse(buffer, &numero_casse);
            if (casse == NULL)
                printf("Si e' verificato un errore.");
            break;

        case 2:
            if (casse == NULL) {
                printf("Casse non ancora caricate!\n");
            }
            else {
                // Richiedere all'utente il tempo minimo oltre i quale si considera una operazione 'lunga'.
                // Verificare che il valore letto sia > 0, in caso contrario si chieda nuovamente l'input all'utente
                // Utilizzare la funzione operazioni_lunghe e stampare la lista risultante tramite visualizza_clienti
                // Successivamente, deallocare la lista tramite la funzione disalloca_clienti
                do {
                    printf("Inserisci il tempo minimo: ");
                    scanf("%f", &tempomin);
                } while (tempomin < 0);
                // TODO Implementazione a cura dello studente
                lista_out = operazioni_lunghe(casse, numero_casse, tempomin);
                printf("----------------RISULTATO-----------------\n");
                visualizza_clienti(lista_out);
                disalloca_clienti(&lista_out);
            }
            break;

        case 3:
            if (casse == NULL) {
                printf("Casse non ancora caricate!\n");
            }
            else {
                // Calcolare (tramite la funzione tempo_stimato) e visualizzare il tempo totale stimato per ogni cassa
                // Successivamente, deallocare l'array restituito dalla funzione
                v = tempo_stimato(casse, numero_casse);
                // TODO Implementazione a cura dello studente
                printf("-------------VETTORE FINALE-------------\n");
                for (int i = 0; i < numero_casse; i++)
                {
                    printf("v[%d] = %.2f\n",i , v[i]);
                }
            }
            break;
        }
    } while (scelta != 0);

    // Disallocare l'array di casse tramite la funzione disalloca_casse
    // TODO Implementazione a cura dello studente
    disalloca_casse(&casse, numero_casse);
    return 0;
}
