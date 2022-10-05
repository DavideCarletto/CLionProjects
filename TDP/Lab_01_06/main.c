#include <stdio.h>


float eseguiOperazione(float n1, float n2, char operazione);

int main() {
    FILE *fp_reader, *fp_writer ;
    char operazione;
    float n1, n2, risultato;
    fp_reader = fopen("../Operations.txt","r");
    fp_writer = fopen("../Results.txt","w");

    while(!feof(fp_reader)) {
        fscanf(fp_reader, "%c %f %f ", &operazione, &n1, &n2);
        risultato = eseguiOperazione( n1,  n2,  operazione);
        fprintf(fp_writer,"%c %.2f\n",operazione,risultato);
    }
    fclose(fp_reader);
    fclose(fp_writer);
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