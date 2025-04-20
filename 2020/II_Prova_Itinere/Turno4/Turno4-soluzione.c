/*
Sviluppo di applicazione in ANSI C per gestire i viaggi di una flotta aziendale di veicoli

In un archivio memorizzato su un file di testo (allegato "viaggi.txt") è memorizzato
l'elenco dei viaggi effettuati dai diversi veicoli.
Ogni viaggio è memorizzato su una riga del file, con i campi:
id viaggio, targa veicolo, km percorsi, costo viaggio.

Implementare le seguenti funzioni:

1. CaricaViaggi: carica l'elenco dei viaggi effettuati dalla flotta (lettura del file; ogni id viaggio è presente solo una volta nel file).
2. AggiungiViaggio: dato un id viaggio, km e costo, se l'id esiste già in lista si sommano ai valori già presenti in lista,
in caso contrario inserisce un nuovo viaggio nella lista
(fornendo da tastiera in tal caso anche la targa)
3. TotaleVeicolo: Data una targa, stampa il totale dei km percorsi ed il costo medio per km di tutti i viaggi ad essa associati

*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>

typedef struct Viaggio {
  char  id_viaggio[5]; 
  char  targa[9];
  int   km;
  float costo;
} TViaggio;

typedef struct NodoLista {
  TViaggio info;
  struct NodoLista* next;
} TNodoLista;

typedef TNodoLista* TipoLista;

/* ListaAggiungi inserisce un elemento in testa alla lista passata
   come primo parametro. Restituisce 1 se l'operazione va a buon fine,
   0 altrimenti */
int ListaAggiungi(TipoLista* plista, TViaggio viaggio)
{
  TipoLista aux;

  aux = (TipoLista)malloc(sizeof(TNodoLista));

  if (aux == NULL)
    return 0;
  
  aux->info = viaggio;
  aux->next = *plista;

  *plista = aux;
  
  return 1;
}

/* 
1. CaricaViaggi: carica l'elenco dei viaggi effettuati dalla flotta (lettura del file; ogni id viaggio è presente solo una volta nel file) in una lista di viaggi
  Restituisce 1 se l'operazione va a buon fine, 0    altrimenti.
*/
int CaricaViaggi(TipoLista* plista, char* nome_file)
{  
	FILE* fp;
    TViaggio v;

    *plista = NULL;

    fp = fopen(nomefile, "r");
     if (fp == NULL)
        return 0;

    while (!feof(fp)) {
        if (fscanf(fp, "%s%s%d%f", v.id_viaggio, v.targa, &v.km, &v.costo) == 4) {
            ListaAggiungi(plista, v);
        }
    }

    fclose(fp);

    return 1;
}

/* 
 2. AggiungiViaggio: dati come parametri di ingresso un id_viaggio, km e costo, 
 se l'id_viaggio esiste già in lista, i km ed il costo si sommano ai valori già presenti in lista, 
	in caso contrario si inserisce un nuovo viaggio nella lista (fornendo da tastiera in tal caso la targa)
*/
void AggiungiViaggio(TipoLista* lista,
		   char* id_viaggio, int km, float costo) {
	TipoLista aux=*lis;
	int trovato=0; 
	while ((aux!=NULL)&& (trovato==0))
		if (strcmp(aux->id_viaggio, id_viaggio)==0) {
			aux->km+=km;
			aux->costo+=costo;
			trovato=1;
			}
		else aux=aux->next;
	if (trovato==0) {
		TViaggio tmp;
		printf("viaggio non presente, inserisci la targa");
		scanf("%s",tmp.targa);
		strcpy(tmp.id_viaggio, id_viaggio);
		tmp.km=km;
		tmp.costo=costo;
		ListaAggiungi(lista, tmp);
	}
}

/*
3. TotaleVeicolo: Data in ingresso una targa, restituisce il totale dei km percorsi di quell'auto
ed il costo medio per km di tutti i viaggi ad essa associati
*/
void TotaleVeicolo(TipoLista lista, char* targa, float* totkm, float* costomedio) {
	float totcosto=0.0;
    *totkm = 0;
    *costomedio=0.0
  	while (lista!=NULL) {
		if (strcmp(lista->targa, targa)==0 {
			*totkm+=lista->km;
			totcosto+=lista->costo;
		}
        if (*totkm!=0)
        	*costomedio= totcosto/(*totkm);
	}
}

int Menu() {
  int scelta;
  
  printf("*** M E N U ***\n"
	 "1 - CaricaViaggi\n"
	 "2 - AggiungiViaggio\n"
	 "3 - TotaleVeicolo\n"
	 "0 - Uscita\n\n"
	 "Scelta: ");
  scanf("%d", &scelta);

  return scelta;
}

void VisualizzaLista(TipoLista lis) {

    while (lis != NULL) {
        printf("Id viaggio: %s\n", lis->info.id_viaggio);
        printf("Targa: %s\n", lis->info.targa);
        printf("Km: %d\n", lis->info.km);
        printf("Costo: %f\n\n", lis->info.costo);
        lis = lis->next;
    }
}

void DisallocaLista(TipoLista lista) {
  TipoLista p;

  while (lista != NULL)
    {
      p = lista;
      lista = lista->next;
      free(p);
    }
}

int main(void) {
  TipoLista lista;
  int        scelta;
 // allocare le variabili necessarie...
	char buffer[64], targa[9];
	char id_viaggio[5];
	int km;
	float costo;
	int totkm;
	float costomedio;
  
  do {
    scelta = Menu();

    switch (scelta)
      {
      case 1:
	// Invocare la funzione CaricaViaggi e visualizzare un messaggio in caso di errore
		printf("Inserisci il nome del file: ");
		scanf("%s", buffer);
		if (CaricaViaggi(&lista, buffer)==0) printf("ERRORE");
		else printf("caricamento corretto");
        VisualizzaLista(lista);
		break;

      case 2:
	// Invocare la funzione AggiungiViaggio, caricando prima da tastiera i valori da passare come parametri
	printf("inserisci id_viaggio, km e costo: ");
	scanf("%s", id_viaggio);
	scanf("%d", &km);
	scanf("%f", &costo);
	AggiungiViaggio(&lista,id_viaggio, km, costo);
	break;

      case 3:
	// Invocare la funzione TotaleVeicolo, acquisendo preventivamente la targa da tastiera
	// Visualizzare km totali e costo medio per km (restituiti dalla funzione)
	printf("inserisci targa da cercare: ");
	scanf("%s", targa);
    TotaleVeicolo(lista, targa, &totkm, &costomedio);
	printf("Totale km %d, con un costo medio per km pari a %f", totkm, costomedio);
	break;
      }
    
  } while (scelta != 0);

  DisallocaLista(lista); // passare il parametro opportuno
  
  return 0;
}

