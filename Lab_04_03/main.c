#include <stdio.h>

void stampaSottomatrici(int matrice[20][20],int dim,int row,int col);
void stampaSottomatriceMassima(int startRow, int startCol, int matrice[20][20],int dim, int somma);

int main() {
    FILE *fin;
    int row,col, min, dim,matrice[20][20];

    if ((fin = fopen("../Matrici.txt", "r")) == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fscanf(fin,"%d %d", &row,&col);

    if(row<col)
        min = row;
    else
        min = col;

    setbuf(stdout,0);

    for(int i=0; i<row;i++){
        for(int j =0; j<col;j++){
            fscanf(fin,"%d",&matrice[i][j]);
        }
    }
    do{
        printf("Inserire la dimensione delle sottomatrici quadrate:");
        scanf("%d", &dim);

        if(dim >=1 && dim<=min)
        stampaSottomatrici(matrice,dim,row,col);
    }while(dim >=1 && dim<= min);

    return 0;
}

void stampaSottomatrici(int matrice[20][20], int dim,int row,int col ){
    int startRow=0, startCol=0,terminato =0, max,maxRow,maxCol;
    printf("Le sottomatrici quadrate di dimensione %d sono:\n\n",dim);
    while(!terminato) {
        int somma =0;
        for (int i = startRow; i < dim+startRow && i < row; i++) {
            for (int j = startCol; j < dim+startCol && j < col; j++) {
                printf(" %d ", matrice[i][j]);
                somma+= matrice[i][j];
            }
            printf("\n");
        }
        if(somma > max){
            max = somma;
            maxRow = startRow;
            maxCol = startCol;
        }
        printf("\n");

            if (startCol+dim == col) {
                startRow++;
                startCol = 0;
            } else
                startCol++;

        if(startRow+dim >row) {
            terminato = 1;
        }

    }
    stampaSottomatriceMassima(maxRow,maxCol, matrice, dim,max);

}

void stampaSottomatriceMassima(int startRow, int startCol, int matrice[20][20], int dim, int somma){
    printf("La sottomatrice con somma degli elementi massima (%d) e'\n\n",somma);
    for (int i = startRow; i < dim+startRow; i++) {
        for (int j = startCol; j < dim+startCol; j++) {
            printf(" %d ", matrice[i][j]);
        }
        printf("\n");
    }
}