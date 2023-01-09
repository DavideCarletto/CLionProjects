#include "Graph.h"
#include "ST.h"
#include "stdlib.h"
#include "string.h"

#define MAX_C 30

typedef struct node *link;

struct node {int v, wt;  link next;};

struct graph{int V,E,**madj; link *ladj, z; ST tab;};

static link NEWNode(int v, int wt, link next);
static link LISTInit(Graph G);
static void LISTInsertE(Graph G, Edge e);

Graph GRAPHinit(int V){
    Graph grafo =(Graph) malloc(sizeof (*grafo));
    grafo->V=V;
    grafo->E = 0;

    grafo->madj = MATRIXInit(V, V, 0);
    grafo->tab = STinit(V);

    return grafo;
}
void GRAPHfree(Graph G){
    for(int i=0; i<G->V; i++){
        free(G->madj[i]);
    }
    free(G->madj);
    STfree(G->tab);
    free(G);
}
Graph GRAPHload(FILE *fp){
    char *arco1 = malloc(MAX_C*sizeof (char )), *rete1=malloc(MAX_C*sizeof (char )),*arco2  = malloc(MAX_C*sizeof (char )), *rete2 = malloc(MAX_C*sizeof (char )), buffer[MAX_C];
    int wt, countArchi=0;
    while(!feof(fp)){
        fscanf(fp,"%s %s %s %s %d",buffer,buffer,buffer,buffer,&wt);
        countArchi++;
    }
    Graph graph = GRAPHinit(countArchi*2);
    rewind(fp);

    while (!feof(fp)){
        fscanf(fp,"%s %s %s %s %d\n",arco1,rete1,arco2,rete2,&wt);
        STinsert(graph->tab,arco1,rete1);
        STinsert(graph->tab,arco2,rete2);
        GRAPHinsertE(graph, STsearch(graph->tab,arco1), STsearch(graph->tab,arco2),wt);
    }
    STgetNameByIndex(graph->tab,2);
    return graph;
}

int** MATRIXInit(int r,int c,int val){
    int **madj = (int**) malloc(r*sizeof (int*));
    int i;

    for(i =0; i<r; i++)
        madj[i] = (int*) malloc(c*sizeof (int));

    for(i=0; i<r; i++){
        for(int j=0; j<c; j++){
            madj[i][j] = val;
        }
    }

    return madj;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt){
    insertE(G, EDGEcreate(id1, id2, wt));
}

void insertE(Graph G, Edge edge){
    int v= edge.v, w = edge.w, wt = edge.wt;
    if(G->madj[v][w] == 0){
        G->E++;
    }
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;
}

Edge EDGEcreate(int v, int w, int wt){
    Edge edge;

    edge.v = v;
    edge.w = w;
    edge.wt = wt;

    return edge;
}

void GRAPHprint(Graph G){
    int x,y;
    ST sortedTab = STinit(G->V);
    sortedTab = creaCopia(sortedTab, G->tab);
    STsort(sortedTab);

    for(int i=0; i< STgetNumberOfVertex(G->tab);i++){
        for(int j=0; j< STgetNumberOfVertex(G->tab);j++) {
            x = STgetIndexByName(G->tab, STgetNameByIndex(sortedTab,i));
            y = STgetIndexByName(G->tab, STgetNameByIndex(sortedTab,j));
            if(G->madj[x][y] != 0){
                printf("%s %s %s %s %d\n", STgetNameByIndex(sortedTab,i), STgetNetByIndex(G->tab,x),STgetNameByIndex(sortedTab,j),STgetNetByIndex(G->tab,y), G->madj[x][y] );
            }
        }
        printf("\n");
    }
}
int GRAPHCheckSottografoMat(Graph G){
    char *label1 = malloc(MAX_C*sizeof (char)), *label2 = malloc(MAX_C*sizeof (char)), *label3 = malloc(MAX_C*sizeof (char ));
    int index1, index2, index3, n=0;
    printf("Inserire i nomi dei 3 vertici:");
    scanf("%s %s %s",label1,label2,label3);

    index1 = STgetIndexByName(G->tab, label1);
    index2 = STgetIndexByName(G->tab, label2);
    index3 = STgetIndexByName(G->tab, label3);

    if(G->madj[index1][index2] && G->madj[index1][index2]!=0) n++;
    if(G->madj[index1][index3] && G->madj[index3][index1]!=0) n++;
    if(G->madj[index2][index3] && G->madj[index2][index3]!=0) n++;

//    printf("%d",n);
    if(n>=3)
        return 1;

    return 0;
}

void GRAPHGeneraList(Graph G){
    LISTInit(G);
}

static link NEWNode(int v, int wt, link next){
    link x = malloc(sizeof (*x));
    x->v = v;
    x->wt = wt;
    x->next = next;

    return x;
}

static link LISTInit(Graph G){
    G->z = NEWNode(-1,0, NULL);
    G->ladj = malloc(G->V*sizeof (link));

    for (int v = 0; v < G->V; v++)
        G->ladj[v] = G->z;

    for(int i=0; i<G->V;i++){
        for(int j=i; j<G->V; j++){
            if(G->madj[i][j] != 0){
                LISTInsertE(G, EDGEcreate(i,j,G->madj[i][j]));
            }
        }
    }
}

static void LISTInsertE(Graph G, Edge e){
    int v = e.v, w = e.w, wt = e.wt;
    G->ladj[v] = NEWNode(w, wt, G->ladj[v]);
    G->ladj[w] = NEWNode(v, wt, G->ladj[w]);
    G->E++;
}

int GRAPHCheckSottografoList(Graph G){
    char *label1 = malloc(MAX_C*sizeof (char)), *label2 = malloc(MAX_C*sizeof (char)), *label3 = malloc(MAX_C*sizeof (char ));
    int index1, index2, index3, n=0;
    link i;

    printf("Inserire i nomi dei 3 vertici:");
    scanf("%s %s %s",label1,label2,label3);

    index1 = STgetIndexByName(G->tab, label1);
    index2 = STgetIndexByName(G->tab, label2);
    index3 = STgetIndexByName(G->tab, label3);

    for(i=G->ladj[index1];i!=G->z;i=i->next) if(i->v==index2) n++;

    for(i=G->ladj[index2];i!=G->z;i=i->next) if(i->v==index3) n++;

    for(i=G->ladj[index3];i!=G->z;i=i->next) if(i->v==index1) n++;


    if(n==3) return 1;

    return 0;
}