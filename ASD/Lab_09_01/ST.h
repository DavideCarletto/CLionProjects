#ifndef LAB_09_01_ST_H
#define LAB_09_01_ST_H
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct symbolTable *ST;

ST STInit(int M);
void STfree(ST st);
void STInsert(ST tab,char *label);
int STsearch(ST tab, char *label);
char *STGetNameByIndex(ST tab, int index);
int STgetNumberOfVertex(ST tab);
int STGetIndexByName(ST tab, char *label);
#endif //LAB_09_01_ST_H
