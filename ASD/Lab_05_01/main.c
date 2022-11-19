#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int si, fi
}att;

void attSel(int N, att *v);
void powerset (int pos, att *v, int* sol, int n,int c_max, int *b_max, int *b_sol);
void leggiFile(FILE *fp, att **v);
att* allocaV(att* v, int dim);
int intersec(att *v, int *sol, int n);


int main() {
    FILE *fp;
    att *v;
    int dim;

    if((fp = fopen("../E1/att.txt","r")) == NULL){
        printf("Error opening file...");
        return 1;
    }

    if(!feof(fp))
        fscanf(fp, "%d", &dim);

    v = allocaV(v, dim);

    leggiFile(fp, &v);

    attSel(dim, v);

    return 0;
}

att* allocaV(att* v, int dim){
    return (att*) malloc(dim*sizeof(att));
}

void leggiFile(FILE *fp, att **v){
    int i =0;

    while(!feof(fp)){
        fscanf(fp, "%d %d\n", &(*v)[i].si, &(*v)[i].fi);
        i++;
    }
}

void attSel(int N, att *v){
    int *sol, *b_sol, b_max=0;

    sol = (int *) malloc(N*sizeof (int));
    b_sol = (int *) calloc(N, sizeof (int));

    powerset(0, v, sol, N,0,&b_max,b_sol);

    printf("Uno dei sottoinsiemi di S di attivita' compatibili che massimizza la somma delle durate e' {");
    for(int i=0; i<N;i++){
        if(b_sol[i]!=0)
            printf("(%d %d)",v[i].si, v[i].fi);
    }
    printf("}, per una somma delle durate pari a %d.\n", b_max);
}

void powerset (int pos, att *v, int* sol, int n ,int c_max, int *b_max, int *b_sol){
    int i;

    if(pos>=n){
        if(!intersec(v, sol,n) && c_max >*b_max) {
            for( i =0; i<n; i++)
                b_sol[i] = sol[i];
            *b_max = c_max;
        }
        return;
    }
    sol[pos] = 1;
    c_max += (v[pos].fi-v[pos].si);
    powerset(pos+1, v, sol, n,c_max, b_max, b_sol);
    sol[pos] = 0;
    c_max -= (v[pos].fi-v[pos].si);
    powerset(pos+1, v, sol, n, c_max, b_max,b_sol);
}

int intersec(att *v, int *sol, int n){

    for(int i=0; i<n; i++){
        if(sol[i]) {
            for (int j = i + 1; j < n; j++) {
                if (sol[j] && ((v[i].si < v[j].fi) && (v[j].si < v[i].fi)))
                    return 1;
            }
        }
    }
    return 0;
}