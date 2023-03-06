#include "PQ.h"

struct pqueue{
    Item *A;
    int N;
};

int PQ_LEFT(int i){ return (i*2+1);}
int PQ_RIGHT(int i) { return (i*2+2);}
int PQ_PARENT(int i) {return ((i-1)/2);}
static void Swap(PQ pq, int i, int largest);

PQ PQinit(int maxN){
    PQ pq  = malloc(sizeof (PQ*));
    pq->A = malloc(maxN*sizeof (Item));
    pq->N = 0;

    return pq;
}

void PQfree(PQ pq){
    free(pq->A);
    free(pq);
}

int PQempty(PQ pq){
    return pq->N==0;
}
void PQload(FILE *fp, PQ pq, int N){
    Item item;
    char val[5];

    for(int i=0; i<N;i++){
        item = ITEMsetvoid();
        fscanf(fp, "%s ",&val);

        if(strcmp(val,"*")==0)
            PQextractMax(pq);
        else {
            ITEMset(item, atoi(val));
            PQinsert(pq, item);
        }
    }
}
void PQinsert(PQ pq, Item val){
    int i = pq->N++;

    while ((i>=1) && ITEMgreater(val,pq->A[PQ_PARENT(i)])){
        pq->A[i] = pq->A[PQ_PARENT(i)];
        i = PQ_PARENT(i);
    }
    pq->A[i] = val;
}

Item PQextractMax(PQ pq){
    Item val;
    Swap(pq, 0,pq->N-1);
    val = pq->A[pq->N-1];
    pq->N--;
    PQ_HEAPify(pq, 0);

    return val;
}

Item PQshowMax(PQ pq){
    return pq->A[0];
}

void PQdisplay(FILE *fp,PQ pq){

    for(int i=0; i<pq->N; i++)
        ITEMprint(fp, pq->A[i]);
    printf("\n");
}
int PQsize(PQ pq){
    return pq->N;
}
void PQchange(PQ pq, Item val){
    int pos, found =0;

    for(int i=0; i<pq->N && found==0;i++){
        if(ITEMeq(pq->A[i],val)){ //in realtà bisognerebbe fare un controllo sulle chiavi ma per come l'ho impostato io non ha senso. per cui non funziona, ma l'idea è quella.
            found =1;
            pos =i;
        }
    }

    if(found==1){
        while (pos>=1 && !ITEMgreater(pq->A[PQ_PARENT(pos)],val)){ //qui il controllo dovrebbe essere sulle priorità, che se la intendo come val allora va bene
            pos = PQ_PARENT(pos);
        }
        pq->A[pos] = val;
        PQ_HEAPify(pq, pos);
    } else
        printf("Chiave non trovata.\n");
}


static void Swap(PQ pq, int i, int largest) {
    Item tmp = pq->A[i];

    pq->A[i] = pq->A[largest];
    pq->A[largest] = tmp;
}

void PQ_HEAPify(PQ pq, int i){
    int l,r,largest;

    l = PQ_LEFT(i);
    r = PQ_RIGHT(i);

    if(l < pq->N && ITEMgreater(pq->A[l], pq->A[i]))
        largest = l;
    else
        largest = i;
    if(r < pq->N && ITEMgreater(pq->A[r], pq->A[largest]))
        largest = r;

    if(largest!= i){
        Swap(pq, i, largest);
        PQ_HEAPify(pq, largest);
    }
}