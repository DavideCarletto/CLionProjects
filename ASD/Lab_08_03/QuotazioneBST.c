#include "QuotazioneBST.h"

typedef struct BSTnode *link;

struct BSTNode{
    quotazione_t quotazione;
    link l,  r;
};

struct BST{
    link root, z;
};