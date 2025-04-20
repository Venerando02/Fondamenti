/******************************************************************************
Un archivio contiene i dati relativi ai film trasmessi su un canale telvisivo. I file sono di quattro generi
diversi: "COMMEDIA" "THRILLER" "MUSICAL" e "FANTASCIENZA".
L'archivio è costituito da un file testo in cui per ogni film sono memorizzati uno per ciscuna riga le
sguenti informazioni
- titolo del film - una stringa di 255 caratteri che include caratteri bianche
- una stringa contenente il genere
- una stringa contenente la data della prima proiezione nel formato aaaa-mm-gg
Attenzione per il genere nella lista verra memorizzato un codice intero. Vedere il codice
per la corrispondenza.
Scrivere un programma che consente di effettuare le seguenti operazioni
- caricamento dei dati in una lista ordinata rispetto alla data e stampa della lista
- ricerca del film più nuovo e piu vecchio
- estrazioni dei film di un dato genere

*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define leng 226

/*struttura lista*/
typedef struct s {
    int genere; //0 per COMMEDIA, 2 per TRHILLER, 2 per MUSICAL e 3 per FANTSCIENZA
    char data[11]; //aaaa-mm-gg
    char titolo[leng];
}elemento;

typedef struct n {
    elemento info;
    struct n* next;
} nodo, * lista;

lista make_null_lista() 
{ 
    return NULL; 
}

int empty_list(lista l) 
{
    return (l == NULL); 
}

int cons(lista* pL, elemento E) 
{
    nodo* aux = (nodo*)malloc(sizeof(nodo));
    if (aux == NULL)
        return -1;
    aux->info = E;
    aux->next = (*pL);
    (*pL) = aux;
    return 0;
}
int inserimento_ordinamento(lista* pL, elemento E) 
{
    if ((*pL) == NULL)
    {
        return cons(pL, E);
    }
    if (strcmp(E.data, (*pL)->info.data) > 0)
    {
        return cons(pL, E);
    }
    else
        return inserimento_ordinamento(&((*pL)->next), E);
}

void stampa(lista L) {
    while (L != NULL) {
        printf("%s\n", L->info.titolo);
        L = L->next;
    }
}

/*funzioni di servizio*/
int ritorna_indice(char* genere) {
    if (strcmp(genere, "COMMEDIA") == 0) return 0;
    if (strcmp(genere, "THRILLER") == 0) return 1;
    if (strcmp(genere, "MUSICAL") == 0) return 2;
    if (strcmp(genere, "FANTASCIENZA") == 0) return 3;
    return -1;
}

char* ritorna_stringa(int indice) {
    switch (indice) {
    case 0:return "COMMEDIA";
    case 1:return "THRILLER";
    case 2:return "MUSICAL";
    case 3:return "FANTASCIENZA";
    }
    return "NoN";
}

int menu() {
    int scelta;
    printf("1) questito1: carica e stampa\n");
    printf("2) questito2: ricerca film piu' nuovo e piu' vecchio\n");
    printf("3) questito3: film di un dato genere\n\n"
        ">>> "
    );
    scanf("%d", &scelta);
    return scelta;
}

/*quesito1*/
void quesito1(lista* pL) {
    //INSERIRE CODICE QUESITO 1
    char NomeFile[leng];
    printf("Inserisci il nome del file: ");
    scanf("%s", NomeFile);
    FILE* fp = fopen(NomeFile, "r");
    if (fp == NULL)
        return;
    elemento film;
    while (fscanf(fp, "%s%d%s", film.titolo, &film.genere, film.data) == 3)
    {
        inserimento_ordinamento(pL, film);
    }
    fclose(fp);
}


/*quesito2*/
void quesito2(lista ListaFilm, elemento* vecchio, elemento* nuovo) 
{
    //INSERIRE CODICE QUESITO 2
    strcpy((*vecchio).data, "");
    strcpy((*vecchio).titolo, "");
    (*vecchio).genere = -1;
    
    strcpy((*nuovo).data, "");
    strcpy((*nuovo).titolo, "");
    (*nuovo).genere = -1;

    elemento FilmVecchio = ListaFilm->info;
    elemento FilmNuovo = ListaFilm->info;
    while (ListaFilm != NULL) 
    {
        if (strcmp(ListaFilm->info.data, FilmNuovo.data) > 0) 
        {
            FilmNuovo = ListaFilm->info;
        }
        if (strcmp(ListaFilm->info.data, FilmVecchio.data) < 0)
        {
            FilmVecchio = ListaFilm->info;
        }
        ListaFilm = ListaFilm->next;
    }
    (*vecchio) = FilmVecchio;
    (*nuovo) = FilmNuovo;
}

/*quesito3*/
lista quesito3(lista ListaFilm, char * Genere) {
    //INSERIRE CODICE QUESITO 2
    int genere;
    genere = ritorna_indice(Genere);
    lista ListaUscita = make_null_lista();
    while (ListaFilm != NULL) 
    {
        if (ListaFilm->info.genere == genere) 
        {
            inserimento_ordinamento(&ListaUscita, ListaFilm->info);
        }
        ListaFilm = ListaFilm->next;
    }
    return ListaUscita;
}



//main 
int main(void) {
    lista L = make_null_lista();
    int scelta = 0;
    elemento old, nuovo;
    lista result = make_null_lista();
    char g[20];
    do {
        scelta = menu();
        switch (scelta) {
        case 1:
            quesito1(&L);
            stampa(L);
            break;
        case 2: 
            quesito2(L, &old, &nuovo);
            printf("il film piu' vecchio e' %s\n", old.titolo);
            printf("il film piu' nuovo e' %s\n", nuovo.titolo);
            break;
        case 3: 
            printf("inserisci il genere\n");
            scanf("%s", g);
            result = quesito3(L, g);
            stampa(result);
            break;
    }
} while (scelta!=0);
}




