#include <stdio.h>
#include "Ricorsione/AlgoritmiOrdinamento.h"
#include "Ricorsione/CalcoloCombinatorio.h"
#include "stdlib.h"
#include  "Grafi/Graph.h"
#include "Liste/List.h"
#include "Code/Heap.h"
#include "Code/PQ.h"
#include "BST/Bst.h"

void provaAlgoritmiOrdinamento();
void provaCalcoloCombinatorio();
int* alloca2D(int n);
void GRAPHprova();
void LISTprova();
void CODEprova();
void BSTprova();

int main() {
//    provaAlgoritmiOrdinamento();
//provaCalcoloCombinatorio();
GRAPHprova();
//LISTprova();
//CODEprova();
//BSTprova();
    return 0;
}

void provaAlgoritmiOrdinamento(){
    int A[10] = {1,3,0,4,1,5,9,7,2,0}, B[10];
    printf("Vettore non ordinato: ");
    StampaVettore(A,10);
    MergeSort(A,B,10);
    printf("Vettore ordinato con MergeSort (stabile): ");
    StampaVettore(A,10);
    QuickSort(A,10);
    printf("Vettore ordinato con QuickSort (non stabile): ");
    StampaVettore(A,10);
}

void provaCalcoloCombinatorio(){
    int *sol,*val, *mark, lenght = 5, nLivelli =3, cnt=0;
    Livello *livelli = NULL;
    sol = alloca2D(lenght);

//    ------------- princ_molt ---------------

//    livelli  = malloc(nLivelli*sizeof(Livello));
//
//    generaVettoreLivelli(livelli, nLivelli);
//
//    for(int i=0; i<nLivelli;i++){
//        printf("Vettore %d: ",i+1);
//        stampaVettore(livelli[i].val, livelli[i].nScelte);
//    }
//-----------------------------------------------------------------


//    ------------- disp_semplici ---------------

    val = alloca2D(5);
    sol = alloca2D(5);
    mark = calloc(5, sizeof (int));

    generaVettore(val, 5);
    printf("Vettore: ");
    stampaVettore(val, 5);

//    printf("Possibili combinazioni:\n");
//    printf("Powerset:\n");
    printf("Partizione dell'insieme:\n");
//    cnt = princ_molt(0,livelli,sol,3,0);                              // Le possibili combinazioni si ottengono moltiplicando per ogni livello il numero di scelte possibili
//    cnt = disp_semplici(0,val, sol, mark, 5, 3 , cnt);                // Le possibili combinazioni sono n!/(n-k)!
//    cnt = disp_ripetute(0,val, sol, 5,3,cnt);                         // Le possibili combinazioni sono n^k
//    cnt = perm_semplici(0, val, sol, mark, 5, cnt);                   // Le possibili combinazioni sono n!
//    cnt = perm_ripetute(0, val, sol, mark, 5, cnt);                   // Le possibili combinazioni sono n!/(a!*b!...) con a,b le occorrenze di ciascun elemento ripetuto. Mark deve contenere il numero di occorrenze per ogni elemento (no solo 0 e 1).
//    cnt = comb_semplici(0,0,val, sol, 5, 3, cnt);                     // Le possibili combinazioni sono n!(k!*(n-k)!)
//    cnt = comb_ripetute(0,0,val, sol, 5 ,3, cnt);                     // Le possibili combinazioni sono (n+k-1)!/(k!(n-1)!)

//    cnt = powerset_divide_et_impera(0,0,val, sol,5,cnt);
//    cnt = powerset_disp_rip(0,val,sol, 5, cnt);
//    cnt = powerset_comb_semp(val, sol, 5);
//    partition_disp_rip(0,val, sol, 5, 3);
        algoritmo_ER(0,3,val,sol,5,0);
//    printf("In totale sono %d", cnt);
}

int* alloca2D(int n){
    int *val = (int*) malloc(n*sizeof (int));

    return val;
}

void GRAPHprova(){
    FILE *fp;

    if((fp = fopen("../Grafi/Grafo2_esame.txt","r"))==NULL){
        printf("Error opening file...");
        return;
    }
    Graph G = GRAPHload(fp);
    printf("Lettura completata\n");
    GRAPHprint(G);
    GRAPHdfs(G,0);
    GRAPHmstP(G);
    GRAPHspBF(G,3);
}

void LISTprova(){
    FILE *fp;
    Item item;

    if((fp  = fopen("../Liste/List.txt","r"))==NULL){
        printf("Error");
        return;
    }

    LIST  list = LISTinit();
    LISTload(fp, list);
    LISTprint(stdout, list);
    item = LISTsearch(list, 10);
    if(ITEMgetVal(item)!= -1)
        printf("Chiave %d trovata nella lista.\n", ITEMgetVal(item));
    else
        printf("Chiave non trovata nella lista.\n");

    LISTdelHead(list);
    printf("Eliminazione della prima chiave:\n ");
    LISTprint(stdout, list);

    LISTdelKey(list, 10);
    printf("Eliminazione della chiave 10:\n");
    LISTprint(stdout, list);
}

void CODEprova(){
    FILE *fp, *fp2;
    int heapSize,PQsize;
    PQ pq;

    if((fp = fopen("../Code/Heap.txt","r"))==NULL){
        printf("Error opening file");
        return;
    }

    if((fp2 = fopen("../Code/prova_PQ.txt","r"))==NULL) {
        printf("Error opening file");
        return;
    }

    fscanf(fp, "%d\n",&heapSize);

    printf("-------HEAP------\n");
    Heap heap = HEAPinit(heapSize);
    HEAPload(fp, heap, heapSize);
    printf("Letto da file la sequenza di interi (da trasformare in heap):\n");
    HEAPdisplay(stdout, heap);
    HEAPBuild(heap);
    printf("Heap dopo HEAPbuild:\n");
    HEAPdisplay(stdout, heap);
    HEAPsort(heap);
    printf("Heap dopo HEAPsort:\n");
    HEAPdisplay(stdout,heap);
    printf("\n\n");

    printf("-------PQ------\n");
    rewind(fp);
    fscanf(fp, "%d\n",&PQsize);
    pq = PQinit(PQsize);
    PQload(fp,pq, PQsize);
    printf("PQ letta da file:\n");
    PQdisplay(stdout,pq);
    fscanf(fp2, "%d\n",&PQsize);
    pq = PQinit(PQsize);
    PQload(fp2,pq, PQsize);
    printf("Configurazione finale PQ (Da file prova_PQ):\n"); //era un esercizio dell'esame
    PQdisplay(stdout,pq);
    PQfree(pq);
    HEAPfree(heap);
}

void BSTprova(){
    FILE *fp;
    BST bst;
    int N;

    if((fp = fopen("../BST/BST.txt","r"))==NULL){
        printf("Error opening file...");
        return;
    }

    fscanf(fp,"%d\n",&N);

    bst = BSTinit();
    BSTload(fp, bst, N);
    BSTvisit(bst, 0);
    printf("\n");
    BSTdelete(bst, 10);
    BSTvisit(bst, 0);
    printf("\n");

}