#include "TitoliList.h"
#include "stdlib.h"
#include "string.h"

#define MAX_C 30

typedef struct node *link;

struct node{
    link next;
    titolo_t titolo;
};

struct list{
    link head;
    int N;
};

static link NEWNode(titolo_t  titolo, link next);
//static link SortInList(link h, titolo_t titolo);


LIST LISTInit(){
    LIST list = malloc(sizeof (LIST));
    list->head = NULL;
    list->N =0;

    return list;
}

static link NEWNode(titolo_t  titolo, link next){
    link x = malloc(sizeof (*x));

    if(x ==NULL)
        return NULL;

    x->titolo = titolo;
    x->next = next;

    return x;
}

static link SortInList(link h, titolo_t titolo){
    link x,p;

    if(h==NULL || strcmp(GETCodiceTitolo(h->titolo), GETCodiceTitolo(titolo))>0){
        h= NEWNode(titolo,h);
        return h;
    }

    for(x = h->next, p=h; x!= NULL && strcmp(GETCodiceTitolo(titolo),GETCodiceTitolo(x->titolo))>0; p = x, x = x->next);
    p->next = NEWNode(titolo, x);

    return h;
}

static void CreaTitoliBST(link h){
    link x;

    for(x = h; x!= NULL; x=x->next){
        quotazioneBST bst = TITOLOGetBST(x->titolo);
        TITOLOBSTLoad(bst, x->titolo);
    }
}

int TitoloInList(LIST list, char *codice){
    link x, h  = list->head;

    for(x = h; x!= NULL; x = x->next)
        if(strcmp(GETCodiceTitolo(x->titolo), codice)==0)
            return 1;

    return 0;
}

void LISTInsert(LIST list, titolo_t titolo){
    list->head = SortInList(list->head, titolo);
}

void LISTLeggiTitoli(LIST list, FILE *fp){
    int dim_titoli, dim_transiz;
    char codice[MAX_C];
    titolo_t titolo;

    fscanf(fp,"%d\n", &dim_titoli);

    for(int i=0; i< dim_titoli; i++) {
        fscanf(fp, "%s %d\n", codice, &dim_transiz);

        if(!TitoloInList(list, codice)) {
            titolo = TITOLOInit(codice);
            LISTInsert(list, titolo);
        } else
            titolo = LISTGetTitoloByCodice(list, codice);

        TITOLOload(fp, titolo, dim_transiz);

    }
}

titolo_t LISTGetTitoloByCodice(LIST list, char *codice){
    link x;

    for(x = list->head; x!= NULL; x=x->next){
        if(strcmp(GETCodiceTitolo(x->titolo), codice)==0)
            return x->titolo;
    }
    return NULL;
}

void LISTPrint(LIST list){
    link x;
    for(x = list->head; x!= NULL; x = x->next){
        TITOLOPrint(x->titolo);
    }
}

void LISTCreaTitoliBST(LIST list){
    CreaTitoliBST(list->head);
}
