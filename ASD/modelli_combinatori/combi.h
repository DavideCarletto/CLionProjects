//
// Created by Federico Carollo on 28/10/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "util.h"

#ifndef MODELLI_COMBINATORI_COMBI_H

void perm_semplici(int *val, int len);
void disp_semplici(int *val, int len, int k);
void comb_semplici(int *val, int len, int k);
void disp_ripetute(int *val, int len, int k);
void perm_ripetute(int *val, int len);
void comb_ripetute(int *val, int len, int k);

void rec_perm_semplici(int* val, int* sol, int len, int pos, int* mark);
void rec_disp_semplici(int* val, int* sol, int len, int pos, int* mark, int k);
void rec_comb_semplici(int* val, int* sol, int len, int pos, int start, int k);
void rec_disp_ripetute(int* val, int* sol, int len, int pos, int k);
void rec_perm_ripetute(int* val, int* sol, int len, int pos, int* mark);
void rec_comb_ripetute(int* val, int* sol, int len, int pos, int start, int k);


//#region wrapper
void perm_semplici(int *val, int len){
    int* mark = (int*) calloc(len, sizeof(int));    //in modo che vengano inizializzati a 0
    int* sol = (int*) malloc(sizeof(int)*len);
    rec_perm_semplici(val, sol, len, 0, mark);
}
void disp_semplici(int *val, int len, int k){
    int* mark = (int*) calloc(len, sizeof(int));    //in modo che vengano inizializzati a 0
    int* sol = (int*) malloc(sizeof(int)*k);
    rec_disp_semplici(val, sol, len, 0, mark, k);
}
void comb_semplici(int *val, int len, int k){
    int* sol = (int*) malloc(sizeof(int)*k);
    rec_comb_semplici(val, sol, len, 0, 0, k);
}

void disp_ripetute(int* val, int len, int k){
    int* sol = (int*) malloc(sizeof(int)*k);
    rec_disp_ripetute(val, sol, len, 0, k);
}

void perm_ripetute(int* val, int len){
    int* occ, *slim_v, *sol;
    int new_len;    //numero di elementi diversi
    sol = (int*) malloc(sizeof(int)*len);
    qsort(val, len, sizeof(val[0]), cmp_int);
    new_len = filterArray(val, len, &occ, &slim_v);

    for (int i = 0; i < new_len; ++i) {
        printf("%d appare %d volte\n", slim_v[i], occ[i]);
    }

    rec_perm_ripetute(slim_v, sol, new_len, 0, occ);
}
void comb_ripetute(int *val, int len, int k){
    int* sol = (int*) malloc(sizeof(int)*k);
    rec_comb_ripetute(val, sol, len, 0, 0, k);
}

//#endregion

//#region recursive functions
/**
 *
 * @param val sequenza di valori
 * @param sol vettore contenente la soluzione corrente
 * @param pos posizione corrente dove salvare la soluzione parziale
 * @param mark vettore che ricorda se l'elemento in posizione i è già preso
 */
void rec_perm_semplici(int* val, int* sol, int len, int pos, int* mark){
    if(pos>=len){   //condizione di terminazione
        for (int i = 0; i < len; ++i) {
            printf("%d ", sol[i]);
        }
        putchar('\n');
        return;
    }

    for (int i = 0; i < len; ++i) {
        if(mark[i] == 0){   //se l'elemento i-esimo non è ancora stato preso
            mark[i] = 1;    //segna l'elemento come preso (non verrà più usato per la permutazione corrente)
            sol[pos] = val[i];
            rec_perm_semplici(val, sol, len, pos+1, mark);
            mark[i] = 0;    //smarca l'elemento in modo che possa apparire in un'altra posizione
        }
    }
}

/**
 *
 * @param val sequenza di valori
 * @param sol vettore contenente la soluzione corrente
 * @param pos posizione corrente dove salvare la soluzione parziale
 * @param mark vettore che ricorda se l'elemento in posizione i è già preso
 * @param k lunghezza soluzione
 */
void rec_disp_semplici(int* val, int* sol, int len, int pos, int* mark, int k){
    if(pos>=k){   //condizione di terminazione
        for (int i = 0; i < k; ++i) {
            printf("%d ", sol[i]);
        }
        putchar('\n');
        return;
    }

    for (int i = 0; i < len; ++i) {
        if(mark[i] == 0){   //se l'elemento i-esimo non è ancora stato preso
            mark[i] = 1;    //segna l'elemento come preso (non verrà più usato per la permutazione corrente)
            sol[pos] = val[i];
            rec_disp_semplici(val, sol, len, pos+1, mark, k);
            mark[i] = 0;    //smarca l'elemento in modo che possa apparire in un'altra posizione
        }
    }
}

/**
 *
 * @param val sequenza di valori
 * @param sol vettore contenente la soluzione corrente
 * @param pos posizione corrente dove salvare la soluzione parziale
 * @param start indice da cui partire per il ciclo for: selezionato un elemento, quelli successivi possono
 * essere selezionati solamente tra quelli posizionalmente dopo quello corrente
 * @param k lunghezza soluzione
 */
void rec_comb_semplici(int* val, int* sol, int len, int pos, int start, int k){
    if(pos>=k){ //terminazione
        for (int i = 0; i < k; ++i) {
            printf("%d ", sol[i]);
        }
        putchar('\n');
        return;
    }

    for (int i = start; i < len; ++i) {
        sol[pos] = val[i];
        //start parte dall'elemento dopo quello considerato, tanto l'ordine non conta quindi tutte le combinazioni prima
        //sono già state prese in considerazione
        rec_comb_semplici(val, sol, len, pos+1, i+1, k);
    }
}

void rec_disp_ripetute(int* val, int* sol, int len, int pos, int k){
    if(pos>=k){   //condizione di terminazione
        for (int i = 0; i < k; ++i) {
            printf("%d ", sol[i]);
        }
        putchar('\n');
        return;
    }


    for (int i = 0; i < len; ++i) {
        sol[pos] = val[i];  //metti elemento in soluzione
        rec_disp_ripetute(val, sol, len, pos+1, k); //metti ogni possibile altro elemento
    }
}

void rec_perm_ripetute(int* val, int* sol, int len, int pos, int* mark){
    if(pos>=len){   //condizione di terminazione
        for (int i = 0; i < len; ++i) {
            printf("%d ", sol[i]);
        }
        putchar('\n');
        return;
    }

    for (int i = 0; i < len; ++i) {
        if(mark[i]>0){  //stesso principio delle permutazioni semplici, ma il numero indica quante volte val[i] può essere
            //ancora preso
            mark[i]--;
            sol[pos] = val[i];
            rec_perm_ripetute(val, sol, len, pos+1, mark);
            mark[i]++;
        }
    }
}

void rec_comb_ripetute(int* val, int* sol, int len, int pos, int start, int k){
    if(pos>=k){ //terminazione
        for (int i = 0; i < k; ++i) {
            printf("%d ", sol[i]);
        }
        putchar('\n');
        return;
    }

    for (int i = start; i < len; ++i) {
        sol[pos] = val[i];
        //start parte dall'elemento corrente, perché può essere ripetuto più volte
        rec_comb_ripetute(val, sol, len, pos+1, start, k);
        start++;    //va a pari passo con l'incremento di i, analogo a start = i+1
    }
}
//#endregion



#define MODELLI_COMBINATORI_COMBI_H

#endif //MODELLI_COMBINATORI_COMBI_H
