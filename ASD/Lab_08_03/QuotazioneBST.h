#ifndef LAB_08_03_QUOTAZIONEBST_H
#define LAB_08_03_QUOTAZIONEBST_H

#include "Quotazione.h"
#include "TitoliList.h"

typedef struct BST *quotazioneBST;

quotazioneBST BSTInit();
quotazione_t BSTSearch(quotazioneBST bst, char *data);
void BSTLoad(quotazioneBST bst, LIST list);
#endif //LAB_08_03_QUOTAZIONEBST_H
