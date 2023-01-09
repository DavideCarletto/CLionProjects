#ifndef LAB_08_02_GRAPH_H
#define LAB_08_02_GRAPH_H

#include "stdio.h"

typedef struct edge{int v, w, wt;  } Edge;
typedef struct graph *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph G);
Graph GRAPHload(FILE *fp);
int** MATRIXInit(int r,int c,int val);
void GRAPHinsertE(Graph G, int id1, int id2, int wt);
void insertE(Graph G, Edge edge);
Edge EDGEcreate(int v, int w, int wt);
void GRAPHprint(Graph G);
int GRAPHCheckSottografoMat(Graph G);
int GRAPHCheckSottografoList(Graph G);
void GRAPHGeneraList(Graph G);
//...

#endif //LAB_08_02_GRAPH_H
