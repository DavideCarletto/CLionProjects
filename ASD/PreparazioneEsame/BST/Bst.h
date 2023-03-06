#ifndef PREPARAZIONEESAME_BST_H
#define PREPARAZIONEESAME_BST_H

#endif //PREPARAZIONEESAME_BST_H

#include "stdio.h"
#include "stdlib.h"
#include "../Item/Item.h"

typedef struct binarysearchtree *BST;

BST BSTinit();
void BSTfree(BST bst);
int BSTcount(BST bst);
int BSTempty(BST bst);
Item BSTmin(BST bst);
Item BSTmax(BST bst);
void BSTinsert_leafI(BST bst, Item x);
void BSTinsert_leafR(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);
Item BSTsearch(BST bst, int k);
void BSTdelete(BST bst, int k);
Item BSTselect(BST bst, int r);
void BSTvisit(BST bst, int strategy);
Item BSTsucc(BST bst, int k);
Item BSTpred(BST bst, int k);
void BSTbalance(BST bst);
void BSTload(FILE *fp, BST bst, int N);


