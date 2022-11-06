#include <stdio.h>
#include <stdlib.h>

<<<<<<< HEAD
typedef struct {
    int num_scelte;
    int *scelte;
}Livello;

int princ_molt(int pos, Livello *val, int *sol, int k, int cnt);


int main() {
    Livello *elencoVal = (Livello *) malloc(10*sizeof (Livello));
    int *sol = (int *) malloc(10*sizeof (int));

    int valore1[5] = {1,2,3,4,5}, valore2[3] = {6,7,8}, cnt=0;
    Livello n1,n2;

    n1.num_scelte = 5;
    n2.num_scelte = 3;

    n1.scelte = valore1;
    n2.scelte = valore2;

    elencoVal[0] = n1;
    elencoVal[1] = n2;

    cnt = princ_molt(0,elencoVal, sol, 2,cnt);

    printf("%d", cnt);
    return 0;
}


int princ_molt(int pos, Livello *val, int *sol, int k, int cnt){
    int i;

    if(pos>=k){
        for( i=0; i<k; i++){
            printf("%d ",sol[i]);
        }
        printf("\n");
        return cnt+1;
    }

    for(i=0; i < val[pos].num_scelte;i++){
        sol[pos] = val[pos].scelte[i];
        cnt = princ_molt(pos+1, val, sol, k, cnt);
    }

    return cnt;

}
=======
typedef struct{
    int v1,v2;
}arco;

void leggiFile(FILE *fp, int *N, int *E, arco **elencoArchi);
void allocaVertici(arco **elencoArchi, int E);
void stampaArchi(arco *elencoArchi, int E);
int powerset(int pos, int *elencoVertici, arco* elencoArchi, int *sol, int N ,int E, int start, int count);
int check(int *elencoVertici, arco* elencoArchi, int N , int E);

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
>>>>>>> origin
