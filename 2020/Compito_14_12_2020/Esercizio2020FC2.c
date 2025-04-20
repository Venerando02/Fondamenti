/*
  Sviluppo di applicazione in ANSI C per gestire un sistema di
  un termostato che opera come di seguito.

  Su un archivio (allegato all'attività 'termostato.txt') è
  memorizzato l'elenco delle fasce orarie in cui attivare il
  riscaldamento nelle diversa stanze di un edificio. Ogni riga del file
  contiene le segienti informazioni: ora_attivazione,
  ora_disattivazione, id_stanza.

  Implementare le seguenti funzioni:

  1. CaricaFasceOrarie: carica l'elenco delle fasce orarie in una
  lista di fasce orarie.

  2. CreaListaStanze: a partire dalla lista delle fasce orarie,
  costruisce una lista di stanze in cui, per ogni area stanza, ci sia
  il numero di fasce orarie e la lista delle fasce orarie per quella
  specifica stanza.

  3. RiscaldamentoAttivo: dato un orario restituisce un array
  contenente l'id delle stanze che a quell'orario hanno il
  riscaldamento attivato.

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funione.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE  "termostato.txt"

typedef struct FasciaOraria
{
    int  id_stanza;
    char ora_inizio[6]; // formato hh:mm
    char ora_fine[6];   // formato hh:mm
} TFasciaOraria;

typedef struct NodoListaFasceOrarie
{
    TFasciaOraria                fascia_oraria;
    struct NodoListaFasceOrarie* succ;
} TNodoListaFasceOrarie;

typedef TNodoListaFasceOrarie* PNodoListaFasceOrarie;

typedef struct NodoListaStanze
{
    int                     id_stanza;
    int                     num_fasce_orarie;
    PNodoListaFasceOrarie   lista_fasce_orarie;
    struct NodoListaStanze* succ;
} TNodoListaStanze;

typedef TNodoListaStanze* PNodoListaStanze;


/* AggiungiFasciaOraria inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiFasciaOraria(PNodoListaFasceOrarie* fasce_orarie, TFasciaOraria fascia_oraria)
{
    PNodoListaFasceOrarie aux;

    aux = (PNodoListaFasceOrarie)malloc(sizeof(TNodoListaFasceOrarie));

    if (aux == 0)
        return 0;

    aux->fascia_oraria = fascia_oraria;
    aux->succ = *fasce_orarie;

    *fasce_orarie = aux;

    return 1;
}

/*
  1. CaricaFasceOrarie: carica l'elenco delle fasce orarie in una lista
  di fasce orarie.

  Parametri di ingresso: nome del file
  Parametri di uscita: lista delle fasce orarie (PNodoListaFasceOrarie)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
 */
int CaricaFasceOrarie(char* nome_file, PNodoListaFasceOrarie* fasce_orarie)
{
    // ...a cura dello studente...
    FILE* fp = fopen(nome_file, "r");
    if (fp == NULL)
        return 0;
    TFasciaOraria fasciaoraria;
    while (fscanf(fp, "%d%s%s", &fasciaoraria.id_stanza, fasciaoraria.ora_inizio, fasciaoraria.ora_fine) == 3) 
    {
        if (!AggiungiFasciaOraria(fasce_orarie, fasciaoraria))
            return 0;
    }
    fclose(fp);
    return 1;
}

/*
   AggiungiStanza inserisce un elemento in testa alla lista passata
   come parametro. Restituisce la nuova testa della lista
*/
PNodoListaStanze AggiungiStanza(PNodoListaStanze stanze, int id_stanza)
{
    PNodoListaStanze aux;

    aux = (PNodoListaStanze)malloc(sizeof(TNodoListaStanze));

    aux->id_stanza = id_stanza;
    aux->num_fasce_orarie = 0;
    aux->lista_fasce_orarie = NULL;
    aux->succ = stanze;

    return aux;
}

/*
  CercaStanza restituisce il puntatore al nodo della lista delle stanze
  per una specifica stanza. Restituisce NULL se quella stanza non è
  presente nella lista delle stanze.
 */
PNodoListaStanze CercaStanza(PNodoListaStanze stanze, int id_stanza)
{
    while (stanze != NULL)
    {
        if (stanze->id_stanza == id_stanza)
            return stanze;

        stanze = stanze->succ;
    }

    return NULL;
}

/*
  AggiungiFascia_OrariaInStanza aggiunge una fascia_oraria nella lista delle
  fasce_orarie relative alla specifica stanza.
 */
void AggiungiFasciaOrariaInStanza(PNodoListaStanze* plista_stanze, TFasciaOraria fascia_oraria)
{
    PNodoListaStanze p;

    p = CercaStanza(*plista_stanze, fascia_oraria.id_stanza);
    if (p == NULL)
    {
        p = AggiungiStanza(*plista_stanze, fascia_oraria.id_stanza);
        *plista_stanze = p;
    }

    if (AggiungiFasciaOraria(&p->lista_fasce_orarie, fascia_oraria))
        (p->num_fasce_orarie)++;
}

/*
   2. CreaStanze: a partire dalla lista delle fasce_orarie, costruisce una
   lista di stanze in cui, per ogni stanza, ci sia il numero e
   la lista delle fasce_orarie per quella specifica stanza.

   Parametri di ingresso: lista delle fasce_orarie
   Parametri di uscita: lista delle stanze
*/
PNodoListaStanze CreaStanze(PNodoListaFasceOrarie fasce_orarie)
{
    // ...a cura dello studente...
    PNodoListaStanze Stanze = NULL;
    PNodoListaStanze aux;
    PNodoListaFasceOrarie ListaAux = fasce_orarie;
    while (ListaAux != NULL) 
    {
        aux = CercaStanza(Stanze, ListaAux->fascia_oraria.id_stanza);
        if (aux != NULL)
        {
            AggiungiFasciaOrariaInStanza(&aux, ListaAux->fascia_oraria);
        }
        else 
        {
            Stanze = AggiungiStanza(Stanze, ListaAux->fascia_oraria.id_stanza);
            AggiungiFasciaOrariaInStanza(&Stanze, ListaAux->fascia_oraria);
        }
        ListaAux = ListaAux->succ;
    }
    return Stanze;
}

// Restituisce 1 se orario è all'interno della fascia oraria da
// ora_inizio a ora_fine. Restituise 0 altrimenti
int OrarioInFasciaOraria(char* orario, char* ora_inizio, char* ora_fine)
{
    // ...a cura dello student ...
    if ((strcmp(orario, ora_inizio) >= 0) && (strcmp(orario, ora_fine) < 0))
    {
        return 1;
    }
    else
        return 0;
}


/*
  3. RiscaldamentoAttivo: dato un orario restituisce un array
  contenente l'id delle stanze in cui è attivo il riscaldamento a
  quell'ora.

  Parametri di ingresso: lista delle stanze, orario
  Parametri di uscita: array delle stanze
*/
int* RiscaldamentoAttivo(PNodoListaStanze stanze, char* orario, int* n)
{
    // ...a cura dello studente...
    if (stanze == NULL)
        return NULL;
    (*n) = 0;
    int* vettore = NULL;
    PNodoListaStanze ListaAux = stanze;
    PNodoListaFasceOrarie Fasce = NULL;
    int dim = 0;
    while (ListaAux != NULL) 
    {
        Fasce = ListaAux->lista_fasce_orarie;
        while (Fasce != NULL) 
        {
            if (OrarioInFasciaOraria(orario, Fasce->fascia_oraria.ora_inizio, Fasce->fascia_oraria.ora_fine) == 1)
                dim++;
            Fasce = Fasce->succ;
        }
        ListaAux = ListaAux->succ;
    }
    vettore = (int*)malloc(sizeof(int) * dim);
    if (vettore == NULL)
        return NULL;
    ListaAux = stanze;
    while (ListaAux != NULL)
    {
        Fasce = ListaAux->lista_fasce_orarie;
        while (Fasce != NULL)
        {
            if (OrarioInFasciaOraria(orario, Fasce->fascia_oraria.ora_inizio, Fasce->fascia_oraria.ora_fine) == 1)
                vettore[(*n)++] = Fasce->fascia_oraria.id_stanza;
            Fasce = Fasce->succ;
        }
        ListaAux = ListaAux->succ;
    }
    return vettore;
}

void StampaFasceOrarie(PNodoListaFasceOrarie lista) 
{
    while (lista != NULL) 
    {
        printf("%d %s %s\n", lista->fascia_oraria.id_stanza, lista->fascia_oraria.ora_inizio, lista->fascia_oraria.ora_fine);
        lista = lista->succ;
    }
}

void StampaStanze(PNodoListaStanze stanze) 
{
    while (stanze != NULL) 
    {
        printf("ID_STANZA: %d -- NUMERO_FASCE_ORARIE: %d\n"
            "FASCE:\n", stanze->id_stanza, stanze->num_fasce_orarie);
        StampaFasceOrarie(stanze->lista_fasce_orarie);
        printf("\n");
        stanze = stanze->succ;
    }
}

int Menu()
{
    int scelta;

    printf("*** M E N U ***\n"
        "1 - Carica dati termostato\n"
        "2 - Crea stanze\n"
        "3 - Stanze riscaldate\n"
        "0 - Uscita\n\n"
        "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}

void DisallocaListaFasceOrarie(PNodoListaFasceOrarie lista)
{
    PNodoListaFasceOrarie p;

    while (lista != NULL)
    {
        p = lista;
        lista = lista->succ;
        free(p);
    }
}

void DisallocaListaStanze(PNodoListaStanze lista)
{
    // ...a cura dello studente...
    PNodoListaStanze aux;
    while (lista != NULL) 
    {
        DisallocaListaFasceOrarie(lista->lista_fasce_orarie);
        aux = lista;
        lista = lista->succ;
        free(aux);
    }
}

int main(void)
{
    PNodoListaFasceOrarie fasce_orarie = NULL;
    PNodoListaStanze      stanze = NULL;
    int                   scelta, n;
    char                  orario[16];
    int* id_stanze;


    do {
        scelta = Menu();

        switch (scelta)
        {
        case 1:
            if (!CaricaFasceOrarie(NOME_FILE, &fasce_orarie))
                printf("Errore durante il caricamento di %s\n", NOME_FILE);
            StampaFasceOrarie(fasce_orarie);
            printf("\n");

            break;

        case 2:
            stanze = CreaStanze(fasce_orarie);
            StampaStanze(stanze);
            printf("\n");
            break;

        case 3:
            printf("Inserisci l'orario (hh:mm): ");
            scanf("%s", orario);
            id_stanze = RiscaldamentoAttivo(stanze, orario, &n);
            for (int i = 0; i < n; i++)
                printf("%d, ", id_stanze[i]);
            printf("\n");
            free(id_stanze);
            break;
        }

    } while (scelta != 0);

    // Disallocare le lista
    DisallocaListaFasceOrarie(fasce_orarie);
    DisallocaListaStanze(stanze);

    return 0;
}
