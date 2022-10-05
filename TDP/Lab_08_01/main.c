#include <stdio.h>

#define  MAX_R 50
#define MAX_C 50

typedef struct  {
    int x,y,base, altezza, area;
}area_s;

void leggiMatrice(int mat[MAX_R][MAX_C], int maxR, int *nrp, int *ncp);
void stampaMappa(int mappa[MAX_R][MAX_C],int nr,int nc);
void trovaAree(int mappa[MAX_R][MAX_C],int nr, int nc,area_s elencoAree[MAX_R*MAX_C]);
void stampaAreeMax(area_s altezzaMax, area_s baseMax, area_s areaMax);
void trovaMax(area_s elencoAree[MAX_R*MAX_C], int countAree);
int riconosciRegione(int mappa[MAX_R][MAX_C],int nr, int nc,int,int c, int *b,int *h);

int main() {

    int mappa[MAX_R][MAX_C],nr,nc;
    area_s elencoAree[MAX_R*MAX_C];

    leggiMatrice(mappa,MAX_R,&nr,&nc);
    stampaMappa(mappa,nr,nc);
    trovaAree(mappa,nr,nc,elencoAree);
}

void leggiMatrice(int mat[MAX_R][MAX_C], int maxR, int *nrp, int *ncp){
    FILE *fin;
    if((fin = fopen("../mappa.txt","r"))==NULL){
        printf("Error opening file...");
    }
    else {
        fscanf(fin, "%d %d", nrp, ncp);
        for (int i = 0; i < *nrp; ++i) {
            for (int j = 0; j < *ncp; ++j) {
                fscanf(fin, "%d", &mat[i][j]);
            }
        }
        fclose(fin);
    }
}


void trovaAree(int mappa[MAX_R][MAX_C],int nr, int nc, area_s elencoAree[MAX_R*MAX_C]){
    int countAree=0,b=0,h=0;

    for (int i=0; i<nr; i++) {
        for (int j=0; j<nc; j++) {
            if(riconosciRegione(mappa,nr,nc,i,j,&b,&h)){
                printf("Riconosciuta regione con estremo in (%d %d), avente base %d e altezza %d\n ",i,j,b,h);
                elencoAree[countAree].x=i;
                elencoAree[countAree].y=j;
                elencoAree[countAree].base = b;
                elencoAree[countAree].altezza = h;
                elencoAree[countAree].area = b*h;
                countAree++;
                b=0;h=0;
            }
        }
    }
    trovaMax(elencoAree, countAree);
}
void stampaMappa(int mappa[MAX_R][MAX_C],int nr,int nc){
    for(int i=0; i<nr; i++){
        for(int j=0; j < nc; j++){
            printf("%d ",mappa[i][j]);
        }
        printf("\n");
    }
}
int riconosciRegione(int mappa[MAX_R][MAX_C],int nr, int nc,int r,int c, int *b,int *h){
        int x,y,m,termina=0;
        if (mappa[r][c]==1) {
            for (y=r; y<nr && !termina; y++) {
                m=c;
                for (x=c; x<nc; x++) {
                    if ((mappa[y][x]==0 && mappa[y+1][m]==0 )|| (y== nr-1 && x == nc-1)) {
                        termina=1;
                        mappa[y][x]=0;
                        break;
                    }
                    if (mappa[y][x]==1) {
                        if (y==r) {
                            ++*b;
                        }
                        mappa[y][x]=0;
                    }
                }
                ++*h;
            }
            return 1;
        }
        else
            return 0;

}
void trovaMax(area_s elencoAree[MAX_C*MAX_R],int countAree){
    int iMaxBase, iMaxAlt, iMaxArea,h=0,b=0,a=0;

    for(int i=0; i< countAree; i++){
        if(elencoAree[i].altezza>h){
            h=elencoAree[i].altezza;
            iMaxAlt = i;
        }
        if(elencoAree[i].base > b){
            b = elencoAree[i].base;
            iMaxBase =i;
        }
        if(elencoAree[i].area > a){
            a = elencoAree[i].area;
            iMaxArea =i;
        }
    }
    stampaAreeMax(elencoAree[iMaxAlt], elencoAree[iMaxBase],elencoAree[iMaxArea]);
}
void stampaAreeMax(area_s altezzaMax, area_s baseMax, area_s areaMax){
    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n",baseMax.x,baseMax.y,baseMax.base,baseMax.altezza,baseMax.area);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n",areaMax.x,areaMax.y,areaMax.base, areaMax.altezza,areaMax.area);
    printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d",altezzaMax.x,altezzaMax.y,altezzaMax.base, altezzaMax.altezza,altezzaMax.area);

}

