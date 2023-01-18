#include "ST.h"
#define MAX_C 10

struct symbolTable{
    char **elencoVertici;
    int N,M;
};

ST STInit(int M){
    int i;
    ST tab = malloc(sizeof (*tab));
    char **m = malloc(M*sizeof (char*));

    for(i = 0; i<M; i++){
        m[i] = malloc(MAX_C* sizeof (char ));
    }
    tab->N =0;
    tab->M = M;
    tab->elencoVertici = m;
    return tab;
}
void STInsert(ST tab, char *vertice){
    if(STsearch(tab,vertice)==-1) {
        strcpy(tab->elencoVertici[tab->N],vertice);
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
void STfree(ST st) {
    for(int i=0; i<st->N;i++)
        free(st->elencoVertici[i]);
    free(st->elencoVertici);
    free(st);
}

char *STGetNameByIndex(ST tab, int index){
    return tab->elencoVertici[index];
}
int STgetNumberOfVertex(ST tab){
    return tab->N;
};

int STGetIndexByName(ST tab, char *label) {
    for (int i = 0; i < tab->N; i++) {
        if (strcmp(tab->elencoVertici[i], label) == 0)
            return i;
    }
    return -1;
}

