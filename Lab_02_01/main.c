#include <stdio.h>

/*
Scrivere un programma C che, acquisiti 2 numeri interi positivi ne calcoli il massimo comune divisore
utilizzando la formula di Eulero.
Formula di Eulero o metodo dei resti: si procede per divisioni successive del numero maggiore per
quello minore, sostituendo ad ogni passo il valore maggiore con il minore ed il minore
col resto della divisione. Il processo termina quando il resto è 0
 */

int calcolaMCD(int n1, int n2);

int main() {
    int n1, n2, min = 0, max = 0;
    printf("Inserire i due numeri interi positivi su cui si vuole calcolare il MCD:");
    scanf("%d %d", &n1, &n2);

    if (n1 != 0 && n2 != 0) {
        if (n1 > n2) {
            max = n1;
            min = n2;
        } else if (n1 < n2) {
            min = n1;
            max = n2;
        } else {
            min = n1;
            max = n1;
        }
        printf("A = %d, B = %d\n", n1, n2);
        printf("Risultato: MCD = %d ", calcolaMCD(min, max));
    }else{
        printf("Impossibile eseguire l'operazione (uno dei due numeri e' 0!)");
    }


    return 0;
}

int calcolaMCD(int min, int max) {
    int MCD = 0, resto = 0;

    do {
        resto = max % min;
        if (resto != 0) {
            max = min;
            min = resto;
        } else {
            MCD = min;
        }
    } while (resto != 0);

    return MCD;

}