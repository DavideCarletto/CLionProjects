#include <stdio.h>

#define  MAX_R 50
#define MAX_C 50

typedef struct  {
    int x,y,base, altezza, area;
}area_s;

void leggiFile(FILE *fin, int mappa[MAX_R][MAX_C],int nr,int nc);
void stampaMappa(int mappa[MAX_R][MAX_C],int nr,int nc);
void trovaAree(int mappa[MAX_R][MAX_C],int nr, int nc,area_s elencoAree[MAX_R*MAX_C]);
void stampaAreeMax(area_s altezzaMax, area_s baseMax, area_s areaMax);
void trovaMax(area_s elencoAree[MAX_R*MAX_C], int countAree);

int main() {
    FILE *fin;
    int mappa[MAX_R][MAX_C],nr,nc;
    area_s elencoAree[MAX_R*MAX_C];

    if((fin = fopen("../mappa.txt","r"))==NULL){
        printf("Error opening file...");
        return 1;
    }

    fscanf(fin,"%d%d",&nr,&nc);

    leggiFile(fin,mappa,nr,nc);
    stampaMappa(mappa,nr,nc);
    trovaAree(mappa,nr,nc,elencoAree);
}

void leggiFile(FILE *fin, int mappa[MAX_R][MAX_C],int nr,int nc){

    for(int i=0; i<nr; i++){
        for(int j=0; j < nc; j++){
            if(!feof(fin))
                fscanf(fin,"%d",&mappa[i][j]);
        }
    }

}

void trovaAree(int mappa[MAX_R][MAX_C],int nr, int nc, area_s elencoAree[MAX_R*MAX_C]){
    int countAree=0,x,y,m,termina;

    for (int i=0; i<nr; i++) {
        for (int j=0; j<nc; j++) {
            if (mappa[i][j]==1) {
                elencoAree[countAree].x=i;
                elencoAree[countAree].y=j;
                for (x=i; x<nr; x++) {
                    m=j;
                    if (termina==1) {
                        elencoAree[countAree].area=(elencoAree[countAree].base)*(elencoAree[countAree].altezza);
                        termina=0;
                        break;
                    }
                    for (y=j; y<nc; y++) {
                        if (mappa[x][y]==0 && x==m) {
                            termina=1;
                            break;
                        }
                        if (mappa[x][y]==0) {
                            break;
                        }
                        if (mappa[x][y]==1) {
                            if (x==i) {
                                elencoAree[countAree].base++;
                            }
                            mappa[x][y]=0;
                        }
                    }
                    elencoAree[countAree].altezza++;
                }
                countAree++;
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

