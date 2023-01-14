#ifndef LAB_08_03_QUOTAZIONEBST_H
#define LAB_08_03_QUOTAZIONEBST_H

#include "Quotazione.h"

typedef struct BST *quotazioneBST;

quotazioneBST BSTInit();
quotazione_t BSTSearch(quotazioneBST bst, data_t data);
void BSTInsert(quotazioneBST bst, quotazione_t quotazione);
int BSTAltezzaMax(quotazioneBST bst);
int BSTAltezzaMin(quotazioneBST bst);
void BSTBilancia(quotazioneBST bst);
void BSTPrint(quotazioneBST bst);
#endif //LAB_08_03_QUOTAZIONEBST_H
