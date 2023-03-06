#include "CalcoloCombinatorio.h"
#include <time.h>
#include <stdlib.h>
#include "stdio.h"

int powerset_comb_sempR(int pos, int j, int start, int *val, int *sol, int n);

int princ_molt(int pos, Livello *val, int *sol, int n, int cnt){

    if(pos>=n){
        for(int i=0; i<n;i++){
            printf("%d ",sol[i]);
        }
        printf("\n");
        return cnt+1;
    }

    for(int i=0; i<val[pos].nScelte;i++){
        sol[pos] = val[pos].val[i];
        cnt = princ_molt(pos+1, val, sol, n,cnt);
    }
    return cnt;
}


int disp_semplici(int pos, int *val, int *sol, int *mark, int n, int k, int cnt){
    int i;

    if(pos>=k){
        stampaVettore(sol, k);
        return cnt+1;
    }

    for(i =0; i<n; i++){
        if(mark[i]==0){
            sol[pos] = val[i];
            mark[i]=1;
            cnt = disp_semplici(pos+1, val, sol, mark ,n, k ,cnt);
            mark[i]=0;

        }
    }
    return cnt;
}


int disp_ripetute(int pos, int *val, int *sol, int n, int k, int cnt){
    int i;

    if(pos>=k){
        stampaVettore(sol, k);
        return cnt+1;
    }

    for(i=0; i<n; i++){
        sol[pos] = val[i];
        cnt = disp_ripetute(pos+1,val, sol, n, k, cnt);
    }
    return cnt;
}
int perm_semplici(int pos, int *val, int *sol, int *mark, int n, int cnt){
    int i;

    if(pos>=n){
        stampaVettore(sol, n);
        return cnt +1;
    }

    for(i=0; i<n; i++){
        if(mark[i] == 0){
            sol[pos] = val[i];
            mark[i] = 1;
            cnt = perm_semplici(pos+1, val, sol, mark, n, cnt);
            mark[i] = 0;
        }
    }
    return cnt;
}

int perm_ripetute(int pos, int *val, int *sol, int *mark, int n, int cnt){
    int i;

    if(pos>=n){
        stampaVettore(val, n);
        return cnt+1;
    }

    for(i=0; i<n; i++){
        if(mark[i]>0){
            sol[pos] = val[i];
            mark[i]--;
            cnt = perm_ripetute(pos+1, val, sol, mark, n, cnt);
            mark[i]++;
        }
    }
    return cnt;
}

int comb_semplici(int pos, int start, int *val, int *sol, int n, int k, int cnt){
    int i;

    if(pos>=k){
        stampaVettore(sol, k);
        return cnt+1;
    }

    for(i=start; i<n;i++){
        sol[pos] = val[i];
        cnt = comb_semplici(pos+1, i+1,val, sol,n,k,cnt);
    }
    return cnt;
}

int comb_ripetute(int pos, int start, int *val, int *sol, int n, int k, int cnt){
    int i;

    if(pos>=k){
        stampaVettore(sol, k);
        return cnt+1;
    }

    for(i = start; i<n; i++){
        sol[pos] = val[i];
        cnt = comb_ripetute(pos+1, start, val, sol, n, k ,cnt );
        start++;
    }
    return cnt;
}

int powerset_divide_et_impera(int pos, int start, int *val, int *sol, int n, int cnt){
    int i;

    if(start>=n){ // Terminazione: non ci sono più elementi
        stampaVettore(sol, pos);
        return cnt+1;
    }

    for(i=start; i<n; i++){ // Indice start serve per escludere soluzioni simmetriche, prendo tutti gli elementi da start in avanti
        sol[pos] = val[i];
        cnt = powerset_divide_et_impera(pos+1,i+1, val, sol, n, cnt); // Ricorro aggiungendo l'elemento
    }
    cnt = powerset_divide_et_impera(pos, n, val, sol, n, cnt); // ricorro senza aggiungere l'elemento
    return cnt;
}

int powerset_disp_rip(int pos, int *val, int *sol, int n, int cnt){
    int i;

    if(pos>=n){
        printf("[ ");
        for(i=0; i<n;i++){
            if(sol[i]==1)
                printf("%d ",val[i]);
        }
        printf("]\n");
        return cnt+1;
    }

    sol[pos] = 0; // Non prendo l'elemento pos
    cnt  = powerset_disp_rip(pos+1, val, sol, n,cnt); // Ricorro con la scelta di non prendere l'elemento
    sol[pos] = 1;   // Backtrack: prendo l'elemento pos
    cnt = powerset_disp_rip(pos+1, val, sol, n, cnt); // Ricorro con la scelta di prendere l'elemento pos

    return cnt;
}

int powerset_comb_semp(int *val, int *sol, int n){
    int cnt =0, j;

    printf("[]\n"); //stampo l'insieme vuoto
    cnt++;

    for(j=1; j<=n;j++){ //faccio tutte le combinazioni semplici con j elementi
        cnt += powerset_comb_sempR(0,j,0,val, sol, n);
    }
    return cnt;
}

int powerset_comb_sempR(int pos, int j, int start, int *val, int *sol, int n){
    int i, cnt =0;

    if(pos>=j){
        stampaVettore(sol, j);
        return 1;
    }

    for(i=start; i<n; i++){
        sol[pos] = val[i];
        cnt += powerset_comb_sempR(pos+1, j,i+1, val, sol, n);
    }
    return cnt;
}

void partition_disp_rip(int pos, int *val, int *sol, int n, int k){
    int i, j,*occ,ok=1;

    if (pos >= n) {
        occ = calloc(k, sizeof(int));
        for (j=0; j<n; j++)
            occ[sol[j]]++;
        i=0;
        while ((i < k) && ok) { //calcolo occorrenze per ogni blocco
            if (occ[i]==0)
                ok = 0;
            i++;
        }
        if (ok == 0)
            return;
        else {
            printf("partizione: ");
            for (i=0; i<k; i++) {
                printf("{ ");
                for (j=0; j<n; j++) {
                    if (sol[j]==i)
                        printf("%d ", val[j]);
                }
                printf("}  ");
            }
            printf("\n");
            return;
        }
        free(occ);
    }
    for (i = 0; i < k; i++) {
        sol[pos] = i; // sol[pos] contiene l'indice del blocco a cui appartiene l'oggetto di indice pos
        partition_disp_rip(pos+1, val, sol, n, k);
    }
}

void algoritmo_ER(int pos, int k, int *val, int *sol, int n, int m){

    int i, j;

    if(pos>=n){
//        if(m==k) { // Filtro nel caso in cui si vogliano vedere esattamente le partizioni di k blocchi. Se vogliamo vedere tutte le partizioni di tutti i k blocchi possibili k non serve a nulla (la si può togliere dai parametri). Con k ci si riconduce alla funzione sopra con la differenza che qui non serve il calcolo delle occorrenze.
        printf("Partizione in %d blocchi: ",m);
            for (i = 0; i < m; i++) {
                printf("{ ");
                for (j = 0; j < n; j++) {
                    if (sol[j] == i)
                        printf("%d ", val[j]);
                }
                printf("}");
            }
            printf("\n");
//        }
        return;
    }

    for(i=0;i<m;i++){ // m è come k per la funzione della partition, ossia il numero di blocchi possibili. Unica differenza è che qui m cambia.
        sol[pos] = i;
        algoritmo_ER(pos+1, k,val, sol, n, m); // si attribuisce l’oggetto corrente a uno dei blocchi utilizzabili nel passo corrente (indice i tra 0 e m-1) e si ricorre sul prossimo oggetto (pos+1)
    }
    sol[pos] = m; // se non lo faccio ho l'ultimo blocco vuoto
    algoritmo_ER(pos+1,k,val, sol,n,m+1); // si attribuisce l’oggetto corrente al blocco m e si ricorre sul prossimo oggetto (pos+1) e su un numero di blocchi utilizzabili incrementato di 1 (m+1).
}

void generaVettoreLivelli(Livello* livelli, int length){
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        livelli[i].nScelte = 1+ rand()%4;
        livelli[i].val = malloc(livelli[i].nScelte*sizeof (int));
        generaVettore(livelli[i].val, livelli[i].nScelte);
    }
}

void generaVettore(int *val, int lenght){
    srand(time(NULL));
    for(int i=0; i<lenght;i++) {
        val[i] = rand() % 10;
    }
}

void stampaVettore(int *val, int n){

    printf("[ ");
    for(int i=0; i<n; i++){
        printf("%d ",val[i]);
    }
    printf("]\n");

}