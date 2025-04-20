/******************************************************************************
In un file sono contenuti i dati relativi ad alcuni studenti. I dati comprendono
le seguenti informazioni:
cognome, nome, matricola (10 caratteri), numero esami sostenuti (int), numero esami superati (int).
Il programma tramite apposite funzioni deve consentire di:
1) caricare i dati del file in una lista verificando la coerenza dei dati (numero di esami superati e numero si esami sostenuti
devono essere maggior o uguali a 0 e il numero di esami superati deve essere minore o uguale al numeri di esami sostenuti)
e stampare la lista
2) cancellare dalla lista tutti gli studenti che non hanno sostenuto esami
3) data la lista degli studenti e una percentuale P (percentuale esami superati
rispetto a quelli sostenuti) restituire e stampare un vettore che contiene
gli studenti che hanno superato tale percentuale di esami
4) calcolare il rate medio di superamento

*******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NOMEFILE "dati_compito2024.txt"

typedef struct st {
    char cognome[32];
    char nome[32];
    char matricola[11];
    int Esamisostenuti;
    int Esamisuperati;
} Tstudente;

typedef struct n {
    Tstudente info;
    struct n* next;
}TNodo, * TLista;


/* Funzione inserisciTesta da implementare */
int inserisciTesta(TLista* Pl, Tstudente Studente) {
    //la funzione inserisce l'elemento studente in testa alla lista 
    //restituisce 1 se l'inserimento e' avvenuto con successo
    //restituisce 0 altrimenti
    //la funzione prima di inserire verifica che la matricola non sia gia presente
    //in caso di matricola gia presente l'elemento non viene inserito
    //da implementare
    TLista Lista = (*Pl);
    int trovato = 0;
    while (Lista != NULL) 
    {
        if (strcmp(Lista->info.matricola, Studente.matricola) == 0)
        {
            trovato = 1;
            break;
        }
        Lista = Lista->next;
    }
    if (trovato == 0)
    {
        TNodo* aux = (TNodo*)malloc(sizeof(TNodo));
        if (aux == NULL)
        {
            printf("Impossibile allocare memoria nell'heap.\n");
            return -1;
        }
        aux->info = Studente;
        aux->next = (*Pl);
        (*Pl) = aux;
        return 1;
    }
    else
        return 0;
}

/* Funzione Carica da completare */
int Carica(FILE* fp, TLista* pL) {
    //la funzione restituisce 0 in caso di errore 1 altrimenti
    Tstudente studente;
    while (fscanf(fp, "%s%s%s%d%d", studente.cognome, studente.nome, studente.matricola, &studente.Esamisostenuti, &studente.Esamisuperati) == 5) {
        //verifica se il numero di esami sostenuti e il numero di esami superati è valido prima di inserire
        if ((studente.Esamisostenuti >= 0) && (studente.Esamisuperati >= 0) && (studente.Esamisuperati <= studente.Esamisostenuti)) 
        {
            if (!inserisciTesta(pL, studente))
                return 0;
        }
    }
    return 1;
}

/* Funzione stampaLista da implementare */
void stampaLista(TLista L) {
    // la funzione visualizza gli elementi della lista L
    //da implementare
    printf("\n-----------------------------\n");
    while (L != NULL) 
    {
        printf("%s %s %s %d %d\n", L->info.matricola, L->info.cognome, L->info.nome, L->info.Esamisostenuti, L->info.Esamisuperati);
        L = L->next;
    }
}

/* Funzione cancellaStudenti da implementare */
TLista cancellaStudenti(TLista L) 
{
    //data una lista L ne crea una contenente solo gli elementi con EsamiSostenuti 
    //diverso da 0
    TLista Corrente = L;
    TLista Precedente = NULL;
    while (Corrente != NULL) 
    {
        if (Corrente->info.Esamisostenuti == 0) 
        {
            if (Precedente == NULL) 
            {
                L = L->next;
                free(Corrente);
                Corrente = L;
            }
            else 
            {
                Precedente->next = Corrente->next;
                free(Corrente);
                Corrente = Precedente->next;
            }
        }
        else
        {
            Precedente = Corrente;
            Corrente = Corrente->next;
        }
    }
    return L;

}

/* Funzione conta già completa */
int conta(TLista L, float P) {
    //conta quanti studenti della lista L hanno un rate di superamento maggiore di P
    int i = 0;
    while (L != NULL) {
        if (((float)L->info.Esamisuperati / L->info.Esamisostenuti) > P)
            i++;
        L = L->next;
    }
    return i;
}

/* Funzione CreaElenco da implementare */
/* la funzione data la lista degli studenti e una percentuale P
(percentuale esami superati rispetto a quelli sostenuti)
deve restituire un vettore che contiene solo gli studenti
che hanno superato tale percentuale di esami */
Tstudente* CreaElenco(TLista L, float P, int* dim) {
    Tstudente* E = NULL;
    int d;
    // usare la funzione conta per contare il numero di studenti
    // con rate di superamento maggiore di P
    //da completare
    (*dim) = 0;
    TLista Lista = L;
    d = conta(Lista, P);
    E = (Tstudente*)malloc(sizeof(Tstudente) * d);
    if (E == NULL)
        return NULL;
    int index = 0;
    Lista = L;
    while (Lista != NULL) 
    {
        if (((float)Lista->info.Esamisuperati/Lista->info.Esamisostenuti) > P)
            E[(*dim)++] = Lista->info;
        Lista = Lista->next;
    }
    return E;
}

/* Funzione stampaVettore già completa */
void stampaVettore(Tstudente* v, int dim) {
    for (int i = 0; i < dim; i++)
        printf("%s  %s\n", v[i].nome, v[i].cognome);
}

/* Funzione calcolaRateMedioSuperamento da implementare */
/* la funzione deve calcolare e restituire il rate medio di superamento
per tutti gli studenti presenti nella lista L */
float calcolaRateMedioSuperamento(TLista L) 
{
    //da implementare
    int EsamiSuperati;
    int EsamiSostenuti;
    float AccumulatoreEsami = 0;
    int cont = 0;
    while (L != NULL) 
    {
        EsamiSostenuti = L->info.Esamisostenuti;
        EsamiSuperati = L->info.Esamisuperati;
        AccumulatoreEsami += ((float)(EsamiSuperati) / (float)(EsamiSostenuti));
        cont++;
        L = L->next;
    }
    float RateMedio = (float)(AccumulatoreEsami) / (float)(cont);
    return RateMedio;
}


/* Funzione menu già completa */
int menu() {
    int x = 0;
    printf("\n1) cancella studenti che non hanno sostenuto esami");
    printf("\n2) stampa elenco studenti con rate superamento maggiore di una percentuale");
    printf("\n3) calcola e stampa rate superamento medio");
    printf("\n0) esci\n");
    scanf("%d", &x);
    return x;
}

/*** main da completare ove richiesto */
int main(void) {
    TLista L = NULL;
    int scelta = 0;
    float Percentuale;
    Tstudente studente;
    Tstudente* Elenco;
    int dimElenco = 0;
    FILE* f = fopen(NOMEFILE, "r");
    if (f == NULL)
        exit(1);

    if (!Carica(f, &L)) {
        printf("Errore nel caricamento del file");
        exit(2);
    }
    fclose(f);
    stampaLista(L);
    do {
        scelta = menu();
        switch (scelta) {
        case 1:
            L = cancellaStudenti(L);
            printf("Lista dopo la cancellazione degli studenti senza esami sostenuti\n");
            stampaLista(L);
            break;
        case 2:
            printf("\ninserisci la percentuale di superamento esami");
            scanf("%f", &Percentuale);
            // completare
            Elenco = CreaElenco(L, Percentuale, &dimElenco);
            if (Elenco != NULL)
                stampaVettore(Elenco, dimElenco);
            break;
        case 3:
            printf("rate medio superamento = %.2f", calcolaRateMedioSuperamento(L));
            break;
        }
    } while (scelta != 0);
    return 0;
}
