#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_C 100
#define MAX 10
typedef struct {
    char canzoni[MAX][MAX_C];
    int numCanzoni;
}persona;

int leggiFile(FILE *fin, persona **elencoAmici);
int principioMoltiplicazione(int pos,persona *val,char **sol,int n,int cnt);
void malloc2d(persona **elencoAmici, int dim);
void stampaAmici(persona *elencoAmici, int dim);

int main() {
    int dim,cnt =0, pos =0;
    FILE *fin;
    persona *elencoAmici= NULL;
    char **sol=NULL;

    if((fin = fopen("../brani.txt","r"))==NULL){
        printf("Error opening file...");
        return -1;
    }

    dim = leggiFile(fin, &elencoAmici);
//    stampaAmici(elencoAmici, dim);

    sol=(char **) malloc(dim* sizeof(char *));
    for(int i=0;i<dim;i++) sol[i]=(char *) malloc(MAX_C*sizeof (char));

    cnt = principioMoltiplicazione(pos,elencoAmici,sol, dim, cnt);
    printf("Ci sono %d possibili soluzioni.",cnt);

    free(elencoAmici);

    for(int i=0; i<dim;i++)
        free(sol[i]);
    free(sol);

    return 0;
}

int leggiFile(FILE *fin, persona **elencoAmici){
    int dim, pCorr=0,countCanzoni;

    if(!feof(fin)){
        fscanf(fin, "%d", &dim);
    }

    malloc2d(elencoAmici, dim);

    while(!feof(fin)) {
        if(!feof(fin))
        fscanf(fin, "%d", &(*elencoAmici)[pCorr].numCanzoni);
        countCanzoni=0;

        for(int i=0; i<(*elencoAmici)[pCorr].numCanzoni;i++){
            fscanf(fin, "%s", (*elencoAmici)[pCorr].canzoni[countCanzoni++]);
        }
        pCorr++;
    }
    return pCorr;
}

void malloc2d(persona **elencoAmici, int dim){
    *elencoAmici = (persona*) malloc(dim* sizeof (persona));
}

int principioMoltiplicazione(int pos,persona *val,char **sol,int n,int cnt){
    int i,j;
    if(pos>=n){
        for(j=0;j<n;j++) printf("%s ",sol[j]);
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<val[pos].numCanzoni;i++){
        strcpy(sol[pos],val[pos].canzoni[i]);
        cnt=principioMoltiplicazione(pos+1,val,sol,n,cnt);
    }
    return cnt;
}

void stampaAmici(persona *elencoAmici, int dim){

    for(int i=0; i<dim; i++){
        printf("%d\n", elencoAmici[i].numCanzoni);
        for(int j=0; j<elencoAmici[i].numCanzoni; j++){
            printf("\t%s\n", elencoAmici[i].canzoni[j]);
        }
        printf("\n");
    }
}