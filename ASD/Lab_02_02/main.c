#include <stdio.h>
#include <stdlib.h>

void malloc2dP (int ***mat, int *nr, int *nc);
int leggiFile(int ***mat, int *nr, int *nc);
void stampaMatrice(int ***mat, int *nr, int *nc);

int main() {
    int **mat, nr,nc;

    leggiFile(&mat, &nr, &nc);
    stampaMatrice(&mat, &nr, &nc);

    return 0;
}

int leggiFile(int ***mat, int *nr, int *nc){
    FILE *fin;
    if((fin = fopen("../mat.txt","r"))==NULL){
        printf("Error opening file...");
        return 1;
    }

    fscanf(fin, "%d %d", nr, nc);
    malloc2dP(mat, nr,nc);


    for (int i = 0; i < *nr; ++i) {
        for (int j = 0; j < *nc; ++j) {
            fscanf(fin, "%d", ((*mat)[i])+j);
        }
    }

    fclose(fin);

    return 0;
}

void malloc2dP(int ***mat, int *nr, int *nc){
    int **m;

    m = (int **) malloc(*nr *sizeof (int *));

    for(int i=0; i<*nr; i++){
        m[i] = (int *) malloc(*nc *sizeof (int));
    }
    *mat = m;
}

void stampaMatrice(int ***mat, int *nr, int *nc){
    for(int i=0; i<*nr; i++){
        for(int j=0; j<*nc; j++){
            printf("%d ", *((*mat)[i])+j);
        }
        printf("\n");
    }
}