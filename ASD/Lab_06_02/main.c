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
int fZ(int *****m, int *val, int len, int max);
int fR(int *****m, int *val, int len, int max);
int fT(int *****m, int *val, int len, int max);
int fS(int *****m, int *val, int len, int max);
int calcolaMax(int *val, int lenMax);
void allocaVal(int **val, int dim);
int trovaMax(int *maxPietre);
int trovaMaggiore(int a, int b);
int *****malloc5d(int maxZ, int maxR, int maxT, int maxS);
void dealloca5d(int *****m, int maxZ, int maxR, int maxT);

int main() {
    int *val, dim = 0;
    FILE *fp;

    if((fp = fopen("../hard_test_set.txt","r"))==  NULL){
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
    int maxPietre[4], *****m;

    m = malloc5d(val[0]+1, val[1]+1, val[2]+1, val[3]+1);

    maxPietre[zaffiro] = fZ(m,val, lenMax,0);
    maxPietre[rubino] = fR(m,val, lenMax,0);
    maxPietre[topazio] = fT(m,val, lenMax,0);
    maxPietre[smeraldo] = fS(m,val, lenMax,0);

    dealloca5d(m,val[0]+1, val[1]+1, val[2]+1);

    return trovaMax(maxPietre);

}

void allocaVal(int **val, int dim) {
    (*val) = (int *) malloc(dim * sizeof(int));
}

int fZ(int *****m, int *val, int len, int max){
    int maxZ=0, maxR=0;

    if(m[zaffiro][val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]] != -1)
        return m[zaffiro][val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]];

    if(len == 0)
        return 0;

    if(val[zaffiro]>0){
        val[zaffiro]--;
        maxZ = 1+fZ(m,val, len-1,max);
        maxR = 1+fR(m,val, len-1, max);
        val[zaffiro]++;
    }

    max = trovaMaggiore(maxZ,maxR);
    m[zaffiro][val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]] = max;

    return max;
}

int fR(int *****m, int *val, int len, int max){
    int maxS=0, maxT=0;

    if(m[rubino][val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]] != -1)
        return m[rubino][val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]];

    if(len == 0)
        return 0;

    if(val[rubino]>0){
        val[rubino]--;
        maxS = 1+fS(m,val, len-1,max);
        maxT = 1+fT(m,val, len-1, max);
        val[rubino]++;
    }

    max = trovaMaggiore(maxS,maxT);
    m[rubino][val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]] = max;

    return max;
}

int fT(int *****m, int *val, int len, int max){
    int maxZ=0, maxR=0;

    if(m[topazio][val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]] != -1)
        return m[topazio][val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]];

    if(len == 0)
        return 0;

    if(val[topazio]>0){
        val[topazio]--;
        maxZ = 1+fZ(m,val, len-1,max);
        maxR = 1+fR(m,val, len-1,max);
        val[topazio]++;

    }

    max = trovaMaggiore(maxZ, maxR);
    m[topazio][val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]] = max;

    return max;
}

int fS(int *****m, int *val, int len, int max){
    int maxS=0, maxT=0;

    if(m[smeraldo][val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]] != -1)
        return m[smeraldo][val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]];

    if(len == 0)
        return 0;

    if(val[smeraldo]>0){
        val[smeraldo]--;
        maxS = 1+fS(m,val, len-1,max);
        maxT = 1+fT(m,val, len-1,max);
        val[smeraldo]++;
    }

    max = trovaMaggiore(maxS,maxT);
    m[smeraldo][val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]] = max;

    return max;
}

int trovaMaggiore(int a, int b){
    if(a>=b)
        return a;

    return b;
}

int trovaMax(int *maxPietre){
    int max =0;

    for(int i=0; i<4;i++){
        if(maxPietre[i]>max)
            max = maxPietre[i];
    }
    return max;
}

int *****malloc5d(int maxZ, int maxR, int maxT, int maxS){
    int ***** m;
    int i,z,r,t,s;

    m = (int *****) malloc(4*sizeof (int ****));

    for(i=0;i<4;i++){
        m[i] = (int ****) malloc(maxZ *sizeof (int ***));
        for(z=0; z< maxZ; z++){
            m[i][z] = (int ***) malloc(maxR *sizeof (int **));
            for ( r = 0; r < maxR; r++) {
                m[i][z][r] = (int **) malloc(maxT*sizeof (int *));
                for(t =0; t<maxT; t++){
                    m[i][z][r][t] = (int *) malloc(maxS *sizeof (int));
                }
            }
        }
    }

    for(i=0; i<4;i++)
        for(z=0;z<maxZ;z++)
            for(r=0;r<maxR;r++)
                for(t=0;t<maxT;t++)
                    for(s=0;s<maxS;s++)
                        m[i][z][r][t][s]=-1;

    return m;
}

void dealloca5d(int *****m, int maxZ, int maxR, int maxT){

    for(int i=0; i<4;i++){
        for(int z =0; z<maxZ; z++){
            for(int r=0; r<maxR; r++){
                for(int t =0; t<maxT; t++){
                    free(m[i][z][r][t]);
                }
                free(m[i][z][r]);
            }
            free(m[i][z]);
        }
        free(m[i]);
    }
    free(m);
}