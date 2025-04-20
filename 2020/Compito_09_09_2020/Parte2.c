/*
  Sviluppo di applicazione in ANSI C per gestire un sistema di
  videosorveglianza.

  Su un archivio (allegato all'attività 'telecamere.cfg') è
  memorizzato l'elenco dei parametri di configurazione delle
  telecamere che compongono il sistema. La configurazione di una
  telecamera comprende le seguenti informazioni: identificativo
  telecamera, identificativo dell'area monitorata, orario inizio e
  fine registrazione.

  Implementare le seguenti funzioni:

  1. CaricaConfigurazione: carica l'elenco dei parametri di
  configurazione delle telecamere in una lista di telecamere.

  2. CreaAree: a partire dalla lista delle telecamere, costruisce una
  lista di aree in cui, per ogni area monitorata, ci sia il numero e
  la lista delle telecamere che monitorano quella specifica area.

  3. RegistrazioniDisponibili: dato un orario, e l'identificativo di
  un'area, restituisce la lista delle telecamere che sono in modalità
  registrazione a quell'ora.

  La descrizione dettagliata di ogni funzione è riportata come
  commento immediatamente prima della definizione della funione.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_FILE  "telecamere.cfg"

typedef struct Telecamera
{
    char  id_telecamera[16];
    char  id_area[16];
    char  ora_inizio[6]; // formato hh:mm
    char  ora_fine[6];   // formato hh:mm
} TTelecamera;

typedef struct NodoListaTelecamere
{
    TTelecamera                 telecamera;
    struct NodoListaTelecamere* succ;
} TNodoListaTelecamere;

typedef TNodoListaTelecamere* PNodoListaTelecamere;

typedef struct NodoListaAree
{
    char                  id_area[16];
    int                   num_telecamere;
    PNodoListaTelecamere  lista_telecamere;
    struct NodoListaAree* succ;
} TNodoListaAree;

typedef TNodoListaAree* PNodoListaAree;


/* AggiungiTelecamera inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int AggiungiTelecamera(PNodoListaTelecamere* telecamere, TTelecamera telecamera)
{
    PNodoListaTelecamere aux;

    aux = (PNodoListaTelecamere)malloc(sizeof(TNodoListaTelecamere));

    if (aux == 0)
        return 0;

    aux->telecamera = telecamera;
    aux->succ = *telecamere;

    *telecamere = aux;

    return 1;
}

/*
  1. CaricaTelecamere: carica l'elenco delle telecamere in una lista
  di telecamere.

  Parametri di ingresso: nome del file
  Parametri di uscita: lista delle telecamere (PNodoListaTelecamere)
  Valore restituito: 1 operazione andata a buon fine, 0 altrimenti
 */
int CaricaTelecamere(char* nome_file, PNodoListaTelecamere* telecamere)
{
    // Implementare il corpo della funzione
    FILE* fp;
    TTelecamera aux;
    fp = fopen(nome_file, "r");
    if (fp == NULL)
    {
        printf("Impossibile aprire il file.");
        return 0;
    }
    int esito;
    while (fscanf(fp, "%s%s%s%s", aux.id_telecamera, aux.id_area, aux.ora_inizio, aux.ora_fine) == 4) 
    {
        esito = AggiungiTelecamera(telecamere, aux);
    }
    return esito;
}

/*
   AggiungiArea inserisce un elemento in testa alla lista passata
   come parametro. Restituisce la nuova testa della lista
*/
PNodoListaAree AggiungiArea(PNodoListaAree aree, char* id_area)
{
    PNodoListaAree aux;

    aux = (PNodoListaAree)malloc(sizeof(TNodoListaAree));

    strcpy(aux->id_area, id_area);
    aux->num_telecamere = 0;
    aux->lista_telecamere = NULL;
    aux->succ = aree;

    return aux;
}

/*
   2. CreaAree: a partire dalla lista delle telecamere, costruisce una
   lista di aree in cui, per ogni area monitorata, ci sia il numero e
   la lista delle telecamere che monitorano quella specifica area.

   Parametri di ingresso: lista delle telecamere
   Parametri di uscita: lista delle aree
*/
PNodoListaAree CreaAree(PNodoListaTelecamere telecamere)
{
    PNodoListaAree listaAree = NULL;  // Inizializziamo la lista delle aree a NULL
    PNodoListaTelecamere telecameraAttuale = telecamere;

    while (telecameraAttuale != NULL)
    {
        // Cerchiamo se l'area esiste già nella lista delle aree
        PNodoListaAree areaCorrente = listaAree;
        while (areaCorrente != NULL && strcmp(areaCorrente->id_area, telecameraAttuale->telecamera.id_area) != 0)
        {
            areaCorrente = areaCorrente->succ;
        }

        // Se l'area non esiste, la creiamo e la aggiungiamo alla lista delle aree
        if (areaCorrente == NULL)
        {
            listaAree = AggiungiArea(listaAree, telecameraAttuale->telecamera.id_area);
            areaCorrente = listaAree; // Aggiorniamo areaCorrente per puntare alla nuova area
        }

        // Aggiungiamo la telecamera alla lista delle telecamere di questa area
        AggiungiTelecamera(&(areaCorrente->lista_telecamere), telecameraAttuale->telecamera);
        areaCorrente->num_telecamere++; // Incrementiamo il contatore delle telecamere per questa area

        // Passiamo alla telecamera successiva
        telecameraAttuale = telecameraAttuale->succ;
    }

    return listaAree; // Ritorniamo la lista delle aree
}


/*
  3. RegistrazioniDisponibili: dato un orario, e l'identificativo di
  un'area, restituisce la lista delle telecamere che sono in modalità
  registrazione a quell'ora.

  Parametri di ingresso: lista delle are, orario, identificativo area
  Parametri di uscita: lista delle telecamere
*/

PNodoListaTelecamere RegistrazioniDisponibili(PNodoListaAree aree, char* orario, char* id_area)
{
    // Implementare il corpo della funzione
    PNodoListaTelecamere lista = NULL;
    PNodoListaTelecamere lista_t;
    PNodoListaAree aux = aree;
    while (aux != NULL) 
    {
        if (strcmp(aux->id_area, id_area) == 0)
        {
            lista_t = aux->lista_telecamere;
            while (lista_t != NULL) 
            {
                if ((strcmp(orario, lista_t->telecamera.ora_inizio) >= 0) && (strcmp(orario, lista_t->telecamera.ora_fine) < 0)) 
                {
                    AggiungiTelecamera(&lista, lista_t->telecamera);
                }
                lista_t = lista_t->succ;
            }
        }
        aux = aux->succ;
    }
    return lista;
}

/*
  VisualizzaTelecamere visualizza le informazioni delle telecamere
  nella lista di telecamere
 */
void VisualizzaTelecamere(PNodoListaTelecamere telecamere)
{
    while (telecamere != NULL)
    {
        printf("%-15s %-15s %-5s %-5s\n",
            telecamere->telecamera.id_telecamera,
            telecamere->telecamera.id_area,
            telecamere->telecamera.ora_inizio,
            telecamere->telecamera.ora_fine);

        telecamere = telecamere->succ;
    }
}

int Menu()
{
    int scelta;

    printf("*** M E N U ***\n"
        "1 - Carica telecamere\n"
        "2 - Crea aree\n"
        "3 - Registrazioni disponibili\n"
        "0 - Uscita\n\n"
        "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}

void DisallocaListaTelecamere(PNodoListaTelecamere lista)
{
    PNodoListaTelecamere p;

    while (lista != NULL)
    {
        p = lista;
        lista = lista->succ;
        free(p);
    }
}

void DisallocaListaAree(PNodoListaAree lista)
{
    PNodoListaAree p;

    while (lista != NULL)
    {
        p = lista;
        lista = lista->succ;
        free(p);
    }
}

int main(void)
{
    PNodoListaTelecamere telecamere = NULL;
    PNodoListaTelecamere telecamere_disponibili = NULL;
    PNodoListaAree       aree = NULL;
    int                  scelta;
    char                 orario[16], id_area[16];
    int n;


    do {
        scelta = Menu();

        switch (scelta)
        {
        case 1:
            // Invocare la funzione CaricaTelecamere per ottenere la lista telecamere
            n = CaricaTelecamere(NOME_FILE, &telecamere);
            VisualizzaTelecamere(telecamere);
            break;

        case 2:
            // Invocare la funzione CreaAree per ottenre la lista di liste aree
            aree = CreaAree(telecamere);
            
            break;

        case 3:
            // Acquisire l'orario e l'id_area
            // Invocare la funzione RegistrazioniDisponibili per ottenere la lista telecamere_disponibili
            // Visualizzare la lista telecamere_disponibili
            printf("Inserisci l'orario: ");
            scanf("%s", orario);
            printf("Inserisci l'id area: ");
            scanf("%s", id_area);
            telecamere_disponibili = RegistrazioniDisponibili(aree, orario, id_area);
            VisualizzaTelecamere(telecamere_disponibili);
            break;
        }

    } while (scelta != 0);

    // Disallocare le liste
    DisallocaListaAree(aree);
    DisallocaListaTelecamere(telecamere);
    return 0;
}

