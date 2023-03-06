#ifndef PREPARAZIONEESAME_ITEM_H
#define PREPARAZIONEESAME_ITEM_H
#include "stdlib.h"
#include "stdio.h"

typedef struct item *Item;
Item ITEMsetvoid();
void ITEMset(Item item,int val);
int ITEMgetVal(Item item);
int ITEMeq(Item item1, Item item2);
void ITEMprint(FILE *fp, Item val);
int ITEMgreater(Item item1, Item item2);
int ITEMcmp(Item item1, Item item2);
#endif //PREPARAZIONEESAME_ITEM_H
