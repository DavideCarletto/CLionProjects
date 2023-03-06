#ifndef PREPARAZIONEESAME_LIST_H
#define PREPARAZIONEESAME_LIST_H

#endif //PREPARAZIONEESAME_LIST_H
#include "stdio.h"
#include "stdlib.h"
#include "../Item/Item.h"

typedef struct list *LIST;

LIST LISTinit();
void LISTload(FILE *fp, LIST list);
void LISTprint(FILE *fp, LIST list);
void LISTinhead(LIST list, Item val);
void LISTinttail(LIST list, Item val);
void LISTinOrder(LIST list, Item val);
Item LISTsearch(LIST list, int val);
void LISTdelHead(LIST list);
void LISTdelKey(LIST list, int k);