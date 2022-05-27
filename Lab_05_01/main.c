#include <stdio.h>

typedef struct Squadra {
    int somma;
} Squadra;

void stampaCapolista(int matrice[20][20], int row, int col);
int main() {
    FILE *fin;
    int matrice[20][20], row=0, col=0;

    if ((fin = fopen("../mat.txt", "r")) == NULL) {
        printf("Error opening file...");
        return 1;
    }

    fscanf(fin, "%d %d", &row, &col);

    for(int i=0; i<row;i++){
        for(int j =0; j<col;j++){
            fscanf(fin,"%d",&matrice[i][j]);
        }
    }

    stampaCapolista(matrice, row, col);
    return 0;
}

void stampaCapolista(int matrice[20][20], int row, int col) {
    Squadra squadre[20];
    int punteggio;

    for (int j = 0; j < col; j++) {
        int max,index;
        printf("Giornata %d\n",j+1);
        for (int i = 0; i < row; i++) {
            punteggio = matrice[i][j];
            squadre[i].somma+=punteggio;
            if(squadre[i].somma>max) {
                max = squadre[i].somma;
                index = i;
            }
        }
        printf("Squadra capolista:%d\n\n",index+1);
    }
}