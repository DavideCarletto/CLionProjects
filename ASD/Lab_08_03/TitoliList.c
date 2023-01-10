#include "TitoliList.h"
#include "stdlib.h"
#include "string.h"

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
static link SortInList(link h, titolo_t titolo);

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
        return NEWNode(titolo,h);
    }

    for(x = h->next, p=h; x!= NULL && strcmp(GETCodiceTitolo(h->titolo), GETCodiceTitolo(titolo))>0; p = x, x = x->next);
    p->next = NEWNode(titolo, x);

    return h;
}
