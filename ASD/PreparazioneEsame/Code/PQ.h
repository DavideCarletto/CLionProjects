#ifndef PREPARAZIONEESAME_PQ_H
#define PREPARAZIONEESAME_PQ_H

#endif //PREPARAZIONEESAME_PQ_H
#include "../Item/Item.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct pqueue *PQ;

PQ PQinit(int maxN);
void PQfree(PQ pq);
int PQempty(PQ pq);
void PQload(FILE *fp, PQ pq, int N);
void PQ_HEAPify(PQ pq, int i);
void PQinsert(PQ pq, Item val);
Item PQextractMax(PQ pq);
Item PQshowMax(PQ pq);
void PQdisplay(FILE *fp,PQ pq);
int PQsize(PQ pq);
void PQchange(PQ pq, Item val);

