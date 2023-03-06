#include "AlgoritmiOrdinamento.h"

void MergeSortR(int A[], int B[], int l, int r);
void Merge(int A[], int B[], int l, int q, int r);
void QuickSortR(int A[], int l,int r);
int Partition(int A[], int l,int r);
void Swap(int A[], int l, int r);

void MergeSort(int A[], int B[], int N){
    int l =0, r = N-1;
    MergeSortR(A,B,l,r);
}

void MergeSortR(int A[], int B[], int l, int r){
    int q;

    if(l>=r)
        return;

    q = (l+r)/2;
    MergeSortR(A,B,l,q);
    MergeSortR(A,B,q+1,r);
    Merge(A,B,l,q,r);
}

void Merge(int A[], int B[], int l, int q, int r){
    int i,j,k;

    i=l;
    j=q+1;

    for(k = l; k<=r;k++)
        if(i>q) //questo significa che ho esaurito gli elementi nel vettore sx, perciò devo copiare i restanti elementi del sottovettore dx in B
            B[k]  = A[j++];
        else if(j>r) //stessa cosa di prima ma nel caso di esaurimento nel sottovettore dx
            B[k] = A[i++];
        else if(A[i]<=A[j]) //se non ho ancora esaurito gli elementi, controllo quale dei due elementi è il minore e lo inserisco in B
            B[k] = A[i++];
        else
            B[k] = A[j++];

    for(k =l; k<=r;k++) //copio tutti gli elementi da B ad A
        A[k] = B[k];

    return;
}

void QuickSort(int A[], int N){
    int l=0, r = N-1;
    QuickSortR(A, l, r);
}

void QuickSortR(int A[], int l, int r){
    int q;

    if(l>=r)
        return;

    q = Partition(A, l,r);  //ogni volta che trovo un nuovo pivot faccio partire la quick sort sul sottovettore sinistro del pivot e destro
    QuickSortR(A,l,q-1);
    QuickSortR(A, q+1, r);

    return;
}

int Partition(int A[], int l,int r){
    int i=l-1, j=r, q = A[r];

    for(; ;){ //loop infinito fino a che non arrivo a i>=j
        while(A[++i]<q); //vado avanti incrementando i fino a che non trovo un elemento di A che è maggiore di q
        while(A[--j]>q); //vado avanti decrementando j fino a che non trovo un elemento di A che è minore di q
        if(i>=j)
            break;
        Swap(A,i,j); //scambio i due elementi di A agli indici i e j
    }
    Swap(A, i, r); //scambio l'elemento all'indice i con quello del pivot.

    return i; //ritorno il nuovo pivot
}

void Swap(int A[], int l, int r){
    int tmp = A[l];
    A[l] = A[r];
    A[r] = tmp;
}

void StampaVettore(int A[], int N){
    printf("[ ");

    for(int i=0; i<N; i++){
        printf("%d ", A[i]);
    }
    printf("]\n");
}