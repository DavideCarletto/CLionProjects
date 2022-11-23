#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char cT1, cT2;
    int vT1, vT2;
}tessera;

typedef struct{
    int tessera, rotation;
}cella;

void leggiFile(FILE *fp1, FILE *fp2, int T, int R, int C, tessera *elencoTessere, cella **elencoCelle, int *mark);
void allocaTutto(tessera **elencoTessere, int T, cella ***elencoCelle, int R, int C);
void stampaTessere(tessera *elencoTessere, int T);
void stampaCelle(cella **elencoCelle, int R, int C);
void stampaSoluzione(tessera *elencoTessere,cella **elencoCelle, int R, int C);
void disp_semplici(int pos, int *mark, tessera *elencoTessere, cella **elencoCelle, int R, int C, int T);
int controlla(tessera *elencoTessere, cella **elencoCelle, int R, int C, int pos);

int main() {
    FILE *fp1, *fp2;
    int T,R,C, *mark;
    tessera *elencoTessere;
    cella **elencoCelle;

    if((fp1 = fopen("../E2/tiles.txt","r"))==NULL){
        printf("Error opening file...");
        return 1;
    }
    if((fp2 = fopen("../E2/board.txt","r"))==NULL){
        printf("Error opening file...");
        return 1;
    }

    fscanf(fp1,"%d\n", &T);
    fscanf(fp2, "%d %d\n", &R,&C);

    allocaTutto(&elencoTessere,T, &elencoCelle, R, C);

    mark = calloc(T, sizeof (int));
    leggiFile(fp1, fp2, T, R, C, elencoTessere, elencoCelle, mark);

    stampaCelle(elencoCelle, R, C);

    disp_semplici(0, mark,elencoTessere, elencoCelle, R, C, T);

    return 0;
}


void leggiFile(FILE *fp1, FILE *fp2, int T, int R, int C, tessera *elencoTessere, cella **elencoCelle, int *mark){
    int i;

    for(i =0; i<T; i++){
        if(!feof(fp1)){
            fscanf(fp1, "%c %d %c %d\n", &elencoTessere[i].cT1, &elencoTessere[i].vT1, &elencoTessere[i].cT2, &elencoTessere[i].vT2);
        }
    }
    stampaTessere(elencoTessere, T);

    for(i =0; i<R; i++){
        for(int j=0; j<C; j++){
            fscanf(fp2, "%d/%d\n",&elencoCelle[i][j].tessera,&elencoCelle[i][j].rotation);
            if(elencoCelle[i][j].tessera!=-1)
                mark[elencoCelle[i][j].tessera] = 1;
        }
    }
}


void allocaTutto(tessera **elencoTessere, int T, cella ***elencoCelle, int R, int C){
    cella **m;

    *elencoTessere = (tessera*) malloc(T* sizeof(tessera));

    m = (cella **) malloc(R *sizeof (cella *));

    for(int i=0; i<R; i++){
        m[i] = (cella *) malloc(C *sizeof (cella));
    }
    *elencoCelle = m;

}



void stampaTessere(tessera *elencoTessere, int T){
    for(int i=0; i<T; i++){
        printf("%c %d %c %d\n",elencoTessere[i].cT1, elencoTessere[i].vT1, elencoTessere[i].cT2, elencoTessere[i].vT2);
    }
    printf("\n");
}

void stampaCelle(cella **elencoCelle, int R, int C){
    for(int i =0; i<R; i++){
        for(int j=0; j<C; j++){
            printf("%d/%d ",elencoCelle[i][j].tessera,elencoCelle[i][j].rotation);
        }
        printf("\n");
    }
    printf("\n");
}

void stampaSoluzione(tessera *elencoTessere,cella **elencoCelle, int R, int C){
    int indexTessera = 0;

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(elencoCelle[i][j].tessera!=-1){
                indexTessera = elencoCelle[i][j].tessera;
                if(elencoCelle[i][j].rotation== 0)
                    printf("\t%c \n%c \t\t%d \n\t%d",elencoTessere[indexTessera].cT2, elencoTessere[indexTessera].cT1, elencoTessere[indexTessera].vT1, elencoTessere[indexTessera].vT2);
                else
                    printf("\t%c \n%c \t\t%d \n\t%d",elencoTessere[indexTessera].cT1, elencoTessere[indexTessera].cT2, elencoTessere[indexTessera].vT2, elencoTessere[indexTessera].vT1);

                printf("\t");
            }
        }
        printf("\n\n\n\n\n");
    }
}

void disp_semplici(int pos, int *mark, tessera *elencoTessere, cella **elencoCelle,int R, int C, int T){
    int i, j;

    if(pos >= R*C){
        stampaCelle(elencoCelle,R,C);
        return;
    }

    i = pos / (R);
    j = pos % (C);


    if(elencoCelle[i][j].tessera!= -1){
        disp_semplici(pos+1, mark, elencoTessere, elencoCelle, R, C,T);
        return;
    }

    for(int k = 0; k<T; k++){
        if(mark[k]==0) {
            mark[k]=1;
            elencoCelle[i][j].tessera = k;
            elencoCelle[i][j].rotation = 0;

            if (controlla(elencoTessere, elencoCelle, R, C, pos)) {
                disp_semplici(pos + 1, mark, elencoTessere, elencoCelle, R, C, T);
            }

            elencoCelle[i][j].rotation = 1;
            disp_semplici(pos, mark, elencoTessere, elencoCelle, R, C,T);

            elencoCelle[i][j].tessera = -1;
            elencoCelle[i][j].rotation = -1;
            mark[k] = 0;
        }
    }
}

int controlla(tessera *elencoTessere, cella **elencoCelle, int R, int C, int pos){
   int i, j, okCol = 1;
   char cT1, cT2;

   i = pos / (R);
   j = pos % (C);

   if(elencoCelle[i][j].rotation == 1) {
       cT1 = elencoTessere[elencoCelle[i][j].tessera].cT2;
       cT2 = elencoTessere[elencoCelle[i][j].tessera].cT1;
   }
   if(elencoCelle[i][j].rotation==0)
   {
       cT1 = elencoTessere[elencoCelle[i][j].tessera].cT1;
       cT2 = elencoTessere[elencoCelle[i][j].tessera].cT2;
   }

   for(int c = 0; c<C; c++){
       if(c!= j && elencoCelle[i][c].tessera!=-1)
           if(cT1 != elencoTessere[elencoCelle[i][c].tessera].cT1)
               okCol = 0;
   }

   if(!okCol) {
       for (int r = 0; r < R; r++) {
           if (r != i && elencoCelle[r][j].tessera!=-1)
               if (cT2 != elencoTessere[elencoCelle[r][j].tessera].cT2)
                   return 0;
       }
   }
   return 1;
}
