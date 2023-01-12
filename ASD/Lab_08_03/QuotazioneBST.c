#include "QuotazioneBST.h"
#include "Quotazione.h"
#include "stdlib.h"
#include "string.h"

typedef struct BSTNode *link;

struct BSTNode{
    quotazione_t quotazione;
    link l,  r;
};

struct BST{
    link root, z;
};

static link BSTNew(quotazione_t quotazione, link l, link r){
    link x = malloc(sizeof (*x));
    x->quotazione = quotazione;
    x->l = l;
    x->r = r;

    return x;
}

static quotazione_t SearchR(link h, char *data, link z){
    int cmp;

    if(h==z)
        return QUOTAZIONESetNull();

    cmp = strcmp(data, DATAToString(h->quotazione.data));

    if(cmp==0)
        return h->quotazione;
    if(cmp <0)
        return SearchR(h->l,data,z);
    return SearchR(h->r,data, z);
}

quotazioneBST BSTInit(){
    quotazioneBST  BST = malloc(sizeof (*BST));

    BST->root = (BST->z = BSTNew(QUOTAZIONEInit(),NULL, NULL));
}

quotazione_t BSTSearch(quotazioneBST bst, char *data){
    return SearchR(bst->root,data, bst->z);
}

void BSTLoad(quotazioneBST bst, LIST list){

}
