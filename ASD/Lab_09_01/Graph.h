#ifndef LAB_09_01_GRAPH_H
#define LAB_09_01_GRAPH_H

#include "stdio.h"
#include "ST.h"

typedef struct edge{int v, w, wt;} Edge;
typedef struct graph *Graph;

Graph  GRAPHLoad(FILE *fp, Edge **elencoArchi, int *countArchi);
Graph GRAPHInit(int V);
int** MATRIXInit(int r, int c, int val);
void GRAPHfree(Graph G);
void GRAPHPrint(Graph G);
Edge EDGECreate(int v, int w, int wt);
void GRAPHInsertE(Graph G, Edge e);
int GRAPHextendedDfs(Graph G, int id);
void comb_semplici(Graph G, Edge *elencoArchi, int* curSol, Edge ** sol, int *found, int len, int pos, int start, int k, int *elencoArchiRmv);
void GRAPHRemoveE(Graph G, Edge e);
Edge GRAPHGetEdgeFromArray(Edge *elencoArchi, int index);
void EDGEPrint(Edge e, Graph G);
int GRAPHGetTotWeight(Edge *elencoArchi, int nArchi);
int DAGrts(Graph G);
void GRAPHspBF(Graph G, int id);
void DAGGetLongestPath(Graph D, int source);
#endif //LAB_09_01_GRAPH_H
