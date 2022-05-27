#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void ruota(int v[], int n, int p, int dir);

void printArray(int v[], int n);

int main() {
    int end = 0, n, p, dir;
    do {
        printf("Inserire la lunghezza del vettore (<=30): ");
        scanf("%d", &n);
        fflush(stdin);
    } while ((n > 30) || (n < 1));

    int v[n];

    for (int i = 0; i < n; i++) {
        printf("Elemento %d del vettore:", i + 1);
        scanf("%d", &v[i]);
        fflush(stdin);
    }

    do {
        printf("Inserire il numero di spostamenti da effetturare e la direzione di tale spostamento (1 verso destra, -1 verso sinistra):");
        scanf("%d %d", &p, &dir);
        fflush(stdin);
        if (p == 0) {
            end = -1;
        } else {

            if (p < n && (dir == 1 || dir == -1)) {
                ruota(v, n, p, dir);
            } else
                printf("Input non valido.\n");
        }
    } while (!end);

    return 0;
}


void ruota(int v[], int n, int p, int dir) {
    printf("vettore iniziale: ");
    printArray(v, n);

    int* z = (int*) malloc(sizeof (int)*n);

    for (int i = 0; i < n; i++) {
        if (dir == 1)
            z[(i + p) % n] = v[i];
        else
            z[n - ((i + p) % n) - 1] = v[n - 1 - i];
    }
    memcpy(v,z,sizeof (int)*n);
    free(z);

    printf("vettore ruotato: ");
    printArray(v, n);

}
void printArray(int v[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf(" %d ", v[i]);
    }
    printf("]\n");
}