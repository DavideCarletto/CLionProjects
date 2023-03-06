#include "Heap.h"

struct heap{
    int N;
    Item *A;
};

int LEFT(int i){ return (i*2+1);}
int RIGHT(int i) {return (i*2+2);}
int PARENT(int i) {return ((i-1)/2);}

static void Swap(Heap h, int i, int largest);

Heap HEAPinit(int maxN){
    Heap heap = malloc(sizeof (*heap));
    heap->A = malloc(maxN*sizeof (Item));
    heap->N=0;

    return heap;
}
void HEAPload(FILE *fp, Heap h, int N){
    Item item;
    int val;

    for(int i=0; i<N; i++){
        item = ITEMsetvoid();
        fscanf(fp,"%d ",&val);
        ITEMset(item, val);
        HEAPfill(h,item);
    }

}
void HEAPfree(Heap h){
    free(h->A);
    free(h);
}

void HEAPfill(Heap h, Item val){
    h->A[h->N++] = val;
}

void HEAPdisplay(FILE *fp, Heap h){
    for(int i=0; i<h->N;i++)
        fprintf(fp, "%d ", ITEMgetVal(h->A[i]));
    printf("\n");
}

void HEAPify(Heap h, int i){
  int l,r,largest;

  l = LEFT(i);
  r = RIGHT(i);

  if(l<h->N && ITEMgreater(h->A[l],h->A[i]))
      largest = l;
  else
      largest = i;
  if(r<h->N && ITEMgreater(h->A[r], h->A[largest]))
      largest = r;

  if(largest!= i){
      Swap(h,i,largest);
      HEAPify(h,largest);
  }
}
void HEAPBuild(Heap h){
    for(int i = PARENT(h->N-1); i>=0; i--)
        HEAPify(h,i);
}
void HEAPsort(Heap h){
    int j;

    HEAPBuild(h);
    j = h->N;
    for(int i = h->N-1; i>0;i--){
        Swap(h,0,i);
        h->N--;
        HEAPify(h,0);
    }
    h->N = j;
}


static void Swap(Heap h, int i, int largest){
    Item tmp = h->A[i];

    h->A[i] = h->A[largest];
    h->A[largest] = tmp;
}