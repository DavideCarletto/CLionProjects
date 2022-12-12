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
void allocaTutto(tessera **elencoTessere, int T, cella ***elencoCelle, cella ***sol, int R, int C);
void stampaTessere(tessera *elencoTessere, int T);
void stampaCelle(cella **elencoCelle, int R, int C);
void disp_semplici(int pos, int *mark, tessera *elencoTessere, cella **elencoCelle, cella **b_sol,int R, int C, int T, int c_max, int *b_max);
int controlla(tessera *elencoTessere, cella **elencoCelle, int R, int C, int pos);
int calcolaPunteggio(tessera *elencoTessere, cella **elencoCelle, int R, int C);

int main() {
    FILE *fp1, *fp2;
    int T,R,C, *mark, max =0;
    tessera *elencoTessere;
    cella **elencoCelle, **sol;

    if((fp1 = fopen("../tiles.txt","r"))==NULL){
        printf("Error opening file...");
        return 1;
    }
    if((fp2 = fopen("../board.txt","r"))==NULL){
        printf("Error opening file...");
        return 1;
    }

    fscanf(fp1,"%d\n", &T);
    fscanf(fp2, "%d %d\n", &R,&C);

    allocaTutto(&elencoTessere,T, &elencoCelle, &sol, R, C);

    mark = calloc(T, sizeof (int));
    leggiFile(fp1, fp2, T, R, C, elencoTessere, elencoCelle, mark);

//    stampaCelle(elencoCelle, R, C);

    disp_semplici(0, mark,elencoTessere, elencoCelle, sol, R, C, T, 0, &max);

    printf("Soluzione con punteggio massimo (%d):\n\n",max);
    stampaCelle(sol,R,C);

    free(elencoTessere);
    free(elencoCelle);

    return 0;
}


void leggiFile(FILE *fp1, FILE *fp2, int T, int R, int C, tessera *elencoTessere, cella **elencoCelle, int *mark){
    int i;

    for(i =0; i<T; i++){
        if(!feof(fp1)){
            fscanf(fp1, "%c %d %c %d\n", &elencoTessere[i].cT1, &elencoTessere[i].vT1, &elencoTessere[i].cT2, &elencoTessere[i].vT2);
        }
    }
//    stampaTessere(elencoTessere, T);

    for(i =0; i<R; i++){
        for(int j=0; j<C; j++){
            fscanf(fp2, "%d/%d\n",&elencoCelle[i][j].tessera,&elencoCelle[i][j].rotation);
            if(elencoCelle[i][j].tessera!=-1)
                mark[elencoCelle[i][j].tessera] = 1;
        }
    }
}


void allocaTutto(tessera **elencoTessere, int T, cella ***elencoCelle, cella ***sol, int R, int C){
    cella **m, **m_s;

    *elencoTessere = (tessera*) malloc(T* sizeof(tessera));

    m = (cella **) malloc(R *sizeof (cella *));
    m_s = (cella **) malloc(R *sizeof (cella *));

    for(int i=0; i<R; i++){
        m[i] = (cella *) malloc(C *sizeof (cella));
        m_s[i] = (cella *) malloc(C *sizeof (cella));
    }
    *elencoCelle = m;
    *sol = m_s;
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

void disp_semplici(int pos, int *mark, tessera *elencoTessere, cella **elencoCelle, cella **b_sol,int R, int C, int T, int c_max, int *b_max){
    int i, j;

    if(pos >= R*C){
        if((c_max = calcolaPunteggio(elencoTessere, elencoCelle, R, C)) > *b_max){
            for(i=0; i<R;i++){
                for(j=0; j<C;j++){
                    b_sol[i][j] = elencoCelle[i][j];
                }
            }
            *b_max = c_max;
        }
        return;
    }

    i = pos / (R);
    j = pos % (C);


    if(elencoCelle[i][j].tessera!= -1){
        disp_semplici(pos+1, mark, elencoTessere, elencoCelle, b_sol, R, C,T, c_max, b_max);
        return;
    }

    for(int k = 0; k<T; k++){
        if(mark[k]==0) {
            mark[k]=1;
            elencoCelle[i][j].tessera = k;
            elencoCelle[i][j].rotation = 0;

            if (controlla(elencoTessere, elencoCelle, R, C, pos)) {
                disp_semplici(pos + 1, mark, elencoTessere, elencoCelle,b_sol, R, C, T, c_max, b_max);
            }

            elencoCelle[i][j].rotation = 1;
            if(controlla(elencoTessere, elencoCelle,R,C,pos))
                disp_semplici(pos, mark, elencoTessere, elencoCelle,b_sol, R, C,T, c_max, b_max);

            elencoCelle[i][j].tessera = -1;
            elencoCelle[i][j].rotation = -1;
            mark[k] = 0;
        }
    }
}

int controlla(tessera *elencoTessere, cella **elencoCelle, int R, int C, int pos){
    int i, j, okCol = 1;
    char cT1, cT2, cT1_c, cT2_c;

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
        if(c!= j && elencoCelle[i][c].tessera!=-1) {
            if (elencoCelle[i][c].rotation == 1) {
                cT1_c = elencoTessere[elencoCelle[i][c].tessera].cT2;
            }
            if(elencoCelle[i][c].rotation ==0) {
                cT1_c = elencoTessere[elencoCelle[i][c].tessera].cT1;
            }
            if (cT1 != cT1_c)
                okCol = 0;
        }
    }

    if(!okCol) {
        for(int r = 0; r<R; r++){
            if(r!=i  && elencoCelle[r][j].tessera!=-1) {
                if (elencoCelle[r][j].rotation == 1) {
                    cT2_c = elencoTessere[elencoCelle[r][j].tessera].cT1;
                }
                if(elencoCelle[r][j].rotation == 0) {
                    cT2_c = elencoTessere[elencoCelle[r][j].tessera].cT2;
                }

                if (cT2 != cT2_c)
                    return 0;
            }
        }
    }
    return 1;
}

int calcolaPunteggio(tessera *elencoTessere, cella **elencoCelle, int R, int C){
    int punteggioRighe=0, punteggioRiga=0, punteggioColonne=0,punteggioColonna=0, i,j, okRiga=1,okColonna=1, vT1, vT2;
    char cT2_p,cT1_p, cT2_c, cT1_c;

    for(i =0; i<R; i++){
        punteggioRiga = 0;
        for(j=0; j<C;j++){
            if (elencoCelle[i][j].rotation == 1) {
                cT1_c = elencoTessere[elencoCelle[i][j].tessera].cT2;
                vT1 = elencoTessere[elencoCelle[i][j].tessera].vT2;
            }
            if(elencoCelle[i][j].rotation == 0) {
                cT1_c = elencoTessere[elencoCelle[i][j].tessera].cT1;
                vT1 = elencoTessere[elencoCelle[i][j].tessera].vT1;
            }

            punteggioRiga+= vT1;

            if (j!= 0 && cT1_c != cT1_p)
                okRiga=0;

            cT1_p = cT1_c;
        }
        if(okRiga)
            punteggioRighe+=punteggioRiga;
        }

    for(j=0;j<C;j++){
        punteggioColonna=0;
        for(i =0; i<R; i++){
            if (elencoCelle[i][j].rotation == 1) {
                cT2_c = elencoTessere[elencoCelle[i][j].tessera].cT1;
                vT2 = elencoTessere[elencoCelle[i][j].tessera].vT1;
            }
            if(elencoCelle[i][j].rotation == 0) {
                cT2_c = elencoTessere[elencoCelle[i][j].tessera].cT2;
                vT2 = elencoTessere[elencoCelle[i][j].tessera].vT2;
            }

            punteggioColonna+= vT2;

            if (i!= 0 && cT2_c != cT2_p)
                okColonna=0;

            cT2_p = cT2_c;
        }
        if(okColonna)
            punteggioColonne+=punteggioColonna;
    }
    return  punteggioRighe+punteggioColonne;
}
