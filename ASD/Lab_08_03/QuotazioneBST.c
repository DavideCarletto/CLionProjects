#include "QuotazioneBST.h"
#include "stdlib.h"

typedef struct BSTNode *link;

struct BSTNode{
    quotazione_t quotazione;
    link p,l,  r;
    int N;
};

struct BST{
    link root, z;
};
static link BSTNew(quotazione_t quotazione,link p, link l, link r, int N);
static quotazione_t SearchR(link h, data_t data, link z);
static int AltezzaMaxR(link root);
static int AltezzaMinR(link root);
static  link bilanciaR(link h, link z);
static link partR(link h, int r);
static link rotR(link h);
static link rotL(link h);

static link BSTNew(quotazione_t quotazione, link p,link l, link r, int N){
    link x = malloc(sizeof (*x));
    x->quotazione = quotazione;
    x->p = p;
    x->l = l;
    x->r = r;
    x->N  = N;

    return x;
}

static quotazione_t SearchR(link h, data_t data, link z){
    int cmp;

    if(h==z)
        return QUOTAZIONESetNull();

    cmp = DATAcmp(data, h->quotazione.data);

    if(cmp==0)
        return h->quotazione;
    if(cmp <0)
        return SearchR(h->l,data,z);
    return SearchR(h->r,data, z);
}

static link  insertR(link h, quotazione_t quotazione, link z){
    if(h==z)
        return BSTNew(quotazione,z, z,z,1);

    if(DATAcmp(quotazione.data, h->quotazione.data)<0) {
        h->l = insertR(h->l, quotazione, z);
        h->l->p = h;
    }
    else {
        h->r = insertR(h->r, quotazione, z);
        h->r->p = h;
    }
    (h->N)++;
    return h;
}

static int AltezzaMaxR(link root){
    int u,v;

    if(root == NULL)
        return -1;

    u = AltezzaMaxR(root->l);
    v = AltezzaMaxR(root->r);

    if(u>v)
        return u+1;
    return v+1;
}
static int AltezzaMinR(link root){
    int u,v;

    if(root == NULL)
        return -1;

    u = AltezzaMaxR(root->l);
    v = AltezzaMaxR(root->r);

    if(u<=v)
        return u+1;
    return v+1;
}

static  link bilanciaR(link h, link z){
    int r;

    if(h==z)
        return z;

    r = (h->N+1)/2-1;
    h= partR(h,r);
    h->l = bilanciaR(h->l, z);
    h->r = bilanciaR(h->r, z);

    return h;
}

static link partR(link h, int r){
    int t = h->l->N;

    if(t>r){
        h->l = partR(h->l,r);
        h = rotR(h);
    }
    if(t<r){
        h->r = partR(h->r,r-t-1);
        h = rotL(h);
    }
    return h;
}
static link rotR(link h) {
    link x = h->l;
    h->l = x->r;
    x->r->p = h;
    x->p = h->p;
    h->p = x;
    x->r = h;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}

static link rotL(link h) {
    link x = h->r;
    h->r = x->l;
    x->l->p = h;
    x->l = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}

quotazioneBST BSTInit(){
    quotazioneBST  BST = malloc(sizeof (*BST));
    BST->root = (BST->z = BSTNew(QUOTAZIONEInit(),NULL,NULL, NULL,0));
}


quotazione_t BSTSearch(quotazioneBST bst, data_t data){
    return SearchR(bst->root,data, bst->z);
}

void BSTInsert(quotazioneBST bst, quotazione_t quotazione){
    bst->root = insertR(bst->root, quotazione, bst->z);
}

int BSTAltezzaMax(quotazioneBST bst){
    return AltezzaMaxR(bst->root);
}
int BSTAltezzaMin(quotazioneBST bst){
    return AltezzaMinR(bst->root);
}

void BSTBilancia(quotazioneBST bst){
    bst->root = bilanciaR(bst->root, bst->z);
}

