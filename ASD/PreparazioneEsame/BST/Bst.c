#include "Bst.h"

#define PREORDER 0
#define INORDER 1
#define POSTORDER 2

typedef struct node *link;

struct node{
    Item val;
    link l;
    link r;
    link p;
    int N; //dimensione sottoalbero
};

struct binarysearchtree{
    link root, z;
    int N;
};

static link NEW(Item item, link p, link l, link r, int N);
static void treeFree(link h, link z);
static int countR(link h, link z);
static Item searchR(link h, link z, int k);
static Item minR(link h, link z);
static Item maxR(link h, link z);
static link insertR(link h, Item x, link z);
static void treePrintR(link h, link z, int strategy);
static link rotR(link h);
static link rotL(link h);
static link insertT(link h,Item x, link z);
static Item selectR(link h,int r, link z);
static link partR(link h, int r);
static Item searchSucc(link h, int k, link z);
link joinLR(link a, link b, link z);
link deleteR(link h, int k, link z);
static link balanceR(link h, link z);


static link NEW(Item item, link p, link l, link r, int N){
    link x = malloc(sizeof (*x));

    x->val = item;
    x->p = p; x->l = l; x->r = r; x->N = N;

    return x;
}

static void treeFree(link h, link z){
    if(h==z)
        return;

    treeFree(h->l,z);
    treeFree(h->r,z);
    free(h);
}

static int countR(link h, link z){
    if(h==z)
        return 0;
    return countR(h->l,z)+ countR(h->r, z)+1;
}
BST BSTinit(){
    BST bst = malloc(sizeof (BST*));

    bst->root = (bst->z = NEW(ITEMsetvoid(),NULL, NULL, NULL, 0));
    return bst;

}

void BSTfree(BST bst){
    treeFree(bst->root,bst->z);
    free(bst->z);
    free(bst);
}


int BSTcount(BST bst){
    return countR(bst->root,bst->z);
}

int BSTempty(BST bst) {
    if (BSTcount(bst) == 0)
        return 1;
    return 0;
}

Item BSTsearch(BST bst, int k){
    return searchR(bst->root, bst->z,k);
}

static Item searchR(link h, link z, int k){
    int cmp;
    Item item = ITEMsetvoid();
    ITEMset(item, k);

    if(h == z)
        return ITEMsetvoid();

    cmp = ITEMcmp(h->val, item);

    if(cmp == 0)
        return h->val;
    if(cmp == -1)
        return searchR(h->l,z,k);
    return searchR(h->r,z,k);
}

Item BSTmin(BST bst){
    return minR(bst->root,bst->z);
}
Item BSTmax(BST bst){
    return maxR(bst->root,bst->z);
}

static Item minR(link h, link z){
    if(h == z)
        return ITEMsetvoid();
    if(h->l == z)
        return h->val;
    return minR(h->l,z);
}


static Item maxR(link h, link z){
    if(h == z)
        return ITEMsetvoid();
    if(h->r == z)
        return h->val;
    return minR(h->r,z);
}

void BSTinsert_leafI(BST bst, Item x){
    bst->root = insertR(bst->root, x, bst->z);
}

static link insertR(link h, Item x, link z){
    if(h==z)
        return NEW(x,z,z,z,1);

    if(ITEMcmp(x,h->val)==-1) {
        h->l = insertR(h->l, x, z);
        h->l->p = h;
    }
    else{
        h->r = insertR(h->r,x,z);
        h->r->p = h;
    }
    (h->N)++;

    return h;
}

void BSTvisit(BST bst, int strategy){
    if(BSTempty(bst))
        return;
    treePrintR(bst->root,bst->z, strategy);
}

static void treePrintR(link h, link z, int strategy){
    if(h == z)
        return;

    if(strategy == PREORDER)
        ITEMprint(stdout,h->val);
    treePrintR(h->l,z,strategy);

    if(strategy == INORDER)
        ITEMprint(stdout,h->val);
    treePrintR(h->r, z, strategy);

    if(strategy == POSTORDER)
        ITEMprint(stdout,h->val);
}

static link rotR(link h){
    link x = h->l;
    h->l = x->r;
    x->r->p = h;
    x->r = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
}

static link rotL(link h){
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

void BSTinsert_root(BST bst, Item x){
    bst->root = insertT(bst->root, x, bst->z);
}

static link insertT(link h,Item x, link z){
    if(h == z)
        return NEW(x,z,z,z,1);

    if(ITEMcmp(x, h->val) == -1){
        h->l = insertT(h->l,x,z);
        h = rotR(h);
        h->N++;
    }
    else{
        h->r = insertT(h->r,x,z);
        h  = rotL(h);
        h->N++;
    }
    return h;
}

Item BSTselect(BST bst, int r){
    return selectR(bst->root,r, bst->z);
}

static Item selectR(link h,int r, link z){
    int t;

    if(h==z)
        return ITEMsetvoid();
    t = h->l->N;

    if(t>r)
        return selectR(h->l,r,z);
    if(t<r)
        return selectR(h->r, r-t-1,z);
    return h->val;
}

static link partR(link h, int r){
    int t  = h->l->N;

    if(t>r){
        h->l = partR(h->l,r);
        h = rotR(h);
    }
    if(t<r){
        h->r = partR(h->r, r-t-1);
        h = rotL(h);
    }
    return h;
}

Item BSTsucc(BST bst, int k){
    return searchSucc(bst->root,k,bst->root);
}

static Item searchSucc(link h, int k, link z){
    link p;
    Item item = ITEMsetvoid();
    ITEMset(item ,k);

    if(h==z) return ITEMsetvoid();

    if(ITEMcmp(item,h->val)==0){
        if(h->r != z) return minR(h->r,z);
        else{
            p = h->p;
            while(p!= z && h == p->r){
                h = p; p = p->p;
            }
            return p->val;
        }
    }
    if(ITEMcmp(item,h->val)==-1)
        return searchSucc(h->l,k,z);
    return searchSucc(h->r,k,z);

}
Item searchPred(link h, int k, link z) {
    link p;
    Item item = ITEMsetvoid();
    ITEMset(item ,k);

    if (h == z) return ITEMsetvoid();
    if (ITEMcmp(item,h->val)==0==0) {
        if (h->l != z) return maxR(h->l, z);
        else {
            p = h->p;
            while (p != z && h == p->l) {h = p; p = p->p;}
            return p->val;
        }
    }
    if (ITEMcmp(item,h->val)==-1)
        return searchPred(h->l, k, z);
    return searchPred(h->r, k, z);
}
Item BSTpred(BST bst, int k) {
    return searchPred(bst->root, k, bst->z);
}
link joinLR(link a, link b, link z) {
    if (b == z)
        return a;
    b = partR(b, 0);
    b->l = a;
    a->p = b;
    b->N = a->N + b->r->N +1;
    return b;
}


link deleteR(link h, int k, link z) {
    link y, p;
    Item item = ITEMsetvoid();
    ITEMset(item, k);

    if (h == z) return z;
    if (ITEMcmp(item, h->val)==-1)
        h->l = deleteR(h->l, k, z);
    if (ITEMcmp(item, h->val)==1)
        h->r = deleteR(h->r, k, z);
    (h->N)--;
    if (ITEMcmp(item, h->val)==0) {
        y = h; p = h->p;
        h = joinLR(h->l, h->r, z); h->p = p;
        free(y);
    }
    return h;
}
void BSTdelete(BST bst, int k) {
    bst->root= deleteR(bst->root, k, bst->z);
}

static link balanceR(link h, link z) {
    int r;
    if (h == z)
        return z;
    r = (h->N+1)/2-1;
    h = partR(h, r);
    h->l = balanceR(h->l, z);
    h->r = balanceR(h->r, z);
    return h;
}
void BSTbalance(BST bst) {
    bst->root = balanceR(bst->root, bst->z);
}

void BSTload(FILE *fp, BST bst, int N){
    int val;
    Item item;

    for(int i=0; i<N;i++){
        item = ITEMsetvoid();
        fscanf(fp, "%d ", &val);
        ITEMset(item, val);
        BSTinsert_leafI(bst, item);
    }
}