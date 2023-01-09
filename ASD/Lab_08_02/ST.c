#include "ST.h"
#include "stdlib.h"
#include "string.h"

#define MAXCHAR 30

struct st{char **elencoVertici, **elencoSottoreti; int N,M; };

void MergeSortR ( char **A, char **B , int l , int r );
void Merge ( char **A, char **B , int l , int q , int r );

ST STinit(int maxN){
    ST tab = malloc(sizeof (*tab));
    tab->elencoVertici  = (char **) malloc(maxN*sizeof (char* ));
    tab->elencoSottoreti= (char **) malloc(maxN*sizeof (char* ));

    for(int i=0; i<maxN; i++){
        tab->elencoVertici[i] = (char*) malloc(MAXCHAR*sizeof (char));
        tab->elencoSottoreti[i] = (char*) malloc(MAXCHAR*sizeof (char));
    }

    tab->N = 0;
    tab->M = maxN;

    return tab;
}

void STfree(ST symboltable){
    int i;

    for(i=0; i<symboltable->N; i++){
        free(symboltable->elencoVertici[i]);
    }

    free(symboltable);
}

void STinsert(ST tab, char *vertice, char *sottoRete){
    if(STsearch(tab,vertice)==-1) {
        strcpy(tab->elencoVertici[tab->N],vertice);
        strcpy(tab->elencoSottoreti[tab->N],sottoRete);
        tab->N++;
    }
}

int STsearch(ST tab, char *label){
    for(int i=0; i<tab->N;i++){
        if(strcmp(label, tab->elencoVertici[i]) ==0) {
            return i;
        }
    }
    return -1;
}

char* STgetNameByIndex(ST tab, int index){
    return tab->elencoVertici[index];
}
char* STgetNetByIndex(ST tab, int index){
    return tab->elencoSottoreti[index];
}

int STgetIndexByName(ST tab, char *label){
    for(int i=0; i<tab->N; i++){
        if(strcmp(tab->elencoVertici[i],label)==0)
            return i;
    }
    return -1;
}


void STprint(ST tab){
    for(int i=0; i<tab->N; i++){
        printf("%s ",tab->elencoVertici[i]);
    }
}

ST STsort(ST tab){
    char **elencoVertici = (char**) malloc(tab->M*sizeof (char *));
    MergeSortR(tab->elencoVertici, elencoVertici,0,tab->N-1);
    return tab;
}

void MergeSortR ( char **A , char **B  , int l , int r ) {
    int q;
    if (r <= l)
        return;
    q = (l + r) / 2;
    MergeSortR(A, B, l, q);
    MergeSortR(A, B, q + 1, r);
    Merge(A, B, l, q, r);
}

void Merge ( char **A , char **B , int l , int q , int r ) {
    int i, j, k;
    i = l;
    j = q + 1;
    for (k = l; k <= r; k++)
        if (i > q)
            B[k]=A[j++];
        else if (j > r)
           B[k]=A[i++];
        else if (strcmp(A[i], A[j])<0 || strcmp(A[i], A[j])==0)
            B[k]=A[i++];
        else
            B[k]=A[j++];
    for (k = l; k <= r; k++)
        A[k] = B[k];
    return;
}

int STgetNumberOfVertex(ST tab){
    return tab->N;
};

void STsetNumberOfVertex(ST tab, int N){
    tab->N = N;
};

ST creaCopia(ST sortedTab, ST tab){
    sortedTab->N = tab->N;
    sortedTab->M = tab->M;

    for(int i=0; i<sortedTab->N;i++){
        sortedTab->elencoVertici[i] = tab->elencoVertici[i];
    }
    return sortedTab;

}