/*
* FONDAMENTI DI INFORMATICA - Esercizio 2
*
* Si desidera sviluppare un programma per gestire un inventario di una farmacia, che consenta agli impiegati di registrare
* l'arrivo e la vendita di farmaci.
* Le funzioni che si vogliono implementare sono le seguenti:
* 1. AggiungiFarmaco: inserimento di un nuovo farmaco nell'inventario
* 2. VenditaFarmaco: vendita di un farmaco (aggiornando la quantità disponibile)
* 3. VisualizzaInventario: visualizzazione dell'inventario con i relativi dettagli sui farmaci
* 4. CaricaDaFile: carica i dati da un file di testo e aggiunge i farmaci all'inventario
* 5. EstraiFarmaciSottoSoglia: estrae un vettore dei farmaci con quantità inferiore a una soglia data
**
* I dettagli delle funzioni e delle parti da implementare sono definiti in nei commenti presenti prima delle
* funzioni.
*
* I dati dei farmaci sono memorizzati in una struttura dati di tipo lista concatenata.
* Ogni nodo della lista rappresenta un farmaco e contiene le seguenti informazioni:
* - Nome del farmaco
* - Quantità disponibile
* - Prezzo per confezione
**
* La specifica dettagliata delle funzioni è riportata nel seguito
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct farmaco {
    char nome[100];
    int quantita;
    float prezzo;
    struct farmaco* next;
} Farmaco;
typedef Farmaco* FarmacoPtr;

// ........... DA IMPLEMENTARE ............ 
// Aggiunge un nuovo farmaco all'inventario della farmacia
//
// La funzione accetta in ingresso l'inventario (lista dei farmaci), il nome del farmaco, la quantità 
// disponibile e il prezzo per confezione.
// La funzione aggiunge un nuovo nodo alla lista degli inventari con le informazioni del nuovo farmaco.
void AggiungiFarmaco(FarmacoPtr* inventario, char* nome, int quantita, float prezzo) 
{
    Farmaco* aux = (Farmaco*)malloc(sizeof(Farmaco));
    if (aux == NULL)
        return;
    strcpy(aux->nome, nome);
    aux->prezzo = prezzo;
    aux->quantita = quantita;
    aux->next = (*inventario);
    (*inventario) = aux;
}

// Carica i dati da un file di testo e aggiunge i farmaci all'inventario
//
// La funzione accetta in ingresso l'inventario (lista dei farmaci) e il nome del file di testo da 
// cui caricare i dati.

void CaricaDaFile(FarmacoPtr* inventario, const char* nome_file) 
{
    FILE* file = fopen(nome_file, "r");
    if (file == NULL) {
        printf("Impossibile aprire il file %s\n", nome_file);
        return;
    }

    char nome[100];
    int quantita;
    float prezzo;

    while (fscanf(file, "%s %d %f", nome, &quantita, &prezzo) == 3) {
        AggiungiFarmaco(inventario, nome, quantita, prezzo);
    }

    fclose(file);
}

// ........... DA IMPLEMENTARE ............ 
// Esegue la vendita di un farmaco
//
// La funzione accetta in ingresso l'inventario (lista dei farmaci), il nome del farmaco da 
// vendere e la quantità da vendere.
// Se il farmaco è presente nell'inventario e la quantità richiesta è disponibile, 
// la funzione aggiorna la quantità disponibile e restituisce 1, altrimenti, restituisce 0.
//
// Nota che qualora la quantità dovesse diventare zero il farmaco non deve essere cancellato dalla lista
//
int VenditaFarmaco(Farmaco* inventario, char* nome, int quantita_venduta) 
{
    while (inventario != NULL) 
    {
        if (strcmp(inventario->nome, nome) == 0) 
        {
            if (inventario->quantita >= quantita_venduta)
            {
                inventario->quantita = inventario->quantita - quantita_venduta;
                return 1;
            }
            else
                return 0;
        }
        inventario = inventario->next;
    }
    return 0;
}

// Visualizza l'inventario della farmacia con i relativi dettagli sui farmaci
//
// La funzione accetta in ingresso l'inventario (lista dei farmaci).
// La funzione stampa a video il nome del farmaco, la quantità disponibile e il prezzo per confezione.
void VisualizzaInventario(Farmaco* inventario) {
    printf("Inventario della farmacia:\n");
    printf("Nome del farmaco | Quantità disponibile | Prezzo per confezione\n");
    while (inventario != NULL) {
        printf("%-20s | %-20d | %.2f\n", inventario->nome, inventario->quantita, inventario->prezzo);
        inventario = inventario->next;
    }
}

// ........... DA IMPLEMENTARE ............ 
// Estrae un vettore dei farmaci con quantità inferiore a una soglia data
//
// La funzione accetta in ingresso l'inventario (lista dei farmaci), la soglia e un puntatore 
// a intero per memorizzare il numero di farmaci sotto soglia.
// La funzione restituisce il vettore di farmaci con quantità inferiore alla soglia.
// La funzione restituisce NULL se si verifica un errore di allocazione di memoria.

Farmaco* EstraiFarmaciSottoSoglia(FarmacoPtr inventario, int soglia, int* num_farmaci_sotto_soglia) 
{
    (*num_farmaci_sotto_soglia) = 0;
    Farmaco* vettore = NULL;
    int dim = 0;
    FarmacoPtr ListaAux = inventario;
    while (ListaAux != NULL) 
    {
        if (ListaAux->quantita < soglia)
            dim++;
        ListaAux = ListaAux->next;
    }
    vettore = (Farmaco*)malloc(sizeof(Farmaco) * dim);
    if (vettore == NULL)
        return NULL;
    ListaAux = inventario;
    while (ListaAux != NULL) 
    {
        if (ListaAux->quantita < soglia)
        {
            vettore[(*num_farmaci_sotto_soglia)].prezzo = ListaAux->prezzo;
            vettore[(*num_farmaci_sotto_soglia)].quantita = ListaAux->quantita;
            strcpy(vettore[(*num_farmaci_sotto_soglia)].nome, ListaAux->nome);
            (*num_farmaci_sotto_soglia)++;
        }
        ListaAux = ListaAux->next;
    }
    return vettore;
}

int Menu() {
    int scelta;

    printf("*** M E N U ***\n"
        "1 - Aggiungi farmaco\n"
        "2 - Vendi farmaco\n"
        "3 - Visualizza inventario\n"
        "4 - Carica inventario da file\n"
        "5 - Estrai un vettore di farmaci sotto soglia\n"
        "0 - Uscita\n\n"
        "Scelta: ");
    scanf("%d", &scelta);

    return scelta;
}

int main(void) {
    Farmaco* inventario = NULL;
    int scelta;
    char nome[100];
    int quantita;
    float prezzo;
    int soglia;
    Farmaco* farmaci_sotto_soglia = NULL;
    int num_farmaci_sotto_soglia;
    char nome_file[100];

    do {
        scelta = Menu();

        switch (scelta) {
        case 1:
            printf("Nome del farmaco: ");
            scanf("%s", nome);
            printf("Quantità disponibile: ");
            scanf("%d", &quantita);
            printf("Prezzo per confezione: ");
            scanf("%f", &prezzo);
            // ........... DA IMPLEMENTARE ............
            // Completare la voce usando la funzione AggiungiFarmaco
            AggiungiFarmaco(&inventario, nome, quantita, prezzo);
            break;
        case 2:
            printf("Nome del farmaco da vendere: ");
            scanf("%s", nome);
            printf("Quantità da vendere: ");
            scanf("%d", &quantita);
            // ........... DA IMPLEMENTARE ............
            // Completare la voce usando la funzione VenditaFarmaco
            if (VenditaFarmaco(inventario, nome, quantita))
                printf("Vendita avvenuta con successo.\n");
            break;
        case 3:
            VisualizzaInventario(inventario);
            break;
        case 4:
            printf("Inserisci il nome del file da cui caricare i dati: ");
            scanf("%s", nome_file);
            CaricaDaFile(&inventario, nome_file);
            break;
        case 5:
            printf("Inserisci la soglia: ");
            scanf("%d", &soglia);
            // ........... DA IMPLEMENTARE ............
            // Completare la voce usando la funzioni presenti nel testo
            farmaci_sotto_soglia = EstraiFarmaciSottoSoglia(inventario, soglia, &num_farmaci_sotto_soglia);
            printf("\n----------------------\n");
            for (int i = 0; i < num_farmaci_sotto_soglia; i++)
                printf("%s %f %d\n", farmaci_sotto_soglia[i].nome, farmaci_sotto_soglia[i].prezzo, farmaci_sotto_soglia[i].quantita);
            printf("\n");
            break;
        case 0:
            // ........... DA IMPLEMENTARE ............
            // Completare la voce usando la funzioni presenti nel testo
            printf("Uscita programma");
            break;
        default:
            printf("Scelta non valida.\n");
            break;
        }
    } while (scelta != 0);

    return 0;
}
