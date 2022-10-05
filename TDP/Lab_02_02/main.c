#include <stdio.h>

/*
Scrivere un programma in linguaggio C che visualizzi i primi N numeri della serie di Fibonacci, con N
acquisito in input da tastiera.
Suggerimento: ecco i primi numeri appartenenti alla serie 0 1 1 2 3 5 8 … In modo formale la serie si
costruisce considerando la seguente relazione: Xi = Xi-1 + Xi-2, con X0 = 0 e X1 = 1;
Approfondimento (variante dell’esercizio): si modifichi la serie come segue:
Xi = Xi-1 * Xi-2, con X0 = 1 e X1 = 2;
Si determini sperimentalmente (osservando i risultati ottenuti) quanti sono gli elementi di questa serie
rappresentabili con variabili di tipo intero (int) e di tipo intero senza segno (unsigned int)
 */


void calcolaSerie(int n);

int main() {
    unsigned int n = 0;
    printf("Inserire in ingresso quanti numeri della serie si vuole visualizzare:");
    scanf("%d", &n);

    calcolaSerie(n);
    return 0;
}
void calcolaSerie(int n) {
    int risultato = 0, x0 = 0, x1 = 1;
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                risultato = x0;
            } else if (i == 1) {
                risultato = x1;
            } else {
                risultato = x0 + x1;
                x0 = x1;
                x1 = risultato;
            }
                printf("%d ", risultato);
    }
}