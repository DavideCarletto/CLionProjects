#include "Graph.h"
#include "stdlib.h"

#define MAX_C 100

typedef struct node *link;

struct node{int v, wt; link next;};

struct graph{
    int V, E;
    link *ladj, z;
    ST tab;
};


int dfsR(Graph G, Edge e, int *time,int *pre, int *post, int *st, int back);
static link NEW(int v, int wt, link next);

static link NEW(int v, int wt, link next){
    link x = malloc(sizeof *x);
    x->v = v; x->wt = wt; x->next = next;

    return x;
}
Graph  GRAPHLoad(FILE *fp, Edge **elencoArchi, int *countArchi){
    int V, i, id1, id2, wt;
    char label1[MAX_C], label2[MAX_C];
    Graph G;

    fscanf(fp, "%d", &V);

    G = GRAPHInit(V);

    *elencoArchi = (Edge *) malloc((G->V*G->V)*sizeof (Edge));

    for(i =0; i<V; i++){
        fscanf(fp, "%s", label1);
        STInsert(G->tab,label1);
    }

    while(!feof(fp)){
        fscanf(fp,"%s %s %d\n",label1, label2,&wt);
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        GRAPHInsertE(G, EDGECreate(id1, id2, wt));
        (*elencoArchi)[(*countArchi)++] = EDGECreate(id1,id2,wt);
    }
    return G;
}

void GRAPHPrint(Graph G){
    for(int i=0; i<G->V; i++){
        for(link x = G->ladj[i]; x != NULL; x = x->next){
            if(x->v!= -1)
                printf("%s %s %d\n", STGetNameByIndex(G->tab,i),  STGetNameByIndex(G->tab,x->v), x->wt);
        }
    }
}
Graph GRAPHInit(int V){
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E= 0;
    G->z = NEW(-1,-1,NULL);
    G->ladj= malloc(G->V*sizeof (link));
    for(int i=0; i<G->V; i++){
        G->ladj[i] = G->z;
    }
    G->tab = STInit(V);
    return G;
}


void GRAPHfree(Graph G) {
    int v;
    link t, next;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = next) {
            next = t->next;
            free(t);
        }
    STfree(G->tab);
    free(G->ladj); free(G->z); free(G);
}
Edge EDGECreate(int v, int w, int wt){
    Edge e;
    e.v = v; e.w = w; e.wt = wt;
    return e;
}

void GRAPHInsertE(Graph G, Edge e){
    int v = e.v, w = e.w, wt = e.wt;
    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->E++;
}

void GRAPHedges(Graph G, Edge *a) {
    int v, E = 0;
    link t;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = t->next)
            if (v < t->v) a[E++] = EDGECreate(v, t->v, t->wt);
}

int dfsR(Graph G, Edge e, int *time,int *pre, int *post, int *st, int back){
    link t;
    int v, w = e.w;
    Edge x;
    st[e.w] = e.v;
//    if (e.v != e.w)
//        printf("(%s, %s): T \n",STGetNameByIndex(G->tab, e.v), STGetNameByIndex(G->tab, e.w));st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            back = dfsR(G, EDGECreate(w, t->v,-1), time, pre, post, st,back);
        else {
            v = t->v;
            x = EDGECreate(w, v,-1);
            if (post[v] == -1) {
//                printf("(%s, %s): B\n", STGetNameByIndex(G->tab, x.v), STGetNameByIndex(G->tab, x.w));
                back++;
            }
//            else
//            if (pre[v] > pre[w])
//                printf("(%s,%s):F\n",STGetNameByIndex(G->tab, x.v),STGetNameByIndex(G->tab, x.w));
//            else
//                printf("(%s,%s):C\n",STGetNameByIndex(G->tab, x.v),STGetNameByIndex(G->tab, x.w));
        }
    post[w] = (*time)++;
    return back;
}


int GRAPHextendedDfs(Graph G, int id) {
    int v, time=0, *pre, *post, *st, back=0;
    pre= malloc(G->V * sizeof(int));
    post= malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));

    for (v=0;v<G->V;v++) {
        pre[v]=-1; post[v]=-1; st[v]=-1;
    }
    back += dfsR(G, EDGECreate(id,id,-1), &time, pre, post, st,0);

    for (v=0; v < G->V; v++)
        if (pre[v]==-1)
            back += dfsR(G,EDGECreate(v,v,-1),&time,pre,post,st,0);

//    for (v=0; v < G->V; v++)
//        printf("%s:%d/%d\n",STGetNameByIndex(G->tab,v),pre[v],post[v]);printf("resulting DFS tree \n");
//    for (v=0; v < G->V; v++)
//        printf("%s's parent: %s \n",STGetNameByIndex (G->tab, v),STGetNameByIndex (G->tab, st[v]));
    return back;
}


void comb_semplici(Graph G, Edge *elencoArchi, int* curSol, Edge ** sol, int *found, int len, int pos, int start, int k, int *elencoArchiRmv){
    if(pos>=k){
        int back;
        if((back =GRAPHextendedDfs(G, 0))==0){
            *found = 1;
            printf("Trovata una possibile soluzione con rimozione dei seguenti archi:\n",back);
            for(int i=0; i<pos; i++){
                sol[*elencoArchiRmv][i] = GRAPHGetEdgeFromArray(elencoArchi,curSol[i]);
                EDGEPrint(elencoArchi[curSol[i]],G);
            }
            printf("\n");
            (*elencoArchiRmv)++;
        }
//        else {
//            printf("%d La soluzione corrente non va bene\n", back);
//            for(int i=0; i<pos; i++){
//                EDGEPrint(elencoArchi[sol[i]],G);
//            }
//        }
        return;
    }

    for (int i = start; i < len; ++i) {
        curSol[pos] = i;
        GRAPHRemoveE(G, elencoArchi[i]);
        comb_semplici(G,elencoArchi,curSol, sol, found, len, pos+1, i+1, k,elencoArchiRmv);
        GRAPHInsertE(G, elencoArchi[i]);
    }
}

void GRAPHRemoveE(Graph G, Edge e) {
    int v = e.v, w = e.w; link x, p;
    for (x = G->ladj[v], p = NULL; x != G->z; p = x, x = x->next) {
        if (x->v == w) {
            if (x == G->ladj[v])
                G->ladj[v] = x->next;
            else
                p->next = x->next;
            break;
        }
    }
    G->E--; free(x);
}

void EDGEPrint(Edge e, Graph G){
    printf("%s %s %d\n", STGetNameByIndex(G->tab, e.v), STGetNameByIndex(G->tab, e.w), e.wt);
}

int GRAPHGetTotWeight(Edge *elencoArchi, int nArchi){
    int wt=0;
    Edge e;

    for(int i=0; i<nArchi;i++){
        e = GRAPHGetEdgeFromArray(elencoArchi, i);
        wt+=e.wt;
    }

    return wt;
}

Edge GRAPHGetEdgeFromArray(Edge *elencoArchi, int index){
    return elencoArchi[index];
}

void TSdfsR(Graph D, int v, int *ts, int *pre, int *time) {link t; pre[v] = 0;
    for (t = D->ladj[v]; t != D->z; t = t->next)
        if (pre[t->v] == -1)
            TSdfsR(D, t->v, ts, pre, time);
    ts[(*time)--] = v;
}
int DAGrts(Graph D) {
    int v, time = (D->V)-1, *pre, *ts;
    pre=malloc((D->V)*sizeof(Graph));
    ts=malloc((D->V)*sizeof(Graph));
    for (v=0; v < D->V; v++) { pre[v] = -1; ts[v] = -1; }


    for (v=0; v < D->V; v++)
        if (pre[v]== -1) {
            TSdfsR(D, v, ts, pre, &time);
        }

    printf("\n");
    printf("Ordine topologico del DAG:\n");
    for (v=0; v < D->V; v++)
        printf("%s ", STGetNameByIndex(D->tab, ts[v]));

    printf("\n\n");
    return ts[0]; //prima sorgente
}

void DAGGetLongestPath(Graph D, int source){
    int v, time = (D->V)-1, *pre, *ts;
    pre=malloc((D->V)*sizeof(Graph));
    ts=malloc((D->V)*sizeof(Graph));
    for (v=0; v < D->V; v++) { pre[v] = -1; ts[v] = -1; }

    if (pre[source]== -1) {
        TSdfsR(D, source, ts, pre, &time);
        GRAPHspBF(D, source);
    }

    for(v=0; v<D->V;v++) {
        if (pre[v] == -1) {
            TSdfsR(D, v, ts, pre, &time);
            GRAPHspBF(D, v);
        }
    }
}

void GRAPHspBF(Graph G, int id){
    int v, i, negcycfound, minWT = INT_MIN;
    link t;
    int *st, *d;
    st = malloc(G->V*sizeof(int));
    d = malloc(G->V*sizeof(int));

    for (v = 0; v < G->V; v++) {
        st[v]= 0;
        d[v] = minWT;
    }
    d[id] = 0;
    st[id] = id;
    for (i=0; i<G->V-1; i++)
        for (v=0; v<G->V; v++)
            if (d[v] != minWT)
                for (t=G->ladj[v]; t!=G->z ; t=t->next)
                    if (d[t->v] < d[v] + t->wt) {
                        d[t->v] = d[v] + t->wt;
                        st[t->v] = v;
                    }
    negcycfound = 0;
    for (v=0; v<G->V; v++)
        if (d[v] != minWT)
            for (t=G->ladj[v]; t!=G->z ; t=t->next)
                if (d[t->v] < d[v] + t->wt)
                    negcycfound = 1;

    if (negcycfound == 0) {
        printf("\n Massima distanza da %s\n",
               STGetNameByIndex (G->tab, id));
        for (v = 0; v < G->V; v++) {
            printf("%s: ", STGetNameByIndex(G->tab, v));
            if(d[v]==minWT)
                printf("Non raggiungibile\n");
            else
                printf("%d\n", d[v]);
        }
    }
    else
        printf("\n Ciclo a peso negativo trovato!\n");
}