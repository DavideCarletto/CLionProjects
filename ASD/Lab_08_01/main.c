#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#define MAXDIAG 3
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
    int DP;
    float tot;
}programma;

void *leggiFile(FILE *fp, elemento* elementi);
elemento *allocaElementi(int dim);
void stampaElementi(elemento *elementi, int dim);
void MergeSortR ( elemento A[] , elemento B [] , int l , int r );
void Merge ( elemento A [] , elemento B [] , int l , int q , int r );
diagonale *allocaMatDiagonali(int dim, int dimElementi);
programma trovaSol(elemento* elencoElementi, int nElementi, diagonale *elencoDiagoali, int DD, int DP);
int checkDiag(elemento e, diagonale *diag, int DD,int indexElement, int indexDiag, int DP, int curDP);
programma creaProgramma(diagonale *elencoDiagonali, int DP);
void stampaDiagonale(diagonale diag);
elemento copiaElemento(elemento elem);
int checkAcrobaticoSequenza(diagonale *elencoDiag, int startIndexDiag, int nElementi);
int checkAcrobaticoIn(diagonale *elencoDiag, int dim, int nElementi);
int getMinAcrobatics(diagonale *elencoDiag, int startIndexDiag, int nElementi);

int main() {
    int dim =0, count =0,i, DD, DP, maxDiag = MAXDIAG;
    FILE *fp, *fp2;
    elemento *elementi, *B;
    diagonale *elencoDiagonali;
    programma b_sol;

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
    B = allocaElementi(dim);
    leggiFile(fp, elementi);
    MergeSortR(elementi, B,0,dim-1);
//    stampaElementi(elementi, dim);

    while (!feof(fp2)) {
        elencoDiagonali = allocaMatDiagonali(maxDiag, dim);
        fscanf(fp2, "%d %d", &DD, &DP);

        printf("--- Test Case DD = %d DP= %d---\n", DD, DP);
        b_sol = trovaSol(elementi, dim,elencoDiagonali,DD,DP);
        printf("TOT = %f\n",b_sol.tot);
        for(i=0; i<3;i++){
            printf("DIAG #%d > %f ",(i+1), b_sol.diagonali[i].valTot);
            if(b_sol.diagonali[i].bonus==1.5f){
                printf("* 1.5 (BONUS)");
            }
            printf("\n");
            stampaDiagonale(b_sol.diagonali[i]);
        }
        printf("\n");
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
        printf("%s %d %d %d %d %d %.2f %d\n",elementi[i].nome, elementi[i].tipologia, elementi[i].dir_ingresso, elementi[i].dir_uscita,
               elementi[i].req_prec, elementi[i].finale, elementi[i].val, elementi[i].difficolta);
    }
}

void stampaDiagonale(diagonale diag){
    float valTot = 0;
    for(int i=0; i<diag.nElementi; i++){
        printf("%s ",diag.elementi[i].nome);
    }
    printf("\n");
}

void MergeSortR ( elemento A[] , elemento B [] , int l , int r ) {
    int q;
    if (r <= l)
        return;
    q = (l + r) / 2;
    MergeSortR(A, B, l, q);
    MergeSortR(A, B, q + 1, r);
    Merge(A, B, l, q, r);
}

void Merge ( elemento A [] , elemento B [] , int l , int q , int r ) {
    int i, j, k;
    i = l;
    j = q + 1;
    for (k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++];
        else if (j > r)
            B[k] = A[i++];
        else if (((float)A[i].difficolta/A[i].val)<=((float)A[j].difficolta/A[j].val))
            B[k] = A[i++];
        else
            B[k] = A[j++];
    for (k = l; k <= r; k++)
        A[k] = B[k];
    return;
}

diagonale *allocaMatDiagonali(int dim, int dimElementi){
    diagonale *diag = (diagonale*) malloc(dim*sizeof (diagonale));
    for(int i=0; i<dim; i++) {
        diag[i].elementi = allocaElementi(dimElementi);
        diag[i].nElementi =0;
        diag[i].difTot=0;
        diag[i].valTot = 0;
        diag[i].bonus=1;
    }
    return diag;
}

programma trovaSol(elemento* elencoElementi, int nElementi, diagonale *elencoDiagonali, int DD, int DP){
    int res, termina =0, trovato =0, curDP=0;

    for(int i=2; i>=0;i--) {
        termina=0;
        while (!termina) {
            trovato=0;
            for (int j = 0; j < nElementi && !trovato; j++) {
                res = checkDiag(elencoElementi[j], elencoDiagonali, DD, elencoDiagonali[i].nElementi, i,DP,curDP);
                if (res == 1) {
                    elencoDiagonali[i].elementi[elencoDiagonali[i].nElementi++] = copiaElemento(elencoElementi[j]);
                    elencoDiagonali[i].difTot+=elencoElementi[j].difficolta;
                    elencoDiagonali[i].valTot+= elencoElementi[j].val;
                    curDP+=elencoElementi[j].difficolta;
                    trovato=1;
//                    stampaDiagonale(elencoDiagonali[i]);
                } else if (res == -1)
                    termina = 1;
            }
            if(trovato==0)
                termina=1;
        }
        if(i==2 && elencoDiagonali[i].elementi[elencoDiagonali[i].nElementi-1].difficolta>=8)
            elencoDiagonali[i].bonus = 1.5f;
    }
    return creaProgramma(elencoDiagonali,DP);
}
elemento copiaElemento(elemento elem) {
    elemento elementoDiag;

    strcpy(elementoDiag.nome, elem.nome);
    elementoDiag.tipologia = elem.tipologia;
    elementoDiag.dir_ingresso = elem.dir_ingresso;
    elementoDiag.dir_uscita =elem.dir_uscita;
    elementoDiag.difficolta = elem.difficolta;
    elementoDiag.val = elem.val;

    return elementoDiag;
}
int checkDiag(elemento e, diagonale *diag, int DD,int indexElement, int indexDiag, int DP, int curDP){
    if(curDP+e.difficolta+(getMinAcrobatics(diag,indexDiag,diag[indexDiag].nElementi)*indexDiag)>DP)
        return 0;

    if(diag[indexDiag].difTot+e.difficolta>DD)
        return 0;

    if(diag[indexDiag].difTot+e.difficolta<=DD) {
        if (indexElement == 0) {
            if(indexDiag==2 ) {
                if( e.dir_ingresso==1 && e.dir_uscita==0 && e.finale==0)
                    return 1;
            } else {
                if (indexDiag == 0 && !checkAcrobaticoIn(diag, indexDiag, diag[indexElement].nElementi)) {
                    if (e.tipologia == 1)
                        if (e.req_prec == 0) {
                            return 1;
                        }
                }
                if (e.tipologia == 2) {
                    if (e.req_prec == 0) {
                        return 1;
                    }
                }
            }
        } else {
            if (diag[indexDiag].elementi[indexElement - 1].finale == 1 || indexDiag >= 4)
                return -1;

            if (indexDiag == 2 && indexElement == 1) {
                if (e.dir_ingresso == diag[indexDiag].elementi[indexElement - 1].dir_uscita && e.tipologia == 1)
                    return 1;

            } else {
                if (indexDiag == 1 && indexElement == 1) {
                    if (!checkAcrobaticoSequenza(diag, indexDiag, diag[indexElement].nElementi)) {
                        if ((e.dir_ingresso == diag[indexDiag].elementi[indexElement - 1].dir_uscita) &&
                            (e.tipologia == 1 || e.tipologia == 2)) {
                            return 1;
                        }
                    } else {
                        if (e.dir_ingresso == diag[indexDiag].elementi[indexElement - 1].dir_uscita)
                            return 1;
                    }
                } else {
                    if (e.dir_ingresso == diag[indexDiag].elementi[indexElement - 1].dir_uscita)
                        return 1;
                }

            }
        }
    }

    return 0;
}

programma creaProgramma(diagonale *elencoDiagonali, int DP){

    programma  prog;

    prog.diagonali = (diagonale*) malloc(4* sizeof (diagonale));
    prog.DP = DP;
    prog.tot =0;

    for(int i=0; i<3; i++){
        prog.diagonali[i] = elencoDiagonali[i];
        prog.tot+= elencoDiagonali[i].valTot*elencoDiagonali[i].bonus;
    }
    return prog;
}

int checkAcrobaticoIn(diagonale *elencoDiag, int dim, int nElementi) {
    int checkIn=0;

    for (int i = dim; i >= 0; i--) {
        for (int j = 0; j < nElementi; j++) {
            if (elencoDiag[i].elementi[j].tipologia == 1)
                checkIn=1;
        }
    }
    return checkIn;
}

int checkAcrobaticoSequenza(diagonale *elencoDiag, int startIndexDiag, int nElementi) {
    int check=0;

    for (int i = startIndexDiag; i >= 0; i--) {
        for (int j = 0; j < nElementi-1; j++) {
            if((elencoDiag[i].elementi[j].tipologia==1 ||elencoDiag[i].elementi[j].tipologia==2) && (elencoDiag[i].elementi[j+1].tipologia==1 ||elencoDiag[i].elementi[j+1].tipologia==2))
                return 1;
        }
    }
    return 0;
}

int getMinAcrobatics(diagonale *elencoDiag, int startIndexDiag, int nElementi){
    int min=INT_MAX;

    for (int i = 2; i >= startIndexDiag; i--) {
        for (int j = 0; j < nElementi; j++) {
            if (elencoDiag[i].elementi[j].tipologia == 2 && elencoDiag[i].elementi[j].difficolta<min)
                min = elencoDiag[i].elementi[j].difficolta;
        }
    }
    return min;
}