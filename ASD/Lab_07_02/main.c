#include <stdio.h>
#include "stdlib.h"

#define MAXDIAG 10000
typedef struct {
    char nome[100];
    int tipologia,dir_ingresso, dir_uscita,req_prec,finale, difficolta;
    float val;
}elemento;

typedef struct {
    elemento *elementi;
    float valTot, bonus;
    int nElementi, difTot;
}diagonale;

typedef struct {
    diagonale *diagonali;
    float DP;
}programma;

void *leggiFile(FILE *fp, elemento* elementi);
elemento *allocaElementi(int dim);
void stampaElementi(elemento *elementi, int dim);
int calcola_diagonale(int pos, int k, elemento* elementi, int *sol, diagonale *elenco_diagonali, int n, int curDif, float curVal, int dim_sol, int countDiagonali, int DD, int maxDiag);
int check_insElemento(elemento *elementi, int indexCur, int pos, int dim_sol, int curDif, int DD, int *sol);
int check_acrobatico(diagonale diag);

diagonale *allocaMatDiagonali(int dim);
diagonale creaDiagonale(elemento *elementi, int *sol, int k);
void stampaDiagonale(diagonale diag);
float trovaProgramma(int pos, int k, diagonale *elenco_diagonali, int nDiag, int *sol, programma *b_sol, float progCurVal, int DP, float maxVal,int  progCurDp);
programma creaProgramma(diagonale *elencoDiagonali, float DP, int *sol);
int checkProgramma(programma prog);


int main() {
    int dim =0, *sol, count =0,i, DD, DP, maxDiag = MAXDIAG;
    FILE *fp, *fp2;
    elemento *elementi;
    diagonale *elencoDiagonali;
    programma b_sol;
    float  punteggioMax;

    if((fp = fopen("../elementi.txt","r")) == NULL){
        printf("Error opening file...");
        return 1;
    }
    if((fp2 = fopen("../TestSet.txt","r")) == NULL){
        printf("Error opening file...");
        return 1;
    }

    fscanf(fp, "%d\n", &dim);
    elementi = allocaElementi(dim);
    leggiFile(fp, elementi);
    stampaElementi(elementi, dim);

//    for(int i=0; i<dim; i++) sol[i] = -1;


    while (!feof(fp2)) {
        elencoDiagonali = allocaMatDiagonali(maxDiag);
        fscanf(fp2,"%d %d", &DD, &DP);

        printf("--- Test Case DD = %d DP= %d---", DD, DP);
        for (i = 1; i <= 5; i++) {
            sol = calloc(5, sizeof(int));
            count = calcola_diagonale(0, i, elementi, sol, elencoDiagonali, dim, 0, 0, 0, count, DD,MAXDIAG);
        }
        printf("\n Possibili diagonali (%d): \n", count);

//    for(int j=0; j<count; j++){
//        stampaDiagonale(elencoDiagonali[j]);
//    }

        punteggioMax = trovaProgramma(0, 3, elencoDiagonali, count, sol, &b_sol, 0, DP, 0, 0);
//
        for (i = 0; i < 3; i++) {
            stampaDiagonale(b_sol.diagonali[i]);
        }

        printf("Punteggio massimo: %.3f\n\n", punteggioMax);
        free(elencoDiagonali);
        free(sol);
        count =0;
    }
    return 0;
}


void *leggiFile(FILE *fp, elemento* elementi){
    int count =0;

    while(!feof(fp)){
        fscanf(fp,"%s %d %d %d %d %d %f %d", &elementi[count].nome, &elementi[count].tipologia, &elementi[count].dir_ingresso, &elementi[count].dir_uscita,
               &elementi[count].req_prec, &elementi[count].finale, &elementi[count].val, &elementi[count].difficolta);
        count++;
    }
}

elemento *allocaElementi(int dim){
    elemento *elementi = (elemento*) malloc(dim*sizeof (elemento));

    return elementi;
}

void stampaElementi(elemento *elementi, int dim){
    for(int i=0; i<dim; i++){
        printf("%s %d %d %d %d %d %.1f %d\n",elementi[i].nome, elementi[i].tipologia, elementi[i].dir_ingresso, elementi[i].dir_uscita,
               elementi[i].req_prec, elementi[i].finale, elementi[i].val, elementi[i].difficolta);
    }
}

int calcola_diagonale(int pos, int k, elemento* elementi, int *sol, diagonale *elenco_diagonali, int n, int curDif, float curVal, int dim_sol, int countDiagonli, int DD, int maxDiag){
    int i;

    if(pos >= k){
        diagonale  diagonaleTmp = creaDiagonale(elementi, sol,k);
        diagonaleTmp.nElementi = k;
        diagonaleTmp.valTot = curVal;
        diagonaleTmp.bonus = 1;
        diagonaleTmp.difTot = curDif;

        if(check_acrobatico(diagonaleTmp)) {
            if(countDiagonli>=maxDiag){
                maxDiag*=20;
                realloc(elenco_diagonali,maxDiag);
            }
            elenco_diagonali[countDiagonli++] = diagonaleTmp;
        }
        return countDiagonli;
    }

    for(i=0; i< n; i++) {
        if (check_insElemento(elementi, i, pos, dim_sol, curDif, DD, sol)) {
            sol[pos] = i;

            curDif += elementi[i].difficolta;
            curVal+= elementi[i].val;
            dim_sol++;

            countDiagonli = calcola_diagonale(pos + 1, k, elementi, sol, elenco_diagonali, n, curDif, curVal, dim_sol, countDiagonli, DD,maxDiag);

            curDif-= elementi[i].difficolta;
            curVal-= elementi[i].val;
            dim_sol--;
        }
    }
    return countDiagonli;
}

int check_insElemento(elemento *elementi, int indexCur, int pos, int dim_sol, int curDif, int DD, int *sol){
    if( curDif + elementi[indexCur].difficolta <= DD && dim_sol<5) {
        if (pos == 0) {
            if (elementi[indexCur].req_prec == 0 && elementi[indexCur].dir_ingresso == 1)
                return 1;
            return 0;
        }

        if ((elementi[sol[pos-1]].dir_uscita == elementi[indexCur].dir_ingresso) && (elementi[sol[pos-1]].finale == 0)) {
            return 1;
        }
    }
    return 0;
}

diagonale *allocaMatDiagonali(int dim){
    diagonale *diag = (diagonale*) malloc(dim*sizeof (diagonale));
    return diag;
}

diagonale creaDiagonale(elemento *elementi, int *sol, int k){
    diagonale diagonaleTmp;
    elemento *elementiTmp = malloc(k * sizeof(elemento));

    for(int i=0; i<k; i++){
        elementiTmp[i] = elementi[sol[i]];
    }
    diagonaleTmp.elementi = elementiTmp;
    return diagonaleTmp;
}
int check_acrobatico(diagonale diag){
    for(int i=0; i<diag.nElementi; i++){
        if(diag.elementi[i].tipologia == 2 || diag.elementi[i].tipologia == 1)
            return 1;
    }
    return 0;
}

void stampaDiagonale(diagonale diag){
    float valTot = 0;
    for(int i=0; i<diag.nElementi; i++){
        printf("%s ",diag.elementi[i].nome);
        valTot+= diag.elementi[i].val;
    }
    printf("%f", valTot);
    printf("\n");
}

float trovaProgramma(int pos, int k, diagonale *elenco_diagonali, int nDiag, int *sol, programma *b_sol, float progCurVal, int DP, float maxVal,int  progCurDp){
    int i;
    float  bonus=1;
    if(pos>= k){
        programma  prog = creaProgramma(elenco_diagonali, progCurVal, sol);

        if(checkProgramma(prog)){
            if(progCurVal > maxVal){
                *b_sol = prog;
                maxVal = progCurVal;
            }
        }
        return maxVal;
    }

    for(i =0; i<nDiag; i++){
        if(pos == k-1 && elenco_diagonali[i].elementi[elenco_diagonali[i].nElementi-1].difficolta >=8) {
          bonus = 1.5f;
        }

        if(progCurDp+elenco_diagonali[i].difTot <= DP) {
            sol[pos] = i;
            progCurVal = progCurVal+(elenco_diagonali[i].valTot*bonus);
            progCurDp += elenco_diagonali[i].difTot;

            maxVal = trovaProgramma(pos + 1, k, elenco_diagonali, nDiag, sol, b_sol, progCurVal, DP, maxVal, progCurDp);

            progCurVal = progCurVal-(elenco_diagonali[i].valTot*bonus);
            progCurDp -= elenco_diagonali[i].difTot;

        }
    }
    return maxVal;
}

programma creaProgramma(diagonale *elencoDiagonali, float DP, int *sol){

    programma  prog;

    prog.diagonali = (diagonale*) malloc(3* sizeof (diagonale));
    prog.DP = DP;

    for(int i=0; i<3; i++){
        prog.diagonali[i] = elencoDiagonali[sol[i]];
    }
    return prog;
}

int checkProgramma(programma prog){
    int checkAvanti=0, checkIndietro=0, checkSequenzaAcrobatica=0;
    for(int i=0; i< 3; i++){
        for(int j=0; j<prog.diagonali[i].nElementi; j++){
            if(prog.diagonali[i].elementi[j].tipologia == 2) {
                checkAvanti = 1;
            }
            if(prog.diagonali[i].elementi[j].tipologia == 1){
                checkIndietro=1;
            }

            if(j>0){
                if((prog.diagonali[i].elementi[j-1].tipologia ==1 ||prog.diagonali[i].elementi[j-1].tipologia ==2) && (prog.diagonali[i].elementi[j].tipologia ==1 || prog.diagonali[i].elementi[j].tipologia ==2) ) {
                    checkSequenzaAcrobatica = 1;
                }
            }
        }
    }
    if(checkAvanti ==1 &&  checkSequenzaAcrobatica ==1 &&  checkIndietro == 1){
        return 1;
    }

    return 0;
}


