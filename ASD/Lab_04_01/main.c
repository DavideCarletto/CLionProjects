#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num_scelte;
    int *scelte;
}Livello;

int princ_molt(int pos, Livello *val, int *sol, int k, int cnt);


int main() {
    Livello *elencoVal = (Livello *) malloc(10*sizeof (Livello));
    int *sol = (int *) malloc(10*sizeof (int));

    int valore1[5] = {1,2,3,4,5}, valore2[3] = {6,7,8}, cnt=0;
    Livello n1,n2;

    n1.num_scelte = 5;
    n2.num_scelte = 3;

    n1.scelte = valore1;
    n2.scelte = valore2;

    elencoVal[0] = n1;
    elencoVal[1] = n2;

    cnt = princ_molt(0,elencoVal, sol, 2,cnt);

    printf("%d", cnt);
    return 0;
}


int princ_molt(int pos, Livello *val, int *sol, int k, int cnt){
    int i;

    if(pos>=k){
        for( i=0; i<k; i++){
            printf("%d ",sol[i]);
        }
        printf("\n");
        return cnt+1;
    }

    for(i=0; i < val[pos].num_scelte;i++){
        sol[pos] = val[pos].scelte[i];
        cnt = princ_molt(pos+1, val, sol, k, cnt);
    }

    return cnt;

}
