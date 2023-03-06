#ifndef PREPARAZIONEESAME_GRAPH_H
#define PREPARAZIONEESAME_GRAPH_H
#include "stdio.h"
#include "stdlib.h"
#include "ST.h"
#include "../Code/PQ.h"

typedef struct edge{int v; int w; int wt;} Edge;
typedef struct graph *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph G);
Graph GRAPHload(FILE *fp);
void GRAPHinsertE(Graph G, int v, int w, int wt);
void  GRAPHprint(Graph G);
void GRAPHdfs(Graph G, int id);
void GRAPHbfs(Graph G, int id);
void GRAPHmstP(Graph G);
void GRAPHspBF(Graph G, int id);
void GRAPHpath(Graph G, int id1, int id2);
void dfsRcc(Graph G, int v, int id, int *cc);
void DAGrts(Graph Dag);
int GRAPHscc(Graph G);
Graph GRAPHreverse(Graph G);

#endif //PREPARAZIONEESAME_GRAPH_H
