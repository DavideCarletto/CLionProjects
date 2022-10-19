#include <stdio.h>
#include <stdlib.h>

void malloc2dP (int ***mat, int *nr, int *nc);
int leggiFile(int ***mat, int *nr, int *nc);
void stampaMatrice(int **mat, int nr, int nc);
void separa(int **mat, int nr, int nc, int *v1, int *v2, int *dim1, int *dim2);
void stampaVettori(int *v1, int *v2, int dim1, int dim2);

int main() {
    int **mat, nr,nc,*v1,*v2,dim1=0,dim2=0;

    leggiFile(&mat, &nr, &nc);

    v1 = (int *) malloc(nr*nc*sizeof (int));
    v2 = (int *) malloc(nr*nc*sizeof (int));

    stampaMatrice(mat, nr, nc);
    separa(mat,nr, nc, v1, v2,&dim1, &dim2);
    stampaVettori(v1,v2, dim1, dim2);

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

void separa(int **mat, int nr, int nc, int *v1, int *v2, int *dim1, int *dim2){
    int count1=0, count2=0;

    for(int i=0; i<nr; i++){
        for(int j=0; j<nc; j++){
            if((i+j)%2==0)
                v1[count1++]=mat[i][j];
            else
                v2[count2++] = mat[i][j];
        }
    }
    *dim1 = count1;
    *dim2 = count2;
}

void stampaVettori(int *v1, int *v2, int dim1, int dim2){
    printf("Caselle bianche della matrice: ");

    for (int i = 0; i < dim1; ++i) {
        printf("%d ", v1[i]);
    }
    printf("\n");
    printf("Caselle nere della matrice: ");

    for (int j = 0; j < dim2; ++j) {
        printf("%d ", v2[j]);
    }
}


void stampaMatrice(int **mat, int nr, int nc){
    printf("Matrice letta:\n");
    for(int i=0; i<nr; i++){
        for(int j=0; j<nc; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
