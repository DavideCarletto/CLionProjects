#ifndef PREPARAZIONEESAME_ST_H
#define PREPARAZIONEESAME_ST_H
#include "stdlib.h"

typedef struct symbolTable *ST;

ST STinit(int N);
void STfree(ST tab);
void STinsert(ST tab, char V);
char STsearch(ST tab, char label);
char STsearchByIndex(ST tab, int id);
#endif //PREPARAZIONEESAME_ST_H
