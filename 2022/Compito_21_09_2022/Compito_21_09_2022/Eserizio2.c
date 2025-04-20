/*
  Scaricare l'esercizio e completarlo inserendo il codice necessario
  senza modificare quello esistente tranne quando espressamente
  richiesto.

  L'esercizio si considera corretto se il programma compila
  correttamente ed esegue senza errori run-time dando i risultati
  attesi.

  TESTO
  =====
  Gestione dei consumi energetici di una serie di dispositivi. I dispositivi sono univocamente identificato da un valore
  compreso nell'intervallo [0,20], non sempre il dispositivo è presente.

  In un file sono memorizzati in ogni riga l'ora di accensione o spegnimento di ogni dispositivo,
  l'identificativo e la potenza (in Watt) utilizzata. Le funzioni da svolgere sono le seguenti

  1. caricamento dei dati in una lista verificando che l'identificativo sia compreso nell'intervallo richiesto
  2. copia dei dati in un vettore di liste ordinate rispetto l'ora di attivazione, ogni lista contiene i dati del sensore
     con l'identificativo corrispondente (se non sono presenti dati la lista è vuota)
  3. calcolo dell'energia totale utilizzata in Wh (watt per ora, per definizione 1 wattora è l'energia sviluppata da un potenza di un
     1 Watt per 1 ora). Nota che nella lista ordinata l'evento di spegnimento (OFF) deve sempre seguire quello di accensione (ON). Qualora
     mancasse l'evento di spegnimento (il dispositivo è ancora acceso) non se ne calcola il contributo (NOTA: la funzione che calcola
     la differenza in minuti fra due eventi e' fornita gia' implementata)
  4. calcolo del vettore dei consumi di ogni singolo dispositivo

  ESEMPIO FILE INGRESSO
  ====================
    0	09:12 12 ON
    1	09:13 8 ON
    0	09:25 12 OFF
    4   10:04 100 ON
    4   10:14 100 OFF
    1	09:30 8 OFF
    0	09:40 11 ON
    0	09:45 11 OFF

Con i dati conteuti nel file il consumo totale è 21.533 Wh mentre il consumo del dispositivo 1 è 2.267 Wh

  */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMERO_MASSIMO_DISPOSITIVI 20

typedef struct {
    int id;
    char ora[6];
    int potenza;
    char stato[6];
} evento_t;

typedef struct nodo_s {
    evento_t ev;
    struct nodo_s* n;
} nodo_t;

typedef nodo_t* lista_evento_t;
typedef lista_evento_t vettore_eventi_t[NUMERO_MASSIMO_DISPOSITIVI];

// Funzioni di gestione della lista
// aggiungi
//    inserisce un elemento in testa alla lista verificando che il valore dell'identificativo sia valido
//    in caso di errore non fa alcuna operazione
// parametri:
//        lista_evento_t l    : lista a cui aggiungere il nuovo evento
//        evento_t ev         : evento da aggiungere
// return:
//        lista modificata
lista_evento_t aggiungi(lista_evento_t l, evento_t ev)
{
    if (ev.id > NUMERO_MASSIMO_DISPOSITIVI)
        return l;
    nodo_t* aux = (nodo_t*)malloc(sizeof(nodo_t));
    aux->ev = ev;
    aux->n = l;
    return aux;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// aggiungi_ordine
//    inserisce un elemento in base al valore dell'orario alla lista verificando che il valore dell'identificativo sia valido
//    in caso di errore non fa alcuna operazione
// parametri:
//        lista_evento_t l    : lista a cui aggiungere il nuovo evento
//        evento_t ev         : evento da aggiungere
// return:
//        lista modificata
lista_evento_t aggiungi_ordine(lista_evento_t l, evento_t ev)
{
    // A CURA DELLO STUDENTE
    if (ev.id > NUMERO_MASSIMO_DISPOSITIVI)
        return l;
    if (l == NULL)
    {
        l = aggiungi(l, ev);
        return l;
    }
    if (strcmp(l->ev.ora, ev.ora) > 0)
    {
        l = aggiungi(l, ev);
        return l;
    }
    l->n = aggiungi_ordine(l->n, ev);
    return l;
}
//
// stampa
//    stampa il contenuto della lista di eventi
// parametri:
//    lista_evento_t l    : lista di cui stampare il contenuto
// return:
//        nessuno
void stampa(lista_evento_t l) {
    if (l == NULL)
        return;
    printf("%d, %s, %d, %s\n", l->ev.id, l->ev.ora, l->ev.potenza, l->ev.stato);
    stampa(l->n);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// carica
//    carica i dati nella lista generale
// parametri:
//        FILE *f     : descrittore del file già aperto
// return
//        lista modificata
lista_evento_t carica(FILE* f)
{
    // A CURA DELLO STUDENTE
    lista_evento_t ListaEventi = NULL;
    evento_t e;
    while (fscanf(f, "%d%s%d%s", &e.id, e.ora, &e.potenza, e.stato) == 4)
    {
        ListaEventi = aggiungi_ordine(ListaEventi, e);
    }
    fclose(f);
    return ListaEventi;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // distribuisci
  //    la funzione copia i valori presenti nella lista in ingressonel vettore di liste ordinate in base al
  //    valore dell'identificativo
  // parametri:
  //    lista_evento_t l    : lista in ingresso
  //    vettore_eventi_t    : vettore risultante
  // return:
  //    non usato
void distribuisci(lista_evento_t l, vettore_eventi_t v) 
{
    //A CURA DELLO STUDENTE
    if (l == NULL)
        return;
    while (l != NULL) 
    {
        v[l->ev.id] = aggiungi_ordine(v[l->ev.id], l->ev);
        l = l->n;
    }
}

// tempo
//    calcola quanti l'intervallo di tempo, in minuti, fra due eventi a < b. Nota che il calcola presume 
//    che gli eventi siano accaduti nella stessa giornata (non sono presenti eventi a cavallo della mezzanotte)
// parametri
//    evento_t    a, b    : eventi in ingresso
// return
//    intervallo di tempo in minuti (intero)
int tempo(evento_t a, evento_t b) {
    int ha, ma, hb, mb;
    sscanf(a.ora, "%d:%d", &ha, &ma);
    sscanf(b.ora, "%d:%d", &hb, &mb);
    int t = (hb * 60 + mb) - (ha * 60 + ma);
    return (t > 0) ? t : -t;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // calcolo_consumo_dispositivo
  //    calcola il consumo di un dispositivo usando la lista ordinata degli eventi che garantisce che un evento
  //    di spegnimento segue sempre quello di accensione
  //    nel caso in cui l'evento di spegnimento non fosse presente si termina l'analisi e si restituisce il valore
  //    calcolato fino all'errore
  // parametri:
  //    vettore_eventi_t    v   : archivio dei dispositivi
  //    int id                  : identificatore del dispositivo
  // return
  //    valore (float) dell'energia consumata

float calcolo_consumo_dispositivo(vettore_eventi_t v, int id) 
{
    // A CURA DELLO STUDENTE
    float Energia = 0.0;
    int t = 0;
    lista_evento_t l = v[id];
    if (l == NULL)
        return 0.0;
    evento_t ev = { NULL };
    while (l != NULL) 
    {
        ev = l->ev;
        l = l->n;

        if ((strcmp(ev.stato, "ON") == 0) && (strcmp(l->ev.stato, "OFF") == 0)) 
        {
            t = tempo(ev, l->ev);
            Energia += (l->ev.potenza * t);
            l = l->n;
        }
        else
        {
            break;
        }
    }
    return Energia;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// calcolo_consumi
  //    calcola i consumi di tutti i dispositivi
  // parametri:
  //    vettore_eventi_t    v   : archivio dei dispositivi
  // return:
  //    vettore di long che contiene il consumo di ogni dispositivo
float* calcolo_consumi(vettore_eventi_t v) {
    // A CURA DELLO STUDENTE
    lista_evento_t aux;
    evento_t ev = { NULL };
    float Energia;
    int t;
    float* vout = (float*)malloc(sizeof(float) * NUMERO_MASSIMO_DISPOSITIVI);
    for (int i = 0; i < NUMERO_MASSIMO_DISPOSITIVI; i++) 
    {
        aux = v[i];
        Energia = 0.0;
        if (aux == NULL)
        {
            Energia = 0.0F;
            vout[i] = Energia;
        }
        while (aux != NULL) 
        {
            ev = aux->ev;
            aux = aux->n;
            if ((strcmp(ev.stato, "ON") == 0) && (strcmp(aux->ev.stato, "OFF") == 0))
            {
                t = tempo(ev, aux->ev);
                Energia += (aux->ev.potenza * t);
                aux = aux->n;
            }
            else
            {
                break;
            }
            vout[i] = Energia;
        }
    }
    return vout;
}

void VisualizzaLista(lista_evento_t listaeventi) 
{
    while (listaeventi != NULL) 
    {
        printf("%d %s %d %s\n", listaeventi->ev.id, listaeventi->ev.ora, listaeventi->ev.potenza, listaeventi->ev.stato);
        listaeventi = listaeventi->n;
    }
}

void VisualizzaVettore(vettore_eventi_t v, int dim) 
{
    for (int i = 0; i < dim; i++) 
    {
        printf("ID: %d\nELENCO:\n", i);
        VisualizzaLista(v[i]);
        printf("\n");
    }
}

int main(void) {
    lista_evento_t valori_caricati = NULL;
    char NomeFile[64];
    vettore_eventi_t dispositivi = { NULL };
    float consumoTotale;
    float* ConsumoPerOgniDispositivo = NULL;
    int id;
    int scelta;
    do {
        printf("\n\n\n1. Carica i dati da file\n");
        printf("2, distribuisci i dati nel vettore di liste\n");
        printf("3. consumo totale\n");
        printf("4. consumo per dispositivo\n");

        printf("\n >> ");
        scanf("%d", &scelta);
        switch (scelta) {
        case 0:
            printf("Fine programma\n");
            break;
        default:
            printf("Valore di scelta non valido\n");
            break;
        case 1:
            // IMPLEMENTARE QUANTO NECESSARIO A CHIEDERE IL NOME DEL FILE DA CONSOLE,
            // APRIRE IL FILE, CHIAMARE LA FUNZIONE DI CARICAMENTO E STAMPARE IL RISULTATO.
            // VERIFICARE CHE LE STRUTTURE USATE SIANO VUOTE PRIMA DI USARLE
            printf("Inserisci nome del file: ");
            scanf("%s", NomeFile);
            FILE* fp = fopen(NomeFile, "r");
            if (fp == NULL)
                return 0;
            valori_caricati = carica(fp);
            if (valori_caricati != NULL)
                printf("Valori caricati correttamente.\n");
            VisualizzaLista(valori_caricati);
            break;

        case 2:
            // IMPLEMENTARE QUANTO NECESSARIO A COPIARE I VALORI DELLA LISTA NEL VETTORE DI
            // LISTA E STAMPARE IL CONTENUTO DI OGNUNA DI ESSE.
            // VERIFICARE CHE LE STRUTTURE SIANO VUOTE ED INIZIALIZZATE
            if ((valori_caricati != NULL))
            {
                distribuisci(valori_caricati, dispositivi);
                VisualizzaVettore(dispositivi, NUMERO_MASSIMO_DISPOSITIVI);
            }
            break;
        case 3:
            // IMPLEMENTARE QUANTO NECESSARIO A CALCOLARE E STAMPARE IL CONSUMO TOTALE USANDO
            // LE FUNZIONI RICHIESTE
            printf("Inserisci l'id: ");
            scanf("%d", &id);
            consumoTotale = calcolo_consumo_dispositivo(dispositivi, id);
            printf("Il consumo totale e' di %.3f.\n", consumoTotale);
            break;
        case 4:
            // IMPLEMENTARE QUANTO NECESSARIO A CALCOLARE E STAMPARE IL CONSUMO DI UN QUALSIASI
            // DISPOSITIVO RICHIESTO DALL'UTENTE
            ConsumoPerOgniDispositivo = calcolo_consumi(dispositivi);
            for (int i = 0; i < NUMERO_MASSIMO_DISPOSITIVI; i++) 
            {
                printf("v[%d] = %.2f\n", i, ConsumoPerOgniDispositivo[i]);
            }
            break;
        }
    } while (scelta != 0);
}