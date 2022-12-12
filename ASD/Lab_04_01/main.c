#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int v1,v2;
}arco;

void leggiFile(FILE *fp, int *N, int *E, arco **elencoArchi);
void allocaVertici(arco **elencoArchi, int E);
void stampaArchi(arco *elencoArchi, int E);
int powerset(int pos, int *elencoVertici, arco* elencoArchi, int *sol, int N ,int E, int start, int count);
int check(int *elencoVertici, arco* elencoArchi, int N , int E);
void dealloca(arco *elencoArchi, int *sol);

int main() {

    int N,E, count, *sol, *elencoVertici;
    FILE *fp;

    arco *elencoArchi;

    if((fp = fopen("../input files/E1/grafo.txt","r"))==NULL){
        printf("Error opening file...");
        return 1;
    }

    leggiFile(fp, &N, &E, &elencoArchi);
    //stampaArchi(elencoArchi, E);

    sol = (int*) malloc(N*sizeof (int));
    elencoVertici = (int*) malloc(N*sizeof (int));

    for(int i=0; i< N; i++) elencoVertici[i]=i;

    count = powerset(0,elencoVertici,elencoArchi,sol, N,E,0,count);

    dealloca(elencoArchi, sol);
    return 0;
}

void leggiFile(FILE *fp, int *N, int *E, arco **elencoArchi){
    int count =0;

    if(!feof(fp)){
        fscanf(fp, "%d %d",N, E);
    }

    allocaVertici(elencoArchi, *E);

    while(!feof(fp)){
        fscanf(fp, "%d %d", &(*elencoArchi)[count].v1, &(*elencoArchi)[count].v2);
        count++;
    }

}

void allocaVertici(arco **elencoArchi, int E){
    *elencoArchi  = (arco*) malloc(E* sizeof (arco));
}

void stampaArchi(arco *elencoArchi, int E){

    for(int i=0; i<E; i++) {
            printf("%d %d\n", elencoArchi[i].v1, elencoArchi[i].v2);
    }
}


int powerset(int pos, int *elencoVertici, arco* elencoArchi, int *sol, int N, int E, int start, int count){
    int i;
    if(start >= N){
        if(check(sol, elencoArchi, pos, E)) {
            printf("{ ");
            for (i = 0; i < pos; i++) {
                printf("%d ", sol[i]);
            }
            printf("} \n");
        }
        return count+1;
    }

    for (i =start; i < N; i++){
            sol[pos] = elencoVertici[i];
            count = powerset(pos+1, elencoVertici, elencoArchi, sol, N,E, i + 1, count);
    }
    count = powerset(pos, elencoVertici, elencoArchi, sol, N,E, N, count);

    return count;
}

int check(int *elencoVertici, arco* elencoArchi, int N , int E){ //faccio un vettore sol per identificare la copertura o meno degli archi del vertexCover. Ogni cella di sol indica un arco del grafo. Uso 0 o 1
    int *sol = (int*) malloc(E*sizeof (int)),i;

    for(i=0; i<E; i++) sol[i]=0;

    for(i=0;i<N;i++){
        for(int j=0; j<E;j++){
            if(elencoVertici[i]== elencoArchi[j].v1 || elencoVertici[i] == elencoArchi[j].v2){
                sol[j]=1;
            }
        }
    }

    for(i=0; i<E;i++)
        if (sol[i]==0)
            return 0;

    return 1;
}

void dealloca(arco *elencoArchi, int *sol){
    free(elencoArchi);
    free(sol);
}
