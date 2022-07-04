#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITER 500000

typedef struct Pair pair;

struct Pair{
    int num1;
    int num2;
};


pair* readPairs(const char* filename, int* len);

void setNum(pair* _pair, int num1,int num2);

int* genGraph(int min, int max, int* graphLen);

void printPair(pair _pair);
void printV(int v[], int len);

void quick_find(pair pairs[],int len, int graph[], int* graphLen);
void quick_union(pair pairs[],int len, int graph[], int* graphLen);
void weigthed_quick_union(pair pairs[],int len, int graph[], int* graphLen);

int main() {

    int len, graphLen;
    pair* pairs = readPairs("../pairs.txt", &len);
    /*clock_t start, diff;
    start = clock();
    for (int i = 0; i < MAX_ITER; ++i) {
        quick_find(pairs, len, genGraph(0,9,&graphLen), &graphLen);
    }
    diff = clock()-start;
    printf("ms: %d\n", diff*1000/CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < MAX_ITER; ++i) {
        quick_union(pairs, len, genGraph(0,9,&graphLen), &graphLen);
    }
    diff = clock()-start;
    printf("ms: %d\n", diff*1000/CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < MAX_ITER; ++i) {
        weigthed_quick_union(pairs, len, genGraph(0,9,&graphLen), &graphLen);
    }
    diff = clock()-start;
    printf("ms: %d", diff*1000/CLOCKS_PER_SEC);*/
    quick_find(pairs, len, genGraph(0,9,&graphLen), &graphLen);

    quick_union(pairs, len, genGraph(0,9,&graphLen), &graphLen);
    weigthed_quick_union(pairs, len, genGraph(0,9,&graphLen), &graphLen);
    return 0;
}

//Si basa sul salvare direttamente il riferimento del padre:
/**
 * Ricerca: O(1) accesso diretto al padre
 * Union: O(n)  scan di tutto il vettore
 * Complessivo: O(n)
 */
void quick_find(pair pairs[],int len, int graph[], int* graphLen){
    //printf("Quick find\n");
    int num1, num2;
    int temp;
    for (int i = 0; i < len; ++i) {
        num1 = pairs[i].num1;
        num2 = pairs[i].num2;
        printPair(pairs[i]);
        if(graph[num1]!=graph[num2]){
            temp = graph[num1];
            for (int j = 0; j < *graphLen; ++j) {
                if(graph[j] == temp){
                    graph[j] = graph[num2];
                }
            }
        }
        printV(graph, *graphLen);
    }
}


//Si basa sul salvare la gerarchia corrente, non il padre
/* Ricerca: O(n)
 * Union: O(1)
 * Costo: O(n)
 * */
void quick_union(pair pairs[],int len, int graph[], int* graphLen){
    printf("Quick union\n");
    int num1, num2;
    for (int i = 0; i < len; ++i) {
        for (num1 = pairs[i].num1; num1!=graph[num1]; num1 = graph[num1]);
        for (num2 = pairs[i].num2; num2!=graph[num2]; num2 = graph[num2]);
        if(num1!=num2){
            graph[num1] = num2;
        }

        printPair(pairs[i]);
        printV(graph, *graphLen);
    }
}

/*
 * Come la quick union, ma l'aggiunta va dall'albero
 * più piccolo a quello più grande
 */
void weigthed_quick_union(pair pairs[],int len, int graph[], int* graphLen){
    printf("Weigthed quick union\n");
    int tree[*graphLen];
    int num1, num2;
    for (int i = 0; i < *graphLen; ++i) {
        tree[i] = 1;
    }

    for (int i = 0; i < len; ++i) {
        for (num1 = pairs[i].num1; num1!=graph[num1]; num1 = graph[num1]);
        for (num2 = pairs[i].num2; num2!=graph[num2]; num2 = graph[num2]);
        if(num1!=num2){
            if(tree[num1]>tree[num2]){
                graph[num2] = num1;
                tree[num1] += tree[num2];
            } else{
                graph[num1] = num2;
                tree[num2] += tree[num1];
            }

        }

        printPair(pairs[i]);
        printV(graph, *graphLen);
    }
}


void setNum(pair* _pair, int num1,int num2){
    _pair->num1 = num1;
    _pair->num2 = num2;
}

pair* readPairs(const char* filename, int *len){
    pair* pairs;
    int num1, num2;
    FILE *fp = fopen(filename,"r");
    fscanf(fp,"%d\n",len);
    pairs = (pair*) malloc(sizeof(pair)*(*len));

    for(int i=0; fscanf(fp,"%d %d\n", &num1,&num2)!=EOF;i++){
        setNum(&pairs[i],num1,num2);
    }
    return pairs;
}

int* genGraph(int min, int max, int* graphLen){
    int* graph = (int*) malloc(sizeof(int)*((max-min)+1));
    *graphLen = max-min+1;

    for (int i = 0; i < *graphLen; ++i) {
        graph[i] = min+i;
    }
    return graph;
}


void printPair(pair _pair){
    printf("num1: %d\tnum2: %d\n", _pair.num1, _pair.num2);
}

void printV(int v[], int len){
    for (int i = 0; i < len; ++i) {
        printf("%d ", v[i]);
    }
    putchar('\n');
}