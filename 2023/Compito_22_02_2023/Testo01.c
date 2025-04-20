/*
Scrivere un progamma, in ANSI C che, elabora tre serie di valori di temeperature rivelate nell'ambiente 
salvati come valori reali in tre file distinti organizzati in modo che il dato presente nella riga n-esima
di un file sia correlato ai dati presenti nella stessa riga

Le operazioni da svolgere sono le seguenti:
1. caricamento della media dei valori presenti nelle righe corrispondenti dei tre file in
un vettore di numeri reali e stampa su console del risultato;
2. Dato da tastiera un intervallo contare e stampare il rapporto fra i valori contenuti nel
vettore delle medie compresi nell'intervallo e il numero di rilevaioni totali;
3. Salvare in un file di testo i valori compresi nell'intervallo presenti nel vettore delle medie.

Vincoli:
1. i nomi dei file, sia di ingresso che uscita, devono essere letti da console
2. il numero di valori presenti nel file è compreso nell'intervallo [0,50] (estremi compresi)

Il contenuto del vettore delle medie con i dati contenuti nei file alegati all'esercizio è il seguente:
34.50
186.42
165.05
184.45
34.75
179.21
158.07
107.60
17.45
195.36
151.80
195.01
165.25
169.40
151.28
186.65
190.91
178.41
149.44
31.96
78.99
169.18
112.72
247.13
147.33
197.27
178.93
215.61
288.16
177.54
135.50
67.32
160.57
167.17
250.10

inserendo un intervallo [100,200] il rapporto è pari a 0.171429
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
