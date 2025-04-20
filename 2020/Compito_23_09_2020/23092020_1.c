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
    La funzione AcquisisciBinario legge una stringa e verifica che sia
    formata soltanto dai caratteri '0' e '1' e che il numero di
    caratteri della stringa sia multiplo di 4. Restituisce 1 se la
    stringa acquisita rispetta i suddetti requisiti.
 */
int AcquisisciBinario(char* bin_str)
{
    int i, n;

    scanf("%s", bin_str);

    n = strlen(bin_str);
    if (n % 4 != 0)
        return 0;

    for (i = 0; i < n; i++)
        if (bin_str[i] != '0' && bin_str[i] != '1')
            return 0;

    return 1;
}


/*
  La funzione Bits4Hex converte la stringa binaria di 4 bit bits4
  nella corrispondente cifra esadecimale.
 */
char Bits4Hex(char* bits4)
{
    char hex[] = "0123456789ABCDEF";
    int  i;

    i = (bits4[0] - '0') * 8 + (bits4[1] - '0') * 4 + (bits4[2] - '0') * 2 + (bits4[3] - '0') * 1;

    return hex[i];
}

/*
  La funzione Bin2Hex converte un numero binario nel corrispondente
  esadecimale. Il numero binario è rappresentato da una stringa di
  caratteri '1' e '0' la cui dimensione è multiplo di 4. La funzione
  opera su gruppi di sequenze di 4 bit convertendo ogni sequenza nella
  corrispondente cifra esadecimale da 0 a F.

  Suggerimento: utilizzare la funzione Bits4Hex per convertire una una
  sequenza di 4 bit nella corrispondente cifra esadecimale.
 */
void Bin2Hex(char* bin_str, char* hex_str)
{
    // ...implementare a cura dello studente...
    char Cifra[5];
    int index = 0;
    char CifraHex;
    int cont = 0;
    for (int i = 0; bin_str[i] != '\0'; i++) 
    {
        Cifra[cont++] = bin_str[i];
        if (cont == 4)
        {
            Cifra[4] = 0;
            CifraHex = Bits4Hex(Cifra);
            hex_str[index++] = CifraHex;
            cont = 0;
        }
    }
    hex_str[index] = 0;
}


/*
  La funzione VisualizzaHex visualizza la stringa di cifre esadecimali
  in ordine inverso e inserendo un carattere di spazio ogni n cifre
  con n passato come parametro. Es. se la stringa di cifre esadecimale
  è 34A5F2 ed n è 3, divrà essere visualizzato 2F5 A43.
 */
void VisualizzaHex(char * stringa, int n)
{
    // ...implementare a cura dello studente...
    int LunghezzaStringa = (strlen(stringa)-1);
    int num = 0;
    for (int i = LunghezzaStringa; i >= 0; i--) 
    {
        printf("%c", stringa[i]);
        num++;
        if (num == n) 
        {
            printf(" ");
            num = 0;
        }
    }
}


int main(void)
{
    char  bin_str[256];
    char* hex_str;
    int   n;

    /*
      Acquisire la stringa binaria ed assicurarsi che contenga solo
      caratteri '0' e '1'.
    */
    // ...istruzioni...
    AcquisisciBinario(bin_str);

    /*
       Alloca la stringa esadecimale che conterrà un numero di caratteri
       pari ad 1/4 di quelli della stringa binaria.
    */
    //...istruzioni...
    int LunghezzaStringaHex = (strlen(bin_str))/4;
    hex_str = (char*)malloc((sizeof(char) * (LunghezzaStringaHex + 1)));
    if (hex_str == NULL)
        return 0;

    /*
       Invocare la funzione Bin2Hex per convertire il numero binario in
       esadecimale.
    */
    //...istruzioni...
    Bin2Hex(bin_str, hex_str);

    /*
      Invocare la funzione VisualizzaHex per visualizzare il numero
      esadecimale 2 caratteri per volta.
    */
    //...istruzioni...

    VisualizzaHex(hex_str, 2);
    /*
      Disallocare la stringa hex_str
    */
    //...istruzioni...
    free(hex_str);

    return 0;
}
