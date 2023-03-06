#include "Graph.h"


typedef struct node *link;

struct node{int v; int wt; link next;};
struct graph{int V; int E; int **madj; link *ladj; link z; ST tab;};

static int **MATRIXinit(int r, int c, int val);
static link *LISTinit(int V, Graph G);
static Edge EDGEcreate(int v, int w, int wt);
static void insertE(Graph G, Edge e);
static link NEW(int v, int wt, link next);
static void dfsR(Graph G, Edge e, int *time, int  *pre, int *post,int *st);
static void bfs(Graph G, Edge e, int *time, int *pre, int *st, int *dist);
static void mstV(Graph G, int *st, int *wt);
static int pathR(Graph G, int v, int w, int *visited);
int GRAPHcc(Graph G);
void TSdfsR(Graph Dag, int v, int *ts, int *pre, int *time);
void SCCdfsR(Graph G,int w,int *scc,int *time0,int time1,int*post);


Graph GRAPHinit(int V){
    Graph  G  = malloc(sizeof *G);
    G->V=V;
    G->E=0;
    G->z = NEW(-1,-1, NULL);
    G->madj = MATRIXinit(V,V,0);
    G->ladj = LISTinit(V,G);
    G->tab = STinit(V);

    return G;
}

Graph GRAPHload(FILE *fp){
    int V,wt;
    char id1, id2;
    Graph G;

    fscanf(fp,"%d\n", &V);

    G = GRAPHinit(V);

    for(int i=0; i<V;i++){
        fscanf(fp, "%c\n",&id1);
        STinsert(G->tab, id1);
    }

    while(!feof(fp)){
        fscanf(fp, "%c %c %d\n", &id1, &id2, &wt);
        GRAPHinsertE(G, STsearch(G->tab, id1), STsearch(G->tab, id2),wt);
    }
    return G;
}

void GRAPHprint(Graph G){
    link x;

    for(int v =0; v<G->V;v++){
        for(x = G->ladj[v]; x != G->z; x = x->next){
            printf("%c-%c\n", STsearchByIndex(G->tab, v),STsearchByIndex(G->tab,x->v));
        }
        printf("\n");
    }

}
static int **MATRIXinit(int r, int c, int val){
    int **m = malloc(r*sizeof (int*));

    for(int i=0; i<r;i++) m[i]  = malloc(c*sizeof (int*));

    for(int i=0; i<r;i++){
        for(int j=0; j<c;j++)
            m[i][j] = val;
    }
    return m;
}

static link *LISTinit(int V, Graph G){
    int v;

    link *list = malloc(V*sizeof (link));

    for(v=0; v<V; v++)
        list[v] = G->z;

    return list;
}

void GRAPHinsertE(Graph G, int v, int w, int wt){
    insertE(G, EDGEcreate(v,w,wt));
}

void GRAPHdfs(Graph G, int id){
    int v, time=0,*pre, *post, *st;

    pre = malloc(G->V*sizeof (int));
    post = malloc(G->V*sizeof (int));
    st = malloc(G->V*sizeof (int));

    for(v=0; v<G->V;v++){
        pre[v] = -1;
        post[v] = -1;
        st[v] = -1;
    }
    dfsR(G, EDGEcreate(id,id,0), &time, pre, post, st);

    for(v=0; v<G->V;v++)
        if(pre[v]==-1)
            dfsR(G, EDGEcreate(v,v,0),&time,pre, post, st);

    printf("discovery/endprocessing time labels \n");
    for (v=0; v < G->V; v++)
        printf("%c:%d/%d\n",STsearchByIndex(G->tab,v),pre[v],post[v]);
}

static void dfsR(Graph G, Edge e, int *time, int  *pre, int *post,int *st){
    link t;
    int v, w = e.w;
    Edge x;

    if(e.v!= e.w)
        printf("(%c, %c): T \n", STsearchByIndex(G->tab, e.v), STsearchByIndex(G->tab, e.w));

    st[e.w] = e.v;
    pre[w] = (*time)++;

    for(t = G->ladj[w]; t != G->z; t = t->next){
        if(pre[t->v] == -1)
            dfsR(G, EDGEcreate(w,t->v,0),time,pre,post,st);
        else{
            v = t->v;
            x = EDGEcreate(w,v,0);

            if(post[v]==-1)
                printf("(%c, %c): B\n", STsearchByIndex(G->tab, x.v),STsearchByIndex(G->tab, x.w));
            if(pre[w]<pre[v])
                printf("(%c, %c): F\n",STsearchByIndex(G->tab, x.v),STsearchByIndex(G->tab, x.w));
            else
                printf("(%c, %c): C\n",STsearchByIndex(G->tab, x.v),STsearchByIndex(G->tab, x.w));

        }
    }
    post[w] = (*time)++;
}

void GRAPHbfs(Graph G, int id){
    int v, time=0, *pre, *st, *dist;

    pre = malloc(G->V*sizeof (int));
    dist = malloc(G->V*sizeof (int));
    st = malloc(G->V*sizeof (int));

    for(v=0; v<G->V;v++){
        pre[v] = -1;
        dist[v] = INT_MAX;
        st[v] = -1;
    }
    bfs(G, EDGEcreate(id,id,0), &time, pre, st, dist);

    printf("\n Resulting BFS tree \n");
    for (v=0; v < G->V; v++)
        if (st[v] != -1)
            printf("%c’s parent is:%c\n",STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, st[v]));
    printf("\n Levelizing \n");
    for (v=0; v < G->V; v++)
        if (st[v] != -1)
            printf("%c: %d \n",STsearchByIndex(G->tab,v),dist[v]);
}

static void bfs(Graph G, Edge e, int *time, int *pre, int *st, int *dist){
    int x;
    PQ pq = PQinit(G->V);
    // inserisco nella coda e
    dist[e.v] = -1;

//    while(!PQempty(pq))
//        if(pre[(e = PQget(q)).w]==-1){ estrai dalla coda un arco e se non è ancora scoperto
//                pre[e.w] = (*time)++  marco w come scoperto
//                st[e.w] = e.v;        indico che e.v è padre di e.w
//                dist[e.w] = dist[e.v]+1
//                for(x = 0; x<G->V; x++;) trovo i vertici x non ancora scoperti adiacenti a w e metto in coda tutti gli archi che connettono e.w ad essi
//                  if (G->madj[e.w][x] == 1)
//                      if (pre[x] == -1)
//                          Qput(q, EDGEcreate(e.w, x));
//                }
}
static void insertE(Graph G, Edge e){
    int v, w, wt;
    link x;

    v = e.v, w = e.w, wt = e.wt;

    if(G->madj[v][w]==0)
        G->E++;


    G->madj[w][v] = wt;
//    G->madj[v][w] = wt;

    if(G->ladj[v]==G->z){
        G->ladj[v] = NEW(w,wt,G->z);
        return;
    }

    for(x=G->ladj[v]; x->next != G->z; x = x->next);
    x->next = NEW(w, wt, G->z );
//    G->ladj[w] = NEW(v, wt, G->ladj[w]);

}

static link NEW(int v, int wt, link next){
    link x  = malloc(sizeof (*x));

    x->v = v;
    x->wt = wt;
    x->next = next;

    return x;
}

static Edge EDGEcreate(int v, int w, int wt){
    Edge edge;

    edge.v = v;
    edge.w = w;
    edge.wt = wt;

    return edge;
}
void GRAPHmstP(Graph G){
    int v, *st, *wt, weight = 0;

    st = malloc(G->V*sizeof (int)); // per ogni vertice che appartiene alla soluzione si registra il padre
    wt = malloc((G->V+1)*sizeof(int)); // per i vertici in S si registra il peso dell'arco al padre, mentre per i vertici non ancora dentro il peso dell'arco verso il vertice di S più vicino

    mstV(G, st, wt);

    printf("\nEdges in the MST: \n");
    for (v=0; v < G->V; v++) {
        if (st[v] != v) {
            printf("(%c-%c)\n",STsearchByIndex(G->tab,st[v]),STsearchByIndex(G->tab,v));weight += wt[v];
        }
    }
    printf("\nminimum weight: %d\n", weight);
}

static void mstV(Graph G, int *st, int *wt){
    int v, w, min, *fr = malloc(G->V*sizeof (int)); // in fr si registra per ogni vertice non ancora nella soluzione quale è il vertice in S più vicino.

    for(v =0; v<G->V; v++){
        st[v] = -1; fr[v] = v; wt[v] = INT_MAX;
    }

    st[0] = 0; wt[0] = 0; wt[G->V] = INT_MAX;

    for(min =0; min != G->V;){ //min  si incrementa opportunamente. Questo ciclo prende volta per volta il vertice a minima distanza e lo aggiunge a s
        v = min; st[min] = fr[min];
        for(w =0,min = G->V; w <G->V; w++) //ciclo interno sui vertici non ancora in S
            if(st[w] == -1){ //controllo se w non è ancora in S
                if(G->madj[v][w]<wt[w]){ //se l'arco migliora la stima
                    wt[w] = G->madj[v][w]; //la aggiorno
                    fr[w] = v; //indico che il vertice in S più vicino a w è v
                }
                if(wt[w]<wt[min]) //se w è diventato il vertice più vicino a S allora aggiorno min
                    min = w;
            }
    }

}

void GRAPHspBF(Graph G, int id){
    int v, i, negcycfound;
    link t;
    int *st, *d;

    st = malloc(G->V*sizeof(int));
    d = malloc(G->V*sizeof(int));
    for (v = 0; v < G->V; v++) {
        st[v]= -1;
        d[v] = INT_MAX;
    }
    d[id] = 0;
    st[id] = 0;

    for(i=0; i<G->V-1;i++)
        for(v = 0; v<G->V;v++)
            if(d[v]<INT_MAX)
                for(t = G->ladj[v]; t != G->z; t = t->next)
                    if(d[t->v]>d[v]+t->wt){
                        d[t->v] = d[v]+t->wt;
                        st[t->v] = v;
                    }

    negcycfound = 0;
    for (v=0; v<G->V; v++)
        if (d[v] < INT_MAX)
            for (t=G->ladj[v]; t!=G->z ; t=t->next)
                if (d[t->v] > d[v] + t->wt)
                    negcycfound = 1;
    if (negcycfound == 0) {
        printf("\n Shortest path tree\n");
        for (v = 0; v < G->V; v++)
            printf("Parent of %c is %c \n",
                   STsearchByIndex(G->tab, v),
                   STsearchByIndex (G->tab, st[v]));
        printf("\n Min.dist. from %c\n",
               STsearchByIndex (G->tab, id));

        for (v = 0; v < G->V; v++)
            printf("%c: %d\n", STsearchByIndex (G->tab, v), d[v]);}
    else
        printf("\n Negative cycle found!\n");
}

void GRAPHpath(Graph G, int id1, int id2){
    int t, found, *visited;

    visited = malloc(G->V*sizeof (int));

    for(t = 0; t<G->V;t++)
        visited[t] = 0;

    if(id1<0||id2<0)
        return;

    found = pathR(G, id1, id2, visited);
    if (found == 0)
        printf("\n Path not found!\n");

}

static int pathR(Graph G, int v, int w, int *visited){
    int t;

    if(v == w)
        return 1;

    visited[v] = 1;

    for(t = 0; t<G->V;t++){
        if(G->madj[v][t] == 1){
            if(visited[t] ==0){
                if(pathR(G,t,w,visited)){
                    printf("(%c, %c) in path\n",STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, t));
                    return 1;
                }
            }
        }
    }
    return 0;
}

void dfsRcc(Graph G, int v, int id, int *cc){ // semplicemente è una visita in profondità con incremento di id ogni volta che si fa ripartire la funzione
    link t;
    cc[v] = id;

    for(t = G->ladj[v]; t!= G->z; t = t->next){
        if(cc[t->v] == -1)
            dfsRcc(G,t->v, id , cc);
    }
}

int GRAPHcc(Graph G){
    int v, id =0, *cc;

    cc = malloc(G->V*sizeof (int));

    for(v =0; v<G->V;v++) cc[v] = -1;

    for(v =0; v<G->V;v++)
        if(cc[v] == -1)
            dfsRcc(G,v,id++,cc);

    for (v = 0; v < G->V; v++)
        printf("node %c in cc %d\n",STsearchByIndex(G->tab,v),cc[v]);
    return id;
}

void DAGrts(Graph Dag){
    int v, time =0, *pre, *ts;

    pre = malloc(Dag->V*sizeof (int));
    ts = malloc(Dag->V*sizeof (int));

    for(v =0; v<Dag->V;v++){
        pre[v] = -1;
        ts[v] =-1;
    }

    for(v =0; v< Dag->V;v++){
        if(pre[v] == -1)
            TSdfsR(Dag, v, ts, pre, &time);
    }
    printf("DAG nodes in reverse topological order \n");
    for (v=0; v < Dag->V; v++)
        printf("%c ", STsearchByIndex(Dag->tab, ts[v]));printf("\n");
}

void TSdfsR(Graph Dag, int v, int *ts, int *pre, int *time){
    link t; pre[v] = 0;

    for(t = Dag->ladj[v]; t != Dag->z; t = t->next){
        if(pre[t->v] == -1){
            TSdfsR(Dag, t->v, ts, pre, time);
        }
    }
    ts[(*time)++] = v;
}

Graph GRAPHreverse(Graph G){
    Graph R = GRAPHinit(G->V);

    int v;
    link t;

    for(v=0; v<G->V;v++){
        for(t = G->ladj[v]; t!= G->z;t = t->next)
            GRAPHinsertE(R,t->v,v,0);
    }
    return R;
}
int GRAPHscc(Graph G){
    Graph R = GRAPHreverse(G);

    int v, time0 = 0, time1 = 0, *sccG, *sccR, *postG, *postR; //time 0 è il contatore di un vertice che avanza solo quando di un vertice è terminata l'elaborazione, time 1 è il contatore delle SCC.

    sccG = malloc(G->V * sizeof(int));
    sccR = malloc(G->V * sizeof(int));
    postG = malloc(G->V * sizeof(int));
    postR = malloc(G->V * sizeof(int));

    for (v=0; v < G->V; v++) {
        sccG[v]=-1; sccR[v]=-1; postG[v]=-1; postR[v]=-1;
    }

    for(v=0; v<R->V;v++){
        if(sccR[v]==-1) {
            SCCdfsR(R, v, sccR, &time0, time1, postR);
        }
    }
    time0=0; time1=0;

    time0 = 0; time1 = 0;
    for (v = G->V-1; v >= 0; v--)
        if (sccG[postR[v]]==-1){
            SCCdfsR(G,postR[v], sccG, &time0, time1, postG);
            time1++;
        }
    printf("strongly connected components \n");
    for (v = 0; v < G->V; v++)
        printf("node %c in scc %d\n",STsearchByIndex(G->tab,v),sccG[v]);return time1;
}

void SCCdfsR(Graph G,int w,int *scc,int *time0,int time1,int*post) {
    link t;
    scc[w] = time1;

    for(t = G->ladj[w]; t != G->z; t = t->next){
        if(scc[t->v]==-1)
            SCCdfsR(G,t->v,scc, time0,time1, post);
    }
    post[(*time0)++]= w; //al tempo time0++ è terminato w, quindi c'è implicito ordinamento per tempi crescenti
}
