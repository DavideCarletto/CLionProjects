#include "List.h"

typedef struct node *link;

struct node{
    Item val;
    link next;
};

struct list{
    link head;
    int N;
};

link static NEWNode(Item val, link next);

LIST LISTinit(){
    LIST list  = malloc(sizeof (*list));
    list->N = 0;
    list->head =NULL;

    return list;
}

void LISTprint(FILE *fp, LIST list){
    link h = list->head, x;
    for(x = h; x!=NULL; x = x->next){
        ITEMprint(fp, x->val);
    }
    printf("\n");
}

void LISTload(FILE *fp, LIST list){
    int val;
    Item item;

    while (!feof(fp)){
        fscanf(fp, "%d ", &val);
        item = ITEMsetvoid();
        ITEMset(item , val);
//        LISTinhead(list, item);
//        LISTinttail(list, item);
        LISTinOrder(list, item);
    }
}

link static NEWNode(Item val, link next){
    link x = malloc(sizeof (*x));
    if(x ==NULL)
        return NULL;
    x->val = val;
    x->next = next;

    return x;
}

void LISTinhead(LIST list, Item val){

    list->head = NEWNode(val,list->head);
    list->N++;
}

void LISTinttail(LIST list, Item val){
    link x, p, h = list->head;

    if (h==NULL){
        list->head = NEWNode(val , NULL);
        return;
    }


    for(x = h, p = NULL; x!= NULL; p = x, x = x->next);
    p->next = NEWNode(val, NULL);
}

void LISTinOrder(LIST list, Item val){ //se si vuole l'ordine inverso basta scambiare 0 e 1 in tutti e due gli ITEMgrater
    link x, p, h = list->head;

    if (h==NULL || ITEMgreater(val,h->val)==0){
        list->head = NEWNode(val , list->head);
        return;
    }

    for(x = h->next, p = h; x!= NULL && ITEMgreater(val, x->val)==1; p = x,x = x->next);
    p->next = NEWNode(val, x);
}

Item LISTsearch(LIST list, int val){
    link x;

    for(x = list->head; x!= NULL; x = x->next) if (ITEMgetVal(x->val)==val) return x->val;

    return ITEMsetvoid();
}

void LISTdelHead(LIST list){
    link x = list->head;

    if(x == NULL)
        return;

    list->head = x->next;
    free(x);
}

void LISTdelKey(LIST list, int k){
    link p,x, h = list->head;

    if(x ==NULL)
        return;

    for(x = h->next, p =h; x != NULL; p = x, x = x->next) {
        if (ITEMgetVal(x->val) == k) {
            if (x == h)
                list->head = x->next;
            else
                p->next = x->next;
            free(x);
            break;
        }
    }

}