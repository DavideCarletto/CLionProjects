#include "ST.h"

struct symbolTable{int N; char *elencoVertici; int size;};


ST STinit(int N){
    ST tab = malloc(sizeof (ST*));
    tab->elencoVertici = malloc(N*sizeof (char ));
    for(int i=0; i<N;i++) tab->elencoVertici[i] = '.';
    tab->N = N;
    tab->size =0;

    return tab;
}

void STinsert(ST tab, char V){
    tab->elencoVertici[tab->size++] = V;
}

char STsearch(ST tab, char label){

    for(int i=0; i<tab->size;i++){
        if(tab->elencoVertici[i]==label)
            return i;
    }
    return '.';
}

char STsearchByIndex(ST tab, int id){
    return tab->elencoVertici[id];
}
