/*
  Sviluppo di applicazione in ANSI C per gestire
  le autovetture di una società di autonoleggio.

  In un file di testo ("autovetture.txt"), è memorizzato
  l'elenco delle autovetture possedute dalla società.
  Così come visibile nel file, per ciascuna autovettura
  sono memorizzate le seguenti informazioni:
  - targa
  - nome categoria (es: citycar, berlina, SUV, sportive, monovolume, etc)
  - costo giornaliero
  - km percorsi
  - stato (disponibile/noleggiata).

  Implementare le seguenti funzioni:
  1. CaricaVetture:
        carica le autovetture presenti nel file in due liste
        rispettivamente una contenente quelle disponibili
        e l'altra contenente quelle noleggiate.

  2. Noleggia:
        data una targa, rimuove tale vettura (se esiste)
        dalla lista delle auto disponibili e la aggiunge
        a quella delle auto noleggiate.

  3. EstraiVettureDiInteresse:
        dato un valore massimo di km percorsi ed una categoria,
        seleziona dalla lista delle vetture disponibili
        quelle che soddisfano tali criteri e le inserisce
        in un apposito vettore di autovetture.

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funione.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Autovettura {
    char  targa[8];
    char categoria[16];
    float costo;
    long km;
} TAutovettura;

typedef struct NodoAutovettura {
    TAutovettura info;
    struct NodoAutovettura* next;
} TNodoAutovettura;

typedef TNodoAutovettura* TListaAutovetture;


/* AggiungiVettura inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiVettura(TListaAutovetture* plis, TAutovettura elem) {
    TListaAutovetture paux;

    paux = (TListaAutovetture)malloc(sizeof(TNodoAutovettura));

    if (paux == NULL)
        return 0;

    paux->info = elem;
    paux->next = *plis;

    *plis = paux;

    return 1;
}

/*
  1. CaricaVetture: carica le autovetture presenti nel file
  in due liste rispettivamente una contenente quelle disponibili
  e l'altra contenente quelle noleggiate.


  Parametri di ingresso: nome del file
  Parametri di uscita: lista delle autovetture disponibili (disponibili),
                       lista delle autovetture noleggiate (noleggiate)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
 */
int CaricaVetture(char* nome_file, TListaAutovetture* disponibili, TListaAutovetture* noleggiate)
{
    // Implementare il corpo della funzione
    FILE* fp;
    char d[32];
    TAutovettura aux;
    fp = fopen(nome_file, "r");
    if (fp == NULL)
    {
        printf("Impossibile aprire il file.");
        return 0;
    }
    int r;
    while (fscanf(fp, "%s%s%f%ld%s", aux.targa, aux.categoria, &aux.costo, &aux.km, d) == 5)
    {
        if (strcmp("disponibile", d) == 0)
        {
            r = AggiungiVettura(disponibili, aux);
        }
        else if (strcmp("noleggiata", d) == 0)
        {
            r = AggiungiVettura(noleggiate, aux);
        }
    }
    if (r == 1)
    {
        return 1;
    }
    else return 0;
}
/*
  RicercaVettura: ricerca nella lista lis l'autovettura con la targa fornita in ingresso (targa). 
  Restituisce NULL se la vettura con quella targa non è presente nella lista lis.
 */
TListaAutovetture RicercaVettura(TListaAutovetture lis, char* targa) 
{
    while (lis != NULL) {
        if (strcmp(targa, lis->info.targa) == 0)
            return (lis);
        lis = lis->next;
    }
    return(NULL);
}

/*
  CancellaVettura: ricerca nella lista lis l'autovettura con la targa
  fornita in ingresso (targa) e la rimuove dalla lista.
 */
void CancellaVettura(TListaAutovetture* lis, char* targa) {
    // Implementare il corpo della funzione
    TListaAutovetture aux;
    if ((*lis) == NULL) 
    {
        return;
    }
    if (((*lis) != NULL) && (strcmp(((*lis)->info.targa), targa) == 0))
    {
        aux = (*lis);
        (*lis) = (*lis)->next;
        free(aux);
        return;
    }
    CancellaVettura(&((*lis)->next), targa);
}

/*
    2. Noleggia: data una targa, rimuove tale vettura(se esiste)
    dalla lista delle auto disponibili e la aggiunge a quella delle
    auto noleggiate.
    Parametri di ingresso:
            targa autovettura,
  Parametri di ingresso/uscita:
            lista delle autovetture disponibili (disponibili),
            lista delle autovetture noleggiate (noleggiate)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
*/

int Noleggia(char* targa, TListaAutovetture* disponibili, TListaAutovetture* noleggiate) {
    // Implementare il corpo della funzione
    TListaAutovetture aux;
    aux = RicercaVettura((*disponibili), targa);
    if (aux == NULL)
        return 0;
    TAutovettura vettura = aux->info;
    CancellaVettura(disponibili, targa);
    return AggiungiVettura(noleggiate, vettura);
}

/*
    3. EstraiVettureDiInteresse:
        dato un valore massimo di km percorsi ed una categoria,
        seleziona dalla lista delle vetture disponibili
        quelle che soddisfano tali criteri e le inserisce
        in un apposito vettore di autovetture.

    Parametri di ingresso:
            lis - lista delle autovetture disponibili,
            maxkm - numero massimo di km percorsi,
            categoria - categoria di autovettura
  Parametri di uscita:
            dim - numero di autovetture che soddisfano i criteri
  Valore restituito:
            TAutoVettura - vettore delle autovetture selezionate
*/

TAutovettura* EstraiVettureDiInteresse(TListaAutovetture lis, long maxkm, char* categoria, int* dim) {
    // Implementare il corpo della funzione
    TAutovettura* v;
    TListaAutovetture aux = lis;
    (*dim) = 0;
    while (aux != NULL) 
    {
        if ((strcmp(aux->info.categoria, categoria) == 0) && (aux->info.km > maxkm)) 
        {
            (*dim)++;
        }
        aux = aux->next;
    }
    v = malloc(sizeof(TAutovettura) * (*dim));
    int index = 0;
    aux = lis;
    while (aux != NULL)
    {
        if ((strcmp(aux->info.categoria, categoria) == 0) && (aux->info.km > maxkm))
        {
            v[index++] = aux->info;
        }
        aux = aux->next;
    }
    return v;
}


/*
  VisualizzaVetture visualizza le informazioni delle vetture
  nella lista passata come parametro
 */
void VisualizzaVetture(TListaAutovetture lis) {
    while (lis != NULL) {
        printf("%s %s %.2f %ld\n",
            lis->info.targa,
            lis->info.categoria,
            lis->info.costo,
            lis->info.km);
        lis = lis->next;
    }
}

/*
  VisualizzaVettoreAuto visualizza le informazioni delle vetture
  contenute nel vettore passato come parametro
 */
void VisualizzaVettoreAuto(TAutovettura v[], int dim) {
    // Implementare il corpo della funzione
    printf("---------VETTORE RISULTANTE---------\n");
    printf("TARGA  CATEGORIA  COSTO  KM\n");
    for (int i = 0; i < dim; i++)
    {
        printf("%s %s %f %ld\n", v[i].targa, v[i].categoria, v[i].costo, v[i].km);
    }
}



int Menu() {
    int scelta;

    printf("*** M E N U ***\n"
        "1 - Carica vetture\n"
        "2 - Noleggia vettura\n"
        "3 - Cerca Vetture di interesse \n"
        "0 - Uscita\n\n"
        "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}

void DisallocaLista(TListaAutovetture lista) {
    TListaAutovetture paux;

    // Implementare il corpo della funzione
    while (lista != NULL)
    {
        paux = lista;
        lista = lista->next;
        free(paux);
    }
}


int main(void) {
    TListaAutovetture disponibili = NULL;
    TListaAutovetture noleggiate = NULL;

    int  scelta;
    char nomefile[32];
    char targa[8];
    long km;
    int esito;
    int n;
    char cat[16];
    int dim;
    TAutovettura* vett;

    do {
        scelta = Menu();

        switch (scelta) {
        case 1:
            // acquisire il nome del file
            // invocare la funzione CaricaVetture
            // visualizzare le liste ottenute
            printf("Inserisci nome file: ");
            scanf("%s", nomefile);
            esito = CaricaVetture(nomefile, &disponibili, &noleggiate);
            printf("LISTA DISPONIBILI\n");
            VisualizzaVetture(disponibili);
            printf("\nLISTA NOLEGGIATE\n");
            VisualizzaVetture(noleggiate);
            printf("\n");
            break;

        case 2:
            // acquisire la targa dell'auto da noleggiare
            // invocare la funzione Noleggia
            // visualizzare le liste modificate
            printf("Inserisci la targa: ");
            scanf("%s", targa);
            n = Noleggia(targa, &disponibili, &noleggiate);
            printf("LISTA DISPONIBILI\n");
            VisualizzaVetture(disponibili);
            printf("\nLISTA NOLEGGIATE\n");
            VisualizzaVetture(noleggiate);
            printf("\n");
            break;

        case 3:
            // acqusire i km max
            // acquisire una categorai auto
            // invocare la funzione EstraiVettureDiInteresse
            // visualizzare il vettore restituito
            printf("Inserisci il km max: ");
            scanf("%ld", &km);
            printf("\nInserisci una categoria auto: ");
            scanf("%s", cat);
            vett = EstraiVettureDiInteresse(disponibili, km, cat ,&dim);
            VisualizzaVettoreAuto(vett, dim);
            printf("\n");
            break;
        }

    } while (scelta != 0);

    // Disallocare le liste
    DisallocaLista(disponibili);
    DisallocaLista(noleggiate);

    return 0;
}

