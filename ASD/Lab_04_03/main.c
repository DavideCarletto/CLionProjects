#include <stdio.h>
#include <stdlib.h>

/*
 Un gioielliere ha a disposizione z zaffiri, r rubini, t topazi e s smeraldi per creare una collana infilando una pietra
 dopo l’altra. Deve però soddisfare le seguenti regole:

  uno zaffiro deve essere seguito immediatamente o da un altro zaffiro o da un rubino
  uno smeraldo deve essere seguito immediatamente o da un altro smeraldo o da un topazio
  un rubino deve essere seguito immediatamente o da uno smeraldo o da un topazio
  un topazio deve essere seguito immediatamente o da uno zaffiro o da un rubino.

 Si scriva una funzione C che calcoli la lunghezza e visualizzi la composizione di una collana a lunghezza massima che rispetti
 le regole di cui sopra. La lunghezza della collana è il numero di pietre preziose che la compongono.

 Osservazione: la lunghezza della soluzione non è nota a priori, ma può variare tra 1 e (z+r+t+s).

 Suggerimento: l'esercizio può essere risolto adottando un approccio simile a quello delle disposizioni con ripetizione,
 visto a lezione, se opportunamente adottato ai requisiti del problema. Una volta impostato il modello ricorsivo, si scriva
 poi la funzione di filtro (verifica di accettabilità) e di ottimizzazione. Si valuti infine la possibilità di introdurre
 criteri di pruning.
 */
typedef enum{
    zaffiro, rubino, topazio, smeraldo
}pietra;

void leggiFile(FILE *fp, int *val,int *sol, int *dim);
int disp_ripetute(int *val, int *sol, int len, int pos, int last, int k, int max);
void allocaVal(int **val, int dim);
int check(int last, int cur);

int main() {
    int *val, *sol, dim = 0;
    FILE *fp;

    if((fp = fopen("../E3/easy_test_set.txt","r"))==  NULL){
        printf("Error opening file...");
        return 1;
    }
    if(!feof(fp)){
        fscanf(fp,"%d",&dim);
    }

    allocaVal(&val, dim);
    leggiFile(fp, val, sol,&dim);

    free(val);
    return 0;
}

void leggiFile(FILE *fp, int *val, int *sol,int *dim){
    int max = 0, count =1, found = 0,k, len =4 , pos =0, last = -1;

    while(!feof(fp)) {
        for (int i = 0; i < *dim; i++) {
            if(!feof(fp))
            fscanf(fp, "%d %d %d %d\n", &val[0], &val[1], &val[2], &val[3]);
            max = val[0] + val[1] + val[2] + val[3];
            sol = (int *) malloc(max * sizeof (int));

            printf("TEST #%d\n", count);
            count++;
            printf("zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n", val[0], val[1], val[2], val[3],
                   max);
            for (k = max; k > 0 && !found; k--) {
                found = disp_ripetute(val, sol, len, pos, last, k, max);
            }
            printf("Collana massima di lunghezza %d\n", k + 1);
            found = 0;
            free(sol);
        }
    }
}

int disp_ripetute(int *val, int *sol, int len, int pos, int last, int k, int max){

    if(pos>=k){
//        for(int i=0; i<k; i++){
//            switch (sol[i]) {
//                case zaffiro:
//                    printf("zaffiro ");
//                    break;
//                case rubino:
//                    printf("rubino ");
//                    break;
//                case topazio:
//                    printf("topazio ");
//                    break;
//                case smeraldo:
//                    printf("smeraldo ");
//                    break;
//            }
//        }
//        printf("\n");
        return 1;
    }

    for(int i=0; i< len; i++){
        if(val[i]>0 &&  (check(last, i))) {
            sol[pos] = i;
            val[i]--;
            if(disp_ripetute(val, sol, len, pos + 1, i,k, max)) return 1;
            val[i]++;
        }
    }
    return 0;
}

void allocaVal(int **val, int dim){
        (*val) = (int *) malloc(dim* sizeof (int));
}

int check(int last, int cur){
    if(last ==-1 || ((last == zaffiro || last == topazio) && ((cur == zaffiro)|| (cur == rubino)))
    || ((last == smeraldo ||last == rubino) && ((cur == smeraldo)|| (cur == topazio))))
    return 1;

    return 0;
}
