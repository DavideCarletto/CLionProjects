#ifndef LAB_08_02_ST_H
#define LAB_08_02_ST_H

#include "stdio.h"

typedef struct st *ST;

ST STinit(int maxN);
void STfree(ST symboltable);
void STinsert(ST tab, char *vertice, char *sottoRete);
int STsearch(ST tab, char *label);
char* STgetNameByIndex(ST tab, int index);
char* STgetNetByIndex(ST tab, int index);
void STprint(ST tab);
ST STsort(ST tab);
int STgetNumberOfVertex(ST tab);
void STsetNumberOfVertex(ST tab, int N);
int STgetIndexByName(ST tab, char *label);
ST creaCopia(ST sortedTab, ST tab);
//...

#endif //LAB_08_02_ST_H
