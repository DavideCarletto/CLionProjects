#include <stdio.h>
#include <stdlib.h>
float eseguiOperazione(float n1, float n2, char operazione);

int main() {
    float n1, n2;

    printf("Inserire l'operazione da eseguire ('+','-','*','/'):");
    char operazione = getchar();

    printf("Inserire i due valori su cui si vuole eseguire l'operazione '%c' (separati da uno spazio):", operazione);
    scanf("%f %f", &n1,&n2);

    float risultato = eseguiOperazione(n1, n2, operazione);
    printf("%c %.3f", operazione,risultato);

    return 0;
}

float eseguiOperazione (float n1, float n2, char operazione){
    float risultato = 0.0;

    switch (operazione) {
        case '+':
            risultato = n1+n2;
            break;
        case '-':
            risultato = n1-n2;
            break;
        case '*':
            risultato = n1*n2;
            break;
        case '/':
            risultato = n1/n2;
            break;
        default:
            printf("Errore: comando non trovato.");
    }
    return risultato;
}