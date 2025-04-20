/*
  Scaricare l'esercizio e completarlo inserendo il codice necessario
  senza modificare quello esistente tranne quando espressamente
  richiesto.

  L'esercizio si considera corretto se il programma compila
  correttamente ed esegue senza errori run-time dando i risultati
  attesi.

  Il file sorgente deve essere consegnato allegandolo a questa
  attività.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
    La funzione AcquisisciOttale legge una stringa e verifica che sia
    formata soltanto dai caratteri da '0' a '7'. Restituisce 1 se la
    stringa acquisita rispetta il suddetto requisito.
 */
int AcquisisciOttale(char* oct_str)
{
    int i, n;

    scanf("%s", oct_str);

    n = strlen(oct_str);

    for (i = 0; i < n; i++)
        if (oct_str[i] < '0' || oct_str[i] > '7')
            return 0;

    return 1;
}


/*
  La funzione OctBin converte una cifra ottale, 'oct', nella
  corrispondente sequenza di 3 bit, 'bin_str'.
 */
void OctBin(char oct, char* bin_str)
{
    char* oct_bin[8] = { "000", "001", "010", "011", "100", "101", "110", "111" };

    strcpy(bin_str, oct_bin[oct - '0']);
}

/*
  La funzione Oct2Bin converte un numero ottale nel corrispondente
  binario.

  Suggerimento: utilizzare la funzione OctBin per convertire una una
  cifra ottale nella corrispondente sequenza di 3 bit.
 */
void Oct2Bin(char * NumeroOttale, char * NumeroBinario)
{
    // ...da implementare a cura dello studente...
    char cifra[4] = "";
    int index;
    int j = 0;
    for (int i = 0; NumeroOttale[i] != '\0'; i++) 
    {
        index = 0;
        OctBin(NumeroOttale[i], cifra);
        while (index < strlen(cifra)) 
        {
            NumeroBinario[j] = cifra[index];
            index++;
            j++;
        }
    }
    NumeroBinario[j] = '\0';
}


/*
  La funzione VisualizzaBin visualizza la stringa binaria.
 */
void VisualizzaBin(char* bin_str)
{
    // ...da implementare a cura dello studente...
    printf("%s", bin_str);
}


int main(void)
{
    char  oct_str[256];
    char* bin_str;
    int   n;

    /*
      Acquisire la stringa ottale ed assicurarsi che contenga solo
      caratteri da '0' a '7'.
    */
    // ...istruzioni...
    n = AcquisisciOttale(oct_str);
    /*
       Alloca la stringa binaria che conterrà un numero di caratteri
       pari a 3 volte quelli della stringa ottale.
    */
    // ...istruzioni...
    int dim = strlen(oct_str);
    bin_str = (char*)malloc(sizeof(char) * ((3 * dim) + 1));
    if (bin_str == NULL)
        return 0;
    /*
       Invocare la funzione Oct2Bin per convertire il numero ottale in
       binario.
    */
    Oct2Bin(oct_str, bin_str);

    /*
      Invocare la funzione VisualizzaBin per visualizzare il numero
      binario.
    */
    VisualizzaBin(bin_str);

    /*
      Disallocare la stringa bin_str
    */
    // ...istruzioni...
    free(bin_str);
    return 0;
}
