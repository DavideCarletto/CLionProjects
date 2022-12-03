#include <stdio.h>
#include <stdlib.h>

/*
  uno zaffiro deve essere seguito immediatamente o da un altro zaffiro o da un rubino
  uno smeraldo deve essere seguito immediatamente o da un altro smeraldo o da un topazio
  un rubino deve essere seguito immediatamente o da uno smeraldo o da un topazio
  un topazio deve essere seguito immediatamente o da uno zaffiro o da un rubino.

 Suggerimento: affrontare il problema con la tecnica del divide et impera, osservando che una
collana di lunghezza P può essere definita ricorsivamente come:

  la collana vuota, formata da P=0 gemme
  una gemma seguita da una collana di P-1 gemme.

Poiché vi sono 4 tipi di gemme Z, R, T, S, si scrivano 4 funzioni fZ, fR, fT, fS che calcolino la
lunghezza della collana più lunga iniziante rispettivamente con uno zaffiro, un rubino, un topazio
e uno smeraldo avendo a disposizione z zaffiri, r rubini, t topazi e s smeraldi. Note le regole di
composizione delle collane, è possibile esprimere ricorsivamente il valore di una certa funzione
fX sulla base dei valori delle altre funzioni.
Si presti attenzione a definire adeguatamente i casi terminali di tali funzioni, onde evitare di ricorre
in porzioni non ammissibili dello spazio degli stati.
Si ricorda che il paradigma della memoization prevede di memorizzare le soluzioni dei
sottoproblemi già risolti in opportune strutture dati da progettare e dimensionare e di riusare dette
soluzioni qualora si incontrino di nuovo gli stessi sottoproblemi, limitando l’uso della ricorsione
alla soluzione dei sottoproblemi non ancora risolti.
 */

typedef enum{
    zaffiro, rubino, topazio, smeraldo
}pietra;

void leggiFile(FILE *fp, int *val,int *dim);
int fZ(int *val, int len, int max);
int fR(int *val, int len, int max);
int fT(int *val, int len, int max);
int fS(int *val, int len, int max);
int calcolaMax(int *val, int lenMax);
void allocaVal(int **val, int dim);
int trovaMax(int *maxPietre);

int main() {
    int *val, dim = 0;
    FILE *fp;

    if((fp = fopen("../E2/hard_test_set.txt","r"))==  NULL){
        printf("Error opening file...");
        return 1;
    }
    if(!feof(fp)){
        fscanf(fp,"%d",&dim);
    }

    allocaVal(&val, 4);
    leggiFile(fp, val,&dim);

    free(val);
    return 0;
}

void leggiFile(FILE *fp, int *val,int *dim) {
    int max, count = 1;

    while (!feof(fp)) {
        for (int i = 0; i < *dim; i++) {
            if (!feof(fp))
                fscanf(fp, "%d %d %d %d\n", &val[0], &val[1], &val[2], &val[3]);
            max = val[0] + val[1] + val[2] + val[3];
            printf("TEST #%d\n", count);
            count++;
            printf("zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n", val[0], val[1], val[2], val[3],max);
            max = calcolaMax(val,max);
            printf("Collana massima di lunghezza %d\n",max);
        }
    }
}

int calcolaMax(int *val, int lenMax){
    int maxPietre[4];

    val[zaffiro]--;
    maxPietre[zaffiro] = 1+fZ(val, lenMax-1,0);
    val[zaffiro]++;

    val[rubino]--;
    maxPietre[rubino] = 1+fR(val, lenMax-1,0);
    val[rubino]++;

    val[topazio]--;
    maxPietre[topazio] = 1+fT(val, lenMax-1,0);
    val[topazio]++;

    val[smeraldo]--;
    maxPietre[smeraldo] = 1+fS(val, lenMax-1,0);
    val[smeraldo]++;

//    printf("%d %d %d %d", maxPietre[0], maxPietre[1], maxPietre[2], maxPietre[3]);
    return trovaMax(maxPietre);

}

void allocaVal(int **val, int dim) {
    (*val) = (int *) malloc(dim * sizeof(int));
}

int fZ(int *val, int len, int max){

    if(len == 0)
        return 0;

    if(val[zaffiro]>0){
        val[zaffiro]--;
        max = 1+fZ(val, len-1,max);
        val[zaffiro]++;
    }
    else if(val[rubino]>0){
        val[rubino]--;
        max = 1+fR(val, len-1,max);
        val[rubino]++;
    }

    return max;
}

int fR(int *val, int len, int max){
    if(len == 0)
        return 0;

    if(val[smeraldo]>0){
        val[smeraldo]--;
        max = 1+fS(val, len-1,max);
        val[smeraldo]++;
    }
    else if(val[topazio]>0){
        val[topazio]--;
        max = 1+fT(val, len-1,max);
        val[topazio]++;
    }
    return max;
}

int fT(int *val, int len, int max){

    if(len == 0)
        return 0;
    if(val[zaffiro]>0){
        val[zaffiro]--;
        max = 1+fZ(val, len-1,max);
        val[zaffiro]++;
    }
    else if(val[rubino]>0){
        val[rubino]--;
        max = 1+fR(val, len-1,max);
        val[rubino]++;
    }
    return max;
}

int fS(int *val, int len, int max){
    if(len == 0)
        return 0;
    if(val[smeraldo]>0){
        val[smeraldo]--;
        max = 1+fS(val, len-1,max);
        val[smeraldo]++;
    }
    else if(val[topazio]>0){
        val[topazio]--;
        max = 1+fT(val, len-1,max);
        val[topazio]++;
    }
    return max;
}

int trovaMax(int *maxPietre){
    int max =0;

    for(int i=0; i<4;i++){
        if(maxPietre[i]>max)
            max = maxPietre[i];
    }
    return max;
}