#ifndef PREPARAZIONEESAME_HEAP_H
#define PREPARAZIONEESAME_HEAP_H

#endif //PREPARAZIONEESAME_HEAP_H
#include "../Item/Item.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct heap *Heap;
Heap HEAPinit(int maxN);
void HEAPload(FILE *fp, Heap h, int N);
void HEAPfree(Heap h);
void HEAPfill(Heap h, Item val);
void HEAPify(Heap h, int i);
void HEAPsort(Heap h);
void HEAPdisplay(FILE *fp, Heap h);
void HEAPBuild(Heap h);
